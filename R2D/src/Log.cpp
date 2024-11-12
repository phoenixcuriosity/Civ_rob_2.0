/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)

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

#include "Log.h"

#include "ResourceManager.h"

#include <ctime>
#include <iomanip>
#include <filesystem>
#include <format>
#include <utility>

using namespace R2D;

Logger::Logger()
{
}

void Logger::init(const LogLevelType log_level, const FileLineFunctionType showFILE_LINE_FUNCTION)
{
	m_loglevel = log_level;
	m_showFILE_LINE_FUNCTION = showFILE_LINE_FUNCTION;
}

std::string Logger::GetCurTime()
{
	// Get the current time point
	auto now = std::chrono::system_clock::now();

	// Convert to time_t to get calendar time
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
	std::tm timeInfo;

	// Use localtime_s instead of localtime
	localtime_s(&timeInfo, &currentTime);

	// Format date and time
	std::ostringstream oss;
	oss << std::put_time(&timeInfo, "%Y/%m/%d %H:%M:%S");

	// Get milliseconds
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

	// Append milliseconds to the formatted string
	oss << "::" << std::setfill('0') << std::setw(3) << milliseconds.count();

	return oss.str();
}