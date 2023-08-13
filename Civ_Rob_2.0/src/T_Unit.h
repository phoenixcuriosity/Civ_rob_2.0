/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.1.0
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

#ifndef T_Unit_H
#define T_Unit_H

#include "LIB.h"
#include <vector>

/* Define movement for the Unit in case of tryToMove */
enum class Move_Type
{
	cannotMove,		/* The Unit cannot move to the next Tile */
	canMove,		/* The Unit can move to the next Tile */
	attackMove		/* The Unit can move to the next Tile and attack the other Unit standing on the this Tile */
};

/* Define movement type of the Unit */
enum class Unit_Movement_Type
{
	ground,			/* The Unit can move on ground (dirt,grass,...) */
	air,			/* The Unit can move on ground (dirt,grass,...) or on water */
	water,			/* The Unit can move on water */
	deepwater		/* The Unit can move on deepwater or on water */
};

/* *********************************************************
 *						 Structs						   *
 ********************************************************* */

struct Unit_Template
{

	// nom de l'unit� -> /bin/UNITNAME.txt
	std::string name;

	/*
		statistiques concernant l'unit� -> /bin/UNIT.txt
	*/
	Unit_Movement_Type type = Unit_Movement_Type::ground;
	unsigned int life = 0;
	unsigned int atq = 0;
	unsigned int def = 0;
	unsigned int movement = 0;
	unsigned int numberOfAttack = 0;
	unsigned int level = 0;
	unsigned int nbturnToBuild = 0;
	double workToBuild = 0.0;
	double maintenance = 0.0;
};

typedef std::vector<Unit_Template> VectUnitTemplate;


#endif // !T_Unit_H


