/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.21.1.1
	file version : 1.10

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

#ifndef LIB_H
#define LIB_H

/* *********************************************************
 *				Include Standard						   *
 ********************************************************* */

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <queue>
#include <exception>
#include <stdexcept>
#include "wtypes.h"
#include <direct.h>


/* *********************************************************
 *						Include SDL						   *
 ********************************************************* */


#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"


/* *********************************************************
 *					Include tinyxml2					   *
 ********************************************************* */


#include "tinyxml2.h"


/* *********************************************************
 *					Structures							   *
 ********************************************************* */

typedef struct Unit_Template Unit_Template;
typedef struct SubcatPlayer SubcatPlayer;
typedef struct Tile Tile;
typedef struct SizeCityMap SizeCityMap;
typedef struct Screen Screen;
typedef struct File File;
typedef struct Var Var;
typedef struct Map Map;
typedef struct AllTextures AllTextures;
typedef struct AllTextes AllTextes;
typedef struct AllButtons AllButtons;
typedef struct Sysinfo Sysinfo;

typedef struct randomPos randomPos;
typedef struct GoldStats GoldStats;
typedef struct OnOffDisplay OnOffDisplay;

/* *********************************************************
 *						Classes							   *
 ********************************************************* */

class IHM;
class SaveReload;
class KeyboardMouse;
class GamePlay;
class Texture;
class Texte;
class ButtonImage;
class ButtonTexte;
class City;
class Citizen;
class LTimer;
class Player;
class Unit;
class LoadConfig;

/* *********************************************************
 *					Redéfinition Type					   *
 ********************************************************* */

typedef std::vector<std::vector<Tile>>					MatriceTile;
typedef std::unordered_map<std::string, Texture*>		MapTexture;
typedef std::unordered_map<std::string, Texte*>			MapTexte;
typedef std::unordered_map<std::string, ButtonTexte*>	MapButtonTexte;
typedef std::deque<ButtonTexte*>						DequeButtonTexte;
typedef std::vector<Player*>							TabPlayer;

#define EMPTY_STRING ""

/* Define that the compared strings are identical */
#define IDENTICAL_STRINGS 0

#endif


/*
*	End Of File : LIB.h
*/