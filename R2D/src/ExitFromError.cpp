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

#include "ExitFromError.h"

#include "Log.h"
#include "../../Dependencies/SDL/SDL.h"

using namespace R2D;


void ExitFromError::deleteAll()
{
	LOG(R2D::LogLevelType::info, 0, "[CIV_ROB]", "[START]","*********_________ DeleteAll _________*********");



	/* *********************************************************
	 *				 START delete SDL						   *
	 ********************************************************* */


	SDL_Quit();

	/* *********************************************************
	 *				 END delete SDL							   *
	 ********************************************************* */

	 /* ### Don't put code below here ### */


	LOG(R2D::LogLevelType::info, 0, "[CIV_ROB]", "[N/A]", "SDL_Quit");
	LOG(R2D::LogLevelType::info, 0, "[CIV_ROB]", "[n/A]", "________PROGRAMME FINISH________");
	ErrorLog::closeLog();
}

void ExitFromError::exitFromError
(
	const std::string& errorMsg
)
{
	LOG(R2D::LogLevelType::error, 0, "[CIV_ROB]", "[CRASH]", "{}", errorMsg);
	deleteAll();
	LOG(R2D::LogLevelType::error, 0, "[CIV_ROB]", "[CRASH]", "Last msg before exitError : {}", errorMsg);
	ErrorLog::closeLog();
	exit(EXIT_FAILURE);
}
