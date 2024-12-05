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

#include "InitLoadFromFile.h"

#include "jsonloader.h"
#include "LogSentences.h"
#include "MainMap.h"
#include "T_Unit.h"
#include "XmlConvertValue.h"

#include <tinyxml2/tinyxml2.h>

#include <R2D/src/ResourceManager.h> 
#include <R2D/src/Log.h> 
#include <R2D/src/tinyXml2.h> 

void InitLoadFromFile::loadMainMapConfig(MainMap& mainMap)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_MAINMAP_CONFIG, logS::DATA::START);

	try 
	{
		const std::string text{ R2D::ResourceManager::loadFileToString(R2D::ResourceManager::getFile(R2D::e_Files::mainMap)->getPath()) };

		const jsoncons::ojson configuration = jsoncons::ojson::parse(text);

		if (configuration.contains(jsonloader::KEY_MAP))
		{
			mainMap.SETMainMapConfig(configuration[jsonloader::KEY_MAP].as<MainMapConfig>());
		}
		else
		{
			LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_MAINMAP_CONFIG, logS::DATA::MISSING_KEY_JSON,
				R2D::ResourceManager::getFile(R2D::e_Files::mainMap)->getPath(), jsonloader::KEY_MAP);
		}
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_MAINMAP_CONFIG, logS::DATA::ERROR_KEY_JSON, e.what());
	}
	
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_MAINMAP_CONFIG, logS::DATA::END);
}

void InitLoadFromFile::initFromFile(VectUnitTemplate& vectUnitTemplate, VectCityName& vectCityName)
{
	loadUnitAndSpec(vectUnitTemplate);
	loadCitiesNames(vectCityName);
}


void InitLoadFromFile::loadUnitAndSpec(VectUnitTemplate& vectUnitTemplate)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_UNIT_CONFIG, logS::DATA::START);
	try
	{
		const std::string text{ R2D::ResourceManager::loadFileToString(R2D::ResourceManager::getFile(R2D::e_Files::units)->getPath()) };

		const jsoncons::json configuration = jsoncons::json::parse(text);

		if (configuration.contains(jsonloader::KEY_UNIT_TEMPLATE))
		{
			const std::vector<jsonloader::Unit_Template> units = configuration[jsonloader::KEY_UNIT_TEMPLATE].as<std::vector<jsonloader::Unit_Template>>();

			Unit_Template currentUnit;
			for (const auto& unit : units)
			{
				currentUnit.name = unit.name;
				currentUnit.type = XmlConvertValue::xmlGiveMovementType(unit.type);
				currentUnit.life = unit.life;
				currentUnit.atq = unit.atq;
				currentUnit.def = unit.def;
				currentUnit.movement = unit.movement;
				currentUnit.numberOfAttack = unit.numberOfAttack;
				currentUnit.level = unit.level;
				currentUnit.workToBuild = unit.workToBuild;
				currentUnit.maintenance = unit.maintenance;

				vectUnitTemplate.push_back(currentUnit);
			}
		}
		else
		{
			LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_UNIT_CONFIG, logS::DATA::MISSING_KEY_JSON,
				R2D::ResourceManager::getFile(R2D::e_Files::units)->getPath(), jsonloader::KEY_UNIT_TEMPLATE);
		}
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_UNIT_CONFIG, logS::DATA::ERROR_KEY_JSON, e.what());
	}
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_UNIT_CONFIG, logS::DATA::END);
}

void InitLoadFromFile::loadCitiesNames(VectCityName& vectCityName)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_CITY_NAME, logS::DATA::START);

	const std::string text{ R2D::ResourceManager::loadFileToString(R2D::ResourceManager::getFile(R2D::e_Files::citiesNames)->getPath()) };

	const jsoncons::json configuration = jsoncons::json::parse(text);

	for (const auto& country : configuration.object_range()) 
	{
		for (const auto& city : country.value().array_range())
		{
			vectCityName.push_back(city.as_string());
		}
	}

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_CITY_NAME, logS::DATA::END);
}