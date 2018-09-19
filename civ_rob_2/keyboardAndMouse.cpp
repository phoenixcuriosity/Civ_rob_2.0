/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.11

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

#include "keyboardAndMouse.h"
#include "renduecran.h"
#include "unit.h"
#include "citie.h"
#include "initAndError.h"

using namespace std;

void cinDigit(sysinfo& information, unsigned int& digit, unsigned int x, unsigned int& y){
	bool continuer = true;
	SDL_Event event;
	int SDL_EnableUNICODE(1);

	while (continuer)
	{
		SDL_WaitEvent(&event); // attente d'un événement (clavier, souris)
		switch (event.type) // test sur le type d'événement
		{
		case SDL_QUIT:	// permet de quitter le jeu
			SDL_Quit();
			break;
		case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
			switch (event.key.keysym.sym){
			case SDLK_ESCAPE:
				if (digit == 0)
					digit = 1;
				continuer = false;
				break;
			case SDLK_RETURN:
				if (digit == 0)
					digit = 1;
				continuer = false;
				break;
			case SDLK_KP_ENTER:
				if (digit == 0)
					digit = 1;
				continuer = false;
				break;
			case SDLK_1:
				digit = 1;
				break;
			case SDLK_2:
				digit = 2;
				break;
			case SDLK_3:
				digit = 3;
				break;
			case SDLK_4:
				digit = 4;
				break;
			case SDLK_5:
				digit = 5;
				break;
			case SDLK_6:
				digit = 6;
				break;
			case SDLK_7:
				digit = 7;
				break;
			case SDLK_8:
				digit = 8;
				break;
			case SDLK_9:
				digit = 9;
				break;
			case SDLK_KP_1:
				digit = 1;
				break;
			case SDLK_KP_2:
				digit = 2;
				break;
			case SDLK_KP_3:
				digit = 3;
				break;
			case SDLK_KP_4:
				digit = 4;
				break;
			case SDLK_KP_5:
				digit = 5;
				break;
			case SDLK_KP_6:
				digit = 6;
				break;
			case SDLK_KP_7:
				digit = 7;
				break;
			case SDLK_KP_8:
				digit = 8;
				break;
			case SDLK_KP_9:
				digit = 9;
				break;
			}
			Texture::writetxt(information, shaded, "Number of player(s)" + to_string(digit), { 255, 127, 127, 255 }, { 64, 64, 64, 255 }, 24, x, y, center_x);
			SDL_RenderPresent(information.ecran.renderer);
			break;
		}
	}
}

void cinAlphabet(sysinfo& information, std::string &name, unsigned int initx, unsigned int& y){
	bool continuer = true;
	SDL_Event event;
	int SDL_EnableUNICODE(1);
	unsigned int xspace = 12;

	while (continuer)
	{
		SDL_WaitEvent(&event); // attente d'un événement (clavier, souris)
		switch (event.type) // test sur le type d'événement
		{
		case SDL_QUIT:	// permet de quitter le jeu
			SDL_Quit();
			break;
		case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
			switch (event.key.keysym.sym){
			case SDLK_ESCAPE:
				if (name.compare("") == 0) {
					name = "NoName" + to_string(information.variable.s_player.nbNoNamePlayer);
					information.variable.s_player.nbNoNamePlayer++;
				}
				continuer = false;
				break;
			case SDLK_BACKSPACE:
				if (name.compare("") != 0)
					name.pop_back();
				break;
			case SDLK_RETURN:
				if (name.compare("") == 0) {
					name = "NoName" + to_string(information.variable.s_player.nbNoNamePlayer);
					information.variable.s_player.nbNoNamePlayer++;
				}
				continuer = false;
				break;
			case SDLK_KP_ENTER:
				if (name.compare("") == 0) {
					name = "NoName" + to_string(information.variable.s_player.nbNoNamePlayer);
					information.variable.s_player.nbNoNamePlayer++;
				}
				continuer = false;
				break;
			case SDLK_a:
				name = name + 'a';
				break;
			case SDLK_b:
				name = name + 'b';
				break;
			case SDLK_c:
				name = name + 'c';
				break;
			case SDLK_d:
				name = name + 'd';
				break;
			case SDLK_e:
				name = name + 'e';
				break;
			case SDLK_f:
				name = name + 'f';
				break;
			case SDLK_g:
				name = name + 'g';
				break;
			case SDLK_h:
				name = name + 'h';
				break;
			case SDLK_i:
				name = name + 'i';
				break;
			case SDLK_j:
				name = name + 'j';
				break;
			case SDLK_k:
				name = name + 'k';
				break;
			case SDLK_l:
				name = name + 'l';
				break;
			case SDLK_m:
				name = name + 'm';
				break;
			case SDLK_n:
				name = name + 'n';
				break;
			case SDLK_o:
				name = name + 'o';
				break;
			case SDLK_p:
				name = name + 'p';
				break;
			case SDLK_q:
				name = name + 'q';
				break;
			case SDLK_r:
				name = name + 'r';
				break;
			case SDLK_s:
				name = name + 's';
				break;
			case SDLK_t:
				name = name + 't';
				break;
			case SDLK_u:
				name = name + 'u';
				break;
			case SDLK_v:
				name = name + 'v';
				break;
			case SDLK_w:
				name = name + 'w';
				break;
			case SDLK_x:
				name = name + 'x';
				break;
			case SDLK_y:
				name = name + 'y';
				break;
			case SDLK_z:
				name = name + 'z';
				break;
			case SDLK_1:
				name = name + "1";
				break;
			case SDLK_2:
				name = name + "2";
				break;
			case SDLK_3:
				name = name + "3";
				break;
			case SDLK_4:
				name = name + "4";
				break;
			case SDLK_5:
				name = name + "5";
				break;
			case SDLK_6:
				name = name + "6";
				break;
			case SDLK_7:
				name = name + "7";
				break;
			case SDLK_8:
				name = name + "8";
				break;
			case SDLK_9:
				name = name + "9";
				break;
			case SDLK_KP_1:
				name = name + "1";
				break;
			case SDLK_KP_2:
				name = name + "2";
				break;
			case SDLK_KP_3:
				name = name + "3";
				break;
			case SDLK_KP_4:
				name = name + "4";
				break;
			case SDLK_KP_5:
				name = name + "5";
				break;
			case SDLK_KP_6:
				name = name + "6";
				break;
			case SDLK_KP_7:
				name = name + "7";
				break;
			case SDLK_KP_8:
				name = name + "8";
				break;
			case SDLK_KP_9:
				name = name + "9";
				break;
			}
			if (name.size() > 50){
				name = "par_defaut";
				logfileconsole("cinAlphabet ERROR : Name to long > 50 char");
			}
			Texture::writetxt(information, shaded, name, { 255, 127, 127, 255 }, { 64, 64, 64, 255 }, 24, initx + xspace, y, center_x);
			SDL_RenderPresent(information.ecran.renderer);
			break;
		}
	}
}


void keySDLK_b(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.variable.statescreen == STATEmainmap && information.variable.select == selectmove)
		createcitie(information, tabplayer);
}
void keySDLK_i(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.variable.statescreen == STATEmainmap && information.variable.select == selectmove)
		irrigate(information, tabplayer);
}

void keySDLK_KP_1(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.variable.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, -(int)(information.maps.tileSize), information.maps.tileSize);
}
void keySDLK_KP_2(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.variable.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, 0, information.maps.tileSize);
}
void keySDLK_KP_3(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.variable.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, information.maps.tileSize, information.maps.tileSize);
}
void keySDLK_KP_4(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.variable.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, -(int)(information.maps.tileSize), 0);
}
void keySDLK_KP_5(sysinfo& information, vector<Player*>& tabplayer) {

}
void keySDLK_KP_6(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.variable.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, information.maps.tileSize, 0);
}
void keySDLK_KP_7(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.variable.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, -(int)(information.maps.tileSize), -(int)(information.maps.tileSize));
}
void keySDLK_KP_8(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.variable.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, 0, -(int)(information.maps.tileSize));
}
void keySDLK_KP_9(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.variable.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, information.maps.tileSize, -(int)(information.maps.tileSize));
}



void mouse(sysinfo& information, vector<Player*>& tabplayer, SDL_Event event) {
	/*

		Handle Mouse Event
		BUTTON_LEFT
		BUTTON_RIGHT

	*/

	if (event.button.button == SDL_BUTTON_LEFT)
		cliqueGauche(information, tabplayer, event);
	else if (event.button.button == SDL_BUTTON_RIGHT && information.variable.statescreen == STATEmainmap)
		cliqueDroit(information, tabplayer, event);

}
void cliqueGauche(sysinfo& information, std::vector<Player*>& tabplayer, SDL_Event event) {
	// inspect citie
	if (information.variable.statescreen == STATEmainmap) {
		if (information.variable.s_player.selectplayer > -1) {
			if (information.variable.select == selectinspect && tabplayer[information.variable.s_player.selectplayer]->GETtabcities().size() != 0) {
				information.variable.s_wheel.mouse_x = (unsigned int)ceil(event.button.x / information.maps.tileSize) * information.maps.tileSize;
				information.variable.s_wheel.mouse_y = (unsigned int)ceil(event.button.y / information.maps.tileSize) * information.maps.tileSize;
				searchCitieTile(information, tabplayer);
			}
		}
	}
	// recherche du bouton par comparaison de string et des positions x et y du clic

	switch (information.variable.statescreen) {
	case STATEmainmap:
		for (unsigned int i = 0; i < information.allButton.mainmap.size(); i++) {
			if (information.allButton.mainmap[i]->searchButton((string)"Ecran Titre", information.variable.statescreen, event.button.x, event.button.y)) {
				savemaps(information);
				savePlayer(information, tabplayer);
				logfileconsole("__________________________");
				ecrantitre(information);
			}
			else if (information.allButton.mainmap[i]->searchButton((string)"Create Unit", information.variable.statescreen, event.button.x, event.button.y)) {
				information.allButton.mainmap[i]->changeOn();
				if (information.variable.select != selectcreate)
					information.variable.select = selectcreate;
				else
					information.variable.select = selectnothing;
			}
			else if (information.allButton.mainmap[i]->searchButton((string)"Move Unit", information.variable.statescreen, event.button.x, event.button.y)) {
				information.allButton.mainmap[i]->changeOn();
				if (information.variable.select != selectmove)
					information.variable.select = selectmove;
				else {
					information.variable.s_player.selectunit = -1;
					information.variable.select = selectnothing;
				}
			}
			else if (information.allButton.mainmap[i]->searchButton((string)"Inspect", information.variable.statescreen, event.button.x, event.button.y)) {
				information.allButton.mainmap[i]->changeOn();
				if (information.variable.select != selectinspect)
					information.variable.select = selectinspect;
				else {
					information.variable.s_player.selectunit = -1;
					information.variable.select = selectnothing;
				}
			}
			else if (information.allButton.mainmap[i]->searchButton((string)"Next Turn", information.variable.statescreen, event.button.x, event.button.y)) {
				nextTurn(information, tabplayer);
			}
			else if (information.allButton.mainmap[i]->searchButton((string)"Delete Unit", information.variable.statescreen, event.button.x, event.button.y)) {
				information.allButton.mainmap[i]->SETon(!information.allButton.mainmap[i]->GETon());
			}

	
			// reset de l'affichage On des boutons
			for (unsigned int l = 0; l < information.allButton.mainmap.size(); l++) {
				information.allButton.mainmap[l]->resetOnStatescreen(information.variable.select, selectnothing);
				information.allButton.mainmap[l]->resetOnPlayer(information.variable.s_player.selectplayer, information.variable.s_player.tabPlayerName);
			}
		}
		for (unsigned int i = 0; i < information.allButton.player.size(); i++) {
			// player select
			for (unsigned int l = 0; l < tabplayer.size(); l++) {
				if (information.allButton.player[i]->searchButton((string)tabplayer[l]->GETname(), information.variable.statescreen, event.button.x, event.button.y)) {
					information.allButton.player[i]->changeOn();
					if (information.variable.s_player.selectplayer != l)
						information.variable.s_player.selectplayer = l;
					else
						information.variable.s_player.selectplayer = -1;
					logfileconsole("information.variable.selectplayer = " + tabplayer[l]->GETname());
					break;
				}
			}
			for (unsigned int l = 0; l < information.allButton.player.size(); l++) {
				information.allButton.player[l]->resetOnStatescreen(information.variable.select, selectnothing);
				information.allButton.player[l]->resetOnPlayer(information.variable.s_player.selectplayer, information.variable.s_player.tabPlayerName);
			}
		}
		break;
	case STATEecrantitre:
		for (unsigned int i = 0; i < information.allButton.ecrantitre.size(); i++) {
			if (information.allButton.ecrantitre[i]->searchButton((string)"New Game", information.variable.statescreen, event.button.x, event.button.y)) {
				newgame(information, tabplayer);
				return;
			}
			else if (information.allButton.ecrantitre[i]->searchButton((string)"Reload", information.variable.statescreen, event.button.x, event.button.y)) {
				reloadScreen(information);
				return;
			}
			else if (information.allButton.ecrantitre[i]->searchButton((string)"Option", information.variable.statescreen, event.button.x, event.button.y)) {
				//clearSave(information);
				return;
			}
			else if (information.allButton.ecrantitre[i]->searchButton((string)"Quit", information.variable.statescreen, event.button.x, event.button.y)) {
				information.variable.continuer = false;
				return;
			}
		}
		break;
	case STATEreload:
		for (unsigned int i = 0; i < information.allButton.reload.size(); i++) {
			if (information.allButton.reload[i]->searchButton((string)"Back", information.variable.statescreen, event.button.x, event.button.y)) {
				ecrantitre(information);
				return;
			}
			else if (information.allButton.reload[i]->searchButton((string)"Remove all saves", information.variable.statescreen, event.button.x, event.button.y)) {
				information.allButton.reload[i]->changeOn();
				clearSave(information);
				reloadScreen(information);
				return;
			}
			else if (information.allButton.reload[i]->searchButton((string)"Load", information.variable.statescreen, event.button.x, event.button.y)) {
				reload(information, tabplayer);
				return;
			}
			else if (information.allButton.reload[i]->searchButton((string)"Remove", information.variable.statescreen, event.button.x, event.button.y)) {
				removeSave(information);
				reloadScreen(information);
				return;
			}
			else {
				for (unsigned int j = 0; j < information.variable.s_save.nbSave; j++) {
					if (information.allButton.reload[i]->searchButton((string)"Save : " + to_string(information.variable.s_save.tabSave[j]), information.variable.statescreen, event.button.x, event.button.y)) {
						information.allButton.reload[i]->changeOn();
						information.variable.s_save.currentSave = information.variable.s_save.tabSave[j];
						information.file.Savemaps = "save/" + to_string(information.variable.s_save.tabSave[j]) + "/Savemaps.txt";
						information.file.SavePlayer = "save/" + to_string(information.variable.s_save.tabSave[j]) + "/SavePlayer.txt";
						reloadScreen(information);
						return;
					}
				}
			}
		}
		break;
	case STATEcitiemap:
		for (unsigned int i = 0; i < information.allButton.citie.size(); i++) {
			if (information.allButton.citie[i]->searchButton((string)"Map", information.variable.statescreen, event.button.x, event.button.y)) {
				information.variable.s_player.selectCitie = -1;
				information.variable.statescreen = STATEmainmap;
				information.variable.select = selectnothing;
			}
			else if (information.allButton.citie[i]->searchButton((string)"Build", information.variable.statescreen, event.button.x, event.button.y)) {
				information.allButton.citie[i]->changeOn();
				if (information.variable.select != selectcreate)
					information.variable.select = selectcreate;
				else
					information.variable.select = selectnothing;
			}
			else if (information.allButton.citie[i]->searchButton((string)"Place Citizen", information.variable.statescreen, event.button.x, event.button.y)) {
				information.allButton.citie[i]->changeOn();
				if (information.variable.select != selectmoveCitizen)
					information.variable.select = selectmoveCitizen;
				else
					information.variable.select = selectnothing;
			}
			if (information.variable.select == selectcreate) {
				for (unsigned int j = 0; j < information.variable.s_player.unitNameMaxToCreate; j++) {
					if (information.allButton.citie[i]->searchButton(information.variable.s_player.s_tabUnitAndSpec[j].name, information.variable.statescreen, event.button.x, event.button.y)) {
						information.variable.s_player.toBuild = information.variable.s_player.s_tabUnitAndSpec[j].name;
						tabplayer[information.variable.s_player.selectplayer]->addUnit(information.variable.s_player.s_tabUnitAndSpec[j].name,
							tabplayer[information.variable.s_player.selectplayer]->GETthecitie(information.variable.s_player.selectCitie)->GETx(),
							tabplayer[information.variable.s_player.selectplayer]->GETthecitie(information.variable.s_player.selectCitie)->GETy(),
							information.variable.s_player.s_tabUnitAndSpec[j].life, information.variable.s_player.s_tabUnitAndSpec[j].atq,
							information.variable.s_player.s_tabUnitAndSpec[j].def, information.variable.s_player.s_tabUnitAndSpec[j].movement,
							information.variable.s_player.s_tabUnitAndSpec[j].level);

						information.variable.select = selectnothing;
						break;
					}
				}
			}
		}
		for (unsigned int l = 0; l < information.allButton.citie.size(); l++)
			information.allButton.citie[l]->resetOnStatescreen(information.variable.select, selectnothing);
		break;
	}
}

void cliqueDroit(sysinfo& information, std::vector<Player*>& tabplayer, SDL_Event event) {
	unsigned int selectunit = 0;
	information.variable.s_wheel.mouse_x = (unsigned int)ceil(event.button.x / information.maps.tileSize) * information.maps.tileSize;
	information.variable.s_wheel.mouse_y = (unsigned int)ceil(event.button.y / information.maps.tileSize) * information.maps.tileSize;
	if (information.variable.s_player.selectplayer > -1) {
		switch (information.variable.statescreen) {
		case STATEmainmap:
			switch (information.variable.select) {
			case selectcreate:
				for (unsigned int p = 0; p < information.variable.s_player.unitNameMaxToCreate; p++) {
					if (information.variable.s_player.unitNameToCreate.compare(information.variable.s_player.s_tabUnitAndSpec[p].name) == 0) {
						selectunit = p;
						break;
					}
				}
				tabplayer[information.variable.s_player.selectplayer]->addUnit(information.variable.s_player.unitNameToCreate,
					information.variable.s_wheel.mouse_x, information.variable.s_wheel.mouse_y,
					information.variable.s_player.s_tabUnitAndSpec[selectunit].life, information.variable.s_player.s_tabUnitAndSpec[selectunit].atq,
					information.variable.s_player.s_tabUnitAndSpec[selectunit].def, information.variable.s_player.s_tabUnitAndSpec[selectunit].movement,
					information.variable.s_player.s_tabUnitAndSpec[selectunit].level);
				break;
			case selectmove:
				if (tabplayer[information.variable.s_player.selectplayer]->GETtabunit().size() != 0) {
					searchUnitTile(information, tabplayer);
					logfileconsole("Unit select to move n:" + to_string(information.variable.s_player.selectunit));
				}
				break;
			case selectinspect:
				if (tabplayer[information.variable.s_player.selectplayer]->GETtabunit().size() != 0) {
					searchUnitTile(information, tabplayer);
					logfileconsole("Unit select to move n:" + to_string(information.variable.s_player.selectunit));
				}
				break;
			}
			break;
		}
	}
}
void wheel(sysinfo& information, int& wheel) {
	if (information.variable.select == selectcreate) {
		if (wheel == 1) {
			if (information.variable.s_player.unitToCreate > 0)
				information.variable.s_player.unitToCreate--;
		}
		else if (wheel == -1) {
			if (information.variable.s_player.unitToCreate < information.variable.s_player.unitNameMaxToCreate - 1)
				information.variable.s_player.unitToCreate++;
		}
		searchunit(information);
	}
	/*
	else if (information.variable.statescreen == STATEreload) {
		if (wheel == 1) {
			if (information.variable.currentSave > 0)
				information.variable.currentSave--;
		}
		else if (wheel == -1) {
			if (information.variable.currentSave < information.variable.nbSave)
				information.variable.currentSave++;
		}
	}
	*/
}