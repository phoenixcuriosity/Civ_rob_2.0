/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.22.0.0
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

#ifndef ConstCityIHM_H
#define ConstCityIHM_H

/*
 * WARNING
 * As of 0.20.4.1
 * This file will be deleted when the generic size will be implemented for scale
 */

/* BUILDS */

#define CITY_BUILDS_SPACE_Y 32
#define CITY_BUILDS_BEGIN_Y 96

/* BUILD QUEUE */

#define CITY_BUILD_QUEUE_FONT_SIZE 32
#define CITY_BUILD_QUEUE_SPACE_Y (CITY_BUILD_QUEUE_FONT_SIZE + (CITY_BUILD_QUEUE_FONT_SIZE / 2))
#define CITY_BUILD_QUEUE_BEGIN_X 100
#define CITY_BUILD_QUEUE_BEGIN_Y 600

/* FOOD */

#define CITY_FOOD_NB_PER_ROW 10
#define CITY_FOOD_SPACE_X 24
#define CITY_FOOD_BEGIN_X 1400
#define CITY_FOOD_BEGIN_Y 500

#endif // !ConstCityIHM_H

/*
*	End Of File : ConstCityIHM.h
*/
