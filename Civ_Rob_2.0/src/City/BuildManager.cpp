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

#include "BuildManager.h"

#include "Citizen.h"
#include "CitizenManager.h"
#include "T_City.h"

#include "BuildFactory.h"
#include "IBuildManagerVisitor.h"
#include "IBuild.h"

#include <CEGUI/widgets/PushButton.h>


city::BuildManager::BuildManager
(
	const CitizenManager& citizenManager,
	FoodManager& foodManager,
	const conversionSurplus_Type& conversionToApplyf
)
:
m_citizenManager(citizenManager),
m_foodManager(foodManager),
m_conversionToApply(conversionToApplyf),
m_workBalance(RESOURCES_WORK_ZERO),
m_workSurplusPreviousTurn(RESOURCES_WORK_ZERO),
m_buildQueue()
{
}

city::BuildManager::~BuildManager()
{
	clearDynamicContextBuildToQueue();
}

void city::BuildManager::computeWork()
{
	/* Sum work from citizen */
	m_workBalance = m_citizenManager.getWorkFromCitizen();

	/* Applying Emotion multiplier */
	m_workBalance *= ((double)m_citizenManager.getEmotion() / Citizen::EMOTION_MEAN);

	/* Applying the work which was converted from food in the previous turn */
	m_workBalance += m_workSurplusPreviousTurn;

	/* Reset m_workSurplusPreviousTurn to CITY_ZERO */
	m_workSurplusPreviousTurn = RESOURCES_WORK_ZERO;
}

void
city::BuildManager
::computeWorkToBuild(bool& needToUpdateDrawUnit)
{
	bool loopContinue{ true };
	double loopComputeWork{ m_workBalance };
	while (!m_buildQueue.empty() && loopContinue)
	{
		std::tie(loopContinue, loopComputeWork) =
			m_buildQueue.front().buildQ->computeWorkToBuild(loopComputeWork);

		if (loopContinue)
		{
			removeBuildToQueueFront();
			needToUpdateDrawUnit = true;
		}
	}
}

void city::BuildManager::convertFoodSurplusToWork
(
	const double foodSurplus
)
{
	m_workSurplusPreviousTurn = foodSurplus * FOOD_TO_WORK;
}

void city::BuildManager::addBuildToQueue
(
	const buildGUI& buildToQueue
)
{
	m_buildQueue.push_back(std::move(buildToQueue));
}

void city::BuildManager::removeBuildToQueueFront()
{
	if (m_buildQueue.front().buildG != nullptr)
	{
		m_buildQueue.front().buildG->destroy();
		m_buildQueue.front().buildG = nullptr;
	}
	m_buildQueue.pop_front();
}

void city::BuildManager::removeBuildToQueue
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

void city::BuildManager::clearDynamicContextBuildToQueue()
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

double city::BuildManager::GETBuildPerc()const
{
	if (!m_buildQueue.empty())
	{
		return m_buildQueue.front().buildQ->getRemainingWorkoverWork();
	}
	return RESOURCES_WORK_ZERO;
};

void
city::BuildManager
::accept(IBuildManagerVisitor& visitor) const
{
	visitor.visit(*this);
}