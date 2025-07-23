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
#include "T_City.h"
#include "../Player.h"
#include "../Unit/Unit.h"

#include "BuildFactory.h"
#include "BuildUnit.h"

#include <jsoncons/json.hpp>
#include <CEGUI/widgets/PushButton.h>

city::BuildManager::BuildManager
(
	const CitizenManager& citizenManager,
	FoodManager& foodManager,
	const R2D::Coor& coor,
	const conversionSurplus_Type& conversionToApplyf
)
:
m_citizenManager(citizenManager),
m_foodManager(foodManager),
m_coor(coor),
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

void city::BuildManager::computeWorkToBuild
(
	PlayerPtrT& player,
	bool& needToUpdateDrawUnit
)
{
	bool loopContinue{ true };
	double loopComputeWork{ m_workBalance };
	while (!m_buildQueue.empty() && loopContinue)
	{
		std::tie(loopContinue, loopComputeWork) =
			m_buildQueue.front().buildQ->computeWorkToBuild(loopComputeWork, player, m_coor);

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
	if (m_buildQueue.empty() == CONTAINERS::NOT_EMPTY)
	{
		return m_buildQueue.front().buildQ->getRemainingWorkoverWork();
	}
	return RESOURCES_WORK_ZERO;
};

jsoncons::ojson city::BuildManager::saveToOjson()const
{
	jsoncons::ojson value;
	jsoncons::ojson builds{ jsoncons::ojson::make_array() };

	for (const auto& build : m_buildQueue)
	{
		jsoncons::ojson b;
		build.buildQ->save(b);
		builds.push_back(b);
	}

	value.insert_or_assign("m_workBalance", m_workBalance);
	value.insert_or_assign("m_workSurplusPreviousTurn", m_workSurplusPreviousTurn);
	value.insert_or_assign("m_buildQueue", builds);

	return value;
}

void city::BuildManager::loadFromOjson(const jsoncons::ojson& jsonLoad)
{
	if	(
			jsonLoad.contains("m_workBalance") && jsonLoad.contains("m_workSurplusPreviousTurn") && jsonLoad.contains("m_buildQueue") &&
			jsonLoad["m_buildQueue"].is_array()
		)
	{
		m_workBalance = jsonLoad["m_workBalance"].as<double>();
		m_workSurplusPreviousTurn = jsonLoad["m_workSurplusPreviousTurn"].as<double>();

		for (const auto& build : jsonLoad["m_buildQueue"].array_range())
		{
			buildGUI buildToQueue;
			buildToQueue.buildQ = std::move(BuildFactory::createBuild(build));
			m_buildQueue.push_back(std::move(buildToQueue));
		}
	}
}