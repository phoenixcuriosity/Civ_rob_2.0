/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.4.0
	file version : 1.23

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

#ifndef City_H
#define City_H

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"

#include "MainMap.h"
#include "Unit.h"
#include "Citizen.h"

#include <vector>
#include <queue>
#include <memory>

#include <RealEngine2D/src/Window.h>
#include <RealEngine2D/src/GUI.h>

/* Redef : include in .cpp */
class GamePlayScreen;
class Players;
class Player;
class GameInput;

struct Screen;
struct Var;
struct GoldStats;

/* *********************************************************
 *					 Constantes							   *
 ********************************************************* */

  /* taille de la carte transpos�e dans la citiemap */
const unsigned int INIT_SIZE_VIEW = 9;

/* Population maximale dans une Citie */
const unsigned int MAX_POP = 50;

/* Minimal population in City */
const unsigned int MIN_POP = 1;

/* Minimal influence level in City */
const unsigned int MIN_INFLUENCE_LEVEL = 1;

/* Todo : g�n�ralisation : compter nb Citie par player dans CITIENAME.txt */

/* Nombre de noms de Citie dans CITIENAME.txt */
const unsigned int MAX_CITY_PER_PLAYER = 5;

/* Define the maximum range of emotion */
const double SCALE_RANGE_MAX_EMOTION = 100.0;

/* Define the minimum range of emotion */
const double SCALE_RANGE_MIN_EMOTION = 0.0;

/* Define the mean emotion */
const double MEAN_EMOTION = ((SCALE_RANGE_MAX_EMOTION + SCALE_RANGE_MIN_EMOTION) / 2.0);

/* Define the mean value of emotion range */
const double SCALE_RANGE_MEAN_EMOTION = ((abs(SCALE_RANGE_MAX_EMOTION) + abs(SCALE_RANGE_MIN_EMOTION)) / 2.0);

/* Define the multiplier coefficient to convert work to food */
const double MULTIPLIER_CONVERSION_WORK_TO_FOOD = 10.0;

/* Define the multiplier coefficient to convert food to work */
const double MULTIPLIER_CONVERSION_FOOD_TO_WORK = (1.0 / MULTIPLIER_CONVERSION_WORK_TO_FOOD);

/* Define the multiplier coefficient to convert work to gold */
const double MULTIPLIER_CONVERSION_WORK_TO_GOLD = (10.0 * MULTIPLIER_CONVERSION_WORK_TO_FOOD);

/* Define the multiplier coefficient to convert food to gold */
const double MULTIPLIER_CONVERSION_FOOD_TO_GOLD = (MULTIPLIER_CONVERSION_WORK_TO_GOLD / MULTIPLIER_CONVERSION_FOOD_TO_WORK);

const unsigned int CITY_IHM_SECOND_INDEX = 1;

/* Define the minimum food in a City */
const double CITY_ZERO_FOOD = 0.0;

/* Define the minimum food in a City */
const double CITY_ZERO = 0.0;

/* Define the minimum food to level up */
const double MIN_FOOD_TO_LEVEL_UP = 1.0;

/* Define Percent */
const double ONE_HUNDRED_PERCENT = 100.0;

/* *********************************************************
 *							 Enum						   *
 ********************************************************* */

 /* Define the types of builds that a city can create */
enum class build_Type : unsigned int
{
	building,	/* ### Not implemented as of 0.20.3.1 ### */
	unit
};

/* Define types of conversion that a city can apply to the ressources */
enum class conversionSurplus_Type : unsigned int
{
	No_Conversion,
	FoodToWork, /* Apply MULTIPLIER_CONVERSION_FOOD_TO_WORK */
	FoodToGold, /* Apply MULTIPLIER_CONVERSION_FOOD_TO_GOLD */
	WorkToFood, /* Apply MULTIPLIER_CONVERSION_WORK_TO_FOOD */
	WorkToGold, /* Apply MULTIPLIER_CONVERSION_WORK_TO_GOLD */
	GoldToFood, /* ### Not implemented as of 0.20.3.1 ### */
	GoldToWork  /* ### Not implemented as of 0.20.3.1 ### */
};

/* Define a type to resize Units Texture between city and mainmap */
enum class resizeUnitTexture_Type : unsigned int
{
	mainmap,
	city
};


/* *********************************************************
 *						 Structs						   *
 ********************************************************* */

 /*
	 Define a building in a City
	 Use for building Queue
 */
struct build
{
	std::string name;
	build_Type type;
	double work;
	double remainingWork;
};

struct buildGUI
{
	CEGUI::PushButton* buildG = nullptr;
	build buildQ;
};

typedef std::deque<buildGUI> dequeBuild;

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */

class City
{
public:
	/* *********************************************************
	 *					City::STATIC						   *
	 ********************************************************* */

	/* ----------------------------------------------------------------------------------- */
	/* NAME : createCity																   */
	/* ROLE : Cr�ation d'une City � partir d'un settler sur la carte					   */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	static void createCity
	(
		GamePlayScreen& mainGame,
		unsigned int influenceLevel = MIN_INFLUENCE_LEVEL
	);

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
	static void fillCitieTiles
	(
		const RealEngine2D::Window& window,
		unsigned int middletileX,
		unsigned int middletileY,
		unsigned int selectplayer,
		MainMap& mainMap,
		VectMap& tabtile,
		unsigned int influenceLevel = MIN_INFLUENCE_LEVEL
	);

private:

	/* ----------------------------------------------------------------------------------- */
	/* NAME : initSizeInfluenceCondition												   */
	/* ROLE : Conditions des cases de la ville � l'int�rieur de zone d'influence		   */
	/* INPUT : int o :	index en x														   */
	/* INPUT : int p :	index en y														   */
	/* RETURNED VALUE : bool : false -> invalid / true -> valid							   */
	/* ----------------------------------------------------------------------------------- */
	static bool initSizeInfluenceCondition
	(
		int o,
		int p,
		unsigned int influenceLevel = MIN_INFLUENCE_LEVEL
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : cornerCheck																   */
	/* ROLE : Conditions des cases de la ville � l'int�rieur de zone d'influence		   */
	/* IN : int o :	index en x															   */
	/* IN : int p :	index en y															   */
	/* IN : unsigned int influenceLevel : City influence level 							   */
	/* RETURNED VALUE : bool : false -> this tile is a corner							   */
	/* RETURNED VALUE : bool : true -> this tile is not a corner						   */
	/* ----------------------------------------------------------------------------------- */
	static bool cornerCheck
	(
		int o,
		int p,
		unsigned int influenceLevel
	);


public:
	/* *********************************************************
	 *					City::METHODS						   *
	 ********************************************************* */


	 /* ----------------------------------------------------------------------------------- */
	 /* NAME : City																		   */
	 /* ROLE : Constructeur complet														   */
	 /* INPUT : const std::string &	: name de la Citie									   */
	 /* INPUT : unsigned int x : index en x												   */
	 /* INPUT : unsigned int y : index en y												   */
	 /* INPUT : Tile tile[] : tableau de tile de la Citie								   */
	 /* ----------------------------------------------------------------------------------- */
	City
	(
		const std::string&,
		unsigned int x,
		unsigned int y,
		VectMap& tiles
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : ~City																		   */
	/* ROLE : Destructeur																   */
	/* INPUT : void																		   */
	/* ----------------------------------------------------------------------------------- */
	virtual ~City();

	/* ----------------------------------------------------------------------------------- */
	/* NAME : resetTabCitizen															   */
	/* ROLE : Remove all Citizens in the City											   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void resetTabCitizen();

	/* ----------------------------------------------------------------------------------- */
	/* NAME : foodNextTurn																   */
	/* ROLE : Calcul et application du niveau de Food pour le prochain tour				   */
	/* OUT : GoldStats& goldStats : Player gold stats									   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void foodNextTurn
	(
		GoldStats& goldStats
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : searchCityTile															   */
	/* ROLE : Recherche la case de la City et renvoie vers cityMap						   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual bool searchCityTile
	(
		unsigned int indexX,
		unsigned int indexY
	);

private:

	virtual double tileValue
	(
		const Tile& tile,
		double coefFood = 1.0,
		double coefWork = 1.0,
		double coefGold = 1.0
	) const;

public:
	/* ----------------------------------------------------------------------------------- */
	/* NAME : testPos																	   */
	/* ROLE : Retourne si la position est valide										   */
	/* INPUT : unsigned int x : position de la souris en x								   */
	/* INPUT : unsigned int y : position de la souris en y								   */
	/* RETURNED VALUE : bool : false : invalid / true : valid							   */
	/* ----------------------------------------------------------------------------------- */
	virtual bool testPos
	(
		unsigned int x,
		unsigned int y
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : computeEmotion															   */
	/* ROLE : Calcul sur une echelle de 0 � 100 le bonheur de la Citie					   */
	/* INPUT : void																		   */
	/* INTERNAL OUTPUT : m_emotion : bonheur de la Citie								   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void computeEmotion();

	/* ----------------------------------------------------------------------------------- */
	/* NAME : computeWork																   */
	/* ROLE : Calculate the work for the turn											   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void computeWork();

	/* ----------------------------------------------------------------------------------- */
	/* NAME : computeWorkToBuild														   */
	/* ROLE : Compute the remaining work to build a building or unit					   */
	/* ROLE : if the remaining work is zero then the building or unit is created		   */
	/* ROLE : if the build is created and there work Surplus then either apply it ...	   */
	/* ROLE : ... to next build or convert it to food									   */
	/* INPUT : Player* : ptr to the selected player										   */
	/* INPUT : std::vector<Unit_Template>& : vector of Units template					   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void computeWorkToBuild
	(
		Player& player,
		const VectUnitTemplate& vectUnitTemplate,
		bool* needToUpdateDrawUnit
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : computeGold																   */
	/* ROLE : Calculate the gold for the turn											   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void computeGold();

	/* ----------------------------------------------------------------------------------- */
	/* NAME : addCityGoldToTaxIncome													   */
	/* ROLE : Add m_goldBalance to a player taxIncome 									   */
	/* OUT : GoldStats& goldStats : struct of player gold								   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void addCityGoldToTaxIncome
	(
		GoldStats& goldStats
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : convertWorkSurplusToFood													   */
	/* ROLE : Convert work to food ; Place in m_foodSurplusPreviousTurn					   */
	/* INPUT : double workSurplus : work surplus to convert into food					   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void convertWorkSurplusToFood
	(
		double workSurplus
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : convertWorkSurplusToFood													   */
	/* ROLE : Convert food to work ; Place in m_workSurplusPreviousTurn					   */
	/* INPUT : double workSurplus : food surplus to convert into work					   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void convertFoodSurplusToWork
	(
		double foodSurplus
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : convertFoodSurplusToGold													   */
	/* ROLE : Convert food to gold ; Place in goldStats.goldConversionSurplus			   */
	/* INPUT : double workSurplus : food surplus to convert into work					   */
	/* OUT : GoldStats& goldStats : gold surplus conversion								   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void convertFoodSurplusToGold
	(
		double foodSurplus,
		GoldStats& goldStats
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : addBuildToQueue															   */
	/* ROLE : Push build to buildQueue													   */
	/* IN : build buildToQueue : build to push into buildQueue							   */
	/* OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
	/* INPUT : SDL_Renderer*& renderer : ptr SDL_renderer								   */
	/* INPUT : TTF_Font* font[] : array of SDL font										   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void addBuildToQueue
	(
		const buildGUI& buildToQueue
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : removeBuildToQueueFront													   */
	/* ROLE : Pop build to buildQueue													   */
	/* IN/OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void removeBuildToQueueFront();

	/* ----------------------------------------------------------------------------------- */
	/* NAME : removeBuildToQueue														   */
	/* ROLE : remove build to buildQueue at index										   */
	/* IN/OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
	/* IN : unsigned int index : index to remove										   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void removeBuildToQueue
	(
		size_t index
	);

public:
	/* *********************************************************
	 *				City::METHODS::GET/SET					   *
	 ********************************************************* */

	inline virtual std::string GETimage()const { return m_image; };
	inline virtual std::string GETname()const { return m_name; };
	inline virtual unsigned int GETx()const { return m_x; };
	inline virtual unsigned int GETy()const { return m_y; };
	inline virtual VectMap& GETtile() { return m_tile; };
	inline virtual VectCitizen& GETcitizens() { return m_citizens; };
	inline virtual unsigned int GETinfluenceLevel()const { return m_influenceLevel; };
	inline virtual unsigned int GETnbpop()const { return m_nbpop; };
	inline virtual unsigned int GETatq()const { return m_atq; };
	inline virtual unsigned int GETdef()const { return m_def; };
	inline virtual unsigned int GETemotion()const { return m_emotion; };
	inline virtual unsigned int GETnbstructurebuild()const { return m_nbstructurebuild; };
	inline virtual double GETfoodStock()const { return m_foodStock; };
	inline virtual double GETfoodBalance()const { return m_foodBalance; };
	inline virtual double GETfoodSurplusPreviousTurn()const { return m_foodSurplusPreviousTurn; };
	inline virtual double GETfoodToLevelUp()const { return m_foodToLevelUp; };
	inline virtual double GETgoldBalance()const { return m_goldBalance; };
	inline virtual conversionSurplus_Type GETconversionToApply()const { return m_conversionToApply; };
	inline virtual dequeBuild& GETbuildQueue() { return m_buildQueue; };

	inline virtual double GETfoodStockPerc()const { return ((m_foodStock / m_foodToLevelUp) * ONE_HUNDRED_PERCENT); };
	inline virtual double GETBuildPerc()const
	{
		if (m_buildQueue.empty() == VECT_NOT_EMPTY)
		{
			return 
				(
					(
						(
							m_buildQueue.front().buildQ.work
							-
							m_buildQueue.front().buildQ.remainingWork
						)
						/ 
						m_buildQueue.front().buildQ.work
					)
					* ONE_HUNDRED_PERCENT
				);
		}
		return 0.0;
	};

	inline virtual void SETimage(std::string image) { m_image = image; };
	inline virtual void SETname(std::string name) { m_name = name; };
	inline virtual void SETx(unsigned int x) { m_x = x; };
	inline virtual void SETy(unsigned int y) { m_y = y; };
	inline virtual void SETtile(VectMap& tile) { m_tile = tile; };
	//inline virtual void SETcitizens(VectCitizen& citizens) { m_citizens = citizens; };
	inline virtual void SETinfluenceLevel(unsigned int influenceLevel) { m_influenceLevel = influenceLevel; };
	inline virtual void SETnbpop(unsigned int nbpop) { m_nbpop = nbpop; };
	inline virtual void SETatq(unsigned int atq) { m_atq = atq; };
	inline virtual void SETdef(unsigned int def) { m_def = def; };
	inline virtual void SETemotion(unsigned int emotion) { m_emotion = emotion; };
	inline virtual void SETnbstructurebuild(unsigned int nbstructurebuild) { m_nbstructurebuild = nbstructurebuild; };
	inline virtual void SETfoodStock(double foodStock) { m_foodStock = foodStock; };
	inline virtual void SETfoodBalance(double foodBalance) { m_foodBalance = foodBalance; };
	inline virtual void SETfoodSurplusPreviousTurn(double foodSurplusPreviousTurn) { m_foodSurplusPreviousTurn = foodSurplusPreviousTurn; };
	inline virtual void SETfoodToLevelUp(double foodToLevelUp) { m_foodToLevelUp = foodToLevelUp; };
	inline virtual void SETgoldBalance(double goldBalance) { m_goldBalance = goldBalance; };
	inline virtual void SETconversionToApply(conversionSurplus_Type type) { m_conversionToApply = type; };


private:
	/* *********************************************************
	 *					City::ATTRIBUTS						   *
	 ********************************************************* */

	std::string m_image;
	std::string m_name;
	unsigned int m_x;
	unsigned int m_y;
	VectMap m_tile;
	VectCitizen m_citizens;
	unsigned int m_influenceLevel;
	unsigned int m_nbpop;
	unsigned int m_atq;
	unsigned int m_def;
	unsigned int m_emotion;
	unsigned int m_nbstructurebuild;

	double m_foodStock;
	double m_foodBalance;
	double m_foodSurplusPreviousTurn;
	double m_foodToLevelUp;

	double m_workBalance;
	double m_workSurplusPreviousTurn;

	double m_goldBalance;

	conversionSurplus_Type m_conversionToApply;

	dequeBuild m_buildQueue;
};


typedef std::vector<std::shared_ptr<City>> VectCity;



#endif /* City_H */

/*
*	End Of File : City.h
*/
