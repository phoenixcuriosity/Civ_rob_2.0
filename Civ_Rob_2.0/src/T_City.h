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

#ifndef T_CITY_H
#define T_CITY_H

namespace CITY_INFLUENCE
{
	/* taille de la carte transpos�e dans la citiemap */
	constexpr unsigned int INIT_SIZE_VIEW = 9;

	const int INIT_SIZE_VIEW_DIV = static_cast<int>(ceil(CITY_INFLUENCE::INIT_SIZE_VIEW / 2));

	constexpr unsigned int INIT_AREA_VIEW = INIT_SIZE_VIEW * INIT_SIZE_VIEW;

	/* Minimal influence level in City */
	constexpr unsigned int MIN_INFLUENCE_LEVEL = 1;
}


namespace EMOTION_RANGE
{
	/* Define the maximum range of emotion */
	constexpr double MAX = 100.0;

	/* Define the minimum range of emotion */
	constexpr double MIN = 0.0;

	/* Define the mean emotion */
	constexpr double MEAN = ((MAX + MIN) / 2.0);

	/* Define the mean value of emotion range */
	const double SCALE_MEAN = ((abs(MAX) + abs(MIN)) / 2.0);
}


namespace MULTIPLIER
{
	namespace CONVERSION
	{
		/* Define the multiplier coefficient to convert work to food */
		constexpr double WORK_TO_FOOD = 10.0;

		/* Define the multiplier coefficient to convert food to work */
		constexpr double FOOD_TO_WORK = (1.0 / WORK_TO_FOOD);

		/* Define the multiplier coefficient to convert work to gold */
		constexpr double WORK_TO_GOLD = (10.0 * WORK_TO_FOOD);

		/* Define the multiplier coefficient to convert food to gold */
		constexpr double FOOD_TO_GOLD = (WORK_TO_GOLD / FOOD_TO_WORK);
	}
}

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

enum class modifAppartenance_Type : bool
{
	modify = true,
	dontModify = false
};

#endif

/*
*	End Of File : T_CITY_H.h
*/