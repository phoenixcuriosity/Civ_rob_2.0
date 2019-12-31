/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.18
	file version : 1.9

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
#include "LoadConfig.h"
#include "End.h"

/* *********************************************************
 *						MAIN							   *
 ********************************************************* */

int main(int argc, char* argv[])
{
	Sysinfo sysinfo;
	LoadConfig::initPtrSysinfo(sysinfo);

	sysinfo.var.argc = argc;
	sysinfo.var.argv = argv;

	LoadConfig::initStructs(sysinfo);

	srand((unsigned int)time(NULL));

	auto start(std::chrono::system_clock::now());
	auto end(std::chrono::system_clock::now());
	std::chrono::duration<double> elapsed_seconds(end - start);

	LoadConfig::initFile(sysinfo.file);

	LoadConfig::logfileconsole("[INFO]___: ________PROGRAMME START________");

	try
	{
		LoadConfig::initMain(sysinfo);
	}
	catch (std::string const& chaine)
	{
		End::exitError(chaine);
	}

	LoadConfig::initTile(sysinfo.map);

	if (LoadConfig::initSDL(sysinfo.screen, sysinfo.allTextures.font))
	{
		Unit::loadUnitAndSpec(sysinfo);

		try
		{
			LoadConfig::calculImage(sysinfo);
		}
		catch (std::string const& chaine)
		{
			End::exitError(chaine);
		}
		
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		LoadConfig::logfileconsole("[INFO]___: temps d'execution de l'initialisation : " + std::to_string(elapsed_seconds.count()));

		sysinfo.var.cinState = cinTitleScreen;

		IHM::titleScreen(sysinfo);

		while (sysinfo.var.continuer)
		{
			KeyboardMouse::eventSDL(sysinfo);

			IHM::countFrame(sysinfo.screen);

			try 
			{
				IHM::alwaysrender(sysinfo);
			}
			catch (const std::string& msg)
			{
				End::exitError(msg);
			}
			
		}	
	}
	else
	{
		/* N/A */
	}
	End::deleteAll(sysinfo);

	return EXIT_SUCCESS;
}

/*
*	End Of File : main.cpp
*/
