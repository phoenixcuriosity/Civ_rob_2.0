/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.2.0
	file version : 1.2

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

#include "GamePlaySrceen.h"
#include <RealEngine2D/src/IMainGame.h>

#include <SDL/SDL.h>
#include <SDL/glew.h>

#include <iostream>

#include "MainMap.h"
#include "Utility.h"
#include "XmlConvertValue.h"
#include "NewGame.h"

#include <RealEngine2D\src\ResourceManager.h>

static std::ofstream* ptrlogger;
static GamePlayScreen* ptrMainGame;


GamePlayScreen::GamePlayScreen()
{

}
GamePlayScreen::~GamePlayScreen()
{

}

int GamePlayScreen::getNextScreenIndex()const
{
	return INIT_SCREEN_INDEX;
}
int GamePlayScreen::getPreviousScreenIndex()const
{
	return INIT_SCREEN_INDEX;
}

void GamePlayScreen::build()
{

}
void GamePlayScreen::destroy()
{
	//deleteAll(*this);
}

void GamePlayScreen::onEntry()
{
	
}


void GamePlayScreen::onExit()
{

}

void GamePlayScreen::update()
{
	checkInput();
}
void GamePlayScreen::draw()
{
	
}


void GamePlayScreen::checkInput()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		m_game->onSDLEvent(ev);
		//GameInput::inputSDL(*this, ev);
		//m_screen.openGLScreen.m_gui.onSDLEvent(ev, m_screen.openGLScreen.inputManager);
	}
}

