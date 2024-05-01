/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.1.0
	file version : 1.8

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

#ifndef GameInput_H
#define GameInput_H

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

/* N/A */

/* *********************************************************
 *						 Enum							   *
 ********************************************************* */

 /* Define input from keyboard in a context */
enum class CinState_Type : unsigned int
{
	cinNothing,						/* Inputs from keyboards are discard */
	cinTitleScreen,					/* Inputs from keyboards are use in Title Screen */
	cinScreenNewGameNbPlayer,		/* Inputs from keyboards are use in New Game : for number of player */
	cinScreenNewGameNamePlayer,		/* Inputs from keyboards are use in New Game : for names of players */
	cinMainMap,						/* Inputs from keyboards are use in Main map */
};

/* *********************************************************
 *						Structures						   *
 ********************************************************* */

 /* N/A */


#endif /* GameInput_H */


/*
*	End Of File : GameInput.h
*/
