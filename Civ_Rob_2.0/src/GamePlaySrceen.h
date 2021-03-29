/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.4.0
	file version : 1.3

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

#include <RealEngine2D/src/IGameScreen.h>

#include "LIB.h"

#include <vector>

#include <RealEngine2D\src\Sprite.h>
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

#include "Player.h"
#include "GameInput.h"
#include "MainMap.h"
#include "SaveReload.h"
#include "NextTurn.h"
#include "NewGame.h"

struct File;
struct UserInputNewGame;

struct Screen
{

	float fps = 0.0;

	RealEngine2D::GLSLProgram gLSLProgram;

	RealEngine2D::Camera2D camera;
	RealEngine2D::Camera2D cameraHUD;

	RealEngine2D::SpriteFont* spriteFont;
	RealEngine2D::SpriteBatch spriteBatchHUDDynamic;
	RealEngine2D::SpriteBatch spriteBatchHUDStatic;

	RealEngine2D::AudioEngine audioEngine;

	RealEngine2D::GUI m_gui;
	/*std::vector<CEGUI::PushButton*> m_vectPlayerButton;*/
	std::vector<CEGUI::RadioButton*> m_vectPlayerRadioButton;
	std::vector<WidgetLabel> m_widgetLabels;
};
struct Var
{

	std::string tempPlayerName = EMPTY_STRING;

	/*
		état de la sélection du joueur
		enum Select_Type : unsigned int
		{
			selectnothing,
			selectcreate,
			selectinspect,
			selectmove,
			selectmoveCitizen
		};
	*/
	Select_Type select = Select_Type::selectnothing;

	/*
		état de l'écran du joueur
		enum State_Type : unsigned int
		{
			STATEnothing,
			STATEtitleScreen,
			STATEscreennewgame,
			STATEreload,
			STATEmainmap,
			STATEscience,
			STATEcitiemap
		};
	*/
	State_Type statescreen = State_Type::error;

	/*
			état de l'entrée clavier
			enum CinState_Type : unsigned int
			{
				cinNothing,
				cinTitleScreen,
				cinScreenNewGameNbPlayer,
				cinScreenNewGameNamePlayer,
				cinMainMap,
			};
		*/
	CinState_Type cinState = CinState_Type::cinNothing;
};






const float MS_PER_SECOND(1000.0f);
const float TARGET_FRAMETIME = MS_PER_SECOND / (float)RealEngine2D::SCREEN_REFRESH_RATE;
const unsigned int MAX_PHYSICS_STEPS(6);
const float MAX_DELTA_TIME(1.0f);






class GamePlayScreen : public RealEngine2D::IGameScreen
{
public:
	GamePlayScreen
	(
		File* file,
		SaveReload* SaveReload,
		RealEngine2D::Window* window,
		RealEngine2D::InputManager* inputManager,
		UserInputNewGame* userInputNewGame
	);

	~GamePlayScreen();

	virtual int getNextScreenIndex()const override;
	virtual int getPreviousScreenIndex()const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual void onEntry() override;

private:

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : loadFile																	   */
	/* ROLE : 										   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void loadFile();


private:



	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initStructs																   */
	/* ROLE : Initialisation des donn�es par d�faut des structures						   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void initStructsNULL();



	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : computeSize																   */
	/* ROLE : Calcul des diff�rentes tailles de fenetre en fonction de tileSize			   */
	/* INPUT/OUTPUT : Screen& screen : longueur et hauteur �cran						   */
	/* INPUT/OUTPUT : struct Sysinfo& : diff�rentes tailles de fenetre					   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void computeSize();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initOpenGLScreen															   */
	/* ROLE : Init m_screen.openGLScreen and m_mainMap									   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void initOpenGLScreen();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initShaders																   */
	/* ROLE : Init shaders for OpenGL													   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void initShaders();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initHUDText																   */
	/* ROLE : Init static Text in HUD													   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void initHUDText();

	void initUI();

public:

	/* *********************************************************
	 *							Load						   *
	 ********************************************************* */

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : loadUnitAndSpec															   */
	/* ROLE : Chargement des informations concernant les unit�s � partir d'un fichier	   */
	/* INPUT : const std::string& : nom du fichier � ouvrir								   */
	/* OUTPUT : std::vector<Unit_Template>& : Vecteur des Unit							   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void loadUnitAndSpec();

private:

	void moveCameraByDeltaTime();

	void moveCamera(float deltaTime);

	void drawGame();

	void drawHUD();

public:

	virtual void onExit() override;

	virtual void update() override;
	virtual void draw() override;



	bool onPlayerButtonClicked(const CEGUI::EventArgs& e);

private:

	bool onExitClicked(const CEGUI::EventArgs& e);


public:


	inline Screen& GETscreen() { return m_screen; };
	inline const Screen& GETscreen()const { return m_screen; };
	inline Var& GETvar() { return m_var; };
	inline const Var& GETvar()const { return m_var; };
	inline MainMap& GETmainMap() { return m_mainMap; };
	inline const MainMap& GETmainMap()const { return m_mainMap; };
	inline Players& GETPlayers() { return m_players; };
	inline const Players& GETPlayers()const { return m_players; };
	inline GameInput& GETgameInput() { return m_gameInput; };
	inline const GameInput& GETgameInput()const { return m_gameInput; };
	inline File* getFile() { return m_file; };
	inline SaveReload* getSaveReload() { return m_SaveReload; };
	inline const RealEngine2D::Window* getwindow() { return m_window; };
	inline RealEngine2D::InputManager* getInputManager() { return m_inputManager; };
	inline UserInputNewGame* getUserInputNewGame() { return m_userInputNewGame; };

	inline void SETscreen(Screen& screen) { m_screen = screen; };
	inline void SETvar(Var& var) { m_var = var; };
	inline void SETmainMap(MainMap& mainMap) { m_mainMap = mainMap; };
	inline void SETPlayers(Players& players) { m_players = players; };
	inline void SETgameInput(GameInput& gameInput) { m_gameInput = gameInput; };


private:

	Screen m_screen;

	Var m_var;

	MainMap m_mainMap;

	NextTurn m_nextTurn;

	Players m_players;

	GameInput m_gameInput;

	File* m_file = nullptr;
	SaveReload* m_SaveReload = nullptr;
	RealEngine2D::Window* m_window = nullptr;
	RealEngine2D::InputManager* m_inputManager = nullptr;
	UserInputNewGame* m_userInputNewGame = nullptr;
};




#endif // !GamePlayScreen_H


