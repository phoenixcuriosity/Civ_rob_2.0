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

#ifndef ErrorLog_H
#define ErrorLog_H

#include <iostream>
#include <fstream>

namespace R2D
{
	namespace BUFFER_LOGEVENT
	{
		const unsigned int MAX_CHAR = 80;
	}

	class ErrorLog
	{
	public:

		static void initializeLog();

		static void closeLog();

		static void logEvent
		(
			const std::string& evt
		);

	private:

		static std::ofstream m_log;
		static char m_buffer[BUFFER_LOGEVENT::MAX_CHAR];
		static std::string m_lastEvent;
		static bool m_isInitialize;
	};

}


#endif // !ErrorLog_H

