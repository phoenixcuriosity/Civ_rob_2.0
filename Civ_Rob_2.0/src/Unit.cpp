/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.6.0
	file version : 1.24

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
#include "Player.h"
#include "App.h"


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
/* RETURNED VALUE : unsigned int : index of the unit										   */
/* ----------------------------------------------------------------------------------- */
unsigned int Unit::searchUnitByName
(
	const std::string& name,
	const VectUnitTemplate& tabUnit_Template
)
{
	for (unsigned int p(0); p < tabUnit_Template.size(); p++)
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
/* NAME : searchUnitTile															   */
/* ROLE : Cherche l'unit� �tant dans la case s�l�ctionn�							   */
/* INPUT/OUTPUT : SubcatPlayer& s_player : structure concernant un joueur			   */
/* INPUT : const KeyboardMouse& mouse : donn�es g�n�rale des entr�es utilisateur	   */
/* INPUT/OUTPUT : std::vector<Player*>& tabplayer : Vecteur de joueurs				   */
/* OUTPUT : Select_Type* select : type de s�lection									   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Unit::searchUnitTile
(
	Players& players,
	const glm::i32vec2& mouseCoorNorm,
	Select_Type* select
)
{
	if (NO_PLAYER_SELECTED < players.GETselectedPlayerId())
	{
		std::shared_ptr<Player> selPlayer(players.GETselectedPlayerPtr());

		for (unsigned int i(0); i < selPlayer->GETtabUnit().size(); i++)
		{
			if (selPlayer->GETtabUnit()[i]->testPos(mouseCoorNorm.x, mouseCoorNorm.y))
			{
				selPlayer->SETselectedUnit(i);

				selPlayer->GETtabUnit()[i]->SETshow(true);
				App::logfileconsole("[INFO]___: Unit select to move n:" + std::to_string(i));
				*select = Select_Type::selectmove;
				return true;
			}
		}
		selPlayer.reset();
	}
	return false;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : tryToMove																	   */
/* ROLE : Recherche � faire bouger l'unit� selon le contexte						   */
/* ROLE : Attention : contient un rappel r�cursif									   */
/* INPUT : const std::vector<std::vector<Tile>>& : Matrice de la MAP				   */
/* INPUT/OUTPUT : Struct SubcatPlayer& : structure concernant un joueur				   */
/* INPUT/OUTPUT : std::vector<Player*>& : Vecteur de joueurs						   */
/* INPUT : Select_Type : �tat de la s�lection du joueur (enum Select_Type : unsigned int)	   */
/* INPUT : int x : pos X															   */
/* INPUT : int y : pos Y															   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::tryToMove
(
	const MatriceMap& maps,
	Players& players,
	Select_Type select,
	const int x,
	const int y
)
{
	if (players.GETselectedPlayerId() != NO_PLAYER_SELECTED)
	{
		std::shared_ptr<Player> selPlayer(players.GETselectedPlayerPtr());
		int playerToAttack(NO_PLAYER_SELECTED), unitToAttack(NO_UNIT_SELECTED), selectunit(selPlayer->GETselectedUnit());

		switch (searchToMove(maps, players, x, y, &playerToAttack, &unitToAttack))
		{
		case Move_Type::canMove:

			selPlayer->GETtabUnit()[selectunit]->move(select, selectunit, x, y);
			selPlayer->SETselectedUnit(selectunit);
			players.SETneedToUpdateDrawUnit(NEED_TO_UPDATE_DRAW_UNIT);
			break;
		case Move_Type::attackMove:
		{
			/* safe index playerToAttack / unitToAttack : filled by searchToMove */
			std::shared_ptr<Player> attackPlayer(players.GETvectPlayer()[playerToAttack]);
			std::shared_ptr<Unit> attackUnit{ selPlayer->GETtabUnit()[selectunit] };
			std::shared_ptr<Unit> defenderUnit{ attackPlayer->GETtabUnit()[unitToAttack] };

			if	(attackUnit->isPossibleToAttack())
			{
				attackUnit->attack(*(defenderUnit.get()));

				/* if the opposite Unit is destroy, try to move to its position */
				if (defenderUnit->GETalive() == DEAD_UNIT)
				{
					attackPlayer->deleteUnit(unitToAttack);
					tryToMove(maps, players, select, x, y);
				}
			}
			
			/* Cannot move further for this turn */
			attackUnit->SETmovement(NO_MOVEMENT);
			break;
		}
		case Move_Type::cannotMove:
		default:
			/*
			* Do nothing
			*/
			break;
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : searchToMove																   */
/* ROLE : Recherche � faire bouger l'unit� selon le contexte						   */
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
	const MatriceMap& maps,
	Players& players,
	const int x,
	const int y,
	int* const playerToAttack,
	int* const unitToAttack
)
{

	/* --------------------------------------------------------------------------------------- */
	/* conditions de mouvement :														 	   */
	/*	- que la case cible soit du ground si l'Unit et de type ground						   */
	/*	- ou que la case cible soit de l'air ou water et si l'Unit et de type air		   	   */
	/*	- ou que la case cible soit de la water et si l'Unit et de type water				   */
	/*	- ou que la case cible soit de la deepwater ou water et si l'Unit et de type deepwater */
	/*		- que la case cible est libre													   */
	/*		- ou que la case cible est occup�e par un ennemi								   */
	/*		  susceptible de mourrir par l'attaque											   */
	/* --------------------------------------------------------------------------------------- */

	std::shared_ptr<Player> selPlayer(players.GETselectedPlayerPtr());
	std::shared_ptr<Unit> unit(selPlayer->GETtabUnit()[selPlayer->GETselectedUnit()]);

	bool nextTileValidToMove(false);
	const unsigned int xIndex(MainMap::convertPosXToIndex(unit->GETx() + x));
	const unsigned int yIndex(MainMap::convertPosYToIndex(unit->GETy() + y));

	if	(
			unit->isGroundMovement_Type()
			&&
			maps[xIndex][yIndex].tile_ground == Ground_Type::grass
		)
	{
		nextTileValidToMove = true;
	}
	else
	if	(
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
	if	(
			unit->isWaterMovement_Type()
			&&
			maps[xIndex][yIndex].tile_ground == Ground_Type::water
		)
	{
		nextTileValidToMove = true;
	}
	else
	if	(
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

		for (unsigned int i{0}; i < players.GETvectPlayer().size(); i++)
		{
			for (unsigned int j{0}; j < players.GETvectPlayer()[i]->GETtabUnit().size(); j++)
			{
				condition = checkUnitNextTile(*unit, *(players.GETvectPlayer()[i]->GETtabUnit()[j]), x, y);
				if (true == condition)
				{
					if (players.GETselectedPlayerId() == (int)i)
					{
						return Move_Type::cannotMove;
					}
					else
					{
						*playerToAttack = (int)i;
						*unitToAttack = (int)j;
						return Move_Type::attackMove;
					}
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
/* ROLE : Check des �qualit�s des positions des Units avec + x et +y				   */
/* INPUT : const Unit* from : Unit avec un mouvement possible + x + y				   */
/* INPUT : const Unit* from : Unit aux positions + x + y							   */
/* INPUT : int x : delta horizontal tileSize en fonction du cardinal				   */
/* INPUT : int y : delta vertical tileSize en fonction du cardinal					   */
/* RETURNED VALUE : bool : false->position diff�rente / true->m�me positions		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Unit::checkUnitNextTile
(
	const Unit& from,
	const Unit& to,
	const int x,
	const int y
)
{
	if ((from.GETx() + x) == to.GETx())
	{
		if ((from.GETy() + y) == to.GETy())
		{
			return true;
		}
	}
	return false;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : checkNextTile																   */
/* ROLE : Check des �qualit�s des positions des Units avec + x et +y				   */
/* INPUT : const Unit* from : Unit aux positions + x + y							   */
/* INPUT : const Tile& to : Tile � tester											   */
/* INPUT : int x : delta horizontal tileSize en fonction du cardinal				   */
/* INPUT : int y : delta vertical tileSize en fonction du cardinal					   */
/* RETURNED VALUE : bool : false->position diff�rente / true->m�me positions		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Unit::checkNextTile
(
	const Unit& from,
	const Tile& to,
	const int x,
	const int y
)
{
	if ((from.GETx() + x) == (to.tile_x))
	{
		if ((from.GETy() + y) == (to.tile_y))
		{
			return true;
		}
	}
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
  /* ROLE : Constructeur par d�faut													   */
  /* INPUT : void																		   */
  /* ----------------------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------------------- */
Unit::Unit()
: 
m_name(EMPTY_STRING), 
m_x(0),
m_y(0),
m_movementType(Unit_Movement_Type::ground),
m_maxlife(100),
m_maxatq(10),
m_maxdef(5),
m_maxmovement(1),
m_maxNumberOfAttack(1),
m_maxlevel(100),
m_life(100), 
m_atq(10),
m_def(5),
m_movement(1),
m_numberOfAttack(1),
m_level(1),
m_alive(true),
m_maintenance(1.0),
m_blit(ZERO_BLIT),
m_show(true),
m_showStats(false),
m_owner(NO_OWNER)
{
	App::logfileconsole("[INFO]___: Create Unit Par Defaut Success");
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
	const std::string& name,
	unsigned int x,
	unsigned int y,
	Unit_Movement_Type movementType,
	unsigned int life,
	unsigned int atq,
	unsigned int def,
	unsigned int move,
	unsigned int numberOfAttack,
	unsigned int level,
	double maintenance,
	Player* ptrToPlayer
)
:
m_name(name),
m_x(x),
m_y(y),
m_movementType(movementType),
m_maxlife(life),
m_maxatq(atq),
m_maxdef(def),
m_maxmovement(move),
m_maxNumberOfAttack(numberOfAttack),
m_maxlevel(level),
m_life(life),
m_atq(atq),
m_def(def), 
m_movement(move),
m_numberOfAttack(numberOfAttack),
m_level(level),
m_alive(true),
m_maintenance(maintenance),
m_blit(ZERO_BLIT),
m_show(true),
m_showStats(false),
m_owner(ptrToPlayer)
{
	App::logfileconsole("[INFO]___: Create Unit:  Success");
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
	m_owner = nullptr;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : attack																	   */
/* ROLE : Attaque la cible avec les dommages appliqu�s de l'unit�					   */
/* INPUT/OUTPUT : Units* : pointeur vers l'unit� qui doit se d�fendre				   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::attack
(
	Unit& cible
)
{
	m_numberOfAttack--;

	if (m_movement > NO_MOVEMENT)
	{
		cible.defend(m_atq);
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : defend																	   */
/* ROLE : D�fense de l'unit� face � une attaque										   */
/* INPUT : unsigned int : dommage appliqu� par l'attaque							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::defend
(
	const int dmg
)
{
	if (dmg > m_def)
	{
		if ((m_life - (dmg - m_def)) <= ENOUGH_DAMAGE_TO_KILL)
		{
			m_life = ZERO_LIFE;
			m_alive = false;
		}
		else
		{
			m_life -= (dmg - m_def);
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : move																		   */
/* ROLE : Application du mouvement � l'unit�										   */
/* ROLE : Si l'unit� n'a plus de mouvement disponible alors arret					   */
/* INPUT : unsigned int& : enum Select_Type												   */
/* INPUT : int& : unit� s�l�ctionn�e												   */
/* INPUT : int x : incrementation coor x											   */
/* INPUT : int y : incrementation coor y											   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::move
(
	Select_Type& select,
	int& selectunit,
	const int x,
	const int y
)
{
	if (NO_MOVEMENT < m_movement)
	{
		m_x += x;
		m_y += y;
		m_movement--;
	}

	if (NO_MOVEMENT == m_movement)
	{
		select = Select_Type::selectnothing;
		selectunit = NO_UNIT_SELECTED;
		m_blit = ZERO_BLIT;
		m_show = true;
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : heal																		   */
/* ROLE : Soigne l'unit� en fonction du territoire sur lequel elle se trouve		   */
/* INPUT : const std::vector<std::vector<Tile>>& tiles : tableau de cases			   */
/* INPUT : unsigned int : donn�es g�n�rale de la map : joueur s�lectionn�			   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::heal
(
	const MatriceMap& tiles,
	const unsigned int selectplayer
)
{
	const int i(MainMap::convertPosXToIndex(m_x));
	const int j(MainMap::convertPosYToIndex(m_y));

	if (NO_APPARTENANCE == tiles[i][j].appartenance)
	{
		m_life += (unsigned int)ceil(m_maxlife / COEF_DIV_HEAL_NO_APPARTENANCE);
		if (m_life > m_maxlife)
		{
			m_life = m_maxlife;
		}
		return;
	}
	else if (tiles[i][j].appartenance == (int)selectplayer)
	{
		m_life += (unsigned int)ceil(m_maxlife / COEF_DIV_HEAL_APPARTENANCE);
		if (m_life > m_maxlife)
		{
			m_life = m_maxlife;
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
/* ROLE : Incr�mentation de 1 de level												   */
/* INPUT : void																		   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::levelup()
{
	m_level++;

	m_maxlife += (int)ceil(m_maxlife / COEF_DIV_LEVELUP);
	m_life = m_maxlife;

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
	m_movement = m_maxmovement;
}

void Unit::RESETnumberOfAttack()
{
	m_numberOfAttack = m_maxNumberOfAttack;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : testPos																	   */
/* ROLE : Test sur les positions de la souris et de l'unit�							   */
/* INPUT : unsigned int mouse_x : position x										   */
/* INPUT : unsigned int mouse_y : position y										   */
/* RETURNED VALUE    : int : 0 : pas s�lection� / 1 : s�lectionn�					   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Unit::testPos
(
	const unsigned int mouse_x,
	const unsigned int mouse_y
)
{
	if (
		(unsigned __int64)m_x == mouse_x
		&&
		(unsigned __int64)m_y == mouse_y
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
	return m_movementType == Unit_Movement_Type::ground ? true : false;
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
	return m_movementType == Unit_Movement_Type::air ? true : false;
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
	return m_movementType == Unit_Movement_Type::water ? true : false;
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
	return m_movementType == Unit_Movement_Type::deepwater ? true : false;
}

bool Unit::isPossibleToAttack()
{
	return m_numberOfAttack > ZERO_NUMBER_OF_ATTACK ? true : false;
}

bool Unit::isThisUnitType
(
	const std::string& nameToCompare
)
{
	if (m_name.compare(nameToCompare) == IDENTICAL_STRINGS)
	{
		return true;
	}
	return false;
}


/* ----------------------------------------------------------------------------------- */
/* NAME : irrigate																	   */
/* ROLE : Modify GroundType 														   */
/* RETURNED VALUE : bool															   */
/* ----------------------------------------------------------------------------------- */
bool Unit::irrigate
(
	MatriceMap& map
)
{
	Tile& tileToIrragate{ map[MainMap::convertPosXToIndex(m_x)][MainMap::convertPosXToIndex(m_y)] };

	if	(
			(NO_MOVEMENT < m_movement)
			&&
			(tileToIrragate.tile_spec == GroundSpec_Type::nothing)
			&&
			(tileToIrragate.appartenance == m_owner->GETid())
		)
	{
		tileToIrragate.tile_ground = Ground_Type::irragated;
		tileToIrragate.food = +FOOD_ADD_BY_IRRAGATION;
		tileToIrragate.gold = +GOLD_ADD_BY_IRRAGATION;
		return true;
	}
	return false;
}

/* *********************************************************
 *					END Units::METHODS					   *
 ********************************************************* */


 /* *********************************************************
  *			START Units::METHODS::AFFICHAGE				   *
  ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : cmpblit																	   */
/* ROLE : Compteur permettant de faire clignoter l'unit�							   */
/* ROLE : Attention : bas� sur SCREEN_REFRESH_RATE									   */
/* INPUT : void																		   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Unit::cmpblit()
{
	/* ---------------------------------------------------------------------- */
	/* 50% off 50% on , environ 1s le cycle									  */
	/* ---------------------------------------------------------------------- */
	if ((++m_blit %= (RealEngine2D::SCREEN_REFRESH_RATE / BLIT_RATE)) == MODULO_ZERO)
	{
		m_show = !m_show;
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