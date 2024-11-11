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
#include "LogSentences.h"
#include "Unit.h"
#include "Utility.h"

#include <R2D/src/ResourceManager.h>
#include <R2D/src/ValueToScale.h>
#include <R2D/src/ErrorLog.h> 
#include <R2D/src/Log.h> 

 /* *********************************************************
  *				START Player::METHODS					   *
  ********************************************************* */

Player::Player() :
	m_name("NoName"),
	m_tabUnit(),
	m_tabCity(),
	m_selectedUnit(SELECTION::NO_UNIT_SELECTED),
	m_selectedCity(SELECTION::NO_CITY_SELECTED),
	m_goldStats{ PlayerH::INITIAL_GOLD , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
	m_onOffDisplay{ false }
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_PLAYER, logS::DATA::CONSTRUCTOR_PLAYER, 
		m_name, m_id);
}

Player::Player
(
	const std::string& name,
	const int id
) 
:
	m_name(name),
	m_id(id),
	m_tabUnit(),
	m_tabCity(),
	m_selectedUnit(SELECTION::NO_UNIT_SELECTED),
	m_selectedCity(SELECTION::NO_CITY_SELECTED),
	m_goldStats{ PlayerH::INITIAL_GOLD , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
	m_onOffDisplay{ false }
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_PLAYER, logS::DATA::CONSTRUCTOR_PLAYER,
		m_name, m_id);
}

Player::~Player()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_PLAYER, logS::DATA::DESTRUCTOR_PLAYER, m_name);
	deletePlayer();
}

Player& Player::operator=
(
	const Player& player
)
{
	if (this != &player)
	{
		deletePlayer();
		m_name = player.GETname();
		m_tabUnit = player.GETtabUnit();
		m_tabCity = player.GETtabCity();
		m_goldStats = player.GETgoldStats();
	}
	return *this;
}

void Player::deletePlayer()
{
	for (auto& u : m_tabUnit)
	{
		u.reset();
	}
	m_tabUnit.clear();

	for (auto& c : m_tabCity)
	{
		c.reset();
	}
	m_tabCity.clear();
}

void Player::addEmptyUnit()
{
	m_tabUnit.push_back(std::make_shared<Unit>());
}

void Player::addUnit
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
	double maintenance
)
{
	m_tabUnit.push_back
	(
		std::make_shared<Unit>
		(
			name, x, y, movementType, life, atq, def, move, numberOfAttack, level, maintenance, this
		)
	);
}

void Player::deleteUnit
(
	const unsigned int index
)
{
	if (Utility::assertSize(m_tabUnit.size(), index))
	{
		if (nullptr != m_tabUnit[index])
		{
			m_tabUnit[index].reset();
			if (m_tabUnit.size() > 1 && index < m_tabUnit.size() - 1)
			{
				for (unsigned int i(index); i < (m_tabUnit.size() - 1); i++)
					m_tabUnit[i] = m_tabUnit[(unsigned __int64)i + 1];
			}
			m_tabUnit.pop_back();
		}
		else
		{
			LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_TAB_UNIT, logS::DATA::ERROR_DELETE_TAB_UNIT);
		}
	}
}

void Player::addCity
(
	const std::string& name,
	const unsigned int x,
	const unsigned int y,
	VectMap& tiles
)
{
	m_tabCity.push_back(std::make_shared<City>(name, x, y, tiles));
}

void Player::deleteCity
(
	const unsigned int index
)
{

	if (Utility::assertSize(m_tabCity.size(), index))
	{
		if (nullptr != m_tabCity[index])
		{
			m_tabCity[index].reset();
			if (m_tabCity.size() > 1 && index < m_tabCity.size() - 1)
			{
				for (unsigned int i(index); i < (m_tabCity.size() - 1); i++)
					m_tabCity[i] = m_tabCity[(unsigned __int64)i + 1];
			}
			m_tabCity.pop_back();
		}
		else
		{
			LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_TAB_CITY, logS::DATA::ERROR_DELETE_TAB_CITY);
		}
	}
}

CityPtrT* Player::searchCity
(
	const unsigned int indexX,
	const unsigned int indexY
)
{
	for (auto &c : m_tabCity)
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

 /*
 *	End Of File : Player.cpp
 */