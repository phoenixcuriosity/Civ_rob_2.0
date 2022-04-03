/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.3.0
	file version : 1.14

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


/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"

#include <RealEngine2D/src/IGameScreen.h>
#include <RealEngine2D/src/IMainGame.h>
#include <RealEngine2D/src/GLSLProgram.h>
#include <RealEngine2D/src/Camera2D.h>
#include <RealEngine2D/src/WidgetLabel.h>
#include <RealEngine2D/src/SpriteBatch.h>
#include <RealEngine2D/src/AudioEngine.h>
#include <RealEngine2D/src/GUI.h>
#include <RealEngine2D/src/Window.h>

#include "NewGame.h"
#include "GameInput.h"

#include "NextTurn.h"
#include "MainMap.h"
#include "Player.h"
#include "City.h"

#include <vector>
#include <memory>

/* *********************************************************
 *						 Structs						   *
 ********************************************************* */

/* 
	All RealEngine2D objects
	- Shaders
	- camera/cameraHUD
	- Sprite/font
	- audioEngine
	- GUI
*/
struct Screen
{
	std::shared_ptr<RealEngine2D::SpriteFont> spriteFont = nullptr;
	RealEngine2D::GLSLProgram* gLSLProgram;

	RealEngine2D::Camera2D camera;
	RealEngine2D::Camera2D cameraHUD;

	RealEngine2D::SpriteBatch spriteBatchHUDDynamic;
	RealEngine2D::SpriteBatch spriteBatchHUDStatic;

	RealEngine2D::AudioEngine audioEngine;

	RealEngine2D::GUI m_gui;
	std::vector<CEGUI::RadioButton*> m_vectPlayerRadioButton;
	std::vector<RealEngine2D::WidgetLabel> m_widgetLabels;

	int m_nextScreenIndexMenu = INIT_SCREEN_INDEX;
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


/* *********************************************************
 *					 Constantes							   *
 ********************************************************* */

const float MS_PER_SECOND(1000.0f);
const float TARGET_FRAMETIME = MS_PER_SECOND / (float)RealEngine2D::SCREEN_REFRESH_RATE;
const unsigned int MAX_PHYSICS_STEPS(6);
const float MAX_DELTA_TIME(1.0f);

/* *********************************************************
 *						 Classe							   *
 ********************************************************* */

class GamePlayScreen : public RealEngine2D::IGameScreen
{
public:

	/* *********************************************************
	 *					Constructor/Destructor				   *
	 ********************************************************* */

	GamePlayScreen
	(
		File* file,
		SaveReload* saveReload,
		UserInputNewGame* userInputNewGame,
		RealEngine2D::GLSLProgram* gLSLProgram,
		std::shared_ptr<RealEngine2D::SpriteFont>& spriteFont
	);

	~GamePlayScreen();


public:

	/* *********************************************************
	 *					   Parent override					   *
	 ********************************************************* */

	virtual int getNextScreenIndex()const override;
	virtual int getPreviousScreenIndex()const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual bool onEntry() override;

	virtual void onExit() override;

	/* ----------------------------------------------------------------------------------- */
	/* NAME : update																	   */
	/* ROLE : Call each cycle 															   */
	/* ROLE : Update input from SDL and game / Update GUI input							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void update() override;

	/* ----------------------------------------------------------------------------------- */
	/* NAME : draw																		   */
	/* ROLE : Call each cycle 															   */
	/* ROLE : Update picture from game and GUI 											   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	virtual void draw() override;

private:

	/* *********************************************************
	 *							File						   *
	 ********************************************************* */

	/* ----------------------------------------------------------------------------------- */
	/* NAME : loadFile																	   */
	/* ROLE :																			   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	void loadFile();

	
public:

	/* *********************************************************
	 *					STATIC XmlConvertValue				   *
	 ********************************************************* */

	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : xmlGiveStateType																			    	  */
	/* ROLE : Convert an std::string from XML document to State_Type from Texture class						      */
	/* INPUT : std::string type																				      */
	/* RETURNED VALUE    : State_Type																			  */
	/* ---------------------------------------------------------------------------------------------------------- */
	static State_Type xmlGiveStateType
	(
		std::string type
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : xmlGiveSelectType																			    	  */
	/* ROLE : Convert an std::string from XML document to Select_Type from Texture class					      */
	/* INPUT : std::string type																				      */
	/* RETURNED VALUE    : Select_Type																			  */
	/* ---------------------------------------------------------------------------------------------------------- */
	static Select_Type xmlGiveSelectType
	(
		std::string type
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : convertUintToUnit_Movement_Type															    	  */
	/* ROLE : Convert a unsigned integer from XML document to Unit_Movement_Type from Unit class			      */
	/* ROLE : Exit if error : XML document is not properly formated											      */
	/* INPUT : unsigned int toConvert																		      */
	/* RETURNED VALUE    : Unit_Movement_Type																	  */
	/* ---------------------------------------------------------------------------------------------------------- */
	static Unit_Movement_Type convertUintToUnit_Movement_Type
	(
		unsigned int toConvert
	);

	static Unit_Movement_Type xmlGiveMovementType
	(
		std::string type
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : convert2ConversionToApply																	    	  */
	/* ROLE : Convert an integer from XML document to conversionSurplus_Type from City class				      */
	/* ROLE : Exit if error : XML document is not properly formated											      */
	/* INPUT : int toConvert																				      */
	/* RETURNED VALUE    : conversionSurplus_Type																  */
	/* ---------------------------------------------------------------------------------------------------------- */
	static conversionSurplus_Type convert2ConversionToApply
	(
		int toConvert
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : convert2build_Type																		    	  */
	/* ROLE : Convert an integer from XML document to build_Type from City class							      */
	/* ROLE : Exit if error : XML document is not properly formated											      */
	/* INPUT : int toConvert																				      */
	/* RETURNED VALUE    : build_Type																			  */
	/* ---------------------------------------------------------------------------------------------------------- */
	static build_Type convert2build_Type
	(
		int toConvert
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : convert2Emotion_Type																		    	  */
	/* ROLE : Convert an integer from XML document to Emotion_Type from City class							      */
	/* ROLE : Exit if error : XML document is not properly formated											      */
	/* INPUT : int toConvert																				      */
	/* RETURNED VALUE    : Emotion_Type																			  */
	/* ---------------------------------------------------------------------------------------------------------- */
	static Emotion_Type convert2Emotion_Type
	(
		int toConvert
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : convert2Religion_Type																		    	  */
	/* ROLE : Convert an integer from XML document to Religion_Type from City class							      */
	/* ROLE : Exit if error : XML document is not properly formated											      */
	/* INPUT : int toConvert																				      */
	/* RETURNED VALUE    : Religion_Type																		  */
	/* ---------------------------------------------------------------------------------------------------------- */
	static Religion_Type convert2Religion_Type
	(
		int toConvert
	);


private:

	/* *********************************************************
	 *							Init						   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* NAME : initStructs																   */
	/* ROLE : Initialisation des donn�es par d�faut des structures						   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	void initStructsNULL();

	/* ----------------------------------------------------------------------------------- */
	/* NAME : computeSize																   */
	/* ROLE : Calcul des diff�rentes tailles de fenetre en fonction de tileSize			   */
	/* INPUT/OUTPUT : Screen& screen : longueur et hauteur �cran						   */
	/* INPUT/OUTPUT : struct Sysinfo& : diff�rentes tailles de fenetre					   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	void computeSize();

	/* ----------------------------------------------------------------------------------- */
	/* NAME : initOpenGLScreen															   */
	/* ROLE : Init m_screen.openGLScreen and m_mainMap									   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	void initOpenGLScreen();

	/* ----------------------------------------------------------------------------------- */
	/* NAME : initHUDText																   */
	/* ROLE : Init static Text in HUD													   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	void initHUDText();

	void initUI();

public:

	/* *********************************************************
	 *							Load						   *
	 ********************************************************* */

	/* ----------------------------------------------------------------------------------- */
	/* NAME : loadUnitAndSpec															   */
	/* ROLE : Chargement des informations concernant les unit�s � partir d'un fichier	   */
	/* INPUT : const std::string& : nom du fichier � ouvrir								   */
	/* OUTPUT : std::vector<Unit_Template>& : Vecteur des Unit							   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	void loadUnitAndSpec();

	void loadCitiesNames();

private:

	/* *********************************************************
	 *						New Game						   *
	 ********************************************************* */

	/* ----------------------------------------------------------------------------------- */
	/* NAME : newGame																   	   */
	/* ROLE : Create a new save with new spaw settlers		 							   */
	/* ROLE : Players names are associate to radio button		 						   */
	/* ROLE : Save the new game set								 						   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : void														       */
	/* ------------------------------------------------------------------------------------*/
	void newGame();

	/* ----------------------------------------------------------------------------------- */
	/* NAME : pushNewPlayer															   	   */
	/* ROLE : For every name in struct UserInputNewGame push new player in m_players	   */
	/* attribut in : UserInputNewGame* m_userInputNewGame								   */
	/* attribut out : m_players															   */
	/* RETURNED VALUE : void														       */
	/* ------------------------------------------------------------------------------------*/
	void pushNewPlayer();

	/* ----------------------------------------------------------------------------------- */
	/* NAME : newGameSettlerSpawn														   */
	/* ROLE : Création des position pour les settlers de chaque joueurs					   */
	/* INPUT : const std::vector<Unit_Template>& : tableau des statistiques ...			   */
	/* INPUT : ...  par défauts des unités												   */
	/* INPUT : const struct Map& map : structure globale de la map						   */
	/* INPUT/OUTPUT : std::vector<Player*>& : vecteurs de joueurs						   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	void newGameSettlerSpawn
	(
		Players& players,
		const MainMap& mainMap
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : makeRandomPosTab															   */
	/* ROLE : WHILE new positions are not valid, create new ones						   */
	/* ROLE : --- create new positions with matriceMap & tileSize						   */
	/* ROLE : --- IF positions are valid - on ground THEN quit loop						   */
	/* ROLE : --- IF IN_DEBUG && iteration loop > MAX_RANDOM_POS_ITERATION THEN THROW	   */
	/* ROLE : Push new valid position to vector of new positions						   */
	/* IN : const Map& map : struct main map : map & tileSize							   */
	/* IN/OUT : std::vector<randomPos>& : New vector positions							   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	void makeRandomPosTab
	(
		const MainMap& mainMap,
		std::vector<randomPos>& tabRandom
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : makeRandomPos																   */
	/* ROLE : Create random positions between matriceMap								   */
	/* ROLE : pos === size - 2 * MAP_BORDER_MAX * tileSize								   */
	/* ROLE : Ceil value with tileSize													   */
	/* OUT : randomPos& RandomPOS :	New random positions								   */
	/* IN : const MatriceMap& matriceMap : matriceMap for size							   */
	/* IN : const unsigned int tileSize	: Globale tileSize								   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	void makeRandomPos
	(
		randomPos& RandomPOS,
		const MatriceMap& matriceMap,
		const unsigned int tileSize
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : conditionspace															   */
	/* ROLE : IF empty tab return TRUE													   */
	/* ROLE : ELSE test every positions with new positions  							   */
	/* ROLE : --- IF new position is in a square of spaceBetweenSettler THEN return FALSE  */
	/* ROLE : --- ELSE new position is not in a square with every positions				   */
	/* ROLE : ---			of spaceBetweenSettler THEN return TRUE						   */
	/* INPUT : const randomPos& RandomPOS : Positions to test							   */
	/* INPUT : const std::vector<randomPos>& tabRandom : tab of positions				   */
	/* INPUT : const unsigned int tileSize : Globale tileSize							   */
	/* RETURNED VALUE : TRUE -> New positions valid									       */
	/* RETURNED VALUE : FALSE -> New positions not valid						           */
	/* ------------------------------------------------------------------------------------*/
	bool conditionspace
	(
		const randomPos& RandomPOS,
		const std::vector<randomPos>& tabRandom,
		const unsigned int tileSize
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : conditionground															   */
	/* ROLE : Convert new positions to index											   */
	/* ROLE : IF Assert index to maticeMap size && tile index is ground THEN return TRUE   */
	/* ROLE : ELSE return FALSE															   */
	/* INPUT : const MatriceMap& matriceMap	: Map matrice								   */
	/* INPUT : const randomPos& RandomPOS :	New positions								   */
	/* RETURNED VALUE : TRUE -> New positions valid									       */
	/* RETURNED VALUE : FALSE -> New positions not valid						           */
	/* ------------------------------------------------------------------------------------*/
	bool conditionground
	(
		const MatriceMap& matriceMap,
		const randomPos& RandomPOS
	);

public:

	/* ----------------------------------------------------------------------------------- */
	/* NAME : makePlayersButtons														   */
	/* ROLE : Create for p, number of players, a radio button 							   */
	/* ROLE : Button will be arrange in vertical axis and by p order					   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : void														       */
	/* ------------------------------------------------------------------------------------*/
	void makePlayersButtons();

private:

	/* *********************************************************
	 *						Draw/Camera						   *
	 ********************************************************* */

	void moveCameraByDeltaTime();

	void moveCamera(float deltaTime);

	void drawGame();

	void drawHUD();

private:

	/* *********************************************************
	 *					   Input Manager					   *
	 ********************************************************* */

	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : run_SDL																					    	  */
	/* ROLE : Recherche infini des �venements d'entr� de type SDL_event : souris, clavier					      */
	/* ROLE : Si aucun �venements n'est trouv� alors le programme continue									      */
	/* INPUT : struct Sysinfo& : structure globale du programme									    			  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	void inputSDL
	(
		SDL_Event& ev
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : actionByKey																				    	  */
	/* ROLE : Define action for each key press																      */
	/* INPUT : SDL_Event& ev : Event from SDL input												    			  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	void actionByKey();

	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : wheel																						    	  */
	/* ROLE : Recherche l'incr�mentation ou d�cr�mentation du contexte										      */
	/* INPUT : struct Sysinfo& : structure globale du programme												      */
	/* INPUT : int& wheel : l'�venement de scroll de la souris													  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	void wheel
	(
		SDL_Event& ev
	);

	void mouseClick
	(
		SDL_Event& ev
	);

	unsigned int getMouseCoorNorm(unsigned char c);



	bool onPlayerButtonClicked(const CEGUI::EventArgs& e);

private:

	/* *********************************************************
	 *				   Screen Input Manager		    		   *
	 ********************************************************* */

	bool onExitClicked(const CEGUI::EventArgs& e);


public:

	/* *********************************************************
	 *						 GET/SET						   *
	 ********************************************************* */

	inline Screen& GETscreen() { return m_screen; };
	inline const Screen& GETscreen()const { return m_screen; };
	inline Var& GETvar() { return m_var; };
	inline const Var& GETvar()const { return m_var; };
	inline MainMap& GETmainMap() { return m_mainMap; };
	inline const MainMap& GETmainMap()const { return m_mainMap; };
	inline Players& GETPlayers() { return m_players; };
	inline const Players& GETPlayers()const { return m_players; };
	inline File* getFile() { return m_file; };
	inline SaveReload* getSaveReload() { return m_SaveReload; };
	inline UserInputNewGame* getUserInputNewGame() { return m_userInputNewGame; };

	inline void SETvar(Var& var) { m_var = var; };
	inline void SETmainMap(MainMap& mainMap) { m_mainMap = mainMap; };
	inline void SETPlayers(Players& players) { m_players = players; };

	inline RealEngine2D::Window& getParentWindow() { return m_game->getWindow(); }

private:

	/* *********************************************************
	 *						 Attributs						   *
	 ********************************************************* */

	 /*
		 All RealEngine2D objects
		 - Shaders
		 - camera/cameraHUD
		 - Sprite/font
		 - audioEngine
		 - GUI
	*/
	Screen m_screen;

	Var m_var;

	MainMap m_mainMap;

	NextTurn m_nextTurn;

	Players m_players;

	File* m_file;
	SaveReload* m_SaveReload;
	UserInputNewGame* m_userInputNewGame;

	bool m_isInitialize;
};




#endif // !GamePlayScreen_H


