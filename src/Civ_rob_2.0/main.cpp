/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.22.0.0
	file version : 1.13

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

#include "civ_lib.h"
#include "IHM.h"
#include "LoadConfig.h"
#include "End.h"

/* *********************************************************
 *						MAIN							   *
 ********************************************************* */

int main(int argc, char* argv[])
{
	/* ---------------------------------------------------------------------- */
	/* 1° : Initialisation sysinfo et initPtr 								  */
	/* ---------------------------------------------------------------------- */

	Sysinfo sysinfo;
	LoadConfig::initPtrSysinfo(sysinfo);

	sysinfo.var.argc = argc;
	sysinfo.var.argv = argv;

	LoadConfig::initStructs(sysinfo);

	/* ---------------------------------------------------------------------- */
	/* 2° : Initialisation random (debug : chrono)							  */
	/* ---------------------------------------------------------------------- */

	srand((unsigned int)time(NULL));

#ifdef _DEBUG_MODE
	auto start(std::chrono::system_clock::now());
	auto end(std::chrono::system_clock::now());
	std::chrono::duration<double> elapsed_seconds(end - start);
#endif // DEBUG_MODE

	/* ---------------------------------------------------------------------- */
	/* 3° : Remplissage sysinfo avec les fichiers inuts						  */
	/* ---------------------------------------------------------------------- */

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
	LoadConfig::computeSize(sysinfo.screen, sysinfo.map);
	LoadConfig::updateStaticValues(sysinfo);
	LoadConfig::initTile(sysinfo.map);
	LoadConfig::loadUnitAndSpec(sysinfo.file.units, sysinfo.var.s_player.tabUnit_Template);

	/* ---------------------------------------------------------------------- */
	/* 4° : Initialisation SDL												  */
	/*    : Initialisation des images, textes et boutons 					  */
	/*    : Mise en place de l'Ecran titre				 					  */
	/*    : Boucle principale : Event SDL et Affichage et countFrame	 	  */
	/* ---------------------------------------------------------------------- */

		/* ---------------------------------------------------------------------- */
		/* 4.1° : Initialisation SDL											  */
		/* ---------------------------------------------------------------------- */
	if (LoadConfig::initSDL(sysinfo.screen, sysinfo.allTextures.font))
	{
		/* ---------------------------------------------------------------------- */
		/* 4.2° : Initialisation des images, textes et boutons					  */
		/* ---------------------------------------------------------------------- */
		try
		{
			LoadConfig::calculImage(sysinfo);
		}
		catch (std::string const& chaine)
		{
			End::exitError(chaine);
		}
		
#ifdef _DEBUG_MODE
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		LoadConfig::logfileconsole
		("[INFO]___: temps d'execution de l'initialisation : "
			+ std::to_string(elapsed_seconds.count()));
#endif // DEBUG_MODE

		/* ---------------------------------------------------------------------- */
		/* 4.3° : Mise en place de l'Ecran titre								  */
		/* ---------------------------------------------------------------------- */

		sysinfo.var.cinState = CinState_Type::cinTitleScreen;

		IHM::titleScreen(sysinfo);

		/* ---------------------------------------------------------------------- */
		/* 4.4° : Boucle principale : Event SDL et Affichage et countFrame		  */
		/* ---------------------------------------------------------------------- */

		while (sysinfo.var.continuer)
		{
			/* ---------------------------------------------------------------------- */
			/* 4.4.1° : Event SDL													  */
			/* ---------------------------------------------------------------------- */

			KeyboardMouse::checkCaseSDL(sysinfo);

			/* ---------------------------------------------------------------------- */
			/* 4.4.2° : countFrame													  */
			/* ---------------------------------------------------------------------- */

			IHM::countFrame(sysinfo.screen);

			/* ---------------------------------------------------------------------- */
			/* 4.4.3° : Affichage													  */
			/* ---------------------------------------------------------------------- */

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

	/* ---------------------------------------------------------------------- */
	/* 5° : Fin du programme : destruction sysinfo							  */
	/* ---------------------------------------------------------------------- */

	End::deleteAll(sysinfo);

	return EXIT_SUCCESS;
}

/*
*	End Of File : main.cpp
*/
