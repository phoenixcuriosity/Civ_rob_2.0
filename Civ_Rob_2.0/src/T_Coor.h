﻿/*

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

#ifndef T_Coor_H
#define T_Coor_H

#include "LIB.h"
#include <jsoncons/json.hpp>

struct Coor
{
	unsigned int x = 0;
	unsigned int y = 0;
};
JSONCONS_ALL_MEMBER_NAME_TRAITS(Coor, (x, "x"), (y, "y"))
typedef std::vector<Coor> VectCoor;

#endif // !T_Coor_H


