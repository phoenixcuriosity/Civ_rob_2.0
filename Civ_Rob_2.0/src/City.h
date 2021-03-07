/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.2.0
	file version : 1.17

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

#include <vector>
#include <queue>

/* Redef : include in .cpp */
class MainGame;
class Citizen;
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
	double remainingWork;
};

/*
	Define 2 arrays :
	-> buildQueue : use for City process
	-> cityMapBuildQueue : use for City IHM
	Error if both are not with the same size
*/
struct cityBuildQueue
{
	std::deque<build> buildQueue;

};

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
	 /* ----------------------------------------------------------------------------------- */
	 /* NAME : createCity																   */
	 /* ROLE : Cr�ation d'une City � partir d'un settler sur la carte					   */
	 /* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
	 /* RETURNED VALUE    : void															   */
	 /* ----------------------------------------------------------------------------------- */
	 /* ----------------------------------------------------------------------------------- */
	static void createCity
	(
		MainGame& mainGame,
		unsigned int influenceLevel = MIN_INFLUENCE_LEVEL
	);

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
	static void fillCitieTiles
	(
		const Screen& screen,
		unsigned int middletileX,
		unsigned int middletileY,
		unsigned int selectplayer,
		MainMap& mainMap,
		VectMap& tabtile,
		unsigned int influenceLevel = MIN_INFLUENCE_LEVEL
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initSizeInfluenceCondition												   */
	/* ROLE : Conditions des cases de la ville � l'int�rieur de zone d'influence		   */
	/* INPUT : int o :	index en x														   */
	/* INPUT : int p :	index en y														   */
	/* RETURNED VALUE : bool : false -> invalid / true -> valid							   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static bool initSizeInfluenceCondition
	(
		int o,
		int p,
		unsigned int influenceLevel = MIN_INFLUENCE_LEVEL
	);

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
	static bool cornerCheck
	(
		int o,
		int p,
		unsigned int influenceLevel
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : searchCityTile															   */
	/* ROLE : Recherche la case de la City et renvoie vers cityMap						   */
	/* INPUT : const std::vector<Player*>& : Vecteur de joueurs							   */
	/* INPUT/OUTPUT : Var& : Structure Var												   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void searchCityTile
	(
		Players& players,
		const GameInput& gameInput,
		Var& var
	);

public:
	/* *********************************************************
	 *					City::METHODS						   *
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
	City
	(
		const std::string&,
		unsigned int x,
		unsigned int y,
		VectMap& tiles
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : ~City																		   */
	/* ROLE : Destructeur																   */
	/* INPUT : void																		   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual ~City();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : resetTabCitizen															   */
	/* ROLE : Remove all Citizens in the City											   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void resetTabCitizen();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : foodNextTurn																   */
	/* ROLE : Calcul et application du niveau de Food pour le prochain tour				   */
	/* OUT : GoldStats& goldStats : Player gold stats									   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void foodNextTurn
	(
		GoldStats& goldStats
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : testPos																	   */
	/* ROLE : Retourne si la position est valide										   */
	/* INPUT : unsigned int x : position de la souris en x								   */
	/* INPUT : unsigned int y : position de la souris en y								   */
	/* RETURNED VALUE : bool : false : invalid / true : valid							   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual bool testPos
	(
		unsigned int x,
		unsigned int y
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : computeEmotion															   */
	/* ROLE : Calcul sur une echelle de 0 � 100 le bonheur de la Citie					   */
	/* INPUT : void																		   */
	/* INTERNAL OUTPUT : _emotion : bonheur de la Citie									   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void computeEmotion();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : computeWork																   */
	/* ROLE : Calculate the work for the turn											   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void computeWork();

	/* ----------------------------------------------------------------------------------- */
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
	/* ----------------------------------------------------------------------------------- */
	virtual void computeWorkToBuild
	(
		Player* player,
		const VectUnitTemplate& tabUnit_Template
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : computeGold																   */
	/* ROLE : Calculate the gold for the turn											   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void computeGold();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : addCityGoldToTaxIncome													   */
	/* ROLE : Add _goldBalance to a player taxIncome 									   */
	/* OUT : GoldStats& goldStats : struct of player gold								   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void addCityGoldToTaxIncome
	(
		GoldStats& goldStats
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : convertWorkSurplusToFood													   */
	/* ROLE : Convert work to food ; Place in _foodSurplusPreviousTurn					   */
	/* INPUT : double workSurplus : work surplus to convert into food					   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void convertWorkSurplusToFood
	(
		double workSurplus
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : convertWorkSurplusToFood													   */
	/* ROLE : Convert food to work ; Place in _workSurplusPreviousTurn					   */
	/* INPUT : double workSurplus : food surplus to convert into work					   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void convertFoodSurplusToWork
	(
		double foodSurplus
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : convertFoodSurplusToGold													   */
	/* ROLE : Convert food to gold ; Place in goldStats.goldConversionSurplus			   */
	/* INPUT : double workSurplus : food surplus to convert into work					   */
	/* OUT : GoldStats& goldStats : gold surplus conversion								   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void convertFoodSurplusToGold
	(
		double foodSurplus,
		GoldStats& goldStats
	);

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
	virtual void addBuildToQueue
	(

	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : removeBuildToQueueFront													   */
	/* ROLE : Pop build to buildQueue													   */
	/* IN/OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void removeBuildToQueueFront();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : removeBuildToQueue														   */
	/* ROLE : remove build to buildQueue at index										   */
	/* IN/OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
	/* IN : unsigned int index : index to remove										   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void removeBuildToQueue
	(
		unsigned int index
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : copyLoopBuildQueue														   */
	/* ROLE : copy index + 1 to index, start at index									   */
	/* IN/OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
	/* IN : unsigned int index : start of loop											   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void copyLoopBuildQueue
	(
		unsigned int index
	);

public:
	/* *********************************************************
	 *				City::METHODS::Affichage				   *
	 ********************************************************* */


	 /* ----------------------------------------------------------------------------------- */
	 /* ----------------------------------------------------------------------------------- */
	 /* NAME : afficher																	   */
	 /* ROLE : Affichage de la City (Texture et nom)										   */
	 /* INPUT : truct Sysinfo& : structure globale du programme							   */
	 /* RETURNED VALUE    : void															   */
	 /* ----------------------------------------------------------------------------------- */
	 /* ----------------------------------------------------------------------------------- */
	virtual void afficher
	(
		
	);

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
	virtual void displayTexturesTextesButtons
	(

	);

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
	virtual void afficherCityMap
	(

	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : afficherCitieTiles														   */
	/* ROLE : Display City Tiles to the citieMap with Citizen							   */
	/* INPUT : truct Sysinfo& : Global struct											   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void afficherCityTiles
	(

	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : afficherCitieFood															   */
	/* ROLE : Display the food stock of the city										   */
	/* INPUT : unsigned int tileSize : Size of tile in the city							   */
	/* INPUT : MapTexture& citieMap : UnorderMap of City Texture 						   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void afficherCityFood
	(

	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : afficherCitieBuildToQueue													   */
	/* ROLE : Display the build Queue													   */
	/* INPUT : MapTexte& citieMap : UnorderMap of City Texte							   */
	/* INPUT : DequeButtonTexte& : Deque of buttons use in build Queue					   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void afficherCityBuildToQueue
	(

	);


public:
	/* *********************************************************
	 *				City::METHODS::GET/SET					   *
	 ********************************************************* */

	inline virtual std::string GETimage()const { return _image; };
	inline virtual std::string GETname()const { return _name; };
	inline virtual unsigned int GETx()const { return _x; };
	inline virtual unsigned int GETy()const { return _y; };
	inline virtual VectMap& GETtile() { return _tile; };
	inline virtual std::vector<Citizen*>& GETcitizens() { return _citizens; };
	inline virtual unsigned int GETinfluenceLevel()const { return _influenceLevel; };
	inline virtual unsigned int GETnbpop()const { return _nbpop; };
	inline virtual unsigned int GETatq()const { return _atq; };
	inline virtual unsigned int GETdef()const { return _def; };
	inline virtual unsigned int GETemotion()const { return _emotion; };
	inline virtual unsigned int GETnbstructurebuild()const { return _nbstructurebuild; };
	inline virtual double GETfoodStock()const { return _foodStock; };
	inline virtual double GETfoodBalance()const { return _foodBalance; };
	inline virtual double GETfoodSurplusPreviousTurn()const { return _foodSurplusPreviousTurn; };
	inline virtual double GETgoldBalance()const { return _goldBalance; };
	inline virtual conversionSurplus_Type GETconversionToApply()const { return _conversionToApply; };
	inline virtual cityBuildQueue& GETbuildQueue() { return _buildQueue; };

	inline virtual void SETimage(std::string image) { _image = image; };
	inline virtual void SETname(std::string name) { _name = name; };
	inline virtual void SETx(unsigned int x) { _x = x; };
	inline virtual void SETy(unsigned int y) { _y = y; };
	inline virtual void SETtile(VectMap& tile) { _tile = tile; };
	inline virtual void SETcitizens(std::vector<Citizen*>& citizens) { _citizens = citizens; };
	inline virtual void SETinfluenceLevel(unsigned int influenceLevel) { _influenceLevel = influenceLevel; };
	inline virtual void SETnbpop(unsigned int nbpop) { _nbpop = nbpop; };
	inline virtual void SETatq(unsigned int atq) { _atq = atq; };
	inline virtual void SETdef(unsigned int def) { _def = def; };
	inline virtual void SETemotion(unsigned int emotion) { _emotion = emotion; };
	inline virtual void SETnbstructurebuild(unsigned int nbstructurebuild) { _nbstructurebuild = nbstructurebuild; };
	inline virtual void SETfoodStock(double foodStock) { _foodStock = foodStock; };
	inline virtual void SETfoodBalance(double foodBalance) { _foodBalance = foodBalance; };
	inline virtual void SETfoodSurplusPreviousTurn(double foodSurplusPreviousTurn) { _foodSurplusPreviousTurn = foodSurplusPreviousTurn; };
	inline virtual void SETgoldBalance(double goldBalance) { _goldBalance = goldBalance; };
	inline virtual void SETconversionToApply(conversionSurplus_Type type) { _conversionToApply = type; };


private:
	/* *********************************************************
	 *					City::ATTRIBUTS						   *
	 ********************************************************* */

	std::string _image;
	std::string _name;
	unsigned int _x;
	unsigned int _y;
	VectMap _tile;
	std::vector<Citizen*> _citizens;
	unsigned int _influenceLevel;
	unsigned int _nbpop;
	unsigned int _atq;
	unsigned int _def;
	unsigned int _emotion;
	unsigned int _nbstructurebuild;

	double _foodStock;
	double _foodBalance;
	double _foodSurplusPreviousTurn;

	double _workBalance;
	double _workSurplusPreviousTurn;

	double _goldBalance;

	conversionSurplus_Type _conversionToApply;

	cityBuildQueue _buildQueue;
};

#endif /* City_H */

/*
*	End Of File : City.h
*/
