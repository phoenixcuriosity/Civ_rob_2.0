/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.1.0
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

#include "NewGameScreen.h"

#include "LogSentences.h"
#include "ScreenIndices.h"

#include "App.h"
#include <R2D/src/ResourceManager.h>
#include <R2D/src/Log.h>

NewGameScreen::NewGameScreen
(
)
:
R2D::IGameScreen(),
R2D::CScreen(),
m_nextScreenIndexMenu(R2D::SCREEN_INDEX::INIT),
m_userInputNewGame(),
m_vectSlider(),
m_isInitialize(false)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::NEWGAME_MENU, logS::WHAT::CONSTRUCTOR, logS::DATA::SCREEN);
	build();
}

NewGameScreen::~NewGameScreen()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::NEWGAME_MENU, logS::WHAT::DESTRUCTOR, logS::DATA::SCREEN);
	destroy();
}

int NewGameScreen::getNextScreenIndex()const
{
	return SCREEN_INDEX::GAMEPLAY;
}
int NewGameScreen::getPreviousScreenIndex()const
{
	return SCREEN_INDEX::MAINMENU;
}

void NewGameScreen::build()
{
	m_screenIndex = SCREEN_INDEX::NEWGAME;
}

void NewGameScreen::destroy()
{
	end();
}

bool NewGameScreen::onEntry()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::NEWGAME_MENU, logS::WHAT::ON_ENTRY, logS::DATA::START);
	init(m_game->getWindow().GETscreenWidth(), m_game->getWindow().GETscreenHeight());
	LOG(R2D::LogLevelType::info, 0, logS::WHO::NEWGAME_MENU, logS::WHAT::ON_ENTRY, logS::DATA::END);
	return true;
}

void NewGameScreen::doInitOptimizeTexture()
{
	/* Do nothing */
}

void NewGameScreen::doInitUI()
{
	if (!m_isInitialize)
	{
		CEGUI::PushButton* previousMenu = static_cast<CEGUI::PushButton*>
			(m_gui.createWidget(
				"AlfiskoSkin/Button",
				{ 0.05f, 0.05f, 0.1f, 0.05f },
				{ 0,0,0,0 },
				"QuitGame"));

		previousMenu->setText("Previous Menu");
		previousMenu->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&NewGameScreen::onExitClicked, this)
		);

		CEGUI::PushButton* defaultSetup = static_cast<CEGUI::PushButton*>
			(m_gui.createWidget(
				"AlfiskoSkin/Button",
				{ 0.4f, 0.45f, 0.2f, 0.05f },
				{ 0,0,0,0 },
				"defaultSetup"));

		defaultSetup->setText("Default new game setup");
		defaultSetup->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&NewGameScreen::onDefaultSetupClicked, this)
		);

		m_vectSlider["nbPlayerSlider"] = (static_cast<CEGUI::Slider*>
			(m_gui.createWidget(
				"TaharezLook/Slider",
				{ 0.1f, 0.5f, 0.005f, 0.2f },
				{ 0,0,0,0 },
				"nbPlayerSlider")));

		m_vectSlider["nbPlayerSlider"]->setMaxValue(NUMBER_OF_PLAYER_MAX);
		m_vectSlider["nbPlayerSlider"]->setCurrentValue(NUMBER_OF_PLAYER_INITIAL);
		m_vectSlider["nbPlayerSlider"]->setClickStep(1.0f);
		m_vectSlider["nbPlayerSlider"]->subscribeEvent
		(
			CEGUI::Slider::EventValueChanged,
			CEGUI::Event::Subscriber(&NewGameScreen::onSliderPlayer, this)
		);

		m_isInitialize = true;
	}
}

void NewGameScreen::doInitHUDText()
{
	/* Do nothing */
}

void NewGameScreen::onExit()
{
	/* Do nothing */
}



//----------------------------------------------------------GameLoop----------------------------------------------------------------//



void NewGameScreen::draw()
{
	drawAll();
}

void NewGameScreen::doDrawAll()
{
	/* Do nothing for now
	*
	*	Place here new display on each cycle
	*
	*/
}


void NewGameScreen::update()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev))
	{
		m_game->onSDLEvent(ev);
		m_gui.onSDLEvent(ev, m_game->getInputManager());
	}
}

bool NewGameScreen::onDefaultSetupClicked(const CEGUI::EventArgs& /* e */)
{
	/* Clear buffer */
	m_userInputNewGame.vectPlayerName.clear();

#ifdef _DEBUG
	m_userInputNewGame.vectPlayerName.emplace_back("Robin");
	m_userInputNewGame.vectPlayerName.emplace_back("Thibaut");
	m_userInputNewGame.vectPlayerName.emplace_back("NoName0");
#endif // _DEBUG

	/* TODO : default configuration */

	/* Enable to change to next ScreenState */
	m_currentState = R2D::ScreenState::CHANGE_NEXT;
	return true;
}

bool NewGameScreen::onSliderPlayer(const CEGUI::EventArgs& /* e */)
{
	/* Clear buffer */
	m_userInputNewGame.vectPlayerName.clear();

	/* Resize buffer, change value of the number of player */
	m_userInputNewGame.vectPlayerName.resize((unsigned int)m_vectSlider["nbPlayerSlider"]->getCurrentValue());
	return true;
}

bool NewGameScreen::onExitClicked(const CEGUI::EventArgs& /* e */)
{
	/* Enable to change to previous ScreenState */
	m_currentState = R2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}

