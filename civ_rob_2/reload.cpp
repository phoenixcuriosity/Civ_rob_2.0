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

#include "reload.h"

#include "createButton.h"
#include "unit.h"

using namespace std;

void reload(sysinfo& information, vector<Player*>& tabplayer){
	logfileconsole("_Reload Start_");
	information.ecran.statescreen = STATEmainmap;

	string destroy;
	int k = 0;
	string inttostringTileSize = to_string(tileSize);

	ifstream savemaps(information.file.Savemaps);
	if (savemaps){
		for (int i = toolBarSize; i < SCREEN_WIDTH / tileSize; i++){
			for (int j = 0; j < SCREEN_HEIGHT / tileSize; j++){
				savemaps >> destroy;
				if (destroy.compare("nb=") == 0)
					savemaps >> information.maps.tiles[k].tile_nb;
				else
					logfileconsole("reload ERROR : comparaison string nb= non identique");
				savemaps >> destroy;
				if (destroy.compare("x=") == 0)
					savemaps >> information.maps.tiles[k].tile_x;
				else
					logfileconsole("reload ERROR : comparaison string x= non identique");
				savemaps >> destroy;
				if (destroy.compare("y=") == 0)
					savemaps >> information.maps.tiles[k].tile_y;
				else
					logfileconsole("reload ERROR : comparaison string y= non identique");
				savemaps >> destroy;
				if (destroy.compare("stringground=") == 0)
					savemaps >> information.maps.tiles[k].tile_stringground;
				else
					logfileconsole("reload ERROR : comparaison string stringground= non identique");
				savemaps >> destroy;
				if (destroy.compare("ground=") == 0)
					savemaps >> information.maps.tiles[k].tile_ground;
				else
					logfileconsole("reload ERROR : comparaison string ground= non identique");
				savemaps >> destroy;
				if (destroy.compare("stringspec=") == 0)
					savemaps >> information.maps.tiles[k].tile_stringspec;
				else
					logfileconsole("reload ERROR : comparaison string stringspec= non identique");
				savemaps >> destroy;
				if (destroy.compare("spec=") == 0)
					savemaps >> information.maps.tiles[k].tile_spec;
				else
					logfileconsole("reload ERROR : comparaison string spec= non identique");
				savemaps >> destroy;
				if (destroy.compare("appartenance=") == 0)
					savemaps >> information.maps.tiles[k].appartenance;
				else
					logfileconsole("reload ERROR : comparaison string appartenance= non identique");
				savemaps >> destroy;
				if (destroy.compare("food=") == 0)
					savemaps >> information.maps.tiles[k].food;
				else
					logfileconsole("reload ERROR : comparaison string food= non identique");
				savemaps >> destroy;
				if (destroy.compare("work=") == 0)
					savemaps >> information.maps.tiles[k].work;
				else
					logfileconsole("reload ERROR : comparaison string work= non identique");
				savemaps >> destroy;
				if (destroy.compare("gold=") == 0)
					savemaps >> information.maps.tiles[k].gold;
				else
					logfileconsole("reload ERROR : comparaison string gold= non identique");

				k++;
			}
		}
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.Savemaps);

	unsigned int nbplayer = 0, nbunit = 0, test = 0,test1 = 0;
	unsigned int var[7];
	string name, unitname;
	int initspacename = 200, spacename = 32;
	

	ifstream savePlayer(information.file.SavePlayer);
	if (savePlayer){
		savePlayer >> destroy;
		savePlayer >> nbplayer;

		if (nbplayer > 0){
			for (unsigned int i = 0; i < nbplayer; i++){
				savePlayer >> destroy;
				savePlayer >> test;
				if (test == i){
					savePlayer >> destroy;
					savePlayer >> name;
					tabplayer.push_back(new Player(name));
					createbutton(information, name, { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, 0, initspacename += spacename);

					savePlayer >> destroy;
					savePlayer >> nbunit;
					if (nbunit > 0){
						for (unsigned int j = 0; j < nbunit; j++){
							savePlayer >> destroy;
							savePlayer >> test1;
							if (test1 == j){
								savePlayer >> destroy;
								savePlayer >> unitname;

								for (unsigned int k = 0; k < 7; k++){
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

