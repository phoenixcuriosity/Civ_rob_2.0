/*

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
#pragma once

#include "LIB.h"

namespace MAPH
{
	constexpr unsigned int MAP_BORDER_MAX = 4;
}

 // Define Ground type use on the map
enum class Ground_Type
{
	error,			/* ### Reserved on error detection ### */
	grass,
	water,
	deepwater,
	irragated,
	dirt,			/* ### Not use as of 0.20.0.3 ### */
	sand			/* ### Not use as of 0.20.0.3 ### */
};

// Define specification for a tile on the map
enum class GroundSpec_Type
{
	nothing,		/* The Tile has no specification */
	coal,
	copper,
	iron,
	tree,
	stone,
	uranium,
	horse,
	fish,
	petroleum
};

struct Tile
{
	// index en X de la case : en tileSize
	unsigned int indexX = 0;

	// index en Y de la case : en tileSize
	unsigned int indexY = 0;

	// index en X de la case : en pixel
	unsigned int tile_x = 0;

	// index en Y de la case : en pixel
	unsigned int tile_y = 0;

	// type de sol -> enum Ground_Type : unsigned int { noGround, grass, water, deepwater, dirt, sand};
	Ground_Type tile_ground = Ground_Type::error;

	/*
		type de sp�cification
		-> enum GroundSpec_Type : unsigned int { nothing, coal, copper, iron, tree, stone, uranium, horse, fish, petroleum };
	*/
	GroundSpec_Type tile_spec = GroundSpec_Type::nothing;

	// index d'appartenance d'un case � un joueur : appartenance neutre = -1
	int appartenance = SELECTION::NO_APPARTENANCE;

	// indice de nourriture de la case
	int food = -1;

	// indice de production de la case
	int work = -1;

	// indice financier de la case
	int gold = -1;
};