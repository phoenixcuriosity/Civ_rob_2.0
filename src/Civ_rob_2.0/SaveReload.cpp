/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.20.0.3
	file version : 1.6

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
#include "LoadConfig.h"
#include "Player.h"


/* *********************************************************
 *				START SaveReload::STATIC				   *
 ********************************************************* */
 

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : savemaps																					    	  */
/* ROLE : Sauvegardes des sys map.map et map.screen														      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void																	    			  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::saveMaps
(
	Sysinfo& sysinfo
)
{
	std::ofstream saveMaps(sysinfo.file.saveMaps);
	if (saveMaps)
	{
		for (unsigned int i = 0; i < sysinfo.map.maps.size(); i++)
		{
			for (unsigned int j = 0; j < sysinfo.map.maps[i].size(); j++)
			{
				saveMaps << (unsigned int)sysinfo.map.maps[i][j].indexX << std::endl;
				saveMaps << (unsigned int)sysinfo.map.maps[i][j].indexY << std::endl;
				saveMaps << sysinfo.map.maps[i][j].tile_x << std::endl;
				saveMaps << sysinfo.map.maps[i][j].tile_y << std::endl;
				saveMaps << sysinfo.map.maps[i][j].tile_stringground << std::endl;
				saveMaps << (unsigned int)sysinfo.map.maps[i][j].tile_ground << std::endl;
				saveMaps << sysinfo.map.maps[i][j].tile_stringspec << std::endl;
				saveMaps << (unsigned int)sysinfo.map.maps[i][j].tile_spec << std::endl;
				saveMaps << sysinfo.map.maps[i][j].appartenance << std::endl;
				saveMaps << (unsigned int)sysinfo.map.maps[i][j].food << std::endl;
				saveMaps << (unsigned int)sysinfo.map.maps[i][j].work << std::endl;
				saveMaps << (unsigned int)sysinfo.map.maps[i][j].gold << std::endl << std::endl;
			}
		}
	}
	else
		LoadConfig::logfileconsole("[ERROR]___: Impossible d'ouvrir le fichier " + sysinfo.file.saveMaps);
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : loadMaps																					    	  */
/* ROLE : Chargement des sys map.map et map.screen														      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void								    												  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::loadMaps
(
	Sysinfo& sysinfo
)
{
	std::string input(EMPTY_STRING);

	std::ifstream saveMaps(sysinfo.file.saveMaps);
	if (saveMaps)
	{
		for (unsigned int i = 0; i < sysinfo.map.maps.size(); i++)
		{
			for (unsigned int j = 0; j < sysinfo.map.maps[i].size(); j++)
			{
				saveMaps >> input;
				sysinfo.map.maps[i][j].indexX = (Uint8)std::stoul(input);

				saveMaps >> input;
				sysinfo.map.maps[i][j].indexY = (Uint8)std::stoul(input);

				saveMaps >> input;
				sysinfo.map.maps[i][j].tile_x = std::stoul(input);

				saveMaps >> input;
				sysinfo.map.maps[i][j].tile_y = std::stoul(input);

				saveMaps >> sysinfo.map.maps[i][j].tile_stringground;

				saveMaps >> input;
				sysinfo.map.maps[i][j].tile_ground = (Ground_Type)std::stoul(input);

				saveMaps >> sysinfo.map.maps[i][j].tile_stringspec;

				saveMaps >> input;
				sysinfo.map.maps[i][j].tile_spec = (GroundSpec_Type)std::stoul(input);

				saveMaps >> input;
				sysinfo.map.maps[i][j].appartenance = std::stoi(input);

				saveMaps >> input;
				sysinfo.map.maps[i][j].food = (int8_t)std::stoi(input);

				saveMaps >> input;
				sysinfo.map.maps[i][j].work = (int8_t)std::stoi(input);

				saveMaps >> input;
				sysinfo.map.maps[i][j].gold = (int8_t)std::stoi(input);
			}
		}
	}
	else
		LoadConfig::logfileconsole("[ERROR]___: Impossible d'ouvrir le fichier " + sysinfo.file.saveMaps);

	LoadConfig::logfileconsole("[INFO]___: Save End");
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : savePlayer																				    	  */
/* ROLE : Sauvegarde des joueurs (units et cities) dans SavePlayer.txt									      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void 																				  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::savePlayer
(
	Sysinfo& sysinfo
)
{
	std::ofstream savePlayer(sysinfo.file.savePlayers);
	if (savePlayer)
	{
		savePlayer << "nbPlayer= " << sysinfo.tabplayer.size();
		if (sysinfo.tabplayer.size() != 0)
		{
			for (unsigned int i(0); i < sysinfo.tabplayer.size(); i++)
			{
				savePlayer << std::endl << std::endl << "player= " + std::to_string(i);
				savePlayer << std::endl << "name= " << sysinfo.tabplayer[i]->GETname();
				savePlayer << std::endl << "nbunitTotal= " << sysinfo.tabplayer[i]->GETtabUnit().size();
				if (sysinfo.tabplayer[i]->GETtabUnit().size() != 0)
				{
					for (unsigned int j(0); j < sysinfo.tabplayer[i]->GETtabUnit().size(); j++)
					{
						savePlayer << std::endl << std::endl << "\tunit= " << j;
						savePlayer << std::endl << "\tname= " << sysinfo.tabplayer[i]->GETtheUnit(j)->GETname();
						savePlayer << std::endl << "\tx= " << sysinfo.tabplayer[i]->GETtheUnit(j)->GETx();
						savePlayer << std::endl << "\ty= " << sysinfo.tabplayer[i]->GETtheUnit(j)->GETy();
						savePlayer << std::endl << "\tmovementType= " << (unsigned int)sysinfo.tabplayer[i]->GETtheUnit(j)->GETmovementType();
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
		LoadConfig::logfileconsole("[ERROR]___: Impossible d'ouvrir le fichier " + sysinfo.file.savePlayers);

}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : loadPlayer																				    	  */
/* ROLE : Chargement des joueurs (units et cities) dans SavePlayer.txt									      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::loadPlayer
(
	Sysinfo& sysinfo
)
{
	sysinfo.var.statescreen = State_Type::STATEmainMap;

	std::string		destroy(EMPTY_STRING),
					name(EMPTY_STRING),
					unitname(EMPTY_STRING);

	unsigned int	nbplayer(0),
					nbunit(0),
					test(0),
					test1(0);

	unsigned int var[8];

	int initspacename(200), spacename(32);

	std::ifstream savePlayer(sysinfo.file.savePlayers);
	if (savePlayer)
	{
		savePlayer >> destroy;
		savePlayer >> nbplayer;

		if (nbplayer > 0)
		{
			for (unsigned int i(0); i < nbplayer; i++)
			{
				savePlayer >> destroy;
				savePlayer >> test;
				if (test == i)
				{
					savePlayer >> destroy;
					savePlayer >> name;
					sysinfo.tabplayer.push_back(new Player(name));
					ButtonTexte::createButtonTexte(sysinfo.screen.renderer,
						sysinfo.allTextures.font,
						sysinfo.var.statescreen,
						sysinfo.var.select,
						sysinfo.allButton.player,
						Texte_Type::shaded,
						name,
						{ 255, 64, 0, 255 },
						{ 64, 64, 64, 255 },
						24,
						0,
						initspacename += spacename,
						nonTransparent,
						no_angle);

					savePlayer >> destroy;
					savePlayer >> nbunit;
					if (nbunit > 0)
					{
						for (unsigned int j(0); j < nbunit; j++)
						{
							savePlayer >> destroy;
							savePlayer >> test1;
							if (test1 == j)
							{
								savePlayer >> destroy;
								savePlayer >> unitname;

								for (unsigned int k(0); k < 7; k++)
								{
									savePlayer >> destroy;
									savePlayer >> var[k];
								}
								sysinfo.tabplayer[i]->addUnit(unitname,
									var[0],
									var[1],
									(Unit_Movement_Type)var[2],
									var[3],
									var[4],
									var[5],
									var[6],
									var[7] );
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
		LoadConfig::logfileconsole("[ERROR]___: Impossible d'ouvrir le fichier " + sysinfo.file.savePlayers);
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : reload																					    	  */
/* ROLE : Chargement de la partie à patir des fichiers de sauvegarde									      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::reload
(
	Sysinfo& sysinfo
)
{
	LoadConfig::logfileconsole("[INFO]___: Reload Start");

	loadMaps(sysinfo);
	loadPlayer(sysinfo);

	SDL_RenderPresent(sysinfo.screen.renderer);
	LoadConfig::logfileconsole("[INFO]___: Reload End");
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : createSave																				    	  */
/* ROLE : Création d'un emplacement de fichier de sauvegarde (courant)									      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::createSave
(
	Sysinfo& sysinfo
)
{
	LoadConfig::logfileconsole("[INFO]___: createSave Start");
	std::string destroy;

	for (unsigned int i(0); i < sysinfo.var.save.GETnbSave(); i++)
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


	std::ofstream saveInfo(sysinfo.file.saveInfo);
	if (saveInfo) 
	{
		saveInfo << "NbSave=";
		saveInfo << std::endl << sysinfo.var.save.GETnbSave() + 1;
		saveInfo << std::endl << "SaveUse=";
		for (unsigned int i(0); i < sysinfo.var.save.GETnbSave() + 1; i++)
			saveInfo << std::endl << sysinfo.var.save.GETtabSave()[i];
	}
	else
		LoadConfig::logfileconsole("[ERROR]___: Impossible d'ouvrir le fichier " + sysinfo.file.saveInfo);

	std::string save = "save/" + std::to_string(sysinfo.var.save.GETcurrentSave());
	_mkdir(save.c_str());
	sysinfo.var.save.SETnbSave(sysinfo.var.save.GETnbSave() + 1);

	sysinfo.file.saveMaps = "save/" + std::to_string(sysinfo.var.save.GETcurrentSave()) + "/saveMaps.txt";
	sysinfo.file.savePlayers = "save/" + std::to_string(sysinfo.var.save.GETcurrentSave()) + "/savePlayer.txt";

	LoadConfig::logfileconsole("[INFO]___: createSave End");
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : removeSave																				    	  */
/* ROLE : Supprime une sauvegarde du dossier de sauvegarde												      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::removeSave
(
	Sysinfo& sysinfo
)
{
	LoadConfig::logfileconsole("[INFO]___: removeSave Start");
	std::string file(EMPTY_STRING);
	bool condition(false);

	if (sysinfo.var.save.GETcurrentSave() != 0) 
	{

		for (unsigned int i(0); i < sysinfo.var.save.GETnbSave(); i++)
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

			file = "save/" + std::to_string(sysinfo.var.save.GETcurrentSave()) + "/saveMaps.txt";
			if (remove(file.c_str()) != 0)
				LoadConfig::logfileconsole("[ERROR]___: Impossible d'effacer le fichier " + file);
			else
				LoadConfig::logfileconsole("[INFO]___: file : " + file + " successfully remove");

			file = "save/" + std::to_string(sysinfo.var.save.GETcurrentSave()) + "/savePlayer.txt";
			if (remove(file.c_str()) != 0)
				LoadConfig::logfileconsole("[ERROR]___: Impossible d'effacer le fichier " + file);
			else
				LoadConfig::logfileconsole("[INFO]___: file : " + file + " successfully remove");

			file = "save/" + std::to_string(sysinfo.var.save.GETcurrentSave());
			if (_rmdir(file.c_str()) != 0)
				LoadConfig::logfileconsole("[ERROR]___: Impossible d'effacer le dossier " + file);
			else
				LoadConfig::logfileconsole("[INFO]___: directory : " + file + " successfully remove");

			sysinfo.var.save.SETnbSave(sysinfo.var.save.GETnbSave() - 1);
			if (sysinfo.var.save.GETnbSave() == 0)
				sysinfo.var.save.GETtabSave().clear();
			else
				sysinfo.var.save.GETtabSave().erase
					(sysinfo.var.save.GETtabSave().begin() + sysinfo.var.save.GETcurrentSave() - 1);


			// suppression du pointeur vers la sauvegarde courante
			delete sysinfo.allButton.reload["Save : " + std::to_string(sysinfo.var.save.GETcurrentSave())];
			sysinfo.allButton.reload.erase("Save : " + std::to_string(sysinfo.var.save.GETcurrentSave()));

			

			std::ofstream saveInfo(sysinfo.file.saveInfo);
			if (saveInfo)
			{
				saveInfo << "NbSave=";
				saveInfo << std::endl << sysinfo.var.save.GETnbSave();
				saveInfo << std::endl << "SaveUse=";
				for (unsigned int i(0); i < sysinfo.var.save.GETnbSave(); i++)
					saveInfo << std::endl << sysinfo.var.save.GETtabSave()[i];
			}
			else
				LoadConfig::logfileconsole("[ERROR]___: Impossible d'ouvrir le fichier " + sysinfo.file.saveInfo);
		}
		else
		{
			/* N/A */
		}
	}
	else
		LoadConfig::logfileconsole("[ERROR]___: currentSave = 0");

	LoadConfig::logfileconsole("[INFO]___: removeSave End");
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : clearSave																					    	  */
/* ROLE : Supprime toutes les sauvegardes du dossier													      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void SaveReload::clearSave
(
	Sysinfo& sysinfo
)
{
	LoadConfig::logfileconsole("[INFO]___: clearSave Start");

	for (unsigned int j(0); j < sysinfo.var.save.GETnbSave(); j++) 
	{
		delete sysinfo.allButton.reload["Save : " + std::to_string(sysinfo.var.save.GETtabSave()[j])];
		sysinfo.allButton.reload.erase("Save : " + std::to_string(sysinfo.var.save.GETtabSave()[j]));
	}

	std::string file(EMPTY_STRING);
	for (unsigned int i(0); i < sysinfo.var.save.GETnbSave(); i++)
	{
		file = "save/" + std::to_string(sysinfo.var.save.GETtabSave()[i]) + "/saveMaps.txt";
		if (remove(file.c_str()) != 0)
			LoadConfig::logfileconsole("[ERROR]___: Impossible d'effacer le fichier " + file);
		else
			LoadConfig::logfileconsole("[INFO]___: file : " + file + " successfully remove");

		file = "save/" + std::to_string(sysinfo.var.save.GETtabSave()[i]) + "/savePlayer.txt";
		if (remove(file.c_str()) != 0)
			LoadConfig::logfileconsole("[ERROR]___: Impossible d'effacer le fichier " + file);
		else
			LoadConfig::logfileconsole("[INFO]___: file : " + file + " successfully remove");

		file = "save/" + std::to_string(sysinfo.var.save.GETtabSave()[i]);
		if (_rmdir(file.c_str()) != 0)
			LoadConfig::logfileconsole("[ERROR]___: Impossible d'effacer le dossier " + file);
		else
			LoadConfig::logfileconsole("[INFO]___: directory : " + file + " successfully remove");
	}

	std::ofstream saveInfo(sysinfo.file.saveInfo);
	if (saveInfo)
	{
		saveInfo << "NbSave=";
		saveInfo << std::endl << "0";
		saveInfo << std::endl << "SaveUse=";
	}
	else
		LoadConfig::logfileconsole("[ERROR]___: Impossible d'ouvrir le fichier " + sysinfo.file.saveInfo);

	sysinfo.var.save.SETnbSave(0);
	sysinfo.var.save.SETcurrentSave(0);
	sysinfo.var.save.GETtabSave().clear();

	LoadConfig::logfileconsole("[INFO]___: clearSave End");
}


/* *********************************************************
 *				END SaveReload::STATIC					   *
 ********************************************************* */
 
 
 
 /* *********************************************************
  *				START SaveReload::METHODS				    *
  ********************************************************* */


/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : SaveReload																				    	  */
/* ROLE : Constructeur par défaut																		      */
/* INPUT : void																							      */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
SaveReload::SaveReload(): _nbSave(0), _currentSave(0)
{
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : ~SaveReload																				    	  */
/* ROLE : Destructeur par défaut																		      */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
SaveReload::~SaveReload()
{
}


/* *********************************************************
 *				END SaveReload::METHODS					   *
 ********************************************************* */

/*
*	End Of File : SaveReload.cpp
*/
