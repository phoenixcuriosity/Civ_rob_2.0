/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.11.0
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

#ifndef IGameScreen_H
#define IGameScreen_H

namespace RealEngine2D
{

#define INIT_SCREEN_INDEX -1

class IMainGame;

enum class ScreenState
{
	NONE,
	RUNNING,
	EXIT_APPLICATION,
	CHANGE_NEXT,
	CHANGE_PREVIOUS
};


class IGameScreen
{
public:
	IGameScreen():
	m_game(nullptr),
	m_screenIndex(INIT_SCREEN_INDEX),
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

