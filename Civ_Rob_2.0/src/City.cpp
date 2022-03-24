/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.1.0
	file version : 1.38

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
#include <RealEngine2D/src/Window.h>

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
	unsigned int influenceLevel
)
{
	if (mainGame.GETPlayers().GETselectedPlayerId() != NO_PLAYER_SELECTED)
	{
		unsigned int selectedPlayer((unsigned int)mainGame.GETPlayers().GETselectedPlayerId());
		std::shared_ptr<Player> splayer(mainGame.GETPlayers().GETselectedPlayerPtr());
		unsigned int selectedUnit((unsigned int)splayer->GETselectedUnit());
		std::shared_ptr<Unit> sUnit(splayer->GETtabUnit()[selectedUnit]);

		if (sUnit->GETname().compare("settler") == IDENTICAL_STRINGS)
		{
			/* ---------------------------------------------------------------------- */
			/* 1� : Recherche du nom de la nouvelle Citie 							  */
			/*    : Recherche dans le tableau global des noms de Citie				  */
			/*  : En fonction du nombre de Citie d�j� cr�es et de MAX_CITY_PER_PLAYER */
			/* ---------------------------------------------------------------------- */

			std::string name(mainGame.GETPlayers().GETvectCityName()
				[
					(size_t)
					(
						((size_t)selectedPlayer * MAX_CITY_PER_PLAYER)
						+
						splayer->GETtabCity().size()
						)
				]);

			/* ---------------------------------------------------------------------- */
			/* 2� : Recherche du position de la nouvelle Citie = position settler 	  */
			/* ---------------------------------------------------------------------- */

			unsigned int x(sUnit->GETx());
			unsigned int y(sUnit->GETy());

			/* ---------------------------------------------------------------------- */
			/* 3� : Recherche de la tile ou se trouve le settler 					  */
			/* ---------------------------------------------------------------------- */

			unsigned int middletileX(0), middletileY(0);
			middletileX = MainMap::convertPosXToIndex(x);
			middletileY = MainMap::convertPosYToIndex(y);

			std::vector<Tile> tabtile;
			tabtile.resize(INIT_SIZE_VIEW * INIT_SIZE_VIEW);

			/* ---------------------------------------------------------------------- */
			/* 4� : Remplisage tableau de tile Citie			 					  */
			/* ---------------------------------------------------------------------- */

			fillCitieTiles
			(
				mainGame.getParentWindow(),
				middletileX,
				middletileY,
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

			splayer->addCity(name, x, y, tabtile);

			splayer->deleteUnit(selectedUnit);
			splayer->SETselectedUnit(NO_UNIT_SELECTED);

			mainGame.GETPlayers().SETneedToUpdateDrawUnit(true);
			mainGame.GETPlayers().SETneedToUpdateDrawCity(true);
		}
		else
		{
			/* N/A */
		}
		splayer.reset();
		sUnit.reset();
	}
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
	const RealEngine2D::Window& window,
	unsigned int middletileX,
	unsigned int middletileY,
	unsigned int selectplayer,
	MainMap& mainMap,
	VectMap& tabtile,
	unsigned int influenceLevel
)
{
	unsigned int k(0);
	
	for (int o(-(int)ceil(INIT_SIZE_VIEW / 2)); o <= (int)ceil(INIT_SIZE_VIEW / 2); o++)
	{
		for (int p(-(int)ceil(INIT_SIZE_VIEW / 2)); p <= (int)ceil(INIT_SIZE_VIEW / 2); p++)
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
			tabtile[k].tile_x = (window.GETscreenWidth() / 2) - (-o * mainMap.GETtileSize()) - mainMap.GETtileSize() / 2;
			tabtile[k].tile_y = (window.GETscreenHeight() / 2) - (-p * mainMap.GETtileSize()) - mainMap.GETtileSize() / 2;
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
	int o,
	int p,
	unsigned int influenceLevel
)
{
	if (
		o >= (int16_t)(-(int16_t)MIN_INFLUENCE_LEVEL * (int16_t)influenceLevel)
		&&
		o <= (int16_t)(MIN_INFLUENCE_LEVEL * (int16_t)influenceLevel)
		&&
		p >= (int16_t)(-(int16_t)MIN_INFLUENCE_LEVEL * (int16_t)influenceLevel)
		&&
		p <= (int16_t)(MIN_INFLUENCE_LEVEL * (int16_t)influenceLevel)
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
	int o,
	int p,
	unsigned int influenceLevel
)
{
	if (
		MIN_INFLUENCE_LEVEL < influenceLevel
		&&
		std::abs(o) == std::abs(p)
		&&
		(MIN_INFLUENCE_LEVEL * influenceLevel) == (unsigned int)std::abs(o)
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
	unsigned int indexX,
	unsigned int indexY
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
	m_citizens(),
	m_influenceLevel(MIN_INFLUENCE_LEVEL),
	m_nbpop(MIN_POP),
	m_atq(0),
	m_def(0),
	m_emotion((unsigned int)MEAN_EMOTION),
	m_nbstructurebuild(0),
	m_foodStock(CITY_ZERO_FOOD),
	m_foodBalance(tiles[(unsigned int)ceil((INIT_SIZE_VIEW * INIT_SIZE_VIEW) / 2)].food),
	m_foodSurplusPreviousTurn(CITY_ZERO_FOOD),
	m_workBalance(0),
	m_workSurplusPreviousTurn(0),
	m_goldBalance(0.0),
	m_conversionToApply(conversionSurplus_Type::No_Conversion),
	m_buildQueue()
{
	/* Add initial citizen in the middle case */
	m_citizens.push_back
	(
		std::make_unique<Citizen>
		(tiles[(unsigned int)ceil((INIT_SIZE_VIEW * INIT_SIZE_VIEW) / 2)])
	);

	App::logfileconsole("[INFO]___: Create Citie: " + m_name + " Success");
}

/* ----------------------------------------------------------------------------------- */
/* NAME : ~City																		   */
/* ROLE : Destructeur																   */
/* INPUT : void																		   */
/* ----------------------------------------------------------------------------------- */
City::~City()
{
	resetTabCitizen();

	App::logfileconsole("[INFO]___: Destroy Citie: " + m_name + " Success");
}

/* ----------------------------------------------------------------------------------- */
/* NAME : resetTabCitizen															   */
/* ROLE : Remove all Citizens in the City											   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void City::resetTabCitizen()
{
	for (auto& n : m_citizens)
	{
		n.reset();
	}
	m_citizens.clear();
	m_citizens.resize(0);
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
	double foodLimitPerLevelCurrent(15 + ((double)m_nbpop - 1) * 6 + pow((m_nbpop - 1), 1.8));
	double foodLimitPerLevelMinusOne(15 + ((double)m_nbpop - 1 - 1) * 6 + pow((m_nbpop - 1 - 1), 1.8));

	/* Update m_foodStock : add m_foodBalance */
	m_foodStock += m_foodBalance;

	/* Processing m_foodStock */
	if (CITY_ZERO_FOOD > m_foodStock)
	{
		/* CASE Decreasing : Need to delete a Citizen */

		if (m_citizens.size() == MIN_POP)
		{
			/* 1 POP */
			m_foodStock = CITY_ZERO_FOOD;
		}
		else
		{
			/* 2 or more POP */

			/* Priority check Citizen delete */

			double minValueTile{ 999.9 }, curV{0.0};
			int selectedCitizen{ -1 };
			for (size_t c(0); c < m_citizens.size(); c++)
			{
				if (m_citizens[c]->GETplace() && ((curV = tileValue(m_tile[m_citizens[c]->GETtileOccupied()])) < minValueTile))
				{
					minValueTile = curV;
					selectedCitizen = (int)c;
				}
			}

			/* Delete Citizen */

			m_citizens[selectedCitizen].reset();
			m_citizens.erase(m_citizens.begin() + selectedCitizen);
			m_nbpop--;


			m_foodStock = foodLimitPerLevelMinusOne;
		}
	}
	else if (m_foodStock >= foodLimitPerLevelCurrent)
	{
		/* CASE Increasing : Need to add a Citizen */

		m_nbpop++;

		m_citizens.push_back(std::make_unique<Citizen>(m_tile, m_citizens));
		m_foodStock -= foodLimitPerLevelCurrent;
	}
	else
	{
		/* ---------------------------------------------------------------------- */
		/* Entre 0 et foodLimitPerLevelCurrent									  */
		/* ---------------------------------------------------------------------- */
		/* N/A */
	}

	double emotionOnFoodModifier((double)m_emotion / SCALE_RANGE_MEAN_EMOTION);
	double consumptionFoodCity(2.0 * ((double)m_nbpop - 1.0));
	double sommeFoodCitizen(CITY_ZERO_FOOD);

	for (auto& c : m_citizens)
	{
		sommeFoodCitizen += c->GETfood();
	}

	/* Applying Emotion multiplier */
	sommeFoodCitizen *= emotionOnFoodModifier;

	m_foodBalance = m_foodSurplusPreviousTurn + sommeFoodCitizen - consumptionFoodCity;
	m_foodSurplusPreviousTurn = CITY_ZERO_FOOD;

	if (m_foodBalance > CITY_ZERO_FOOD)
	{
		switch (m_conversionToApply)
		{
		case conversionSurplus_Type::No_Conversion:
			/* N/A */
			break;
		case conversionSurplus_Type::FoodToWork:
			convertFoodSurplusToWork(m_foodBalance);
			m_foodBalance = 0.0;
			break;
		case conversionSurplus_Type::FoodToGold:
			convertFoodSurplusToGold(m_foodBalance, goldStats);
			m_foodBalance = 0.0;
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
}

double City::tileValue
(
	const Tile& tile,
	double coefFood,
	double coefWork,
	double coefGold
)const
{
	double sum{ 0.0 };
	sum = tile.food * coefFood + tile.gold * coefGold + tile.work * coefWork;
	return sum;
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
	unsigned int mouse_x,
	unsigned int mouse_y
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
/* NAME : computeEmotion															   */
/* ROLE : Calcul sur une echelle de 0 � 100 le bonheur de la Citie					   */
/* INPUT : void																		   */
/* INTERNAL OUTPUT : m_emotion : bonheur de la Citie									   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void City::computeEmotion()
{
	double result{0.0};

	for (auto& c : m_citizens)
	{
		result += (double)c->GEThappiness();
	}
	
	try
	{
		m_emotion = (unsigned int)Utility::computeValueToScale
		(
			result,
			(double)Emotion_Type::angry,
			(double)Emotion_Type::ecstatic,
			SCALE_RANGE_MIN_EMOTION,
			SCALE_RANGE_MAX_EMOTION,
			(int)m_citizens.size()
		);
	}
	catch (std::string const& msg)
	{
		if (msg.compare("[ERROR]___: protectedDiv: div by 0") == IDENTICAL_STRINGS)
		{
			App::logfileconsole(msg);
			m_emotion = (unsigned int)SCALE_RANGE_MEAN_EMOTION;
#ifdef _DEBUG
			throw(msg);
#endif // _DEBUG
		}
		else if (msg.compare("[ERROR]___: computeValueToScale : checkMinMaxValidityRange") == IDENTICAL_STRINGS)
		{
			App::logfileconsole(msg);
			m_emotion = (unsigned int)SCALE_RANGE_MEAN_EMOTION;
#ifdef _DEBUG
			throw(msg);
#endif // _DEBUG
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME : computeWork																   */
/* ROLE : Calculate the work for the turn											   */
/* INPUT : void																		   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void City::computeWork()
{
	/* Reset m_workBalance to CITY_ZERO */
	m_workBalance = CITY_ZERO;

	/* Sum work from citizen */
	for (const auto& c : m_citizens)
	{
		m_workBalance += (double)c->GETwork();
	}

	/* Applying Emotion multiplier */
	m_workBalance *= ((double)m_emotion / SCALE_RANGE_MEAN_EMOTION);

	/* Applying the work which was converted from food in the previous turn */
	m_workBalance += m_workSurplusPreviousTurn;

	/* Reset m_workSurplusPreviousTurn to CITY_ZERO */
	m_workSurplusPreviousTurn = CITY_ZERO;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : computeWorkToBuild														   */
/* ROLE : Compute the remaining work to build a building or unit					   */
/* ROLE : if the remaining work is zero then the building or unit is created		   */
/* ROLE : if the build is created and there work Surplus then either apply it ...	   */
/* ROLE : ... to next build or convert it to food									   */
/* OUT : Player* : ptr to the selected player										   */
/* INPUT : std::vector<Unit_Template>& : vector of Units template					   */
/* IN/OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void City::computeWorkToBuild
(
	Player& player,
	const VectUnitTemplate& vectUnitTemplate,
	bool* needToUpdateDrawUnit
)
{
	switch (m_conversionToApply)
	{
	case conversionSurplus_Type::No_Conversion:
	case conversionSurplus_Type::FoodToWork:
	case conversionSurplus_Type::FoodToGold:
	case conversionSurplus_Type::WorkToFood:
	case conversionSurplus_Type::GoldToFood:
	case conversionSurplus_Type::GoldToWork:

		/* CASE : work to build */
		if (!m_buildQueue.empty())
		{
			/* Decrease by m_workBalance the amont of the remainingWork to build */
			m_buildQueue.front().buildQ.remainingWork -= m_workBalance;

			double workSurplus(0.0);
			while (m_buildQueue.front().buildQ.remainingWork < 0.0)
			{
				switch (m_buildQueue.front().buildQ.type)
				{
				case build_Type::unit:
				{
					unsigned int unitToBuild(Unit::searchUnitByName(m_buildQueue.front().buildQ.name, vectUnitTemplate));

					player.addUnit
					(
						m_buildQueue.front().buildQ.name,
						m_x,
						m_y,
						vectUnitTemplate[unitToBuild].type,
						vectUnitTemplate[unitToBuild].life,
						vectUnitTemplate[unitToBuild].atq,
						vectUnitTemplate[unitToBuild].def,
						vectUnitTemplate[unitToBuild].movement,
						vectUnitTemplate[unitToBuild].level,
						vectUnitTemplate[unitToBuild].maintenance
					);
					*needToUpdateDrawUnit = true;

					break;
				}
				case build_Type::building:

					/* TODO */

					break;
				default:
#ifdef _DEBUG
					throw("[ERROR]___: computeWorkToBuild : m_buildQueue.front().type == else");
#endif // _DEBUG
					break;
				}

				workSurplus = -m_buildQueue.front().buildQ.remainingWork;

				removeBuildToQueueFront();

				if (!m_buildQueue.empty())
				{
					m_buildQueue.front().buildQ.remainingWork -= workSurplus;
				}
				else
				{
					convertWorkSurplusToFood(workSurplus);
					return;
				}
			}
		}
		break;
	default:

#ifdef _DEBUG
		throw("[ERROR]___: computeWorkToBuild : conversionSurplus_Type::??????");
#endif // _DEBUG

		break;
	case conversionSurplus_Type::WorkToGold:

		/* CASE : work conversion to gold */
		player.addGoldToGoldConversionSurplus(m_workBalance * MULTIPLIER_CONVERSION_WORK_TO_GOLD);

		break;
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME : computeGold																   */
/* ROLE : Calculate the gold for the turn											   */
/* INPUT : void																		   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void City::computeGold()
{
	/* Reset m_goldBalance to CITY_ZERO */
	m_goldBalance = CITY_ZERO;

	/* Sum gold from citizen */
	for (auto& c : m_citizens)
	{
		m_goldBalance += (double)c->GETwork();
	}
	
	/* Applying Emotion multiplier */
	m_goldBalance *= ((double)m_emotion / SCALE_RANGE_MEAN_EMOTION);
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
/* NAME : convertWorkSurplusToFood													   */
/* ROLE : Convert work to food ; Place in m_foodSurplusPreviousTurn					   */
/* INPUT : double workSurplus : work surplus to convert into food					   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void City::convertWorkSurplusToFood
(
	double workSurplus
)
{
	m_foodSurplusPreviousTurn = workSurplus * MULTIPLIER_CONVERSION_WORK_TO_FOOD;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : convertWorkSurplusToFood													   */
/* ROLE : Convert food to work ; Place in m_workSurplusPreviousTurn					   */
/* INPUT : double workSurplus : food surplus to convert into work					   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void City::convertFoodSurplusToWork
(
	double foodSurplus
)
{
	m_workSurplusPreviousTurn = foodSurplus * MULTIPLIER_CONVERSION_FOOD_TO_WORK;
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
	double foodSurplus,
	GoldStats& goldStats
)
{
	goldStats.goldConversionSurplus = foodSurplus * MULTIPLIER_CONVERSION_FOOD_TO_GOLD;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : addBuildToQueue															   */
/* ROLE : Push build to buildQueue													   */
/* IN : build buildToQueue : build to push into buildQueue							   */
/* OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
/* INPUT : SDL_Renderer*& renderer : ptr SDL_renderer								   */
/* INPUT : TTF_Font* font[] : array of SDL font										   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void City::addBuildToQueue
(
	const buildGUI& buildToQueue
)
{
	m_buildQueue.push_back(buildToQueue);
}

/* ----------------------------------------------------------------------------------- */
/* NAME : removeBuildToQueueFront													   */
/* ROLE : Pop build to buildQueue													   */
/* IN/OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void City::removeBuildToQueueFront()
{
	if (m_buildQueue.front().buildG != nullptr)
	{
		m_buildQueue.front().buildG->destroy();
		m_buildQueue.front().buildG = nullptr;
	}
	m_buildQueue.pop_front();
}

/* ----------------------------------------------------------------------------------- */
/* NAME : removeBuildToQueue														   */
/* ROLE : remove build to buildQueue at index										   */
/* IN/OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
/* IN : unsigned int index : index to remove										   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void City::removeBuildToQueue
(
	size_t index
)
{
	if (m_buildQueue[index].buildG != nullptr)
	{
		m_buildQueue[index].buildG->destroy();
		m_buildQueue[index].buildG = nullptr;
	}
	m_buildQueue.erase(m_buildQueue.begin() + index);
}

/* *********************************************************
 *					END City::METHODS					   *
 ********************************************************* */


 /*
 *	End Of File City.cpp
 */