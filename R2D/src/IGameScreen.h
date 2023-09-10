/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.1.0
	file version : 1.5

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

#ifndef IGameScreen_H
#define IGameScreen_H

#include <glm\glm.hpp>

namespace R2D
{

/* Define initial screen index -> Default Screen */
namespace SCREEN_INDEX
{
	const int INIT = -1;
}


class IMainGame;

enum class ScreenState
{
	NONE,
	RUNNING,
	EXIT_APPLICATION,
	CHANGE_NEXT,
	CHANGE_PREVIOUS
};

/* Setting to not use percent for a widget */
const glm::vec4 NOT_BY_PERCENT = { 0.0f, 0.0f, 0.0f, 0.0f };


class IGameScreen
{
public:
	IGameScreen():
	m_game(nullptr),
	m_screenIndex(SCREEN_INDEX::INIT),
	m_currentState(ScreenState::NONE)
	{};


	virtual ~IGameScreen() {};

	virtual int getNextScreenIndex()const = 0;
	virtual int getPreviousScreenIndex()const = 0;

	virtual void build() = 0;
	virtual void destroy() = 0;

	virtual bool onEntry() = 0;
	virtual void onExit() = 0;
	
	virtual void update() = 0;
	virtual void draw() = 0;

	int GETscreenIndex()const { return m_screenIndex; };
	ScreenState GETscreenState()const { return m_currentState; };

	void setScreenIndex(int screenIndex) { m_screenIndex = screenIndex; };
	void setRunning() { m_currentState = ScreenState::RUNNING; };
	void setPrevious() { m_currentState = ScreenState::CHANGE_PREVIOUS; };

	void setParentGame(IMainGame* game) { m_game = game; }

protected:
	IMainGame* m_game;
	int m_screenIndex;
	ScreenState m_currentState;
};

}


#endif // !IGameScreen_H

