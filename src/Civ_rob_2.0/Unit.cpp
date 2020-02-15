/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.18
	file version : 1.10

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Civ_rob_2.0

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "Unit.h"
#include "IHM.h"
#include "LoadConfig.h"

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */

/* *********************************************************
 *					START Unit::STATIC					   *
 ********************************************************* */

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : loadUnitAndSpec															   */
/* ROLE : Chargement des informations concernant les unités à partir d'un fichier	   */
/* INPUT : const std::string& : nom du fichier à ouvrir								   */
/* OUTPUT : std::vector<Unit_Struct>& : Vecteur des Unit							   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::loadUnitAndSpec
(
	const std::string& UNIT,
	std::vector<Unit_Struct>& tabUnit_Struct
)
{
	tinyxml2::XMLDocument texteFile;
	texteFile.LoadFile(UNIT.c_str());

	const char* root("Root");

	const char	* s_Unit("Unit"),
					* s_Name("Name"),
					* s_Life("Life"),
					* s_Atq("Atq"),
					* s_Def("Def"),
					* s_Mouvement("Mouvement"),
					* s_Level("Level");

	tinyxml2::XMLNode* node(texteFile.FirstChildElement(root)->FirstChildElement(s_Unit));
	Unit_Struct currentUnit;

	while (node != nullptr)
	{
		currentUnit.name = node->FirstChildElement(s_Name)->GetText();
		node->FirstChildElement(s_Life)->QueryIntText((int*)&currentUnit.life);
		node->FirstChildElement(s_Atq)->QueryIntText((int*)& currentUnit.atq);
		node->FirstChildElement(s_Def)->QueryIntText((int*)& currentUnit.def);
		node->FirstChildElement(s_Mouvement)->QueryIntText((int*)& currentUnit.movement);
		node->FirstChildElement(s_Level)->QueryIntText((int*)& currentUnit.level);
		
		tabUnit_Struct.push_back(currentUnit);

		/* Recherche du noeud Model suivant */
		node = node->NextSibling();
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : searchunit																   */
/* ROLE : Sélection du nom de l'unité à partir de l'index du tableau				   */
/* INPUT/OUTPUT : struct Map& : données générale de la map : taille					   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::searchUnit
(
	SubcatPlayer& s_player
)
{
	s_player.unitNameToCreate = s_player.tabUnit_Struct[s_player.unitToCreate].name;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : searchUnitTile															   */
/* ROLE : Cherche l'unité étant dans la case séléctionné							   */
/* INPUT/OUTPUT : SubcatPlayer& s_player : structure concernant un joueur			   */
/* INPUT : const KeyboardMouse& mouse : données générale des entrées utilisateur	   */
/* INPUT : const Map& map : données générale de la map								   */
/* INPUT/OUTPUT : std::vector<Player*>& tabplayer : Vecteur de joueurs				   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::searchUnitTile
(
	SubcatPlayer& s_player,
	const KeyboardMouse& mouse,
	const Map& map,
	std::vector<Player*>& tabplayer
)
{
	for (unsigned int i(0); i <tabplayer[s_player.selectplayer]->GETtabUnit().size(); i++)
	{
		if (tabplayer[s_player.selectplayer]->GETtheUnit(i)->testPos
				(
					mouse.GETmouse_x() + map.screenOffsetXIndexMin * map.tileSize,
					mouse.GETmouse_y() + map.screenOffsetYIndexMin * map.tileSize
				)
			)
		{
			s_player.selectunit = i;
			s_player.unitNameToMove = tabplayer[s_player.selectplayer]->GETtheUnit(i)->GETname();

			tabplayer[s_player.selectplayer]->GETtheUnit(i)->SETblit(true);
			break;
		}
		else
		{
			/* N/A */
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : tryToMove																	   */
/* ROLE : Recherche à faire bouger l'unité selon le contexte						   */
/* ROLE : Attention : contient un rappel récursif									   */
/* INPUT : const std::vector<std::vector<Tile>>& : Matrice de la MAP				   */
/* INPUT/OUTPUT : Struct SubcatPlayer& : structure concernant un joueur				   */
/* INPUT/OUTPUT : std::vector<Player*>& : Vecteur de joueurs						   */
/* INPUT : Select_Type : état de la sélection du joueur (enum Select_Type : Uint8)	   */
/* INPUT : int x : pos X															   */
/* INPUT : int y : pos Y															   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::tryToMove
(
	const std::vector<std::vector<Tile>>& maps,
	SubcatPlayer& s_player,
	std::vector<Player*>& tabplayer,
	Select_Type select,
	int x,
	int y
)
{
	switch (searchToMove(maps, s_player, tabplayer, x, y))
	{
	case cannotMove:
		/*
		* N/A
		*/
		break;
	case canMove:

		tabplayer[s_player.selectplayer]
			->GETtheUnit(s_player.selectunit)
				->move(select, s_player.selectunit, x, y);
		break;
	case attackMove:

		tabplayer[s_player.selectplayer]
			->GETtheUnit(s_player.selectunit)
				->attack(tabplayer[s_player.selectPlayerToAttack]
					->GETtheUnit(s_player.selectUnitToAttack));

		if	(
				tabplayer[s_player.selectPlayerToAttack]
					->GETtheUnit(s_player.selectUnitToAttack)
						->GETalive()
				==
				false
			)
		{
			tabplayer[s_player.selectPlayerToAttack]
				->deleteUnit(s_player.selectUnitToAttack);
			tryToMove(maps, s_player, tabplayer, select, x, y);
		}
		tabplayer[s_player.selectplayer]
			->GETtheUnit(s_player.selectunit)->SETmovement(0);
		break;
	default:
		/* N/A */
		break;
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : searchToMove																   */
/* ROLE : Recherche à faire bouger l'unité selon le contexte						   */
/* ROLE : Action conditionnelle (case libre, ennemi, amis)							   */
/* INPUT : const std::vector<std::vector<Tile>>& : Matrice de la MAP			   	   */
/* INPUT : Struct SubcatPlayer& : structure concernant un joueur					   */
/* INPUT : const std::vector<Player*>& : Vecteur de joueurs							   */
/* INPUT : int x : pos X														   	   */
/* INPUT : int y : pos Y															   */
/* RETURNED VALUE : Move_Type : / 0 : ne bouge pas / 1 : case libre : peut bouger	   */
/* RETURNED VALUE : Move_Type : / 2 : ennemi : ne bouge pas							   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Move_Type Unit::searchToMove
(
	const std::vector<std::vector<Tile>>& maps,
	SubcatPlayer& s_player,
	const std::vector<Player*>& tabplayer,
	int x,
	int y
)
{

	/* ---------------------------------------------------------------------- */
	/* conditions de mouvement :											  */
	/*	- que la case cible soit du sol et									  */
	/*		- que la case cible est libre									  */
	/*		- ou que la case cible est occupée par un ennemi				  */
	/*		  susceptible de mourrir par l'attaque							  */
	/* ---------------------------------------------------------------------- */

	bool onGround = false;

	for (unsigned int i(0); i < maps.size(); i++)
	{
		for (unsigned int j(0); j < maps[i].size(); j++)
		{
			if	(checkNextTile
					(
						maps[i][j],
						tabplayer[s_player.selectplayer]->GETtheUnit(s_player.selectunit),
						x, y
					)
				)
			{
				if (maps[i][j].tile_ground == grass)
				{
					onGround = true;
					break;
				}
				else
				{
					/* N/A */
				}
			}
			else
			{
				/* N/A */
			}
		}
	}

	if (onGround)
	{
		/* On ground */

		for (unsigned int i = 0; i < tabplayer.size(); i++) 
		{
			for (unsigned int j = 0; j < tabplayer[i]->GETtabUnit().size(); j++) 
			{
				if	(checkUnitNextTile
						(
							tabplayer[s_player.selectplayer]->GETtheUnit(s_player.selectunit),
							tabplayer[i]->GETtheUnit(j),
							x, y
						)	
					)
				{
					if (s_player.selectplayer == (int)i)
					{
						return cannotMove;
					}		
					else
					{
						s_player.selectPlayerToAttack = (int)i;
						s_player.selectUnitToAttack = (int)j;
						return attackMove;
					}
				}
				else
				{
					/* N/A */
				}
			}
		}
	}
	else
	{
		/* Not on ground */

		return cannotMove;
	}	
	return canMove;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : checkUnitNextTile															   */
/* ROLE : Check des équalités des positions des Units avec + x et +y				   */
/* INPUT : const Unit* from : Unit avec un mouvement possible + x + y				   */
/* INPUT : const Unit* from : Unit aux positions + x + y							   */
/* INPUT : int x : delta horizontal tileSize en fonction du cardinal				   */
/* INPUT : int y : delta vertical tileSize en fonction du cardinal					   */
/* RETURNED VALUE : bool : false->position différente / true->même positions		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Unit::checkUnitNextTile
(
	const Unit* from,
	const Unit* to,
	int x,
	int y
)
{
	if ((from->GETx() + x) == to->GETx())
	{
		if ((from->GETy() + y) == to->GETy())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : checkNextTile																   */
/* ROLE : Check des équalités des positions des Units avec + x et +y				   */
/* INPUT : const Tile& from : Tile à tester											   */
/* INPUT : const Unit* from : Unit aux positions + x + y							   */
/* INPUT : int x : delta horizontal tileSize en fonction du cardinal				   */
/* INPUT : int y : delta vertical tileSize en fonction du cardinal					   */
/* RETURNED VALUE : bool : false->position différente / true->même positions		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Unit::checkNextTile
(
	const Tile& from,
	const Unit* to,
	int x,
	int y
)
{
	if ((from.tile_x + x) == to->GETx())
	{
		if ((from.tile_y + y) == to->GETy())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : irrigate																	   */
/* ROLE : 	TODO																	   */
/* RETURNED VALUE : bool															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Unit::irrigate
(
	Sysinfo&
)
{
	return false;
}

/* *********************************************************
 *					END Units::STATIC					   *
 ********************************************************* */


/* *********************************************************
 *				START Units::METHODS					   *
 ********************************************************* */

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Unit																		   */
/* ROLE : Constructeur par défaut													   */
/* INPUT : void																		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Unit::Unit() :	_name(""), _x(0), _y(0),
				_maxlife(0), _maxatq(0), _maxdef(0), _maxmovement(0), _maxlevel(0),
				_life(100), _atq(10), _def(5), _movement(1), _level(1), _alive(true), _blit(0), _show(true)
{
	LoadConfig::logfileconsole("[INFO]___: Create Unit Par Defaut Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Unit																		   */
/* ROLE : Constructeur par complet													   */
/* INPUT : const std::string &name : nom											   */
/* INPUT : unsigned int x :	position en x sur la map								   */
/* INPUT : unsigned int y : position en y sur la map								   */
/* INPUT : unsigned int life : vie max												   */
/* INPUT : unsigned int atq	: atq max												   */
/* INPUT : unsigned int def	: def max												   */
/* INPUT : unsigned int move : move max												   */
/* INPUT : unsigned int level : level 1												   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Unit::Unit
(
	const std::string &name,
	unsigned int x,
	unsigned int y,
	unsigned int life,
	unsigned int atq,
	unsigned int def,
	unsigned int move,
	unsigned int level
)
	: _name(name), _x(x), _y(y),
	_maxlife(life), _maxatq(atq), _maxdef(def), _maxmovement(move), _maxlevel(level),
	_life(life), _atq(atq), _def(def), _movement(move), _level(level), _alive(true), _blit(0), _show(true)
{
	LoadConfig::logfileconsole("[INFO]___: Create Unit:  Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : ~Unit																		   */
/* ROLE : Destructeur																   */
/* INPUT : void																		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Unit::~Unit()
{
	/* N/A */
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : attack																	   */
/* ROLE : Attaque la cible avec les dommages appliqués de l'unité					   */
/* INPUT/OUTPUT : Units* : pointeur vers l'unité qui doit se défendre				   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::attack
(
	Unit* cible
)
{
	if (_movement > 0)
	{
		cible->defend(_atq);
	}
	else
	{
		/* N/A */
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : defend																	   */
/* ROLE : Défense de l'unité face à une attaque										   */
/* INPUT : unsigned int : dommage appliqué par l'attaque							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::defend
(
	unsigned int dmg
)
{
	int test(0);
	if (dmg > _def)
	{
		if ((test = (_life - (dmg - _def))) <= 0) 
		{
			_life = 0;
			_alive = false;
		}
		else
		{
			_life -= (dmg - _def);
		}
	}
	else
	{
		/* N/A */
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : move																		   */
/* ROLE : Application du mouvement à l'unité										   */
/* ROLE : Si l'unité n'a plus de mouvement disponible alors arret					   */
/* INPUT : Uint8& : enum Select_Type												   */
/* INPUT : int& : unité séléctionnée												   */
/* INPUT : int x : incrementation coor x											   */
/* INPUT : int y : incrementation coor y											   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::move
(
	Select_Type& select,
	int& selectunit,
	int x,
	int y
)
{
	if (_movement > 0)
	{
		_x += x;
		_y += y;
		_movement--;
	}
	else
	{
		/* N/A */
	}
	
	if (_movement == 0)
	{
		select = selectnothing;
		selectunit = -1;
		_blit = 0;
		_show = true;
	}
	else
	{
		/* N/A */
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : heal																		   */
/* ROLE : Soigne l'unité en fonction du territoire sur lequel elle se trouve		   */
/* INPUT : const std::vector<std::vector<Tile>>& tiles : tableau de cases			   */
/* INPUT : unsigned int : données générale de la map : joueur sélectionné			   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::heal
(
	const std::vector<std::vector<Tile>>& tiles,
	unsigned int selectplayer
)
{
	for (unsigned int i(0); i < tiles.size(); i++) 
	{
		for (unsigned int j(0); j < tiles[i].size(); j++)
		{
			if (_x == tiles[i][j].tile_x && _y == tiles[i][j].tile_y)
			{
				if (tiles[i][j].appartenance == -1) 
				{
					_life += (unsigned int)ceil(_maxlife / 20);
					if (_life > _maxlife)
					{
						_life = _maxlife;
					}
					else
					{
						/* N/A */
					}	
					return;
				}
				else if (tiles[i][j].appartenance == (int)selectplayer)
				{
					_life += (unsigned int)ceil(_maxlife / 5);
					if (_life > _maxlife)
					{
						_life = _maxlife;
					}
					else
					{
						/* N/A */
					}	
					return;
				}
				else
				{
					return;
				}	
			}
			else
			{
				/* N/A */
			}
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : levelup																	   */
/* ROLE : Incrémentation de 1 de level												   */
/* INPUT : void																		   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::levelup()
{
	_level++;

	/* Todo */
	//heal();
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : RESETmovement																   */
/* ROLE : Reset du nombre de mouvement disponible pour un tour						   */
/* INPUT : void																	       */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::RESETmovement()
{
	_movement = _maxmovement;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : testPos																	   */
/* ROLE : Test sur les positions de la souris et de l'unité							   */
/* INPUT : unsigned int mouse_x : position x										   */
/* INPUT : unsigned int mouse_y : position y										   */
/* RETURNED VALUE    : int : 0 : pas sélectioné / 1 : sélectionné					   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Unit::testPos
(
	unsigned int mouse_x,
	unsigned int mouse_y
) 
{
	if (_x == mouse_x && _y == mouse_y)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

/* *********************************************************
 *					END Units::METHODS					   *
 ********************************************************* */


/* *********************************************************
 *			START Units::METHODS::AFFICHAGE				   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : afficher																	   */
/* ROLE : Affichage de la Texture de l'unité ainsi que la barre de vie et couleur	   */
/* INPUT/OUPUT : AllTextures& : Structure contenant toutes les Textures				   */
/* INPUT : const struct Map& : données générale de la map							   */
/* INPUT : unsigned int iPlayer : joueur sélectionné								   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::afficher
(
	AllTextures& allTextures,
	const Map& map,
	unsigned int iPlayer
)
{
	if (_show)
	{
		unsigned int x(_x - map.screenOffsetXIndexMin * map.tileSize);
		unsigned int y(_y - map.screenOffsetYIndexMin * map.tileSize);
		allTextures.unit[_name]->render( x, y);
	
		if (_life == _maxlife)
		{
			allTextures.barLife["maxlife.bmp"]->render(x + (map.tileSize / 2) - 4, y + map.tileSize);
		}
		else if (_life < _maxlife && _life >= (_maxlife - ceil(_maxlife * 0.1)))
		{
			allTextures.barLife["0.9life.bmp"]->render(x + (map.tileSize / 2) - 4, y + map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.1)) && _life >= (_maxlife - ceil(_maxlife * 0.2))) 
		{
			allTextures.barLife["0.8life.bmp"]->render(x + (map.tileSize / 2) - 4, y + map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.2)) && _life >= (_maxlife - ceil(_maxlife * 0.3)))
		{
			allTextures.barLife["0.7life.bmp"]->render(x + (map.tileSize / 2) - 4, y + map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.3)) && _life >= (_maxlife - ceil(_maxlife * 0.4)))
		{
			allTextures.barLife["0.6life.bmp"]->render(x + (map.tileSize / 2) - 4, y + map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.4)) && _life >= (_maxlife - ceil(_maxlife * 0.5)))
		{
			allTextures.barLife["0.5life.bmp"]->render(x + (map.tileSize / 2) - 4, y + map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.5)) && _life >= (_maxlife - ceil(_maxlife * 0.6))) 
		{
			allTextures.barLife["0.4life.bmp"]->render(x + (map.tileSize / 2) - 4, y + map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.6)) && _life >= (_maxlife - ceil(_maxlife * 0.7))) 
		{
			allTextures.barLife["0.3life.bmp"]->render(x + (map.tileSize / 2) - 4, y + map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.7)) && _life >= (_maxlife - ceil(_maxlife * 0.8)))
		{
			allTextures.barLife["0.2life.bmp"]->render(x + (map.tileSize / 2) - 4, y + map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.8)) && _life >= (_maxlife - ceil(_maxlife * 0.9)))
		{
			allTextures.barLife["0.1life.bmp"]->render(x + (map.tileSize / 2) - 4, y + map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.9)))
		{
			allTextures.barLife["0.0life.bmp"]->render(x + (map.tileSize / 2) - 4, y + map.tileSize);
		}
		else
		{
			/* N/A */
		}

		allTextures.colorapp["ColorPlayer" + std::to_string(iPlayer) + ".bmp"]->render(x, y + map.tileSize);
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : afficherstat																   */
/* ROLE : Affichage des statistiques de l'unité (nom, x, y ...)						   */
/* INPUT : TTF_Font* font[] : tableau de ptr de font SDL							   */
/* INPUT/OUTPUT : SDL_Renderer*& : ptr sur le renderer SDL							   */
/* INPUT : unsigned int tileSize : données de la map : taille tile					   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::afficherstat
(
	TTF_Font* font[],
	SDL_Renderer*& renderer,
	unsigned int tileSize
)
{
	if (_show)
	{
		int initspace(_y), space(14);

		Texte::writeTexte
		(
			renderer, font, blended, "Name: "  + _name, Red, White,
			12, _x + tileSize, initspace, no_angle
		);

		Texte::writeTexte
		(
			renderer, font, blended, "X: " + std::to_string(_x), Red, White,
			12, _x + tileSize, initspace += space, no_angle
		);

		Texte::writeTexte
		(
			renderer, font, blended, "Y: " + std::to_string(_y), Red, White,
			12, _x + tileSize, initspace += space, no_angle
		);

		Texte::writeTexte
		(
			renderer, font, blended, "life: " + std::to_string(_life), Red, White,
			12, _x + tileSize, initspace += space, no_angle
		);

		Texte::writeTexte
		(
			renderer, font,blended, "atq: " + std::to_string(_atq), Red, White,
			12, _x + tileSize, initspace += space, no_angle
		);

		Texte::writeTexte
		(
			renderer, font, blended, "def: " + std::to_string(_def), Red, White,
			12, _x + tileSize, initspace += space, no_angle
		);

		Texte::writeTexte
		(
			renderer, font, blended, "movement: " + std::to_string(_movement), Red, White,
			12, _x + tileSize, initspace += space, no_angle
		);

		Texte::writeTexte
		(
			renderer, font, blended, "level: " + std::to_string(_level), Red, White,
			12, _x + tileSize, initspace += space, no_angle
		);
	}
	else
	{
		/* N/A */
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : cmpblit																	   */
/* ROLE : Compteur permettant de faire clignoter l'unité							   */
/* ROLE : Attention : basé sur SCREEN_REFRESH_RATE									   */
/* INPUT : void																		   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::cmpblit() 
{
	/* ---------------------------------------------------------------------- */
	/* 50% off 50% on , environ 1s le cycle									  */
	/* ---------------------------------------------------------------------- */
	if((++_blit %= (SCREEN_REFRESH_RATE / 2)) == 0)
	{
		_show = !_show;
	}
	else
	{
		/* N/A */
	}
}


/* *********************************************************
 *				END Units::METHODS::AFFICHAGE			   *
 ********************************************************* */


/*
*	End Of File Unit.cpp
*/