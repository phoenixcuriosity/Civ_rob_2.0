/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.14
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
/*

	civ_lib :
	Ce module est la librairie principale du projet civ_rob_2
	Celui-ci comprend par ordre d'apparition:
		- un appel aux différentes librairies standard et celles de la SDL2.0.8
		- un appel aux différentes librairies du projet civ_rob_2
		- la définition des constantes très importantes
		- des énumérations d'options ou spécifications
		- différentes structures différenciées par leur thème
		- une structure englobant toutes les autres -> Sysinfo


*/

#ifndef civ_lib_H
#define civ_lib_H

#include "LIB.h"
#include "Texture.h"
#include "LTimer.h"
#include "SaveReload.h"
#include "KeyboardMouse.h"


/* *********************************************************
						 Constantes
  ********************************************************* */

//--- Constantes concernant l'ecran et la dimension de la fenetre  -----------------------------------------------------------------------------------

/*
	Pendant le développement du jeux, les parametres optimaux ont été:
	*	-> SCREEN_WIDTH = 1920 pixels
	*	-> SCREEN_HEIGHT = 1088 pixels
	*	-> SCREEN_REFRESH_RATE = 60 Hz
*/


/* *********************************************************
			Calcul des Constantes
  ********************************************************* */

// Donne la valeur en pixel de la longueur et de la largeur de l'écran
inline Uint16 getHorizontal()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	Uint16 complete = 0;
	if ((complete = ((Uint16)desktop.right % 64)) == 0)
		return (Uint16)desktop.right;
	return (Uint16)desktop.right + (64 - complete);
}
// longueur de la fenetre en pixel
const Uint16 SCREEN_WIDTH = getHorizontal();

inline Uint16 getVertical()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	Uint16 complete = 0;
	if ((complete = ((Uint16)desktop.bottom % 64)) == 0)
		return (Uint16)desktop.bottom;
	return (Uint16)desktop.bottom + (64 - complete);
}
// hauteur de la fenetre en pixel
const Uint16 SCREEN_HEIGHT = getVertical();

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
						 Enum
  ********************************************************* */

// type de sol
enum Ground_Type : Uint8 { noGround, grass, water, deepwater, dirt, sand};

// spécifications du terrain
enum GroundSpec_Type : Uint8 { specnothing, coal, copper, iron, tree, stone, uranium, horse, fish, petroleum }; 

// différents état de l'écran
enum State_Type : Uint8 { STATEnothing, STATEtitleScreen, STATEscreennewgame, STATEreload, STATEmainmap, STATEscience, STATEcitiemap };

// spécifications de la séléction
enum Select_Type : Uint8 { selectnothing, NotToSelect, selectcreate, selectinspect, selectmove, selectmoveCitizen };



/* *********************************************************
						Structures
  ********************************************************* */

//---------------------- Structure niveau 3 ---------------------------------------------------------------------------------------------------------
struct Unit_Struct {

	// nom de l'unité -> /bin/UNITNAME.txt
	std::string name;

	/*
		statistiques concernant l'unité -> /bin/UNIT.txt
	*/

	unsigned int life = 0;
	unsigned int atq = 0;
	unsigned int def = 0;
	unsigned int movement = 0;
	unsigned int level = 0;
	unsigned int nbturnToBuild = 0;

};
//---------------------- Structure niveau 2 ---------------------------------------------------------------------------------------------------------
struct SubcatPlayer {

	// *** Index ***//

	// index de la cité actuellement sélectionnée
	int selectCitie = -1;

	// index du joueur actuellement sélectionné
	int selectplayer = -1;

	// index du joueur actuellement sélectionné, action : Attaquer
	int selectPlayerToAttack = -1;

	// index de l'unité actuellement sélectionnée
	int selectunit = -1;

	// index de l'unité actuellement sélectionnée, action : Attaquer
	int selectUnitToAttack = -1;

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
	std::vector<std::string> tabCitieName;

	// tableau des noms des joueurs
	std::vector<std::string> tabPlayerName;

	// tableau des statistiques par défauts des unités
	std::vector<Unit_Struct> tabUnit_Struct;

	// nombre de joueur sans nom
	unsigned int nbNoNamePlayer = 0;

	// nombre d'unité maximal différentes à créer 
	unsigned int unitNameMaxToCreate = 0;

	// nombre de cité maximal différentes à créer 
	unsigned int citieNameMaxToCreate = 0;
};
struct Tile{

	// index en X de la case : en tileSize
	Uint8 indexX = 0;

	// index en Y de la case : en tileSize
	Uint8 indexY = 0;

	// index en X de la case : en pixel
	unsigned int tile_x = 0;

	// index en Y de la case : en pixel
	unsigned int tile_y = 0;

	// nom du type de sol
	std::string tile_stringground = "";

	// type de sol -> enum Ground_Type : Uint8 { noGround, grass, water, deepwater, dirt, sand};
	Uint8 tile_ground = noGround;

	// nom du type de spécification de la case
	std::string tile_stringspec = "";

	/* 
		type de spécification
		-> enum GroundSpec_Type : Uint8 { specnothing, coal, copper, iron, tree, stone, uranium, horse, fish, petroleum }; 
	*/
	Uint8 tile_spec = 0;

	// index d'appartenance d'un case à un joueur : appartenance neutre = -1
	int appartenance = -1;

	// indice de nourriture de la case
	int8_t food = -1;

	// indice de production de la case
	int8_t work = -1;

	// indice financier de la case
	int8_t gold = -1;
};
//---------------------- Structure niveau 1 ---------------------------------------------------------------------------------------------------------
struct Screen {
	// ptr sur la fenetre crée par la SDL
	SDL_Window *window = nullptr;

	// ptr sur le renderer crée par la SDL
	SDL_Renderer *renderer = nullptr;

	// autorise le début du compteur de fps
	bool enableFPS = false;

	LTimer fpsTimer;

	// fps moyen
	int avgFPS = 0;

	int countedFrames = 0;
};
struct File {
	const std::string log = "bin/log/log.txt";
	const std::string readme = "bin/readme.txt";
	const std::string BUILDING = "bin/BUILDING.txt";
	const std::string BUILDINGNAME = "bin/BUILDINGNAME.txt";
	const std::string CITIENAME = "bin/CITIENAME.txt";
	const std::string UNIT = "bin/UNIT.txt";
	const std::string UNITNAME = "bin/UNITNAME.txt";
	const std::string SPECNAME = "bin/SPECNAME.txt";

	const std::string SaveInfo = "save/SaveInfo.txt";

	std::string SaveScreen = "save/SaveScreen.txt";
	std::string SaveMaps = "save/SaveMaps.txt";
	std::string SavePlayer = "save/SavePlayer.txt";
};
struct Var {

	/*** type primitif	***/

	// variable permettant de quitter la boucle principale donc le jeu
	bool continuer = true;

	// nombre de tours passé dans le jeu
	unsigned int nbturn = 0;

	/*	
		état de la sélection du joueur
		enum Select_Type : Uint8 { selectnothing, NotToSelect, selectcreate, selectinspect, selectmove, selectmoveCitizen };
	*/
	Uint8 select = selectnothing;

	/* 
		état de l'écran du joueur
		enum State_Type : Uint8 { STATEnothing, STATEtitleScreen, STATEscreennewgame,
		STATEreload, STATEmainmap, STATEscience, STATEcitiemap };
	*/
	Uint8 statescreen = 0;



	/*** type personnalisé	***/

	SubcatPlayer s_player;
	KeyboardMouse mouse;
	SaveReload save;
};
struct Map {
	/*
		Attention config spéciale de visual studio 2017 pour dépasser 1Mo de données dans un tableau
		propriété -> éditeur de lien -> système -> taille de la réserve de la pile -> mettre une valeur plus grande que 1Mo
	*/
	unsigned int mapSize = 4096; // en pixels
	unsigned int tileSize = 64;
	unsigned int toolBarSize = (SCREEN_WIDTH / 10) / tileSize;
	unsigned int screenOffsetX = 0; // en pixels
	unsigned int screenOffsetY = 0; // en pixels
	std::vector<std::vector<Tile>> screen;
	std::vector<std::vector<Tile>> maps;
};
struct AllTextures {
	std::vector<Texture*> ground;
	std::vector<Texture*> groundSpec;
	std::vector<Texture*> unit;
	std::vector<Texture*> citie;
	std::vector<Texture*> barLife;
	std::vector<Texture*> colorapp;
	std::vector<Texture*> colorapptile;
	std::vector<Texture*> miscTexture;

	std::vector<Texture*> titleScreen;

	TTF_Font *font[MAX_FONT];
};
struct AllTextes {
	std::vector<Texte*> titleScreen;
	std::vector<Texte*> newGame;
	std::vector<Texte*> mainMap;
	std::vector<Texte*> citieMap;

	std::vector<unsigned int> titleScreenIndex;
	std::vector<unsigned int> newGameIndex;
	std::vector<unsigned int> mainMapIndex;
	std::vector<unsigned int> citieMapIndex;
};
struct AllButtons {
	std::vector<ButtonTexte*> titleScreen;
	std::vector<ButtonTexte*> reload;
	std::vector<ButtonTexte*> mainmap;
	std::vector<ButtonTexte*> citieMap;

	std::vector<ButtonTexte*> player; // init in GamePlay.cpp

	std::vector<unsigned int> titleScreenIndex;
	std::vector<unsigned int> reloadIndex;
	std::vector<unsigned int> mainMapIndex;
	std::vector<unsigned int> citieMapIndex;
	std::vector<unsigned int> playerIndex;
};
//---------------------- Structure niveau 0 ---------------------------------------------------------------------------------------------------------
struct Sysinfo {
	// contient les données en rapport à la SDL 
	Screen screen;

	// contient les noms et le chemins des fichiers .txt 
	File file;

	// contient des variables non organisées
	Var var;

	// contient toutes les images
	AllTextures allTextures;

	// contient tous les textes
	AllTextes allTextes;

	// contient tous les boutons
	AllButtons allButton;

	// contient les données en rapport à la map
	Map map;

	// tableau de ptr sur les objets Player
	std::vector<Player*> tabplayer;
};

#endif

/*
*	End Of File
*/