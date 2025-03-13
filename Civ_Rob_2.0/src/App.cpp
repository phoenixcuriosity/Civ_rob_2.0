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

#include "App.h"

#include "CityScreen.h"
#include "GamePlayScreen.h"
#include "jsonloader.h"
#include "LogSentences.h"
#include "MainMenuScreen.h"
#include "NewGameScreen.h"
#include "ReloadMenuScreen.h"

#include <jsoncons/json.hpp>
#include <R2D/src/ResourceManager.h> 
#include <R2D/src/ErrorLog.h> 
#include <R2D/src/Log.h> 
#include <R2D/src/ExitFromError.h> 
#include <R2D/src/SpriteFont.h>
#include <R2D/src/ScreenList.h>

namespace FILE_APP
{
	namespace PATH
	{
		constexpr char CONFIG[] = "bin/filePath.json";
		constexpr char LOG[] = "bin/log/log.txt";
	}
}

App::App()
:
R2D::IMainGame(),
m_mainMenuScreen(nullptr),
m_newGameScreen(nullptr),
m_reloadMenuScreen(nullptr),
m_gamePlayScreen(nullptr),
m_CityScreen(nullptr)
{
	R2D::ResourceManager::initializeRGBA8Map();
}

App::~App()
{
	m_mainMenuScreen.reset();
	m_newGameScreen.reset();
	m_reloadMenuScreen.reset();
	m_gamePlayScreen.reset();
	m_CityScreen.reset();
	R2D::ExitFromError::deleteAll();
}

void App::onInit()
{
	/* Set location of logging file */
	R2D::ResourceManager::initializeFilePath(R2D::e_Files::log, FILE_APP::PATH::LOG);
	R2D::ErrorLog::initializeLog();
	R2D::Logger::instance().init(R2D::LogLevelType::info, R2D::FileLineFunctionType::dont_show);

	initMain();

	SaveReload::getInstance().init();

	m_window.SETscreenWidth(R2D::Window::getHorizontal());
	m_window.SETscreenHeight(R2D::Window::getVertical());
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
	R2D::ResourceManager::getGLSLProgram().compileShaders
	(
		R2D::ResourceManager::getFile(R2D::e_Files::colorShadingVert)->getPath(),
		R2D::ResourceManager::getFile(R2D::e_Files::colorShadingFrag)->getPath()
	);
	R2D::ResourceManager::getGLSLProgram().addAttribut("vertexPosition");
	R2D::ResourceManager::getGLSLProgram().addAttribut("vertexColor");
	R2D::ResourceManager::getGLSLProgram().addAttribut("vertexUV");
	R2D::ResourceManager::getGLSLProgram().linkShaders();
	R2D::ResourceManager::getSpriteFont()
		= std::make_shared<R2D::SpriteFont>
		(R2D::FONT::GUI::NAME.c_str(), R2D::FONT::GUI::SIZE::DEFAULT);
}

void App::InitTexture()
{
	R2D::ResourceManager::loadTextureFromDir(R2D::ResourceManager::getFile(R2D::e_Files::imagesPath)->getPath());
}


void App::onExit()
{
	/* Do nothing */
}

void App::addScreens()
{
	m_mainMenuScreen = std::make_shared<MainMenuScreen>();
	m_newGameScreen = std::make_shared<NewGameScreen>();
	m_reloadMenuScreen = std::make_shared<ReloadMenuScreen>();
	m_gamePlayScreen = std::make_shared<GamePlayScreen>(m_newGameScreen->getUserInputNewGame());
	m_CityScreen = std::make_shared<CityScreen>(&m_gamePlayScreen->GETPlayers(), m_gamePlayScreen->GETmainMap().GETtileSizePtr());

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
	LOG(R2D::LogLevelType::info, 0, logS::WHO::APP, logS::WHAT::INIT_MAIN, logS::DATA::START);

	try
	{
		const std::string text{ R2D::ResourceManager::loadFileToString(FILE_APP::PATH::CONFIG) };

		const jsoncons::ojson configuration = jsoncons::ojson::parse(text);

		if (configuration.contains(jsonloader::KEY_FILE_PATH) && configuration[jsonloader::KEY_FILE_PATH].is_array())
		{
			const auto filepaths = configuration[jsonloader::KEY_FILE_PATH].as<std::vector<std::string>>();

			if (filepaths.size() == R2D::NUMBER_OF_FILEPATH)
			{
				for (size_t i{0}; i < R2D::NUMBER_OF_FILEPATH; i++)
				{
					R2D::ResourceManager::initializeFilePath
					(
						R2D::tab_e_Files[i],
						filepaths[i]
					);
				}
			}
			else
			{
				throw("Diff between code and json");
			}
		}
		else
		{
			LOG(R2D::LogLevelType::error, 0, logS::WHO::APP, logS::WHAT::INIT_MAIN, logS::DATA::MISSING_KEY_JSON,
				R2D::ResourceManager::getFile(R2D::e_Files::mainMap)->getPath(), jsonloader::KEY_FILE_PATH);
		}
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::APP, logS::WHAT::INIT_MAIN, logS::DATA::ERROR_KEY_JSON, e.what());
	}

	LOG(R2D::LogLevelType::info, 0, logS::WHO::APP, logS::WHAT::INIT_MAIN, logS::DATA::END);
}


//----------------------------------------------------------Destroy----------------------------------------------------------------//

void App::destroy()
{
	R2D::ExitFromError::deleteAll();
}
