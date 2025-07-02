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

#include "../App.h"
#include "../jsonloader.h"
#include "../LogSentences.h"
#include "../MainMap.h"
#include "../Player.h"
#include "../Players.h"

#include <jsoncons/json.hpp>
#include <R2D/src/CardinalDirection.h>
#include <R2D/src/ErrorLog.h>
#include <R2D/src/Log.h>

unit::Unit::Unit(const PlayerPtrT& ptrToPlayer):
R2D::IBlickable(BLIT_RATE),
R2D::IMoveable(),
UnitStats(),
m_name(DEFAULT_UNIT_NAME),
m_alive(true),
m_maintenance(1.0),
m_owner(ptrToPlayer)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_UNIT, logS::DATA::CONSTRUCTOR_UNIT, m_name);
}

unit::Unit::Unit(	const UnitName& name,
			const Coor& coor,
			const UnitStat& unitStat,
			double maintenance,
			const PlayerPtrT& ptrToPlayer):
R2D::IBlickable(BLIT_RATE),
R2D::IMoveable(coor),
UnitStats(unitStat),
m_name(name),
m_alive(true),
m_maintenance(maintenance),
m_owner(ptrToPlayer)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_UNIT, logS::DATA::CONSTRUCTOR_UNIT, m_name);
}

unit::Unit::~Unit()
{
	m_owner = nullptr;
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_UNIT, logS::DATA::DESTRUCTOR_UNIT, m_name);
}

void unit::Unit::attack
(
	Unit& cible
)
{
	numberOfAttack--;

	if (canMove())
	{
		LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::UNIT, logS::DATA::ATTACK, m_name, cible.GETname());
		cible.defend(atq);
	}
}

void unit::Unit::defend
(
	const int dmg
)
{
	if (dmg > static_cast<int>(def))
	{
		const int damageReceive{ (dmg - static_cast<int>(def)) };
		if ((life - damageReceive) <= ENOUGH_DAMAGE_TO_KILL)
		{
			life = ZERO_LIFE;
			m_alive = false;
			LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::UNIT, logS::DATA::DIE_FROM_ATTACK, m_name, damageReceive);
		}
		else
		{
			life -= damageReceive;
			LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::UNIT, logS::DATA::DMG_FROM_ATTACK, m_name, damageReceive, life);
		}
	}
}

void unit::Unit::move
(
	Select_Type& select,
	int& selectunit,
	const R2D::CardinalDirection& cardinalDirection
)
{
	if (canMove())
	{
		moveX(cardinalDirection.m_pixelValueEW);
		moveY(cardinalDirection.m_pixelValueNS);
		movement--;
		LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::UNIT, logS::DATA::MOVE, m_name, movement);
	}

	if (!canMove())
	{
		select = Select_Type::selectnothing;
		selectunit = SELECTION::NO_UNIT_SELECTED;
		makeShow();
		LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::UNIT, logS::DATA::FINISH_MOVING, m_name);
	}
}

void unit::Unit::heal
(
	const MatriceMap& tiles,
	const unsigned int selectplayer
)
{
	const int i(MainMap::convertPosXToIndex(getX()));
	const int j(MainMap::convertPosYToIndex(getY()));

	if (SELECTION::NO_APPARTENANCE == tiles[i][j].appartenance)
	{
		healNeutral();
	}
	else if (tiles[i][j].appartenance == static_cast<int>(selectplayer))
	{
		healFriendly();
	}
	else
	{
		/* Do nothing*/
	}
}

bool unit::Unit::irrigate
(
	MatriceMap& map
)
{
	Tile& tileToIrragate{ map[MainMap::convertPosXToIndex(getX())][MainMap::convertPosXToIndex(getY())] };

	if	(
			(canMove())
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

void
unit::Unit
::nextTurn(const unsigned int index, const MatriceMap& matriceMap)
{
	resetMovement();
	resetNumberOfAttack();
	heal(matriceMap, index);
}

jsoncons::ojson unit::Unit::saveToOjson()const
{
	jsoncons::ojson value;
	value.insert_or_assign("m_name", m_name);
	value.insert_or_assign("m_x", m_coor.x);
	value.insert_or_assign("m_y", m_coor.y);
	value.insert_or_assign("m_movementType", static_cast<std::underlying_type_t<UnitTemplate::Movement_Type>>(movementType));
	value.insert_or_assign("m_maxlife", stats_max.life);
	value.insert_or_assign("m_maxatq", stats_max.atq);
	value.insert_or_assign("m_maxdef", stats_max.def);
	value.insert_or_assign("m_maxmovement", stats_max.movement);
	value.insert_or_assign("m_maxlevel", stats_max.level);
	value.insert_or_assign("m_life", life);
	value.insert_or_assign("m_atq", atq);
	value.insert_or_assign("m_def", def);
	value.insert_or_assign("m_movement", movement);
	value.insert_or_assign("m_level", level);
	value.insert_or_assign("m_maintenance", m_maintenance);
	return value;
}

void unit::Unit::loadFromOjson(const jsoncons::ojson& jsonLoad)
{
	if	(
			jsonLoad.contains("m_name") && jsonLoad.contains("m_x") && jsonLoad.contains("m_y") &&
			jsonLoad.contains("m_movementType") && jsonLoad.contains("m_maxlife") && jsonLoad.contains("m_maxatq") &&
			jsonLoad.contains("m_maxdef") && jsonLoad.contains("m_maxmovement") && jsonLoad.contains("m_maxlevel") &&
			jsonLoad.contains("m_life") && jsonLoad.contains("m_atq") && jsonLoad.contains("m_def") &&
			jsonLoad.contains("m_movement") && jsonLoad.contains("m_level") && jsonLoad.contains("m_maintenance")
		)
	{
		m_name = jsonLoad["m_name"].as_string();
		m_coor.x = jsonLoad["m_x"].as<unsigned int>();
		m_coor.y = jsonLoad["m_y"].as<unsigned int>();
		movementType = static_cast<UnitTemplate::Movement_Type>(jsonLoad["m_movementType"].as<std::underlying_type_t<UnitTemplate::Movement_Type>>());
		stats_max.life = jsonLoad["m_maxlife"].as<int>();
		stats_max.atq = jsonLoad["m_maxatq"].as<int>();
		stats_max.def = jsonLoad["m_maxdef"].as<int>();
		stats_max.movement = jsonLoad["m_maxmovement"].as<int>();
		stats_max.level = jsonLoad["m_maxlevel"].as<int>();
		life = jsonLoad["m_life"].as<int>();
		atq = jsonLoad["m_atq"].as<int>();
		def = jsonLoad["m_def"].as<int>();
		movement = jsonLoad["m_movement"].as<int>();
		level = jsonLoad["m_level"].as<int>();
		m_maintenance = jsonLoad["m_maintenance"].as<int>();
	}
	else
	{
		throw(jsonloader::KEY_PLAYERS);
	}
}

 /*
 *	End Of File Unit.cpp
 */