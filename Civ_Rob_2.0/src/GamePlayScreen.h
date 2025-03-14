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

#ifndef GamePlayScreen_H
#define GamePlayScreen_H

#include "LIB.h"

#include "MainMap.h"
#include "NextTurn.h"
#include "Players.h"
#include "T_GamePlayScreen.h"

#include <R2D/src/IMainGame.h>
#include <R2D/src/Screen.h>

class GamePlayScreen : public R2D::IGameScreen, public R2D::CScreen
{
public:

	GamePlayScreen(UserInputNewGame* userInputNewGame);

	~GamePlayScreen();

public: /* Override from R2D::IGameScreen */

	int getNextScreenIndex()const override;
	int getPreviousScreenIndex()const override;

	void build() override;
	void destroy() override;

	bool onEntry() override;
	void onExit() override;

	void update() override;
	void draw() override;

private: /* Override from R2D::CScreen */

	void doInitOptimizeTexture()override;
	void doInitUI() override;
	void doInitHUDText() override;
	void doDrawAll() override;

private:

	/* NAME : initStructs																   */
	/* ROLE : Initialisation des donn�es par d�faut des structures						   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	void initStructsNULL();

	/* NAME : computeSize																   */
	/* ROLE : Calcul des diff�rentes tailles de fenetre en fonction de tileSize			   */
	/* INPUT/OUTPUT : Screen& screen : longueur et hauteur �cran						   */
	/* INPUT/OUTPUT : struct Sysinfo& : diff�rentes tailles de fenetre					   */
	/* RETURNED VALUE    : void															   */
	void computeSize();

	/* NAME : initOpenGLScreen															   */
	/* ROLE : Init m_screen.openGLScreen and m_mainMap									   */
	/* RETURNED VALUE    : void															   */
	void initOpenGLScreen();


public:

	/* NAME : makePlayersButtons														   */
	/* ROLE : Create for p, number of players, a radio button 							   */
	/* ROLE : Button will be arrange in vertical axis and by p order					   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : void														       */
	void makePlayersButtons();

private:

	bool onPlayerButtonClicked(const CEGUI::EventArgs& e);
	bool onExitClicked(const CEGUI::EventArgs& e);

public:

	Screen& GETscreen()							{ return m_screen; };
	Var& GETvar()								{ return m_var; };
	MainMap& GETmainMap()						{ return m_mainMap; };
	Players& GETPlayers()						{ return m_players; };
	NextTurn& getNextTurn()						{ return m_nextTurn; };
	UserInputNewGame* getUserInputNewGame()		{ return m_userInputNewGame; };
	R2D::Window& getParentWindow()				{ return m_game->getWindow(); };
	R2D::InputManager& getInputManager()		{ return m_game->getInputManager(); };

	const Screen& GETscreen()const		{ return m_screen; };
	const Var& GETvar()const			{ return m_var; };
	const MainMap& GETmainMap()const	{ return m_mainMap; };
	const Players& GETPlayers()const	{ return m_players; };

	void SETvar(Var& var)				{ m_var = var; };
	void SETmainMap(MainMap& mainMap)	{ m_mainMap = mainMap; };
	void SETPlayers(Players& players)	{ m_players = players; };

private:

	Screen m_screen;

	Var m_var;

	MainMap m_mainMap;

	NextTurn m_nextTurn;

	Players m_players;

	UserInputNewGame* m_userInputNewGame;

	bool m_isInitialize;
};

#endif // !GamePlayScreen_H


