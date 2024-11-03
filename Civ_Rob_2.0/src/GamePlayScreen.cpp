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

#include "GamePlayScreen.h"

#include "App.h"
#include "Player.h"
#include "ScreenIndices.h"
#include "Unit.h"
#include "Utility.h"
#include "T_Unit.h"
#include "XmlConvertValue.h"

#include <tinyxml2/tinyxml2.h>

#include <R2D/src/ResourceManager.h> 
#include <R2D/src/ErrorLog.h> 
#include <R2D/src/tinyXml2.h> 



namespace DELTA_TIME
{
	constexpr float MS_PER_SECOND(1000.0f);
	const float TARGET_FRAMETIME = MS_PER_SECOND / (float)R2D::SCREEN_REFRESH_RATE;
	constexpr unsigned int MAX_PHYSICS_STEPS(6);
	constexpr float MAX_DELTA_TIME(1.0f);
}


GamePlayScreen::GamePlayScreen
(
	SaveReloadPtrT SaveReload,
	UserInputNewGame* userInputNewGame
)
: 
R2D::IGameScreen(),
R2D::CScreen(),
m_screen(),
m_var(),
m_mainMap(),
m_nextTurn(),
m_players(),
m_SaveReload(SaveReload),
m_isInitialize(false),
m_userInputNewGame(userInputNewGame)
{
	build();
}

GamePlayScreen::~GamePlayScreen()
{
	destroy();
}

int GamePlayScreen::getNextScreenIndex()const
{
	return m_screen.m_nextScreenIndexMenu;
}
int GamePlayScreen::getPreviousScreenIndex()const
{
	return SCREEN_INDEX::MAINMENU;
}

void GamePlayScreen::build()
{
	m_screenIndex = SCREEN_INDEX::GAMEPLAY;
}

void GamePlayScreen::destroy()
{
	end();

	m_screen.m_widgetLabels.clear();

	m_players.deleteAllPlayers();
}

bool GamePlayScreen::onEntry()
{
	init(m_game->getWindow().GETscreenWidth(), m_game->getWindow().GETscreenHeight());

	if (!m_isInitialize)
	{
		loadFile();

		R2D::ResourceManager::InitializeCardinalDirectionMapping
			(m_mainMap.GETtileSize());

		initStructsNULL();

		computeSize();

		initOpenGLScreen();

		loadUnitAndSpec();

		loadCitiesNames();

		/* Need to be after loadUnitAndSpec */
		m_players.init(R2D::ResourceManager::getFile(R2D::e_Files::imagesPath)->getPath());

		try
		{
			m_mainMap.initMainMap(m_camera);
			//R2D::Music music = m_screen.audioEngine.loadMusic("sounds/the_field_of_dreams.mp3");

			if (m_SaveReload->GETcurrentSave() != SELECTION::NO_CURRENT_SAVE_SELECTED)
			{
				m_SaveReload->reload(*this);
			}
			else
			{
				newGame();
			}

		}
		catch (const std::string& msg)
		{
			R2D::ErrorLog::logEvent("[ERROR]___: GamePlayScreen::onEntry : " + msg);
			return false;
		}

		m_isInitialize = true;
	}
	return true;
}

void GamePlayScreen::doInitUI()
{
	/* MainMenuButton */
	CEGUI::PushButton* mainMenuButton = static_cast<CEGUI::PushButton*>
		(m_gui.createWidget(
			"AlfiskoSkin/Button",
			{ 0.0f, 0.0f, 0.1f, 0.05f },
			{ 0,0,0,0 },
			"TestButton"));

	mainMenuButton->setText("Main Menu");
	mainMenuButton->subscribeEvent
	(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GamePlayScreen::onExitClicked, this)
	);
}

void GamePlayScreen::doInitHUDText()
{
	std::string buffer = std::format("Civ_Rob_2.0 : version {}.{}.{}", "0", 25, "xxxx");
	R2D::ResourceManager::getSpriteFont()->draw
	(
		m_spriteBatchHUDStatic,
		buffer.c_str(),
		glm::vec2(0.0f, 2.0f), // offset pos
		glm::vec2(R2D::SpriteFont::getScaleFontToScreen(1.28)), // size
		0.0f,
		R2D::COLOR_WHITE
	);

	/*
	static GLuint id = R2D::ResourceManager::getTexture("bin/image/toolbar.png")->GETid();
	m_screen.openGLScreen.spriteBatchHUDStatic.draw
	(
		glm::vec4(0.0f, 0.0f, (int)ceil((m_mainMap.GETtoolBarSize() + 1) * m_mainMap.GETtileSize()), m_screen.screenHeight),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		id,
		0.0f,
		R2D::COLOR_WHITE
	)*/
}

void GamePlayScreen::onExit()
{
	/* Do nothing */
}

void GamePlayScreen::update()
{
	SDL_Event ev{};

	/* Get Input */
	while (SDL_PollEvent(&ev))
	{
		m_game->onSDLEvent(ev);
		inputSDL(ev);
		mouseClick(ev);
		updateInputManager(ev, m_game->getInputManager());
	}

	/* Process Input */
	actionByKey();
	moveCameraByDeltaTime();
}

void GamePlayScreen::draw()
{
	drawAll();
}

void GamePlayScreen::doDrawAll()
{
	/* --- Draw --- */
	m_mainMap.drawMap(m_camera, m_game->getWindow());

	m_players.isAUnitSelected();
	m_players.drawUnit(m_mainMap, m_camera);
	m_players.drawCity(m_mainMap, m_camera, R2D::ResourceManager::getSpriteFont());

	/* --- Render --- */
	m_mainMap.renderMap();
	m_players.renderUnit();
	m_players.renderCity();

	static const float FONT_SIZE_G = R2D::SpriteFont::getScaleFontToScreen(0.32f);


	std::string buffer = std::format("FPS : {}",  m_game->getFPS());
	R2D::ResourceManager::getSpriteFont()->draw
	(
		m_spriteBatchHUDDynamic,
		buffer.c_str(),
		glm::vec2(0.0f, 32.0f), // offset pos
		glm::vec2(FONT_SIZE_G), // size
		0.0f,
		R2D::COLOR_WHITE
	);

	buffer = std::format("Nb Turn : {}", m_nextTurn.GETnbTurn());
	R2D::ResourceManager::getSpriteFont()->draw
	(
		m_spriteBatchHUDDynamic,
		buffer.c_str(),
		glm::vec2(0.0f, 64.0f), // offset pos
		glm::vec2(FONT_SIZE_G), // size
		0.0f,
		R2D::COLOR_BLUE
	);

#ifdef _DEBUG

	buffer = std::format("Scale : {}", m_camera.GETscale());
	R2D::ResourceManager::getSpriteFont()->draw
	(
		m_spriteBatchHUDDynamic,
		buffer.c_str(),
		glm::vec2(0.0f, 500.0f), // offset pos
		glm::vec2(FONT_SIZE_G), // size
		0.0f,
		R2D::COLOR_RED
	);

#endif // _DEBUG

	for (auto& l : m_screen.m_widgetLabels)
		l.draw(m_spriteBatchHUDDynamic, *R2D::ResourceManager::getSpriteFont(), m_game->getWindow());

}

void GamePlayScreen::loadFile()
{
	R2D::ErrorLog::logEvent("[INFO]___: [START] : initMain");

	tinyxml2::XMLDocument config{};
	config.LoadFile(R2D::ResourceManager::getFile(R2D::e_Files::mainMap)->getPath().c_str());
	unsigned int tmp{ 0 };

	if (config.ErrorID() == 0)
	{
		tinyxml2::XMLElement* node = R2D::tinyXml2::getFirstElement(config);

		if (nullptr != node)
		{
			node->QueryUnsignedText(&tmp);
			m_mainMap.SETtileSize(tmp);
		}
		node = node->NextSiblingElement();

		if (nullptr != node)
		{
			node->QueryUnsignedText(&tmp);
			m_mainMap.SETmapSizePixX(tmp);
		}
		node = node->NextSiblingElement();

		if (nullptr != node)
		{
			node->QueryUnsignedText(&tmp);
			m_mainMap.SETmapSizePixY(tmp);
		}
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + R2D::ResourceManager::getFile(R2D::e_Files::mainMap)->getPath());
	}

	R2D::ErrorLog::logEvent("[INFO]___: [END] : initMain");
}

void GamePlayScreen::initStructsNULL()
{
	m_var.tempPlayerName = STRINGS::EMPTY;
	m_var.select = Select_Type::selectnothing;
	m_var.statescreen = State_Type::error;
	m_var.cinState = CinState_Type::cinNothing;
}

void GamePlayScreen::computeSize()
{
	m_mainMap.SETtoolBarSize
	(
		(unsigned int)std::ceil
		(
			(double)(m_game->getWindow().GETscreenWidth() / 8)
			/
			(double)m_mainMap.GETtileSize()
		)
	);
}

void GamePlayScreen::initOpenGLScreen()
{
	m_screen.audioEngine.init();

	m_game->getInputManager().init(m_mainMap.GETtileSizePtr());
}

void GamePlayScreen::loadUnitAndSpec()
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

		m_players.GETvectUnitTemplate().push_back(currentUnit);

		node = node->NextSibling();
	}
}

void GamePlayScreen::loadCitiesNames()
{
	unsigned int nbcity{ 0 };
	std::string city{ STRINGS::EMPTY}, dummy{ STRINGS::EMPTY };
	std::ifstream CITIENAME{ R2D::ResourceManager::getFile(R2D::e_Files::citiesNames)->getPath() };


	if (CITIENAME)
	{
		CITIENAME >> dummy;

		CITIENAME >> nbcity;
		m_players.GETvectCityName().resize(nbcity);

		for (auto& c : m_players.GETvectCityName())
		{
			CITIENAME >> c;
		}
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + R2D::ResourceManager::getFile(R2D::e_Files::citiesNames)->getPath());
	}
}

void GamePlayScreen::moveCameraByDeltaTime()
{
	static Uint32 prevTicks{ SDL_GetTicks() };
	Uint32 frameTime{ 0 }, newTicks{ 0 };
	float totalDeltaTime{ 0.0f }, deltaTime{ 0.0f };

	newTicks = SDL_GetTicks();
	frameTime = newTicks - prevTicks;
	prevTicks = newTicks;
	totalDeltaTime = (float)frameTime / DELTA_TIME::TARGET_FRAMETIME;
	int i{ 0 };

	while (totalDeltaTime > 0.0f && i < DELTA_TIME::MAX_PHYSICS_STEPS)
	{
		deltaTime = std::min(totalDeltaTime, DELTA_TIME::MAX_DELTA_TIME);
		moveCamera(deltaTime);
		totalDeltaTime -= deltaTime;
		i++;
	}
}

bool GamePlayScreen::onPlayerButtonClicked(const CEGUI::EventArgs& /* e */)
{
	for (size_t i(0); i < m_screen.m_vectPlayerRadioButton.size(); i++)
	{
		if (m_screen.m_vectPlayerRadioButton[i]->isSelected())
		{
			if (i != m_players.GETselectedPlayerId())
			{
				/* Reset if needed SHOW for the unit previously selected */
				if (m_players.GETselectedPlayerId() != SELECTION::NO_PLAYER_SELECTED && m_players.GETselectedPlayerPtr() != nullptr)
				{			
					if (m_players.GETselectedPlayerPtr()->GETselectedUnit() != SELECTION::NO_UNIT_SELECTED)
					{
						m_players.GETselectedPlayerPtr()->GETSelectedUnitPtr()->SETshow(true);
						m_players.SETneedToUpdateDrawUnit(true);

						m_players.GETselectedPlayerPtr()->SETselectedUnit(SELECTION::NO_UNIT_SELECTED);
					}
				}

				/* Select player i */
				m_players.SETselectedPlayerId((int)i);
				m_players.SETselectedPlayerPtr(m_players.GETvectPlayer()[i]);
			}
			
			return true;
		}
	}
	return true;
}

bool GamePlayScreen::onExitClicked(const CEGUI::EventArgs& /* e */)
{
	SaveReload::save(*this);

	m_currentState = R2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}



Screen& GamePlayScreen::GETscreen()
{
	return m_screen;
};

const Screen& GamePlayScreen::GETscreen()const
{
	return m_screen;
};

Var& GamePlayScreen::GETvar()
{ 
	return m_var;
};

const Var& GamePlayScreen::GETvar()const
{
	return m_var; 
};

MainMap& GamePlayScreen::GETmainMap()
{
	return m_mainMap;
};

const MainMap& GamePlayScreen::GETmainMap()const
{ 
	return m_mainMap; 
};

Players& GamePlayScreen::GETPlayers()
{ 
	return m_players;
};

const Players& GamePlayScreen::GETPlayers()const
{
	return m_players; 
};

SaveReloadPtrT GamePlayScreen::getSaveReload()
{ 
	return m_SaveReload; 
};

UserInputNewGame* GamePlayScreen::getUserInputNewGame()
{ 
	return m_userInputNewGame;
};

void GamePlayScreen::SETvar(Var& var)
{ 
	m_var = var; 
};

void GamePlayScreen::SETmainMap(MainMap& mainMap)
{
	m_mainMap = mainMap; 
};

void GamePlayScreen::SETPlayers(Players& players)
{ 
	m_players = players;
};

R2D::Window& GamePlayScreen::getParentWindow()
{
	return m_game->getWindow();
}