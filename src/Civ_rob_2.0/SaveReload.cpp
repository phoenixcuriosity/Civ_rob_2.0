/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.17
	file version : 1.3

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

#include "SaveReload.h"
#include "civ_lib.h"
#include "IHM.h"


/* *********************************************************
 *				START SaveReload::STATIC				   *
 ********************************************************* */
 
 
/*
* NAME : savemaps
* ROLE : Sauvegardes des sys map.map et map.screen
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Sauvegardes des maps : map.map dans SaveMap.txt
* OUTPUT PARAMETERS : et map.screen dans SaveScreen.txt
* RETURNED VALUE    : void
*/
void SaveReload::savemaps(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_Save Start_");



	std::ofstream saveMaps(sysinfo.file.SaveMaps);
	if (saveMaps)
	{
		for (unsigned int i = 0; i < sysinfo.map.maps.size(); i++)
		{
			for (unsigned int j = 0; j < sysinfo.map.maps[i].size(); j++)
			{
				saveMaps << "nbX= " << (unsigned int)sysinfo.map.maps[i][j].indexX << std::endl;
				saveMaps << "nbY= " << (unsigned int)sysinfo.map.maps[i][j].indexY << std::endl;
				saveMaps << "x= " << sysinfo.map.maps[i][j].tile_x << std::endl;
				saveMaps << "y= " << sysinfo.map.maps[i][j].tile_y << std::endl;
				saveMaps << "stringground= " << sysinfo.map.maps[i][j].tile_stringground << std::endl;
				saveMaps << "ground= " << (unsigned int)sysinfo.map.maps[i][j].tile_ground << std::endl;
				saveMaps << "stringspec= " << sysinfo.map.maps[i][j].tile_stringspec << std::endl;
				saveMaps << "spec= " << (unsigned int)sysinfo.map.maps[i][j].tile_spec << std::endl;
				saveMaps << "appartenance= " << sysinfo.map.maps[i][j].appartenance << std::endl;
				saveMaps << "food= " << (unsigned int)sysinfo.map.maps[i][j].food << std::endl;
				saveMaps << "work= " << (unsigned int)sysinfo.map.maps[i][j].work << std::endl;
				saveMaps << "gold= " << (unsigned int)sysinfo.map.maps[i][j].gold << std::endl << std::endl;
			}
		}
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.SaveMaps);

	IHM::logfileconsole("_Save End_");
}

/*
* NAME : savePlayer
* ROLE : Sauvegarde des joueurs (units et cities)
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Sauvegarde des joueurs (units et cities) dans SavePlayer.txt
* RETURNED VALUE    : void
*/
void SaveReload::savePlayer(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_SavePlayer Start_");
	std::ofstream savePlayer(sysinfo.file.SavePlayer);
	if (savePlayer) {
		savePlayer << "nbPlayer= " << sysinfo.tabplayer.size();
		if (sysinfo.tabplayer.size() != 0)
		{
			for (unsigned int i = 0; i < sysinfo.tabplayer.size(); i++)
			{
				savePlayer << std::endl << std::endl << "player= " + std::to_string(i);
				savePlayer << std::endl << "name= " << sysinfo.tabplayer[i]->GETname();
				savePlayer << std::endl << "nbunitTotal= " << sysinfo.tabplayer[i]->GETtabUnit().size();
				if (sysinfo.tabplayer[i]->GETtabUnit().size() != 0)
				{
					for (unsigned int j = 0; j < sysinfo.tabplayer[i]->GETtabUnit().size(); j++)
					{
						savePlayer << std::endl << std::endl << "\tunit= " << j;
						savePlayer << std::endl << "\tname= " << sysinfo.tabplayer[i]->GETtheUnit(j)->GETname();
						savePlayer << std::endl << "\tx= " << sysinfo.tabplayer[i]->GETtheUnit(j)->GETx();
						savePlayer << std::endl << "\ty= " << sysinfo.tabplayer[i]->GETtheUnit(j)->GETy();
						savePlayer << std::endl << "\tlife= " << sysinfo.tabplayer[i]->GETtheUnit(j)->GETlife();
						savePlayer << std::endl << "\tatq= " << sysinfo.tabplayer[i]->GETtheUnit(j)->GETatq();
						savePlayer << std::endl << "\tdef= " << sysinfo.tabplayer[i]->GETtheUnit(j)->GETdef();
						savePlayer << std::endl << "\tmovement= " << sysinfo.tabplayer[i]->GETtheUnit(j)->GETmovement();
						savePlayer << std::endl << "\tlevel= " << sysinfo.tabplayer[i]->GETtheUnit(j)->GETlevel();
					}
				}
				else
				{
					/* N/A */
				}

				//savePlayer << endl << "nbcitie= " << tabplayer[i]->GETtabcities().size();
				/*
				if (tabplayer[i]->GETtabcities().size() != 0){
					for (int j = 0; j < tabplayer[i]->GETtabcities().size(); j++){



					}
				}
				*/
			}
		}
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.SavePlayer);

	IHM::logfileconsole("_SavePlayer End_");
}

/*
* NAME : reload
* ROLE : Chargement de la partie à patir des fichiers de sauvegarde
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Chargement de la partie
* RETURNED VALUE    : void
*/
void SaveReload::reload(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_Reload Start_");
	sysinfo.var.statescreen = STATEmainmap;

	std::string destroy;
	std::string inttostringtileSize = std::to_string(sysinfo.map.tileSize);

	
	unsigned int nbplayer = 0, nbunit = 0, test = 0, test1 = 0;
	unsigned int var[7];
	std::string name, unitname;
	int initspacename = 200, spacename = 32;


	std::ifstream savePlayer(sysinfo.file.SavePlayer);
	if (savePlayer)
	{
		savePlayer >> destroy;
		savePlayer >> nbplayer;

		if (nbplayer > 0) {
			for (unsigned int i = 0; i < nbplayer; i++)
			{
				savePlayer >> destroy;
				savePlayer >> test;
				if (test == i)
				{
					savePlayer >> destroy;
					savePlayer >> name;
					sysinfo.tabplayer.push_back(new Player(name));
					ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.player,
						shaded, name, { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, 0, initspacename += spacename, nonTransparent, no_angle);

					savePlayer >> destroy;
					savePlayer >> nbunit;
					if (nbunit > 0) {
						for (unsigned int j = 0; j < nbunit; j++)
						{
							savePlayer >> destroy;
							savePlayer >> test1;
							if (test1 == j) {
								savePlayer >> destroy;
								savePlayer >> unitname;

								for (unsigned int k = 0; k < 7; k++)
								{
									savePlayer >> destroy;
									savePlayer >> var[k];
								}
								sysinfo.tabplayer[i]->addUnit(unitname, var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
							}
							else
							{
								/* N/A */
							}
						}
					}
				}
				else
				{
					/* N/A */
				}
			}
		}
		else
		{
			/* N/A */
		}
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.SavePlayer);

	SDL_RenderPresent(sysinfo.screen.renderer);
	IHM::logfileconsole("_Reload End_");
}

/*
* NAME : createSave
* ROLE : Création d'un emplacement de fichier de sauvegarde (courant)
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Création d'un emplacement de fichier de sauvegarde
* RETURNED VALUE    : void
*/
void SaveReload::createSave(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_createSave Start_");
	std::string destroy;

	for (unsigned int i = 0; i < sysinfo.var.save.GETnbSave(); i++)
	{
		if ((i + 1) != sysinfo.var.save.GETtabSave()[i])
		{
			sysinfo.var.save.SETcurrentSave(i + 1);
			sysinfo.var.save.GETtabSave().push_back(sysinfo.var.save.GETcurrentSave());
			break;
		}
		else
		{
			/* N/A */
		}
	}
	if (sysinfo.var.save.GETcurrentSave() == 0)
	{
		sysinfo.var.save.SETcurrentSave(sysinfo.var.save.GETnbSave() + 1);
		sysinfo.var.save.GETtabSave().push_back(sysinfo.var.save.GETcurrentSave());
	}
	else
	{
		/* N/A */
	}


	std::ofstream saveInfo(sysinfo.file.SaveInfo);
	if (saveInfo) 
	{
		saveInfo << "NbSave=";
		saveInfo << std::endl << sysinfo.var.save.GETnbSave() + 1;
		saveInfo << std::endl << "SaveUse=";
		for (unsigned int i = 0; i < sysinfo.var.save.GETnbSave() + 1; i++)
			saveInfo << std::endl << sysinfo.var.save.GETtabSave()[i];
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.SaveInfo);

	std::string save = "save/" + std::to_string(sysinfo.var.save.GETcurrentSave());
	_mkdir(save.c_str());
	sysinfo.var.save.SETnbSave(sysinfo.var.save.GETnbSave() + 1);

	sysinfo.file.SaveMaps = "save/" + std::to_string(sysinfo.var.save.GETcurrentSave()) + "/SaveMaps.txt";
	sysinfo.file.SavePlayer = "save/" + std::to_string(sysinfo.var.save.GETcurrentSave()) + "/SavePlayer.txt";

	IHM::logfileconsole("_createSave Start_");
}

/*
* NAME : removeSave
* ROLE : Supprime une sauvegarde du dossier de sauvegarde
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Supprime une sauvegarde
* RETURNED VALUE    : void
*/
void SaveReload::removeSave(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_removeSave Start_");
	std::string file;
	bool condition = false;

	if (sysinfo.var.save.GETcurrentSave() != 0) 
	{

		for (unsigned int i = 0; i < sysinfo.var.save.GETnbSave(); i++)
		{
			if (sysinfo.var.save.GETcurrentSave() == sysinfo.var.save.GETtabSave()[i]) 
			{
				condition = true;
				break;
			}
			else
			{
				/* N/A */
			}
		}


		if (condition) 
		{

			file = "save/" + std::to_string(sysinfo.var.save.GETcurrentSave()) + "/SaveMaps.txt";
			if (remove(file.c_str()) != 0)
				IHM::logfileconsole("ERREUR: Impossible d'effacer le fichier " + file);
			else
				IHM::logfileconsole("file : " + file + " successfully remove");

			file = "save/" + std::to_string(sysinfo.var.save.GETcurrentSave()) + "/SavePlayer.txt";
			if (remove(file.c_str()) != 0)
				IHM::logfileconsole("ERREUR: Impossible d'effacer le fichier " + file);
			else
				IHM::logfileconsole("file : " + file + " successfully remove");

			file = "save/" + std::to_string(sysinfo.var.save.GETcurrentSave());
			if (_rmdir(file.c_str()) != 0)
				IHM::logfileconsole("ERREUR: Impossible d'effacer le dossier " + file);
			else
				IHM::logfileconsole("directory : " + file + " successfully remove");

			sysinfo.var.save.SETnbSave(sysinfo.var.save.GETnbSave() - 1);
			if (sysinfo.var.save.GETnbSave() == 0)
				sysinfo.var.save.GETtabSave().clear();
			else
				sysinfo.var.save.GETtabSave().erase(sysinfo.var.save.GETtabSave().begin() + sysinfo.var.save.GETcurrentSave() - 1);


			// suppression du pointeur vers la sauvegarde courante
			delete sysinfo.allButton.reload["Save : " + std::to_string(sysinfo.var.save.GETcurrentSave())];
			sysinfo.allButton.reload.erase("Save : " + std::to_string(sysinfo.var.save.GETcurrentSave()));

			

			std::ofstream saveInfo(sysinfo.file.SaveInfo);
			if (saveInfo)
			{
				saveInfo << "NbSave=";
				saveInfo << std::endl << sysinfo.var.save.GETnbSave();
				saveInfo << std::endl << "SaveUse=";
				for (unsigned int i = 0; i < sysinfo.var.save.GETnbSave(); i++)
					saveInfo << std::endl << sysinfo.var.save.GETtabSave()[i];
			}
			else
				IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.SaveInfo);
		}
		else
		{
			/* N/A */
		}
	}
	else
		IHM::logfileconsole("ERREUR: currentSave = 0");

	IHM::logfileconsole("_removeSave End_");
}

/*
* NAME : clearSave
* ROLE : Supprime toutes les sauvegardes du dossier
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Supprime toutes les sauvegardes du dossier
* RETURNED VALUE    : void
*/
void SaveReload::clearSave(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_clearSave Start_");

	for (unsigned int j = 0; j < sysinfo.var.save.GETnbSave(); j++) 
	{
		delete sysinfo.allButton.reload["Save : " + std::to_string(sysinfo.var.save.GETtabSave()[j])];
		sysinfo.allButton.reload.erase("Save : " + std::to_string(sysinfo.var.save.GETtabSave()[j]));
	}

	std::string file;
	for (unsigned int i = 0; i < sysinfo.var.save.GETnbSave(); i++)
	{
		file = "save/" + std::to_string(sysinfo.var.save.GETtabSave()[i]) + "/SaveMaps.txt";
		if (remove(file.c_str()) != 0)
			IHM::logfileconsole("ERREUR: Impossible d'effacer le fichier " + file);
		else
			IHM::logfileconsole("file : " + file + " successfully remove");

		file = "save/" + std::to_string(sysinfo.var.save.GETtabSave()[i]) + "/SavePlayer.txt";
		if (remove(file.c_str()) != 0)
			IHM::logfileconsole("ERREUR: Impossible d'effacer le fichier " + file);
		else
			IHM::logfileconsole("file : " + file + " successfully remove");

		file = "save/" + std::to_string(sysinfo.var.save.GETtabSave()[i]);
		if (_rmdir(file.c_str()) != 0)
			IHM::logfileconsole("ERREUR: Impossible d'effacer le dossier " + file);
		else
			IHM::logfileconsole("directory : " + file + " successfully remove");
	}

	std::ofstream saveInfo(sysinfo.file.SaveInfo);
	if (saveInfo)
	{
		saveInfo << "NbSave=";
		saveInfo << std::endl << "0";
		saveInfo << std::endl << "SaveUse=";
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.SaveInfo);

	sysinfo.var.save.SETnbSave(0);
	sysinfo.var.save.SETcurrentSave(0);
	sysinfo.var.save.GETtabSave().clear();

	IHM::logfileconsole("_clearSave End_");
}


/* *********************************************************
 *				END SaveReload::STATIC					   *
 ********************************************************* */
 
 
 
 /* *********************************************************
  *				START SaveReload::METHODS				    *
  ********************************************************* */

SaveReload::SaveReload(): _nbSave(0), _currentSave(0)
{
}
SaveReload::~SaveReload()
{
}


/* *********************************************************
 *				END SaveReload::METHODS					   *
 ********************************************************* */

/*
*	End Of File : SaveReload.cpp
*/
