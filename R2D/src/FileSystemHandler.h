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
#include "FileWriter.h"

#include "ErrorLog.h"
#include "log.h"
#include "LogSentences.h"


#include <filesystem>

namespace R2D
{
template <typename Format>
class FileSystemHandler
{
	using Path = std::string;
	using FileName = std::string;
	using Data = std::string;
public:
    void createDirectory(const Path& path) {
		if (!std::filesystem::create_directory(path))
		{
			LOG(R2D::LogLevelType::error, 0, logR::WHO::REGISTER, logR::WHAT::REGISTER_DIRECTORY, logR::DATA::ERROR_DIR, " : createDirectory");
		}
		else
		{
			LOG(R2D::LogLevelType::info, 0, logR::WHO::REGISTER, logR::WHAT::REGISTER_DIRECTORY, logR::DATA::NO_ERROR_DIR, " : createDirectory");
		}
	}

    void removeFile(const FileName& file) {
		if (!std::filesystem::remove(file))
		{
			LOG(R2D::LogLevelType::error, 0, logR::WHO::REGISTER, logR::WHAT::REGISTER_DIRECTORY, logR::DATA::ERROR_DIR, " : removeFile");
		}
		else
		{
			LOG(R2D::LogLevelType::info, 0, logR::WHO::REGISTER, logR::WHAT::REGISTER_DIRECTORY, logR::DATA::NO_ERROR_DIR, " : removeFile");
		}
	}

	void writeDataInFile(const FileName& file, const Format& data)
	{
		FileWriter<Format> writer(file);
		writer.write(data);
	}

	Format readDataFromFile(const FileName& file)
	{
		FileReader<Format> reader(file);
		return reader.read(file);
	}

    virtual ~FileSystemHandler() = default;
};
}

