/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.7.0
	file version : 1.3

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

#ifndef NewGame_H
#define NewGame_H

#include "LIB.h"

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

/* The first settler to spawn in the map for each Player does not cost maintenance */
const double MAINTENANCE_COST_1TH_SETTLER = 0.0;

/* *********************************************************
 *						 Structs						   *
 ********************************************************* */

/* ---------------------------------------------------------------------- */
/* Structure d'un couple de positions									  */
/* Positions en x et y permettant le spawn des settlers					  */
/* ---------------------------------------------------------------------- */
struct randomPos
{
	unsigned int x;
	unsigned int y;
};

#endif // !NewGame_H
