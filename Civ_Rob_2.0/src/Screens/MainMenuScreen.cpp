/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.9.0
	file version : 1.12

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

#include "MainMenuScreen.h"

#include "LogSentences.h"
#include "ScreenIndices.h"

#include "App.h"

#include <R2D/src/ResourceManager.h> 
#include <R2D/src/ErrorLog.h> 
#include <R2D/src/Log.h> 
#include <R2D/src/SpriteFont.h> 

MainMenuScreen::MainMenuScreen()
: 
R2D::IGameScreen(),
R2D::CScreen(),
m_nextScreenIndexMenu(R2D::SCREEN_INDEX::INIT),
m_isInitialize(false)
{
	build();
	LOG(R2D::LogLevelType::info, 0, logS::WHO::MAIN_MENU, logS::WHAT::CONSTRUCTOR, logS::DATA::EMPTY_DATA);
}

MainMenuScreen::~MainMenuScreen()
{
	destroy();
	LOG(R2D::LogLevelType::info, 0, logS::WHO::MAIN_MENU, logS::WHAT::DESTRUCTOR, logS::DATA::EMPTY_DATA);
}

int MainMenuScreen::getNextScreenIndex()const
{
	return m_nextScreenIndexMenu;
}
int MainMenuScreen::getPreviousScreenIndex()const
{
	return R2D::SCREEN_INDEX::INIT;
}

void MainMenuScreen::build()
{
	m_screenIndex = SCREEN_INDEX::MAINMENU;
}

void MainMenuScreen::destroy()
{
	end();
}

bool MainMenuScreen::onEntry()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::MAIN_MENU, logS::WHAT::ON_ENTRY, logS::DATA::START);

	if (!m_isInitialize)
	{
		init(m_game->getWindow().GETscreenWidth(), m_game->getWindow().GETscreenHeight());
		m_isInitialize = true;
	}

	LOG(R2D::LogLevelType::info, 0, logS::WHO::MAIN_MENU, logS::WHAT::ON_ENTRY, logS::DATA::END);
	return true;
}

void MainMenuScreen::doInitOptimizeTexture()
{
	/* Do nothing */
}

void MainMenuScreen::doInitUI()
{
	const float xC(0.45f), xL(0.1f), yL(0.05f), yDelta(0.1f);
	float yC(0.4f);

	CEGUI::PushButton* newGame = static_cast<CEGUI::PushButton*>
		(m_gui.createWidget(
			"AlfiskoSkin/Button",
			{ xC, yC, xL, yL },
			R2D::NOT_BY_PERCENT,
			"newGame"));

	newGame->setText("New Game");
	newGame->subscribeEvent
	(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&MainMenuScreen::onNewGameClicked, this)
	);

	CEGUI::PushButton* reloadButton = static_cast<CEGUI::PushButton*>
		(m_gui.createWidget(
			"AlfiskoSkin/Button",
			{ xC, yC += yDelta, xL, yL },
			R2D::NOT_BY_PERCENT,
			"Reload"));

	reloadButton->setText("Reload");
	reloadButton->subscribeEvent
	(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&MainMenuScreen::onReloadClicked, this)
	);

	CEGUI::PushButton* optionButton = static_cast<CEGUI::PushButton*>
		(m_gui.createWidget(
			"AlfiskoSkin/Button",
			{ xC, yC += yDelta, xL, yL },
			R2D::NOT_BY_PERCENT,
			"Option"));

	optionButton->setText("Option");
	optionButton->subscribeEvent
	(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&MainMenuScreen::onOptionClicked, this)
	);

	CEGUI::PushButton* quitGame = static_cast<CEGUI::PushButton*>
		(m_gui.createWidget(
			"AlfiskoSkin/Button",
			{ xC, yC += yDelta, xL, yL },
			R2D::NOT_BY_PERCENT,
			"QuitGame"));

	quitGame->setText("Quit Game");
	quitGame->subscribeEvent
	(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&MainMenuScreen::onExitClicked, this)
	);
}

void MainMenuScreen::doInitHUDText()
{
	R2D::MapTexts mapTexts;
	R2D::ResourceManager::getTextFromFile
	(
		R2D::e_Files::texts_MainMenu,
		mapTexts
	);

	R2D::ResourceManager::displayTextFromFile
	(
		mapTexts,
		m_game->getWindow(),
		m_spriteBatchHUDStatic
	);
}


void MainMenuScreen::onExit()
{
	/* Do nothing */
}


//----------------------------------------------------------GameLoop----------------------------------------------------------------//


void MainMenuScreen::draw()
{
	drawAll();
}

void MainMenuScreen::doDrawAll()
{
	
}


void MainMenuScreen::update()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev))
	{
		updateInputManager(ev, m_game->getInputManager());
		m_game->onSDLEvent(ev);
	}
}


bool MainMenuScreen::onNewGameClicked(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = SCREEN_INDEX::NEWGAME;
	m_currentState = R2D::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreen::onReloadClicked(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = SCREEN_INDEX::RELOAD;
	m_currentState = R2D::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreen::onOptionClicked(const CEGUI::EventArgs& /* e */)
{
	return true;
}

bool MainMenuScreen::onExitClicked(const CEGUI::EventArgs& /* e */)
{
	m_currentState = R2D::ScreenState::EXIT_APPLICATION;
	return true;
}
