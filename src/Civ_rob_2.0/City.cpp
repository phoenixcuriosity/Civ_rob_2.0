/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.22.2.1
	file version : 1.26

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

#include "ConstCityIHM.h"

#include "IHM.h"
#include "LoadConfig.h"
#include "civ_lib.h"
#include "Citizen.h"
#include "Utility.h"
#include "Texture.h"

/* *********************************************************
 *					START City::STATIC					   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : createCity																   */
/* ROLE : Création d'une City à partir d'un settler sur la carte					   */
/* INPUT/OUTPUT : struct Sysinfo& : Global structure								   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::createCity
(
	Sysinfo& sysinfo,
	unsigned int influenceLevel
)
{
	if (sysinfo.var.s_player.unitNameToMove.compare("settler") == IDENTICAL_STRINGS)
	{
		/* ---------------------------------------------------------------------- */
		/* 1° : Recherche du nom de la nouvelle Citie 							  */
		/*    : Recherche dans le tableau global des noms de Citie				  */
		/*  : En fonction du nombre de Citie déjà crées et de MAX_CITY_PER_PLAYER */
		/* ---------------------------------------------------------------------- */

		std::string name(sysinfo.var.s_player.tabCitiesName
			[
				(unsigned __int64)
				(
					((unsigned __int64)sysinfo.var.s_player.selectplayer * MAX_CITY_PER_PLAYER)
					+ sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
						->GETtabCity().size()
				)
			]);

		/* ---------------------------------------------------------------------- */
		/* 2° : Recherche du position de la nouvelle Citie = position settler 	  */
		/* ---------------------------------------------------------------------- */

		unsigned int x(sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
						->GETtheUnit(sysinfo.var.s_player.selectunit)
							->GETx());
		unsigned int y(sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
						->GETtheUnit(sysinfo.var.s_player.selectunit)
							->GETy());

		/* ---------------------------------------------------------------------- */
		/* 3° : Recherche de la tile ou se trouve le settler 					  */
		/* ---------------------------------------------------------------------- */

		unsigned int middletileX(0), middletileY(0);
		middletileX = GamePlay::convertPosXToIndex(x);
		middletileY = GamePlay::convertPosYToIndex(y);

		std::vector<Tile> tabtile;
		tabtile.resize(INIT_SIZE_VIEW * INIT_SIZE_VIEW);

		/* ---------------------------------------------------------------------- */
		/* 4° : Remplisage tableau de tile Citie			 					  */
		/* ---------------------------------------------------------------------- */

		fillCitieTiles
					(
						sysinfo.screen,
						middletileX,
						middletileY,
						sysinfo.var.s_player.selectplayer,
						sysinfo.map,
						tabtile,
						influenceLevel
					);

		/* ---------------------------------------------------------------------- */
		/* 5° : Création d'un ptr et passage au tableau de Citie du joueur		  */
		/*    : Destruction ptr de l'Unit										  */
		/*    : Aucune Unit n'est séléctionnée et aucune Unit à bouger	 		  */
		/* ---------------------------------------------------------------------- */

		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
			->addCity(name, x, y, tabtile);

		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
			->deleteUnit(sysinfo.var.s_player.selectunit);
		sysinfo.var.s_player.selectunit = NO_UNIT_SELECTED;
		sysinfo.var.s_player.unitNameToMove = EMPTY_STRING;
	}
	else
	{
		/* N/A */
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : fillCitieTiles															   */
/* ROLE : Rempli le tableau de la Citie avec le point centrale la middletileXY		   */
/* ROLE : et de largeur et hauteur totale INIT_SIZE_VIEW							   */
/* INPUT : const Screen& screen	: taille en x et y de l'écran						   */
/* INPUT : unsigned int middletileX : index en tileSize de x de la Citie			   */
/* INPUT : unsigned int middletileY : index en tileSize de y de la Citie			   */
/* INPUT : unsigned int selectplayer : index d'appartenance							   */
/* INPUT/OUTPUT : Map& map : structure de la Map									   */
/* OUTPUT : std::vector<Tile>& tabtile : tableau à remplir de la Citie				   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::fillCitieTiles
(
	const Screen& screen,
	unsigned int middletileX,
	unsigned int middletileY,
	unsigned int selectplayer,
	Map& map,
	std::vector<Tile>& tabtile,
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
				map.maps[(unsigned int)((double)middletileX + o)]
						[(unsigned int)((double)middletileY + p)]
						.appartenance = selectplayer;
			}
			else
			{
				/* N/A */
			}

			/* ---------------------------------------------------------------------- */
			/* Remplissage du tableau de Tile								 		  */
			/* ---------------------------------------------------------------------- */
			tabtile[k] = map.maps
							[(unsigned int)((double)middletileX + o)]
							[(unsigned int)((double)middletileY + p)];
			tabtile[k].tile_x = (screen.screenWidth / 2) - (-o * map.tileSize);
			tabtile[k].tile_y = (screen.screenHeight / 2) - (-p * map.tileSize);
			k++;
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initSizeInfluenceCondition												   */
/* ROLE : Conditions des cases de la ville à l'intérieur de zone d'influence		   */
/* INPUT : int o :	index en x														   */
/* INPUT : int p :	index en y														   */
/* RETURNED VALUE : bool : false -> invalid / true -> valid							   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool City::initSizeInfluenceCondition
(
	int o,
	int p,
	unsigned int influenceLevel
)
{
	if	(
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
/* ----------------------------------------------------------------------------------- */
/* NAME : cornerCheck																   */
/* ROLE : Conditions des cases de la ville à l'intérieur de zone d'influence		   */
/* IN : int o :	index en x															   */
/* IN : int p :	index en y															   */
/* IN : unsigned int influenceLevel : City influence level 							   */
/* RETURNED VALUE : bool : false -> this tile is a corner							   */
/* RETURNED VALUE : bool : true -> this tile is not a corner						   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool City::cornerCheck
(
	int o,
	int p,
	unsigned int influenceLevel
)
{
	if	(
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
/* ----------------------------------------------------------------------------------- */
/* NAME : searchCityTile															   */
/* ROLE : Recherche la case de la City et renvoie vers cityMap						   */
/* INPUT : const std::vector<Player*>& : Vecteur de joueurs							   */
/* INPUT/OUTPUT : Var& : Structure Var												   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::searchCityTile
(
	const std::vector<Player*>& tabplayer,
	Var& var
)
{
	
	for (unsigned int i(0); i < tabplayer[var.s_player.selectplayer]->GETtabCity().size(); i++)
	{
		if	(
				tabplayer[var.s_player.selectplayer]
					->GETtheCity(i)
						->testPos
							(var.mouse.GETmouse_xNormalized(), var.mouse.GETmouse_yNormalized())
			)
		{
			var.s_player.selectCity = i;
			var.statescreen = State_Type::STATEcityMap;
			var.select = Select_Type::selectnothing;
			return;
		}
		else
		{
			/* N/A */
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : resizeUnitTextureCity														   */
/* ROLE : Resize all Textures in Unit depends on resizeUnitTexture_Type				   */
/* OUTPUT : MapTexture& unit : Unit vector to resize								   */
/* INPUT : unsigned int tileSize : size for unit in case of mainmap					   */
/* INPUT : resizeUnitTexture_Type type : type to resize the Texture					   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::resizeUnitTextureCity
(
	MapTexture& unit,
	unsigned int tileSize,
	resizeUnitTexture_Type type
)
{
	for (const auto& n : unit)
	{
		switch (type)
		{
		case resizeUnitTexture_Type::mainmap:
			n.second->resizeLl(tileSize, tileSize);
			break;
		case resizeUnitTexture_Type::city:
			n.second->resizeLl(CITY_BUILDS_SPACE_Y, CITY_BUILDS_SPACE_Y);
			break;
		}
	}
}


/* *********************************************************
 *					END City::STATIC					   *
 ********************************************************* */


 
/* *********************************************************
 *					START City::METHODS					   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : City																		   */
/* ROLE : Constructeur complet														   */
/* INPUT : const std::string &	: name de la Citie									   */
/* INPUT : unsigned int x : index en x												   */
/* INPUT : unsigned int y : index en y												   */
/* INPUT : Tile tile[] : tableau de tile de la Citie								   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
City::City
(
	const std::string& name,
	unsigned int x,
	unsigned int y,
	std::vector<Tile>& tiles
)
	: _image("citie.png"),
_name(name), _x(x), _y(y), _tile(tiles),
_influenceLevel(2),_nbpop(MIN_POP), _atq(0), _def(0), _emotion((unsigned int)MEAN_EMOTION), _nbstructurebuild(0),
_foodStock(CITY_ZERO_FOOD), _foodBalance(tiles[(unsigned int)ceil((INIT_SIZE_VIEW*INIT_SIZE_VIEW) / 2)].food),
_foodSurplusPreviousTurn(CITY_ZERO_FOOD), _workBalance(0), _workSurplusPreviousTurn(0), _goldBalance(0.0),
_conversionToApply(conversionSurplus_Type::No_Conversion)
{
	_citizens.push_back(new Citizen(tiles[(unsigned int)ceil((INIT_SIZE_VIEW * INIT_SIZE_VIEW) / 2)]));

	LoadConfig::logfileconsole("[INFO]___: Create Citie: " + _name + " Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : ~City																		   */
/* ROLE : Destructeur																   */
/* INPUT : void																		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
City::~City()
{
	resetTabCitizen();

	for (unsigned int i(0); i <_buildQueue.cityMapBuildQueue.size(); i++)
	{
		removeBuildToQueue(i);
	}
	
	LoadConfig::logfileconsole("[INFO]___: Destroy Citie: " + _name + " Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : resetTabCitizen															   */
/* ROLE : Remove all Citizens in the City											   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::resetTabCitizen()
{
	for (const auto& n : _citizens)
	{
		if (nullptr != n)
		{
			delete n;
		}
	}
	_citizens.resize(0);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : foodNextTurn																   */
/* ROLE : Calcul et application du niveau de Food pour le prochain tour				   */
/* OUT : GoldStats& goldStats : Player gold stats									   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::foodNextTurn
(
	GoldStats& goldStats
)
{
	double foodLimitPerLevelCurrent(15 + ((double)_nbpop - 1) * 6 + pow((_nbpop - 1), 1.8));
	double foodLimitPerLevelMinusOne(15 + ((double)_nbpop - 1 - 1) * 6 + pow((_nbpop - 1 - 1), 1.8));

	_foodStock += _foodBalance;
	
	if (CITY_ZERO_FOOD > _foodStock)
	{
		if (_citizens.size() == MIN_POP)
		{
			_foodStock = CITY_ZERO_FOOD;
		}
		else
		{
			/* ---------------------------------------------------------------------- */
			/* TODO gestion prioritaire de suppression de Citizen					  */
			/* ---------------------------------------------------------------------- */
			_nbpop--;
			if (nullptr != _citizens[_citizens.size() - 1])
			{
				delete _citizens[_citizens.size() - 1];
			}
			else
			{
				/* TODO Throw error */
			}
			_citizens.pop_back();
			_foodStock = foodLimitPerLevelMinusOne;
		}
	}
	else if (_foodStock >= foodLimitPerLevelCurrent)
	{
		_nbpop++;
		
		_citizens.push_back(new Citizen(_tile, _citizens));
		_foodStock -= foodLimitPerLevelCurrent;
	}
	else
	{
		/* ---------------------------------------------------------------------- */
		/* Entre 0 et foodLimitPerLevelCurrent									  */
		/* ---------------------------------------------------------------------- */
		/* N/A */
	}

	double emotionOnFoodModifier((double)_emotion / SCALE_RANGE_MEAN_EMOTION);
	double consumptionFoodCity(2.0 * ((double)_nbpop - 1.0));
	double sommeFoodCitizen(0);

	for (unsigned int i(0); i < _citizens.size(); i++)
	{
		sommeFoodCitizen += _citizens[i]->GETfood();
	}

	/* Applying Emotion multiplier */
	sommeFoodCitizen *= emotionOnFoodModifier;

	_foodBalance = _foodSurplusPreviousTurn + sommeFoodCitizen - consumptionFoodCity;
	_foodSurplusPreviousTurn = 0.0;

	if (_foodBalance > 0.0)
	{
		switch (_conversionToApply)
		{
		case conversionSurplus_Type::No_Conversion:
			/* N/A */
			break;
		case conversionSurplus_Type::FoodToWork:
			convertFoodSurplusToWork(_foodBalance);
			_foodBalance = 0.0;
			break;
		case conversionSurplus_Type::FoodToGold:
			convertFoodSurplusToGold(_foodBalance, goldStats);
			_foodBalance = 0.0;
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

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : testPos																	   */
/* ROLE : Retourne si la position est valide										   */
/* INPUT : unsigned int x : position de la souris en x								   */
/* INPUT : unsigned int y : position de la souris en y								   */
/* RETURNED VALUE : bool : false : invalid / true : valid							   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool City::testPos
(
	unsigned int mouse_x,
	unsigned int mouse_y
)
{
	if	(
			_x == mouse_x
			&&
			_y == mouse_y
		)
	{
		return true;
	}	
	return false;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : computeEmotion															   */
/* ROLE : Calcul sur une echelle de 0 à 100 le bonheur de la Citie					   */
/* INPUT : void																		   */
/* INTERNAL OUTPUT : _emotion : bonheur de la Citie									   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::computeEmotion()
{
	double result(0);

	for (unsigned int nbCitizen(0); nbCitizen < _citizens.size(); nbCitizen++)
	{
		result += (double)_citizens[nbCitizen]->GEThappiness();
	}

	try
	{
		_emotion = (unsigned int)Utility::computeValueToScale
		(
			result,
			(double)Emotion_Type::angry,
			(double)Emotion_Type::ecstatic,
			SCALE_RANGE_MIN_EMOTION,
			SCALE_RANGE_MAX_EMOTION,
			(int)_citizens.size()
		);
	}
	catch (std::string const& msg)
	{
		if (msg.compare("[ERROR]___: protectedDiv: div by 0") == IDENTICAL_STRINGS)
		{
			LoadConfig::logfileconsole(msg);
			_emotion = (unsigned int)SCALE_RANGE_MEAN_EMOTION;
#ifdef _DEBUG_MODE
			throw(msg);
#endif // DEBUG_MODE
		}
		else if (msg.compare("[ERROR]___: computeValueToScale : checkMinMaxValidityRange") == IDENTICAL_STRINGS)
		{
			LoadConfig::logfileconsole(msg);
			_emotion = (unsigned int)SCALE_RANGE_MEAN_EMOTION;
#ifdef _DEBUG_MODE
			throw(msg);
#endif // DEBUG_MODE
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : computeWork																   */
/* ROLE : Calculate the work for the turn											   */
/* INPUT : void																		   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::computeWork()
{
	_workBalance = 0.0;
	for (unsigned int nbCitizen(0); nbCitizen < _citizens.size(); nbCitizen++)
	{
		_workBalance += (double)_citizens[nbCitizen]->GETwork();
	}

	/* Applying Emotion multiplier */
	_workBalance *= ((double)_emotion / SCALE_RANGE_MEAN_EMOTION);

	/* Applying the work which was converted from food in the previous turn */
	_workBalance += _workSurplusPreviousTurn;
	_workSurplusPreviousTurn = 0;
}

/* ----------------------------------------------------------------------------------- */
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
/* ----------------------------------------------------------------------------------- */
void City::computeWorkToBuild
(
	Player* player,
	const std::vector<Unit_Template>& tabUnit_Template
)
{
	if (_conversionToApply != conversionSurplus_Type::WorkToGold)
	{
		if (!_buildQueue.buildQueue.empty())
		{
			_buildQueue.buildQueue.front().remainingWork -= _workBalance;

			double workSurplus(0.0);
			while (_buildQueue.buildQueue.front().remainingWork < 0.0)
			{
				if (build_Type::unit == _buildQueue.buildQueue.front().type)
				{
					Uint8 unitToBuild(Unit::searchUnitByName(_buildQueue.buildQueue.front().name, tabUnit_Template));

					player->addUnit
					(
						_buildQueue.buildQueue.front().name,
						_x,
						_y,
						tabUnit_Template[unitToBuild].type,
						tabUnit_Template[unitToBuild].life,
						tabUnit_Template[unitToBuild].atq,
						tabUnit_Template[unitToBuild].def,
						tabUnit_Template[unitToBuild].movement,
						tabUnit_Template[unitToBuild].level
					);
				}
				else
				if (build_Type::building == _buildQueue.buildQueue.front().type)
				{
					/* TODO buildings */
				}
				else
				{
					/* N/A */
#ifdef _DEBUG_MODE
					throw("[ERROR]___: computeWorkToBuild : _buildQueue.front().type == else");
#endif // DEBUG_MODE
				}

				workSurplus = -(_buildQueue.buildQueue.front().remainingWork);

				removeBuildToQueueFront();

				if (!_buildQueue.buildQueue.empty())
				{
					_buildQueue.buildQueue.front().remainingWork -= workSurplus;
				}
				else
				{
					convertWorkSurplusToFood(workSurplus);
					return;
				}
			}
		}
	}
	else
	{
		player->addGoldToGoldConversionSurplus(_workBalance * MULTIPLIER_CONVERSION_WORK_TO_GOLD);
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : computeGold																   */
/* ROLE : Calculate the gold for the turn											   */
/* INPUT : void																		   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::computeGold()
{
	_goldBalance = 0.0;
	for (unsigned int nbCitizen(0); nbCitizen < _citizens.size(); nbCitizen++)
	{
		_goldBalance += (double)_citizens[nbCitizen]->GETwork();
	}

	/* Applying Emotion multiplier */
	_goldBalance *= ((double)_emotion / SCALE_RANGE_MEAN_EMOTION);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : addCityGoldToTaxIncome													   */
/* ROLE : Add _goldBalance to a player taxIncome 									   */
/* OUT : GoldStats& goldStats : struct of player gold								   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::addCityGoldToTaxIncome
(
	GoldStats& goldStats
)
{
	goldStats.taxIncome += _goldBalance;
	_goldBalance = 0.0;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : convertWorkSurplusToFood													   */
/* ROLE : Convert work to food ; Place in _foodSurplusPreviousTurn					   */
/* INPUT : double workSurplus : work surplus to convert into food					   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::convertWorkSurplusToFood
(
	double workSurplus
)
{
	_foodSurplusPreviousTurn = workSurplus * MULTIPLIER_CONVERSION_WORK_TO_FOOD;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : convertWorkSurplusToFood													   */
/* ROLE : Convert food to work ; Place in _workSurplusPreviousTurn					   */
/* INPUT : double workSurplus : food surplus to convert into work					   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::convertFoodSurplusToWork
(
	double foodSurplus
)
{
	_workSurplusPreviousTurn = foodSurplus * MULTIPLIER_CONVERSION_FOOD_TO_WORK;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : convertFoodSurplusToGold													   */
/* ROLE : Convert food to gold ; Place in goldStats.goldConversionSurplus			   */
/* INPUT : double workSurplus : food surplus to convert into work					   */
/* OUT : GoldStats& goldStats : gold surplus conversion								   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
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
/* ----------------------------------------------------------------------------------- */
/* NAME : addBuildToQueue															   */
/* ROLE : Push build to buildQueue													   */
/* IN : build buildToQueue : build to push into buildQueue							   */
/* OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
/* INPUT : SDL_Renderer*& renderer : ptr SDL_renderer								   */
/* INPUT : TTF_Font* font[] : array of SDL font										   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::addBuildToQueue
(
	build buildToQueue,
	SDL_Renderer*& renderer,
	TTF_Font* font[]
)
{
	ButtonTexte::createButtonTexte
		(renderer, font,
		State_Type::STATEcityMap, Select_Type::selectnothing, _buildQueue.cityMapBuildQueue,
		Texte_Type::shaded, buildToQueue.name, WriteColorButton, BackColorButton, (Uint8)CITY_BUILD_QUEUE_FONT_SIZE,
		(int)CITY_BUILD_QUEUE_BEGIN_X,
		(int)(CITY_BUILD_QUEUE_BEGIN_Y + ((unsigned int)_buildQueue.cityMapBuildQueue.size() * CITY_BUILD_QUEUE_SPACE_Y)),
		nonTransparent, no_angle, Center_Type::center);
	_buildQueue.buildQueue.push_back(buildToQueue);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : removeBuildToQueueFront													   */
/* ROLE : Pop build to buildQueue													   */
/* IN/OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::removeBuildToQueueFront()
{
	if (nullptr != _buildQueue.cityMapBuildQueue.front())
	{
		delete _buildQueue.cityMapBuildQueue.front();
		_buildQueue.cityMapBuildQueue.front() = nullptr;
	}
	else
	{
		/* N/A */
#ifdef _DEBUG_MODE
		throw("[ERROR]___: removeBuildToQueueFront : nullptr == citieMapBuildQueue.front()");
#endif // DEBUG_MODE
	}

	for (unsigned int i(CITY_IHM_SECOND_INDEX); i < _buildQueue.cityMapBuildQueue.size(); i++)
	{
		_buildQueue.cityMapBuildQueue[i]->SETdsty(_buildQueue.cityMapBuildQueue[i]->GETdsty() - CITY_BUILD_QUEUE_SPACE_Y);
	}

	_buildQueue.cityMapBuildQueue.pop_front();
	_buildQueue.buildQueue.pop_front();
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : removeBuildToQueue														   */
/* ROLE : remove build to buildQueue at index										   */
/* IN/OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
/* IN : unsigned int index : index to remove										   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::removeBuildToQueue
(
	unsigned int index
)
{
	if (index < _buildQueue.cityMapBuildQueue.size())
	{
		if (nullptr != _buildQueue.cityMapBuildQueue[index])
		{
			delete _buildQueue.cityMapBuildQueue[index];
			_buildQueue.cityMapBuildQueue[index] = nullptr;
		}
		else
		{
			/* N/A */
#ifdef _DEBUG_MODE
			throw("[ERROR]___: removeBuildToQueue : nullptr == citieMapBuildQueue.front()");
#endif // DEBUG_MODE
		}

		copyLoopBuildQueue(index);

		_buildQueue.cityMapBuildQueue.pop_back();
		_buildQueue.buildQueue.pop_back();
	}
	else
	{
#ifdef _DEBUG_MODE
		throw("[ERROR]___: removeBuildToQueue : index > citieMapBuildQueue.size() ");
#endif // DEBUG_MODE
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : copyLoopBuildQueue														   */
/* ROLE : copy index + 1 to index, start at index									   */
/* IN/OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
/* IN : unsigned int index : start of loop											   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::copyLoopBuildQueue
(
	unsigned int index
)
{
	for (unsigned int i(index); i < _buildQueue.cityMapBuildQueue.size() - 1; i++)
	{
		_buildQueue.cityMapBuildQueue[i] = _buildQueue.cityMapBuildQueue[(__int64)i + 1];
		_buildQueue.cityMapBuildQueue[i]->SETdsty(_buildQueue.cityMapBuildQueue[i]->GETdsty() - CITY_BUILD_QUEUE_SPACE_Y);
		_buildQueue.cityMapBuildQueue[(__int64)i + 1] = nullptr;
		_buildQueue.buildQueue[i] = _buildQueue.buildQueue[(__int64)i + 1];
	}
}

/* *********************************************************
 *					END City::METHODS					   *
 ********************************************************* */

 
 
/* *********************************************************
 *				START City::METHODS::Affichage			   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : afficher																	   */
/* ROLE : Affichage de la City (Texture et nom)										   */
/* INPUT : truct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::afficher
(
	Sysinfo& sysinfo
)
{
	int x(_x - sysinfo.map.screenOffsetXIndexMin * sysinfo.map.tileSize);
	int y(_y - sysinfo.map.screenOffsetYIndexMin * sysinfo.map.tileSize);

	if ((int)_x > (x - (int)(sysinfo.map.tileSize * sysinfo.map.toolBarSize)) && (int)_y >= y)
	{
		sysinfo.allTextures.cityMap[_image]->render(x, y);

		sysinfo.allTextes.mainMap[_name]->render(x + (int)(sysinfo.map.tileSize / 2), y + (int)(sysinfo.map.tileSize));

		sysinfo.allTextes.number[std::to_string((unsigned int)floor(_nbpop))]
			->render(x + (int)sysinfo.map.tileSize / 2 - 20, y + (int)sysinfo.map.tileSize - 6);
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : affichercitiemap															   */
/* ROLE : Display City Tiles to the citieMap with Citizen							   */
/* ROLE : Display the food stock of the city										   */
/* ROLE : Display the build Queue													   */
/* INPUT : truct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::afficherCityMap
(
	Sysinfo& sysinfo
)
{
	displayTexturesTextesButtons
	(
		sysinfo.allTextures.cityMap,
		sysinfo.allTextures.unit,
		sysinfo.allTextes.cityMap,
		sysinfo.allButton.cityMap,
		sysinfo.var,
		sysinfo.screen.screenWidth
	);

	afficherCityTiles(sysinfo);

	afficherCityFood(sysinfo.map.tileSize, sysinfo.allTextures.cityMap);

	afficherCityBuildToQueue(sysinfo.allTextes.cityMap);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : afficher																	   */
/* ROLE : Affichage de la City (Texture et nom)										   */
/* IN : MapTexture& cityMapTextures : CityMap Textures								   */
/* IN : MapTexture& unit : Unit Textures											   */
/* IN : MapTexte& cityMapTextes : CityMap Textes									   */
/* IN : MapButtonTexte& cityMapButtonTexte : CityMap Buttons						   */
/* IN : Var& var : structure Var													   */
/* IN : unsigned int screenWidth : screen size width in pixel 						   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::displayTexturesTextesButtons
(
	MapTexture& cityMapTextures,
	MapTexture& unit,
	MapTexte& cityMapTextes,
	MapButtonTexte& cityMapButtonTexte,
	Var& var,
	unsigned int screenWidth
)
{
	cityMapTextures["CitieToolbarButtons"]->render();
	cityMapTextures["CitieToolbarStats"]->render();

	/* *********************************************************
	 *					START Button						   *
	 ********************************************************* */

	std::string buildName(EMPTY_STRING);
	unsigned int initspace(CITY_BUILDS_BEGIN_Y);
	if (Select_Type::selectcreate == var.select)
	{
		for (Uint8 j(0); j < MAX_UNIT_TO_DISPLAY_CITIEMAP; j++)
		{
			if (
				((unsigned __int64)var.s_player.unitToCreate + j)
				<
				var.s_player.tabUnit_Template.size()
				)
			{
				buildName = var.s_player.tabUnit_Template
					[(unsigned __int64)var.s_player.unitToCreate + j].name;
			}
			else
			{
				break;
			}

			cityMapButtonTexte[buildName]
				->renderButtonTexte(var.statescreen, screenWidth / 2, initspace += CITY_BUILDS_SPACE_Y);
			unit[buildName]
				->render((screenWidth / 2) - 50, initspace);
			cityMapTextes[
				"life:" + std::to_string(var.s_player.tabUnit_Template[(__int64)var.s_player.unitToCreate + j].life) +
					"/atq:" + std::to_string(var.s_player.tabUnit_Template[(__int64)var.s_player.unitToCreate + j].atq) +
					"/def:" + std::to_string(var.s_player.tabUnit_Template[(__int64)var.s_player.unitToCreate + j].def) +
					"/move:" + std::to_string(var.s_player.tabUnit_Template[(__int64)var.s_player.unitToCreate + j].movement)]
				->render((screenWidth / 2) + 200, initspace);
		}

		cityMapTextes["Scroll up or down"]->render();
		cityMapTextes["Left click to Select"]->render();
		cityMapTextes["create : "]->render();
		cityMapTextes["selectcreate"]->render();
	}
	else
	{
		/* N/A */
	}


	cityMapButtonTexte["Map"]->renderButtonTexte(var.statescreen);
	cityMapButtonTexte["Build"]->renderButtonTexte(var.statescreen);
	cityMapButtonTexte["Food"]->renderButtonTexte(var.statescreen);
	cityMapButtonTexte["Place Citizen"]->renderButtonTexte(var.statescreen);

}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : afficherCitieTiles														   */
/* ROLE : Display City Tiles to the citieMap with Citizen							   */
/* INPUT : truct Sysinfo& : Global struct											   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::afficherCityTiles
(
	Sysinfo& sysinfo
)
{
	unsigned int offsetY(192), y(0);
	/* Affichage des cases qui compose le secteur de la City */
	for (unsigned int i(0); (i < (INIT_SIZE_VIEW * INIT_SIZE_VIEW)); i++)
	{
		y = _tile[i].tile_y + offsetY;
		switch (_tile[i].tile_ground)
		{
		case Ground_Type::error:
#ifdef _DEBUG_MODE
			throw("[ERROR]___: affichercitiemap : sysinfo.allTextures.ground[]");
#endif // DEBUG_MODE
			break;
		case Ground_Type::grass:
			sysinfo.allTextures.ground["grass.bmp"]->render(_tile[i].tile_x, y);
			break;
		case Ground_Type::water:
			sysinfo.allTextures.ground["water.bmp"]->render(_tile[i].tile_x, y);
			break;
		case Ground_Type::deepwater:
			/* ### As of 0.20.4.5 : deepwater cannoit be seen in a city ### */
			break;
		case Ground_Type::dirt:
			/* ### As of 0.20.4.5 : not implemented ### */
			break;
		case Ground_Type::sand:
			/* ### As of 0.20.4.5 : not implemented ### */
			break;
		default:
			/* N/A */
#ifdef _DEBUG_MODE
			throw("[ERROR]___: affichercitiemap : sysinfo.allTextures.ground[]");
#endif // DEBUG_MODE
			break;
		}

		if (GroundSpec_Type::nothing < _tile[i].tile_spec)
		{
			sysinfo.allTextures.groundSpec[_tile[i].tile_stringspec]
				->render(_tile[i].tile_x, y);
		}
		else
		{
			/* N/A */
		}

		if (NO_APPARTENANCE < _tile[i].appartenance)
		{
			sysinfo.allTextures.colorapptile["ColorPlayertile" + std::to_string(_tile[i].appartenance) + ".bmp"]
				->render(_tile[i].tile_x, y);
		}
		else
		{
			/* N/A */
		}

		for (unsigned int nbCitizen(0); nbCitizen < _citizens.size(); nbCitizen++)
		{
			if (_citizens[nbCitizen]->GETtileOccupied() == i && _citizens[nbCitizen]->GETplace())
			{
				_citizens[nbCitizen]->afficher(sysinfo.allTextures.cityMap, _tile[i].tile_x, y);
			}
			else
			{
				/* N/A */
			}
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : afficherCitieFood															   */
/* ROLE : Display the food stock of the city										   */
/* INPUT : unsigned int tileSize : Size of tile in the city							   */
/* INPUT : MapTexture& citieMap : UnorderMap of City Texture 						   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::afficherCityFood
(
	unsigned int tileSize,
	MapTexture& citieMap
)
{
	/* Affichage food */
	unsigned int renderFoodY(tileSize), offSetRenderX(0), offSetRenderY(0);
	if (_foodStock > CITY_ZERO_FOOD)
	{
		for (double nbfood(CITY_ZERO_FOOD); nbfood < _foodStock; nbfood++)
		{
			if (((unsigned int)nbfood % CITY_FOOD_NB_PER_ROW) == MODULO_ZERO)
			{
				offSetRenderY++;
				offSetRenderX = 0;
			}
			else
			{
				/* N/A */
			}

			citieMap["food.png"]->render
				(CITY_FOOD_BEGIN_X + (offSetRenderX * CITY_FOOD_SPACE_X),
				 CITY_FOOD_BEGIN_Y + (offSetRenderY * renderFoodY));

			offSetRenderX++;
		}
	}
	else
	{
		/* N/A */
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : afficherCitieBuildToQueue													   */
/* ROLE : Display the build Queue													   */
/* INPUT : MapTexte& citieMap : UnorderMap of City Texte							   */
/* INPUT : DequeButtonTexte& : Deque of buttons use in build Queue					   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::afficherCityBuildToQueue
(
	MapTexte& citieMap
)
{
	if  (
			_buildQueue.buildQueue.empty() == false
			&&
			_buildQueue.buildQueue.size() == _buildQueue.cityMapBuildQueue.size()
		)
	{
		for (unsigned int indexBuildQueue(0); indexBuildQueue < _buildQueue.buildQueue.size(); indexBuildQueue++)
		{
			_buildQueue.cityMapBuildQueue[indexBuildQueue]->render();
		}
	}
	else
	{
		citieMap["Currently no build is being built"]->render();
	}
}


/* *********************************************************
 *				END City::METHODS::Affichage			   *
 ********************************************************* */


/*
*	End Of File City.cpp
*/