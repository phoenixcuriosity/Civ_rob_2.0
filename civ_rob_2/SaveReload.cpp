/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.12

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


///////////////////////////// SaveReload //////////////////////////////
/* SaveReload :: STATIC */
void SaveReload::savemaps(sysinfo& information) {
	IHM::logfileconsole("_Save Start_");

	std::ofstream saveScreen(information.file.SaveScreen);
	if (saveScreen) {
		for (unsigned int i = 0; i < information.maps.screen.size(); i++) {
			saveScreen << "nb= " << information.maps.screen[i].tile_nb << std::endl;
			saveScreen << "x= " << information.maps.screen[i].tile_x << std::endl;
			saveScreen << "y= " << information.maps.screen[i].tile_y << std::endl;
			saveScreen << "stringground= " << information.maps.screen[i].tile_stringground << std::endl;
			saveScreen << "ground= " << information.maps.screen[i].tile_ground << std::endl;
			saveScreen << "stringspec= " << information.maps.screen[i].tile_stringspec << std::endl;
			saveScreen << "spec= " << information.maps.screen[i].tile_spec << std::endl;
			saveScreen << "appartenance= " << information.maps.screen[i].appartenance << std::endl;
			saveScreen << "food= " << information.maps.screen[i].food << std::endl;
			saveScreen << "work= " << information.maps.screen[i].work << std::endl;
			saveScreen << "gold= " << information.maps.screen[i].gold << std::endl << std::endl;
		}
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SaveScreen);


	std::ofstream saveMaps(information.file.SaveMaps);
	if (saveMaps) {
		for (unsigned int i = 0; i < information.maps.maps.size(); i++) {
			saveMaps << "nb= " << information.maps.maps[i].tile_nb << std::endl;
			saveMaps << "x= " << information.maps.maps[i].tile_x << std::endl;
			saveMaps << "y= " << information.maps.maps[i].tile_y << std::endl;
			saveMaps << "stringground= " << information.maps.maps[i].tile_stringground << std::endl;
			saveMaps << "ground= " << information.maps.maps[i].tile_ground << std::endl;
			saveMaps << "stringspec= " << information.maps.maps[i].tile_stringspec << std::endl;
			saveMaps << "spec= " << information.maps.maps[i].tile_spec << std::endl;
			saveMaps << "appartenance= " << information.maps.maps[i].appartenance << std::endl;
			saveMaps << "food= " << information.maps.maps[i].food << std::endl;
			saveMaps << "work= " << information.maps.maps[i].work << std::endl;
			saveMaps << "gold= " << information.maps.maps[i].gold << std::endl << std::endl;
		}
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SaveMaps);

	IHM::logfileconsole("_Save End_");
}
void SaveReload::savePlayer(sysinfo& information, std::vector<Player*>& tabplayer) {
	IHM::logfileconsole("_SavePlayer Start_");
	std::ofstream savePlayer(information.file.SavePlayer);
	if (savePlayer) {
		savePlayer << "nbPlayer= " << tabplayer.size();
		if (tabplayer.size() != 0) {
			for (unsigned int i = 0; i < tabplayer.size(); i++) {
				savePlayer << std::endl << std::endl << "player= " + std::to_string(i);
				savePlayer << std::endl << "name= " << tabplayer[i]->GETname();
				savePlayer << std::endl << "nbunitTotal= " << tabplayer[i]->GETtabunit().size();
				if (tabplayer[i]->GETtabunit().size() != 0) {
					for (unsigned int j = 0; j < tabplayer[i]->GETtabunit().size(); j++) {
						savePlayer << std::endl << std::endl << "\tunit= " << j;
						savePlayer << std::endl << "\tname= " << tabplayer[i]->GETtheunit(j)->GETname();
						savePlayer << std::endl << "\tx= " << tabplayer[i]->GETtheunit(j)->GETx();
						savePlayer << std::endl << "\ty= " << tabplayer[i]->GETtheunit(j)->GETy();
						savePlayer << std::endl << "\tlife= " << tabplayer[i]->GETtheunit(j)->GETlife();
						savePlayer << std::endl << "\tatq= " << tabplayer[i]->GETtheunit(j)->GETatq();
						savePlayer << std::endl << "\tdef= " << tabplayer[i]->GETtheunit(j)->GETdef();
						savePlayer << std::endl << "\tmovement= " << tabplayer[i]->GETtheunit(j)->GETmovement();
						savePlayer << std::endl << "\tlevel= " << tabplayer[i]->GETtheunit(j)->GETlevel();
					}
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
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SavePlayer);

	IHM::logfileconsole("_SavePlayer End_");
}
void SaveReload::reload(sysinfo& information, std::vector<Player*>& tabplayer) {
	IHM::logfileconsole("_Reload Start_");
	information.variable.statescreen = STATEmainmap;

	std::string destroy;
	std::string inttostringTileSize = std::to_string(information.maps.tileSize);

	std::ifstream saveScreen(information.file.SaveScreen);
	if (saveScreen) {
		for (unsigned int i = 0; i < information.maps.screen.size(); i++) {
			saveScreen >> destroy;
			if (destroy.compare("nb=") == 0)
				saveScreen >> information.maps.screen[i].tile_nb;
			else
				IHM::logfileconsole("reload ERROR : comparaison string nb= non identique");
			saveScreen >> destroy;
			if (destroy.compare("x=") == 0)
				saveScreen >> information.maps.screen[i].tile_x;
			else
				IHM::logfileconsole("reload ERROR : comparaison string x= non identique");
			saveScreen >> destroy;
			if (destroy.compare("y=") == 0)
				saveScreen >> information.maps.screen[i].tile_y;
			else
				IHM::logfileconsole("reload ERROR : comparaison string y= non identique");
			saveScreen >> destroy;
			if (destroy.compare("stringground=") == 0)
				saveScreen >> information.maps.screen[i].tile_stringground;
			else
				IHM::logfileconsole("reload ERROR : comparaison string stringground= non identique");
			saveScreen >> destroy;
			if (destroy.compare("ground=") == 0)
				saveScreen >> information.maps.screen[i].tile_ground;
			else
				IHM::logfileconsole("reload ERROR : comparaison string ground= non identique");
			saveScreen >> destroy;
			if (destroy.compare("stringspec=") == 0)
				saveScreen >> information.maps.screen[i].tile_stringspec;
			else
				IHM::logfileconsole("reload ERROR : comparaison string stringspec= non identique");
			saveScreen >> destroy;
			if (destroy.compare("spec=") == 0)
				saveScreen >> information.maps.screen[i].tile_spec;
			else
				IHM::logfileconsole("reload ERROR : comparaison string spec= non identique");
			saveScreen >> destroy;
			if (destroy.compare("appartenance=") == 0)
				saveScreen >> information.maps.screen[i].appartenance;
			else
				IHM::logfileconsole("reload ERROR : comparaison string appartenance= non identique");
			saveScreen >> destroy;
			if (destroy.compare("food=") == 0)
				saveScreen >> information.maps.screen[i].food;
			else
				IHM::logfileconsole("reload ERROR : comparaison string food= non identique");
			saveScreen >> destroy;
			if (destroy.compare("work=") == 0)
				saveScreen >> information.maps.screen[i].work;
			else
				IHM::logfileconsole("reload ERROR : comparaison string work= non identique");
			saveScreen >> destroy;
			if (destroy.compare("gold=") == 0)
				saveScreen >> information.maps.screen[i].gold;
			else
				IHM::logfileconsole("reload ERROR : comparaison string gold= non identique");

		}
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SaveScreen);

	unsigned int nbplayer = 0, nbunit = 0, test = 0, test1 = 0;
	unsigned int var[7];
	std::string name, unitname;
	int initspacename = 200, spacename = 32;


	std::ifstream savePlayer(information.file.SavePlayer);
	if (savePlayer) {
		savePlayer >> destroy;
		savePlayer >> nbplayer;

		if (nbplayer > 0) {
			for (unsigned int i = 0; i < nbplayer; i++) {
				savePlayer >> destroy;
				savePlayer >> test;
				if (test == i) {
					savePlayer >> destroy;
					savePlayer >> name;
					tabplayer.push_back(new Player(name));
					Buttons::createbutton(information, information.allButton.player,
						shaded, name, { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, 0, initspacename += spacename);

					savePlayer >> destroy;
					savePlayer >> nbunit;
					if (nbunit > 0) {
						for (unsigned int j = 0; j < nbunit; j++) {
							savePlayer >> destroy;
							savePlayer >> test1;
							if (test1 == j) {
								savePlayer >> destroy;
								savePlayer >> unitname;

								for (unsigned int k = 0; k < 7; k++) {
									savePlayer >> destroy;
									savePlayer >> var[k];
								}
								tabplayer[i]->addUnit(unitname, var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
							}
						}
					}
				}
			}
		}
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SavePlayer);

	SDL_RenderPresent(information.ecran.renderer);
	IHM::logfileconsole("_Reload End_");
}
void SaveReload::createSave(sysinfo& information) {
	IHM::logfileconsole("_createSave Start_");
	std::string destroy;
	unsigned int currentSave = 0;


	for (unsigned int i = 0; i < information.variable.save.GETnbSave(); i++) {
		if ((i + 1) != information.variable.save.GETtabSave()[i]) {
			information.variable.save.SETcurrentSave(i + 1);
			information.variable.save.GETtabSave().push_back(information.variable.save.GETcurrentSave());
			break;
		}
	}
	if (information.variable.save.GETcurrentSave() == 0) {
		information.variable.save.SETcurrentSave(information.variable.save.GETnbSave() + 1);
		information.variable.save.GETtabSave().push_back(information.variable.save.GETcurrentSave());
	}

	std::ofstream saveInfo(information.file.SaveInfo);
	if (saveInfo) {
		saveInfo << "NbSave=";
		saveInfo << std::endl << information.variable.save.GETnbSave() + 1;
		saveInfo << std::endl << "SaveUse=";
		for (unsigned int i = 0; i < information.variable.save.GETnbSave() + 1; i++)
			saveInfo << std::endl << information.variable.save.GETtabSave()[i];
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SaveInfo);

	std::string save = "save/" + std::to_string(information.variable.save.GETcurrentSave());
	_mkdir(save.c_str());
	information.variable.save.SETnbSave(information.variable.save.GETnbSave() + 1);

	information.file.SaveScreen = "save/" + std::to_string(information.variable.save.GETcurrentSave()) + "/SaveScreen.txt";
	information.file.SaveMaps = "save/" + std::to_string(information.variable.save.GETcurrentSave()) + "/SaveMaps.txt";
	information.file.SavePlayer = "save/" + std::to_string(information.variable.save.GETcurrentSave()) + "/SavePlayer.txt";

	IHM::logfileconsole("_createSave Start_");
}
void SaveReload::removeSave(sysinfo& information) {
	IHM::logfileconsole("_removeSave Start_");
	std::string file;
	bool condition = false;

	if (information.variable.save.GETcurrentSave() != 0) {

		for (unsigned int i = 0; i < information.variable.save.GETnbSave(); i++) {
			if (information.variable.save.GETcurrentSave() == information.variable.save.GETtabSave()[i]) {
				condition = true;
				break;
			}
		}


		if (condition) {
			file = "save/" + std::to_string(information.variable.save.GETcurrentSave()) + "/SaveScreen.txt";
			if (remove(file.c_str()) != 0)
				IHM::logfileconsole("ERREUR: Impossible d'effacer le fichier " + file);
			else
				IHM::logfileconsole("file : " + file + " successfully remove");

			file = "save/" + std::to_string(information.variable.save.GETcurrentSave()) + "/SaveMaps.txt";
			if (remove(file.c_str()) != 0)
				IHM::logfileconsole("ERREUR: Impossible d'effacer le fichier " + file);
			else
				IHM::logfileconsole("file : " + file + " successfully remove");

			file = "save/" + std::to_string(information.variable.save.GETcurrentSave()) + "/SavePlayer.txt";
			if (remove(file.c_str()) != 0)
				IHM::logfileconsole("ERREUR: Impossible d'effacer le fichier " + file);
			else
				IHM::logfileconsole("file : " + file + " successfully remove");

			file = "save/" + std::to_string(information.variable.save.GETcurrentSave());
			if (_rmdir(file.c_str()) != 0)
				IHM::logfileconsole("ERREUR: Impossible d'effacer le dossier " + file);
			else
				IHM::logfileconsole("directory : " + file + " successfully remove");

			information.variable.save.SETnbSave(information.variable.save.GETnbSave() - 1);
			if (information.variable.save.GETnbSave() == 0)
				information.variable.save.GETtabSave().clear();
			else
				information.variable.save.GETtabSave().erase(information.variable.save.GETtabSave().begin() + information.variable.save.GETcurrentSave() - 1);

			for (unsigned int i = 0; i < information.allButton.reload.size(); i++) {
				if (information.allButton.reload[i]->searchButtonName("Save : " + std::to_string(information.variable.save.GETcurrentSave()), information.variable.statescreen)) {
					delete information.allButton.reload[i];
					information.allButton.reload.erase(information.allButton.reload.begin() + i);
					break;
				}
			}

			std::ofstream saveInfo(information.file.SaveInfo);
			if (saveInfo) {
				saveInfo << "NbSave=";
				saveInfo << std::endl << information.variable.save.GETnbSave();
				saveInfo << std::endl << "SaveUse=";
				for (unsigned int i = 0; i < information.variable.save.GETnbSave(); i++)
					saveInfo << std::endl << information.variable.save.GETtabSave()[i];
			}
			else
				IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SaveInfo);
		}
	}
	else
		IHM::logfileconsole("ERREUR: currentSave = 0");

	IHM::logfileconsole("_removeSave End_");
}
void SaveReload::clearSave(sysinfo& information) {
	IHM::logfileconsole("_clearSave Start_");


	for (unsigned int i = 0; i < information.allButton.reload.size(); i++) {
		for (unsigned int j = 0; j < information.variable.save.GETnbSave(); j++) {
			if (information.allButton.reload[i]->searchButtonName("Save : " + std::to_string(information.variable.save.GETtabSave()[j]), information.variable.statescreen)) {
				delete information.allButton.reload[i];
				information.allButton.reload.erase(information.allButton.reload.begin() + i);
			}
		}
	}

	std::string file;
	for (unsigned int i = 0; i < information.variable.save.GETnbSave(); i++) {


		file = "save/" + std::to_string(information.variable.save.GETtabSave()[i]) + "/SaveScreen.txt";
		if (remove(file.c_str()) != 0)
			IHM::logfileconsole("ERREUR: Impossible d'effacer le fichier " + file);
		else
			IHM::logfileconsole("file : " + file + " successfully remove");

		file = "save/" + std::to_string(information.variable.save.GETtabSave()[i]) + "/SaveMaps.txt";
		if (remove(file.c_str()) != 0)
			IHM::logfileconsole("ERREUR: Impossible d'effacer le fichier " + file);
		else
			IHM::logfileconsole("file : " + file + " successfully remove");

		file = "save/" + std::to_string(information.variable.save.GETtabSave()[i]) + "/SavePlayer.txt";
		if (remove(file.c_str()) != 0)
			IHM::logfileconsole("ERREUR: Impossible d'effacer le fichier " + file);
		else
			IHM::logfileconsole("file : " + file + " successfully remove");

		file = "save/" + std::to_string(information.variable.save.GETtabSave()[i]);
		if (_rmdir(file.c_str()) != 0)
			IHM::logfileconsole("ERREUR: Impossible d'effacer le dossier " + file);
		else
			IHM::logfileconsole("directory : " + file + " successfully remove");
	}

	std::ofstream saveInfo(information.file.SaveInfo);
	if (saveInfo) {
		saveInfo << "NbSave=";
		saveInfo << std::endl << "0";
		saveInfo << std::endl << "SaveUse=";
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SaveInfo);

	information.variable.save.SETnbSave(0);
	information.variable.save.SETcurrentSave(0);
	information.variable.save.GETtabSave().clear();

	IHM::logfileconsole("_clearSave End_");
}


/* SaveReload :: METHODES */

SaveReload::SaveReload(): _nbSave(0), _currentSave(0)
{
}
SaveReload::~SaveReload()
{
}
std::vector<unsigned int>& SaveReload::GETtabSave(){
	return _tabSave;
}
unsigned int SaveReload::GETcurrentSave()const {
	return _currentSave;
}
unsigned int SaveReload::GETnbSave()const {
	return _nbSave;
}
void SaveReload::SETtabSave(std::vector<unsigned int>& tab) {
	_tabSave = tab;
}

void SaveReload::SETcurrentSave(unsigned int currentSave) {
	_currentSave = currentSave;
}
void SaveReload::SETnbSave(unsigned int nbSave) {
	_nbSave = nbSave;
}
