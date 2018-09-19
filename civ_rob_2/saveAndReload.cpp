/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.9

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

#include "saveAndReload.h"
#include "initAndError.h"

using namespace std;

void savemaps(sysinfo& information){
	logfileconsole("_Save Start_");
	ofstream savemaps(information.file.Savemaps);
	if (savemaps){}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.Savemaps);

	for (unsigned int i = 0; i < information.maps.screen.size(); i++){
		savemaps << "nb= " << information.maps.screen[i].tile_nb << endl;
		savemaps << "x= " << information.maps.screen[i].tile_x << endl;
		savemaps << "y= " << information.maps.screen[i].tile_y << endl;
		savemaps << "stringground= " << information.maps.screen[i].tile_stringground << endl;
		savemaps << "ground= " << information.maps.screen[i].tile_ground << endl;
		savemaps << "stringspec= " << information.maps.screen[i].tile_stringspec << endl;
		savemaps << "spec= " << information.maps.screen[i].tile_spec << endl;
		savemaps << "appartenance= " << information.maps.screen[i].appartenance << endl;
		savemaps << "food= " << information.maps.screen[i].food << endl;
		savemaps << "work= " << information.maps.screen[i].work << endl;
		savemaps << "gold= " << information.maps.screen[i].gold << endl << endl;
	}
	logfileconsole("_Save End_");
}

void savePlayer(sysinfo& information, std::vector<Player*>& tabplayer){
	logfileconsole("_SavePlayer Start_");
	ofstream savePlayer(information.file.SavePlayer);
	if (savePlayer){
		savePlayer << "nbPlayer= " << tabplayer.size();
		if (tabplayer.size() != 0){
			for (unsigned int i = 0; i < tabplayer.size(); i++){
				savePlayer << endl << endl << "player= " + to_string(i);
				savePlayer << endl << "name= " << tabplayer[i]->GETname();
				savePlayer << endl << "nbunitTotal= " << tabplayer[i]->GETtabunit().size();
				if (tabplayer[i]->GETtabunit().size() != 0){
					for (unsigned int j = 0; j < tabplayer[i]->GETtabunit().size(); j++){
						savePlayer << endl << endl << "\tunit= " << j;
						savePlayer << endl << "\tname= " << tabplayer[i]->GETtheunit(j)->GETname();
						savePlayer << endl << "\tx= " << tabplayer[i]->GETtheunit(j)->GETx();
						savePlayer << endl << "\ty= " << tabplayer[i]->GETtheunit(j)->GETy();
						savePlayer << endl << "\tlife= " << tabplayer[i]->GETtheunit(j)->GETlife();
						savePlayer << endl << "\tatq= " << tabplayer[i]->GETtheunit(j)->GETatq();
						savePlayer << endl << "\tdef= " << tabplayer[i]->GETtheunit(j)->GETdef();
						savePlayer << endl << "\tmovement= " << tabplayer[i]->GETtheunit(j)->GETmovement();
						savePlayer << endl << "\tlevel= " << tabplayer[i]->GETtheunit(j)->GETlevel();
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
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SavePlayer);

	logfileconsole("_SavePlayer End_");
}

void reload(sysinfo& information, vector<Player*>& tabplayer) {
	logfileconsole("_Reload Start_");
	information.variable.statescreen = STATEmainmap;

	string destroy;
	string inttostringTileSize = to_string(information.maps.tileSize);

	ifstream savemaps(information.file.Savemaps);
	if (savemaps) {
		for (unsigned int i = 0; i < information.maps.screen.size(); i++) {
			savemaps >> destroy;
			if (destroy.compare("nb=") == 0)
				savemaps >> information.maps.screen[i].tile_nb;
			else
				logfileconsole("reload ERROR : comparaison string nb= non identique");
			savemaps >> destroy;
			if (destroy.compare("x=") == 0)
				savemaps >> information.maps.screen[i].tile_x;
			else
				logfileconsole("reload ERROR : comparaison string x= non identique");
			savemaps >> destroy;
			if (destroy.compare("y=") == 0)
				savemaps >> information.maps.screen[i].tile_y;
			else
				logfileconsole("reload ERROR : comparaison string y= non identique");
			savemaps >> destroy;
			if (destroy.compare("stringground=") == 0)
				savemaps >> information.maps.screen[i].tile_stringground;
			else
				logfileconsole("reload ERROR : comparaison string stringground= non identique");
			savemaps >> destroy;
			if (destroy.compare("ground=") == 0)
				savemaps >> information.maps.screen[i].tile_ground;
			else
				logfileconsole("reload ERROR : comparaison string ground= non identique");
			savemaps >> destroy;
			if (destroy.compare("stringspec=") == 0)
				savemaps >> information.maps.screen[i].tile_stringspec;
			else
				logfileconsole("reload ERROR : comparaison string stringspec= non identique");
			savemaps >> destroy;
			if (destroy.compare("spec=") == 0)
				savemaps >> information.maps.screen[i].tile_spec;
			else
				logfileconsole("reload ERROR : comparaison string spec= non identique");
			savemaps >> destroy;
			if (destroy.compare("appartenance=") == 0)
				savemaps >> information.maps.screen[i].appartenance;
			else
				logfileconsole("reload ERROR : comparaison string appartenance= non identique");
			savemaps >> destroy;
			if (destroy.compare("food=") == 0)
				savemaps >> information.maps.screen[i].food;
			else
				logfileconsole("reload ERROR : comparaison string food= non identique");
			savemaps >> destroy;
			if (destroy.compare("work=") == 0)
				savemaps >> information.maps.screen[i].work;
			else
				logfileconsole("reload ERROR : comparaison string work= non identique");
			savemaps >> destroy;
			if (destroy.compare("gold=") == 0)
				savemaps >> information.maps.screen[i].gold;
			else
				logfileconsole("reload ERROR : comparaison string gold= non identique");

		}
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.Savemaps);

	unsigned int nbplayer = 0, nbunit = 0, test = 0, test1 = 0;
	unsigned int var[7];
	string name, unitname;
	int initspacename = 200, spacename = 32;


	ifstream savePlayer(information.file.SavePlayer);
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
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SavePlayer);

	SDL_RenderPresent(information.ecran.renderer);
	logfileconsole("_Reload End_");
}

void createSave(sysinfo& information) {
	logfileconsole("_createSave Start_");
	string destroy;
	unsigned int currentSave = 0;

	for (unsigned int i = 0; i < information.variable.s_save.nbSave; i++) {
		if ((i + 1) != information.variable.s_save.tabSave[i]) {
			information.variable.s_save.currentSave = i + 1;
			information.variable.s_save.tabSave.push_back(information.variable.s_save.currentSave);
			break;
		}
	}

	if (information.variable.s_save.currentSave == 0) {
		information.variable.s_save.currentSave = information.variable.s_save.nbSave + 1;
		information.variable.s_save.tabSave.push_back(information.variable.s_save.currentSave);
	}

	ofstream saveInfo(information.file.SaveInfo);
	if (saveInfo) {
		saveInfo << "NbSave=";
		saveInfo << endl << information.variable.s_save.nbSave + 1;
		saveInfo << endl << "SaveUse=";
		for (unsigned int i = 0; i < information.variable.s_save.nbSave + 1; i++)
			saveInfo << endl << information.variable.s_save.tabSave[i];
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SaveInfo);

	string save = "save/" + to_string(information.variable.s_save.currentSave);
	_mkdir(save.c_str());
	information.variable.s_save.nbSave++;

	information.file.Savemaps = "save/" + to_string(information.variable.s_save.currentSave) + "/Savemaps.txt";
	information.file.SavePlayer = "save/" + to_string(information.variable.s_save.currentSave) + "/SavePlayer.txt";

	logfileconsole("_createSave Start_");
}
void removeSave(sysinfo& information) {
	logfileconsole("_removeSave Start_");
	string file;
	bool condition = false;

	if (information.variable.s_save.currentSave != 0) {

		for (unsigned int i = 0; i < information.variable.s_save.nbSave; i++) {
			if (information.variable.s_save.currentSave == information.variable.s_save.tabSave[i]) {
				condition = true;
				break;
			}
		}


		if (condition) {
			file = "save/" + to_string(information.variable.s_save.currentSave) + "/Savemaps.txt";
			if (remove(file.c_str()) != 0)
				logfileconsole("ERREUR: Impossible d'effacer le fichier " + file);
			else
				logfileconsole("file : " + file + " successfully remove");

			file = "save/" + to_string(information.variable.s_save.currentSave) + "/SavePlayer.txt";
			if (remove(file.c_str()) != 0)
				logfileconsole("ERREUR: Impossible d'effacer le fichier " + file);
			else
				logfileconsole("file : " + file + " successfully remove");

			file = "save/" + to_string(information.variable.s_save.currentSave);
			if (_rmdir(file.c_str()) != 0)
				logfileconsole("ERREUR: Impossible d'effacer le dossier " + file);
			else
				logfileconsole("directory : " + file + " successfully remove");

			information.variable.s_save.nbSave--;
			if (information.variable.s_save.nbSave == 0)
				information.variable.s_save.tabSave.clear();
			else
				information.variable.s_save.tabSave.erase(information.variable.s_save.tabSave.begin() + information.variable.s_save.currentSave - 1);

			for (unsigned int i = 0; i < information.allButton.reload.size(); i++) {
				if (information.allButton.reload[i]->searchButtonName("Save : " + to_string(information.variable.s_save.currentSave), information.variable.statescreen)) {
					delete information.allButton.reload[i];
					information.allButton.reload.erase(information.allButton.reload.begin() + i);
					break;
				}
			}

			ofstream saveInfo(information.file.SaveInfo);
			if (saveInfo) {
				saveInfo << "NbSave=";
				saveInfo << endl << information.variable.s_save.nbSave;
				saveInfo << endl << "SaveUse=";
				for (unsigned int i = 0; i < information.variable.s_save.nbSave; i++)
					saveInfo << endl << information.variable.s_save.tabSave[i];
			}
			else
				logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SaveInfo);
		}
	}
	else
		logfileconsole("ERREUR: currentSave = 0");

	logfileconsole("_removeSave End_");
}
void clearSave(sysinfo& information) {
	logfileconsole("_clearSave Start_");


	for (unsigned int i = 0; i < information.allButton.reload.size(); i++) {
		for (unsigned int j = 0; j < information.variable.s_save.nbSave; j++) {
			if (information.allButton.reload[i]->searchButtonName("Save : " + to_string(information.variable.s_save.tabSave[j]), information.variable.statescreen)) {
				delete information.allButton.reload[i];
				information.allButton.reload.erase(information.allButton.reload.begin() + i);
			}
		}
	}

	string file;
	for (unsigned int i = 0; i < information.variable.s_save.nbSave; i++) {	
		

		file = "save/" + to_string(information.variable.s_save.tabSave[i]) + "/Savemaps.txt";
		if(remove(file.c_str()) != 0)
			logfileconsole("ERREUR: Impossible d'effacer le fichier " + file);
		else
			logfileconsole("file : " + file + " successfully remove");

		file = "save/" + to_string(information.variable.s_save.tabSave[i]) + "/SavePlayer.txt";
		if (remove(file.c_str()) != 0)
			logfileconsole("ERREUR: Impossible d'effacer le fichier " + file);
		else
			logfileconsole("file : " + file + " successfully remove");

		file = "save/" + to_string(information.variable.s_save.tabSave[i]);
		if(_rmdir(file.c_str()) != 0)
			logfileconsole("ERREUR: Impossible d'effacer le dossier " + file);
		else
			logfileconsole("directory : " + file + " successfully remove");
	}

	ofstream saveInfo(information.file.SaveInfo);
	if (saveInfo) {
		saveInfo << "NbSave=";
		saveInfo << endl << "0";
		saveInfo << endl << "SaveUse=";
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SaveInfo);

	information.variable.s_save.nbSave = 0;
	information.variable.s_save.currentSave = 0;
	information.variable.s_save.tabSave.clear();
	

	logfileconsole("_clearSave End_");
}