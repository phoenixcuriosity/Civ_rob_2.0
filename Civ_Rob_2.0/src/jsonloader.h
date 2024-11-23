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

#include <jsoncons/json.hpp>

namespace jsonloader
{

constexpr char KEY_MAP[] = "Map";
constexpr char KEY_UNIT_TEMPLATE[] = "Units";
struct MapConfigJSON
{
	unsigned int TileSize;
	unsigned int MapSizeX;
	unsigned int MapSizeY;
};

struct Unit_Template
{
	std::string name;
	std::string type;
	unsigned int life;
	unsigned int atq;
	unsigned int def;
	unsigned int movement;
	unsigned int numberOfAttack;
	unsigned int level;
	double workToBuild;
	double maintenance;
};

}


JSONCONS_ALL_MEMBER_NAME_TRAITS(jsonloader::MapConfigJSON, (TileSize, "TileSize"), (MapSizeX, "MapSizeX"), (MapSizeY, "MapSizeY"))
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

#endif // !jsonloader_H

