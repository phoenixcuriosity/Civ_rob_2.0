/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.2.0
	file version : 1.17

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

#include "MainGame.h"


#include <fstream>
#include <iostream>
#include <filesystem>

 /* *********************************************************
  *						MAIN							   *
  ********************************************************* */

int main(int argc, char* argv[])
{
	MainGame mainGame;
	mainGame.GETvar().argc = argc;
	mainGame.GETvar().argv = argv;

	/*

	for (auto& p : std::filesystem::recursive_directory_iterator("bin"))
		std::cout << p.path() << '\n';

		*/
	
	mainGame.runGameLoop();

	mainGame.destroy();
	

	return EXIT_SUCCESS;
}

/*
*	End Of File : main.cpp
*/
