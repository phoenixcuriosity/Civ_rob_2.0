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

#include <iostream>
#include <fstream>
#include <jsoncons/json.hpp>
#include <filesystem>

namespace R2D
{
class FileReader
{
private:
    using FilePath = std::string;
    using Data = std::string;

public:
	FileReader(const FilePath& filename);
    Data read(const FilePath& filename);
    jsoncons::ojson readJson(const FilePath& filename);
    ~FileReader() = default;

private:
    std::ifstream m_file;
};
}
