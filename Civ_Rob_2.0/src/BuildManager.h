/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2024 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.12.4
	file version : 1.4

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

#ifndef BuildManager_H
#define BuildManager_H

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"
#include "T_CityScreen.h"
#include "T_City.h"
#include "T_Unit.h"
#include "CitizenManager.h"
#include "FoodManager.h"


class BuildManager
{
public:

	BuildManager
	(
		const CitizenManager& citizenManager,
		FoodManager& foodManager,
		const unsigned int& x,
		const unsigned int& y,
		const conversionSurplus_Type& conversionToApplyf
	);
	~BuildManager();

public:


	/* ----------------------------------------------------------------------------------- */
	/* NAME : computeWork																   */
	/* ROLE : Calculate the work for the turn											   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	void computeWork();

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
	void computeWorkToBuild
	(
		Player& player,
		const VectUnitTemplate& vectUnitTemplate,
		bool* needToUpdateDrawUnit
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : convertWorkSurplusToFood													   */
	/* ROLE : Convert food to work ; Place in m_workSurplusPreviousTurn					   */
	/* INPUT : double workSurplus : food surplus to convert into work					   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	void convertFoodSurplusToWork
	(
		const double foodSurplus
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
	void addBuildToQueue
	(
		const buildGUI& buildToQueue
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : removeBuildToQueueFront													   */
	/* ROLE : Pop build to buildQueue													   */
	/* IN/OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	void removeBuildToQueueFront();

	/* ----------------------------------------------------------------------------------- */
	/* NAME : removeBuildToQueue														   */
	/* ROLE : remove build to buildQueue at index										   */
	/* IN/OUT : DequeButtonTexte& : Deque of ButtonTexte for BuildQueue					   */
	/* IN : unsigned int index : index to remove										   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	void removeBuildToQueue
	(
		const size_t index
	);

	void clearDynamicContextBuildToQueue();

	double GETBuildPerc()const;
	double getWorkBalance()const			{ return m_workBalance; };

	dequeBuild& getBuildQueue()				{ return m_buildQueue; };
	const dequeBuild& getBuildQueue()const	{ return m_buildQueue; };
	

private:

	const CitizenManager& m_citizenManager;
	FoodManager& m_foodManager;
	const unsigned int& m_x;
	const unsigned int& m_y;
	const conversionSurplus_Type& m_conversionToApply;

	double m_workBalance;
	double m_workSurplusPreviousTurn;

	dequeBuild m_buildQueue;
};


#endif /* BuildManager_H */

/*
*	End Of File : BuildManager.h
*/
