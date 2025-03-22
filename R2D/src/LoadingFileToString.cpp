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

#include "LoadingFileToString.h"

#include "Log.h"
#include "LogSentences.h"

#include <filesystem>

using namespace R2D;

std::string FileTools::loadFileToString(const std::string& path)
{
	std::error_code ec;
	const uintmax_t length = std::filesystem::file_size(path, ec);
	if (ec)
	{
		LOG(R2D::LogLevelType::error, 0, logR::WHO::RESSOURCES_MANAGER, logR::WHAT::FILE, logR::DATA::ERROR_SIZE_FILE, ec.message());
	}
	std::string buffer(length, '\0');
	std::ifstream stream(path, std::ios::in);
	stream.read(buffer.data(), length);
	stream.close();

	const std::string text{ std::string(buffer.c_str(), strlen(buffer.c_str())) };
	if (text.empty())
	{
		LOG(R2D::LogLevelType::error, 0, logR::WHO::RESSOURCES_MANAGER, logR::WHAT::FILE, logR::DATA::ERROR_EMPTY_FILE, path);
	}

	return text;
}