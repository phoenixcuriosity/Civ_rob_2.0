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

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>

#include "LogLevel.h"
#include "ErrorLog.h"

namespace R2D
{
	
enum class FileLineFunctionType
{
	show = true,
	dont_show = false
};

class Logger
{
public:

    static Logger& instance()
    {
        static Logger myInstance;
        return myInstance;
    }
    Logger(Logger const&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger const&) = delete;
    Logger& operator=(Logger&&) = delete;

private:
    Logger();
    ~Logger() = default;
   
private:

    std::string GetCurTime(); ///< @return date time as ISO8601 strings("YYYY-MM-DD HH:MM:SS.SSS").
    void log(std::stringstream& ss, const char* format);

    inline const char* castLevel(LogLevelType severity)
    {
        switch (severity)
        {
        case LogLevelType::info:
            return STR_INFO;
        case LogLevelType::debug:
            return STR_DEBUG;
        case LogLevelType::warning:
            return STR_WARN;
        case LogLevelType::error:
            return STR_ERR;
        default:
            throw std::invalid_argument("sévérité de log non implémenté");
        }
    }

public:

    void init(const LogLevelType log_level, const FileLineFunctionType showFILE_LINE_FUNCTION);

public: // template functions
    template <typename... Targs>
    void log(const char* file, const int line, const char* function, LogLevelType severity, const uint64_t& t_simu,
        const std::string& who, const std::string& what, const char* format, Targs... Fargs)
    {
        if (severity < m_loglevel) return;

        if (m_showFILE_LINE_FUNCTION == FileLineFunctionType::show)
        {
            ErrorLog::logEvent(std::format("{}  : File : {}, Line : {}, Function : {}   ::::  {} , {} , {} , {} , {}",
                Logger::GetCurTime(), file, line, function, castLevel(severity), t_simu, who, what, std::vformat(format, std::make_format_args(Fargs...))));
        }
        else
        {
            ErrorLog::logEvent(std::format("{}  :  {} , {} , {} , {} , {}",
                Logger::GetCurTime(), castLevel(severity), t_simu, who, what, std::vformat(format, std::make_format_args(Fargs...))));
        }
    }

private:

    LogLevelType m_loglevel;
    FileLineFunctionType m_showFILE_LINE_FUNCTION;
};
}

#define LOG(severity, time, who, what, ...) R2D::Logger::instance().log(__FILE__, __LINE__, __FUNCTION__, severity, time, who, what, __VA_ARGS__)





#endif // !LOG_H

