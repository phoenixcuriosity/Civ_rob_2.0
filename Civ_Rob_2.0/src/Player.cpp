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

#include "Player.h"

#include "App.h"
#include "City.h"
#include "jsonloader.h"
#include "LogSentences.h"
#include "MainMap.h"
#include "SaveReload.h"
#include "Unit.h"
#include "Utility.h"

#include <jsoncons/json.hpp>
#include <R2D/src/ResourceManager.h>
#include <R2D/src/ValueToScale.h>
#include <R2D/src/ErrorLog.h>
#include <R2D/src/Log.h>

Player::Player
(
	Private,
	const std::string& name,
	const int id
)
	:
	m_name(name),
	m_id(id),
	m_selectedUnit(SELECTION::NO_UNIT_SELECTED),
	m_selectedCity(SELECTION::NO_CITY_SELECTED),
	m_goldStats{ PlayerH::INITIAL_GOLD , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
	m_onOffDisplay{ false },
	m_unitManager(),
	m_CityManager()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_PLAYER, logS::DATA::CONSTRUCTOR_PLAYER, saveToOjson().as_string());
}

Player::~Player()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_PLAYER, logS::DATA::DESTRUCTOR_PLAYER, saveToOjson().as_string());
}

void Player::addEmptyUnit()
{
	m_unitManager.addEmptyUnit();
}

void Player::addUnit
(
	const Unit::UnitName& name,
	const Unit::Coor coor
)
{
	m_unitManager.addUnit(name, coor, shared_from_this());
}

void Player::deleteUnit
(
	const unsigned int index
)
{
	m_unitManager.removeUnit(index);
}

void Player::addCity(const Unit::Coor coor, VectMapPtr& tiles)
{
	m_CityManager.addCity(m_id, coor, tiles);
}

void Player::addEmptyCity()
{
	m_CityManager.addEmptyCity();
}

void Player::deleteCity
(
	const unsigned int index
)
{
	m_CityManager.removeCity(index);
}

CityPtrT* Player::searchCity
(
	const unsigned int indexX,
	const unsigned int indexY
)
{
	for (auto &c : m_CityManager.getCities())
	{
		if (c->searchCityTile(indexX, indexY)) return &c;
	}
	return nullptr;
}

void Player::computeGold()
{
	computeMaintenanceCostUnit();

	m_goldStats.income = m_goldStats.taxIncome
		+ m_goldStats.commerceIncome
		+ m_goldStats.goldConversionSurplus;

	m_goldStats.cost = m_goldStats.buildingsCost
		+ m_goldStats.armiesCost;

	m_goldStats.goldBalance = m_goldStats.income - m_goldStats.cost;
	m_goldStats.gold += m_goldStats.goldBalance;

}

void Player::computeMaintenanceCostUnit()
{
	/*
	for (unsigned int i(0); i < m_tabUnit.size(); i++)
	{
		m_goldStats.armiesCost += m_tabUnit[i]->GETmaintenance();
	}
	*/
}

void Player::resetGoldStats()
{
	m_goldStats.goldBalance = 0.0;
	m_goldStats.cost = 0.0;
	m_goldStats.taxIncome = 0.0;
	m_goldStats.commerceIncome = 0.0;
	m_goldStats.goldConversionSurplus = 0.0;
	m_goldStats.buildingsCost = 0.0;
	m_goldStats.armiesCost = 0.0;
}

void Player::addGoldToGoldConversionSurplus
(
	const double goldToAdd
)
{
	m_goldStats.goldConversionSurplus += goldToAdd;
}

jsoncons::ojson Player::saveToOjson()const
{
	jsoncons::ojson value;
	jsoncons::ojson units{ jsoncons::ojson::make_array() };
	jsoncons::ojson cities{ jsoncons::ojson::make_array() };
	jsoncons::ojson goldStats;

	for (const auto& unit : m_unitManager.getUnits())
	{
		units.push_back(unit->saveToOjson());
	}

	for (const auto& city : m_CityManager.getCities())
	{
		cities.push_back(city->saveToOjson());
	}

	goldStats.insert_or_assign("gold", m_goldStats.gold);
	goldStats.insert_or_assign("goldBalance", m_goldStats.goldBalance);
	goldStats.insert_or_assign("income", m_goldStats.income);
	goldStats.insert_or_assign("cost", m_goldStats.cost);
	goldStats.insert_or_assign("taxIncome", m_goldStats.taxIncome);
	goldStats.insert_or_assign("commerceIncome", m_goldStats.commerceIncome);
	goldStats.insert_or_assign("goldConversionSurplus", m_goldStats.goldConversionSurplus);
	goldStats.insert_or_assign("armiesCost", m_goldStats.armiesCost);
	goldStats.insert_or_assign("buildingsCost", m_goldStats.buildingsCost);

	value.insert_or_assign("m_name", m_name);
	value.insert_or_assign("m_id", m_id);
	value.insert_or_assign("m_tabUnit", units);
	value.insert_or_assign("m_tabCity", cities);
	value.insert_or_assign("m_selectedUnit", m_selectedUnit);
	value.insert_or_assign("m_selectedCity", m_selectedCity);
	value.insert_or_assign("m_goldStats", goldStats);

	return value;
}

void Player::loadFromOjson(const jsoncons::ojson& jsonLoad, MatriceMap& matriceMap)
{
	if (
			jsonLoad.contains("m_tabUnit") && jsonLoad["m_tabUnit"].is_array() &&
			jsonLoad.contains("m_tabCity") && jsonLoad["m_tabCity"].is_array() &&
			jsonLoad.contains("m_selectedUnit") && jsonLoad.contains("m_selectedCity") &&
			jsonLoad.contains("m_goldStats") && jsonLoad["m_goldStats"].contains("cost") &&
			jsonLoad["m_goldStats"].contains("gold") && jsonLoad["m_goldStats"].contains("goldBalance") &&
			jsonLoad["m_goldStats"].contains("income") && jsonLoad["m_goldStats"].contains("taxIncome") &&
			jsonLoad["m_goldStats"].contains("commerceIncome") && jsonLoad["m_goldStats"].contains("goldConversionSurplus") &&
			jsonLoad["m_goldStats"].contains("armiesCost") && jsonLoad["m_goldStats"].contains("buildingsCost")
		)
	{
		m_selectedUnit = jsonLoad["m_selectedUnit"].as<int>();
		m_selectedCity = jsonLoad["m_selectedCity"].as<int>();
		m_goldStats = jsonLoad["m_goldStats"].as<GoldStats>();

		for (const auto& unit : jsonLoad["m_tabUnit"].array_range())
		{
			addEmptyUnit();
			m_unitManager.getUnits().back()->loadFromOjson(unit);
		}

		for (const auto& city : jsonLoad["m_tabCity"].array_range())
		{
			addEmptyCity();
			CityPtrT city_l{ m_CityManager.getCities().back() };
			city_l->loadFromOjson(city);
			City::loadCity(matriceMap, m_id, city_l, modifAppartenance_Type::dontModify);
		}
	}
	else
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_SAVE_PLAYER, logS::DATA::MISSING_KEY_JSON,
			R2D::ResourceManager::getFile(R2D::e_Files::savePlayers), jsonloader::KEY_PLAYERS);
	}
}

 /*
 *	End Of File : Player.cpp
 */