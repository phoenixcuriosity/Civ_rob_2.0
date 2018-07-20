/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.6

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

#include "citie.h"


using namespace std;

void createcitie(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.variable.unitNameToMove.compare("settler") == 0) {

		string name = information.variable.tabCitieName[(information.variable.selectplayer * 5) + tabplayer[information.variable.selectplayer]->GETtabcities().size()];
		int x = tabplayer[information.variable.selectplayer]->GETtheunit(information.variable.selectunit)->GETx();
		int y = tabplayer[information.variable.selectplayer]->GETtheunit(information.variable.selectunit)->GETy();

		unsigned int k = 0, middleTile = 0;
		
		tile tabtile[initSizeView*initSizeView];
		for (int i = toolBarSize; i < SCREEN_WIDTH / tileSize; i++) {
			for (int j = 0; j < SCREEN_HEIGHT / tileSize; j++) {
				if (information.maps.tiles[k].tile_x == x && information.maps.tiles[k].tile_y == y) {
					middleTile = k;
					break;
				}
				k++;
			}
		}
		int o = (int)floor((double)initSizeView / 2.0);
		for (int z = -(int)floor((double)initSizeView / 2.0); z < (int)ceil((double)initSizeView / 2.0); z++) {
			o = (int)floor((double)initSizeView / 2.0);
			for (int i = (initSizeView * (z + (int)floor((double)initSizeView / 2.0))); i < (initSizeView * (z + (int)ceil((double)initSizeView / 2.0))); i++) {
				if (o > -initSizeInfluence && o < initSizeInfluence && z > -initSizeInfluence && z < initSizeInfluence)
					information.maps.tiles[middleTile - z - (o * (SCREEN_HEIGHT / tileSize))].appartenance = information.variable.selectplayer;
				tabtile[i] = information.maps.tiles[middleTile - z - (o * (SCREEN_HEIGHT / tileSize))];
				tabtile[i].tile_x = (SCREEN_WIDTH / 2) - (o * tileSize);
				tabtile[i].tile_y = (SCREEN_HEIGHT / 2) - (z * tileSize);
				o--;
			}
		}
		tabplayer[information.variable.selectplayer]->addCitie(name, x, y, tabtile);

		tabplayer[information.variable.selectplayer]->deleteUnit(information.variable.selectunit);
		information.variable.selectunit = -1;
		information.variable.unitNameToMove = "";
	}
}






void searchCitieTile(sysinfo& information, std::vector<Player*>& tabplayer) {
	for (unsigned int i = 0; i < tabplayer[information.variable.selectplayer]->GETtabcities().size(); i++) {
		if (tabplayer[information.variable.selectplayer]->GETthecitie(i)->testPos(information.variable.mouse_x, information.variable.mouse_y)) {
			information.variable.selectCitie = i;
			information.ecran.statescreen = STATEcitiemap;
			information.variable.select = selectnothing;
			break;
		}
	}
}