/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.4.0
	file version : 1.0

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

#include "ScreenIndices.h"

#include "App.h"

NewGameScreen::NewGameScreen
(
	File* file,
	RealEngine2D::Window* window,
	RealEngine2D::InputManager* inputManager
)
	: m_file(file), m_window(window), m_inputManager(inputManager)
{
	m_screenIndex = NEWGAME_SCREEN_INDEX;
}

NewGameScreen::~NewGameScreen()
{

}

int NewGameScreen::getNextScreenIndex()const
{
	return GAMEPLAY_SCREEN_INDEX;
}
int NewGameScreen::getPreviousScreenIndex()const
{
	return MAINMENU_SCREEN_INDEX;
}

void NewGameScreen::build()
{

}
void NewGameScreen::destroy()
{
	m_gui.destroy();
}

void NewGameScreen::onEntry()
{
	m_gui.init(m_file->GUIPath);

	m_gui.loadScheme("AlfiskoSkin.scheme");
	m_gui.loadScheme("TaharezLook.scheme");

	m_gui.setFont("DejaVuSans-12");


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

	m_vectSlider["nbPlayerSlider"]->setMaxValue(MAX_NUMBER_OF_PLAYER);
	m_vectSlider["nbPlayerSlider"]->setCurrentValue(INITIAL_NUMBER_OF_PLAYER);
	m_vectSlider["nbPlayerSlider"]->setClickStep(1.0f);
	m_vectSlider["nbPlayerSlider"]->subscribeEvent
	(
		CEGUI::Slider::EventValueChanged,
		CEGUI::Event::Subscriber(&NewGameScreen::onSliderPlayer, this)
	);


	m_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
	m_gui.showMouseCursor();

	/* HIDE normal mouse cursor */
	SDL_ShowCursor(0);
}



//----------------------------------------------------------GameLoop----------------------------------------------------------------//



void NewGameScreen::draw()
{
	/* line for CEGUI because CEGUI doesn't do it, do not remove  */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Back */
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_gui.draw();
}


void NewGameScreen::update()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		m_game->onSDLEvent(ev);
		m_gui.onSDLEvent(ev, *m_inputManager);
	}
}



void NewGameScreen::onExit()
{

}

bool NewGameScreen::onDefaultSetupClicked(const CEGUI::EventArgs& /* e */)
{
	m_userInputNewGame.vectPlayerName.clear();

	m_userInputNewGame.vectPlayerName.emplace_back("Robin");
	m_userInputNewGame.vectPlayerName.emplace_back("Thibaut");
	m_userInputNewGame.vectPlayerName.emplace_back("NoName0");

	m_currentState = RealEngine2D::ScreenState::CHANGE_NEXT;
	return true;
}

bool NewGameScreen::onSliderPlayer(const CEGUI::EventArgs& /* e */)
{
	m_userInputNewGame.vectPlayerName.clear();
	m_userInputNewGame.vectPlayerName.resize((unsigned int)m_vectSlider["nbPlayerSlider"]->getCurrentValue());
	return true;
}

bool NewGameScreen::onExitClicked(const CEGUI::EventArgs& /* e */)
{
	m_currentState = RealEngine2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}

