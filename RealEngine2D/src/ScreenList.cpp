/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.3.0
	file version : 1.1

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

#include "ScreenList.h"

#include "IGameScreen.h"
#include "IMainGame.h"

namespace RealEngine2D
{

ScreenList::ScreenList(IMainGame* game):
m_game(game)
{
}

ScreenList::~ScreenList()
{
	destroy();
}

IGameScreen* ScreenList::moveNext()
{
	IGameScreen* currentScreen = getCurrent();
	if (currentScreen->getNextScreenIndex() != INIT_SCREEN_INDEX)
	{
		m_currentScreenIndex = currentScreen->getNextScreenIndex();
	}
	return getCurrent();
}

IGameScreen* ScreenList::movePrevious()
{
	IGameScreen* currentScreen = getCurrent();
	if (currentScreen->getPreviousScreenIndex() != INIT_SCREEN_INDEX)
	{
		m_currentScreenIndex = currentScreen->getPreviousScreenIndex();
	}
	return getCurrent();
}

void ScreenList::setScreen(int nextScreen)
{
	m_currentScreenIndex = nextScreen;
}
void ScreenList::addScreen(IGameScreen* newScreen)
{
	newScreen->setScreenIndex((int)m_screens.size());
	m_screens.push_back(newScreen);
	newScreen->build();
	newScreen->setParentGame(m_game);
}

void ScreenList::destroy()
{
	for (size_t i(0); i < m_screens.size(); i++)
	{
		m_screens[i]->destroy();
	}
	m_screens.resize(0);
	m_currentScreenIndex = INIT_SCREEN_INDEX;
}

IGameScreen* ScreenList::getCurrent()
{
	if (INIT_SCREEN_INDEX == m_currentScreenIndex) return nullptr;
	return m_screens[m_currentScreenIndex];
}

}
