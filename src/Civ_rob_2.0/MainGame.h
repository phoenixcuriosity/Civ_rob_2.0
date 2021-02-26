/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.0.0
	file version : 1.0

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

//--- Constants related to the screen  ----------------------------------------------------------------------------------------------------------

/* Define a pixel out of range of the screen on x */
#define SCREEN_MIN_X_OUT_OF_RANGE -1

/* Define a pixel out of range of the screen on y */
#define SCREEN_MIN_Y_OUT_OF_RANGE -1

/* *********************************************************
 *						 Enum							   *
 ********************************************************* */


//--- enum related to Texture -----------------------------------------------------------------------------------------------------------


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

#define NO_PLAYER_SELECTED -1
#define NO_UNIT_SELECTED -1
#define NO_CITY_SELECTED -1

struct SubcatPlayer
{

	// *** Index ***//

	// index de la cité actuellement sélectionnée
	int selectCity = NO_CITY_SELECTED;

	// index du joueur actuellement sélectionné
	int selectplayer = NO_PLAYER_SELECTED;

	// index du joueur actuellement sélectionné, action : Attaquer
	int selectPlayerToAttack = NO_PLAYER_SELECTED;

	// index de l'unité actuellement sélectionnée
	int selectunit = NO_UNIT_SELECTED;

	// index de l'unité actuellement sélectionnée, action : Attaquer
	int selectUnitToAttack = NO_UNIT_SELECTED;

	// index de l'unité actuellement sélectionnée, action : Créer
	unsigned int unitToCreate = 0;


	// *** Name ***//


	// nom de l'unité à créer à partir du menu citieMap
	std::string toBuild;

	// nom de l'unité à créer à partir du menu mainMap
	std::string unitNameToCreate;

	// nom de l'unité à effectuer un mouvement à partir du menu mainMap
	std::string unitNameToMove;


	// *** Vector ***//

	// tableau des noms des citié de tous les joueurs
	std::vector<std::string> tabCitiesName;

	// tableau des noms des joueurs
	std::vector<std::string> tabPlayerName;

	// tableau des statistiques par défauts des unités
	//std::vector<Unit_Template> tabUnit_Template;

	// nombre de joueur sans nom
	unsigned int nbNoNamePlayer = 0;

	// nombre de cité maximal différentes à créer 
	unsigned int citiesNameMaxToCreate = 0;
};

struct SizeCityMap
{
	unsigned int ToolbarButtonsH = 0;
	unsigned int ToolbarButtonsW = 0;
};

//---------------------- Structure niveau 1 ---------------------------------------------------------------------------------------------------------
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
	//CinState_Type cinState = CinState_Type::cinNothing;



	/*** type personnalisé	***/

	SubcatPlayer s_player;

};
struct Map
{
	/*
		Attention config spéciale de visual studio 2017 pour dépasser 1Mo de données dans un tableau
		propriété -> éditeur de lien -> système -> taille de la réserve de la pile -> mettre une valeur plus grande que 1Mo
	*/
	unsigned int mapSize = 0; // en pixels
	unsigned int tileSize = 0;
	unsigned int toolBarSize = 0;
	unsigned int screenOffsetXIndexMin = 0;
	unsigned int screenOffsetYIndexMin = 0;
	unsigned int screenOffsetXIndexMax = 0;
	unsigned int screenOffsetYIndexMax = 0;
	//MatriceMap matriceMap;
	SizeCityMap sizeCityMap;
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	
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

	void runGameLoop();

public:

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
	

	inline Screen& GETscreen() { return _screen; };
	inline File& GETfile() { return _file; };
	inline Var& GETvar() { return _var; };
	inline Map& GETmap() { return _map; };
	inline VectPlayer& GETvectPlayer() { return _vectPlayer; };
	inline GameInput& GETgameInput() { return _gameInput; };
	inline std::ofstream& GETlogger() { return _logger; };

	inline void SETscreen(Screen& screen) { _screen = screen; };
	inline void SETfile(File& file) { _file = file; };
	inline void SETvar(Var& var) {_var = var; };
	inline void SETmap(Map& map) { _map = map; };
	inline void SETvectPlayer(VectPlayer& vectPlayer) {  _vectPlayer = vectPlayer; };
	inline void SETgameInput(GameInput& gameInput) {  _gameInput= gameInput; };
	/* NO SET : _logger */

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
	/* NAME : initTile																	   */
	/* ROLE : Initialisation des cases de la map en fonction de sa taille				   */
	/* INPUT : struct Map& : donn�es g�n�rale de la map : taille						   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void initTile
	(
		Map& map
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


private:
	
	Screen _screen;

	File _file;

	Var _var;

	Map _map;

	VectPlayer _vectPlayer;

	GameInput _gameInput;

	std::ofstream _logger;

};

#endif /* MainGame_H */

/*
*	End Of File : MainGame.h
*/

