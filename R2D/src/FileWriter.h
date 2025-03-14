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

namespace R2D
{
class FileWriter
{
public:
    FileWriter(const std::string& filename)
    : m_file(filename, std::ios::out | std::ios::binary)
    {
        if (!m_file)
        {
            throw std::runtime_error("Unable to open file: " + filename);
        }
    }

    template <typename T>
    void write(const T& data)
    {
        if constexpr (std::is_same_v<T, std::string>)
        {
            m_file.write(data.data(), data.size());
        }
        else if constexpr (std::is_same_v<T, jsoncons::ojson>)
        {
            jsoncons::encode_json(data, m_file, jsoncons::indenting::indent);
        }
        else
        {
            static_assert(sizeof(T) == 0, "Unsupported type for FileWriter.");
        }

        if (!m_file)
        {
            throw std::runtime_error("Error writing to file.");
        }
    }

    ~FileWriter() = default;

private:
    std::ofstream m_file;
};
}