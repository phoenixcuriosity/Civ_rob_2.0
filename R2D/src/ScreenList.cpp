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

#include "ScreenList.h"

#include "IGameScreen.h"
#include "IMainGame.h"

namespace R2D
{

ScreenList::ScreenList(IMainGame* game):
m_game(game), m_currentScreenIndex(R2D::SCREEN_INDEX::INIT)
{
}

ScreenList::~ScreenList()
{
	destroy();
}

std::shared_ptr<IGameScreen> ScreenList::moveNext()
{
	std::shared_ptr<IGameScreen> currentScreen = getCurrent();
	if (currentScreen->getNextScreenIndex() != R2D::SCREEN_INDEX::INIT)
	{
		m_currentScreenIndex = currentScreen->getNextScreenIndex();
	}
	currentScreen.reset();
	return getCurrent();
}

std::shared_ptr<IGameScreen> ScreenList::movePrevious()
{
	std::shared_ptr<IGameScreen> currentScreen = getCurrent();
	if (currentScreen->getPreviousScreenIndex() != R2D::SCREEN_INDEX::INIT)
	{
		m_currentScreenIndex = currentScreen->getPreviousScreenIndex();
	}
	currentScreen.reset();
	return getCurrent();
}

void ScreenList::setScreen(int nextScreen)
{
	m_currentScreenIndex = nextScreen;
}
void ScreenList::addScreen(std::shared_ptr<IGameScreen> newScreen)
{
	newScreen->setScreenIndex((int)m_screens.size());
	m_screens.push_back(newScreen);
	newScreen->build();
	newScreen->setParentGame(m_game);
}

void ScreenList::destroy()
{
	for (auto s : m_screens)
	{
		s->destroy();
		s.reset();
	}
	m_screens.resize(0);
	m_screens.clear();
	m_currentScreenIndex = R2D::SCREEN_INDEX::INIT;
}

std::shared_ptr<IGameScreen> ScreenList::getCurrent()
{
	if (R2D::SCREEN_INDEX::INIT == m_currentScreenIndex) return nullptr;
	return m_screens[m_currentScreenIndex];
}

}
