/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.7.0
	file version : 1.6

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

#ifndef NewGameScreen_H
#define NewGameScreen_H

#include "LIB.h"

#include <RealEngine2D/src/IGameScreen.h>

#include <vector>

#include <RealEngine2D\src\Vertex.h>
#include <RealEngine2D\src\GLSLProgram.h>
#include <RealEngine2D\src\GameEngine.h>
#include <RealEngine2D\src\Window.h>
#include <RealEngine2D\src\Camera2D.h>
#include <RealEngine2D\src\SpriteBatch.h>
#include <RealEngine2D\src\InputManager.h>
#include <RealEngine2D\src\Timing.h>
#include <RealEngine2D\src\SpriteFont.h>
#include <RealEngine2D/src/AudioEngine.h>
#include <RealEngine2D/src/GUI.h>


#define MAX_NUMBER_OF_PLAYER 9 
#define INITIAL_NUMBER_OF_PLAYER 1 


struct UserInputNewGame
{
	std::vector<std::string> vectPlayerName;

};

class NewGameScreen : public RealEngine2D::IGameScreen
{
public:

	NewGameScreen();
	~NewGameScreen();

	virtual int getNextScreenIndex()const override;
	virtual int getPreviousScreenIndex()const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual bool onEntry() override;

private:



public:

	virtual void onExit() override;

	virtual void update() override;
	virtual void draw() override;


private:

	bool onDefaultSetupClicked(const CEGUI::EventArgs& e);
	bool onSliderPlayer(const CEGUI::EventArgs& e);
	bool onExitClicked(const CEGUI::EventArgs& e);


public:


	UserInputNewGame* getUserInputNewGame() { return &m_userInputNewGame; };

private:
	int m_nextScreenIndexMenu = INIT_SCREEN_INDEX;

	UserInputNewGame m_userInputNewGame;

	std::unordered_map<std::string, CEGUI::Slider*> m_vectSlider;
	RealEngine2D::GUI m_gui;

	bool m_isInitialize;
};

#endif // !NewGameScreen_H


