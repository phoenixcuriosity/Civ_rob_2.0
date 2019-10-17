/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.17
	file version : 1.8

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

#include "Unit.h"
#include "IHM.h"


/* *********************************************************
 *				START Unit::STATIC						   *
 ********************************************************* */


/*
* NAME : loadUnitAndSpec
* ROLE : Chargement des informations concernant les unités à partir d'un fichier
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : tableau de nom et spec concernant les unités
* RETURNED VALUE    : void
*/
void Unit::loadUnitAndSpec(Sysinfo& sysinfo)
{
	tinyxml2::XMLDocument texteFile;
	texteFile.LoadFile(sysinfo.file.UNIT.c_str());

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
		
		sysinfo.var.s_player.tabUnit_Struct.push_back(currentUnit);

		/* Recherche du noeud Model suivant */
		node = node->NextSibling();
	}
}


/*
* NAME : searchunit
* ROLE : Sélection du nom de l'unité à partir de l'index du tableau
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : nom de l'unité
* RETURNED VALUE    : void
*/
void Unit::searchUnit(Sysinfo& sysinfo)
{
	sysinfo.var.s_player.unitNameToCreate = sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate].name;
}


/*
* NAME : searchUnitTile
* ROLE : Cherche l'unité étant dans la case séléctionné
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : index et nom de l'unité sélectionnée
* OUTPUT PARAMETERS : activation de la méthode blit (clignotement)
* RETURNED VALUE    : void
*/
void Unit::searchUnitTile(Sysinfo& sysinfo)
{
	for (unsigned int i(0); i < sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabUnit().size(); i++)
	{
		if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(i)->testPos(
				sysinfo.var.mouse.GETmouse_x() + sysinfo.map.screenOffsetXIndexMin * sysinfo.map.tileSize,
				sysinfo.var.mouse.GETmouse_y() + sysinfo.map.screenOffsetYIndexMin * sysinfo.map.tileSize)
			)
		{
			sysinfo.var.s_player.selectunit = i;
			sysinfo.var.s_player.unitNameToMove = sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(i)->GETname();
			sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(i)->SETblit(true);
			break;
		}
		else
		{
			/* N/A */
		}
	}
}


/*
* NAME : tryToMove
* ROLE : Recherche à faire bouger l'unité selon le contexte
* ROLE : Attention : contient un rappel récursif
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : l'unité reste à sa place ou bouge en fonction du contexte
* RETURNED VALUE    : void
*/
void Unit::tryToMove(Sysinfo& sysinfo, int x, int y)
{
	switch (searchToMove(sysinfo, x, y))
	{
	case cannotMove:
		/*
		* N/A
		*/
		break;
	case canMove:
		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(sysinfo.var.s_player.selectunit)->move(sysinfo.var.select, sysinfo.var.s_player.selectunit, x, y);
		break;
	case attackMove:
		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(sysinfo.var.s_player.selectunit)->attack(sysinfo.tabplayer[sysinfo.var.s_player.selectPlayerToAttack]->GETtheUnit(sysinfo.var.s_player.selectUnitToAttack));
		if (sysinfo.tabplayer[sysinfo.var.s_player.selectPlayerToAttack]->GETtheUnit(sysinfo.var.s_player.selectUnitToAttack)->GETalive() == false)
		{
			sysinfo.tabplayer[sysinfo.var.s_player.selectPlayerToAttack]->deleteUnit(sysinfo.var.s_player.selectUnitToAttack);
			tryToMove(sysinfo, x, y);
		}
		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(sysinfo.var.s_player.selectunit)->SETmovement(0);
		break;
	default:
		/* N/A */
		break;
	}
}


/*
* NAME : searchToMove
* ROLE : Recherche à faire bouger l'unité selon le contexte
* ROLE : Action conditionnelle (case libre, ennemi, amis)
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : l'unité reste à sa place ou bouge en fonction du contexte
* RETURNED VALUE    : Move_Type : 0 : ne bouge pas / 1 : case libre : peut bouger / 2 : ennemi : ne bouge pas
*
*/
Move_Type Unit::searchToMove(Sysinfo& sysinfo, int x, int y)
{
	/*
		conditions de mouvement :
			- que la case cible soit du sol et
					- que la case cible est libre
					- ou que la case cible est occupée par un ennemi susceptible de mourrir par l'attaque

	*/
	bool ground = false;

	for (unsigned int i(0); i < sysinfo.map.maps.size(); i++)
	{
		for (unsigned int j(0); j < sysinfo.map.maps[i].size(); j++)
		{
			if (sysinfo.map.maps[i][j].tile_x == sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(sysinfo.var.s_player.selectunit)->GETx() + x &&
				sysinfo.map.maps[i][j].tile_y == sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(sysinfo.var.s_player.selectunit)->GETy() + y)
			{
				if (sysinfo.map.maps[i][j].tile_ground == grass)
				{
					ground = true;
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

	if (ground)
	{
		/* On ground */

		for (unsigned int i = 0; i < sysinfo.tabplayer.size(); i++) 
		{
			for (unsigned int j = 0; j < sysinfo.tabplayer[i]->GETtabUnit().size(); j++) 
			{
				if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(sysinfo.var.s_player.selectunit)->GETx() + x == sysinfo.tabplayer[i]->GETtheUnit(j)->GETx())
				{
					if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(sysinfo.var.s_player.selectunit)->GETy() + y == sysinfo.tabplayer[i]->GETtheUnit(j)->GETy())
					{
						if (sysinfo.var.s_player.selectplayer == (int)i)
						{
							return cannotMove;
						}		
						else
						{
							sysinfo.var.s_player.selectPlayerToAttack = (int)i;
							sysinfo.var.s_player.selectUnitToAttack = (int)j;
							return attackMove;
						}
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
	}
	else
	{
		/* Not on ground */

		return cannotMove;
	}	
	return canMove;
}


/*
* NAME : irrigate
* ROLE :
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS :
* RETURNED VALUE    : bool
*/
bool Unit::irrigate(Sysinfo&)
{
	return false;
}

/* *********************************************************
 *					END Units::STATIC					   *
 ********************************************************* */


/* *********************************************************
 *				START Units::METHODS					   *
 ********************************************************* */

Unit::Unit() :	_name(""), _x(0), _y(0),
				_maxlife(0), _maxatq(0), _maxdef(0), _maxmovement(0), _maxlevel(0),
				_life(100), _atq(10), _def(5), _movement(1), _level(1), _alive(true)
{
	IHM::logfileconsole("Create Unit Par Defaut Success");
}
Unit::Unit(const std::string &name, unsigned int x, unsigned int y, unsigned int life, unsigned int atq,
	unsigned int def, unsigned int move, unsigned int level)
	: _name(name), _x(x), _y(y),
	_maxlife(life), _maxatq(atq), _maxdef(def), _maxmovement(move), _maxlevel(level),
	_life(life), _atq(atq), _def(def), _movement(move), _level(level), _alive(true), _blit(0), _show(true)
{
	IHM::logfileconsole("Create Unit:  Success");
}
Unit::~Unit()
{
	/* N/A */
}


/*
* NAME : attack
* ROLE : Attaque la cible avec les dommages appliqués de l'unité
* INPUT  PARAMETERS : Units* : pointeur vers l'unité qui doit se défendre
* OUTPUT PARAMETERS : Attaque d'une unité
* RETURNED VALUE    : void
*/
void Unit::attack(Unit* cible)
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


/*
* NAME : defend
* ROLE : Défense de l'unité face à une attaque
* INPUT  PARAMETERS : unsigned int : dommage appliqué par l'attaque
* OUTPUT PARAMETERS : l'unité peut prendre des dommage et/ou mourrir
* RETURNED VALUE    : void
*/
void Unit::defend(unsigned int dmg)
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


/*
* NAME : move
* ROLE : Application du mouvement à l'unité
* ROLE : Si l'unité n'a plus de mouvement disponible alors arret
* INPUT  PARAMETERS : Uint8& : enum Select_Type
* INPUT  PARAMETERS : int& : unité séléctionnée
* INPUT  PARAMETERS : int x : incrementation coor x
* INPUT  PARAMETERS : int y : incrementation coor y
* OUTPUT PARAMETERS : Application du mouvement à l'unité
* RETURNED VALUE    : void
*/
void Unit::move(Uint8& select, int& selectunit, int x, int y)
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


/*
* NAME : heal
* ROLE : Soigne l'unité en fonction du territoire sur lequel elle se trouve
* INPUT  PARAMETERS : std::vector<std::vector<Tile>>& tiles : tableau de cases
* INPUT  PARAMETERS : unsigned int : données générale de la map : joueur sélectionné
* OUTPUT PARAMETERS : Soigne l'unité en fonction du contexte
* RETURNED VALUE    : void
*/
void Unit::heal(std::vector<std::vector<Tile>>& tiles, unsigned int selectplayer)
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


/*
* NAME : levelup
* ROLE : levelup
* INPUT  PARAMETERS : void
* OUTPUT PARAMETERS : levelup
* RETURNED VALUE    : void
*/
void Unit::levelup()
{
	_level++;

	/* Todo */
	//heal();
}


/*
* NAME : RESETmovement
* ROLE : RESETmovement
* INPUT  PARAMETERS : void
* OUTPUT PARAMETERS : RESETmovement
* RETURNED VALUE    : void
*/
void Unit::RESETmovement()
{
	_movement = _maxmovement;
}


/*
* NAME : testPos
* ROLE : Test sur les positions de la souris et de l'unité
* INPUT  PARAMETERS : unsigned int mouse_x : position x
* OUTPUT PARAMETERS : unsigned int mouse_y : position y
* RETURNED VALUE    : int : 0 : pas sélectioné / 1 : sélectionné
*/
bool Unit::testPos(unsigned int mouse_x, unsigned int mouse_y) 
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


/*
* NAME : afficher
* ROLE : Affichage de la Texture de l'unité ainsi que la barre de vie et couleur
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* INPUT  PARAMETERS : unsigned int iPlayer : joueur sélectionné
* OUTPUT PARAMETERS : Affichage de l'unité
* RETURNED VALUE    : void
*/
void Unit::afficher(Sysinfo& sysinfo, unsigned int iPlayer){
	if (_show)
	{
		unsigned int x = _x - sysinfo.map.screenOffsetXIndexMin * sysinfo.map.tileSize;
		unsigned int y = _y - sysinfo.map.screenOffsetYIndexMin * sysinfo.map.tileSize;
		sysinfo.allTextures.unit[_name]->render( x, y);
	
		if (_life == _maxlife)
		{
			sysinfo.allTextures.barLife["maxlife.bmp"]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < _maxlife && _life >= (_maxlife - ceil(_maxlife * 0.1)))
		{
			sysinfo.allTextures.barLife["0.9life.bmp"]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.1)) && _life >= (_maxlife - ceil(_maxlife * 0.2))) 
		{
			sysinfo.allTextures.barLife["0.8life.bmp"]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.2)) && _life >= (_maxlife - ceil(_maxlife * 0.3)))
		{
			sysinfo.allTextures.barLife["0.7life.bmp"]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.3)) && _life >= (_maxlife - ceil(_maxlife * 0.4)))
		{
			sysinfo.allTextures.barLife["0.6life.bmp"]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.4)) && _life >= (_maxlife - ceil(_maxlife * 0.5)))
		{
			sysinfo.allTextures.barLife["0.5life.bmp"]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.5)) && _life >= (_maxlife - ceil(_maxlife * 0.6))) 
		{
			sysinfo.allTextures.barLife["0.4life.bmp"]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.6)) && _life >= (_maxlife - ceil(_maxlife * 0.7))) 
		{
			sysinfo.allTextures.barLife["0.3life.bmp"]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.7)) && _life >= (_maxlife - ceil(_maxlife * 0.8)))
		{
			sysinfo.allTextures.barLife["0.2life.bmp"]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.8)) && _life >= (_maxlife - ceil(_maxlife * 0.9)))
		{
			sysinfo.allTextures.barLife["0.1life.bmp"]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.9)))
		{
			sysinfo.allTextures.barLife["0.0life.bmp"]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else
		{
			/* N/A */
		}

		sysinfo.allTextures.colorapp["ColorPlayer" + std::to_string(iPlayer) + ".bmp"]->render(x, y + sysinfo.map.tileSize);
	}
}


/*
* NAME : afficherstat
* ROLE : Affichage des statistiques de l'unité (nom, x, y ...)
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : Affichage des statistiques de l'unité
* RETURNED VALUE    : void
*/
void Unit::afficherstat(Sysinfo& sysinfo)
{
	if (_show)
	{
		int initspace(_y), space(14);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "Name: "  + _name, Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace, no_angle);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "X: " + std::to_string(_x), Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space, no_angle);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "Y: " + std::to_string(_y), Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space, no_angle);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "life: " + std::to_string(_life), Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space, no_angle);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "atq: " + std::to_string(_atq), Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space, no_angle);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "def: " + std::to_string(_def), Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space, no_angle);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "movement: " + std::to_string(_movement), Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space, no_angle);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "level: " + std::to_string(_level), Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space, no_angle);
	}
	else
	{
		/* N/A */
	}
}


/*
* NAME : cmpblit
* ROLE : Compteur permettant de faire clignoter l'unité
* ROLE : Attention : basé sur SCREEN_REFRESH_RATE
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : Compteur permettant de faire clignoter l'unité
* RETURNED VALUE    : void
*/
void Unit::cmpblit() 
{
	/*
		50% off 50% on , environ 1s le cycle
	*/
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