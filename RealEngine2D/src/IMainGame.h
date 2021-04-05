/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.8.0
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

#ifndef IMainGame_H
#define IMainGame_H

#include "Window.h"
#include "InputManager.h"

#include <memory>

namespace RealEngine2D
{

class ScreenList;
class IGameScreen;

class IMainGame
{
public:
	IMainGame();
	virtual ~IMainGame();

	void run();
	void exitGame();

	virtual void onInit() = 0;
	virtual void onExit() = 0;
	virtual void addScreens() = 0;

	const float getFPS()const { return m_fps; };

	void onSDLEvent(SDL_Event& ev);
	
protected:

	virtual void update();
	virtual void draw();


	bool init();
	bool initSystem();

protected:
	std::unique_ptr<ScreenList> m_screenList;
	std::shared_ptr<IGameScreen> m_currentScreen;

	bool m_isRunning;
	float m_fps;

	Window m_window;
	InputManager m_inputManager;
};

}

#endif // !IMainGame_H

