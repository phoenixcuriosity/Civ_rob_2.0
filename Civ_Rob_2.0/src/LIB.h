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

#pragma once

#define NOMINMAX // forbid to redifine std::max/min by Windows.h and Visual Studio

#include <array>
#include <deque>
#include <memory>
#include <queue>
#include <string>
#include <vector>

namespace STRINGS
{
	/* Define an empty string */
	constexpr char EMPTY[] = "";

	/* Define that the compared strings are identical */
	constexpr int IDENTICAL = 0;

	/* Define that the compared strings are identical */
	constexpr bool START_WITH = true;
}

namespace MODULO
{
	/* Define 0 for module use */
	constexpr unsigned int ZERO = 0;
}

namespace PERCENTAGE
{
	/* Define Percent */
	constexpr double ONE_HUNDRED = 100.0;
}

namespace CONTAINERS
{
	/* Define a non EMPTY vect/list/map */
	constexpr bool NOT_EMPTY = false;
}

namespace SELECTION
{
	constexpr int NO_PLAYER_SELECTED = -1;

	constexpr int NO_UNIT_SELECTED = -1;

	constexpr int NO_CITY_SELECTED = -1;

	/* The tile is not own by a player */
	constexpr int NO_APPARTENANCE = -1;

	constexpr auto NO_OWNER = nullptr;
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

namespace jsoncons
{
	template <typename CharT, typename Policy, typename Allocator>
	class basic_json;

	struct order_preserving_policy;
	using ojson = basic_json<char, order_preserving_policy, std::allocator<char>>;
}