/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.22.3.1
	file version : 1.11

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

#include "MainGame.h"
#include "MainMap.h"
#include "XmlConvertValue.h"

/* *********************************************************
 *				START SaveReload::STATIC				   *
 ********************************************************* */

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : save																						    	  */
/* ROLE : Save Maps and Player info in a folder in 2 files												      */
/* ROLE : Maps in saveMaps.txt and Player info in savePlayers.xml 										      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::save
(
	MainGame& mainGame
)
{
	saveMaps(mainGame);
	savePlayer(mainGame);
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : savemaps																					    	  */
/* ROLE : Sauvegardes des sys map.map et map.screen														      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void																	    			  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::saveMaps
(
	MainGame& mainGame
)
{
	std::ofstream saveMaps(mainGame.GETfile().saveMaps);
	if (saveMaps)
	{
		for (unsigned int i = 0; i < mainGame.GETmainMap().GETmatriceMap().size(); i++)
		{
			for (unsigned int j = 0; j < mainGame.GETmainMap().GETmatriceMap()[i].size(); j++)
			{
				saveMaps << (unsigned int)mainGame.GETmainMap().GETmatriceMap()[i][j].indexX << std::endl;
				saveMaps << (unsigned int)mainGame.GETmainMap().GETmatriceMap()[i][j].indexY << std::endl;
				saveMaps << mainGame.GETmainMap().GETmatriceMap()[i][j].tile_x << std::endl;
				saveMaps << mainGame.GETmainMap().GETmatriceMap()[i][j].tile_y << std::endl;
				saveMaps << mainGame.GETmainMap().GETmatriceMap()[i][j].tile_stringground << std::endl;
				saveMaps << (unsigned int)mainGame.GETmainMap().GETmatriceMap()[i][j].tile_ground << std::endl;
				saveMaps << mainGame.GETmainMap().GETmatriceMap()[i][j].tile_stringspec << std::endl;
				saveMaps << (unsigned int)mainGame.GETmainMap().GETmatriceMap()[i][j].tile_spec << std::endl;
				saveMaps << mainGame.GETmainMap().GETmatriceMap()[i][j].appartenance << std::endl;
				saveMaps << (unsigned int)mainGame.GETmainMap().GETmatriceMap()[i][j].food << std::endl;
				saveMaps << (unsigned int)mainGame.GETmainMap().GETmatriceMap()[i][j].work << std::endl;
				saveMaps << (unsigned int)mainGame.GETmainMap().GETmatriceMap()[i][j].gold << std::endl << std::endl;
			}
		}
	}
	else
		MainGame::logfileconsole("[ERROR]___: Impossible d'ouvrir le fichier " + mainGame.GETfile().saveMaps);
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : savePlayer																				    	  */
/* ROLE : Sauvegarde des joueurs (units et cities) dans savePlayers.xml									      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void 																				  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::savePlayer
(
	MainGame& mainGame
)
{
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLNode* pRoot = xmlDoc.NewElement("SavePlayers");

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

		GoldStatsElementGold->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStatsConst().gold);
		GoldStatsElementGoldBalance->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStatsConst().goldBalance);
		GoldStatsElementIncome->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStatsConst().income);
		GoldStatsElementCost->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStatsConst().cost);
		GoldStatsElementTaxIncome->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStatsConst().taxIncome);
		GoldStatsElementCommerceIncome->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStatsConst().commerceIncome);
		GoldStatsElementGoldConversionSurplus->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStatsConst().goldConversionSurplus);
		GoldStatsElementArmiesCost->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStatsConst().armiesCost);
		GoldStatsElementBuildingsCost->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETgoldStatsConst().buildingsCost);

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
			tinyxml2::XMLElement* unitLevelElement = xmlDoc.NewElement("Level");
			tinyxml2::XMLElement* unitMaintenanceElement = xmlDoc.NewElement("Maintenance");

			unitNameElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheUnit(i)->GETname().c_str());
			unitXElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheUnit(i)->GETx());
			unitYElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheUnit(i)->GETy());
			unitMovementTypeElement->SetText((Uint8)mainGame.GETPlayers().GETvectPlayer()[p]->GETtheUnit(i)->GETmovementType());
			unitLifeElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheUnit(i)->GETlife());
			unitAtqElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheUnit(i)->GETatq());
			unitDefElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheUnit(i)->GETdef());
			unitMovementElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheUnit(i)->GETmovement());
			unitLevelElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheUnit(i)->GETlevel());
			unitMaintenanceElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheUnit(i)->GETmaintenance());

			unitElement->InsertEndChild(unitNameElement);
			unitElement->InsertEndChild(unitXElement);
			unitElement->InsertEndChild(unitYElement);
			unitElement->InsertEndChild(unitMovementTypeElement);
			unitElement->InsertEndChild(unitLifeElement);
			unitElement->InsertEndChild(unitAtqElement);
			unitElement->InsertEndChild(unitDefElement);
			unitElement->InsertEndChild(unitMovementElement);
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
			tinyxml2::XMLElement* cityNbPopElement = xmlDoc.NewElement("NbPop");
			tinyxml2::XMLElement* cityAtqElement = xmlDoc.NewElement("Atq");
			tinyxml2::XMLElement* cityDefElement = xmlDoc.NewElement("Def");
			tinyxml2::XMLElement* cityEmotionElement = xmlDoc.NewElement("Emotion");
			tinyxml2::XMLElement* cityFoodStockElement = xmlDoc.NewElement("FoodStock");
			tinyxml2::XMLElement* cityFoodBalanceElement = xmlDoc.NewElement("FoodBalance");
			tinyxml2::XMLElement* cityFoodSurplusPreviousTurnElement = xmlDoc.NewElement("FoodSurplusPreviousTurn");
			tinyxml2::XMLElement* cityGoldBalanceElement = xmlDoc.NewElement("GoldBalance");
			tinyxml2::XMLElement* cityConversionToApplyElement = xmlDoc.NewElement("ConversionToApply");

			tinyxml2::XMLElement* cityBuildQueueElement = xmlDoc.NewElement("BuildQueue");
			tinyxml2::XMLElement* cityTabCitizenElement = xmlDoc.NewElement("TabCitizen");

			cityNameElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETname().c_str());
			cityXElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETx());
			cityYElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETy());
			cityInfluenceLevelElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETinfluenceLevel());
			cityNbPopElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETnbpop());
			cityAtqElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETatq());
			cityDefElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETdef());
			cityEmotionElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETemotion());
			cityFoodStockElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETfoodStock());
			cityFoodBalanceElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETfoodBalance());
			cityFoodSurplusPreviousTurnElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETfoodSurplusPreviousTurn());
			cityGoldBalanceElement->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETgoldBalance());
			cityConversionToApplyElement->SetText((UINT8)mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETconversionToApply());

			cityElement->InsertEndChild(cityNameElement);
			cityElement->InsertEndChild(cityXElement);
			cityElement->InsertEndChild(cityYElement);
			cityElement->InsertEndChild(cityInfluenceLevelElement);
			cityElement->InsertEndChild(cityNbPopElement);
			cityElement->InsertEndChild(cityAtqElement);
			cityElement->InsertEndChild(cityDefElement);
			cityElement->InsertEndChild(cityEmotionElement);
			cityElement->InsertEndChild(cityFoodStockElement);
			cityElement->InsertEndChild(cityFoodBalanceElement);
			cityElement->InsertEndChild(cityFoodSurplusPreviousTurnElement);
			cityElement->InsertEndChild(cityGoldBalanceElement);
			cityElement->InsertEndChild(cityConversionToApplyElement);

			for (
				unsigned int indexBuild(0);
				indexBuild < mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETbuildQueue().buildQueue.size();
				indexBuild++
				)
			{
				tinyxml2::XMLElement* cityBuildInQueueElement = xmlDoc.NewElement("BuildInQueue");

				tinyxml2::XMLElement* cityBuildInQueueNameElement = xmlDoc.NewElement("Name");
				tinyxml2::XMLElement* cityBuildInQueueTypeElement = xmlDoc.NewElement("Type");
				tinyxml2::XMLElement* cityBuildInQueueRemainingWorkElement = xmlDoc.NewElement("RemainingWork");

				cityBuildInQueueNameElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETbuildQueue().buildQueue[indexBuild].name.c_str());
				cityBuildInQueueTypeElement
					->SetText((Uint8)mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETbuildQueue().buildQueue[indexBuild].type);
				cityBuildInQueueRemainingWorkElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETbuildQueue().buildQueue[indexBuild].remainingWork);

				cityBuildInQueueElement->InsertEndChild(cityBuildInQueueNameElement);
				cityBuildInQueueElement->InsertEndChild(cityBuildInQueueTypeElement);
				cityBuildInQueueElement->InsertEndChild(cityBuildInQueueRemainingWorkElement);

				cityBuildQueueElement->InsertEndChild(cityBuildInQueueElement);
			}

			for (unsigned int indexCitizen(0); indexCitizen < mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETcitizens().size(); indexCitizen++)
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
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETcitizens()[indexCitizen]->GETtileOccupied());
				cityCitizensHappinessElement
					->SetText((int8_t)mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETcitizens()[indexCitizen]->GEThappiness());
				cityCitizensFoodElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETcitizens()[indexCitizen]->GETfood());
				cityCitizensWorkElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETcitizens()[indexCitizen]->GETwork());
				cityCitizensGoldElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETcitizens()[indexCitizen]->GETgold());
				cityCitizensRevoltElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETcitizens()[indexCitizen]->GETrevolt());
				cityCitizensReligionElement
					->SetText((UINT8)mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETcitizens()[indexCitizen]->GETreligion());
				cityCitizensPlaceElement
					->SetText(mainGame.GETPlayers().GETvectPlayer()[p]->GETtheCity(i)->GETcitizens()[indexCitizen]->GETplace());

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
	xmlDoc.SaveFile(mainGame.GETfile().savePlayers.c_str());
}


/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : reload																					    	  */
/* ROLE : Chargement de la partie à patir des fichiers de sauvegarde									      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::reload
(
	MainGame& mainGame
)
{
	MainGame::logfileconsole("[INFO]___: Reload Start");

	loadMaps(mainGame);
	loadPlayer(mainGame);

	mainGame.GETvar().statescreen = State_Type::STATEmainMap;
	mainGame.GETvar().cinState = CinState_Type::cinMainMap;
	mainGame.GETPlayers().SETselectedPlayer(NO_PLAYER_SELECTED);


	//SDL_RenderPresent(sysinfo.screen.renderer);

	MainGame::logfileconsole("[INFO]___: Reload End");
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : loadMaps																					    	  */
/* ROLE : Chargement des sys map.map et map.screen														      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void								    												  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::loadMaps
(
	MainGame& mainGame
)
{
	std::string input(EMPTY_STRING);

	std::ifstream saveMaps(mainGame.GETfile().saveMaps);
	if (saveMaps)
	{
		for (unsigned int i = 0; i < mainGame.GETmainMap().GETmatriceMap().size(); i++)
		{
			for (unsigned int j = 0; j < mainGame.GETmainMap().GETmatriceMap()[i].size(); j++)
			{
				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].indexX = (Uint8)std::stoul(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].indexY = (Uint8)std::stoul(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].tile_x = std::stoul(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].tile_y = std::stoul(input);

				saveMaps >> mainGame.GETmainMap().GETmatriceMap()[i][j].tile_stringground;

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].tile_ground = (Ground_Type)std::stoul(input);

				saveMaps >> mainGame.GETmainMap().GETmatriceMap()[i][j].tile_stringspec;

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].tile_spec = (GroundSpec_Type)std::stoul(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].appartenance = std::stoi(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].food = (int8_t)std::stoi(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].work = (int8_t)std::stoi(input);

				saveMaps >> input;
				mainGame.GETmainMap().GETmatriceMap()[i][j].gold = (int8_t)std::stoi(input);
			}
		}
	}
	else
		MainGame::logfileconsole("[ERROR]___: Impossible d'ouvrir le fichier " + mainGame.GETfile().saveMaps);

	MainGame::logfileconsole("[INFO]___: Save End");
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : loadPlayer																				    	  */
/* ROLE : Chargement des joueurs (units et cities) dans SavePlayer.txt									      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::loadPlayer
(
	MainGame& mainGame
)
{
	std::string errCheck(EMPTY_STRING);
	tinyxml2::XMLDocument xmlDoc;

	if (xmlDoc.LoadFile(mainGame.GETfile().savePlayers.c_str()) == tinyxml2::XML_SUCCESS)
	{
		tinyxml2::XMLNode* pRoot = xmlDoc.FirstChild();
		if (nullptr == pRoot) MainGame::exitError("[ERROR]___: loadPlayer : pRoot == nullptr");

		tinyxml2::XMLNode* nPlayer = pRoot->FirstChild();
		errCheck = nPlayer->Value();
		if (errCheck.compare("Player") != IDENTICAL_STRINGS) MainGame::exitError("[ERROR]___: loadPlayer : nPlayer != Player");

		while (nullptr != nPlayer)
		{
			tinyxml2::XMLNode* nName = nPlayer->FirstChild();
			tinyxml2::XMLNode* nGoldStats = nName->NextSibling();
			tinyxml2::XMLNode* nTabUnit = nGoldStats->NextSibling();
			tinyxml2::XMLNode* nTabCity = nTabUnit->NextSibling();

			if (nullptr == nName) MainGame::exitError("[ERROR]___: loadPlayer : nName == nullptr");
			errCheck = nName->Value();
			if (errCheck.compare("Name") != IDENTICAL_STRINGS) MainGame::exitError("[ERROR]___: loadPlayer : nName != Name");

			mainGame.GETPlayers().GETvectPlayer().push_back(new Player(nName->FirstChild()->Value()));
			mainGame.GETPlayers().SETselectedPlayer((int)mainGame.GETPlayers().GETvectPlayer().size() - 1);

			loadGoldStatsXML
			(
				mainGame.GETPlayers().GETvectPlayer()[mainGame.GETPlayers().GETvectPlayer().size() - 1]->GETgoldStats(),
				nGoldStats
			);

			//L10:
			if (nullptr != nTabUnit)
			{
				errCheck = nTabUnit->Value();
				if (errCheck.compare("TabUnit") != IDENTICAL_STRINGS)
				{
					nTabCity = nTabUnit;
					nTabUnit = nullptr;
					goto L20;
				}
				if (errCheck.compare("TabUnit") != IDENTICAL_STRINGS) MainGame::exitError("[ERROR]___: loadPlayer : nTabUnit != TabUnit");

				tinyxml2::XMLNode* nUnit = nTabUnit->FirstChild();
				if (nullptr != nUnit)
				{
					errCheck = nUnit->Value();
					if (errCheck.compare("Unit") != IDENTICAL_STRINGS) MainGame::exitError("[ERROR]___: loadPlayer : nUnit != Unit");
				}

				loadUnitXML(mainGame, nUnit);
			}

		L20:
			if (nullptr != nTabCity)
			{


				errCheck = nTabCity->Value();
				if (errCheck.compare("TabCity") != IDENTICAL_STRINGS) MainGame::exitError("[ERROR]___: loadPlayer : nTabCity != TabCity");

				tinyxml2::XMLNode* nCity = nTabCity->FirstChild();
				if (nullptr != nCity)
				{
					errCheck = nCity->Value();
					if (errCheck.compare("City") != IDENTICAL_STRINGS) MainGame::exitError("[ERROR]___: loadPlayer : nCity != City");
				}

				loadCityXML(mainGame, nCity);
			}


			nPlayer = nPlayer->NextSibling();
		}
	}
	else
	{
		MainGame::exitError("[ERROR]___: loadPlayer : xmlDoc.LoadFile() != tinyxml2::XML_SUCCESS");
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : loadGoldStatsXML																			    	  */
/* ROLE : Load Gold Stats reference to Player															      */
/* ROLE : Player->GETgoldStats() should be used instead of Player->GETgoldStatsConst()						  */
/* ROLE : Data type : double ; use std::stod															      */
/* INPUT/OUTPUT : GoldStats& goldStats : Structure of the Player's gold stats 							      */
/* INPUT/OUTPUT : tinyxml2::XMLNode* nGoldStats : Ptr on the GoldStats node in the XML document			      */
/* RETURNED VALUE    : void								    												  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::loadGoldStatsXML
(
	GoldStats& goldStats,
	tinyxml2::XMLNode* nGoldStats
)
{
	tinyxml2::XMLNode* inputNode;

	inputNode = nGoldStats->FirstChild();
	if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadGoldStatsXML : goldStats->gold == nullptr");
	goldStats.gold = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadGoldStatsXML : goldStats->GoldBalance == nullptr");
	goldStats.goldBalance = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadGoldStatsXML : goldStats->Income == nullptr");
	goldStats.income = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadGoldStatsXML : goldStats->Cost == nullptr");
	goldStats.cost = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadGoldStatsXML : goldStats->TaxIncome == nullptr");
	goldStats.taxIncome = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadGoldStatsXML : goldStats->CommerceIncome == nullptr");
	goldStats.commerceIncome = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadGoldStatsXML : goldStats->GoldConversionSurplus == nullptr");
	goldStats.goldConversionSurplus = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadGoldStatsXML : goldStats->ArmiesCost == nullptr");
	goldStats.armiesCost = std::stod(inputNode->FirstChild()->Value());

	inputNode = inputNode->NextSibling();
	if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadGoldStatsXML : goldStats->BuildingsCost == nullptr");
	goldStats.buildingsCost = std::stod(inputNode->FirstChild()->Value());
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : loadUnitXML																				    	  */
/* ROLE : Load Unit reference to Player																	      */
/* ROLE : While Loop : load all Units to a Player														      */
/* INPUT/OUTPUT : MainGame& mainGame : General struct							 							      */
/* INPUT/OUTPUT : tinyxml2::XMLNode* nUnit : Ptr on the Unit node in the XML document					      */
/* RETURNED VALUE    : void								    												  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::loadUnitXML
(
	MainGame& mainGame,
	tinyxml2::XMLNode* nUnit
)
{
	tinyxml2::XMLNode* inputNode;
	Unit_Template blankUnitTemp;

	while (nullptr != nUnit)
	{
		Player* blankPlayer(mainGame.GETPlayers().GETvectPlayer()[mainGame.GETPlayers().GETselectedPlayer()]);
		blankPlayer->addEmptyUnit();

		Unit* blankUnit = blankPlayer->GETtheUnit((unsigned int)(blankPlayer->GETtabUnit().size() - 1));

		inputNode = nUnit->FirstChild();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadPlayer : Unit->Name == nullptr");
		blankUnit->SETname(inputNode->FirstChild()->Value());

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadPlayer : Unit->x == nullptr");
		blankUnit->SETx(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadPlayer : Unit->y == nullptr");
		blankUnit->SETy(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadPlayer : Unit->movement_type == nullptr");
		blankUnit->SETmovementType(XmlConvertValue::convertUintToUnit_Movement_Type((Uint8)std::stoul(inputNode->FirstChild()->Value())));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadPlayer : Unit->life == nullptr");
		blankUnit->SETlife(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadPlayer : Unit->atq == nullptr");
		blankUnit->SETatq(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadPlayer : Unit->def == nullptr");
		blankUnit->SETdef(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadPlayer : Unit->movement == nullptr");
		blankUnit->SETmovement(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadPlayer : Unit->level == nullptr");
		blankUnit->SETlevel(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadPlayer : Unit->maintenance == nullptr");
		blankUnit->SETmaintenance(std::stoul(inputNode->FirstChild()->Value()));

		blankUnitTemp =
			mainGame.GETPlayers().GETvectUnitTemplate()
			[Unit::searchUnitByName(blankUnit->GETname(), mainGame.GETPlayers().GETvectUnitTemplate())];

		blankUnit->SETmaxlife(blankUnitTemp.life);
		blankUnit->SETmaxatq(blankUnitTemp.atq);
		blankUnit->SETmaxdef(blankUnitTemp.def);
		blankUnit->SETmaxmovement(blankUnitTemp.movement);
		blankUnit->SETmaxlevel(blankUnitTemp.level);

		nUnit = nUnit->NextSibling();
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : loadCityXML																				    	  */
/* ROLE : Load City reference to Player																	      */
/* ROLE : While Loop : load all Cities to a Player														      */
/* INPUT/OUTPUT : MainGame& mainGame : General struct							 							      */
/* INPUT/OUTPUT : tinyxml2::XMLNode* nCity : Ptr on the City node in the XML document					      */
/* RETURNED VALUE    : void								    												  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::loadCityXML
(
	MainGame& mainGame,
	tinyxml2::XMLNode* nCity
)
{
	unsigned int middletileX(0), middletileY(0), influenceLevel(MIN_INFLUENCE_LEVEL);
	std::vector<Tile> tabtile;
	tabtile.resize(INIT_SIZE_VIEW * INIT_SIZE_VIEW);

	tinyxml2::XMLNode* inputNode;
	struct BlankCity
	{
		unsigned int x = 0;
		unsigned int y = 0;
		std::string name = EMPTY_STRING;
	};
	BlankCity blankCity;
	build blankBluid;
	Citizen* ptrCitizen;


	Player* ptrPlayer(mainGame.GETPlayers().GETvectPlayer()[mainGame.GETPlayers().GETselectedPlayer()]);
	City* ptrCity;

	while (nullptr != nCity)
	{
		inputNode = nCity->FirstChild();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadCityXML : City->Name == nullptr");
		blankCity.name = inputNode->FirstChild()->Value();

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadCityXML : City->x == nullptr");
		blankCity.x = std::stoul(inputNode->FirstChild()->Value());

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadCityXML : City->y == nullptr");
		blankCity.y = std::stoul(inputNode->FirstChild()->Value());

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadCityXML : City->InfluenceLevel == nullptr");
		influenceLevel = std::stoul(inputNode->FirstChild()->Value());

		middletileX = MainMap::convertPosXToIndex(blankCity.x);
		middletileY = MainMap::convertPosYToIndex(blankCity.y);

		City::fillCitieTiles
		(
			mainGame.GETscreen(),
			middletileX,
			middletileY,
			mainGame.GETPlayers().GETselectedPlayer(),
			mainGame.GETmainMap(),
			tabtile,
			influenceLevel
		);

		ptrPlayer->addCity(blankCity.name, blankCity.x, blankCity.y, tabtile);

		ptrCity = ptrPlayer->GETtheCity((unsigned int)ptrPlayer->GETtabCity().size() - 1);

		ptrCity->SETinfluenceLevel(influenceLevel);

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadCityXML : City->NbPop == nullptr");
		ptrCity->SETnbpop(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadCityXML : City->Atq == nullptr");
		ptrCity->SETatq(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadCityXML : City->Def == nullptr");
		ptrCity->SETdef(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadCityXML : City->Emotion == nullptr");
		ptrCity->SETemotion(std::stoul(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadCityXML : City->FoodStock == nullptr");
		ptrCity->SETfoodStock(std::stod(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadCityXML : City->FoodBalance == nullptr");
		ptrCity->SETfoodBalance(std::stod(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadCityXML : City->FoodSurplusPreviousTurn == nullptr");
		ptrCity->SETfoodSurplusPreviousTurn(std::stod(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadCityXML : City->GoldBalance == nullptr");
		ptrCity->SETgoldBalance(std::stod(inputNode->FirstChild()->Value()));

		inputNode = inputNode->NextSibling();
		if (nullptr == inputNode) MainGame::exitError("[ERROR]___: loadCityXML : City->ConversionToApply == nullptr");
		conversionSurplus_Type type = XmlConvertValue::convert2ConversionToApply(std::stoi(inputNode->FirstChild()->Value()));
		ptrCity->SETconversionToApply(type);



		tinyxml2::XMLNode* nBuildQueue = inputNode->NextSibling();
		if (nullptr != nBuildQueue)
		{
			tinyxml2::XMLNode* nBuildQueueElement = nBuildQueue->FirstChild();

			while (nullptr != nBuildQueueElement)
			{
				tinyxml2::XMLNode* nBuildQueueElementName = nBuildQueueElement->FirstChild();
				if (nullptr == nBuildQueueElementName) MainGame::exitError("[ERROR]___: loadCityXML : City->nBuildQueue->Name == nullptr");
				blankBluid.name = nBuildQueueElementName->FirstChild()->Value();

				tinyxml2::XMLNode* nBuildQueueElementType = nBuildQueueElementName->NextSibling();
				if (nullptr == nBuildQueueElementType) MainGame::exitError("[ERROR]___: loadCityXML : City->nBuildQueue->Type == nullptr");
				blankBluid.type = XmlConvertValue::convert2build_Type(std::stoi(nBuildQueueElementType->FirstChild()->Value()));

				tinyxml2::XMLNode* nBuildQueueElementRemainingWork = nBuildQueueElementType->NextSibling();
				if (nullptr == nBuildQueueElementRemainingWork) MainGame::exitError("[ERROR]___: loadCityXML : City->nBuildQueue->RemainingWork == nullptr");
				blankBluid.remainingWork = std::stod(nBuildQueueElementRemainingWork->FirstChild()->Value());


				ptrCity->addBuildToQueue
				(

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
				ptrCity->GETcitizens().push_back(new Citizen);
				ptrCitizen = ptrCity->GETcitizens()[ptrCity->GETcitizens().size() - 1];

				tinyxml2::XMLNode* nTabCitizenElementtileOccupied = nTabCitizenElement->FirstChild();
				if (nullptr == nTabCitizenElementtileOccupied) MainGame::exitError("[ERROR]___: loadCityXML : City->nTabCitizen->tileOccupied == nullptr");
				ptrCitizen->SETtileOccupied(std::stoi(nTabCitizenElementtileOccupied->FirstChild()->Value()));

				tinyxml2::XMLNode* nTabCitizenElementHappiness = nTabCitizenElementtileOccupied->NextSibling();
				if (nullptr == nTabCitizenElementHappiness) MainGame::exitError("[ERROR]___: loadCityXML : City->nTabCitizen->Happiness == nullptr");
				ptrCitizen->SEThappiness(XmlConvertValue::convert2Emotion_Type(std::stoi(nTabCitizenElementHappiness->FirstChild()->Value())));

				tinyxml2::XMLNode* nTabCitizenElementFood = nTabCitizenElementHappiness->NextSibling();
				if (nullptr == nTabCitizenElementFood) MainGame::exitError("[ERROR]___: loadCityXML : City->nTabCitizen->Food == nullptr");
				ptrCitizen->SETfood(std::stoi(nTabCitizenElementFood->FirstChild()->Value()));

				tinyxml2::XMLNode* nTabCitizenElementWork = nTabCitizenElementFood->NextSibling();
				if (nullptr == nTabCitizenElementWork) MainGame::exitError("[ERROR]___: loadCityXML : City->nTabCitizen->Work == nullptr");
				ptrCitizen->SETwork(std::stoi(nTabCitizenElementWork->FirstChild()->Value()));

				tinyxml2::XMLNode* nTabCitizenElementGold = nTabCitizenElementWork->NextSibling();
				if (nullptr == nTabCitizenElementGold) MainGame::exitError("[ERROR]___: loadCityXML : City->nTabCitizen->Gold == nullptr");
				ptrCitizen->SETgold(std::stoi(nTabCitizenElementGold->FirstChild()->Value()));

				tinyxml2::XMLNode* nTabCitizenElementReligion_Type = nTabCitizenElementGold->NextSibling();
				if (nullptr == nTabCitizenElementReligion_Type) MainGame::exitError("[ERROR]___: loadCityXML : City->nTabCitizen->Religion_Type == nullptr");
				ptrCitizen->SETreligion(XmlConvertValue::convert2Religion_Type(std::stoi(nTabCitizenElementReligion_Type->FirstChild()->Value())));

				tinyxml2::XMLNode* nTabCitizenElementplace = nTabCitizenElementReligion_Type->NextSibling();
				if (nullptr == nTabCitizenElementplace) MainGame::exitError("[ERROR]___: loadCityXML : City->nTabCitizen->place == nullptr");
				ptrCitizen->SETplace(std::stoi(nTabCitizenElementplace->FirstChild()->Value()));

				nTabCitizenElement = nTabCitizenElement->NextSibling();
			}
		}


		nCity = nCity->NextSibling();
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : createSave																				    	  */
/* ROLE : Création d'un emplacement de fichier de sauvegarde (courant)									      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::createSave
(
	MainGame& mainGame
)
{
	MainGame::logfileconsole("[INFO]___: createSave Start");
	std::string destroy;

	for (unsigned int i(0); i < mainGame.GETsaveReload().GETnbSave(); i++)
	{
		if ((i + 1) != mainGame.GETsaveReload().GETtabSave()[i])
		{
			mainGame.GETsaveReload().SETcurrentSave(i + 1);
			mainGame.GETsaveReload().GETtabSave().push_back(mainGame.GETsaveReload().GETcurrentSave());
			break;
		}
		else
		{
			/* N/A */
		}
	}
	if (mainGame.GETsaveReload().GETcurrentSave() <= 0)
	{
		mainGame.GETsaveReload().SETcurrentSave(mainGame.GETsaveReload().GETnbSave() + 1);
		mainGame.GETsaveReload().GETtabSave().push_back(mainGame.GETsaveReload().GETcurrentSave());
	}
	else
	{
		/* N/A */
	}


	std::ofstream saveInfo(mainGame.GETfile().saveInfo);
	if (saveInfo)
	{
		saveInfo << "NbSave=";
		saveInfo << std::endl << mainGame.GETsaveReload().GETnbSave() + 1;
		saveInfo << std::endl << "SaveUse=";
		for (unsigned int i(0); i < mainGame.GETsaveReload().GETnbSave() + 1; i++)
			saveInfo << std::endl << mainGame.GETsaveReload().GETtabSave()[i];
	}
	else
		MainGame::logfileconsole("[ERROR]___: Impossible d'ouvrir le fichier " + mainGame.GETfile().saveInfo);

	std::string save = "save/" + std::to_string(mainGame.GETsaveReload().GETcurrentSave());
	_mkdir(save.c_str());
	mainGame.GETsaveReload().SETnbSave(mainGame.GETsaveReload().GETnbSave() + 1);

	mainGame.GETfile().saveMaps = "save/" + std::to_string(mainGame.GETsaveReload().GETcurrentSave()) + "/" + mainGame.GETfile().saveMaps;
	mainGame.GETfile().savePlayers = "save/" + std::to_string(mainGame.GETsaveReload().GETcurrentSave()) + "/" + mainGame.GETfile().savePlayers;

	MainGame::logfileconsole("[INFO]___: createSave End");
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : removeSave																				    	  */
/* ROLE : Supprime une sauvegarde du dossier de sauvegarde												      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::removeSave
(
	MainGame& mainGame
)
{
	MainGame::logfileconsole("[INFO]___: removeSave Start");
	std::string file(EMPTY_STRING);
	bool condition(false);

	if (mainGame.GETsaveReload().GETcurrentSave() != 0)
	{

		for (unsigned int i(0); i < mainGame.GETsaveReload().GETnbSave(); i++)
		{
			if (mainGame.GETsaveReload().GETcurrentSave() == (int)mainGame.GETsaveReload().GETtabSave()[i])
			{
				condition = true;
				break;
			}
			else
			{
				/* N/A */
			}
		}


		if (condition)
		{

			file = "save/" + std::to_string(mainGame.GETsaveReload().GETcurrentSave()) + "/saveMaps.txt";
			if (remove(file.c_str()) != 0)
				MainGame::logfileconsole("[ERROR]___: Impossible d'effacer le fichier " + file);
			else
				MainGame::logfileconsole("[INFO]___: file : " + file + " successfully remove");

			file = "save/" + std::to_string(mainGame.GETsaveReload().GETcurrentSave()) + "/savePlayers.xml";
			if (remove(file.c_str()) != 0)
				MainGame::logfileconsole("[ERROR]___: Impossible d'effacer le fichier " + file);
			else
				MainGame::logfileconsole("[INFO]___: file : " + file + " successfully remove");

			file = "save/" + std::to_string(mainGame.GETsaveReload().GETcurrentSave());
			if (_rmdir(file.c_str()) != 0)
				MainGame::logfileconsole("[ERROR]___: Impossible d'effacer le dossier " + file);
			else
				MainGame::logfileconsole("[INFO]___: directory : " + file + " successfully remove");

			mainGame.GETsaveReload().SETnbSave(mainGame.GETsaveReload().GETnbSave() - 1);
			if (mainGame.GETsaveReload().GETnbSave() == 0)
				mainGame.GETsaveReload().GETtabSave().clear();
			else
				mainGame.GETsaveReload().GETtabSave().erase
				(mainGame.GETsaveReload().GETtabSave().begin() + mainGame.GETsaveReload().GETcurrentSave() - 1);




			std::ofstream saveInfo(mainGame.GETfile().saveInfo);
			if (saveInfo)
			{
				saveInfo << "NbSave=";
				saveInfo << std::endl << mainGame.GETsaveReload().GETnbSave();
				saveInfo << std::endl << "SaveUse=";
				for (unsigned int i(0); i < mainGame.GETsaveReload().GETnbSave(); i++)
					saveInfo << std::endl << mainGame.GETsaveReload().GETtabSave()[i];
			}
			else
				MainGame::logfileconsole("[ERROR]___: Impossible d'ouvrir le fichier " + mainGame.GETfile().saveInfo);
		}
		else
		{
			/* N/A */
		}
	}
	else
		MainGame::logfileconsole("[ERROR]___: currentSave = 0");

	MainGame::logfileconsole("[INFO]___: removeSave End");
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : clearSave																					    	  */
/* ROLE : Supprime toutes les sauvegardes du dossier													      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::clearSave
(
	MainGame& mainGame
)
{
	MainGame::logfileconsole("[INFO]___: clearSave Start");

	for (unsigned int j(0); j < mainGame.GETsaveReload().GETnbSave(); j++)
	{
		
	}

	std::string file(EMPTY_STRING);
	for (unsigned int i(0); i < mainGame.GETsaveReload().GETnbSave(); i++)
	{
		file = "save/" + std::to_string(mainGame.GETsaveReload().GETtabSave()[i]) + "/saveMaps.txt";
		if (remove(file.c_str()) != 0)
			MainGame::logfileconsole("[ERROR]___: Impossible d'effacer le fichier " + file);
		else
			MainGame::logfileconsole("[INFO]___: file : " + file + " successfully remove");

		file = "save/" + std::to_string(mainGame.GETsaveReload().GETtabSave()[i]) + "/savePlayers.xml";
		if (remove(file.c_str()) != 0)
			MainGame::logfileconsole("[ERROR]___: Impossible d'effacer le fichier " + file);
		else
			MainGame::logfileconsole("[INFO]___: file : " + file + " successfully remove");

		file = "save/" + std::to_string(mainGame.GETsaveReload().GETtabSave()[i]);
		if (_rmdir(file.c_str()) != 0)
			MainGame::logfileconsole("[ERROR]___: Impossible d'effacer le dossier " + file);
		else
			MainGame::logfileconsole("[INFO]___: directory : " + file + " successfully remove");
	}

	std::ofstream saveInfo(mainGame.GETfile().saveInfo);
	if (saveInfo)
	{
		saveInfo << "NbSave=";
		saveInfo << std::endl << "0";
		saveInfo << std::endl << "SaveUse=";
	}
	else
		MainGame::logfileconsole("[ERROR]___: Impossible d'ouvrir le fichier " + mainGame.GETfile().saveInfo);

	mainGame.GETsaveReload().SETnbSave(0);
	mainGame.GETsaveReload().SETcurrentSave(0);
	mainGame.GETsaveReload().GETtabSave().clear();

	MainGame::logfileconsole("[INFO]___: clearSave End");
}



/* *********************************************************
 *				END SaveReload::STATIC					   *
 ********************************************************* */



 /* *********************************************************
  *				START SaveReload::METHODS				    *
  ********************************************************* */


  /* ---------------------------------------------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------------------------------------------- */
  /* NAME : SaveReload																				    	  */
  /* ROLE : Constructeur par défaut																		      */
  /* INPUT : void																							      */
  /* ---------------------------------------------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------------------------------------------- */
SaveReload::SaveReload() : _nbSave(0), _currentSave(NO_CURRENT_SAVE_SELECTED)
{
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : ~SaveReload																				    	  */
/* ROLE : Destructeur par défaut																		      */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
SaveReload::~SaveReload()
{
}


/* *********************************************************
 *				END SaveReload::METHODS					   *
 ********************************************************* */

 /*
 *	End Of File : SaveReload.cpp
 */