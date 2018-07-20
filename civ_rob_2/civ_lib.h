/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.7

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
		- une structure englobant toutes les autres -> sysinfo


*/

#ifndef civ_lib_H
#define civ_lib_H

#include "LIB.h"

#include "Buttons.h"
#include "Texture.h"
#include "LTimer.h"

const unsigned int SCREEN_WIDTH = 1920;
const unsigned int SCREEN_HEIGHT = 1088;
const int tileSize = 32;
const unsigned int buildingSize = 128;
const unsigned int toolBarSize = (SCREEN_WIDTH / 10) / tileSize;
const unsigned int minusTiles = (SCREEN_HEIGHT / tileSize) * toolBarSize;
const unsigned int nbSuperTiles = 9;

const int initSizeView = 7; // taille de la carte transposée dans la citiemap
const int initSizeInfluence = 2;// taille de l'influence de la citie initialement

const SDL_Color Black = { 0, 0, 0, 255 };
const SDL_Color White = { 255, 255, 255, 255 };
const SDL_Color Red = { 255, 0, 0, 255 };
const SDL_Color Green = { 0, 255, 0, 255 };
const SDL_Color Blue = { 0, 0, 255, 255 };
const SDL_Color WriteColorButton = { 255, 64, 0, 255 }; // orange
const SDL_Color BackColorButton = { 64, 64, 64, 255 }; // gris

enum { normal, shaded, normaltexture};
enum { nocenter, center_x, center_y, center };
enum { noground, grass, water, deepwater, dirt, sand};
enum unitclass{ biter, car, ouvrier_tier_1, ouvrier_tier_2, ouvrier_tier_3, robot, rocket, rover ,settler,
	spitter, tank, transport_plan};
enum { specnothing, coal, copper, iron, tree, stone, uranium, horse, fish, petroleum }; // spécifications du terrain
enum { STATEnothing, STATEecrantitre, STATEecrannewgame, STATEmainmap, STATEscience, STATEcitiemap };  // différents état de l'écran
enum { selectnothing, NotToSelect, selectcreate, selectinspect, selectmove, selectmoveCitizen };	// spécifications de la séléction
enum { cottage, hameau, village, ville, metropole, megalopole };


typedef struct screen screen;
struct screen {
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;

	unsigned int statescreen = 0; // selectnothing par défaut
	int optiontileSize = 32; // par défaut
	std::string stringTileSize = std::to_string(optiontileSize);

	bool enableFPS = false;
	LTimer fpsTimer;
	int avgFPS = 0;

};

typedef struct fichier fichier;
struct fichier {
	const std::string log = "bin/log/log.txt";
	const std::string readme = "bin/readme.txt";
	const std::string BUILDING = "bin/BUILDING.txt";
	const std::string BUILDINGNAME = "bin/BUILDINGNAME.txt";
	const std::string CITIENAME = "bin/CITIENAME.txt";
	const std::string UNIT = "bin/UNIT.txt";
	const std::string UNITNAME = "bin/UNITNAME.txt";
	const std::string SPECNAME = "bin/SPECNAME.txt";

	const std::string SaveInfo = "save/SaveInfo.txt";
	
	std::string Savemaps = "save/Savemaps.txt";
	std::string SavePlayer = "save/SavePlayer.txt";
};


typedef struct tabUnitAndSpec tabUnitAndSpec;
struct tabUnitAndSpec {
	std::string name;

	unsigned int life = 0;
	unsigned int atq = 0;
	unsigned int def = 0;
	unsigned int movement = 0;
	unsigned int level = 0;
	unsigned int nbturnToBuild = 0;

};

typedef struct var var;
struct var {
	unsigned int nbturn = 0;

	unsigned int select = selectnothing;
	int selectTile = -1;
	int selectCitie = -1;
	int selectplayer = -1;
	int selectPlayerToAttack = -1;
	int selectunit = -1;
	int selectUnitToAttack = -1;
	unsigned int unitToCreate = 0;
	std::string toBuild;
	std::string unitNameToCreate;
	std::string unitNameToMove;
	std::vector<std::string> tabCitieName;
	std::vector<std::string> tabPlayerName;
	std::vector<tabUnitAndSpec> s_tabUnitAndSpec;
	unsigned int nbNoNamePlayer = 0;
	unsigned int unitNameMaxToCreate = 0;
	unsigned int citieNameMaxToCreate = 0;


	unsigned int mouse_x = 0;
	unsigned int mouse_y = 0;
	unsigned int ywheel = 0;
	unsigned int xwheel = 0;

	unsigned int currentSave = 0;
	unsigned int nbSave = 0;

	bool continuer = true;
};


typedef struct tile tile;
struct tile{
	unsigned int tile_nb = 0;
	unsigned int tile_x = 0;
	unsigned int tile_y = 0;
	std::string tile_stringground = "";
	unsigned int tile_ground = 0; // 1=grass,2=water
	std::string tile_stringspec = "";
	unsigned int tile_spec = 0;// 0=nothing
	int appartenance = -1; // appartenance neutre

	unsigned int food = -1;
	unsigned int work = -1;
	unsigned int gold = -1;
};

typedef struct map map;
struct map {
	/*
		Attention config spéciale de visual studio 2017 pour dépasser 1Mo de données dans un tableau
		propriété -> éditeur de lien -> système -> taille de la réserve de la pile -> mettre une valeur plus grande que 1Mo
	*/
	tile tiles[(((SCREEN_WIDTH / tileSize)*(SCREEN_HEIGHT / tileSize)) - minusTiles)];
	
	//unsigned int selectsupertiles = ceil(float(SUPERTILES)/2);
};



typedef struct texture texture;
struct texture {
	std::vector<Texture*> tabTexture;
	TTF_Font *font[80];
	unsigned int indexEndGroundStartSpec = 0;
	unsigned int indexEndSpecStartUnit = 0;
	unsigned int indexEndUnitStartBarLife = 0;
	unsigned int indexEndBarLifeStartColorApp = 0;
	unsigned int indexEndColorAppStartColorAppTile = 0;
	unsigned int indexEndColorAppTileStartMiscTexture = 0;
	unsigned int indexEndMiscTextureStartWrite = 0;
};

typedef struct sysinfo sysinfo;
struct sysinfo {
	screen ecran;
	fichier file;
	var variable;
	map maps;
	std::vector<Buttons*> tabbutton;
	texture allTextures;
};












#endif