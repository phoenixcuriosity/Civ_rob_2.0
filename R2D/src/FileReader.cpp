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

#include "FileReader.h"

R2D::FileReader
::FileReader(const FilePath& filename)
: m_file(filename, std::ios::in)
{
    if (!m_file)
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }
}

R2D::FileReader::Data
R2D::FileReader
::read(const FilePath& filename)
{
    std::error_code ec;
    const uintmax_t length = std::filesystem::file_size(filename, ec);
    if (ec)
    {
        throw std::runtime_error(ec.message());
    }
    Data buffer(length, '\0');
    m_file.read(buffer.data(), length);

    const Data text{ std::string(buffer.c_str(), strlen(buffer.c_str())) };
    if (text.empty())
    {
        throw std::runtime_error("Empty file");
    }

    return text;
}

jsoncons::ojson
R2D::FileReader
::readJson(const FilePath& filename)
{
    return jsoncons::ojson::parse(read(filename));
};