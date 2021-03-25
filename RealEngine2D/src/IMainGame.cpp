/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.3.0
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

#include "IMainGame.h"

#include "Timing.h"
#include "IGameScreen.h"
#include "GameEngine.h"
#include "ScreenList.h"

#include <SDL/SDL.h>
#include <SDL/glew.h>


namespace RealEngine2D
{

IMainGame::IMainGame()
{
	m_screenList = new ScreenList(this);
}

IMainGame::~IMainGame()
{
	if (nullptr != m_screenList)
		delete m_screenList;
}


void IMainGame::run()
{
	if (!init()) return;

	m_isRunning = true;

	FpsLimiter limiter;
	limiter.setMaxFPS(60.0f);

	while (m_isRunning)
	{
		limiter.begin();

		m_inputManager.update();
		if (!m_isRunning) return;

		update();
		draw();

		m_fps = limiter.end();
		m_window.swap();
	}

}

void IMainGame::exitGame()
{
	m_currentScreen->onExit();
	if (m_screenList)
	{
		m_screenList->destroy();
	}
	m_isRunning = false;
}

	
	
void IMainGame::update()
{
	if (m_currentScreen)
	{
		switch (m_currentScreen->GETscreenState())
		{
		case ScreenState::NONE:
			/* N/A */
			break;
		case ScreenState::RUNNING:
			m_currentScreen->update();
			break;
		case ScreenState::EXIT_APPLICATION:
			exitGame();
			break;
		case ScreenState::CHANGE_NEXT:
			m_currentScreen->onExit();
			m_currentScreen = m_screenList->moveNext();
			if (m_currentScreen)
			{
				m_currentScreen->setRunning();
				m_currentScreen->onEntry();
			}
			break;
		case ScreenState::CHANGE_PREVIOUS:
			m_currentScreen->onExit();
			m_currentScreen = m_screenList->movePrevious();
			if (m_currentScreen)
			{
				m_currentScreen->setRunning();
				m_currentScreen->onEntry();
			}
			break;
		default:
			/* N/A */
			break;
		}
	}
	else
	{
		exitGame();
	}

}
void IMainGame::draw()
{
	glViewport(0, 0, m_window.GETscreenWidth(), m_window.GETscreenHeight());
	if  (
			m_currentScreen
			&&
			m_currentScreen->GETscreenState() == ScreenState::RUNNING
		)
	{
		m_currentScreen->draw();
	}
}

void IMainGame::onSDLEvent(SDL_Event& ev)
{
	switch (ev.type)
	{

	case SDL_QUIT:
		exitGame();
		break;


	case SDL_KEYDOWN:
		m_inputManager.pressKey(ev.key.keysym.sym);

		break;
	case SDL_KEYUP:
		m_inputManager.releaseKey(ev.key.keysym.sym);
		break;


	case SDL_MOUSEBUTTONDOWN:
		m_inputManager.pressKey(ev.button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		m_inputManager.releaseKey(ev.button.button);
		break;



	case SDL_MOUSEWHEEL:
		//wheel(mainGame);
		break;



	case SDL_MOUSEMOTION:
		m_inputManager.setMouseCoords(ev.motion.x, ev.motion.y);
		break;

	default:
		/* N/A */
		break;
	}


	if (m_inputManager.isKeyDown(SDLK_ESCAPE))
	{
		exitGame();
	}
}


bool IMainGame::init()
{
	if (initSDLOpenGL() != 0) return false;



	if (!initSystem()) return false;

	onInit();
	addScreens();

	m_currentScreen = m_screenList->getCurrent();
	m_currentScreen->onEntry();
	m_currentScreen->setRunning();

	return true;
}

bool IMainGame::initSystem()
{
	m_window.create("Default", 1280, 720, 0);
	return true;
}


}