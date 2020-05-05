/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.20.2.1
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

#ifndef Utility_H
#define Utility_H

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"

/* *********************************************************
 *					 Constantes							   *
 ********************************************************* */

/* Define the lowest value to perform a division */
#define PRECISION_DIV 1e-12

/* *********************************************************
 *						 Structs						   *
 ********************************************************* */

/* N/A */

/* *********************************************************
 *							 Enum						   *
 ********************************************************* */

/* N/A */

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */

class Utility
{

public:

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : checkPlayerUnitSelection													   */
	/* ROLE : Check si un joueur et une unitée sont selectionnés						   */
	/* INPUT : const SubcatPlayer& : structure contenant les infos du joueur 			   */
	/* RETURNED VALUE : bool : false -> joueur et/ou unité non selectionné (==-1)		   */
	/* RETURNED VALUE : bool : true -> joueur et unité selectionné (!=-1)				   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static bool checkPlayerUnitSelection
	(
		const SubcatPlayer& s_player
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : checkPlayerCitieSelection													   */
	/* ROLE : Check si un joueur et une Citie sont selectionnés							   */
	/* INPUT : const SubcatPlayer& : structure contenant les infos du joueur 			   */
	/* RETURNED VALUE : bool : false -> joueur et/ou Citie non selectionné (==-1)		   */
	/* RETURNED VALUE : bool : true -> joueur et Citie selectionné (!=-1)				   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static bool checkPlayerCitieSelection
	(
		const SubcatPlayer& s_player
	);


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
	static bool conditionTryToMove
	(
		const Var var
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : protectedDiv																				    	  */
	/* ROLE : Check if the denominator is 0.0 then throw error, else do the division.						      */
	/* IN : double num : The numerator																		      */
	/* IN : double den : The denominator																	      */
	/* RETURNED VALUE : double -> result from division															  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static double protectedDiv
	(
		double num,
		double den
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : checkMinMaxValidityRange																	    	  */
	/* ROLE : Check if the min value is strictly lower than max value										      */
	/* IN : double min : The minimum value																	      */
	/* IN : double max : The maximum value																	      */
	/* RETURNED VALUE : bool : false -> min is greater than or equal to max										  */
	/* RETURNED VALUE : bool : true -> min strictly lower than max value										  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static bool checkMinMaxValidityRange
	(
		double min,
		double max
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : computeValueToScale																		    	  */
	/* ROLE : Scale a value from an initial range to a target range											      */
	/* ROLE : Error management : Throw error if checkMinMaxValidityRange return false						      */
	/* IN : double value : The value to scale																      */
	/* IN : double minValue : The minimum value	of the initial range										      */
	/* IN : double maxValue : The maximum value	of the initial range										      */
	/* IN : double minScale : The minimum value	of the target range											      */
	/* IN : double maxScale : The maximum value	of the target range											      */
	/* IN : int divToScaleSize : A factor to scale the initial value, default value is 1					      */
	/* RETURNED VALUE : double : result the value in the target range											  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static double computeValueToScale
	(
		double value,
		double minValue,
		double maxValue,
		double minScale,
		double maxScale,
		int divToScaleSize = 1
	);

};


#endif /* Utility_H */

/*
*	End Of File : Utility.h
*/
