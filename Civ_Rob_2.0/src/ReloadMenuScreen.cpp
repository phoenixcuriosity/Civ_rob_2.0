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

#include "ReloadMenuScreen.h"

#include "ScreenIndices.h"

#include "App.h"
#include "SaveReload.h"

ReloadMenuScreen::ReloadMenuScreen
(
	File* file,
	SaveReload* SaveReload,
	RealEngine2D::Window* window,
	RealEngine2D::InputManager* inputManager
)
	: m_file(file), m_SaveReload(SaveReload), m_window(window), m_inputManager(inputManager)
{
	m_screenIndex = MAINMENU_SCREEN_INDEX;
}

ReloadMenuScreen::~ReloadMenuScreen()
{

}

int ReloadMenuScreen::getNextScreenIndex()const
{
	return INIT_SCREEN_INDEX;
}
int ReloadMenuScreen::getPreviousScreenIndex()const
{
	return MAINMENU_SCREEN_INDEX;
}

void ReloadMenuScreen::build()
{

}
void ReloadMenuScreen::destroy()
{
	m_gui.destroy();
}

void ReloadMenuScreen::onEntry()
{
	m_gui.init(m_file->GUIPath);

	m_gui.loadScheme("AlfiskoSkin.scheme");

	m_gui.setFont("DejaVuSans-10");

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
		CEGUI::Event::Subscriber(&ReloadMenuScreen::onExitClicked, this)
	);


	CEGUI::PushButton* clearSavesButton = static_cast<CEGUI::PushButton*>
		(m_gui.createWidget(
			"AlfiskoSkin/Button",
			{ 0.45f, 0.5f, 0.1f, 0.05f },
			{ 0,0,0,0 },
			"ClearSaves"));

	clearSavesButton->setText("Clear Saves");
	clearSavesButton->subscribeEvent
	(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&ReloadMenuScreen::onClearSavesCliked, this)
	);





	m_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
	m_gui.showMouseCursor();

	/* HIDE normal mouse cursor */
	SDL_ShowCursor(0);
}



//----------------------------------------------------------GameLoop----------------------------------------------------------------//



void ReloadMenuScreen::draw()
{
	/* line for CEGUI because CEGUI doesn't do it, do not remove  */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Back */
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_gui.draw();
}


void ReloadMenuScreen::update()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		m_game->onSDLEvent(ev);
		m_gui.onSDLEvent(ev, *m_inputManager);
	}
}



void ReloadMenuScreen::onExit()
{

}

bool ReloadMenuScreen::onClearSavesCliked(const CEGUI::EventArgs& /* e */)
{
	m_SaveReload->clearSave(m_file->saveInfo);
	return true;
}

bool ReloadMenuScreen::onExitClicked(const CEGUI::EventArgs& /* e */)
{
	m_currentState = RealEngine2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}