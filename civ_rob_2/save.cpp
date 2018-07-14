/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.6

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Civ_rob_2

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

#include "save.h"
#include "sdl.h"

using namespace std;

void savemaps(sysinfo& information){
	logfileconsole("_Save Start_");
	ofstream savemaps(information.file.Savemaps);
	if (savemaps){}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.Savemaps);


	int k = 0;
	for (int i = toolBarSize; i < SCREEN_WIDTH / tileSize; i++){
		for (int j = 0; j < SCREEN_HEIGHT / tileSize; j++){
			savemaps << "nb= " << information.maps.tiles[k].tile_nb << endl;
			savemaps << "x= " << information.maps.tiles[k].tile_x << endl;
			savemaps << "y= " << information.maps.tiles[k].tile_y << endl;
			savemaps << "stringground= " << information.maps.tiles[k].tile_stringground << endl;
			savemaps << "ground= " << information.maps.tiles[k].tile_ground << endl;
			savemaps << "stringspec= " << information.maps.tiles[k].tile_stringspec << endl;
			savemaps << "spec= " << information.maps.tiles[k].tile_spec << endl;
			savemaps << "appartenance= " << information.maps.tiles[k].appartenance << endl;
			savemaps << "food= " << information.maps.tiles[k].food << endl;
			savemaps << "work= " << information.maps.tiles[k].work << endl;
			savemaps << "gold= " << information.maps.tiles[k].gold << endl << endl;
			k++;
		}
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