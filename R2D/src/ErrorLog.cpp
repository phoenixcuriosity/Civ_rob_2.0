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

#include "ErrorLog.h"

#include "ResourceManager.h"

using namespace R2D;

std::ofstream ErrorLog::m_log;
std::string ErrorLog::m_lastEvent;
bool ErrorLog::m_isInitialize;
char ErrorLog::m_buffer[BUFFER_LOGEVENT::MAX_CHAR];

void ErrorLog::initializeLog()
{
	if (false == m_isInitialize)
	{
		m_log.open
		(
			ResourceManager::getFile(e_Files::log)->getPath(),
			std::ofstream::out | std::ofstream::trunc
		);

		if (!m_log.is_open())
		{
			exit(EXIT_FAILURE);
		}
		else
		{
			m_isInitialize = true;
		}
	}
}

void ErrorLog::closeLog()
{
	m_log.close();
	m_isInitialize = false;
}


/* ----------------------------------------------------------------------------------- */
/* NAME : logfileconsole															   */
/* ROLE : Transmission du message sur la console et dans le fichier log.txt			   */
/* INPUT : const std::string msg : message											   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
void ErrorLog::logEvent
(
	const std::string& msg
)
{
	if (true == m_isInitialize)
	{
		time_t now{ time(0) };
		struct tm  tstruct {};
		localtime_s(&tstruct, &now);
		strftime(m_buffer, sizeof(m_buffer), "%F %X", &tstruct);

		m_lastEvent = m_buffer + (std::string)"      " + msg;

#ifdef _DEBUG
		std::cout << std::endl << m_lastEvent;
#endif // DEBUG_MODE
		m_log << std::endl << m_lastEvent;
	}
	else
	{
#ifdef _DEBUG
		std::cout << std::endl << "[ERROR]___: Cannot open log file, cannot log event";
#endif // DEBUG_MODE
	}
}