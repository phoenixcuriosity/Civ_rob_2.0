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

#ifndef City_H
#define City_H

#include "LIB.h"

#include "BuildManager.h"
#include "T_City.h"
#include "T_MainMap.h"

#include "R2D/src/API_fwd.h"

#include <jsoncons/json.hpp>

class City
{
public: /* STATIC */

	/**
	 * Create a City from a Settler on the map
	 * @param[in,out]	mainGame MainGame object to add the City from the settler position
	 * @param[in] influenceLevel Optional : Level of influence, default value CITY_INFLUENCE::MIN_INFLUENCE_LEVEL
	 */
	static void createCity
	(
		GamePlayScreen& mainGame,
		const unsigned int influenceLevel = CITY_INFLUENCE::MIN_INFLUENCE_LEVEL
	);

	/**
	 * Fill the tabtile from mainmap
	 * @param[in]		  window x and y screen size
	 * @param[in]	 middletileX X index from mainmap
	 * @param[in]	 middletileY Y index from mainmap
	 * @param[in]	selectplayer Selected player index to create the City
	 * @param[in,out]	 mainMap Main map values to copy from
	 * @param[out]       tabtile City tile to copy to
	 * @param[in] influenceLevel Optional : Level of influence, default value CITY_INFLUENCE::MIN_INFLUENCE_LEVEL
	 */
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

	/**
	 * Condition to fill to create a City
	 * @param[in]			   o X index from mainmap
	 * @param[in]			   p Y index from mainmap
	 * @param[in] influenceLevel Optional : Level of influence, default value CITY_INFLUENCE::MIN_INFLUENCE_LEVEL
	 * @return false if invalid
	 * @return  true if valid
	 */
	static bool initSizeInfluenceCondition
	(
		const int o,
		const int p,
		const unsigned int influenceLevel = CITY_INFLUENCE::MIN_INFLUENCE_LEVEL
	);

	/**
	 * Condition to validate a corner to create a City
	 * @param[in]			   o X index from mainmap
	 * @param[in]			   p Y index from mainmap
	 * @param[in] influenceLevel Level of influence
	 * @return false if invalid
	 * @return  true if valid
	 */
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

	/**
	 * Constructor
	 * @param[in]  name Name of the City to create
	 * @param[in]	  x x tile
	 * @param[in]     y y tile
	 * @param[in] tiles The City tiles from the MainMap
	 */
	City
	(
		const std::string& name,
		unsigned int x,
		unsigned int y,
		VectMap& tiles
	);

	/**
	 * Destructor
	 */
	virtual ~City();

	/**
	 * Compute the current City food stock
	 * @param[in] goldStats Gold from the player, can be used from gold to food conversion
	 */
	virtual void computefood
	(
		GoldStats& goldStats
	);

	/**
	 * Compute the current City work stock
	 * @param[out]               player The player, can be used from gold to work conversion
	 * @param[in]      vectUnitTemplate Template of all Unit
	 * @param[out] needToUpdateDrawUnit True if the City is created, else false
	 */
	virtual void computeWork
	(
		Player& player,
		const VectUnitTemplate& vectUnitTemplate,
		bool* needToUpdateDrawUnit
	);

	/**
	 * Search if the City is at those coor
	 * @param[in] indexX x tile
	 * @param[in] indexY y tile
	 * @return  true if the City is at those coor, else false
	 */
	virtual bool searchCityTile
	(
		const unsigned int indexX,
		const unsigned int indexY
	);

public:

	/**
	 * Search if the City is at those coor
	 * @param[in] indexX x tile
	 * @param[in] indexY y tile
	 * @return  true if the City is at those coor, else false
	 */
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

	jsoncons::ojson saveToOjson();
	
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
