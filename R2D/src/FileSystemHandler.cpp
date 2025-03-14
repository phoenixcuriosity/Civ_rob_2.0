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

#include "FileSystemHandler.h"

#include "FileWriter.h"
#include "FileReader.h"
#include "LogSentences.h"

#include "ErrorLog.h"
#include "ExitFromError.h"
#include "Log.h"

#include <filesystem>

void
R2D::FileSystemHandler
::createDirectory(const Path& path)
{
	if (!std::filesystem::create_directory(path))
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::REGISTER, logS::WHAT::REGISTER_DIRECTORY, logS::DATA::ERROR_DIR, " : createDirectory");
	}
	else
	{
		LOG(R2D::LogLevelType::info, 0, logS::WHO::REGISTER, logS::WHAT::REGISTER_DIRECTORY, logS::DATA::NO_ERROR_DIR, " : createDirectory");
	}
}

void
R2D::FileSystemHandler
::removeFile(const FileName& file)
{
	if (!std::filesystem::remove(file))
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::REGISTER, logS::WHAT::REGISTER_DIRECTORY, logS::DATA::ERROR_DIR, " : removeFile");
	}
	else
	{
		LOG(R2D::LogLevelType::info, 0, logS::WHO::REGISTER, logS::WHAT::REGISTER_DIRECTORY, logS::DATA::NO_ERROR_DIR, " : removeFile");
	}
}

void
R2D::FileSystemHandler
::writeDataInFile(const FileName& file, const Data& data)
{
	FileWriter writer(file);
	writer.write(data);
}

void
R2D::FileSystemHandler
::writeDataInFile(const FileName& file, const jsoncons::ojson& data)
{
	FileWriter writer(file);
	writer.write(data);
}

R2D::FileSystemHandler::Data
R2D::FileSystemHandler
::readDataFromFile(const FileName& file)
{
	FileReader reader(file);
	return reader.read(file);
}

jsoncons::ojson
R2D::FileSystemHandler
::readDataFromFile(const FileName& file, const bool /* dummy = false */)
{
	FileReader reader(file);
	return reader.readJson(file);
}
