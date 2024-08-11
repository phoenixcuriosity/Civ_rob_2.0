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
#include "Player.h"
#include "Players.h"
#include "Unit.h"
#include "Utility.h"

#include <R2D/src/ErrorLog.h> 
#include <R2D/src/ValueToScale.h>
#include <R2D/src/Window.h>

namespace POP
{
	/* Population maximale dans une Citie */
	const unsigned int MAX = 50;

	/* Minimal population in City */
	const unsigned int MIN = 1;
}

namespace RESOURCES
{
	namespace FOOD
	{
		/* Define the minimum food in a City */
		const double ZERO = 0.0;

		/* Define the minimum food to level up */
		const double MIN_TO_LEVEL_UP = 1.0;
	}

	namespace GOLD
	{
		const double ZERO = 0.0;
	}
}

namespace CityC
{
	/* Todo : g�n�ralisation : compter nb Citie par player dans CITIENAME.txt */

	/* Nombre de noms de Citie dans CITIENAME.txt */
	const unsigned int MAX_CITY_PER_PLAYER = 5;

	const unsigned int CITY_IHM_SECOND_INDEX = 1;
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
		mainGame.getParentWindow(),
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
	const R2D::Window& window,
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
				mainMap.GETmatriceMap()[(unsigned int)((double)middletileX + o)]
					[(unsigned int)((double)middletileY + p)]
				.appartenance = (int)selectplayer;
			}
			else
			{
				/* N/A */
			}

			/* ---------------------------------------------------------------------- */
			/* Remplissage du tableau de Tile								 		  */
			/* ---------------------------------------------------------------------- */
			tabtile[k] = mainMap.GETmatriceMap()
				[(unsigned int)((double)middletileX + o)]
			[(unsigned int)((double)middletileY + p)];
			tabtile[k].tileXCityScreen = (window.GETscreenWidth() / 2) - (-o * mainMap.GETtileSize()) - mainMap.GETtileSize() / 2;
			tabtile[k].tileYCityScreen = (window.GETscreenHeight() / 2) - (-p * mainMap.GETtileSize()) - mainMap.GETtileSize() / 2;
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
	R2D::ErrorLog::logEvent("[INFO]___: Create Citie: " + m_name + " Success");
}

City::~City()
{
	R2D::ErrorLog::logEvent("[INFO]___: Destroy Citie: " + m_name + " Success");
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

 /*
 *	End Of File City.cpp
 */