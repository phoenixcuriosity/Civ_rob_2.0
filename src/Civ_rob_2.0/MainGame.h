/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.1.0
	file version : 1.1

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

#include "Player.h"
#include "GameInput.h"
#include "MainMap.h"
#include "SaveReload.h"
#include "GameEngine.h"


/* Define center type for Texture to print on the screen */
enum class Center_Type : Uint8
{
	nocenter,	/* Positions x and y are unchanged */
	center_x,	/* Positions y is unchanged and x is center depending on the length of the texte */
	center_y,	/* Positions x is unchanged and y is center depending on the height of the texte */
	center		/* Positions x and y are center depending on the length and the height of the texte */
};

// Donne la fréquence de rafraichissement de l'écran en Hz
inline Uint8 getRefreshRate()
{
	DEVMODE screen;
	memset(&screen, 0, sizeof(DEVMODE));
	if (EnumDisplaySettings(NULL, 0, &screen))
	{
		return (Uint8)screen.dmDisplayFrequency;
	}
	return 0;
}
// fréquence de rafraichissement de l'écran en Hz
const Uint8 SCREEN_REFRESH_RATE = getRefreshRate();

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

const std::string configFilePath = "bin/config.xml";



//---------------------- Structure niveau 1 ------------------------------------------------------------------------------//
struct Screen
{
	// ptr sur la fenetre crée par la SDL
	SDL_Window* window = nullptr;

	Uint16 screenWidth = 0;

	Uint16 screenHeight = 0;

	SDL_Event evnt;
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
};
struct Var
{

	/*** type primitif	***/

	int argc = 0;

	char** argv = nullptr;

	// variable permettant de quitter la boucle principale donc le jeu
	bool continuer = true;

	bool waitEvent = true;

	// nombre de tours passé dans le jeu
	unsigned int nbturn = 0;

	/* Nb player */
	Uint8 nbPlayer = 0;

	std::string tempPlayerName = EMPTY_STRING;

	unsigned int tempX = 0;
	unsigned int tempY = 0;

	/*
		état de la sélection du joueur
		enum Select_Type : Uint8
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
		enum State_Type : Uint8
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
			enum CinState_Type : Uint8
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
	void initStructs
	(

	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initFile																	   */
	/* ROLE : Initialisation des fichiers : log											   */
	/* INPUT : struct File& : nom des fichiers											   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void initFile
	(

	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initMain																	   */
	/* ROLE : Chargement des informations de la configuration du jeu					   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void initMain
	(

	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : computeSize																   */
	/* ROLE : Calcul des diff�rentes tailles de fenetre en fonction de tileSize			   */
	/* INPUT/OUTPUT : Screen& screen : longueur et hauteur �cran						   */
	/* INPUT/OUTPUT : struct Sysinfo& : diff�rentes tailles de fenetre					   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void computeSize
	(

	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initSDL																	   */
	/* ROLE : Initialisation de la SDL fenetre et renderer ...							   */
	/* ROLE : ... ainsi que le tableau de police de font								   */
	/* INPUT : SDL_Window*& : pointeur sur la fenetre de la SDL							   */
	/* INPUT : SDL_Renderer*& : pointeur sur le Renderer de la SDL						   */
	/* INPUT : TTF_Font*[] : pointeur sur le tableau de police de font					   */
	/* RETURNED VALUE    : bool : true = pas d'erreur lors de l'initialisation de la SDL   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	bool initSDL();

public:

	/* *********************************************************
	*					Screen width and height				   *
	********************************************************* */
	
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : getHorizontal																   */
	/* ROLE : Calcul de la longueur en pixels de la fenetre								   */
	/* INPUT : unsigned int tileSize : taille en pixel d'une tile 						   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static Uint16 getHorizontal
	(
		unsigned int tileSize
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : getVertical																   */
	/* ROLE : Calcul de la hauteur en pixels de la fenetre								   */
	/* INPUT : unsigned int tileSize : taille en pixel d'une tile 						   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static Uint16 getVertical
	(
		unsigned int tileSize
	);

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

	void runGameLoop();

private:

public:

	/* *********************************************************
     *						NewGame							   *
     ********************************************************* */

	void newGame();

private:
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : newGameSettlerSpawn														   */
	/* ROLE : Création des position pour les settlers de chaque joueurs					   */
	/* INPUT : const std::vector<Unit_Template>& : tableau des statistiques ...			   */
	/* INPUT : ...  par défauts des unités												   */
	/* INPUT : const struct Map& map : structure globale de la map						   */
	/* INPUT/OUTPUT : std::vector<Player*>& : vecteurs de joueurs						   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void newGameSettlerSpawn();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : makeRandomPosTab															   */
	/* ROLE : Créér autant de vecteur de position (x,y) que de joueur initial			   */
	/* INPUT : const Map& map : structure globale de la map								   */
	/* INPUT/OUTPUT : std::vector<randomPos>& : vecteurs de positions					   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void makeRandomPosTab
	(
		const MainMap& mainMap,
		std::vector<randomPos>& tabRandom
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : makeRandomPos																   */
	/* ROLE : créér un vecteur de position (x,y) aléatoire respectant la taille de l'écran */
	/* OUTPUT : randomPos& RandomPOS : couple de positions								   */
	/* INPUT : const std::vector<std::vector<Tile>>& maps : Matrice maps				   */
	/* INPUT : unsigned int toolBarSize: taille de la barre d'outil						   */
	/* INPUT : unsigned int tileSize													   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void makeRandomPos
	(
		randomPos& RandomPOS,
		const MatriceMap& matriceMap,
		unsigned int toolBarSize,
		unsigned int tileSize
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : conditionspace															   */
	/* ROLE : condition pour valider les coordonnées crées:								   */
	/* ROLE : etre en dehors d'un carré d'influence (ici tileSize * 8) d'une autre entitée */
	/* INPUT : const randomPos& RandomPOS : couple de positions							   */
	/* INPUT : const std::vector<randomPos>& : vecteurs de positions					   */
	/* INPUT : unsigned int tileSize													   */
	/* INPUT : unsigned int i : couple de positions courant								   */
	/* RETURNED VALUE    : true -> condition de position validée / false -> non valide     */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	bool conditionspace
	(
		const randomPos& RandomPOS,
		const std::vector<randomPos>& tabRandom,
		unsigned int tileSize
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : conditionground															   */
	/* ROLE : condition pour valider les coordonnées crées:								   */
	/* ROLE : - etre sur une tile possédant la caractéristique d'etre du sol			   */
	/* INPUT : const std::vector<std::vector<Tile>>& : Matrice de la map				   */
	/* INPUT : const std::vector<randomPos>& : vecteurs de positions					   */
	/* RETURNED VALUE    : true -> condition de position validée / false -> non valide	   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	bool conditionground
	(
		const MatriceMap& matriceMap,
		const randomPos& RandomPOS
	);


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
		const std::string msg
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
		const std::string msg
	);

public:
	
	/* *********************************************************
	 *						GET/SET							   *
	 ********************************************************* */

	inline Screen& GETscreen() { return _screen; };
	inline const Screen& GETscreen()const { return _screen; };
	inline File& GETfile() { return _file; };
	inline const File& GETfile()const { return _file; };
	inline Var& GETvar() { return _var; };
	inline const Var& GETvar()const { return _var; };
	inline MainMap& GETmainMap() { return _mainMap; };
	inline const MainMap& GETmainMap()const { return _mainMap; };
	inline Players& GETPlayers() { return _players; };
	inline const Players& GETPlayers()const { return _players; };
	inline GameInput& GETgameInput() { return _gameInput; };
	inline const GameInput& GETgameInput()const { return _gameInput; };
	inline SaveReload& GETsaveReload() { return _saveReload; };
	inline const SaveReload& GETsaveReload()const { return _saveReload; };
	inline GameEngine& GETgameEngine() { return _gameEngine; };
	inline const GameEngine& GETgameEngine()const { return _gameEngine; };
	inline std::ofstream& GETlogger() { return _logger; };

	inline void SETscreen(Screen& screen) { _screen = screen; };
	inline void SETfile(File& file) { _file = file; };
	inline void SETvar(Var& var) {_var = var; };
	inline void SETmainMap(MainMap& mainMap) { _mainMap = mainMap; };
	inline void SETPlayers(Players& players) {  _players = players; };
	inline void SETgameInput(GameInput& gameInput) {  _gameInput= gameInput; };
	inline void SETsaveReload(SaveReload& saveReload) {  _saveReload = saveReload; };
	/* NO SET : _logger */

private:

	/* *********************************************************
	 *						Attributs						   *
	 ********************************************************* */
	
	Screen _screen;

	File _file;

	Var _var;

	MainMap _mainMap;

	Players _players;

	GameInput _gameInput;

	GameEngine _gameEngine;
	
	SaveReload _saveReload;

	std::ofstream _logger;

};

#endif /* MainGame_H */

/*
*	End Of File : MainGame.h
*/

