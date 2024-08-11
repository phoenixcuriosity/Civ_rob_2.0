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

#ifndef LIB_H
#define LIB_H

#define NOMINMAX // forbid to redifine std::max/min by Windows.h and Visual Studio

#include <deque>
#include <memory>
#include <queue>
#include <string>
#include <vector>

namespace STRINGS
{
	/* Define an empty string */
	const std::string EMPTY = "";

	/* Define that the compared strings are identical */
	const int IDENTICAL = 0;

	/* Define that the compared strings are identical */
	const bool START_WITH = true;
}

namespace MODULO
{
	/* Define 0 for module use */
	const unsigned int ZERO = 0;
}

namespace PERCENTAGE
{
	/* Define Percent */
	const double ONE_HUNDRED = 100.0;
}

namespace CONTAINERS
{
	/* Define a non EMPTY vect/list/map */
	const bool NOT_EMPTY = false;
}

namespace SELECTION
{
	const int NO_PLAYER_SELECTED = -1;

	const int NO_UNIT_SELECTED = -1;

	const int NO_CITY_SELECTED = -1;

	/* The tile is not own by a player */
	const int NO_APPARTENANCE = -1;

	const auto NO_OWNER = nullptr;

	const int NO_CURRENT_SAVE_SELECTED = -1;
}

 // Define all State of the game, relate to screen
enum class State_Type
{
	error,					/* ### Reserved on error detection ### */
	STATEnothing,			/* ### Reserved for fast writeTxt  ### */
	STATEtitleScreen,		/* Title screen : first screen selection */
	STATEscreenNewgame,		/* New game screen : selection of options of a new game */
	STATEreload,			/* Load screen : selection of saves to load */
	STATEmainMap,			/* Maip map screen */
	STATEscience,			/* Science screen ### Not implemented as of 0.20.0.3  ### */
	STATEcityMap			/* Citie map screen : Unit and buildings creation */
};

// Define all Selection in the game, relate to mouse click
enum class Select_Type
{
	selectnothing,			/* Nothing is selected */
	selectcreate,			/* ### Reserved on debug as of 0.20.0.3 ### */
	selectinspect,			/* ### Reserved on debug as of 0.20.0.3 ### */
	selectmove,				/* Selection to move a Unit */
	selectmoveCitizen		/* ### Not use as of 0.20.0.3 ### */
};

struct build;
struct buildGUI;
struct GoldStats;
struct randomPos;
struct Screen;
struct Tile;
struct Unit_Template;
struct UserInputNewGame;
struct Var;

class Citizen;
class City;
class GameInput;
class GamePlayScreen;
class MainMap;
class NextTurn;
class Player;
class Players;
class SaveReload;
class Unit;

class CityScreen;
class GamePlayScreen;
class MainMenuScreen;
class NewGameScreen;
class ReloadMenuScreen;

enum class build_Type : unsigned int;
enum class CinState_Type : unsigned int;
enum class conversionSurplus_Type : unsigned int;
enum class Emotion_Type;
enum class Ground_Type;
enum class GroundSpec_Type;
enum class Move_Type;
enum class Religion_Type;
enum class resizeUnitTexture_Type : unsigned int;
enum class Unit_Movement_Type;

typedef std::deque<buildGUI> dequeBuild;

typedef std::shared_ptr<Player> PlayerPtrT;
typedef std::shared_ptr<Unit> UnitPtrT;
typedef std::shared_ptr<City> CityPtrT;
typedef std::shared_ptr<Citizen> CitizenPtrT;

typedef std::shared_ptr<CityScreen>			CityScreenPtrT;
typedef std::shared_ptr<GamePlayScreen>		GamePlayScreenPtrT;
typedef std::shared_ptr<MainMenuScreen>		MainMenuScreenPtrT;
typedef std::shared_ptr<NewGameScreen>		NewGameScreenPtrT;
typedef std::shared_ptr<ReloadMenuScreen>	ReloadMenuScreenPtrT;

typedef std::vector<Tile> VectMap;
typedef std::vector<VectMap> MatriceMap;
typedef std::vector<CitizenPtrT> VectCitizen;
typedef std::vector<CityPtrT> VectCity;
typedef std::vector<PlayerPtrT> VectPlayer;
typedef std::vector<UnitPtrT> VectUnit;
typedef std::vector<Unit_Template> VectUnitTemplate;

#endif


/*
*	End Of File : LIB.h
*/