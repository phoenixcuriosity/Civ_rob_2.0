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

namespace logR
{
	namespace WHO
	{
		constexpr char RESSOURCES_MANAGER[] = "[RESSOURCES_MANAGER]";
		constexpr char REGISTER[] = "[REGISTER]";
	};
	namespace WHAT
	{
		constexpr char TEXTURE[] = "[TEXTURE]";
		constexpr char FILE[] = "[FILE]";
		constexpr char TEXT[] = "[TEXT]";
		constexpr char DIRECTION[] = "[DIRECTION]";

		constexpr char REGISTER_DIRECTORY[] = "[REGISTER_DIRECTORY]";
	};
	namespace DATA
	{
		constexpr char ERROR_LOAD_TEXTURE[] = "[ERROR_LOAD_TEXTURE] : {}";
		constexpr char LOAD_TEXTURE[] = "[LOAD_TEXTURE] : {}";

		constexpr char ERROR_FIND_TEXTURE[] = "[TEXTURE] : {}";
		constexpr char ERROR_OPEN_FILE[] = "ERROR_OPEN_FILE : {}";
		constexpr char ERROR_EMPTY_FILE[] = "ERROR_EMPTY_FILE : {}";
		constexpr char ERROR_SIZE_FILE[] = "ERROR_SIZE_FILE : {}";

		constexpr char ERROR_KEY_TEXT_MISSING[] = "ERROR_KEY_TEXT_MISSING : {}";

		constexpr char ERROR_DIRECTION[] = "[ERROR : {}]";

		constexpr char ERROR_DIR[] = "[ERROR : {}]";
		constexpr char NO_ERROR_DIR[] = "[OK : {}]";
	};
};


