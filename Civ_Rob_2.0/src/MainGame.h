/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.2.0
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

#ifndef MainGame_H
#define MainGame_H

#include "LIB.h"


#include <fstream> // logger
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

/* Define center type for Texture to print on the screen */
enum class Center_Type
{
	nocenter,	/* Positions x and y are unchanged */
	center_x,	/* Positions y is unchanged and x is center depending on the length of the texte */
	center_y,	/* Positions x is unchanged and y is center depending on the height of the texte */
	center		/* Positions x and y are center depending on the length and the height of the texte */
};

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

const std::string configFilePath = "bin/config.xml";


const float MS_PER_SECOND(1000.0f);
const float TARGET_FRAMETIME = MS_PER_SECOND / RealEngine2D::SCREEN_REFRESH_RATE;
const unsigned int MAX_PHYSICS_STEPS(6);
const float MAX_DELTA_TIME(1.0f);



//---------------------- Structure niveau 1 ------------------------------------------------------------------------------//
struct OpenGLScreen
{
	RealEngine2D::GLSLProgram gLSLProgram;

	RealEngine2D::Camera2D camera;
	RealEngine2D::Camera2D cameraHUD;

	RealEngine2D::InputManager inputManager;

	RealEngine2D::FpsLimiter fpsLimiter;

	RealEngine2D::SpriteFont* spriteFont;
	RealEngine2D::SpriteBatch spriteBatchHUDDynamic;
	RealEngine2D::SpriteBatch spriteBatchHUDStatic;

	RealEngine2D::AudioEngine audioEngine;

	RealEngine2D::GUI m_gui;
};

struct Screen
{
	RealEngine2D::Window window;

	int screenWidth = 0;
	int screenHeight = 0;
	float fps = 0.0;

	OpenGLScreen openGLScreen;
};
struct File
{
	std::string log = "bin/log/log.txt";

	std::string readme = EMPTY_STRING;
	std::string texts = EMPTY_STRING;
	std::string buildings = EMPTY_STRING;
	std::string citiesNames = EMPTY_STRING;
	std::string units = EMPTY_STRING;
	std::string specNames = EMPTY_STRING;

	std::string saveInfo = EMPTY_STRING;

	std::string saveMaps = EMPTY_STRING;
	std::string savePlayers = EMPTY_STRING;

	std::string colorShadingVert = EMPTY_STRING;
	std::string colorShadingFrag = EMPTY_STRING;

	std::string imagesPath = EMPTY_STRING;
	std::string GUIPath = EMPTY_STRING;
};
struct Var
{

	/*** type primitif	***/

	int argc = 0;

	char** argv = nullptr;

	// variable permettant de quitter la boucle principale donc le jeu
	bool continuer = true;

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

class MainGame
{
public:
	/* *********************************************************
	 *						Const and Destr					   *
	 ********************************************************* */

	MainGame();
	~MainGame();

private:

	void init();

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
	/* NAME : initFile																	   */
	/* ROLE : Initialisation des fichiers : log											   */
	/* INPUT : struct File& : nom des fichiers											   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void initFile();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initMain																	   */
	/* ROLE : Chargement des informations de la configuration du jeu					   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void initMain();

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
	/* NAME : initSDL																	   */
	/* ROLE : Init SDL, create window													   */
	/* RETURNED VALUE    : bool : true = no Error										   */
	/* RETURNED VALUE    : bool : flase = Error											   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	bool initSDL();

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

public:

	/* *********************************************************
	 *						GameLoop						   *
	 ********************************************************* */

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : runGameLoop																   */
	/* ROLE : Run the game main's loop													   */
	/* ROLE : fpsLimiter, update inputManager, inputSDL, moveCameraByDeltaTime			   */
	/* ROLE : camera update, drawGame, fpsLimiter										   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void runGameLoop();

private:

	void inputUpdate();

	void moveCameraByDeltaTime();

	void moveCamera(float deltaTime);

	void drawGame();

	void drawHUD();

private:
	


public:

	/* *********************************************************
	 *						Destroy							   *
	 ********************************************************* */

	void destroy();


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : exitError																	   */
	/* ROLE : Enregistre l'erreur survenue et termine le programme de façon sécurisée	   */
	/* INPUT : const std::string msg : message de l'erreur								   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void exitError
	(
		const std::string& msg
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deleteAll																	   */
	/* ROLE : Destruction des allocations dynamique du programme						   */
	/* ROLE : Destruction de la fenetre et du Renderer de la SDL						   */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void deleteAll
	(
		MainGame& mainGame
	);


public:

	/* *********************************************************
	 *						Logger							   *
	 ********************************************************* */

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : logfileconsole															   */
	/* ROLE : Transmission du message sur la console et dans le fichier log.txt			   */
	/* INPUT : const std::string msg : message											   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void logfileconsole
	(
		const std::string& msg
	);

public:
	
	/* *********************************************************
	 *						GET/SET							   *
	 ********************************************************* */

	inline Screen& GETscreen() { return m_screen; };
	inline const Screen& GETscreen()const { return m_screen; };
	inline File& GETfile() { return m_file; };
	inline const File& GETfile()const { return m_file; };
	inline Var& GETvar() { return m_var; };
	inline const Var& GETvar()const { return m_var; };
	inline MainMap& GETmainMap() { return m_mainMap; };
	inline const MainMap& GETmainMap()const { return m_mainMap; };
	inline Players& GETPlayers() { return m_players; };
	inline const Players& GETPlayers()const { return m_players; };
	inline GameInput& GETgameInput() { return m_gameInput; };
	inline const GameInput& GETgameInput()const { return m_gameInput; };
	inline SaveReload& GETsaveReload() { return m_saveReload; };
	inline const SaveReload& GETsaveReload()const { return m_saveReload; };
	inline std::ofstream& GETlogger() { return m_logger; };

	inline void SETscreen(Screen& screen) { m_screen = screen; };
	inline void SETfile(File& file) { m_file = file; };
	inline void SETvar(Var& var) {m_var = var; };
	inline void SETmainMap(MainMap& mainMap) { m_mainMap = mainMap; };
	inline void SETPlayers(Players& players) {  m_players = players; };
	inline void SETgameInput(GameInput& gameInput) {  m_gameInput= gameInput; };
	inline void SETsaveReload(SaveReload& saveReload) {  m_saveReload = saveReload; };
	/* NO SET : m_logger */

private:

	/* *********************************************************
	 *						Attributs						   *
	 ********************************************************* */
	
	Screen m_screen;

	File m_file;

	Var m_var;

	MainMap m_mainMap;

	NextTurn m_nextTurn;

	Players m_players;

	GameInput m_gameInput;
	
	SaveReload m_saveReload;

	std::ofstream m_logger;

};

#endif /* MainGame_H */

/*
*	End Of File : MainGame.h
*/

