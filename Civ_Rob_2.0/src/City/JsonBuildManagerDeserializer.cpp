#include "JsonBuildManagerDeserializer.h"

#include "BuildFactory.h"
#include "BuildManager.h"
#include "../Player.h"

void
city::JsonBuildManagerDeserializer
::deserialize(const jsoncons::ojson& input, BuildManager& buildManager, std::shared_ptr<Player>& owner) const
{
	if (
		input.contains("m_workBalance") && input.contains("m_workSurplusPreviousTurn") && input.contains("m_buildQueue") &&
		input["m_buildQueue"].is_array()
		)
	{
		buildManager.m_workBalance = input["m_workBalance"].as<double>();
		buildManager.m_workSurplusPreviousTurn = input["m_workSurplusPreviousTurn"].as<double>();

		for (const auto& build : input["m_buildQueue"].array_range())
		{
			BuildManager::buildGUI buildToQueue;
			buildToQueue.buildQ = std::move(BuildFactory::createBuild(build, owner));
			buildManager.m_buildQueue.push_back(std::move(buildToQueue));
		}
	}
}

