/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2024 (robin.sauter@orange.fr)

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

#include "App.h"
#include "jsonloader.h"
#include "LogSentences.h"
#include "MainMap.h"
#include "Player.h"
#include "Players.h"
#include "T_Unit.h"

#include <jsoncons/json.hpp>
#include <R2D/src/CardinalDirection.h> 
#include <R2D/src/ErrorLog.h> 
#include <R2D/src/Log.h> 

namespace UNITC
{
	constexpr char DEFAULT_UNIT_NAME[] = "DEFAULT_UNIT_NAME";

	constexpr unsigned int NO_MOVEMENT = 0;

	constexpr unsigned int ENOUGH_DAMAGE_TO_KILL = 0;

	constexpr unsigned int ZERO_LIFE = 0;

	constexpr unsigned int ZERO_BLIT = 0;

	constexpr unsigned int ZERO_NUMBER_OF_ATTACK = 0;

	constexpr bool DEAD_UNIT = false;

	/*
		use as 1/x
		default : x = 20
	*/
	constexpr unsigned int COEF_DIV_HEAL_NO_APPARTENANCE = 20;

	/*
		use as 1/x
		default : x = 5
	*/
	constexpr unsigned int COEF_DIV_HEAL_APPARTENANCE = 5;

	/*
		use as 1/x
		default : x = 4
	*/
	constexpr unsigned int COEF_DIV_LEVELUP = 4;

	/*
		use as 1/x
		Use for screen_refresh_rate/BLIT_RATE
		default = 2
	*/
	constexpr unsigned int BLIT_RATE = 2;

	constexpr int FOOD_ADD_BY_IRRAGATION = 2;
	constexpr int GOLD_ADD_BY_IRRAGATION = 1;
}

unsigned int Unit::searchUnitByName
(
	const std::string& name,
	const VectUnitTemplate& tabUnit_Template
)
{
	for (unsigned int p(0); p < tabUnit_Template.size(); p++)
	{
		if (tabUnit_Template[p].name.compare(name) == STRINGS::IDENTICAL)
		{
			return p;
		}
	}
	return 0;
}

bool Unit::searchUnitTile
(
	Players& players,
	const glm::i32vec2& mouseCoorNorm,
	Select_Type* select
)
{
	if (SELECTION::NO_PLAYER_SELECTED < players.GETselectedPlayerId())
	{
		PlayerPtrT selPlayer(players.GETselectedPlayerPtr());

		for (unsigned int i(0); i < selPlayer->GETtabUnit().size(); i++)
		{
			if (selPlayer->GETtabUnit()[i]->testPos(mouseCoorNorm.x, mouseCoorNorm.y))
			{
				selPlayer->SETselectedUnit(i);

				selPlayer->GETtabUnit()[i]->SETshow(true);
				*select = Select_Type::selectmove;

				LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::SEARCH_UNIT_TILE, logS::DATA::SEARCH_UNIT_TILE,
					i, selPlayer->GETtabUnit()[i]->GETname(), selPlayer->GETname());

				return true;
			}
		}
		selPlayer.reset();
	}
	return false;
}

void Unit::tryToMove
(
	const MatriceMap& maps,
	Players& players,
	Select_Type select,
	const R2D::CardinalDirection& cardinalDirection
)
{
	if (players.GETselectedPlayerId() != SELECTION::NO_PLAYER_SELECTED)
	{
		const PlayerPtrT selPlayer(players.GETselectedPlayerPtr());
		int playerToAttack(SELECTION::NO_PLAYER_SELECTED), unitToAttack(SELECTION::NO_UNIT_SELECTED), selectunit(selPlayer->GETselectedUnit());

		switch (searchToMove(maps, players, cardinalDirection, &playerToAttack, &unitToAttack))
		{
		case Move_Type::canMove:

			selPlayer->GETtabUnit()[selectunit]->move(select, selectunit, cardinalDirection);
			selPlayer->SETselectedUnit(selectunit);
			players.SETneedToUpdateDrawUnit(PlayerH::NEED_TO_UPDATE_DRAW_UNIT);
			break;
		case Move_Type::attackMove:
		{
			/* safe index playerToAttack / unitToAttack : filled by searchToMove */
			const PlayerPtrT attackPlayer(players.GETvectPlayer()[playerToAttack]);
			const UnitPtrT attackUnit{ selPlayer->GETtabUnit()[selectunit] };
			const UnitPtrT defenderUnit{ attackPlayer->GETtabUnit()[unitToAttack] };

			if	(attackUnit->isPossibleToAttack())
			{
				attackUnit->attack(*(defenderUnit.get()));

				/* if the opposite Unit is destroy, try to move to its position */
				if (defenderUnit->GETalive() == UNITC::DEAD_UNIT)
				{
					attackPlayer->deleteUnit(unitToAttack);
					tryToMove(maps, players, select, cardinalDirection);
				}
			}
			
			/* Cannot move further for this turn */
			attackUnit->SETmovement(UNITC::NO_MOVEMENT);
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

Move_Type Unit::searchToMove
(
	const MatriceMap& maps,
	Players& players,
	const R2D::CardinalDirection& cardinalDirection,
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

	const PlayerPtrT selPlayer(players.GETselectedPlayerPtr());
	const UnitPtrT unit(selPlayer->GETtabUnit()[selPlayer->GETselectedUnit()]);


	bool nextTileValidToMove(false);
	const unsigned int xIndex
	(MainMap::convertPosXToIndex(unit->GETx() + cardinalDirection.GETpixelValueEW()));
	const unsigned int yIndex
	(MainMap::convertPosYToIndex(unit->GETy() + cardinalDirection.GETpixelValueNS()));

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
				condition = checkUnitNextTile
					(
						*unit,
						*(players.GETvectPlayer()[i]->GETtabUnit()[j]),
						cardinalDirection.GETpixelValueEW(),
						cardinalDirection.GETpixelValueNS()
					);
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

Unit::Unit()
: 
m_name(UNITC::DEFAULT_UNIT_NAME),
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
m_blit(UNITC::ZERO_BLIT),
m_show(true),
m_showStats(false),
m_owner(SELECTION::NO_OWNER)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_UNIT, logS::DATA::CONSTRUCTOR_UNIT,
		m_name, m_x, m_y);
}

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
m_blit(UNITC::ZERO_BLIT),
m_show(true),
m_showStats(false),
m_owner(ptrToPlayer)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_UNIT, logS::DATA::CONSTRUCTOR_UNIT,
		m_name, m_x, m_y);
}

Unit::~Unit()
{
	m_owner = nullptr;
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_UNIT, logS::DATA::DESTRUCTOR_UNIT, m_name);
}

void Unit::attack
(
	Unit& cible
)
{
	m_numberOfAttack--;

	if (m_movement > UNITC::NO_MOVEMENT)
	{
		LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::UNIT, logS::DATA::ATTACK, m_name, cible.GETname());
		cible.defend(m_atq);
	}
}

void Unit::defend
(
	const int dmg
)
{
	if (dmg > m_def)
	{
		const int damageReceive{ (dmg - m_def) };
		if ((m_life - damageReceive) <= UNITC::ENOUGH_DAMAGE_TO_KILL)
		{
			m_life = UNITC::ZERO_LIFE;
			m_alive = false;
			LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::UNIT, logS::DATA::DIE_FROM_ATTACK, m_name, damageReceive);
		}
		else
		{
			m_life -= damageReceive;
			LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::UNIT, logS::DATA::DMG_FROM_ATTACK, m_name, damageReceive, m_life);
		}
	}
}

void Unit::move
(
	Select_Type& select,
	int& selectunit,
	const R2D::CardinalDirection& cardinalDirection
)
{
	if (UNITC::NO_MOVEMENT < m_movement)
	{
		m_x += cardinalDirection.GETpixelValueEW();
		m_y += cardinalDirection.GETpixelValueNS();
		m_movement--;
		LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::UNIT, logS::DATA::MOVE, m_name, m_movement);
	}

	if (UNITC::NO_MOVEMENT == m_movement)
	{
		select = Select_Type::selectnothing;
		selectunit = SELECTION::NO_UNIT_SELECTED;
		m_blit = UNITC::ZERO_BLIT;
		m_show = true;
		LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::UNIT, logS::DATA::FINISH_MOVING, m_name);
	}
}

void Unit::heal
(
	const MatriceMap& tiles,
	const unsigned int selectplayer
)
{
	const int i(MainMap::convertPosXToIndex(m_x));
	const int j(MainMap::convertPosYToIndex(m_y));

	if (SELECTION::NO_APPARTENANCE == tiles[i][j].appartenance)
	{
		m_life += (unsigned int)ceil(m_maxlife / UNITC::COEF_DIV_HEAL_NO_APPARTENANCE);
		if (m_life > m_maxlife)
		{
			m_life = m_maxlife;
		}
		return;
	}
	else if (tiles[i][j].appartenance == (int)selectplayer)
	{
		m_life += (unsigned int)ceil(m_maxlife / UNITC::COEF_DIV_HEAL_APPARTENANCE);
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

void Unit::levelup()
{
	m_level++;

	m_maxlife += (int)ceil(m_maxlife / UNITC::COEF_DIV_LEVELUP);
	m_life = m_maxlife;

	/* Todo */
	//heal();
}

void Unit::RESETmovement()
{
	m_movement = m_maxmovement;
}

void Unit::RESETnumberOfAttack()
{
	m_numberOfAttack = m_maxNumberOfAttack;
}

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

bool Unit::isGroundMovement_Type()
{
	return m_movementType == Unit_Movement_Type::ground ? true : false;
}

/* ----------------------------------------------------------------------------------- */
bool Unit::isAirMovement_Type()
{
	return m_movementType == Unit_Movement_Type::air ? true : false;
}

bool Unit::isWaterMovement_Type()
{
	return m_movementType == Unit_Movement_Type::water ? true : false;
}

bool Unit::isDeepWaterMovement_Type()
{
	return m_movementType == Unit_Movement_Type::deepwater ? true : false;
}

bool Unit::isPossibleToAttack()
{
	return m_numberOfAttack > UNITC::ZERO_NUMBER_OF_ATTACK ? true : false;
}

bool Unit::isThisUnitType
(
	const std::string& nameToCompare
)
{
	if (m_name.compare(nameToCompare) == STRINGS::IDENTICAL)
	{
		return true;
	}
	return false;
}

bool Unit::irrigate
(
	MatriceMap& map
)
{
	Tile& tileToIrragate{ map[MainMap::convertPosXToIndex(m_x)][MainMap::convertPosXToIndex(m_y)] };

	if	(
			(UNITC::NO_MOVEMENT < m_movement)
			&&
			(tileToIrragate.tile_spec == GroundSpec_Type::nothing)
			&&
			(tileToIrragate.appartenance == m_owner->GETid())
		)
	{
		tileToIrragate.tile_ground = Ground_Type::irragated;
		tileToIrragate.food = +UNITC::FOOD_ADD_BY_IRRAGATION;
		tileToIrragate.gold = +UNITC::GOLD_ADD_BY_IRRAGATION;
		return true;
	}
	return false;
}

void Unit::cmpblit()
{
	/* ---------------------------------------------------------------------- */
	/* 50% off 50% on , environ 1s le cycle									  */
	/* ---------------------------------------------------------------------- */
	if ((++m_blit %= (R2D::SCREEN_REFRESH_RATE / UNITC::BLIT_RATE)) == MODULO::ZERO)
	{
		m_show = !m_show;
	}
	else
	{
		/* N/A */
	}
}

jsoncons::ojson Unit::saveToOjson()
{
	jsoncons::ojson value;
	value.insert_or_assign("m_name", m_name);
	value.insert_or_assign("m_x", m_x);
	value.insert_or_assign("m_y", m_y);
	value.insert_or_assign("m_movementType", static_cast<size_t>(m_movementType));
	value.insert_or_assign("m_maxlife", m_maxlife);
	value.insert_or_assign("m_maxatq", m_maxatq);
	value.insert_or_assign("m_maxdef", m_maxdef);
	value.insert_or_assign("m_maxmovement", m_maxmovement);
	value.insert_or_assign("m_level", m_level);
	value.insert_or_assign("m_life", m_life);
	value.insert_or_assign("m_atq", m_atq);
	value.insert_or_assign("m_def", m_def);
	value.insert_or_assign("m_movement", m_movement);
	value.insert_or_assign("m_level", m_level);
	value.insert_or_assign("m_maintenance", m_maintenance);
	return value;
}

 /*
 *	End Of File Unit.cpp
 */