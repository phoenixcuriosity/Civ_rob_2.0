/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.17
	file version : 1.1

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

#include "End.h"
#include "IHM.h"
#include "LoadConfig.h"


/* *********************************************************
 *					Variable Globale					   *
 ********************************************************* */

static std::ofstream* logger;
static Sysinfo* ptrSysinfo;

void End::initPtrSysinfoLogger(Sysinfo& sysinfo, std::ofstream& ptrlogger)
{
	ptrSysinfo = &sysinfo;
	logger = &ptrlogger;
}


/*
* NAME : exitError
* ROLE : Enregistre l'erreur survenue et termine le programme de façon sécurisée
* INPUT  PARAMETERS : const std::string msg : message de l'erreur
* OUTPUT PARAMETERS : EXIT_FAILURE
* RETURNED VALUE    : void
*/
void End::exitError(const std::string msg)
{
	LoadConfig::logfileconsole("[ERROR]___: " + msg);
	deleteAll(*ptrSysinfo);
	LoadConfig::logfileconsole("[ERROR]___: Last msg before exitError : " + msg);
	exit(EXIT_FAILURE);
}


/*
 * NAME : deleteAll
 * ROLE : Destruction des allocations dynamique du programme
 * ROLE : Destruction de la fenetre et du Renderer de la SDL
 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
 * OUTPUT PARAMETERS : Destruction des allocations dynamique du programme
 * RETURNED VALUE    : void
 */
void End::deleteAll(Sysinfo& sysinfo)
{
	LoadConfig::logfileconsole("[INFO]___: [START] *********_________ DeleteAll _________*********");

	/* *********************************************************
	 *					START delete font*					   *
	 ********************************************************* */

	for (unsigned int i(1); i < MAX_FONT; i++)
	{
		if (sysinfo.allTextures.font[i] != nullptr)
		{
			TTF_CloseFont(sysinfo.allTextures.font[i]);
		}
		else
		{
			/* N/A */
		}
	}

	/* *********************************************************
	 *					END delete font*					   *
	 ********************************************************* */


	/* *********************************************************
	 *				 START delete Texture	   		 		   *
	 ********************************************************* */

	deleteTexture(sysinfo.allTextures.ground, "Texture");
	deleteTexture(sysinfo.allTextures.groundSpec, "Texture");
	deleteTexture(sysinfo.allTextures.barLife, "Texture");
	deleteTexture(sysinfo.allTextures.colorapp, "Texture");
	deleteTexture(sysinfo.allTextures.colorapptile, "Texture");

	deleteTexture(sysinfo.allTextures.titleScreen, "Texture");
	deleteTexture(sysinfo.allTextures.unit, "Texture");
	deleteTexture(sysinfo.allTextures.citieMap, "Texture");

	/* *********************************************************
	 *				 END delete Texture*					   *
	 ********************************************************* */


	 /* *********************************************************
	  *				 START delete Texte*					   *
	  ********************************************************* */

	deleteTexte(sysinfo.allTextes.number, "Texte");
	deleteTexte(sysinfo.allTextes.titleScreen, "Texte");
	deleteTexte(sysinfo.allTextes.newGame, "Texte");
	deleteTexte(sysinfo.allTextes.mainMap, "Texte");
	deleteTexte(sysinfo.allTextes.citieMap, "Texte");

	/* *********************************************************
	 *					END delete Texte*					   *
	 ********************************************************* */


	 /* *********************************************************
	  *				 START delete Button*					   *
	  ********************************************************* */

	deleteButtonTexte(sysinfo.allButton.titleScreen, "Button");
	deleteButtonTexte(sysinfo.allButton.player, "Button");
	deleteButtonTexte(sysinfo.allButton.reload, "Button");
	deleteButtonTexte(sysinfo.allButton.mainMap, "Button");
	deleteButtonTexte(sysinfo.allButton.citieMap, "Button");

	/* *********************************************************
	 *				 END delete Button*						   *
	 ********************************************************* */

	deletePlayer(sysinfo.tabplayer, "player");

	/* *********************************************************
	 *				 START delete SDL						   *
	 ********************************************************* */

	if (sysinfo.screen.renderer != nullptr)
	{
		SDL_DestroyRenderer(sysinfo.screen.renderer);
		sysinfo.screen.renderer = nullptr;
	}
	else
	{
		/* N/A */
	}

	if (sysinfo.screen.window != nullptr)
	{
		SDL_DestroyWindow(sysinfo.screen.window);
		sysinfo.screen.window = nullptr;
	}
	else
	{
		/* N/A */
	}

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	/* *********************************************************
	 *				 END delete SDL							   *
	 ********************************************************* */

	 /* ### Don't put code below here ### */

	LoadConfig::logfileconsole("[INFO]___: [END] : *********_________ DeleteAll _________*********");

	LoadConfig::logfileconsole("[INFO]___: SDL_Quit Success");
	LoadConfig::logfileconsole("[INFO]___:________PROGRAMME FINISH________");

	logger->close();
}



void End::deleteTexture(std::unordered_map<std::string, Texture*>& unmap, const std::string& name)
{
	for (const auto& n : unmap)
	{
		if (n.second != nullptr)
		{
			LoadConfig::logfileconsole("[INFO]___: Delete " + name + " name = " + n.second->GETname() + " Success");
			delete n.second;
		}
		else
		{
			/* N/A */
		}
	}
}

void End::deleteTexte(std::unordered_map<std::string, Texte*>& unmap, const std::string& name)
{
	for (const auto& n : unmap)
	{
		if (n.second != nullptr)
		{
			LoadConfig::logfileconsole("[INFO]___: Delete " + name + " name = " + n.second->GETname() + " Success");
			delete n.second;
		}
		else
		{
			/* N/A */
		}
	}
}

void End::deleteButtonTexte(std::unordered_map<std::string, ButtonTexte*>& unmap, const std::string& name)
{
	for (const auto& n : unmap)
	{
		if (n.second != nullptr)
		{
			LoadConfig::logfileconsole("[INFO]___: Delete " + name + " name = " + n.second->GETname() + " Success");
			delete n.second;
		}
		else
		{
			/* N/A */
		}
	}
}

void End::deletePlayer(std::vector<Player*>& vect, const std::string& name)
{
	for (unsigned int i(0); i < vect.size(); i++)
	{
		if (vect[i] != nullptr)
		{
			LoadConfig::logfileconsole("[INFO]___: Delete " + name + " name = " + vect[i]->GETname() + " Success");
			delete vect[i];
		}
		else
		{
			/* N/A */
		}
	}
}

/*
*	End Of File : End.cpp
*/