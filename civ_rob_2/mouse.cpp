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
#include "mouse.h"

#include "sdl.h"
#include "renduecran.h"
#include "unit.h"
#include "save.h"
#include "reload.h"
#include "newgame.h"
#include "nextTurn.h"
#include "citie.h"

using namespace std;

void mouse(sysinfo& information, vector<Player*>& tabplayer, SDL_Event event){
	/*
	Handle Mouse Event
	BUTTON_LEFT
	BUTTON_RIGHT
	
	*/
	
	if (event.button.button == SDL_BUTTON_LEFT)
		cliqueGauche(information, tabplayer, event);
	else if (event.button.button == SDL_BUTTON_RIGHT && information.ecran.statescreen == STATEmainmap)
		cliqueDroit(information, tabplayer, event);
	
}
void cliqueGauche(sysinfo& information, std::vector<Player*>& tabplayer, SDL_Event event){
	// inspect citie
	if (information.ecran.statescreen == STATEmainmap) {
		if (information.variable.selectplayer > -1) {
			if (information.variable.select == selectinspect && tabplayer[information.variable.selectplayer]->GETtabcities().size() != 0) {
				information.variable.mouse_x = (unsigned int)ceil(event.button.x / tileSize) * tileSize;
				information.variable.mouse_y = (unsigned int)ceil(event.button.y / tileSize) * tileSize;
				searchCitieTile(information, tabplayer);
			}
		}
	}
	// recherche du bouton par comparaison de string et des positions x et y du clic
	for (unsigned int i = 0; i < information.tabbutton.size(); i++){ // recherche si une bouton est dans ces coordonnées
		switch (information.ecran.statescreen){
		case STATEmainmap:
			if (information.tabbutton[i]->searchButton((string)"Ecran Titre", information.ecran.statescreen, event.button.x, event.button.y)) {
				savemaps(information);
				savePlayer(information, tabplayer);
				logfileconsole("__________________________");
				ecrantitre(information);
			}
			else if (information.tabbutton[i]->searchButton((string)"Create Unit", information.ecran.statescreen, event.button.x, event.button.y)) {
				information.tabbutton[i]->changeOn();
				if (information.variable.select != selectcreate)
					information.variable.select = selectcreate;
				else
					information.variable.select = selectnothing;
			}
			else if (information.tabbutton[i]->searchButton((string)"Move Unit", information.ecran.statescreen, event.button.x, event.button.y)) {
				information.tabbutton[i]->changeOn();
				if (information.variable.select != selectmove)
					information.variable.select = selectmove;
				else {
					information.variable.selectunit = -1;
					information.variable.select = selectnothing;
				}
			}
			else if (information.tabbutton[i]->searchButton((string)"Inspect", information.ecran.statescreen, event.button.x, event.button.y)) {
				information.tabbutton[i]->changeOn();
				if (information.variable.select != selectinspect)
					information.variable.select = selectinspect;
				else {
					information.variable.selectunit = -1;
					information.variable.select = selectnothing;
				}
			}
			else if (information.tabbutton[i]->searchButton((string)"Next Turn", information.ecran.statescreen, event.button.x, event.button.y)) {
				nextTurn(information, tabplayer);
			}
			else if (information.tabbutton[i]->searchButton((string)"Delete Unit", information.ecran.statescreen, event.button.x, event.button.y)) {
				information.tabbutton[i]->SETon(!information.tabbutton[i]->GETon());
			}

			// player select
			for (unsigned int l = 0; l < tabplayer.size(); l++) {
				if (information.tabbutton[i]->searchButton((string)tabplayer[l]->GETname(), information.ecran.statescreen, event.button.x, event.button.y)) {
					information.tabbutton[i]->changeOn();
					if (information.variable.selectplayer != l)
						information.variable.selectplayer = l;
					else
						information.variable.selectplayer = -1;
					logfileconsole("information.variable.selectplayer = " + tabplayer[l]->GETname());
					break;
				}
			}
			// reset de l'affichage On des boutons
			for (unsigned int l = 0; l < information.tabbutton.size(); l++){
				information.tabbutton[l]->resetOnStatescreen(information.variable.select, selectnothing);
				information.tabbutton[l]->resetOnPlayer(information.variable.selectplayer, information.variable.tabPlayerName);
			}
			break;
		case STATEecrantitre:
			if (information.tabbutton[i]->searchButton((string)"New Game", information.ecran.statescreen, event.button.x, event.button.y)){
				newgame(information, tabplayer);
				return;
			}
			else if (information.tabbutton[i]->searchButton((string)"Reload", information.ecran.statescreen, event.button.x, event.button.y)){
				reload(information, tabplayer);
				return;
			}
			else if (information.tabbutton[i]->searchButton((string)"Quit", information.ecran.statescreen, event.button.x, event.button.y)) {
				information.variable.continuer = false;
				return;
			}
			break;
		case STATEcitiemap:
			if (information.tabbutton[i]->searchButton((string)"Map", information.ecran.statescreen, event.button.x, event.button.y)) {
				information.variable.selectCitie = -1;
				information.ecran.statescreen = STATEmainmap;
				information.variable.select = selectnothing;
			}
			else if (information.tabbutton[i]->searchButton((string)"Build", information.ecran.statescreen, event.button.x, event.button.y)) {
				information.tabbutton[i]->changeOn();
				if (information.variable.select != selectcreate)
					information.variable.select = selectcreate;
				else
					information.variable.select = selectnothing;
			}
			else if (information.tabbutton[i]->searchButton((string)"Place Citizen", information.ecran.statescreen, event.button.x, event.button.y)) {
				information.tabbutton[i]->changeOn();
				if (information.variable.select != selectmoveCitizen)
					information.variable.select = selectmoveCitizen;
				else
					information.variable.select = selectnothing;
			}
			if (information.variable.select == selectcreate){
				for (unsigned int j = 0; j < information.variable.unitNameMaxToCreate; j++){
					if (information.tabbutton[i]->searchButton(information.variable.s_tabUnitAndSpec[j].name, information.ecran.statescreen, event.button.x, event.button.y)) {
						information.variable.toBuild = information.variable.s_tabUnitAndSpec[j].name;
						tabplayer[information.variable.selectplayer]->addUnit(information.variable.s_tabUnitAndSpec[j].name,
							tabplayer[information.variable.selectplayer]->GETthecitie(information.variable.selectCitie)->GETx(),
							tabplayer[information.variable.selectplayer]->GETthecitie(information.variable.selectCitie)->GETy(),
							information.variable.s_tabUnitAndSpec[j].life, information.variable.s_tabUnitAndSpec[j].atq,
							information.variable.s_tabUnitAndSpec[j].def, information.variable.s_tabUnitAndSpec[j].movement,
							information.variable.s_tabUnitAndSpec[j].level);

						information.variable.select = selectnothing;
						break;
					}
				}
			}
			for (unsigned int l = 0; l < information.tabbutton.size(); l++)
				information.tabbutton[l]->resetOnStatescreen(information.variable.select, selectnothing);
			break;
		}
	}	
}

void cliqueDroit(sysinfo& information, std::vector<Player*>& tabplayer, SDL_Event event){
	unsigned int selectunit = 0;
	information.variable.mouse_x = (unsigned int)ceil(event.button.x / tileSize) * tileSize;
	information.variable.mouse_y = (unsigned int)ceil(event.button.y / tileSize) * tileSize;
	if (information.variable.selectplayer > -1) {
		switch (information.ecran.statescreen){
		case STATEmainmap :
			switch (information.variable.select){
			case selectcreate:
				for (unsigned int p = 0; p < information.variable.unitNameMaxToCreate; p++){
					if (information.variable.unitNameToCreate.compare(information.variable.s_tabUnitAndSpec[p].name) == 0){
						selectunit = p;
						break;
					}
				}
				tabplayer[information.variable.selectplayer]->addUnit(information.variable.unitNameToCreate,
					information.variable.mouse_x, information.variable.mouse_y,
					information.variable.s_tabUnitAndSpec[selectunit].life, information.variable.s_tabUnitAndSpec[selectunit].atq,
					information.variable.s_tabUnitAndSpec[selectunit].def, information.variable.s_tabUnitAndSpec[selectunit].movement,
					information.variable.s_tabUnitAndSpec[selectunit].level);
				break;
			case selectmove:
				if (tabplayer[information.variable.selectplayer]->GETtabunit().size() != 0) {
					searchUnitTile(information, tabplayer);
					logfileconsole("Unit select to move n:" + to_string(information.variable.selectunit));
				}
				break;
			case selectinspect:
				if (tabplayer[information.variable.selectplayer]->GETtabunit().size() != 0) {
					searchUnitTile(information, tabplayer);
					logfileconsole("Unit select to move n:" + to_string(information.variable.selectunit));
				}
				break;
			}
			break;
		}
	}
}
void wheel(sysinfo& information, int& wheel){
	if (information.variable.select == selectcreate){
		if (wheel == 1){
			if (information.variable.unitToCreate > 0)
				information.variable.unitToCreate--;
		}
		else if (wheel == -1){
			if (information.variable.unitToCreate < information.variable.unitNameMaxToCreate - 1)
				information.variable.unitToCreate++;
		}
		searchunit(information);
	}
}
