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

#ifndef NewGameScreen_H
#define NewGameScreen_H

#include "LIB.h"

#include <R2D/src/IGameScreen.h>
#include <R2D/src/GUI.h>

struct UserInputNewGame
{
	std::vector<std::string> vectPlayerName;

};

class NewGameScreen : public R2D::IGameScreen
{
public:

	NewGameScreen();
	~NewGameScreen();

	int getNextScreenIndex()const override;
	int getPreviousScreenIndex()const override;

	void build() override;
	void destroy() override;

	bool onEntry() override;

private:



public:

	void onExit() override;

	void update() override;
	void draw() override;


private:

	bool onDefaultSetupClicked(const CEGUI::EventArgs& e);
	bool onSliderPlayer(const CEGUI::EventArgs& e);
	bool onExitClicked(const CEGUI::EventArgs& e);


public:


	UserInputNewGame* getUserInputNewGame() { return &m_userInputNewGame; };

private:
	int m_nextScreenIndexMenu;

	UserInputNewGame m_userInputNewGame;

	std::unordered_map<std::string, CEGUI::Slider*> m_vectSlider;
	R2D::GUI m_gui;

	bool m_isInitialize;
};

#endif // !NewGameScreen_H



