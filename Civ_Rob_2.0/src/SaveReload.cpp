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
#include "MainMap.h"
#include "NewGameScreen.h"
#include "Player.h"
#include "Unit.h"
#include "T_Unit.h"
#include "XmlConvertValue.h"

#include <R2D/src/ResourceManager.h> 
#include <R2D/src/ErrorLog.h> 
#include <R2D/src/ExitFromError.h> 

#include <filesystem>

namespace SAVE
{
	const size_t OFFSET_INDEX = 1;
}

void SaveReload::init(const std::string& filePath)
{
	std::string destroy{ STRINGS::EMPTY };
	std::ifstream loadInfo{ filePath };
	size_t size{ 0 };
	bool wellFormatedSaveFile{ false };

	if (loadInfo)
	{
		while (!wellFormatedSaveFile && std::getline(loadInfo, destroy))
		{
			auto pos = destroy.find("NbSave=");
			if (pos != std::string::npos) wellFormatedSaveFile = true;
		}

		if(!wellFormatedSaveFile) throw(std::exception("Corrupted or damaged Save file"));

		loadInfo >> size;

		m_tabSave.resize(size);

		loadInfo >> destroy;

		for (auto& index : m_tabSave) loadInfo >> index;
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + filePath);
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
	
	std::ofstream saveMaps{ R2D::ResourceManager::getFile(R2D::e_Files::saveMaps)->getPath() };
	if (saveMaps)
	{
		for (size_t i{0}; i < mainGame.GETmainMap().GETmatriceMap().size(); i++)
		{
			for (size_t j{0}; j < mainGame.GETmainMap().GETmatriceMap()[i].size(); j++)
			{
				saveMaps << (unsigned int)mainGame.GETmainMap().GETmatriceMap()[i][j].indexX << std::endl;
				saveMaps << (unsigned int)mainGame.GETmainMap().GETmatriceMap()[i][j].indexY << std::endl;
				saveMaps << mainGame.GETmainMap().GETmatriceMap()[i][j].tile_x << std::endl;
				saveMaps << mainGame.GETmainMap().GETmatriceMap()[i][j].tile_y << std::endl;
				saveMaps << (unsigned int)mainGame.GETmainMap().GETmatriceMap()[i][j].tile_ground << std::endl;
				saveMaps << (unsigned int)mainGame.GETmainMap().GETmatriceMap()[i][j].tile_spec << std::endl;
				saveMaps << mainGame.GETmainMap().GETmatriceMap()[i][j].appartenance << std::endl;
				saveMaps << (unsigned int)mainGame.GETmainMap().GETmatriceMap()[i][j].food << std::endl;
				saveMaps << (unsigned int)mainGame.GETmainMap().GETmatriceMap()[i][j].work << std::endl;
				saveMaps << (unsigned int)mainGame.GETmainMap().GETmatriceMap()[i][j].gold << std::endl << std::endl;
			}
		}
	}
	else
		R2D::ErrorLog::logEvent
		(
			"[ERROR]___: Impossible d'ouvrir le fichier "
			+ 
			R2D::ResourceManager::getFile(R2D::e_Files::saveMaps)->getPath()
		);
}

void SaveReload::savePlayer
(
	GamePlayScreen& mainGame
)
{
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.Clear();
	tinyxml2::XMLNode* pRoot{ xmlDoc.NewElement("SavePlayers") };

	xmlDoc.InsertFirstChild(pRoot);

	/* ---------------------------------------------------------------------- */
	/* Level :																  */
	/* ----- :																  */
	/* 1 : Player															  */
	/* 1.1			-> Name  												  */
	/* 1.2			-> TabUnit  											  */
	/* 1.2.1		->	-> Unit  											  */
	/* 1.2.1.1		->  ->	-> Name  										  */
	/* 1.2.1.2		->  ->	-> X  											  */
	/* 1.2.1.3		->  ->	-> Y  											  */
	/* 1.2.1.4		->  ->	-> MovementType  								  */
	/* 1.2.1.5		->  ->	-> Life  										  */
	/* 1.2.1.6		->  ->	-> Atq  										  */
	/* 1.2.1.7		->  ->	-> Def  										  */
	/* 1.2.1.8		->  ->	-> Movement  									  */
	/* 1.2.1.9		->  ->	-> Level	  									  */
	/* 1.3			-> TabCity  											  */
	/* 1.3.1		->	-> City  											  */
	/* 1.3.1.1		->  ->	-> Name  										  */
	/* 1.3.1.2		->  ->	-> X  											  */
	/* 1.3.1.3		->	->	-> Y  											  */
	/* ---------------------------------------------------------------------- */

	for (unsigned int p(0); p < mainGame.GETPlayers().GETvectPlayer().size(); p++)
	{
		tinyxml2::XMLElement* playerElement = xmlDoc.NewElement("Player");
		tinyxml2::XMLElement* playerNameElement = xmlDoc.NewElement("Name");
		playerNameElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETname().c_str());
		playerElement->InsertEndChild(playerNameElement);

		tinyxml2::XMLElement* playerIDElement = xmlDoc.NewElement("ID");
		playerIDElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETid());
		playerElement->InsertEndChild(playerIDElement);

		tinyxml2::XMLElement* GoldStatsElement = xmlDoc.NewElement("GoldStats");

		tinyxml2::XMLElement* GoldStatsElementGold = xmlDoc.NewElement("Gold");
		tinyxml2::XMLElement* GoldStatsElementGoldBalance = xmlDoc.NewElement("GoldBalance");
		tinyxml2::XMLElement* GoldStatsElementIncome = xmlDoc.NewElement("Income");
		tinyxml2::XMLElement* GoldStatsElementCost = xmlDoc.NewElement("Cost");
		tinyxml2::XMLElement* GoldStatsElementTaxIncome = xmlDoc.NewElement("TaxIncome");
		tinyxml2::XMLElement* GoldStatsElementCommerceIncome = xmlDoc.NewElement("CommerceIncome");
		tinyxml2::XMLElement* GoldStatsElementGoldConversionSurplus = xmlDoc.NewElement("GoldConversionSurplus");
		tinyxml2::XMLElement* GoldStatsElementArmiesCost = xmlDoc.NewElement("ArmiesCost");
		tinyxml2::XMLElement* GoldStatsElementBuildingsCost = xmlDoc.NewElement("BuildingsCost");

		GoldStatsElementGold->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStats().gold);
		GoldStatsElementGoldBalance->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStats().goldBalance);
		GoldStatsElementIncome->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStats().income);
		GoldStatsElementCost->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStats().cost);
		GoldStatsElementTaxIncome->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStats().taxIncome);
		GoldStatsElementCommerceIncome->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStats().commerceIncome);
		GoldStatsElementGoldConversionSurplus->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStats().goldConversionSurplus);
		GoldStatsElementArmiesCost->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStats().armiesCost);
		GoldStatsElementBuildingsCost->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStats().buildingsCost);

		GoldStatsElement->InsertEndChild(GoldStatsElementGold);
		GoldStatsElement->InsertEndChild(GoldStatsElementGoldBalance);
		GoldStatsElement->InsertEndChild(GoldStatsElementIncome);
		GoldStatsElement->InsertEndChild(GoldStatsElementCost);
		GoldStatsElement->InsertEndChild(GoldStatsElementTaxIncome);
		GoldStatsElement->InsertEndChild(GoldStatsElementCommerceIncome);
		GoldStatsElement->InsertEndChild(GoldStatsElementGoldConversionSurplus);
		GoldStatsElement->InsertEndChild(GoldStatsElementArmiesCost);
		GoldStatsElement->InsertEndChild(GoldStatsElementBuildingsCost);

		playerElement->InsertEndChild(GoldStatsElement);

		tinyxml2::XMLElement* tabUnitElement = xmlDoc.NewElement("TabUnit");

		for (unsigned int i(0); i < mainGame.GETPlayers().GETvectPlayer()[p]->GETtabUnit().size(); i++)
		{
			tinyxml2::XMLElement* unitElement = xmlDoc.NewElement("Unit");
			tinyxml2::XMLElement* unitNameElement = xmlDoc.NewElement("Name");
			tinyxml2::XMLElement* unitXElement = xmlDoc.NewElement("X");
			tinyxml2::XMLElement* unitYElement = xmlDoc.NewElement("Y");
			tinyxml2::XMLElement* unitMovementTypeElement = xmlDoc.NewElement("MovementType");
			tinyxml2::XMLElement* unitLifeElement = xmlDoc.NewElement("Life");
			tinyxml2::XMLElement* unitAtqElement = xmlDoc.NewElement("Atq");
			tinyxml2::XMLElement* unitDefElement = xmlDoc.NewElement("Def");
			tinyxml2::XMLElement* unitMovementElement = xmlDoc.NewElement("Movement");
			tinyxml2::XMLElement* unitNumberOfAttackElement = xmlDoc.NewElement("NumberOfAttack");
			tinyxml2::XMLElement* unitLevelElement = xmlDoc.NewElement("Level");
			tinyxml2::XMLElement* unitMaintenanceElement = xmlDoc.NewElement("Maintenance");

			unitNameElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabUnit()[i]->GETname().c_str());
			unitXElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabUnit()[i]->GETx());
			unitYElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabUnit()[i]->GETy());
			unitMovementTypeElement->SetText((unsigned int)mainGame.GETPlayers().GETvectPlayer()[p]->GETtabUnit()[i]->GETmovementType());
			unitLifeElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabUnit()[i]->GETlife());
			unitAtqElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabUnit()[i]->GETatq());
			unitDefElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabUnit()[i]->GETdef());
			unitMovementElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabUnit()[i]->GETmovement());
			unitNumberOfAttackElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabUnit()[i]->GETnumberOfAttack());
			unitLevelElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabUnit()[i]->GETlevel());
			unitMaintenanceElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabUnit()[i]->GETmaintenance());

			unitElement->InsertEndChild(unitNameElement);
			unitElement->InsertEndChild(unitXElement);
			unitElement->InsertEndChild(unitYElement);
			unitElement->InsertEndChild(unitMovementTypeElement);
			unitElement->InsertEndChild(unitLifeElement);
			unitElement->InsertEndChild(unitAtqElement);
			unitElement->InsertEndChild(unitDefElement);
			unitElement->InsertEndChild(unitMovementElement);
			unitElement->InsertEndChild(unitNumberOfAttackElement);
			unitElement->InsertEndChild(unitLevelElement);
			unitElement->InsertEndChild(unitMaintenanceElement);

			tabUnitElement->InsertEndChild(unitElement);
			playerElement->InsertEndChild(tabUnitElement);
		}

		tinyxml2::XMLElement* tabCityElement = xmlDoc.NewElement("TabCity");

		for (unsigned int i(0); i < mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity().size(); i++)
		{
			tinyxml2::XMLElement* cityElement = xmlDoc.NewElement("City");
			tinyxml2::XMLElement* cityNameElement = xmlDoc.NewElement("Name");
			tinyxml2::XMLElement* cityXElement = xmlDoc.NewElement("X");
			tinyxml2::XMLElement* cityYElement = xmlDoc.NewElement("Y");
			tinyxml2::XMLElement* cityInfluenceLevelElement = xmlDoc.NewElement("InfluenceLevel");
			tinyxml2::XMLElement* cityAtqElement = xmlDoc.NewElement("Atq");
			tinyxml2::XMLElement* cityDefElement = xmlDoc.NewElement("Def");
			tinyxml2::XMLElement* cityEmotionElement = xmlDoc.NewElement("Emotion");
			tinyxml2::XMLElement* cityFoodStockElement = xmlDoc.NewElement("FoodStock");
			tinyxml2::XMLElement* cityFoodBalanceElement = xmlDoc.NewElement("FoodBalance");
			tinyxml2::XMLElement* cityFoodSurplusPreviousTurnElement = xmlDoc.NewElement("FoodSurplusPreviousTurn");
			tinyxml2::XMLElement* cityFoodToLevelUp = xmlDoc.NewElement("FoodToLevelUp");
			tinyxml2::XMLElement* cityGoldBalanceElement = xmlDoc.NewElement("GoldBalance");
			tinyxml2::XMLElement* cityConversionToApplyElement = xmlDoc.NewElement("ConversionToApply");

			tinyxml2::XMLElement* cityBuildQueueElement = xmlDoc.NewElement("BuildQueue");
			tinyxml2::XMLElement* cityTabCitizenElement = xmlDoc.NewElement("TabCitizen");

			cityNameElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETname().c_str());
			cityXElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETx());
			cityYElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETy());
			cityInfluenceLevelElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETinfluenceLevel());
			cityAtqElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETatq());
			cityDefElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETdef());
			cityEmotionElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETemotion());
			cityFoodStockElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETfoodStock());
			cityFoodBalanceElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETfoodBalance());
			cityFoodSurplusPreviousTurnElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETfoodSurplusPreviousTurn());
			cityFoodToLevelUp->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETfoodToLevelUp());
			cityGoldBalanceElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETgoldBalance());
			cityConversionToApplyElement->SetText((unsigned int)mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETconversionToApply());

			cityElement->InsertEndChild(cityNameElement);
			cityElement->InsertEndChild(cityXElement);
			cityElement->InsertEndChild(cityYElement);
			cityElement->InsertEndChild(cityInfluenceLevelElement);
			cityElement->InsertEndChild(cityAtqElement);
			cityElement->InsertEndChild(cityDefElement);
			cityElement->InsertEndChild(cityEmotionElement);
			cityElement->InsertEndChild(cityFoodStockElement);
			cityElement->InsertEndChild(cityFoodBalanceElement);
			cityElement->InsertEndChild(cityFoodSurplusPreviousTurnElement);
			cityElement->InsertEndChild(cityFoodToLevelUp);
			cityElement->InsertEndChild(cityGoldBalanceElement);
			cityElement->InsertEndChild(cityConversionToApplyElement);

			for (
				unsigned int indexBuild(0);
				indexBuild < mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETbuildQueue().size();
				indexBuild++
				)
			{
				tinyxml2::XMLElement* cityBuildInQueueElement = xmlDoc.NewElement("BuildInQueue");

				tinyxml2::XMLElement* cityBuildInQueueNameElement = xmlDoc.NewElement("Name");
				tinyxml2::XMLElement* cityBuildInQueueTypeElement = xmlDoc.NewElement("Type");
				tinyxml2::XMLElement* cityBuildInQueueWorkElement = xmlDoc.NewElement("Work");
				tinyxml2::XMLElement* cityBuildInQueueRemainingWorkElement = xmlDoc.NewElement("RemainingWork");

				cityBuildInQueueNameElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETbuildQueue()[indexBuild].buildQ.name.c_str());
				cityBuildInQueueTypeElement
					->SetText((unsigned int)mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETbuildQueue()[indexBuild].buildQ.type);
				cityBuildInQueueWorkElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETbuildQueue()[indexBuild].buildQ.work);
				cityBuildInQueueRemainingWorkElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETbuildQueue()[indexBuild].buildQ.remainingWork);

				cityBuildInQueueElement->InsertEndChild(cityBuildInQueueNameElement);
				cityBuildInQueueElement->InsertEndChild(cityBuildInQueueTypeElement);
				cityBuildInQueueElement->InsertEndChild(cityBuildInQueueWorkElement);
				cityBuildInQueueElement->InsertEndChild(cityBuildInQueueRemainingWorkElement);

				cityBuildQueueElement->InsertEndChild(cityBuildInQueueElement);
			}

			for (unsigned int indexCitizen(0); indexCitizen < mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETcitizens().size(); indexCitizen++)
			{
				tinyxml2::XMLElement* cityCitizensElement = xmlDoc.NewElement("Citizens");
				tinyxml2::XMLElement* cityCitizensTileOccupiedElement = xmlDoc.NewElement("TileOccupied");
				tinyxml2::XMLElement* cityCitizensHappinessElement = xmlDoc.NewElement("Happiness");
				tinyxml2::XMLElement* cityCitizensFoodElement = xmlDoc.NewElement("Food");
				tinyxml2::XMLElement* cityCitizensWorkElement = xmlDoc.NewElement("Work");
				tinyxml2::XMLElement* cityCitizensGoldElement = xmlDoc.NewElement("Gold");
				tinyxml2::XMLElement* cityCitizensRevoltElement = xmlDoc.NewElement("Revolt");
				tinyxml2::XMLElement* cityCitizensReligionElement = xmlDoc.NewElement("Religion");
				tinyxml2::XMLElement* cityCitizensPlaceElement = xmlDoc.NewElement("Place");

				cityCitizensTileOccupiedElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETcitizens()[indexCitizen]->GETtileOccupied());
				cityCitizensHappinessElement
					->SetText((int)mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETcitizens()[indexCitizen]->GEThappiness());
				cityCitizensFoodElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETcitizens()[indexCitizen]->GETfood());
				cityCitizensWorkElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETcitizens()[indexCitizen]->GETwork());
				cityCitizensGoldElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETcitizens()[indexCitizen]->GETgold());
				cityCitizensRevoltElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETcitizens()[indexCitizen]->GETrevolt());
				cityCitizensReligionElement
					->SetText((unsigned int)mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETcitizens()[indexCitizen]->GETreligion());
				cityCitizensPlaceElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtabCity()[i]->GETcitizens()[indexCitizen]->GETplace());

				cityCitizensElement->InsertEndChild(cityCitizensTileOccupiedElement);
				cityCitizensElement->InsertEndChild(cityCitizensHappinessElement);
				cityCitizensElement->InsertEndChild(cityCitizensFoodElement);
				cityCitizensElement->InsertEndChild(cityCitizensWorkElement);
				cityCitizensElement->InsertEndChild(cityCitizensGoldElement);
				cityCitizensElement->InsertEndChild(cityCitizensRevoltElement);
				cityCitizensElement->InsertEndChild(cityCitizensReligionElement);
				cityCitizensElement->InsertEndChild(cityCitizensPlaceElement);

				cityTabCitizenElement->InsertEndChild(cityCitizensElement);
			}

			cityElement->InsertEndChild(cityBuildQueueElement);
			cityElement->InsertEndChild(cityTabCitizenElement);

			tabCityElement->InsertEndChild(cityElement);

			playerElement->InsertEndChild(tabCityElement);
		}
		pRoot->InsertEndChild(playerElement);
	}
	
	xmlDoc.SaveFile(R2D::ResourceManager::getFile(R2D::e_Files::savePlayers)->getPath().c_str());
}

void SaveReload::reload
(
	GamePlayScreen& mainGame
)
{
	R2D::ErrorLog::logEvent("[INFO]___: Reload Start");

	loadMaps(mainGame);
	loadPlayer(mainGame);

	mainGame.GETvar().cinState = CinState_Type::cinMainMap;
	mainGame.GETPlayers().SETselectedPlayerId(SELECTION::NO_PLAYER_SELECTED);

	mainGame.makePlayersButtons();
	mainGame.GETmainMap().initMainMapTexture();

	R2D::ErrorLog::logEvent("[INFO]___: Reload End");
}

void SaveReload::loadMaps
(
	GamePlayScreen& mainGame
)
{
	std::string input(STRINGS::EMPTY);

	std::ifstream saveMaps(R2D::ResourceManager::getFile(R2D::e_Files::saveMaps)->getPath());
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
		R2D::ErrorLog::logEvent
		(
			"[ERROR]___: Impossible d'ouvrir le fichier "
			+
			R2D::ResourceManager::getFile(R2D::e_Files::saveMaps)->getPath()
		);

	R2D::ErrorLog::logEvent("[INFO]___: Save End");
}

void SaveReload::loadPlayer
(
	GamePlayScreen& mainGame
)
{
	std::string errCheck(STRINGS::EMPTY);
	tinyxml2::XMLDocument xmlDoc;
	
	if (xmlDoc.LoadFile(R2D::ResourceManager::getFile(R2D::e_Files::savePlayers)->getPath().c_str()) == tinyxml2::XML_SUCCESS)
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
	R2D::ErrorLog::logEvent("[INFO]___: createSave Start");
	std::string destroy;

	for (unsigned int i(SAVE::OFFSET_INDEX); i < m_tabSave.size() + SAVE::OFFSET_INDEX; i++)
	{
		if (i != m_tabSave[i - SAVE::OFFSET_INDEX])
		{
			m_currentSave = i;
			m_tabSave.push_back(m_currentSave);
			break;
		}
	}

	if (m_currentSave <= 0)
	{
		m_currentSave = static_cast<int>(m_tabSave.size() + SAVE::OFFSET_INDEX);
		m_tabSave.push_back(m_currentSave);
	}

	rewriteSaveInfoFile();

	createSaveDir();

	R2D::ErrorLog::logEvent("[INFO]___: createSave End");
}

void SaveReload::createSaveDir()
{
	const std::string dir{ "save/" + std::to_string(m_currentSave) };

	if (!std::filesystem::create_directory(dir))
	{
		R2D::ErrorLog::logEvent("[ERROR]___: create directory failed ");
	}

	R2D::ResourceManager::modifyFilePath(
		R2D::e_Files::saveMaps, dir + "/" + R2D::ResourceManager::getFile(R2D::e_Files::saveMaps)->getPath());

	R2D::ResourceManager::modifyFilePath(
		R2D::e_Files::savePlayers, dir + "/" + R2D::ResourceManager::getFile(R2D::e_Files::savePlayers)->getPath());
}

void SaveReload::removeSave()
{
	R2D::ErrorLog::logEvent("[INFO]___: removeSave Start");

	if (isSelectCurrentSave() && isSelectCurrentSaveInTab())
	{
		removeSaveDir(m_currentSave);

		m_tabSave.erase(m_tabSave.begin() + searchIndexToRemove());

		unselectCurrentSave();

		rewriteSaveInfoFile();
	}
	else
		R2D::ErrorLog::logEvent("[ERROR]___: currentSave = 0");

	R2D::ErrorLog::logEvent("[INFO]___: removeSave End");
}

void SaveReload::clearSave()
{
	R2D::ErrorLog::logEvent("[INFO]___: clearSave Start");

	for (const auto index : m_tabSave)
	{
		removeSaveDir(index);
	}

	m_tabSave.clear();

	unselectCurrentSave();

	rewriteSaveInfoFile();

	R2D::ErrorLog::logEvent("[INFO]___: clearSave End");
}

void SaveReload::removeSaveDir(const size_t index)
{
	const std::string dir{ "save/" + std::to_string(index) };
	removeSaveFile(dir + "/saveMaps.txt");
	removeSaveFile(dir + "/savePlayers.xml");
	removeSaveFile(dir);
}

void SaveReload::removeSaveFile(const std::string& file)
{
	if (!std::filesystem::remove(file))
		R2D::ErrorLog::logEvent("[ERROR]___: Impossible d'effacer le fichier " + file);
	else
		R2D::ErrorLog::logEvent("[INFO]___: file : " + file + " successfully remove");
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
	for (const auto index : m_tabSave)
	{
		if (m_currentSave == static_cast<int>(index))
		{
			return true;
		}
	}
	return false;
}

void SaveReload::rewriteSaveInfoFile()
{
	const std::string& file{ R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath() };
	std::ofstream saveInfo(file);
	if (saveInfo)
	{
		saveInfo << "NbSave="			<< std::endl;
		saveInfo << m_tabSave.size()	<< std::endl;
		saveInfo << "SaveUse="			<< std::endl;
		for (const auto index : m_tabSave) saveInfo << index << std::endl;
	}
	else
		R2D::ErrorLog::logEvent("[ERROR]___: Impossible d'ouvrir le fichier " + file);
}

size_t SaveReload::searchIndexToRemove()
{
	size_t loopIndex{ 0 };
	for (const auto index : m_tabSave)
	{
		if (index == static_cast<GLuint>(m_currentSave))
		{
			return loopIndex;
		}
		loopIndex++;
	}
	return 0;
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