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

#include "SaveReload.h"

#include "App.h"
#include "Citizen.h"
#include "City.h"
#include "GamePlayScreen.h"
#include "LogSentences.h"
#include "MainMap.h"
#include "NewGameScreen.h"
#include "Player.h"
#include "Unit.h"
#include "T_Unit.h"
#include "XmlConvertValue.h"

#include <jsoncons/json.hpp>
#include <R2D/src/ResourceManager.h> 
#include <R2D/src/ErrorLog.h> 
#include <R2D/src/ExitFromError.h> 
#include <R2D/src/Log.h> 

#include <filesystem>
#include <algorithm> // For std::max_element
#include <execution> // For std::execution::par

namespace SAVE
{
	constexpr size_t OFFSET_INDEX = 1;
}

void SaveReload::init()
{
	const std::string filePath{ R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath() };
	if (std::filesystem::exists(filePath) && std::filesystem::is_directory(filePath))
	{
		for (const auto& entry : std::filesystem::directory_iterator(filePath))
		{
			if (entry.is_directory())
			{
				m_tabSave.push_back(std::stoul(entry.path().stem().string()));
			}
		}
	}
}

void SaveReload::save
(
	GamePlayScreen& mainGame
)
{
	saveMaps(mainGame);
	savePlayer(mainGame);
}

void SaveReload::saveMaps
(
	GamePlayScreen& mainGame
)
{
	try
	{
		std::ofstream ofs{ std::format("{}{:04}/{}",
			R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(),
			mainGame.getSaveReload()->GETcurrentSave(),
				R2D::ResourceManager::getFile(R2D::e_Files::saveMaps)->getPath() )};

		if (!ofs) { throw std::runtime_error("Failed to open file for writing."); }
	
		jsoncons::encode_json(mainGame.GETmainMap().saveToOjson(), ofs, jsoncons::indenting::indent);
			}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::OPEN_FILE, logS::DATA::ERROR_OPEN_FILE,
			e.what());
	}
}

void SaveReload::savePlayer
(
	GamePlayScreen& mainGame
)
{
	try
	{
		std::ofstream ofs((std::format("{}{:04}/{}",
			R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(),
			mainGame.getSaveReload()->GETcurrentSave(),
			R2D::ResourceManager::getFile(R2D::e_Files::savePlayers)->getPath()).c_str()));

		if (!ofs) { throw std::runtime_error("Failed to open file for writing."); }

		jsoncons::encode_json(mainGame.GETPlayers().saveToOjson(), ofs, jsoncons::indenting::indent);
		}
	catch (const std::exception& e)
		{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::OPEN_FILE, logS::DATA::ERROR_OPEN_FILE,
			e.what());
			}
	}
	
void SaveReload::reload
(
	GamePlayScreen& mainGame
)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::RELOAD, logS::DATA::START);

	loadMaps(mainGame);
	loadPlayer(mainGame);

	mainGame.GETvar().cinState = CinState_Type::cinMainMap;
	mainGame.GETPlayers().SETselectedPlayerId(SELECTION::NO_PLAYER_SELECTED);
	
	mainGame.makePlayersButtons();
	mainGame.GETmainMap().initMainMapTexture(mainGame.GETscreen().m_idTexture);

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::RELOAD, logS::DATA::END);
}

void SaveReload::loadMaps
(
	GamePlayScreen& mainGame
)
{
	std::string input(STRINGS::EMPTY);

	std::ifstream saveMaps(std::format("{}{:04}/{}",
		R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(),
		mainGame.getSaveReload()->GETcurrentSave(),
		R2D::ResourceManager::getFile(R2D::e_Files::saveMaps)->getPath()));
	if (saveMaps)
	{
		for (unsigned int i = 0; i < mainGame.GETmainMap().GETmatriceMap().size(); i++)
		{
			for (unsigned int j = 0; j < mainGame.GETmainMap().GETmatriceMap()[i].size(); j++)
			{
				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].indexX = (unsigned int)std::stoul(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].indexY = (unsigned int)std::stoul(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].tile_x = std::stoul(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].tile_y = std::stoul(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].tile_ground = (Ground_Type)std::stoul(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].tile_spec = (GroundSpec_Type)std::stoul(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].appartenance = std::stoi(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].food = (int)std::stoi(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].work = (int)std::stoi(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].gold = (int)std::stoi(input);
			}
		}
	}
	else
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::OPEN_FILE, logS::DATA::ERROR_OPEN_FILE,
			std::format("{}{:04}/{}",
				R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(),
				mainGame.getSaveReload()->GETcurrentSave(),
				R2D::ResourceManager::getFile(R2D::e_Files::saveMaps)->getPath()));
	}
}

void SaveReload::loadPlayer
(
	GamePlayScreen& mainGame
)
{
	std::string errCheck(STRINGS::EMPTY);
	tinyxml2::XMLDocument xmlDoc;
	
	if (xmlDoc.LoadFile(std::format("{}{:04}/{}",
		R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(),
		mainGame.getSaveReload()->GETcurrentSave(),
		R2D::ResourceManager::getFile(R2D::e_Files::savePlayers)->getPath()).c_str()) == tinyxml2::XML_SUCCESS)
	{
		tinyxml2::XMLNode* pRoot = xmlDoc.FirstChild();
		if (nullptr == pRoot) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : pRoot == nullptr");

		tinyxml2::XMLNode* nPlayer = pRoot->FirstChild();
		errCheck = nPlayer->Value();
		if (errCheck.compare("Player") != STRINGS::IDENTICAL) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : nPlayer != Player");

		while (nullptr != nPlayer)
		{
			tinyxml2::XMLNode* nName		= nPlayer->FirstChild();
			tinyxml2::XMLNode* nID			= nName->NextSibling();
			tinyxml2::XMLNode* nGoldStats	= nID->NextSibling();
			tinyxml2::XMLNode* nTabUnit		= nGoldStats->NextSibling();
			tinyxml2::XMLNode* nTabCity		= nTabUnit->NextSibling();

			if (nullptr == nName) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : nName == nullptr");
			errCheck = nName->Value();
			if (errCheck.compare("Name") != STRINGS::IDENTICAL) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : nName != Name");

			mainGame.GETPlayers().GETvectPlayer().push_back
				(
					std::make_shared<Player>
					(
						nName->FirstChild()->Value(),
						std::stoul(nID->FirstChild()->Value())
					)
				);
			mainGame.GETPlayers().SETselectedPlayerId((int)mainGame.GETPlayers().GETvectPlayer().size() - 1);
			mainGame.GETPlayers().SETselectedPlayerPtr(mainGame.GETPlayers().GETvectPlayer()[(int)mainGame.GETPlayers().GETvectPlayer().size() - 1]);

			/* Set Player name in vectPlayerName */
			mainGame.getUserInputNewGame()->vectPlayerName.push_back(nName->FirstChild()->Value());

			loadGoldStatsXML
			(
				mainGame.GETPlayers().GETvectPlayer()[mainGame.GETPlayers().GETvectPlayer().size() - 1]->GETgoldStats(),
				nGoldStats
			);

			//L10:
			if (nullptr != nTabUnit)
			{
				errCheck = nTabUnit->Value();
				if (errCheck.compare("TabUnit") != STRINGS::IDENTICAL)
				{
					nTabCity = nTabUnit;
					nTabUnit = nullptr;
					goto L20;
				}
				if (errCheck.compare("TabUnit") != STRINGS::IDENTICAL) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : nTabUnit != TabUnit");

				tinyxml2::XMLNode* nUnit = nTabUnit->FirstChild();
				if (nullptr != nUnit)
				{
					errCheck = nUnit->Value();
					if (errCheck.compare("Unit") != STRINGS::IDENTICAL) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : nUnit != Unit");
				}

				loadUnitXML(mainGame, nUnit);
			}

		L20:
			if (nullptr != nTabCity)
			{


				errCheck = nTabCity->Value();
				if (errCheck.compare("TabCity") != STRINGS::IDENTICAL) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : nTabCity != TabCity");

				tinyxml2::XMLNode* nCity = nTabCity->FirstChild();
				if (nullptr != nCity)
				{
					errCheck = nCity->Value();
					if (errCheck.compare("City") != STRINGS::IDENTICAL) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : nCity != City");
				}

				loadCityXML(mainGame, nCity);
			}


			nPlayer = nPlayer->NextSibling();
		}
	}
	else
	{
		R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : xmlDoc.LoadFile() != tinyxml2::XML_SUCCESS");
	}
}

void SaveReload::loadGoldStatsXML
(
	GoldStats& goldStats,
	tinyxml2::XMLNode* nGoldStats
)
{
	tinyxml2::XMLNode* inputNode;

	inputNode = nGoldStats->FirstChild();
	if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadGoldStatsXML : goldStats->gold == nullptr");
	goldStats.gold = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadGoldStatsXML : goldStats->GoldBalance == nullptr");
	goldStats.goldBalance = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadGoldStatsXML : goldStats->Income == nullptr");
	goldStats.income = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadGoldStatsXML : goldStats->Cost == nullptr");
	goldStats.cost = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadGoldStatsXML : goldStats->TaxIncome == nullptr");
	goldStats.taxIncome = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadGoldStatsXML : goldStats->CommerceIncome == nullptr");
	goldStats.commerceIncome = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadGoldStatsXML : goldStats->GoldConversionSurplus == nullptr");
	goldStats.goldConversionSurplus = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadGoldStatsXML : goldStats->ArmiesCost == nullptr");
	goldStats.armiesCost = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadGoldStatsXML : goldStats->BuildingsCost == nullptr");
	goldStats.buildingsCost = std::stod(inputNode->FirstChild()->Value());
}

void SaveReload::loadUnitXML
(
	GamePlayScreen& mainGame,
	tinyxml2::XMLNode* nUnit
)
{
	tinyxml2::XMLNode* inputNode;
	Unit_Template blankUnitTemp;

	while (nullptr != nUnit)
	{
		PlayerPtrT blankPlayer(mainGame.GETPlayers().GETvectPlayer()[mainGame.GETPlayers().GETselectedPlayerId()]);
		blankPlayer->addEmptyUnit();

		UnitPtrT blankUnit(blankPlayer->GETtabUnit()[(unsigned int)(blankPlayer->GETtabUnit().size() - 1)]);
		blankUnit->SETowner(blankPlayer.get());

		inputNode = nUnit->FirstChild();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : Unit->Name == nullptr");
		blankUnit->SETname(inputNode->FirstChild()->Value());

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : Unit->x == nullptr");
		blankUnit->SETx(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : Unit->y == nullptr");
		blankUnit->SETy(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : Unit->movement_type == nullptr");
		blankUnit->SETmovementType(XmlConvertValue::convertUintToUnit_Movement_Type((unsigned int)std::stoul(inputNode->FirstChild()->Value())));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : Unit->life == nullptr");
		blankUnit->SETlife(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : Unit->atq == nullptr");
		blankUnit->SETatq(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : Unit->def == nullptr");
		blankUnit->SETdef(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : Unit->movement == nullptr");
		blankUnit->SETmovement(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : Unit->SETnumberOfAttack == nullptr");
		blankUnit->SETnumberOfAttack(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : Unit->level == nullptr");
		blankUnit->SETlevel(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadPlayer : Unit->maintenance == nullptr");
		blankUnit->SETmaintenance(std::stoul(inputNode->FirstChild()->Value()));

		blankUnitTemp =
			mainGame.GETPlayers().GETvectUnitTemplate()
			[Unit::searchUnitByName(blankUnit->GETname(), mainGame.GETPlayers().GETvectUnitTemplate())];

		blankUnit->SETmaxlife(blankUnitTemp.life);
		blankUnit->SETmaxatq(blankUnitTemp.atq);
		blankUnit->SETmaxdef(blankUnitTemp.def);
		blankUnit->SETmaxmovement(blankUnitTemp.movement);
		blankUnit->SETmaxNumberOfAttack(blankUnitTemp.numberOfAttack);
		blankUnit->SETmaxlevel(blankUnitTemp.level);

		nUnit = nUnit->NextSibling();

		blankPlayer.reset();
		blankUnit.reset();
	}
}

void SaveReload::loadCityXML
(
	GamePlayScreen& mainGame,
	tinyxml2::XMLNode* nCity
)
{
	unsigned int middletileX(0), middletileY(0), influenceLevel(CITY_INFLUENCE::MIN_INFLUENCE_LEVEL);
	std::vector<Tile> tabtile;
	tabtile.resize(CITY_INFLUENCE::INIT_AREA_VIEW);

	tinyxml2::XMLNode* inputNode;
	struct BlankCity
	{
		unsigned int x = 0;
		unsigned int y = 0;
		std::string name = STRINGS::EMPTY;
	};
	BlankCity blankCity;
	build blankBluid;
	CitizenPtrT ptrCitizen;


	PlayerPtrT ptrPlayer(mainGame.GETPlayers().GETselectedPlayerPtr());
	CityPtrT ptrCity;

	while (nullptr != nCity)
	{
		inputNode = nCity->FirstChild();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->Name == nullptr");
		blankCity.name = inputNode->FirstChild()->Value();

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->x == nullptr");
		blankCity.x = std::stoul(inputNode->FirstChild()->Value());

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->y == nullptr");
		blankCity.y = std::stoul(inputNode->FirstChild()->Value());

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->InfluenceLevel == nullptr");
		influenceLevel = std::stoul(inputNode->FirstChild()->Value());

		middletileX = MainMap::convertPosXToIndex(blankCity.x);
		middletileY = MainMap::convertPosYToIndex(blankCity.y);

		City::fillCitieTiles
		(
			mainGame.getParentWindow(),
			middletileX,
			middletileY,
			mainGame.GETPlayers().GETselectedPlayerId(),
			mainGame.GETmainMap(),
			tabtile,
			influenceLevel
		);

		ptrPlayer->addCity(blankCity.name, blankCity.x, blankCity.y, tabtile);

		ptrCity = ptrPlayer->GETtabCity()[(unsigned int)ptrPlayer->GETtabCity().size() - 1];

		ptrCity->SETinfluenceLevel(influenceLevel);

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->Atq == nullptr");
		ptrCity->SETatq(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->Def == nullptr");
		ptrCity->SETdef(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->Emotion == nullptr");
		ptrCity->SETemotion(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->FoodStock == nullptr");
		ptrCity->SETfoodStock(std::stod(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->FoodBalance == nullptr");
		ptrCity->SETfoodBalance(std::stod(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->FoodSurplusPreviousTurn == nullptr");
		ptrCity->SETfoodSurplusPreviousTurn(std::stod(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->FoodToLevelUp == nullptr");
		ptrCity->SETfoodToLevelUp(std::stod(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->GoldBalance == nullptr");
		ptrCity->SETgoldBalance(std::stod(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->ConversionToApply == nullptr");
		conversionSurplus_Type type = XmlConvertValue::convert2ConversionToApply(std::stoi(inputNode->FirstChild()->Value()));
		ptrCity->SETconversionToApply(type);



		tinyxml2::XMLNode* nBuildQueue = inputNode->NextSibling();
		if (nullptr != nBuildQueue)
		{
			tinyxml2::XMLNode* nBuildQueueElement = nBuildQueue->FirstChild();

			while (nullptr != nBuildQueueElement)
			{
				tinyxml2::XMLNode* nBuildQueueElementName = nBuildQueueElement->FirstChild();
				if (nullptr == nBuildQueueElementName) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->nBuildQueue->Name == nullptr");
				blankBluid.name = nBuildQueueElementName->FirstChild()->Value();

				tinyxml2::XMLNode* nBuildQueueElementType = nBuildQueueElementName->NextSibling();
				if (nullptr == nBuildQueueElementType) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->nBuildQueue->Type == nullptr");
				blankBluid.type = XmlConvertValue::convert2build_Type(std::stoi(nBuildQueueElementType->FirstChild()->Value()));

				tinyxml2::XMLNode* nBuildQueueElementWork = nBuildQueueElementType->NextSibling();
				if (nullptr == nBuildQueueElementWork) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->nBuildQueue->Work == nullptr");
				blankBluid.work = std::stod(nBuildQueueElementWork->FirstChild()->Value());

				tinyxml2::XMLNode* nBuildQueueElementRemainingWork = nBuildQueueElementWork->NextSibling();
				if (nullptr == nBuildQueueElementRemainingWork) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->nBuildQueue->RemainingWork == nullptr");
				blankBluid.remainingWork = std::stod(nBuildQueueElementRemainingWork->FirstChild()->Value());


				ptrCity->GETbuildQueue().push_back
					(
						{
							nullptr, /* will be create when call CityScreen::entry */
							blankBluid
						}
					);

				nBuildQueueElement = nBuildQueueElement->NextSibling();
			}
		}


		ptrCity->resetTabCitizen();
		tinyxml2::XMLNode* nTabCitizen = nBuildQueue->NextSibling();
		if (nullptr != nTabCitizen)
		{
			tinyxml2::XMLNode* nTabCitizenElement = nTabCitizen->FirstChild();

			while (nullptr != nTabCitizenElement)
			{
				ptrCity->addCitizen(true);
				ptrCitizen = ptrCity->GETcitizens().back();

				tinyxml2::XMLNode* nTabCitizenElementtileOccupied = nTabCitizenElement->FirstChild();
				if (nullptr == nTabCitizenElementtileOccupied) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->nTabCitizen->tileOccupied == nullptr");
				ptrCitizen->SETtileOccupied(std::stoi(nTabCitizenElementtileOccupied->FirstChild()->Value()));

				tinyxml2::XMLNode* nTabCitizenElementHappiness = nTabCitizenElementtileOccupied->NextSibling();
				if (nullptr == nTabCitizenElementHappiness) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->nTabCitizen->Happiness == nullptr");
				ptrCitizen->SEThappiness(XmlConvertValue::convert2Emotion_Type(std::stoi(nTabCitizenElementHappiness->FirstChild()->Value())));

				tinyxml2::XMLNode* nTabCitizenElementFood = nTabCitizenElementHappiness->NextSibling();
				if (nullptr == nTabCitizenElementFood) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->nTabCitizen->Food == nullptr");
				ptrCitizen->SETfood(std::stoi(nTabCitizenElementFood->FirstChild()->Value()));

				tinyxml2::XMLNode* nTabCitizenElementWork = nTabCitizenElementFood->NextSibling();
				if (nullptr == nTabCitizenElementWork) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->nTabCitizen->Work == nullptr");
				ptrCitizen->SETwork(std::stoi(nTabCitizenElementWork->FirstChild()->Value()));

				tinyxml2::XMLNode* nTabCitizenElementGold = nTabCitizenElementWork->NextSibling();
				if (nullptr == nTabCitizenElementGold) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->nTabCitizen->Gold == nullptr");
				ptrCitizen->SETgold(std::stoi(nTabCitizenElementGold->FirstChild()->Value()));

				tinyxml2::XMLNode* nTabCitizenElementReligion_Type = nTabCitizenElementGold->NextSibling();
				if (nullptr == nTabCitizenElementReligion_Type) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->nTabCitizen->Religion_Type == nullptr");
				ptrCitizen->SETreligion(XmlConvertValue::convert2Religion_Type(std::stoi(nTabCitizenElementReligion_Type->FirstChild()->Value())));

				tinyxml2::XMLNode* nTabCitizenElementplace = nTabCitizenElementReligion_Type->NextSibling();
				if (nullptr == nTabCitizenElementplace) R2D::ExitFromError::exitFromError("[ERROR]___: loadCityXML : City->nTabCitizen->place == nullptr");
				ptrCitizen->SETplace(std::stoi(nTabCitizenElementplace->FirstChild()->Value()));

				nTabCitizenElement = nTabCitizenElement->NextSibling();
			}
		}


		nCity = nCity->NextSibling();
	}
}

void SaveReload::createSave()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_SAVE, logS::DATA::START);

	const auto max_it = std::max_element(std::execution::par, m_tabSave.begin(), m_tabSave.end());
	if (max_it != m_tabSave.end())
	{
		m_currentSave = (*max_it) + SAVE::OFFSET_INDEX;
	}
	else
	{
		m_currentSave = SAVE::OFFSET_INDEX;
	}
	m_tabSave.push_back(m_currentSave);

	createSaveDir();

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_SAVE, logS::DATA::END);
}

void SaveReload::createSaveDir()
{
	const std::string dir{ std::format("{}{:04}", R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(), m_currentSave) };

	if (!std::filesystem::create_directory(dir))
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_DIR, logS::DATA::ERROR_CREATE_DIR, dir);
	}
}

void SaveReload::removeSave()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_SAVE, logS::DATA::START);

	if (isSelectCurrentSave() && isSelectCurrentSaveInTab())
	{
		removeSaveDir(m_currentSave);

		removeIndex(m_currentSave);

		unselectCurrentSave();
	}
	else
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_SAVE, logS::DATA::ERROR_CURRENT_SAVE, m_currentSave);
	}

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_SAVE, logS::DATA::END);
}

void SaveReload::clearSave()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CLEAR_SAVES, logS::DATA::START);

	for (const auto index : m_tabSave)
	{
		removeSaveDir(index);
	}

	m_tabSave.clear();

	unselectCurrentSave();

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CLEAR_SAVES, logS::DATA::END);
}

void SaveReload::removeSaveDir(const size_t index)
{
	const std::string dir{ std::format("{}{:04}", R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(), index) };
	removeSaveFile(dir + "/" + R2D::ResourceManager::getFile(R2D::e_Files::saveMaps)->getPath());
	removeSaveFile(dir + "/" + R2D::ResourceManager::getFile(R2D::e_Files::savePlayers)->getPath());
	removeSaveFile(dir);
}

void SaveReload::removeSaveFile(const std::string& file)
{
	if (!std::filesystem::remove(file))
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_SAVE_FILE, logS::DATA::ERROR_DELETE_SAVE_FILE, file);
	}
	else
	{
		LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_SAVE_FILE, logS::DATA::ERROR_DELETE_SAVE_FILE, file + " successfully remove");
	}
}

void SaveReload::removeIndex(const size_t index)
{
	const auto itFound = std::find(m_tabSave.begin(), m_tabSave.end(), index);
	if (itFound != m_tabSave.end())
	{
		m_tabSave.erase(itFound);
	}
	else
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_SAVE_FILE, logS::DATA::ERROR_ERASE_INDEX, *itFound);
	}
}

void SaveReload::unselectCurrentSave()
{
	m_currentSave = SELECTION::NO_CURRENT_SAVE_SELECTED;
}

bool SaveReload::isSelectCurrentSave()
{
	return m_currentSave != SELECTION::NO_CURRENT_SAVE_SELECTED;
}

bool SaveReload::isSelectCurrentSaveInTab()
{
	const auto findCurrentSave = std::find(m_tabSave.begin(), m_tabSave.end(), static_cast<size_t>(m_currentSave));
	if (findCurrentSave != m_tabSave.end())
	{
		return true;
	}
	return false;
}

SaveReload::SaveReload() 
: 
m_tabSave(),
m_currentSave(SELECTION::NO_CURRENT_SAVE_SELECTED)
{
}

SaveReload::~SaveReload()
{
}

void SaveReload::resetCurrentSave()
{
	m_currentSave = SELECTION::NO_CURRENT_SAVE_SELECTED;
}

 /*
 *	End Of File : SaveReload.cpp
 */