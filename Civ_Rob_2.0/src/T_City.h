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

#ifndef T_CITY_H
#define T_CITY_H


/* *********************************************************
 *					 Constantes							   *
 ********************************************************* */

namespace CITY_INFLUENCE
{
	/* taille de la carte transpos�e dans la citiemap */
	const unsigned int INIT_SIZE_VIEW = 9;

	const unsigned int INIT_AREA_VIEW = INIT_SIZE_VIEW * INIT_SIZE_VIEW;

	/* Minimal influence level in City */
	const unsigned int MIN_INFLUENCE_LEVEL = 1;
}

/* *********************************************************
 *							 Enum						   *
 ********************************************************* */



 /* Define types of conversion that a city can apply to the ressources */
enum class conversionSurplus_Type : unsigned int
{
	No_Conversion,
	FoodToWork, /* Apply MULTIPLIER_CONVERSION_FOOD_TO_WORK */
	FoodToGold, /* Apply MULTIPLIER_CONVERSION_FOOD_TO_GOLD */
	WorkToFood, /* Apply MULTIPLIER_CONVERSION_WORK_TO_FOOD */
	WorkToGold, /* Apply MULTIPLIER_CONVERSION_WORK_TO_GOLD */
	GoldToFood, /* ### Not implemented as of 0.20.3.1 ### */
	GoldToWork  /* ### Not implemented as of 0.20.3.1 ### */
};

/* Define a type to resize Units Texture between city and mainmap */
enum class resizeUnitTexture_Type : unsigned int
{
	mainmap,
	city
};



#endif

/*
*	End Of File : T_CITY_H.h
*/