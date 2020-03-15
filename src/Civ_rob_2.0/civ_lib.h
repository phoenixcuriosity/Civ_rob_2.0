/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.19
	file version : 1.9

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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"
#include "Texture.h"
#include "LTimer.h"
#include "SaveReload.h"
#include "KeyboardMouse.h"

/* *********************************************************
 *				Calcul des Constantes					   *
 ********************************************************* */

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
#define NO_CITIE_SELECTED -1
#define NO_APPARTENANCE -1
#define EMPTY_STRING ""

/* *********************************************************
 *						 Enum							   *
 ********************************************************* */

// spécifications de la séléction CinState_Type
enum class CinState_Type : Uint8
{
	cinNothing,
	cinTitleScreen,
	cinScreenNewGameNbPlayer,
	cinScreenNewGameNamePlayer,
	cinMainMap,
};

// type de sol
enum class Ground_Type : Uint8
{
	error,
	grass,
	water,
	deepwater,
	dirt,
	sand
};

// spécifications du terrain
enum class GroundSpec_Type : Uint8
{
	nothing,
	coal,
	copper,
	iron,
	tree,
	stone,
	uranium,
	horse,
	fish,
	petroleum
};

enum class Unit_Movement_Type : Uint8
{
	ground,
	air,
	water,
	deepwater
};

/* *********************************************************
 *						Structures						   *
 ********************************************************* */

//---------------------- Structure niveau 3 ---------------------------------------------------------------------------------------------------------
struct Unit_Struct
{

	// nom de l'unité -> /bin/UNITNAME.txt
	std::string name;

	/*
		statistiques concernant l'unité -> /bin/UNIT.txt
	*/
	Unit_Movement_Type type = Unit_Movement_Type::ground;
	unsigned int life = 0;
	unsigned int atq = 0;
	unsigned int def = 0;
	unsigned int movement = 0;
	unsigned int level = 0;
	unsigned int nbturnToBuild = 0;

};
//---------------------- Structure niveau 2 ---------------------------------------------------------------------------------------------------------
struct SubcatPlayer
{

	// *** Index ***//

	// index de la cité actuellement sélectionnée
	int selectCitie = NO_CITIE_SELECTED;

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
	std::vector<std::string> tabCitieName;

	// tableau des noms des joueurs
	std::vector<std::string> tabPlayerName;

	// tableau des statistiques par défauts des unités
	std::vector<Unit_Struct> tabUnit_Struct;

	// nombre de joueur sans nom
	unsigned int nbNoNamePlayer = 0;

	// nombre de cité maximal différentes à créer 
	unsigned int citieNameMaxToCreate = 0;
};
struct Tile
{

	// index en X de la case : en tileSize
	Uint8 indexX = 0;

	// index en Y de la case : en tileSize
	Uint8 indexY = 0;

	// index en X de la case : en pixel
	unsigned int tile_x = 0;

	// index en Y de la case : en pixel
	unsigned int tile_y = 0;

	// nom du type de sol
	std::string tile_stringground = EMPTY_STRING;

	// type de sol -> enum Ground_Type : Uint8 { noGround, grass, water, deepwater, dirt, sand};
	Ground_Type tile_ground = Ground_Type::error;

	// nom du type de spécification de la case
	std::string tile_stringspec = EMPTY_STRING;

	/* 
		type de spécification
		-> enum GroundSpec_Type : Uint8 { nothing, coal, copper, iron, tree, stone, uranium, horse, fish, petroleum }; 
	*/
	GroundSpec_Type tile_spec = GroundSpec_Type::nothing;

	// index d'appartenance d'un case à un joueur : appartenance neutre = -1
	int appartenance = NO_APPARTENANCE;

	// indice de nourriture de la case
	int8_t food = -1;

	// indice de production de la case
	int8_t work = -1;

	// indice financier de la case
	int8_t gold = -1;
};
struct CitieMap
{
	unsigned int ToolbarButtonsH = 0;
	unsigned int ToolbarButtonsW = 0;
};

//---------------------- Structure niveau 1 ---------------------------------------------------------------------------------------------------------
struct Screen
{
	// ptr sur la fenetre crée par la SDL
	SDL_Window *window = nullptr;

	// ptr sur le renderer crée par la SDL
	SDL_Renderer *renderer = nullptr;

	Uint16 screenWidth = 0;

	Uint16 screenHeight = 0;

	// autorise le début du compteur de fps
	bool enableFPS = false;

	LTimer fpsTimer;

	// fps moyen
	int avgFPS = 0;

	int countedFrames = 0;
};
struct File
{
	const std::string log = "bin/log/log.txt";

	std::string readme =		EMPTY_STRING;
	std::string Texte =			EMPTY_STRING;
	std::string BUILDING =		EMPTY_STRING;
	std::string CITIENAME =		EMPTY_STRING;
	std::string UNIT =			EMPTY_STRING;
	std::string SPECNAME =		EMPTY_STRING;

	std::string SaveInfo =		EMPTY_STRING;

	std::string SaveMaps =		EMPTY_STRING;
	std::string SavePlayer =	EMPTY_STRING;
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
			NotToSelect,
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



	/*** type personnalisé	***/

	SubcatPlayer s_player;
	KeyboardMouse mouse;
	SaveReload save;
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
	MatriceTile maps;
	CitieMap citieMap;
};
struct AllTextures
{
	TTF_Font *font[MAX_FONT];

	MapTexture ground;
	MapTexture groundSpec;
	MapTexture colorapp;
	MapTexture colorapptile;
	MapTexture barLife;

	MapTexture titleScreen;
	MapTexture unit;
	MapTexture citieMap;
};
struct AllTextes
{
	MapTexte number;

	MapTexte titleScreen;
	MapTexte newGame;
	MapTexte mainMap;
	MapTexte citieMap;
};
struct AllButtons
{
	MapButtonTexte titleScreen;
	MapButtonTexte reload;
	MapButtonTexte mainMap;
	MapButtonTexte citieMap;

	MapButtonTexte player; // init in GamePlay.cpp
};
//---------------------- Structure niveau 0 ---------------------------------------------------------------------------------------------------------
struct Sysinfo
{
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
	TabPlayer tabplayer;
};

#endif /* civ_lib_H */

/*
*	End Of File : civ_lib.h
*/