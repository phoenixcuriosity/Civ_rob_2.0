/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.0.0
	file version : 1.20

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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */


#include "LIB.h"

#include "App.h"

#include <R2D/src/ResourceManager.h>
#include <R2D/src/ErrorLog.h>
#include <R2D/src/log.h>

 /* *********************************************************
  *						MAIN							   *
  ********************************************************* */

int main(int /* argc */, char* /* argv */[])
{
	srand((unsigned int)time(NULL));


	/* Set location of logging file */
	R2D::ResourceManager::initializeFilePath(R2D::e_Files::log, "bin/log/log.txt");
	R2D::ErrorLog::initializeLog();
	R2D::Logger::instance().init(R2D::LogLevelType::info, R2D::FileLineFunctionType::dont_show);

	App app{};
	app.run();


	LOG(R2D::LogLevelType::info, 0, "[CIV_ROB]", "[n/A]", "________PROGRAMME FINISH________");

	return EXIT_SUCCESS;
}

/*
*	End Of File : main.cpp
*/
