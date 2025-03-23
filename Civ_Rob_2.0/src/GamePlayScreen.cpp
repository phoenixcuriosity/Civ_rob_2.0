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
#include "LogSentences.h"
#include "Player.h"
#include "NewGame.h"
#include "ScreenIndices.h"
#include "Unit.h"
#include "SaveReload.h"
#include "T_NewGameScreen.h"

#include <R2D/src/ResourceManager.h>
#include <R2D/src/ErrorLog.h>
#include <R2D/src/Log.h>

GamePlayScreen::GamePlayScreen(UserInputNewGame* userInputNewGame):
R2D::IGameScreen(),
R2D::CScreen(),
R2D::IRegisterLoadAble<jsoncons::ojson>(),
R2D::IRegister(),
m_loadSub(addSubscriber()),
m_screen(),
m_var(),
m_mainMap(m_loadSub),
m_nextTurn(),
m_players(m_loadSub, &m_mainMap.GETmatriceMap()),
m_isInitialize(false),
m_userInputNewGame(userInputNewGame)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CONSTRUCTOR, logS::DATA::SCREEN);
}

R2D::RegisterPairVector GamePlayScreen::addSubscriber()
{
	R2D::RegisterPairVector registerLoad{ {this, typeid(MainMapConfig)}, {this, typeid(UnitTemplate)}, {this, typeid(CityNameTemplate)} };
	return registerLoad;
}

GamePlayScreen::~GamePlayScreen()
{
	destroy();
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DESTRUCTOR, logS::DATA::SCREEN);
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
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::ON_ENTRY, logS::DATA::START);
	init(m_game->getWindow().GETscreenWidth(), m_game->getWindow().GETscreenHeight());

	if (!m_isInitialize)
	{
		try
		{
			IRegisterLoadAble::load();

			R2D::ResourceManager::InitializeCardinalDirectionMapping
			(m_mainMap.GETtileSize());

			initStructsNULL();

			computeSize();

			initOpenGLScreen();

			/* Need to be after loadUnitAndSpec */
			m_players.init(m_screen.m_idTexture);

			m_mainMap.initMainMap(m_camera, m_screen.m_idTexture);
			//R2D::Music music = m_screen.audioEngine.loadMusic("sounds/the_field_of_dreams.mp3");

			if (SaveReload::getInstance().isSelectCurrentSave())
			{
				SaveReload::getInstance().load();

				m_var.cinState = CinState_Type::cinMainMap;
				m_players.SETselectedPlayerId(SELECTION::NO_PLAYER_SELECTED);

				makePlayersButtons();
				m_mainMap.initMainMapTexture(m_screen.m_idTexture);
			}
			else
			{
				NewGameManager::newGame(*this);
				makePlayersButtons();
			}
			m_isInitialize = true;
		}
		catch (const std::string& msg)
		{
			LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::ON_ENTRY, logS::DATA::MSG_DATA, msg);
			return false;
		}
	}
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::ON_ENTRY, logS::DATA::END);
	return true;
}

void GamePlayScreen::doInitOptimizeTexture()
{
	R2D::IdMap idMap;
	R2D::ResourceManager::copyIdMap(idMap);

	m_screen.m_idTexture[GamePlayScreenEnumTexture::grass] = R2D::ResourceManager::searchKeyInIdMap(idMap, "grass");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::grassIrr] = R2D::ResourceManager::searchKeyInIdMap(idMap, "grassIrr");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::deepwater] = R2D::ResourceManager::searchKeyInIdMap(idMap, "deepwater");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::water] = R2D::ResourceManager::searchKeyInIdMap(idMap, "water");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::coal] = R2D::ResourceManager::searchKeyInIdMap(idMap, "coal");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::copper] = R2D::ResourceManager::searchKeyInIdMap(idMap, "copper");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::fish] = R2D::ResourceManager::searchKeyInIdMap(idMap, "fish");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::iron] = R2D::ResourceManager::searchKeyInIdMap(idMap, "iron");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::petroleum] = R2D::ResourceManager::searchKeyInIdMap(idMap, "petroleum");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::stone] = R2D::ResourceManager::searchKeyInIdMap(idMap, "stone");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::tree1] = R2D::ResourceManager::searchKeyInIdMap(idMap, "tree1");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::uranium] = R2D::ResourceManager::searchKeyInIdMap(idMap, "uranium");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::ColorPlayer0] = R2D::ResourceManager::searchKeyInIdMap(idMap, "ColorPlayer0");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::ColorPlayer1] = R2D::ResourceManager::searchKeyInIdMap(idMap, "ColorPlayer1");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::ColorPlayer2] = R2D::ResourceManager::searchKeyInIdMap(idMap, "ColorPlayer2");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::ColorPlayer3] = R2D::ResourceManager::searchKeyInIdMap(idMap, "ColorPlayer3");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::ColorPlayer4] = R2D::ResourceManager::searchKeyInIdMap(idMap, "ColorPlayer4");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::ColorPlayer5] = R2D::ResourceManager::searchKeyInIdMap(idMap, "ColorPlayer5");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::ColorPlayer6] = R2D::ResourceManager::searchKeyInIdMap(idMap, "ColorPlayer6");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::ColorPlayer7] = R2D::ResourceManager::searchKeyInIdMap(idMap, "ColorPlayer7");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::ColorPlayer8] = R2D::ResourceManager::searchKeyInIdMap(idMap, "ColorPlayer8");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::life0] = R2D::ResourceManager::searchKeyInIdMap(idMap, "0.0life");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::life1] = R2D::ResourceManager::searchKeyInIdMap(idMap, "0.1life");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::life2] = R2D::ResourceManager::searchKeyInIdMap(idMap, "0.2life");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::life3] = R2D::ResourceManager::searchKeyInIdMap(idMap, "0.3life");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::life4] = R2D::ResourceManager::searchKeyInIdMap(idMap, "0.4life");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::life5] = R2D::ResourceManager::searchKeyInIdMap(idMap, "0.5life");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::life6] = R2D::ResourceManager::searchKeyInIdMap(idMap, "0.6life");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::life7] = R2D::ResourceManager::searchKeyInIdMap(idMap, "0.7life");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::life8] = R2D::ResourceManager::searchKeyInIdMap(idMap, "0.8life");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::life9] = R2D::ResourceManager::searchKeyInIdMap(idMap, "0.9life");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::maxlife] = R2D::ResourceManager::searchKeyInIdMap(idMap, "maxlife");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::city] = R2D::ResourceManager::searchKeyInIdMap(idMap, "city");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::battleoids] = R2D::ResourceManager::searchKeyInIdMap(idMap, "battleoids");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::biter] = R2D::ResourceManager::searchKeyInIdMap(idMap, "biter");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::bombardier] = R2D::ResourceManager::searchKeyInIdMap(idMap, "bombardier");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::car] = R2D::ResourceManager::searchKeyInIdMap(idMap, "car");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::ouvrier_tier_1] = R2D::ResourceManager::searchKeyInIdMap(idMap, "ouvrier_tier_1");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::ouvrier_tier_2] = R2D::ResourceManager::searchKeyInIdMap(idMap, "ouvrier_tier_2");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::ouvrier_tier_3] = R2D::ResourceManager::searchKeyInIdMap(idMap, "ouvrier_tier_3");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::robot] = R2D::ResourceManager::searchKeyInIdMap(idMap, "robot");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::rocket] = R2D::ResourceManager::searchKeyInIdMap(idMap, "rocket");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::rover] = R2D::ResourceManager::searchKeyInIdMap(idMap, "rover");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::satellite] = R2D::ResourceManager::searchKeyInIdMap(idMap, "satellite");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::settler] = R2D::ResourceManager::searchKeyInIdMap(idMap, "settler");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::spitter] = R2D::ResourceManager::searchKeyInIdMap(idMap, "spitter");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::tank] = R2D::ResourceManager::searchKeyInIdMap(idMap, "tank");
	m_screen.m_idTexture[GamePlayScreenEnumTexture::transport_plan] = R2D::ResourceManager::searchKeyInIdMap(idMap, "transport_plan");
}

void GamePlayScreen::doInitUI()
{
	if (!m_isInitialize)
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
}

void GamePlayScreen::doInitHUDText()
{
	std::string buffer = std::format("Civ_Rob_2.0 : version {}.{}.{}", "0", 25, "xxxx");
	R2D::ResourceManager::getSpriteFont()->draw
	(
		m_spriteBatchHUDStatic,
		buffer.c_str(),
		glm::vec2(0.0f, 2.0f), // offset pos
		glm::vec2(R2D::SpriteFont::getScaleFontToScreen(1.28f)), // size
		0.0f,
		R2D::COLOR_WHITE
	);
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
		GameInput::updateSDLInputCycle
		(
			ev,
			m_game->getInputManager(),
			m_camera,
			m_mainMap,
			m_players,
			getParentWindow(),
			m_screen.m_nextScreenIndexMenu,
			m_currentState
		);
		updateInputManager(ev, m_game->getInputManager());
	}
	GameInput::processInput(*this);
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
	// background
	m_mainMap.renderMap();
	// first depth
	m_players.renderCity();
	// front depth
	m_players.renderUnit();

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

void GamePlayScreen::makePlayersButtons()
{
	float X_POS = 0.01f;
	float Y_POS = 0.20f;
	const float DIMS_PIXELS = 20.0f;
	const float PADDING = 0.035f;
	const float TEXT_SCALE = 0.6f;
	const int GROUP_ID = 1;

	/* Clear buffer */
	m_screen.m_vectPlayerRadioButton.clear();
	m_screen.m_widgetLabels.clear();

	/* Resize buffer */
	m_screen.m_vectPlayerRadioButton.resize(m_userInputNewGame->vectPlayerName.size());
	m_screen.m_widgetLabels.resize(m_userInputNewGame->vectPlayerName.size());

	for (size_t i(0); i < m_screen.m_vectPlayerRadioButton.size(); i++)
	{
		m_screen.m_vectPlayerRadioButton[i]
			= static_cast<CEGUI::RadioButton*>
			(m_gui.createWidget(
				"TaharezLook/RadioButton",
				glm::vec4(X_POS, Y_POS += PADDING, 0.0f, 0.0f),
				glm::vec4(0.0f, 0.0f, DIMS_PIXELS, DIMS_PIXELS),
				m_userInputNewGame->vectPlayerName[i]));

		m_screen.m_vectPlayerRadioButton[i]->setSelected(false);

		m_screen.m_vectPlayerRadioButton[i]->subscribeEvent
		(CEGUI::RadioButton::EventMouseClick,
			CEGUI::Event::Subscriber(&GamePlayScreen::onPlayerButtonClicked, this));
		m_screen.m_vectPlayerRadioButton[i]->setGroupID(GROUP_ID);

		m_screen.m_widgetLabels[i] = R2D::WidgetLabel(
			m_screen.m_vectPlayerRadioButton[i],
			m_userInputNewGame->vectPlayerName[i],
			TEXT_SCALE);

	}
}

bool GamePlayScreen::onPlayerButtonClicked(const CEGUI::EventArgs& /* e */)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::BUTTON_CLICK, logS::DATA::PLAYER_BUTTON);
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
						m_players.GETselectedPlayerPtr()->GETSelectedUnitPtr()->m_show = true;
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
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::BUTTON_CLICK, logS::DATA::EXIT_BUTTON);
	SaveReload::getInstance().save();

	m_currentState = R2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}