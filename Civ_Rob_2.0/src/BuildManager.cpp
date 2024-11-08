﻿/*

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

#include "BuildManager.h"
#include "T_City.h"
#include "Player.h"
#include "Unit.h"
#include "T_CityScreen.h"
#include "T_Unit.h"


namespace RESOURCES
{
	namespace WORK
	{
		const double ZERO = 0.0;
	}
}


BuildManager::BuildManager
(
	const CitizenManager& citizenManager,
	FoodManager& foodManager,
	const unsigned int& x,
	const unsigned int& y,
	const conversionSurplus_Type& conversionToApplyf
)
: 
m_citizenManager(citizenManager),
m_foodManager(foodManager),
m_x(x),
m_y(y),
m_conversionToApply(conversionToApplyf),
m_workBalance(RESOURCES::WORK::ZERO),
m_workSurplusPreviousTurn(RESOURCES::WORK::ZERO),
m_buildQueue()
{
}

BuildManager::~BuildManager()
{
	clearDynamicContextBuildToQueue();
}


/* ----------------------------------------------------------------------------------- */
/* NAME : computeWork																   */
/* ROLE : Calculate the work for the turn											   */
/* INPUT : void																		   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void BuildManager::computeWork()
{
	/* Sum work from citizen */
	m_workBalance = m_citizenManager.getWorkFromCitizen();

	/* Applying Emotion multiplier */
	m_workBalance *= ((double)m_citizenManager.getEmotion() / EMOTION_RANGE::SCALE_MEAN);

	/* Applying the work which was converted from food in the previous turn */
	m_workBalance += m_workSurplusPreviousTurn;

	/* Reset m_workSurplusPreviousTurn to CITY_ZERO */
	m_workSurplusPreviousTurn = RESOURCES::WORK::ZERO;
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
void BuildManager::computeWorkToBuild
(
	Player& player,
	const VectUnitTemplate& vectUnitTemplate,
	bool* needToUpdateDrawUnit
)
{
	if (!m_buildQueue.empty())
	{
		/* Decrease by m_workBalance the amont of the remainingWork to build */
		m_buildQueue.front().buildQ.remainingWork -= m_workBalance;

		double workSurplus(RESOURCES::WORK::ZERO);
		while (m_buildQueue.front().buildQ.remainingWork < RESOURCES::WORK::ZERO)
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
					vectUnitTemplate[unitToBuild].numberOfAttack,
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
				m_foodManager.convertWorkSurplusToFood(workSurplus);
				return;
			}
		}
	}
}


/* ----------------------------------------------------------------------------------- */
/* NAME : convertWorkSurplusToFood													   */
/* ROLE : Convert food to work ; Place in m_workSurplusPreviousTurn					   */
/* INPUT : double workSurplus : food surplus to convert into work					   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void BuildManager::convertFoodSurplusToWork
(
	const double foodSurplus
)
{
	m_workSurplusPreviousTurn = foodSurplus * MULTIPLIER::CONVERSION::FOOD_TO_WORK;
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
void BuildManager::addBuildToQueue
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
void BuildManager::removeBuildToQueueFront()
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
void BuildManager::removeBuildToQueue
(
	const size_t index
)
{
	if (m_buildQueue[index].buildG != nullptr)
	{
		m_buildQueue[index].buildG->destroy();
		m_buildQueue[index].buildG = nullptr;
	}
	m_buildQueue.erase(m_buildQueue.begin() + index);
}

void BuildManager::clearDynamicContextBuildToQueue()
{
	for (auto& button : m_buildQueue)
	{
		if (button.buildG != nullptr)
		{
			button.buildG->destroy();
			button.buildG = nullptr;
		}
	}
}

double BuildManager::GETBuildPerc()const
{
	if (m_buildQueue.empty() == CONTAINERS::NOT_EMPTY)
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
				* PERCENTAGE::ONE_HUNDRED
				);
	}
	return RESOURCES::WORK::ZERO;
};



/*
*	End Of File : BuildManager.cpp
*/