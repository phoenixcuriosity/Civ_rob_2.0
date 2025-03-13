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

#include <R2D/src/ErrorLog.h>
#include <R2D/src/ExitFromError.h>
#include <R2D/src/Log.h>

#include <filesystem>

void
FileSystemHandler
::createDirectory(const Path& path)
{
	if (!std::filesystem::create_directory(path))
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_DIR, logS::DATA::ERROR_CREATE_DIR, path);
	}
	else
	{
		LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_DIR, logS::DATA::ERROR_CREATE_DIR, path + " successfully remove");
	}
}

void
FileSystemHandler
::removeFile(const FileName& file)
{
	if (!std::filesystem::remove(file))
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_SAVE_FILE, logS::DATA::ERROR_DELETE_SAVE_FILE, file);
	}
	else
	{
		LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_SAVE_FILE, logS::DATA::ERROR_DELETE_SAVE_FILE, file + " successfully remove");
	}
}

void
FileSystemHandler
::writeDataInFile(const FileName& file, const Data& data)
{
	FileWriter writer(file);
	writer.write(data);
}

void
FileSystemHandler
::writeDataInFile(const FileName& file, const jsoncons::ojson& data)
{
	FileWriter writer(file);
	writer.write(data);
}

FileSystemHandler::Data
FileSystemHandler
::readDataFromFile(const FileName& file)
{
	FileReader reader(file);
	return reader.read(file);
}

jsoncons::ojson
FileSystemHandler
::readDataFromFile(const FileName& file, const bool /* dummy = false */)
{
	FileReader reader(file);
	return reader.readJson(file);
}
