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

#include "City.h"

#include "App.h"
#include "Citizen.h"
#include "GameplayScreen.h"
#include "jsonloader.h"
#include "LogSentences.h"
#include "Player.h"
#include "Players.h"
#include "Unit.h"
#include "Utility.h"

#include <jsoncons/json.hpp>
#include <R2D/src/Log.h> 
#include <R2D/src/ValueToScale.h>
#include <R2D/src/Window.h>

namespace POP
{
	/* Population maximale dans une Citie */
	constexpr unsigned int MAX = 50;

	/* Minimal population in City */
	constexpr unsigned int MIN = 1;
}

namespace RESOURCES
{
	namespace FOOD
	{
		/* Define the minimum food in a City */
		constexpr double ZERO = 0.0;

		/* Define the minimum food to level up */
		constexpr double MIN_TO_LEVEL_UP = 1.0;
	}

	namespace GOLD
	{
		constexpr double ZERO = 0.0;
	}
}

namespace CityC
{
	/* Todo : g�n�ralisation : compter nb Citie par player dans CITIENAME.txt */

	/* Nombre de noms de Citie dans CITIENAME.txt */
	constexpr unsigned int MAX_CITY_PER_PLAYER = 5;

	constexpr unsigned int CITY_IHM_SECOND_INDEX = 1;
}


void City::createCity
(
	GamePlayScreen& mainGame,
	const unsigned int influenceLevel
)
{
	const unsigned int selectedPlayer((unsigned int)mainGame.GETPlayers().GETselectedPlayerId());
	PlayerPtrT splayer(mainGame.GETPlayers().GETselectedPlayerPtr());
	const unsigned int selectedUnit((unsigned int)splayer->GETselectedUnit());
	UnitPtrT sUnit(splayer->GETtabUnit()[selectedUnit]);

	/* ---------------------------------------------------------------------- */
	/* 1� : Recherche du nom de la nouvelle Citie 							  */
	/*    : Recherche dans le tableau global des noms de Citie				  */
	/*  : En fonction du nombre de Citie d�j� cr�es et de MAX_CITY_PER_PLAYER */
	/* ---------------------------------------------------------------------- */

	const std::string name(mainGame.GETPlayers().GETvectCityName()
		[
			(size_t)
			(
				((size_t)selectedPlayer * CityC::MAX_CITY_PER_PLAYER)
				+
				splayer->GETtabCity().size()
				)
		]);

	std::vector<Tile> tabtile;
	tabtile.resize(CITY_INFLUENCE::INIT_AREA_VIEW);

	/* ---------------------------------------------------------------------- */
	/* 4� : Remplisage tableau de tile Citie			 					  */
	/* ---------------------------------------------------------------------- */

	fillCitieTiles
	(
		MainMap::convertPosXToIndex(sUnit->GETx()),
		MainMap::convertPosYToIndex(sUnit->GETy()),
		selectedPlayer,
		mainGame.GETmainMap(),
		tabtile,
		influenceLevel
	);

	/* ---------------------------------------------------------------------- */
	/* 5� : Cr�ation d'un ptr et passage au tableau de Citie du joueur		  */
	/*    : Destruction ptr de l'Unit										  */
	/*    : Aucune Unit n'est s�l�ctionn�e et aucune Unit � bouger	 		  */
	/* ---------------------------------------------------------------------- */

	splayer->addCity(name, sUnit->GETx(), sUnit->GETy(), tabtile);

	splayer->deleteUnit(selectedUnit);
	splayer->SETselectedUnit(SELECTION::NO_UNIT_SELECTED);

	mainGame.GETPlayers().SETneedToUpdateDrawUnit(true);
	mainGame.GETPlayers().SETneedToUpdateDrawCity(true);

	splayer.reset();
	sUnit.reset();
}

void City::fillCitieTiles
(
	const unsigned int middletileX,
	const unsigned int middletileY,
	const unsigned int selectplayer,
	MainMap& mainMap,
	VectMap& tabtile,
	const unsigned int influenceLevel
)
{
	unsigned int k(0);
	
	for (int o(-(int)ceil(CITY_INFLUENCE::INIT_SIZE_VIEW / 2)); o <= (int)ceil(CITY_INFLUENCE::INIT_SIZE_VIEW / 2); o++)
	{
		for (int p(-(int)ceil(CITY_INFLUENCE::INIT_SIZE_VIEW / 2)); p <= (int)ceil(CITY_INFLUENCE::INIT_SIZE_VIEW / 2); p++)
		{
			if (initSizeInfluenceCondition(o, p, influenceLevel))
			{
				mainMap.GETmatriceMap()[(unsigned int)((double)middletileX + o)][(unsigned int)((double)middletileY + p)]
					.appartenance = (int)selectplayer;
			}

			tabtile[k] = mainMap.GETmatriceMap()[(unsigned int)((double)middletileX + o)][(unsigned int)((double)middletileY + p)];
			k++;
		}
	}
}

bool City::initSizeInfluenceCondition
(
	const int o,
	const int p,
	const unsigned int influenceLevel
)
{
	if (
		o >= (int16_t)(-(int16_t)CITY_INFLUENCE::MIN_INFLUENCE_LEVEL * (int16_t)influenceLevel)
		&&
		o <= (int16_t)(CITY_INFLUENCE::MIN_INFLUENCE_LEVEL * (int16_t)influenceLevel)
		&&
		p >= (int16_t)(-(int16_t)CITY_INFLUENCE::MIN_INFLUENCE_LEVEL * (int16_t)influenceLevel)
		&&
		p <= (int16_t)(CITY_INFLUENCE::MIN_INFLUENCE_LEVEL * (int16_t)influenceLevel)
		&&
		cornerCheck(o, p, influenceLevel)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool City::cornerCheck
(
	const int o,
	const int p,
	const unsigned int influenceLevel
)
{
	if	(
			(CITY_INFLUENCE::MIN_INFLUENCE_LEVEL < influenceLevel)
			&&
			(std::abs(o) == std::abs(p))
			&&
			(CITY_INFLUENCE::MIN_INFLUENCE_LEVEL * influenceLevel) == (unsigned int)std::abs(o)
		)
	{
		return false;
	}
	return true;
}

bool City::searchCityTile
(
	const unsigned int indexX,
	const unsigned int indexY
)
{
	if	(
			MainMap::convertPosXToIndex(m_x) == indexX 
			&&
			MainMap::convertPosXToIndex(m_y) == indexY
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

City::City()
:
m_image("EMPTY"),
m_name("EMPTY"),
m_x(0),
m_y(0),
m_tile(),
m_influenceLevel(CITY_INFLUENCE::MIN_INFLUENCE_LEVEL),
m_atq(0),
m_def(0),
m_nbstructurebuild(0),
m_conversionToApply(conversionSurplus_Type::No_Conversion),
m_citizenManager(m_tile),
m_foodManager(m_citizenManager),
m_buildManager(m_citizenManager, m_foodManager, m_x, m_y, m_conversionToApply),
m_goldBalance(0.0)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_CITY, logS::DATA::CONSTRUCTOR_CITY,
		saveToOjson().as_string());
}

City::City
(
	const std::string& name,
	unsigned int x,
	unsigned int y,
	VectMap& tiles
)
	: 
	m_image("citie.png"),
	m_name(name),
	m_x(x),
	m_y(y),
	m_tile(tiles),
	m_influenceLevel(CITY_INFLUENCE::MIN_INFLUENCE_LEVEL),
	m_atq(0),
	m_def(0),
	m_nbstructurebuild(0),
	m_conversionToApply(conversionSurplus_Type::No_Conversion),
	m_citizenManager(m_tile),
	m_foodManager(m_citizenManager),
	m_buildManager(m_citizenManager, m_foodManager, m_x, m_y, m_conversionToApply),
	m_goldBalance(0.0)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_CITY, logS::DATA::CONSTRUCTOR_CITY,
		saveToOjson().as_string());
}

City::~City()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_CITY, logS::DATA::DESTRUCTOR_CITY, m_name);
}

void City::computefood
(
	GoldStats& goldStats
)
{
	switch (m_foodManager.updateGetFoodStatus())
	{
	case FoodManagerType::famine:

		if (m_citizenManager.getCitizens().size() > POP::MIN)
		{
			m_citizenManager.removeCitizen();

			m_foodManager.updateFoodStockFromReducePop();
		}
		else
		{
			m_foodManager.emptyFoodStock();
		}

		break;
	case FoodManagerType::surplus:

		m_citizenManager.addCitizen();

		m_foodManager.updateFoodStockFromIncreasePop();

		break;
	case FoodManagerType::neutral:
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
		convertFoodSurplusToGold(m_foodManager.getFoodBalanceForConversion(), goldStats);
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

void City::computeWork
(
	Player& player,
	const VectUnitTemplate& vectUnitTemplate,
	bool* needToUpdateDrawUnit
)
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

		m_buildManager.computeWorkToBuild(player, vectUnitTemplate, needToUpdateDrawUnit);

		break;
	default:

#ifdef _DEBUG
		throw("[ERROR]___: computeWorkToBuild : conversionSurplus_Type::??????");
#endif // _DEBUG

		break;
	case conversionSurplus_Type::WorkToGold:

		/* CASE : work conversion to gold */
		player.addGoldToGoldConversionSurplus
			(
				m_buildManager.getWorkBalance()
				*
				MULTIPLIER::CONVERSION::WORK_TO_GOLD
			);

		break;
	}
}

bool City::testPos
(
	const unsigned int mouse_x,
	const unsigned int mouse_y
)
{
	if (
		m_x == mouse_x
		&&
		m_y == mouse_y
		)
	{
		return true;
	}
	return false;
}

void City::computeGold()
{
	/* Sum gold from citizen */
	m_goldBalance = m_citizenManager.getGoldFromCitizen();
	
	/* Applying Emotion multiplier */
	m_goldBalance *= ((double)m_citizenManager.getEmotion() / EMOTION_RANGE::SCALE_MEAN);
}

void City::addCityGoldToTaxIncome
(
	GoldStats& goldStats
)
{
	goldStats.taxIncome += m_goldBalance;
	m_goldBalance = 0.0;
}

void City::convertFoodSurplusToGold
(
	const double foodSurplus,
	GoldStats& goldStats
)
{
	goldStats.goldConversionSurplus = foodSurplus * MULTIPLIER::CONVERSION::FOOD_TO_GOLD;
}

jsoncons::ojson City::saveToOjson()const
{
	jsoncons::ojson value;
	jsoncons::ojson tiles{ jsoncons::ojson::make_array() };

	for (const auto& tile : m_tile)
	{
		jsoncons::ojson oTile;
		oTile.insert_or_assign("indexX", tile.indexX);
		oTile.insert_or_assign("indexY", tile.indexY);
		oTile.insert_or_assign("tile_x", tile.tile_x);
		oTile.insert_or_assign("tile_y", tile.tile_y);
		oTile.insert_or_assign("tile_ground", static_cast<size_t>(tile.tile_ground));
		oTile.insert_or_assign("tile_spec", static_cast<size_t>(tile.tile_spec));
		oTile.insert_or_assign("appartenance", tile.appartenance);
		oTile.insert_or_assign("food", tile.food);
		oTile.insert_or_assign("work", tile.work);
		oTile.insert_or_assign("gold", tile.gold);
		tiles.push_back(oTile);
	}

	value.insert_or_assign("m_image", m_image);
	value.insert_or_assign("m_name", m_name);
	value.insert_or_assign("m_x", m_x);
	value.insert_or_assign("m_y", m_y);
	value.insert_or_assign("VectMap", tiles);
	value.insert_or_assign("m_influenceLevel", m_influenceLevel);
	value.insert_or_assign("m_atq", m_atq);
	value.insert_or_assign("m_def", m_def);
	value.insert_or_assign("m_nbstructurebuild", m_nbstructurebuild);
	value.insert_or_assign("Citizens", m_citizenManager.saveToOjson());
	value.insert_or_assign("Food", m_foodManager.saveToOjson());
	value.insert_or_assign("BuildQueue", m_buildManager.saveToOjson());
	return value;
}

void City::loadFromOjson(const jsoncons::ojson& jsonLoad)
{
	if	(
			jsonLoad.contains("m_image") && jsonLoad.contains("m_name") && jsonLoad.contains("m_x") &&
			jsonLoad.contains("m_y") && jsonLoad.contains("m_influenceLevel") && jsonLoad.contains("m_atq") &&
			jsonLoad.contains("m_def") && jsonLoad.contains("m_nbstructurebuild") && jsonLoad.contains("Citizens") &&
			jsonLoad.contains("Food") && jsonLoad.contains("BuildQueue") &&
			jsonLoad.contains("VectMap") && jsonLoad["VectMap"].is_array()
		)
	{
		m_image = jsonLoad["m_image"].as_string();
		m_name = jsonLoad["m_name"].as_string();
		m_x = jsonLoad["m_x"].as<unsigned int>();
		m_y = jsonLoad["m_y"].as<unsigned int>();

		const std::vector<jsonloader::Tile> mapTile = jsonLoad["VectMap"].as<std::vector<jsonloader::Tile>>();
		m_tile.resize(mapTile.size());
		size_t loopIndex{ 0 };
		for (const auto& tile : mapTile)
		{
			m_tile[loopIndex].indexX = tile.indexX;
			m_tile[loopIndex].indexY = tile.indexY;
			m_tile[loopIndex].tile_x = tile.tile_x;
			m_tile[loopIndex].tile_y = tile.tile_y;
			m_tile[loopIndex].tile_ground = static_cast<Ground_Type>(tile.tile_ground);
			m_tile[loopIndex].tile_spec = static_cast<GroundSpec_Type>(tile.tile_spec);
			m_tile[loopIndex].appartenance = tile.appartenance;
			m_tile[loopIndex].food = tile.food;
			m_tile[loopIndex].work = tile.work;
			m_tile[loopIndex].gold = tile.gold;
			loopIndex++;
		}

		m_influenceLevel = jsonLoad["m_influenceLevel"].as<unsigned int>();
		m_atq = jsonLoad["m_atq"].as<unsigned int>();
		m_def = jsonLoad["m_def"].as<unsigned int>();
		m_nbstructurebuild = jsonLoad["m_nbstructurebuild"].as<unsigned int>();
	
		m_citizenManager.loadFromOjson(jsonLoad["Citizens"]);
		m_foodManager.loadFromOjson(jsonLoad["Food"]);
		m_buildManager.loadFromOjson(jsonLoad["BuildQueue"]);
	}
}

 /*
 *	End Of File City.cpp
 */