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

#ifndef jsonloader_H
#define jsonloader_H

#include "T_Coor.h"
#include "T_Player.h"
#include "T_MainMap.h"

#include <jsoncons/json.hpp>

namespace jsonloader
{

constexpr char KEY_MAP[]				= "Map";
constexpr char KEY_MATRICE_MAP[]		= "MatriceMap";
constexpr char KEY_PLAYERS[]			= "Players";
constexpr char KEY_UNIT_TEMPLATE[]		= "Units";
constexpr char KEY_FILE_PATH[]			= "FilePaths";

struct Unit_Template
{
	std::string name;
	size_t type;
	unsigned int life;
	unsigned int atq;
	unsigned int def;
	unsigned int movement;
	unsigned int numberOfAttack;
	unsigned int level;
	double workToBuild;
	double maintenance;
};

struct Tile
{
	unsigned int indexX;
	unsigned int indexY;
	unsigned int tile_x;
	unsigned int tile_y;
	size_t tile_ground;
	size_t tile_spec;
	int appartenance;
	int food;
	int work;
	int gold;
};

}

JSONCONS_ALL_MEMBER_NAME_TRAITS(Coor, (x, "x"), (y, "y"))
JSONCONS_ALL_MEMBER_NAME_TRAITS(MainMapConfig, (m_tileSize, "TileSize"), (m_mapSizePix, "MapSize"))
JSONCONS_ALL_MEMBER_NAME_TRAITS(jsonloader::Unit_Template,
	(name, "Name"),
	(type, "MovementType"),
	(life, "Life"),
	(atq, "Atq"),
	(def, "Def"),
	(movement, "Mouvement"),
	(numberOfAttack, "NumberOfAttack"),
	(level, "Level"),
	(workToBuild, "WorkToBuild"),
	(maintenance, "Maintenance"))
JSONCONS_ALL_MEMBER_NAME_TRAITS(jsonloader::Tile,
	(indexX, "indexX"),
	(indexY, "indexY"),
	(tile_x, "tile_x"),
	(tile_y, "tile_y"),
	(tile_ground, "tile_ground"),
	(tile_spec, "tile_spec"),
	(appartenance, "appartenance"),
	(food, "food"),
	(work, "work"),
	(gold, "gold"))
JSONCONS_ALL_MEMBER_NAME_TRAITS(GoldStats,
	(gold, "gold"),
	(goldBalance, "goldBalance"),
	(income, "income"),
	(cost, "cost"),
	(taxIncome, "taxIncome"),
	(commerceIncome, "commerceIncome"),
	(goldConversionSurplus, "goldConversionSurplus"),
	(armiesCost, "armiesCost"),
	(buildingsCost, "buildingsCost"))




#endif // !jsonloader_H

