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

#include <iostream>
#include <iomanip>
#include <sstream>

struct Var;
class Players;

class Utility
{
public:
	static bool checkPlayerUnitSelection
	(
		Players& players
	);

	static bool checkPlayerCitieSelection
	(
		Players& players
	);

	static bool conditionTryToMove
	(
		const Var var,
		Players& players
	);

	static bool assertSize
	(
		size_t size,
		unsigned int index
	);


	template <typename T>
	static std::string to_string_with_precision(const T a_value, const int n = 6)
	{
		std::ostringstream out;
		out.precision(n);
		out << std::fixed << a_value;
		return out.str();
	}
};