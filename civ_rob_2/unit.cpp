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
#include "initAndError.h"

using namespace std;

void loadUnitAndSpec(sysinfo& information) {
	ifstream UNIT("bin/UNIT.txt");
	if (UNIT) {
		string destroy;
		tabUnitAndSpec currentUnit;

		UNIT >> destroy;
		UNIT >> information.variable.s_player.unitNameMaxToCreate;

		for (unsigned int i = 0; i < information.variable.s_player.unitNameMaxToCreate; i++) {
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
			information.variable.s_player.s_tabUnitAndSpec.push_back(currentUnit);
		}

	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier bin/UNIT.txt");
}


void searchunit(sysinfo& information){
	information.variable.s_player.unitNameToCreate = information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate].name;
}


void searchUnitTile(sysinfo& information, std::vector<Player*>& tabplayer) {
	for (unsigned int i = 0; i < tabplayer[information.variable.s_player.selectplayer]->GETtabunit().size(); i++) {
		if (tabplayer[information.variable.s_player.selectplayer]->GETtheunit(i)->testPos(information.variable.s_wheel.mouse_x, information.variable.s_wheel.mouse_y)) {
			information.variable.s_player.selectunit = i;
			information.variable.s_player.unitNameToMove = tabplayer[information.variable.s_player.selectplayer]->GETtheunit(i)->GETname();
			tabplayer[information.variable.s_player.selectplayer]->GETtheunit(i)->SETblit(true);
			break;
		}
	}
}


void tryToMove(sysinfo& information, vector<Player*>& tabplayer, int x, int y){
	switch (searchToMove(information, tabplayer, x, y)) {
	case 0:
		break;
	case 1:
		tabplayer[information.variable.s_player.selectplayer]->GETtheunit(information.variable.s_player.selectunit)->move(information.variable.select, information.variable.s_player.selectunit, x, y);
		break;
	case 2:
		tabplayer[information.variable.s_player.selectplayer]->GETtheunit(information.variable.s_player.selectunit)->attack(tabplayer[information.variable.s_player.selectPlayerToAttack]->GETtheunit(information.variable.s_player.selectUnitToAttack));
		if (tabplayer[information.variable.s_player.selectPlayerToAttack]->GETtheunit(information.variable.s_player.selectUnitToAttack)->GETalive() ==  false) {
			tabplayer[information.variable.s_player.selectPlayerToAttack]->deleteUnit(information.variable.s_player.selectUnitToAttack);
			tryToMove(information, tabplayer, x, y);
		}
		tabplayer[information.variable.s_player.selectplayer]->GETtheunit(information.variable.s_player.selectunit)->SETmovement(0);
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
	bool ground = false;

	for (unsigned int i = 0; i < information.maps.screen.size(); i++){
		if (information.maps.screen[i].tile_x == tabplayer[information.variable.s_player.selectplayer]->GETtheunit(information.variable.s_player.selectunit)->GETx() + x &&
			information.maps.screen[i].tile_y == tabplayer[information.variable.s_player.selectplayer]->GETtheunit(information.variable.s_player.selectunit)->GETy() + y){
			if (information.maps.screen[i].tile_ground == grass){
				ground = true;
				break;
			}
		}
	}

	if (ground){
		for (unsigned int i = 0; i < tabplayer.size(); i++) {
			for (unsigned int j = 0; j < tabplayer[i]->GETtabunit().size(); j++) {
				if (tabplayer[information.variable.s_player.selectplayer]->GETtheunit(information.variable.s_player.selectunit)->GETx() + x == tabplayer[i]->GETtheunit(j)->GETx()) {
					if (tabplayer[information.variable.s_player.selectplayer]->GETtheunit(information.variable.s_player.selectunit)->GETy() + y == tabplayer[i]->GETtheunit(j)->GETy()) {
						if (information.variable.s_player.selectplayer == i)
							return 0;
						else {
							information.variable.s_player.selectPlayerToAttack = i;
							information.variable.s_player.selectUnitToAttack = j;
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

bool irrigate(sysinfo&, std::vector<Player*>&) {
	return false;
}


