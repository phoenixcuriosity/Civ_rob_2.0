/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.22.0.0
	file version : 1.16

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

#include "ConstUnitIHM.h"

#include "IHM.h"
#include "LoadConfig.h"
#include "civ_lib.h"
#include "End.h"

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */

/* *********************************************************
 *					START Unit::STATIC					   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : searchUnitByName															   */
/* ROLE : Search the unit in vector template by name								   */
/* INPUT : std::string name : name to compared										   */
/* INPUT : std::vector<Unit_Template>& : vector of template unit 					   */
/* RETURNED VALUE : Uint8 : index of the unit										   */
/* ----------------------------------------------------------------------------------- */
Uint8 Unit::searchUnitByName
(
	std::string name,
	const std::vector<Unit_Template>& tabUnit_Template
)
{
	for (Uint8 p(0); p < tabUnit_Template.size(); p++)
	{
		if (tabUnit_Template[p].name.compare(name) == IDENTICAL_STRINGS)
		{
			return p;
		}
	}
	return 0;
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
	s_player.unitNameToCreate = s_player.tabUnit_Template[s_player.unitToCreate].name;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : searchUnitTile															   */
/* ROLE : Cherche l'unité étant dans la case séléctionné							   */
/* INPUT/OUTPUT : SubcatPlayer& s_player : structure concernant un joueur			   */
/* INPUT : const KeyboardMouse& mouse : données générale des entrées utilisateur	   */
/* INPUT/OUTPUT : std::vector<Player*>& tabplayer : Vecteur de joueurs				   */
/* OUTPUT : Select_Type* select : type de sélection									   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Unit::searchUnitTile
(
	SubcatPlayer& s_player,
	const KeyboardMouse& mouse,
	std::vector<Player*>& tabplayer,
	Select_Type* select
)
{
	if (NO_PLAYER_SELECTED < s_player.selectplayer)
	{
		for (unsigned int i(0); i < tabplayer[s_player.selectplayer]->GETtabUnit().size(); i++)
		{
			if	(
					tabplayer[s_player.selectplayer]->GETtheUnit(i)
						->testPos(mouse.GETmouse_xNormalized(), mouse.GETmouse_yNormalized())
				)
			{
				resetShowWhenChangePU(tabplayer, s_player.selectplayer, s_player.selectunit);

				s_player.selectunit = i;
				s_player.unitNameToMove = tabplayer[s_player.selectplayer]->GETtheUnit(i)->GETname();

				tabplayer[s_player.selectplayer]->GETtheUnit(i)->SETshow(true);
				LoadConfig::logfileconsole("Unit select to move n:" + std::to_string(i));
				*select = Select_Type::selectmove;
				return true;
			}
			else
			{
				/* N/A */
			}
		}
	}
	return false;
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
	case Move_Type::cannotMove:
		/*
		* N/A
		*/
		break;
	case Move_Type::canMove:

		tabplayer[s_player.selectplayer]
			->GETtheUnit(s_player.selectunit)
				->move(select, s_player.selectunit, x, y);
		break;
	case Move_Type::attackMove:

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
			->GETtheUnit(s_player.selectunit)->SETmovement(NO_MOVEMENT);
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

	/* --------------------------------------------------------------------------------------- */
	/* conditions de mouvement :														 	   */
	/*	- que la case cible soit du ground si l'Unit et de type ground						   */
	/*	- ou que la case cible soit de l'air ou water et si l'Unit et de type air		   	   */
	/*	- ou que la case cible soit de la water et si l'Unit et de type water				   */
	/*	- ou que la case cible soit de la deepwater ou water et si l'Unit et de type deepwater */
	/*		- que la case cible est libre													   */
	/*		- ou que la case cible est occupée par un ennemi								   */
	/*		  susceptible de mourrir par l'attaque											   */
	/* --------------------------------------------------------------------------------------- */

	bool nextTileValidToMove(false);
	unsigned int xIndex
	(
		GamePlay::convertPosXToIndex
		(tabplayer[s_player.selectplayer]->GETtheUnit(s_player.selectunit)->GETx() + x)
	);
	unsigned int yIndex
	(
		GamePlay::convertPosYToIndex
		(tabplayer[s_player.selectplayer]->GETtheUnit(s_player.selectunit)->GETy() + y)
	);

	Unit* unit(tabplayer[s_player.selectplayer]->GETtheUnit(s_player.selectunit));

	if	(
				unit->isGroundMovement_Type()
				&&
				maps[xIndex][yIndex].tile_ground == Ground_Type::grass
			)
		{
			nextTileValidToMove = true;
		}
	else 
	if (
			unit->isAirMovement_Type()
			&&
			(
				maps[xIndex][yIndex].tile_ground == Ground_Type::grass
				||
				maps[xIndex][yIndex].tile_ground == Ground_Type::water
			)
		)
	{
		nextTileValidToMove = true;
	}
	else
	if  (
			unit->isWaterMovement_Type()
			&&
			maps[xIndex][yIndex].tile_ground == Ground_Type::water
		)
	{
		nextTileValidToMove = true;
	}
	else
	if (
			unit->isDeepWaterMovement_Type()
			&&
			(
				maps[xIndex][yIndex].tile_ground == Ground_Type::deepwater
				||
				maps[xIndex][yIndex].tile_ground == Ground_Type::water
			)
		)
	{
		nextTileValidToMove = true;
	}
	else
	{
		/* ---------------------------------------------------------------------- */
		/* nextTileValidToMove = false : Unit cannot move						  */
		/* ---------------------------------------------------------------------- */

		/* N/A */
	}
			


	bool condition(false);
	if (nextTileValidToMove)
	{
		/* ---------------------------------------------------------------------- */
		/* Next Tile is a ground Tile 											  */
		/* ---------------------------------------------------------------------- */

		for (unsigned int i = 0; i < tabplayer.size(); i++) 
		{
			for (unsigned int j = 0; j < tabplayer[i]->GETtabUnit().size(); j++) 
			{
				condition = checkUnitNextTile(unit,tabplayer[i]->GETtheUnit(j),x, y);
				if	(true == condition)
				{
					if (s_player.selectplayer == (int)i)
					{
						return Move_Type::cannotMove;
					}		
					else
					{
						s_player.selectPlayerToAttack = (int)i;
						s_player.selectUnitToAttack = (int)j;
						return Move_Type::attackMove;
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
		/* ---------------------------------------------------------------------- */
		/* Next Tile is not a ground Tile 										  */
		/* ---------------------------------------------------------------------- */

		return Move_Type::cannotMove;
	}	
	return Move_Type::canMove;
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
/* INPUT : const Unit* from : Unit aux positions + x + y							   */
/* INPUT : const Tile& to : Tile à tester											   */
/* INPUT : int x : delta horizontal tileSize en fonction du cardinal				   */
/* INPUT : int y : delta vertical tileSize en fonction du cardinal					   */
/* RETURNED VALUE : bool : false->position différente / true->même positions		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Unit::checkNextTile
(
	const Unit* from,
	const Tile& to,
	int x,
	int y
)
{
	if ((from->GETx() + (unsigned __int64)x) == (to.tile_x))
	{
		if ((from->GETy() + (unsigned __int64)y) == (to.tile_y))
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

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : resetShowWhenChangePU														   */
/* ROLE : Reset show to true (alaways visible) 										   */
/* ROLE : when a new Unit or a new Player is selected								   */
/* INPUT : TabPlayer& tabPlayer : Array of Player ptr								   */
/* INPUT : unsigned int playerIndex : Index to the current selected Player			   */
/* INPUT : unsigned int unitIndex : Index to the current selected Unit				   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::resetShowWhenChangePU
(
	TabPlayer& tabPlayer,
	unsigned int playerIndex,
	unsigned int unitIndex
)
{
	if  (
			playerIndex != NO_PLAYER_SELECTED
			&&
			unitIndex != NO_UNIT_SELECTED
		)
	{
		tabPlayer[playerIndex]->GETtheUnit(unitIndex)->SETshow(true);
	}
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
Unit::Unit() :	_name(EMPTY_STRING), _x(0), _y(0), _movementType(Unit_Movement_Type::ground),
				_maxlife(100), _maxatq(10), _maxdef(5), _maxmovement(1), _maxlevel(100),
				_life(100), _atq(10), _def(5), _movement(1), _level(1), _alive(true), _blit(ZERO_BLIT), _show(true), _showStats(false)
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
	Unit_Movement_Type movementType,
	unsigned int life,
	unsigned int atq,
	unsigned int def,
	unsigned int move,
	unsigned int level
)
	: _name(name), _x(x), _y(y), _movementType(movementType),
	_maxlife(life), _maxatq(atq), _maxdef(def), _maxmovement(move), _maxlevel(level),
	_life(life), _atq(atq), _def(def), _movement(move), _level(level), _alive(true), _blit(ZERO_BLIT), _show(true), _showStats(false)
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
	if (_movement > NO_MOVEMENT)
	{
		cible->defend(_atq);
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
	int dmg
)
{
	if (dmg > _def)
	{
		if ((_life - (dmg - _def)) <= ENOUGH_DAMAGE_TO_KILL)
		{
			_life = ZERO_LIFE;
			_alive = false;
		}
		else
		{
			_life -= (dmg - _def);
		}
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
	if (NO_MOVEMENT < _movement)
	{
		_x += x;
		_y += y;
		_movement--;
	}
	
	if (NO_MOVEMENT == _movement)
	{
		select = Select_Type::selectnothing;
		selectunit = NO_UNIT_SELECTED;
		_blit = ZERO_BLIT;
		_show = true;
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
	int i(GamePlay::convertPosXToIndex(_x));
	int j(GamePlay::convertPosYToIndex(_y));

	if (NO_APPARTENANCE == tiles[i][j].appartenance)
	{
		_life += (unsigned int)ceil(_maxlife / COEF_DIV_HEAL_NO_APPARTENANCE);
		if (_life > _maxlife)
		{
			_life = _maxlife;
		}
		return;
	}
	else if (tiles[i][j].appartenance == (int)selectplayer)
	{
		_life += (unsigned int)ceil(_maxlife / COEF_DIV_HEAL_APPARTENANCE);
		if (_life > _maxlife)
		{
			_life = _maxlife;
		}
		return;
	}
	else
	{
		return;
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

	_maxlife += (int)ceil(_maxlife / COEF_DIV_LEVELUP);
	_life = _maxlife;

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
	if  (
			(unsigned __int64)_x == mouse_x
			&&
			(unsigned __int64)_y == mouse_y
		)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : isGroundMovement_Type														   */
/* ROLE : Check if the movement type of the Unit is	ground							   */
/* INPUT : void																		   */
/* RETURNED VALUE : bool : false -> movement type is not ground						   */
/* RETURNED VALUE : bool : true -> movement type is ground							   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Unit::isGroundMovement_Type()
{ 
	return _movementType == Unit_Movement_Type::ground ? true : false;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : isAirMovement_Type														   */
/* ROLE : Check if the movement type of the Unit is	air								   */
/* INPUT : void																		   */
/* RETURNED VALUE : bool : false -> movement type is not air						   */
/* RETURNED VALUE : bool : true -> movement type is air								   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Unit::isAirMovement_Type()
{ 
	return _movementType == Unit_Movement_Type::air ? true : false;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : isWaterMovement_Type														   */
/* ROLE : Check if the movement type of the Unit is	water							   */
/* INPUT : void																		   */
/* RETURNED VALUE : bool : false -> movement type is not water						   */
/* RETURNED VALUE : bool : true -> movement type is water							   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Unit::isWaterMovement_Type()
{ 
	return _movementType == Unit_Movement_Type::water ? true : false;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : isDeepWaterMovement_Type													   */
/* ROLE : Check if the movement type of the Unit is	DeepWater						   */
/* INPUT : void																		   */
/* RETURNED VALUE : bool : false -> movement type is not DeepWater					   */
/* RETURNED VALUE : bool : true -> movement type is DeepWater						   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Unit::isDeepWaterMovement_Type()
{ 
	return _movementType == Unit_Movement_Type::deepwater ? true : false;
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

		if  (
				((unsigned __int64)_x > (x - map.tileSize * map.toolBarSize))
				&&
				((unsigned __int64)_y >= y)
			)
		{
			allTextures.unit[_name]->render(x, y);

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
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : afficherstat																   */
/* ROLE : Affichage des statistiques de l'unité (nom, x, y ...)						   */
/* INPUT : const Map& map : données de la map										   */
/* INPUT : TTF_Font* font[] : tableau de ptr de font SDL							   */
/* INPUT/OUTPUT : SDL_Renderer*& : ptr sur le renderer SDL							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::afficherstat
(
	const Map& map,
	TTF_Font* font[],
	SDL_Renderer*& renderer
)
{
	if (_showStats)
	{
		unsigned int x(_x - map.screenOffsetXIndexMin * map.tileSize);
		unsigned int y(_y - map.screenOffsetYIndexMin * map.tileSize);
		
		Texte::writeTexte
		(
			renderer, font, Index_staticIndexVectorTextes::UNIT_NAME, Texte_Type::blended,
			"Name: "  + _name, Red, White,
			UNIT_STATS_FONT_SIZE, x + map.tileSize, y, nonTransparent, no_angle
		);

		Texte::writeTexte
		(
			renderer, font, Index_staticIndexVectorTextes::UNIT_X, Texte_Type::blended,
			"X: " + std::to_string(_x), Red, White,
			UNIT_STATS_FONT_SIZE, x + map.tileSize, y += UNIT_STATS_SPACE_Y, nonTransparent, no_angle
		);

		Texte::writeTexte
		(
			renderer, font, Index_staticIndexVectorTextes::UNIT_Y, Texte_Type::blended,
			"Y: " + std::to_string(_y), Red, White,
			UNIT_STATS_FONT_SIZE, x + map.tileSize, y += UNIT_STATS_SPACE_Y, nonTransparent, no_angle
		);

		Texte::writeTexte
		(
			renderer, font, Index_staticIndexVectorTextes::UNIT_LIFE, Texte_Type::blended,
			"life: " + std::to_string(_life), Red, White,
			UNIT_STATS_FONT_SIZE, x + map.tileSize, y += UNIT_STATS_SPACE_Y, nonTransparent, no_angle
		);

		Texte::writeTexte
		(
			renderer, font, Index_staticIndexVectorTextes::UNIT_ATQ, Texte_Type::blended,
			"atq: " + std::to_string(_atq), Red, White,
			UNIT_STATS_FONT_SIZE, x + map.tileSize, y += UNIT_STATS_SPACE_Y, nonTransparent, no_angle
		);

		Texte::writeTexte
		(
			renderer, font, Index_staticIndexVectorTextes::UNIT_DEF, Texte_Type::blended,
			"def: " + std::to_string(_def), Red, White,
			UNIT_STATS_FONT_SIZE, x + map.tileSize, y += UNIT_STATS_SPACE_Y, nonTransparent, no_angle
		);

		Texte::writeTexte
		(
			renderer, font, Index_staticIndexVectorTextes::UNIT_MOVEMENT, Texte_Type::blended,
			"movement: " + std::to_string(_movement), Red, White,
			UNIT_STATS_FONT_SIZE, x + map.tileSize, y += UNIT_STATS_SPACE_Y, nonTransparent, no_angle
		);

		Texte::writeTexte
		(
			renderer, font, Index_staticIndexVectorTextes::UNIT_LEVEL, Texte_Type::blended,
			"level: " + std::to_string(_level), Red, White,
			UNIT_STATS_FONT_SIZE, x + map.tileSize, y += UNIT_STATS_SPACE_Y, nonTransparent, no_angle
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
	if((++_blit %= (SCREEN_REFRESH_RATE / BLIT_RATE)) == MODULO_ZERO)
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