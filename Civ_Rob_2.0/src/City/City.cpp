﻿/*

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

#include "City.h"

#include "Citizen.h"
#include "../Screens/GameplayScreen.h"
#include "../LogSentences.h"
#include "../Player.h"
#include "../Players.h"
#include "JsonCitySerializerVisitor.h"

#include <R2D/src/Log.h>

void city::City::createCity
(
	GamePlayScreen& mainGame,
	const unsigned int influenceLevel /* = CITY_INFLUENCE::MIN_INFLUENCE_LEVEL */
)
{
	const unsigned int selectedPlayer((unsigned int)mainGame.GETPlayers().GETselectedPlayerId());
	PlayerPtrT splayer(mainGame.GETPlayers().GETselectedPlayerPtr());
	const unsigned int selectedUnit((unsigned int)splayer->GETselectedUnit());
	const UnitPtrT sUnit(splayer->GETtabUnit()[selectedUnit]);

	VectMapPtr tabtiles;
	tabtiles.resize(City::INIT_AREA_VIEW);

	fillCitieTiles
	(
		MainMap::convertPosXToIndex(sUnit->getX()), MainMap::convertPosYToIndex(sUnit->getY()),
		selectedPlayer, mainGame.GETmainMap().GETmatriceMap(), tabtiles, influenceLevel
	);

	splayer->addCity(sUnit->getCoor(), tabtiles);

	splayer->deleteUnit(selectedUnit);
	splayer->SETselectedUnit(SELECTION::NO_UNIT_SELECTED);

	mainGame.GETPlayers().SETneedToUpdateDrawUnit(true);
	mainGame.GETPlayers().SETneedToUpdateDrawCity(true);

	splayer.reset();
}

void city::City::loadCity
(
	MatriceMap& matriceMap,
	const unsigned int selectplayer,
	CityPtrT& city,
	const modifAppartenance_Type modAppartenance /* = modifAppartenance_Type::modify */
)
{
	assert(city);

	VectMapPtr tiles;
	tiles.resize(City::INIT_AREA_VIEW);
	City::fillCitieTiles
	(
		MainMap::convertPosXToIndex(city->getCoor().x), MainMap::convertPosYToIndex(city->getCoor().y),
		selectplayer, matriceMap, tiles, city->GETinfluenceLevel(), modAppartenance
	);
	city->SETVectMapPtr(tiles);
}

void city::City::fillCitieTiles
(
	const unsigned int middletileX,
	const unsigned int middletileY,
	const unsigned int selectplayer,
	MatriceMap& matriceMap,
	VectMapPtr& tabtile,
	const unsigned int influenceLevel /* = MIN_INFLUENCE_LEVEL */,
	const modifAppartenance_Type modAppartenance /* = modifAppartenance_Type::modify */
)
{
	unsigned int k(0);
	for (int o(-INIT_SIZE_VIEW_DIV + 1); o < INIT_SIZE_VIEW_DIV; o++)
	{
		if (middletileX + o < 0 || middletileX + o >= matriceMap.size()) continue;

		for (int p(-INIT_SIZE_VIEW_DIV + 1); p < INIT_SIZE_VIEW_DIV; p++)
		{
			if (middletileY + p < 0 || middletileY + p >= matriceMap[0].size()) continue;

			if ((modAppartenance == modifAppartenance_Type::modify) && (initSizeInfluenceCondition(o, p, influenceLevel)))
			{
				matriceMap[middletileX + o][middletileY + p].appartenance = selectplayer;
			}

			tabtile[k] = &matriceMap[middletileX + o][middletileY + p];
			k++;
		}
	}
}

bool city::City::initSizeInfluenceCondition
(
	const int o,
	const int p,
	const unsigned int influenceLevel
)
{
	const int bound{ static_cast<int>(MIN_INFLUENCE_LEVEL * influenceLevel) };
	if  (
			o >= -bound && o <= bound && p >= -bound && p <= bound
			&&
			cornerCheck(o, p, influenceLevel)
		)
	{
		return true;
	}
	return false;
}

bool city::City::cornerCheck
(
	const int o,
	const int p,
	const unsigned int influenceLevel
)
{
	if	(
			(MIN_INFLUENCE_LEVEL < influenceLevel)
			&&
			(std::abs(o) == std::abs(p))
			&&
			(MIN_INFLUENCE_LEVEL * influenceLevel) == (unsigned int)std::abs(o)
		)
	{
		return false;
	}
	return true;
}

bool city::City::searchCityTile
(
	const unsigned int indexX,
	const unsigned int indexY
)
{
	if	(
			MainMap::convertPosXToIndex(getCoor().x) == indexX
			&&
			MainMap::convertPosXToIndex(getCoor().y) == indexY
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void logCityConstructor(const city::City& city)
{
	city::JsonCitySerializerVisitor visitor;
	visitor.visit(city);
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_CITY, logS::DATA::CONSTRUCTOR_CITY, visitor.result.to_string());
}
city::City::City(const PlayerPtrT& player)
:
IMoveable(),
m_image("EMPTY"),
m_name("EMPTY"),
m_tileMap(),
m_influenceLevel(MIN_INFLUENCE_LEVEL),
m_atq(0),
m_def(0),
m_nbstructurebuild(0),
m_conversionToApply(conversionSurplus_Type::No_Conversion),
m_citizenManager(m_tileMap),
m_foodManager(m_citizenManager),
m_buildManager(m_citizenManager, m_foodManager, m_conversionToApply),
m_goldBalance(0.0),
m_owner(player)
{
	logCityConstructor(*this);
}

city::City::City
(
	const std::string& name,
	const Coor coor,
	VectMapPtr& tiles,
	const PlayerPtrT& player
)
	:
	IMoveable(coor),
	m_image("citie.png"),
	m_name(name),
	m_tileMap(tiles),
	m_influenceLevel(MIN_INFLUENCE_LEVEL),
	m_atq(0),
	m_def(0),
	m_nbstructurebuild(0),
	m_conversionToApply(conversionSurplus_Type::No_Conversion),
	m_citizenManager(m_tileMap),
	m_foodManager(m_citizenManager),
	m_buildManager(m_citizenManager, m_foodManager, m_conversionToApply),
	m_goldBalance(0.0),
	m_owner(player)
{
	logCityConstructor(*this);
}

city::City::~City()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_CITY, logS::DATA::DESTRUCTOR_CITY, m_name);
}

void
city::City
::nextTurn(bool& needToUpdateDrawUnit)
{
	/* computeEmotion must be in first : Emotion use on other computations */
	computeEmotion();

	computefood();
	computeWork(needToUpdateDrawUnit);
	computeGold();
	addCityGoldToTaxIncome();
}

void city::City::computefood()
{
	switch (m_foodManager.updateGetFoodStatus())
	{
	case FoodManager::FoodManagerType::famine:

		if (m_citizenManager.getCitizens().size() > MIN_POP)
		{
			m_citizenManager.removeCitizen();

			m_foodManager.updateFoodStockFromReducePop();
		}
		else
		{
			m_foodManager.emptyFoodStock();
		}

		break;
	case FoodManager::FoodManagerType::surplus:

		m_citizenManager.addCitizen();

		m_foodManager.updateFoodStockFromIncreasePop();

		break;
	case FoodManager::FoodManagerType::neutral:
		/* Do Nothing */
		break;
	}

	switch (m_conversionToApply)
	{
	case conversionSurplus_Type::No_Conversion:
		/* N/A */
		break;
	case conversionSurplus_Type::FoodToWork:
		m_buildManager.convertFoodSurplusToWork(m_foodManager.getFoodBalanceForConversion());
		m_foodManager.ResetFoodBalanceFromConversion();
		break;
	case conversionSurplus_Type::FoodToGold:
		convertFoodSurplusToGold(m_foodManager.getFoodBalanceForConversion());
		m_foodManager.ResetFoodBalanceFromConversion();
		break;
	case conversionSurplus_Type::WorkToFood:
		/* N/A */
		break;
	case conversionSurplus_Type::WorkToGold:
		/* N/A */
		break;
	case conversionSurplus_Type::GoldToFood:
		/* N/A */
		break;
	case conversionSurplus_Type::GoldToWork:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}

void city::City::computeWork(bool& needToUpdateDrawUnit)
{
	m_buildManager.computeWork();

	switch (m_conversionToApply)
	{
	case conversionSurplus_Type::No_Conversion:
	case conversionSurplus_Type::FoodToWork:
	case conversionSurplus_Type::FoodToGold:
	case conversionSurplus_Type::WorkToFood:
	case conversionSurplus_Type::GoldToFood:
	case conversionSurplus_Type::GoldToWork:

		m_buildManager.computeWorkToBuild(needToUpdateDrawUnit);

		break;
	default:

#ifdef _DEBUG
		throw("[ERROR]___: computeWorkToBuild : conversionSurplus_Type::??????");
#endif // _DEBUG

		break;
	case conversionSurplus_Type::WorkToGold:

		/* CASE : work conversion to gold */
		m_owner->addGoldToGoldConversionSurplus
			(
				m_buildManager.getWorkBalance()
				*
				BuildManager::WORK_TO_GOLD
			);

		break;
	}
}

void city::City::computeGold()
{
	/* Sum gold from citizen */
	m_goldBalance = m_citizenManager.getGoldFromCitizen();

	/* Applying Emotion multiplier */
	m_goldBalance *= ((double)m_citizenManager.getEmotion() / Citizen::EMOTION_MEAN);
}

void city::City::addCityGoldToTaxIncome()
{
	m_owner->GETgoldStats().taxIncome += m_goldBalance;
	m_goldBalance = 0.0;
}

void city::City::convertFoodSurplusToGold
(
	const double foodSurplus
)
{
	m_owner->GETgoldStats().goldConversionSurplus = foodSurplus * BuildManager::FOOD_TO_GOLD;
}

void
city::City
::accept(ICityVisitor& visitor) const
{
	visitor.visit(*this);
}