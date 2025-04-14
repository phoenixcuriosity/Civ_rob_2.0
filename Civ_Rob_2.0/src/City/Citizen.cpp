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

#include "Citizen.h"

#include "App.h"
#include "City.h"
#include "LogSentences.h"
#include "T_MainMap.h"

#include <jsoncons/json.hpp>
#include <R2D/src/Log.h>

city::Citizen::Citizen()
	:
	m_tileOccupied((unsigned int)ceil(City::INIT_AREA_VIEW / 2)),
	m_happiness(Emotion_Type::neutral),
	m_food(2),
	m_work(1),
	m_gold(1),
	m_revolt(0),
	m_religion(Religion_Type::catholic),
	m_place(false)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_CITIZEN, logS::DATA::CONSTRUCTOR_CITIZEN,
		saveToOjson().as_string());
}

city::Citizen::Citizen
(
	const Tile& tile
)
	:
	m_tileOccupied((unsigned int)ceil(City::INIT_AREA_VIEW / 2)),
	m_happiness(Emotion_Type::neutral),
	m_food(tile.food),
	m_work(tile.work),
	m_gold(tile.gold),
	m_revolt(0),
	m_religion(Religion_Type::catholic),
	m_place(true)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_CITIZEN, logS::DATA::CONSTRUCTOR_CITIZEN,
		saveToOjson().as_string());
}

city::Citizen::Citizen
(
	const unsigned int tileOccupied,
	const int food,
	const int work,
	const int gold
)
	:
	m_tileOccupied(tileOccupied),
	m_food(food),
	m_work(work),
	m_gold(gold),
	m_happiness(Emotion_Type::neutral),
	m_revolt(0),
	m_religion(Religion_Type::catholic),
	m_place(true)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_CITIZEN, logS::DATA::CONSTRUCTOR_CITIZEN,
		saveToOjson().as_string());
}

city::Citizen::~Citizen()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_CITIZEN, logS::DATA::EMPTY_DATA);
}

jsoncons::ojson city::Citizen::saveToOjson()const
{
	jsoncons::ojson value;
	value.insert_or_assign("m_tileOccupied", m_tileOccupied);
	value.insert_or_assign("m_food", m_food);
	value.insert_or_assign("m_work", m_work);
	value.insert_or_assign("m_gold", m_gold);
	value.insert_or_assign("m_happiness", static_cast<int>(m_happiness));
	value.insert_or_assign("m_revolt", m_revolt);
	value.insert_or_assign("m_religion", static_cast<size_t>(m_religion));
	value.insert_or_assign("m_place", m_place);
	return value;
}

void city::Citizen::loadFromOjson(const jsoncons::ojson& jsonLoad)
{
	if (
			jsonLoad.contains("m_tileOccupied") && jsonLoad.contains("m_food") && jsonLoad.contains("m_work") &&
			jsonLoad.contains("m_gold") && jsonLoad.contains("m_happiness") && jsonLoad.contains("m_revolt") &&
			jsonLoad.contains("m_religion") && jsonLoad.contains("m_place")
		)
	{
		m_tileOccupied = jsonLoad["m_tileOccupied"].as<unsigned int>();
		m_food = jsonLoad["m_food"].as<int>();
		m_work = jsonLoad["m_work"].as<int>();
		m_gold = jsonLoad["m_gold"].as<int>();
		m_happiness = static_cast<Emotion_Type>(jsonLoad["m_happiness"].as<int>());
		m_revolt = jsonLoad["m_revolt"].as<int>();
		m_religion = static_cast<Religion_Type>(jsonLoad["m_religion"].as<size_t>());
		m_place = jsonLoad["m_place"].as<bool>();
	}
	else
	{
		throw("Citizen::loadFromOjson");
	}
}

 /*
  *	End Of File : Citizen.cpp
  */