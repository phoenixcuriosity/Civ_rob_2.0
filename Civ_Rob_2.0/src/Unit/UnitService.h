
/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2025 (robin.sauter@orange.fr)

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

#include "Unit.h"

namespace unit
{

class UnitService
{
private:
	using PlayerPtrT = std::shared_ptr<Player>;
	using UnitPtrT = std::shared_ptr<Unit>;
	using VectMap = std::vector<Tile>;
	using MatriceMap = std::vector<VectMap>;
public:
    static bool searchUnitTile(Players& players, const glm::i32vec2& mouseCoorNorm, Select_Type* select);
    static void tryToMove(const MatriceMap& maps, Players& players, Select_Type select, const R2D::CardinalDirection& cardinalDirection);
    static Unit::Move_Type searchToMove(const MatriceMap& maps, Players& players, const R2D::CardinalDirection& cardinalDirection, int* const playerToAttack, int* const unitToAttack);
    static bool checkUnitNextTile(const Unit& from, const Unit& to, const int x, const int y);
    static bool checkNextTile(const Unit& from, const Tile& to, const int x, const int y);
};

}
