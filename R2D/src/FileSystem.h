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

#include <string>

#include <jsoncons/json.hpp>

namespace R2D
{

class IFileSystem
{
protected:
	using Path = std::string;
	using FileName = std::string;
	using Data = std::string;
public:
    virtual void createDirectory(const Path& path) = 0;
    virtual void removeFile(const FileName& file) = 0;
	virtual void writeDataInFile(const FileName& file, const Data& data) = 0;
	virtual void writeDataInFile(const FileName& file, const jsoncons::ojson& data) = 0;
	virtual std::string readDataFromFile(const FileName& file) = 0;
	virtual jsoncons::ojson readDataFromFile(const FileName& file, const bool dummy = false) = 0;
    virtual ~IFileSystem() = default;
};


}
