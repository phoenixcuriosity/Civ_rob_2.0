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

#include "unit.h"

using namespace std;

void loadUnitAndSpec(sysinfo& information) {
	ifstream UNIT("bin/UNIT.txt");
	if (UNIT) {
		string destroy;
		tabUnitAndSpec currentUnit;

		UNIT >> destroy;
		UNIT >> information.variable.unitNameMaxToCreate;

		for (unsigned int i = 0; i < information.variable.unitNameMaxToCreate; i++) {
			UNIT >> destroy;
			UNIT >> currentUnit.name;

			UNIT >> destroy;
			UNIT >> currentUnit.life;

			UNIT >> destroy;
			UNIT >> currentUnit.atq;

			UNIT >> destroy;
			UNIT >> currentUnit.def;

			UNIT >> destroy;
			UNIT >> currentUnit.movement;

			UNIT >> destroy;
			UNIT >> currentUnit.level;
			information.variable.s_tabUnitAndSpec.push_back(currentUnit);
		}

	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier bin/UNIT.txt");
}


void searchunit(sysinfo& information){
	information.variable.unitNameToCreate = information.variable.s_tabUnitAndSpec[information.variable.unitToCreate].name;
}


void searchUnitTile(sysinfo& information, std::vector<Player*>& tabplayer) {
	for (unsigned int i = 0; i < tabplayer[information.variable.selectplayer]->GETtabunit().size(); i++) {
		if (tabplayer[information.variable.selectplayer]->GETtheunit(i)->testPos(information.variable.mouse_x, information.variable.mouse_y)) {
			information.variable.selectunit = i;
			information.variable.unitNameToMove = tabplayer[information.variable.selectplayer]->GETtheunit(i)->GETname();
			tabplayer[information.variable.selectplayer]->GETtheunit(i)->SETblit(true);
			break;
		}
	}
}


void tryToMove(sysinfo& information, vector<Player*>& tabplayer, int x, int y){
	switch (searchToMove(information, tabplayer, x, y)) {
	case 0:
		break;
	case 1:
		tabplayer[information.variable.selectplayer]->GETtheunit(information.variable.selectunit)->move(information.variable.select, information.variable.selectunit, x, y);
		break;
	case 2:
		tabplayer[information.variable.selectplayer]->GETtheunit(information.variable.selectunit)->attack(tabplayer[information.variable.selectPlayerToAttack]->GETtheunit(information.variable.selectUnitToAttack));
		if (tabplayer[information.variable.selectPlayerToAttack]->GETtheunit(information.variable.selectUnitToAttack)->GETalive() ==  false) {
			tabplayer[information.variable.selectPlayerToAttack]->deleteUnit(information.variable.selectUnitToAttack);
			tryToMove(information, tabplayer, x, y);
		}
		tabplayer[information.variable.selectplayer]->GETtheunit(information.variable.selectunit)->SETmovement(0);
		break;
	}
}


int searchToMove(sysinfo& information, vector<Player*>& tabplayer, int x, int y) {
	/*
		conditions de mouvement :
			- que la case cible soit du sol et
					- que la case cible est libre
					- ou que la case cible est occupée par un ennemi susceptible de mourrir par l'attaque

	*/

	unsigned int k = 0;
	bool ground = false;

	for (unsigned int i = toolBarSize; i < SCREEN_WIDTH / tileSize; i++){
		for (unsigned int j = 0; j < SCREEN_HEIGHT / tileSize; j++){
			if (information.maps.tiles[k].tile_x == tabplayer[information.variable.selectplayer]->GETtheunit(information.variable.selectunit)->GETx() + x && information.maps.tiles[k].tile_y == tabplayer[information.variable.selectplayer]->GETtheunit(information.variable.selectunit)->GETy() + y){
				if (information.maps.tiles[k].tile_ground == grass){
					ground = true;
					break;
				}
			}
			k++;
		}
	}

	if (ground){
		for (unsigned int i = 0; i < tabplayer.size(); i++) {
			for (unsigned int j = 0; j < tabplayer[i]->GETtabunit().size(); j++) {
				if (tabplayer[information.variable.selectplayer]->GETtheunit(information.variable.selectunit)->GETx() + x == tabplayer[i]->GETtheunit(j)->GETx()) {
					if (tabplayer[information.variable.selectplayer]->GETtheunit(information.variable.selectunit)->GETy() + y == tabplayer[i]->GETtheunit(j)->GETy()) {
						if (information.variable.selectplayer == i)
							return 0;
						else {
							information.variable.selectPlayerToAttack = i;
							information.variable.selectUnitToAttack = j;
							return 2;
						}
					}
				}
			}
		}
	}
	else
		return 0;
	return 1;
}


