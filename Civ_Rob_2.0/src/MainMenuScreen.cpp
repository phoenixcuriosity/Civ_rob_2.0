/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.7.0
	file version : 1.6

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
#include "ScreenIndices.h"

#include "App.h"

#include <RealEngine2D/src/ResourceManager.h> 

MainMenuScreen::MainMenuScreen
(
)
: 
RealEngine2D::IGameScreen(),
m_nextScreenIndexMenu(INIT_SCREEN_INDEX),
m_gui(),
m_isInitialize(false)
{
	build();
}

MainMenuScreen::~MainMenuScreen()
{
	destroy();
}

int MainMenuScreen::getNextScreenIndex()const
{
	return m_nextScreenIndexMenu;
}
int MainMenuScreen::getPreviousScreenIndex()const
{
	return INIT_SCREEN_INDEX;
}

void MainMenuScreen::build()
{
	m_screenIndex = MAINMENU_SCREEN_INDEX;
}

void MainMenuScreen::destroy()
{
	m_gui.destroy();
}

bool MainMenuScreen::onEntry()
{
	if (!m_isInitialize)
	{
		m_gui.init(RealEngine2D::ResourceManager::getFile(e_Files::GUIPath)->getPath());

		m_gui.loadScheme("AlfiskoSkin.scheme");

		m_gui.setFont("DejaVuSans-10");

		const float xC(0.45f), xL(0.1f), yL(0.05f), yDelta(0.1f);
		float yC(0.4f);

		CEGUI::PushButton* newGame = static_cast<CEGUI::PushButton*>
			(m_gui.createWidget(
				"AlfiskoSkin/Button",
				{ xC, yC, xL, yL },
				RealEngine2D::NOT_BY_PERCENT,
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
				RealEngine2D::NOT_BY_PERCENT,
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
				RealEngine2D::NOT_BY_PERCENT,
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
				RealEngine2D::NOT_BY_PERCENT,
				"QuitGame"));

		quitGame->setText("Quit Game");
		quitGame->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&MainMenuScreen::onExitClicked, this)
		);


		m_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
		m_gui.showMouseCursor();

		/* HIDE normal mouse cursor */
		SDL_ShowCursor(0);

		m_isInitialize = true;
	}
	

	return true;
}

void MainMenuScreen::onExit()
{
	/* Do nothing */
}


//----------------------------------------------------------GameLoop----------------------------------------------------------------//



void MainMenuScreen::draw()
{
	/* line for CEGUI because CEGUI doesn't do it, do not remove  */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Back */
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_gui.draw();
}


void MainMenuScreen::update()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev))
	{
		m_gui.onSDLEvent(ev, m_game->getInputManager());
		m_game->onSDLEvent(ev);
	}
}


bool MainMenuScreen::onNewGameClicked(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = NEWGAME_SCREEN_INDEX;
	m_currentState = RealEngine2D::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreen::onReloadClicked(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = RELOAD_SCREEN_INDEX;
	m_currentState = RealEngine2D::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreen::onOptionClicked(const CEGUI::EventArgs& /* e */)
{
	return true;
}

bool MainMenuScreen::onExitClicked(const CEGUI::EventArgs& /* e */)
{
	m_currentState = RealEngine2D::ScreenState::EXIT_APPLICATION;
	return true;
}
