/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.1.0
	file version : 1.8

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

#include "App.h"

#include <RealEngine2D/src/ScreenList.h>

#include <iostream>

#include <tinyxml2/tinyxml2.h>

static std::ofstream* ptrlogger;

App::App()
:
RealEngine2D::IMainGame(),
m_mainMenuScreen(nullptr),
m_newGameScreen(nullptr),
m_reloadMenuScreen(nullptr),
m_gamePlayScreen(nullptr),
m_CityScreen(nullptr),
m_file(),
m_saveReload()
{
	/* Do nothing */
}

App::~App()
{
	m_mainMenuScreen.reset();
	m_newGameScreen.reset();
	m_reloadMenuScreen.reset();
	m_gamePlayScreen.reset();
	m_CityScreen.reset();
	deleteAll();
}

void App::onInit()
{
	/* Set location of logging file */
	m_file.log = "bin/log/log.txt";

	initFile();

	ptrlogger = &m_logger;

	initMain();

	m_window.SETscreenWidth(RealEngine2D::Window::getHorizontal());
	m_window.SETscreenHeight(RealEngine2D::Window::getVertical());

	m_saveReload.init(m_file.saveInfo);
}

void App::onExit()
{
	/* Do nothing */
}

void App::addScreens()
{
	/* Create shared Ptr */
	m_mainMenuScreen = std::make_shared<MainMenuScreen>(&m_file);
	m_newGameScreen = std::make_shared<NewGameScreen>(&m_file);
	m_reloadMenuScreen = std::make_shared<ReloadMenuScreen>(&m_file, &m_saveReload);
	m_gamePlayScreen = std::make_shared<GamePlayScreen>(&m_file, &m_saveReload, m_newGameScreen->getUserInputNewGame());
	m_CityScreen = std::make_shared<CityScreen>
		(
			&m_file, &m_saveReload,
			&m_gamePlayScreen->GETPlayers(),
			m_gamePlayScreen->GETmainMap().GETtileSizePtr(),
			&m_gamePlayScreen->GETscreen()
		);

	/* Add Screen to listed Screen */
	m_screenList->addScreen(m_mainMenuScreen);
	m_screenList->addScreen(m_newGameScreen);
	m_screenList->addScreen(m_reloadMenuScreen);
	m_screenList->addScreen(m_gamePlayScreen);
	m_screenList->addScreen(m_CityScreen);

	/* Set default Screen */
	m_screenList->setScreen(m_mainMenuScreen->GETscreenIndex());
}





/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initFile																	   */
/* ROLE : Initialisation des fichiers : log											   */
/* INPUT : struct File& : nom des fichiers											   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void App::initFile()
{
	m_logger.open(m_file.log, std::ofstream::out | std::ofstream::trunc);
	if (!m_logger.is_open())
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		/* N/A */
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initMain																	   */
/* ROLE : Chargement des informations de la configuration du jeu					   */
/* INPUT : struct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void App::initMain()
{
	logfileconsole("[INFO]___: [START] : initMain");

	tinyxml2::XMLDocument config{};
	config.LoadFile(configFilePath.c_str());

	if (config.ErrorID() == 0)
	{
		const char* root("Config");


		const char
			* s_FilePaths("FilePaths"),
				* s_Readme("Readme"),
				* s_Texte("Texts"),
				* s_MainMap("MainMap"),
				* s_Building("Buildings"),
				* s_CitieName("CitiesNames"),
				* s_Unit("Units"),
				* s_SpecName("SpecNames"),
				* s_SaveInfo("SaveInfo"),
				* s_SaveMaps("SaveMaps"),
				* s_SavePlayer("SavePlayers"),
				* s_ColorShadingVert("ColorShadingVert"),
				* s_ColorShadingFrag("ColorShadingFrag"),
				* s_ImagesPath("ImagesPath"),
				* s_GUIPath("GUIPath");

		m_file.readme = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Readme)->GetText();
		m_file.texts = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Texte)->GetText();
		m_file.mainMap = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_MainMap)->GetText();
		m_file.buildings = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Building)->GetText();
		m_file.citiesNames = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_CitieName)->GetText();
		m_file.units = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Unit)->GetText();
		m_file.specNames = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SpecName)->GetText();
		m_file.saveInfo = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SaveInfo)->GetText();
		m_file.saveMaps = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SaveMaps)->GetText();
		m_file.savePlayers = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SavePlayer)->GetText();
		m_file.colorShadingVert = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ColorShadingVert)->GetText();
		m_file.colorShadingFrag = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ColorShadingFrag)->GetText();
		m_file.imagesPath = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ImagesPath)->GetText();
		m_file.GUIPath = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_GUIPath)->GetText();
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + (std::string)configFilePath);
	}

	logfileconsole("[INFO]___: [END] : initMain");
}


//----------------------------------------------------------Destroy----------------------------------------------------------------//

void App::destroy()
{
	deleteAll();
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : exitError																	   */
/* ROLE : Enregistre l'erreur survenue et termine le programme de façon sécurisée	   */
/* INPUT : const std::string msg : message de l'erreur								   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void App::exitError
(
	const std::string& msg
)
{
	logfileconsole("[ERROR]___: " + msg);
	deleteAll();
	logfileconsole("[ERROR]___: Last msg before exitError : " + msg);
	ptrlogger->close();
	exit(EXIT_FAILURE);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : deleteAll																	   */
/* ROLE : Destruction des allocations dynamique du programme						   */
/* ROLE : Destruction de la fenetre et du Renderer de la SDL						   */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void App::deleteAll()
{
	logfileconsole("[INFO]___: [START] *********_________ DeleteAll _________*********");




	/* *********************************************************
	 *				 START delete SDL						   *
	 ********************************************************* */


	SDL_Quit();

	/* *********************************************************
	 *				 END delete SDL							   *
	 ********************************************************* */

	 /* ### Don't put code below here ### */

	logfileconsole("[INFO]___: [END] : *********_________ DeleteAll _________*********");

	logfileconsole("[INFO]___: SDL_Quit Success");
	logfileconsole("[INFO]___:________PROGRAMME FINISH________");
	ptrlogger->close();
}

//----------------------------------------------------------Logger----------------------------------------------------------------//


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : logfileconsole															   */
/* ROLE : Transmission du message sur la console et dans le fichier log.txt			   */
/* INPUT : const std::string msg : message											   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void App::logfileconsole
(
	const std::string& msg
)
{
	time_t now{ time(0) };
	struct tm  tstruct{};
	char  buf[80]{};
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%F %X", &tstruct);

#ifdef _DEBUG
	std::cout << std::endl << buf << "      " << msg;
#endif // DEBUG_MODE
	*ptrlogger << std::endl << buf << "      " << msg;
}