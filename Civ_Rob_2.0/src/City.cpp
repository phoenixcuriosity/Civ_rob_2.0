/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2024 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.12.0
	file version : 1.49

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

#include "City.h"

#include "Utility.h"
#include "Citizen.h"

#include "App.h"
#include <R2D/src/Window.h>
#include <R2D/src/ValueToScale.h>
#include <R2D/src/ErrorLog.h> 

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

 /* *********************************************************
  *					START City::STATIC					   *
  ********************************************************* */

/* ----------------------------------------------------------------------------------- */
/* NAME : createCity																   */
/* ROLE : Cr�ation d'une City � partir d'un settler sur la carte					   */
/* INPUT/OUTPUT : struct Sysinfo& : Global structure								   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
void City::createCity
(
	GamePlayScreen& mainGame,
	const unsigned int influenceLevel
)
{
	const unsigned int selectedPlayer((unsigned int)mainGame.GETPlayers().GETselectedPlayerId());
	std::shared_ptr<Player> splayer(mainGame.GETPlayers().GETselectedPlayerPtr());
	const unsigned int selectedUnit((unsigned int)splayer->GETselectedUnit());
	std::shared_ptr<Unit> sUnit(splayer->GETtabUnit()[selectedUnit]);

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

/* ----------------------------------------------------------------------------------- */
/* NAME : fillCitieTiles															   */
/* ROLE : Rempli le tableau de la Citie avec le point centrale la middletileXY		   */
/* ROLE : et de largeur et hauteur totale INIT_SIZE_VIEW							   */
/* INPUT : const Screen& screen	: taille en x et y de l'�cran						   */
/* INPUT : unsigned int middletileX : index en tileSize de x de la Citie			   */
/* INPUT : unsigned int middletileY : index en tileSize de y de la Citie			   */
/* INPUT : unsigned int selectplayer : index d'appartenance							   */
/* INPUT/OUTPUT : Map& map : structure de la Map									   */
/* OUTPUT : std::vector<Tile>& tabtile : tableau � remplir de la Citie				   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
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

/* ----------------------------------------------------------------------------------- */
/* NAME : initSizeInfluenceCondition												   */
/* ROLE : Conditions des cases de la ville � l'int�rieur de zone d'influence		   */
/* INPUT : int o :	index en x														   */
/* INPUT : int p :	index en y														   */
/* RETURNED VALUE : bool : false -> invalid / true -> valid							   */
/* ----------------------------------------------------------------------------------- */
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

/* ----------------------------------------------------------------------------------- */
/* NAME : cornerCheck																   */
/* ROLE : Conditions des cases de la ville � l'int�rieur de zone d'influence		   */
/* IN : int o :	index en x															   */
/* IN : int p :	index en y															   */
/* IN : unsigned int influenceLevel : City influence level 							   */
/* RETURNED VALUE : bool : false -> this tile is a corner							   */
/* RETURNED VALUE : bool : true -> this tile is not a corner						   */
/* ----------------------------------------------------------------------------------- */
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

/* ----------------------------------------------------------------------------------- */
/* NAME : searchCityTile															   */
/* ROLE : Recherche la case de la City et renvoie vers cityMap						   */
/* INPUT : const std::vector<Player*>& : Vecteur de joueurs							   */
/* INPUT/OUTPUT : Var& : Structure Var												   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
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


/* *********************************************************
 *					END City::STATIC					   *
 ********************************************************* */



 /* *********************************************************
  *					START City::METHODS					   *
  ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* NAME : City																		   */
/* ROLE : Constructeur complet														   */
/* INPUT : const std::string &	: name de la Citie									   */
/* INPUT : unsigned int x : index en x												   */
/* INPUT : unsigned int y : index en y												   */
/* INPUT : Tile tile[] : tableau de tile de la Citie								   */
/* ----------------------------------------------------------------------------------- */
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

/* ----------------------------------------------------------------------------------- */
/* NAME : ~City																		   */
/* ROLE : Destructeur																   */
/* INPUT : void																		   */
/* ----------------------------------------------------------------------------------- */
City::~City()
{
	R2D::ErrorLog::logEvent("[INFO]___: Destroy Citie: " + m_name + " Success");
}

/* ----------------------------------------------------------------------------------- */
/* NAME : foodNextTurn																   */
/* ROLE : Calcul et application du niveau de Food pour le prochain tour				   */
/* OUT : GoldStats& goldStats : Player gold stats									   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void City::foodNextTurn
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

/* ----------------------------------------------------------------------------------- */
/* NAME : testPos																	   */
/* ROLE : Retourne si la position est valide										   */
/* INPUT : unsigned int x : position de la souris en x								   */
/* INPUT : unsigned int y : position de la souris en y								   */
/* RETURNED VALUE : bool : false : invalid / true : valid							   */
/* ----------------------------------------------------------------------------------- */
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

/* ----------------------------------------------------------------------------------- */
/* NAME : computeGold																   */
/* ROLE : Calculate the gold for the turn											   */
/* INPUT : void																		   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void City::computeGold()
{
	/* Sum gold from citizen */
	m_goldBalance = m_citizenManager.getGoldFromCitizen();
	
	/* Applying Emotion multiplier */
	m_goldBalance *= ((double)m_citizenManager.getEmotion() / EMOTION_RANGE::SCALE_MEAN);
}

/* ----------------------------------------------------------------------------------- */
/* NAME : addCityGoldToTaxIncome													   */
/* ROLE : Add m_goldBalance to a player taxIncome 									   */
/* OUT : GoldStats& goldStats : struct of player gold								   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void City::addCityGoldToTaxIncome
(
	GoldStats& goldStats
)
{
	goldStats.taxIncome += m_goldBalance;
	m_goldBalance = 0.0;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : convertFoodSurplusToGold													   */
/* ROLE : Convert food to gold ; Place in goldStats.goldConversionSurplus			   */
/* INPUT : double workSurplus : food surplus to convert into work					   */
/* OUT : GoldStats& goldStats : gold surplus conversion								   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void City::convertFoodSurplusToGold
(
	const double foodSurplus,
	GoldStats& goldStats
)
{
	goldStats.goldConversionSurplus = foodSurplus * MULTIPLIER::CONVERSION::FOOD_TO_GOLD;
}


/* *********************************************************
 *					END City::METHODS					   *
 ********************************************************* */


 /*
 *	End Of File City.cpp
 */