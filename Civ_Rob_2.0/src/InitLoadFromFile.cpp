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

	tinyxml2::XMLDocument config{};
	config.LoadFile(R2D::ResourceManager::getFile(R2D::e_Files::mainMap)->getPath().c_str());
	unsigned int tmp{ 0 };

	if (config.ErrorID() == 0)
	{
		tinyxml2::XMLElement* node = R2D::tinyXml2::getFirstElement(config);

		if (nullptr != node)
		{
			node->QueryUnsignedText(&tmp);
			mainMap.SETtileSize(tmp);
		}
		node = node->NextSiblingElement();

		if (nullptr != node)
		{
			node->QueryUnsignedText(&tmp);
			mainMap.SETmapSizePixX(tmp);
		}
		node = node->NextSiblingElement();

		if (nullptr != node)
		{
			node->QueryUnsignedText(&tmp);
			mainMap.SETmapSizePixY(tmp);
		}
	}
	else
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::OPEN_FILE, logS::DATA::ERROR_OPEN_FILE, 
			R2D::ResourceManager::getFile(R2D::e_Files::mainMap)->getPath());
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
	tinyxml2::XMLDocument texteFile{};

	texteFile.LoadFile(R2D::ResourceManager::getFile(R2D::e_Files::units)->getPath().c_str());

	const char* root("Root");

	const char* s_Unit("Unit"),
		* s_Name("Name"),
		* s_MovementType("MovementType"),
		* s_Life("Life"),
		* s_Atq("Atq"),
		* s_Def("Def"),
		* s_Mouvement("Mouvement"),
		* s_NumberOfAttack("NumberOfAttack"),
		* s_Level("Level"),
		* s_WorkToBuild("WorkToBuild"),
		* s_Maintenance("Maintenance");

	tinyxml2::XMLNode* node(texteFile.FirstChildElement(root)->FirstChildElement(s_Unit));
	Unit_Template currentUnit;

	while (nullptr != node)
	{
		currentUnit.name = node->FirstChildElement(s_Name)->GetText();
		currentUnit.type = XmlConvertValue::xmlGiveMovementType(node->FirstChildElement(s_MovementType)->GetText());
		node->FirstChildElement(s_Life)->QueryIntText((int*)&currentUnit.life);
		node->FirstChildElement(s_Atq)->QueryIntText((int*)&currentUnit.atq);
		node->FirstChildElement(s_Def)->QueryIntText((int*)&currentUnit.def);
		node->FirstChildElement(s_Mouvement)->QueryIntText((int*)&currentUnit.movement);
		node->FirstChildElement(s_NumberOfAttack)->QueryIntText((int*)&currentUnit.numberOfAttack);
		node->FirstChildElement(s_Level)->QueryIntText((int*)&currentUnit.level);
		node->FirstChildElement(s_WorkToBuild)->QueryDoubleText((double*)&currentUnit.workToBuild);
		node->FirstChildElement(s_Maintenance)->QueryDoubleText((double*)&currentUnit.maintenance);

		vectUnitTemplate.push_back(currentUnit);

		node = node->NextSibling();
	}
}

void InitLoadFromFile::loadCitiesNames(VectCityName& vectCityName)
{
	unsigned int nbcity{ 0 };
	std::string city{ STRINGS::EMPTY }, dummy{ STRINGS::EMPTY };
	std::ifstream CITIENAME{ R2D::ResourceManager::getFile(R2D::e_Files::citiesNames)->getPath() };


	if (CITIENAME)
	{
		CITIENAME >> dummy;

		CITIENAME >> nbcity;
		vectCityName.resize(nbcity);

		for (auto& c : vectCityName)
		{
			CITIENAME >> c;
		}
	}
	else
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::OPEN_FILE, logS::DATA::ERROR_OPEN_FILE,
			R2D::ResourceManager::getFile(R2D::e_Files::citiesNames)->getPath());
	}
}