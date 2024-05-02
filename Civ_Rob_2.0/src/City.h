/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2024 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.14.2
	file version : 1.33

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

#include "T_City.h"
#include "T_CityScreen.h"

#include "MainMap.h"
#include "Unit.h"
#include "Citizen.h"
#include "FoodManager.h"
#include "CitizenManager.h"
#include "BuildManager.h"

#include <vector>
#include <queue>
#include <memory>

#include <R2D/src/Window.h>
#include <R2D/src/GUI.h>





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
		const unsigned int influenceLevel = CITY_INFLUENCE::MIN_INFLUENCE_LEVEL
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
		const R2D::Window& window,
		const unsigned int middletileX,
		const unsigned int middletileY,
		const unsigned int selectplayer,
		MainMap& mainMap,
		VectMap& tabtile,
		const unsigned int influenceLevel = CITY_INFLUENCE::MIN_INFLUENCE_LEVEL
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
		const int o,
		const int p,
		const unsigned int influenceLevel = CITY_INFLUENCE::MIN_INFLUENCE_LEVEL
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
		const int o,
		const int p,
		const unsigned int influenceLevel
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
	/* NAME : computefood																   */
	/* ROLE : Calcul et application du niveau de Food pour le prochain tour				   */
	/* OUT : GoldStats& goldStats : Player gold stats									   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void computefood
	(
		GoldStats& goldStats
	);

	virtual void computeWork
	(
		Player& player,
		const VectUnitTemplate& vectUnitTemplate,
		bool* needToUpdateDrawUnit
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : searchCityTile															   */
	/* ROLE : Recherche la case de la City et renvoie vers cityMap						   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual bool searchCityTile
	(
		const unsigned int indexX,
		const unsigned int indexY
	);

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
		const unsigned int x,
		const unsigned int y
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
	/* NAME : convertFoodSurplusToGold													   */
	/* ROLE : Convert food to gold ; Place in goldStats.goldConversionSurplus			   */
	/* INPUT : double workSurplus : food surplus to convert into work					   */
	/* OUT : GoldStats& goldStats : gold surplus conversion								   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void convertFoodSurplusToGold
	(
		const double foodSurplus,
		GoldStats& goldStats
	);

public:

	/* INTERFACE */

	void addBuildToQueue(const buildGUI& buildToQueue)	{ m_buildManager.addBuildToQueue(buildToQueue); };
	void removeBuildToQueue(const size_t index)			{ m_buildManager.removeBuildToQueue(index); };
	void clearDynamicContextBuildToQueue()				{ m_buildManager.clearDynamicContextBuildToQueue(); };
	double GETBuildPerc()const							{ return m_buildManager.GETBuildPerc(); };

	void addCitizen(bool uselessArg)					{ m_citizenManager.addCitizen(uselessArg); };
	void resetTabCitizen()								{ m_citizenManager.resetTabCitizen(); };
	void computeEmotion()								{ m_citizenManager.computeEmotion(); };
	
public:
	/* *********************************************************
	 *				City::METHODS::GET/SET					   *
	 ********************************************************* */

	/* const & */

	inline virtual const std::string& GETimage()const		{ return m_image; };
	inline virtual const std::string& GETname()const		{ return m_name; };
	inline virtual const VectMap& GETtile()const			{ return m_tile; };
	inline virtual const VectCitizen& GETcitizens()const	{ return m_citizenManager.getCitizens(); };
	inline virtual const FoodManager& GETFoodManager()const { return m_foodManager; };
	inline virtual const CitizenManager& GETCitizenManager()const { return m_citizenManager; };
	inline virtual const dequeBuild& GETbuildQueue()const	{ return m_buildManager.getBuildQueue(); };

	/* & */

	inline virtual dequeBuild& GETbuildQueue() { return m_buildManager.getBuildQueue(); };

	/* implicit const */

	inline virtual size_t GETnbpop()const					{ return m_citizenManager.getCitizens().size(); };
	inline virtual unsigned int GETx()const					{ return m_x; };
	inline virtual unsigned int GETy()const					{ return m_y; };
	inline virtual unsigned int GETinfluenceLevel()const	{ return m_influenceLevel; };
	inline virtual unsigned int GETatq()const				{ return m_atq; };
	inline virtual unsigned int GETdef()const				{ return m_def; };
	inline virtual unsigned int GETemotion()const			{ return m_citizenManager.getEmotion(); };
	inline virtual unsigned int GETnbstructurebuild()const	{ return m_nbstructurebuild; };
	inline virtual double GETfoodStock()const				{ return m_foodManager.getFoodStock(); };
	inline virtual double GETfoodBalance()const				{ return m_foodManager.getFoodBalanceForConversion(); };
	inline virtual double GETfoodSurplusPreviousTurn()const { return m_foodManager.getFoodSurplusPreviousTurn(); };
	inline virtual double GETfoodToLevelUp()const			{ return m_foodManager.getFoodToLevelUp(); };
	inline virtual double GETgoldBalance()const				{ return m_goldBalance; };
	inline virtual conversionSurplus_Type GETconversionToApply()const { return m_conversionToApply; };

	inline virtual void SETimage(std::string image) { m_image = image; };
	inline virtual void SETname(std::string name) { m_name = name; };
	inline virtual void SETx(unsigned int x) { m_x = x; };
	inline virtual void SETy(unsigned int y) { m_y = y; };
	inline virtual void SETtile(VectMap& tile) { m_tile = tile; };
	//inline virtual void SETcitizens(VectCitizen& citizens) { m_citizens = citizens; };
	inline virtual void SETinfluenceLevel(unsigned int influenceLevel) { m_influenceLevel = influenceLevel; };
	inline virtual void SETatq(unsigned int atq) { m_atq = atq; };
	inline virtual void SETdef(unsigned int def) { m_def = def; };
	inline virtual void SETemotion(unsigned int emotion) { m_citizenManager.setEmotion(emotion); };
	inline virtual void SETnbstructurebuild(unsigned int nbstructurebuild) { m_nbstructurebuild = nbstructurebuild; };
	inline virtual void SETfoodStock(double foodStock) { m_foodManager.setFoodStock(foodStock); };
	inline virtual void SETfoodBalance(double foodBalance) { m_foodManager.setFoodBalance(foodBalance); };
	inline virtual void SETfoodSurplusPreviousTurn(double foodSurplusPreviousTurn) { m_foodManager.setFoodSurplusPreviousTurn(foodSurplusPreviousTurn); };
	inline virtual void SETfoodToLevelUp(double foodToLevelUp) { m_foodManager.setFoodToLevelUp(foodToLevelUp); };
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
	unsigned int m_influenceLevel;
	unsigned int m_atq;
	unsigned int m_def;
	unsigned int m_nbstructurebuild;

	conversionSurplus_Type m_conversionToApply;

	CitizenManager m_citizenManager;
	FoodManager m_foodManager;
	BuildManager m_buildManager;

	double m_goldBalance;
};




#endif /* City_H */

/*
*	End Of File : City.h
*/
