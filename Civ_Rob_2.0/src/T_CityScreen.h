/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.2.0
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

#ifndef T_CITYSCREEN_H
#define T_CITYSCREEN_H

#include "LIB.h"

#include <deque>

#include "../../Dependencies/CEGUI/widgets/PushButton.h"

/* Define the types of builds that a city can create */
enum class build_Type : unsigned int
{
	building,	/* ### Not implemented as of 0.20.3.1 ### */
	unit
};

/*
	Define a building in a City
	Use for building Queue
*/
struct build
{
	std::string name = STRINGS::EMPTY;
	build_Type type = build_Type::building;
	double work = 0.0;
	double remainingWork = 0.0;
};

struct buildGUI
{
	CEGUI::PushButton* buildG = nullptr;
	build buildQ;
};

typedef std::deque<buildGUI> dequeBuild;

#endif

/*
*	End Of File : T_CITYSCREEN_H.h
*/