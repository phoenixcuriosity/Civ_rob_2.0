/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.20.0.5
	file version : 1.0

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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "Utility.h"

#include "civ_lib.h"

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : checkPlayerUnitSelection													   */
/* ROLE : Check si un joueur et une unitée sont selectionnés						   */
/* INPUT : const SubcatPlayer& : structure contenant les infos du joueur 			   */
/* RETURNED VALUE : bool : false -> joueur et/ou unité non selectionné (==-1)		   */
/* RETURNED VALUE : bool : true -> joueur et unité selectionné (!=-1)				   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Utility::checkPlayerUnitSelection
(
	const SubcatPlayer& s_player
)
{
	if	(
			NO_PLAYER_SELECTED < s_player.selectplayer
			&&
			NO_UNIT_SELECTED < s_player.selectunit
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : checkPlayerCitieSelection													   */
/* ROLE : Check si un joueur et une Citie sont selectionnés							   */
/* INPUT : const SubcatPlayer& : structure contenant les infos du joueur 			   */
/* RETURNED VALUE : bool : false -> joueur et/ou Citie non selectionné (==-1)		   */
/* RETURNED VALUE : bool : true -> joueur et Citie selectionné (!=-1)				   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool Utility::checkPlayerCitieSelection
(
	const SubcatPlayer& s_player
)
{
	if	(
			NO_PLAYER_SELECTED < s_player.selectplayer
			&&
			NO_CITIE_SELECTED < s_player.selectCitie
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : conditionTryToMove																		    	  */
/* ROLE : Condition pour vouloir bouger une Unit														      */
/* ROLE : S'il y au moins 1 joueur et qu'une Unit est sélectionné et que ...							      */
/* ROLE : statescreen =	STATEmainmap et que select = selectmove	alors l'Unit peut essayer de bouger		      */
/* INPUT : const Var var : structure des variables de types joueurs et Unit								      */
/* RETURNED VALUE : bool -> false : une ou toutes les conditions ne sont pas remplies						  */
/* RETURNED VALUE : bool -> true : toutes les conditions sont remplies										  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
bool Utility::conditionTryToMove
(
	const Var var
)
{
	if	(
			State_Type::STATEmainmap == var.statescreen
			&&
			Select_Type::selectmove == var.select
			&&
			checkPlayerUnitSelection(var.s_player)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
*	End Of File : Utility.cpp
*/
