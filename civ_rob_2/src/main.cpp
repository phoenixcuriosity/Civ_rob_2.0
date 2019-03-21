/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.15
	file version : 1.2

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

#include "IHM.h"

/* *********************************************************
						MAIN
  ********************************************************* */

int main(int argc, char* argv[])
{
	Sysinfo sysinfo;

	srand((unsigned int)time(NULL));

	clock_t t1, t2; // calcul du temps pour calculimage
	t1 = clock();

	IHM::initFile(sysinfo.file);
	IHM::initTile(sysinfo.map);

	IHM::logfileconsole("________PROGRAMME START________");

	if (IHM::initSDL(sysinfo.screen.window, sysinfo.screen.renderer, sysinfo.allTextures.font))
	{
		Unit::loadUnitAndSpec(sysinfo);
		IHM::calculImage(sysinfo);
		
		t2 = clock();
		IHM::logfileconsole("temps d'execution de l'initialisation : " + std::to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC));

		IHM::titleScreen(sysinfo);

		int SDL_EnableUNICODE(1); // on azerty

		while (sysinfo.var.continuer)
		{
			IHM::eventSDL(sysinfo);

			IHM::countFrame(sysinfo.screen);

			IHM::alwaysrender(sysinfo);
		}	
	}
	IHM::deleteAll(sysinfo);

	IHM::logfileconsole("SDL_Quit Success");
	IHM::logfileconsole("________PROGRAMME FINISH________");
	return 0;
}

/*
*	End Of File : main.cpp
*/
