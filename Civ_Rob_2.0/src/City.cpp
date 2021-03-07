/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.2.0
	file version : 1.29

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

#include "MainGame.h"
#include "Utility.h"
#include "Citizen.h"

 /* *********************************************************
  *					START City::STATIC					   *
  ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : createCity																   */
/* ROLE : Cr�ation d'une City � partir d'un settler sur la carte					   */
/* INPUT/OUTPUT : struct Sysinfo& : Global structure								   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::createCity
(
	MainGame& mainGame,
	unsigned int influenceLevel
)
{
	unsigned int selectedPlayer(mainGame.GETPlayers().GETselectedPlayer());
	Player* splayer(mainGame.GETPlayers().GETvectPlayer()[selectedPlayer]);
	unsigned int selectedUnit(splayer->GETselectedUnit());
	Unit* sUnit(splayer->GETtheUnit(selectedUnit));

	if	(
			sUnit->GETname().compare("settler")
			==
			IDENTICAL_STRINGS
		)
	{
		/* ---------------------------------------------------------------------- */
		/* 1� : Recherche du nom de la nouvelle Citie 							  */
		/*    : Recherche dans le tableau global des noms de Citie				  */
		/*  : En fonction du nombre de Citie d�j� cr�es et de MAX_CITY_PER_PLAYER */
		/* ---------------------------------------------------------------------- */

		std::string name(mainGame.GETPlayers().GETvectCityName()
			[
				(unsigned __int64)
				(
					((unsigned __int64)selectedPlayer * MAX_CITY_PER_PLAYER)
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
			mainGame.GETscreen(),
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
/* INPUT : const Screen& screen	: taille en x et y de l'�cran						   */
/* INPUT : unsigned int middletileX : index en tileSize de x de la Citie			   */
/* INPUT : unsigned int middletileY : index en tileSize de y de la Citie			   */
/* INPUT : unsigned int selectplayer : index d'appartenance							   */
/* INPUT/OUTPUT : Map& map : structure de la Map									   */
/* OUTPUT : std::vector<Tile>& tabtile : tableau � remplir de la Citie				   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::fillCitieTiles
(
	const Screen& screen,
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
				.appartenance = selectplayer;
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
			tabtile[k].tile_x = (screen.screenWidth / 2) - (-o * mainMap.GETtileSize());
			tabtile[k].tile_y = (screen.screenHeight / 2) - (-p * mainMap.GETtileSize());
			k++;
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initSizeInfluenceCondition												   */
/* ROLE : Conditions des cases de la ville � l'int�rieur de zone d'influence		   */
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
/* ----------------------------------------------------------------------------------- */
/* NAME : cornerCheck																   */
/* ROLE : Conditions des cases de la ville � l'int�rieur de zone d'influence		   */
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
	Players& players,
	const GameInput& gameInput,
	Var& var
)
{
	Player* selPlayer(players.GETvectPlayer()[players.GETselectedPlayer()]);

	for (unsigned int i(0); i < selPlayer->GETtabCity().size(); i++)
	{
		if (selPlayer->GETtheCity(i)->testPos(gameInput.GETmouse_xNormalized(), gameInput.GETmouse_yNormalized()))
		{
			selPlayer->SETselectedCity(i);
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
	VectMap& tiles
)
	: _image("citie.png"),
	_name(name), _x(x), _y(y), _tile(tiles),
	_influenceLevel(MIN_INFLUENCE_LEVEL), _nbpop(MIN_POP), _atq(0), _def(0), _emotion((unsigned int)MEAN_EMOTION), _nbstructurebuild(0),
	_foodStock(CITY_ZERO_FOOD), _foodBalance(tiles[(unsigned int)ceil((INIT_SIZE_VIEW * INIT_SIZE_VIEW) / 2)].food),
	_foodSurplusPreviousTurn(CITY_ZERO_FOOD), _workBalance(0), _workSurplusPreviousTurn(0), _goldBalance(0.0),
	_conversionToApply(conversionSurplus_Type::No_Conversion)
{
	_citizens.push_back(new Citizen(tiles[(unsigned int)ceil((INIT_SIZE_VIEW * INIT_SIZE_VIEW) / 2)]));

	MainGame::logfileconsole("[INFO]___: Create Citie: " + _name + " Success");
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




	MainGame::logfileconsole("[INFO]___: Destroy Citie: " + _name + " Success");
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
	if (
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
/* ROLE : Calcul sur une echelle de 0 � 100 le bonheur de la Citie					   */
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
			MainGame::logfileconsole(msg);
			_emotion = (unsigned int)SCALE_RANGE_MEAN_EMOTION;
#ifdef _DEBUG_MODE
			throw(msg);
#endif // DEBUG_MODE
		}
		else if (msg.compare("[ERROR]___: computeValueToScale : checkMinMaxValidityRange") == IDENTICAL_STRINGS)
		{
			MainGame::logfileconsole(msg);
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
	const VectUnitTemplate& tabUnit_Template
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
					unsigned int unitToBuild(Unit::searchUnitByName(_buildQueue.buildQueue.front().name, tabUnit_Template));

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
						tabUnit_Template[unitToBuild].level,
						tabUnit_Template[unitToBuild].maintenance
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

)
{

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

)
{

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

)
{
	displayTexturesTextesButtons
	(
	
	);

	afficherCityTiles();

	afficherCityFood();

	afficherCityBuildToQueue();
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


)
{


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

)
{

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
	
)
{

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
	
)
{

}


/* *********************************************************
 *				END City::METHODS::Affichage			   *
 ********************************************************* */


 /*
 *	End Of File City.cpp
 */