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

R2D::ScreenList::IGameScreenPtr
R2D::ScreenList
::moveNext()
{
	const IGameScreenPtr currentScreen = getCurrent();
	if (currentScreen->getNextScreenIndex() != SCREEN_INDEX_INIT)
	{
		m_currentScreenIndex = currentScreen->getNextScreenIndex();
	}
	return getCurrent();
}

R2D::ScreenList::IGameScreenPtr
R2D::ScreenList
::movePrevious()
{
	const IGameScreenPtr currentScreen = getCurrent();
	if (currentScreen->getPreviousScreenIndex() != SCREEN_INDEX_INIT)
	{
		m_currentScreenIndex = currentScreen->getPreviousScreenIndex();
	}
	return getCurrent();
}

void
R2D::ScreenList
::setScreen(int nextScreen)
{
	m_currentScreenIndex = nextScreen;
}

void R2D::ScreenList::addScreen(ScreenList::IGameScreenPtr newScreen)
{
	newScreen->setScreenIndex((int)m_screens.size());
	m_screens.push_back(newScreen);
	newScreen->build();
	newScreen->setParentGame(m_game);
}

void
R2D::ScreenList
::destroy()
{
	for (auto s : m_screens)
	{
		s->destroy();
		s.reset();
	}
	m_screens.resize(0);
	m_screens.clear();
	m_currentScreenIndex = SCREEN_INDEX_INIT;
}

R2D::ScreenList::IGameScreenPtr
R2D::ScreenList
::getCurrent()
{
	if (SCREEN_INDEX_INIT == m_currentScreenIndex) return nullptr;
	return m_screens[m_currentScreenIndex];
}
