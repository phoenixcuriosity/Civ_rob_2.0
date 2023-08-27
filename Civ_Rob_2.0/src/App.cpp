/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.4.0
	file version : 1.14

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


#include <tinyxml2/tinyxml2.h>

#include <RealEngine2D/src/ResourceManager.h> 
#include <RealEngine2D/src/ErrorLog.h> 
#include <RealEngine2D/src/ExitFromError.h> 
#include <RealEngine2D/src/SpriteFont.h> 


namespace AppH
{
	const std::string configFilePath = "bin/filePath.xml";
}

App::App()
:
RealEngine2D::IMainGame(),
m_mainMenuScreen(nullptr),
m_newGameScreen(nullptr),
m_reloadMenuScreen(nullptr),
m_gamePlayScreen(nullptr),
m_CityScreen(nullptr),
m_saveReload()
{
	RealEngine2D::ResourceManager::initializeRGBA8Map();
}

App::~App()
{
	m_mainMenuScreen.reset();
	m_newGameScreen.reset();
	m_reloadMenuScreen.reset();
	m_gamePlayScreen.reset();
	m_CityScreen.reset();
	RealEngine2D::ExitFromError::deleteAll();
}

void App::onInit()
{
	/* Set location of logging file */
	RealEngine2D::ResourceManager::initializeFilePath(e_Files::log, "bin/log/log.txt");
	RealEngine2D::ErrorLog::initializeLog();

	initMain();

	m_window.SETscreenWidth(RealEngine2D::Window::getHorizontal());
	m_window.SETscreenHeight(RealEngine2D::Window::getVertical());
	
	m_saveReload.init(RealEngine2D::ResourceManager::getFile(e_Files::saveInfo)->getPath());
}


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initShaders																   */
/* ROLE : Init shaders for OpenGL													   */
/* ROLE : 2 files : colorShadingVert and colorShadingFrag							   */
/* ROLE : 3 parameters : vertexPosition	, vertexColor , vertexUV					   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void App::InitShaders()
{
	RealEngine2D::ResourceManager::getGLSLProgram().compileShaders
	(
		RealEngine2D::ResourceManager::getFile(e_Files::colorShadingVert)->getPath(),
		RealEngine2D::ResourceManager::getFile(e_Files::colorShadingFrag)->getPath()
	);
	RealEngine2D::ResourceManager::getGLSLProgram().addAttribut("vertexPosition");
	RealEngine2D::ResourceManager::getGLSLProgram().addAttribut("vertexColor");
	RealEngine2D::ResourceManager::getGLSLProgram().addAttribut("vertexUV");
	RealEngine2D::ResourceManager::getGLSLProgram().linkShaders();
	RealEngine2D::ResourceManager::getSpriteFont()
		= std::make_shared<RealEngine2D::SpriteFont>
		(RealEngine2D::FONT::GUI::NAME.c_str(), RealEngine2D::FONT::GUI::SIZE::DEFAULT);
}


void App::onExit()
{
	/* Do nothing */
}

void App::addScreens()
{
	/* Create shared Ptr */
	m_mainMenuScreen = std::make_shared<MainMenuScreen>();

	m_newGameScreen = std::make_shared<NewGameScreen>();

	m_reloadMenuScreen = std::make_shared<ReloadMenuScreen>
		(
			& m_saveReload
		);

	m_gamePlayScreen = std::make_shared<GamePlayScreen>
		(
			&m_saveReload,
			m_newGameScreen->getUserInputNewGame()
		);

	m_CityScreen = std::make_shared<CityScreen>
		(
			&m_saveReload,
			&m_gamePlayScreen->GETPlayers(),
			m_gamePlayScreen->GETmainMap().GETtileSizePtr()
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
/* NAME : initMain																	   */
/* ROLE : Chargement des informations de la configuration du jeu					   */
/* INPUT : struct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void App::initMain()
{
	RealEngine2D::ErrorLog::logEvent("[INFO]___: [START] : initMain");

	tinyxml2::XMLDocument config{};
	config.LoadFile(AppH::configFilePath.c_str());

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

		RealEngine2D::ResourceManager::initializeFilePath
		(
			e_Files::readme,
			config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Readme)->GetText()
		);
		RealEngine2D::ResourceManager::initializeFilePath
		(
			e_Files::texts,
			config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Texte)->GetText()
		);
		RealEngine2D::ResourceManager::initializeFilePath
		(
			e_Files::mainMap,
			config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_MainMap)->GetText()
		);
		RealEngine2D::ResourceManager::initializeFilePath
		(
			e_Files::buildings,
			config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Building)->GetText()
		);
		RealEngine2D::ResourceManager::initializeFilePath
		(
			e_Files::citiesNames,
			config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_CitieName)->GetText()
		);
		RealEngine2D::ResourceManager::initializeFilePath
		(
			e_Files::units,
			config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Unit)->GetText()
		);
		RealEngine2D::ResourceManager::initializeFilePath
		(
			e_Files::specNames,
			config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SpecName)->GetText()
		);
		RealEngine2D::ResourceManager::initializeFilePath
		(
			e_Files::saveInfo,
			config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SaveInfo)->GetText()
		);
		RealEngine2D::ResourceManager::initializeFilePath
		(
			e_Files::saveMaps,
			config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SaveMaps)->GetText()
		);
		RealEngine2D::ResourceManager::initializeFilePath
		(
			e_Files::savePlayers,
			config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SavePlayer)->GetText()
		);
		RealEngine2D::ResourceManager::initializeFilePath
		(
			e_Files::colorShadingVert,
			config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ColorShadingVert)->GetText()
		);
		RealEngine2D::ResourceManager::initializeFilePath
		(
			e_Files::colorShadingFrag,
			config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ColorShadingFrag)->GetText()
		);
		RealEngine2D::ResourceManager::initializeFilePath
		(
			e_Files::imagesPath,
			config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ImagesPath)->GetText()
		);
		RealEngine2D::ResourceManager::initializeFilePath
		(
			e_Files::GUIPath,
			config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_GUIPath)->GetText()
		);
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + (std::string)AppH::configFilePath);
	}

	RealEngine2D::ErrorLog::logEvent("[INFO]___: [END] : initMain");
}


//----------------------------------------------------------Destroy----------------------------------------------------------------//

void App::destroy()
{
	RealEngine2D::ExitFromError::deleteAll();
}
