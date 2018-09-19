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

#include "renduecran.h"
#include "initAndError.h"
#include "mainLoop.h"

using namespace std;

void ecrantitre(sysinfo& information){
	/*
	
		affiche toutes les textures ainsi que les boutons ayant l'attribut _statescreen == STATEecrantitre

	*/
	logfileconsole("_Ecrantitres Start_");
	
	information.variable.statescreen = STATEecrantitre;
	SDL_RenderClear(information.ecran.renderer);

	for (unsigned int i = 0; i < information.allTextures.txtecrantitre.size(); i++)
		information.allTextures.txtecrantitre[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen, information.variable.select);
	for (unsigned int i = 0; i < information.allButton.ecrantitre.size(); i++)
		information.allButton.ecrantitre[i]->renderButton(information.ecran.renderer, information.variable.statescreen);
	
	
	SDL_RenderPresent(information.ecran.renderer);
	logfileconsole("_Ecrantitres End_");
}

void reloadScreen(sysinfo& information) {
	logfileconsole("_reloadScreen Start_");
	information.variable.statescreen = STATEreload;
	SDL_RenderClear(information.ecran.renderer);

	for (unsigned int i = 0; i < information.allButton.reload.size(); i++)
		information.allButton.reload[i]->renderButton(information.ecran.renderer, information.variable.statescreen);


	SDL_RenderPresent(information.ecran.renderer);
	logfileconsole("_reloadScreen End_");
}

void alwaysrender(sysinfo& information, vector<Player*>& tabplayer){
	//clock_t t1, t2;
	//t1 = clock();

	switch (information.variable.statescreen){
	case STATEmainmap:
		SDL_RenderClear(information.ecran.renderer);
		afficherSuperTiles(information);

		// affiche la texture grise de la toolbar
		for (unsigned int i = 0; i < information.maps.toolBarSize; i++){
			for (unsigned int j = 0; j < SCREEN_HEIGHT / information.maps.tileSize; j++)
				information.allTextures.ground[3]->renderTexture(information.ecran.renderer, i * information.maps.tileSize, j * information.maps.tileSize);
		}

		for (unsigned int i = 0; i < information.allButton.mainmap.size(); i++)
			information.allButton.mainmap[i]->renderButton(information.ecran.renderer, information.variable.statescreen);
		for (unsigned int i = 0; i < information.allButton.player.size(); i++)
			information.allButton.player[i]->renderButton(information.ecran.renderer, information.variable.statescreen);



		Texture::writetxt(information, blended,to_string(information.variable.nbturn), { 0, 64, 255, 255 }, NoColor, 24, 80, 850);

		// affiche les unités pour rendre l'unité à créer
		if (information.variable.select == selectcreate) {
			for (unsigned int i = 0; i < information.allTextures.unit.size(); i++)
				information.allTextures.unit[i]->renderTextureTestString(information.ecran.renderer, information.variable.s_player.unitNameToCreate);
		}

		// affiche tous les textes selectionnés
		for (unsigned int i = 0; i < information.allTextures.txtmainmap.size(); i++) {
			information.allTextures.txtmainmap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Select:", information.variable.statescreen);
			information.allTextures.txtmainmap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Turn :", information.variable.statescreen);

			switch (information.variable.select){
			case selectnothing:
				information.allTextures.txtmainmap[i]->renderTextureTestString(information.ecran.renderer, "selectnothing");
				break;
			case selectcreate:
				information.allTextures.txtmainmap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Scroll up or down", information.variable.statescreen);
				information.allTextures.txtmainmap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Right click to create", information.variable.statescreen);
				information.allTextures.txtmainmap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "create : ", information.variable.statescreen);
				information.allTextures.txtmainmap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "selectcreate", information.variable.statescreen);
				information.allTextures.txtmainmap[i]->renderTextureTestString(information.ecran.renderer, information.variable.s_player.unitNameToCreate);
				break;
			case selectmove:
				information.allTextures.txtmainmap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Pick the unit to move", information.variable.statescreen);
				information.allTextures.txtmainmap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "with Right click", information.variable.statescreen);
				information.allTextures.txtmainmap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "selectmove", information.variable.statescreen);
				if (information.variable.s_player.selectunit != -1)
					tabplayer[information.variable.s_player.selectplayer]->GETtheunit(information.variable.s_player.selectunit)->cmpblit();
				break;
			case selectinspect:
				information.allTextures.txtmainmap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Pick the unit to inspect", information.variable.statescreen);
				information.allTextures.txtmainmap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "with Right click", information.variable.statescreen);
				information.allTextures.txtmainmap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "selectinspect", information.variable.statescreen);
				if (information.variable.s_player.selectunit != -1)
					tabplayer[information.variable.s_player.selectplayer]->GETtheunit(information.variable.s_player.selectunit)->afficherstat(information);
				break;
			}
		}

		if (tabplayer.size() != 0){
			for (unsigned int i = 0; i < tabplayer.size(); i++){
				if (tabplayer[i]->GETtabunit().size() != 0){
					for (unsigned int j = 0; j < tabplayer[i]->GETtabunit().size(); j++){
						// affiche pour chaque joueurs les unités existantes (avec les stats)
						tabplayer[i]->GETtheunit(j)->afficher(information);
						tabplayer[i]->GETtheunit(j)->afficherBardeVie(information);
						for (unsigned int h = 0; h < information.allTextures.colorapp.size(); h++)
							information.allTextures.colorapp[h]->renderTextureTestString(information.ecran.renderer, "ColorPlayer" + to_string(i) + ".bmp", tabplayer[i]->GETtheunit(j)->GETx(), tabplayer[i]->GETtheunit(j)->GETy() + information.maps.tileSize);
					}
				}
				if (tabplayer[i]->GETtabcities().size() != 0) {
					for (unsigned int j = 0; j < tabplayer[i]->GETtabcities().size(); j++) {
						// affiche pour chaque joueurs les cités existantes
						tabplayer[i]->GETthecitie(j)->afficher(information);
					}
				}
			}
		}
		break;
	case STATEcitiemap:
		if (tabplayer[information.variable.s_player.selectplayer]->GETtabcities().size() > 0) {
			if (information.variable.s_player.selectCitie != -1) {
				if (information.variable.s_player.selectCitie < (int)tabplayer[information.variable.s_player.selectplayer]->GETtabcities().size())
					citiemap(information, tabplayer);
			}
		}
		break;
	}
	Texture::writetxt(information, blended, to_string(information.ecran.avgFPS), { 0, 64, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 50, center_x);

	SDL_RenderPresent(information.ecran.renderer);
	//t2 = clock();
	//cout << endl << "temps d'execution de alwaysrender : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
}


void afficherSuperTiles(sysinfo& information) {
	for (unsigned int i = 0; i < information.maps.screen.size(); i++) {
		// attention tabtexture 0,1,2 sont réservés, à changer si nécessaire
		if (information.maps.screen[i].tile_ground == grass)
			information.allTextures.ground[0]->renderTexture(information.ecran.renderer, information.maps.screen[i].tile_x, information.maps.screen[i].tile_y);
		else if (information.maps.screen[i].tile_ground == water)
			information.allTextures.ground[1]->renderTexture(information.ecran.renderer, information.maps.screen[i].tile_x, information.maps.screen[i].tile_y);
		else if (information.maps.screen[i].tile_ground == deepwater)
				information.allTextures.ground[2]->renderTexture(information.ecran.renderer, information.maps.screen[i].tile_x, information.maps.screen[i].tile_y);

		if (information.maps.screen[i].tile_spec != 0) {
			for (unsigned int l = 0; l < information.allTextures.groundSpec.size(); l++)
				information.allTextures.groundSpec[l]->renderTextureTestString(information.ecran.renderer, information.maps.screen[i].tile_stringspec, information.maps.screen[i].tile_x, information.maps.screen[i].tile_y);
		}
		if (information.maps.screen[i].appartenance != -1) {
			for (unsigned int l = 0; l < information.allTextures.colorappTile.size(); l++)
				information.allTextures.colorappTile[l]->renderTextureTestString(information.ecran.renderer, "ColorPlayerTile" + to_string(information.maps.screen[i].appartenance) + ".bmp", information.maps.screen[i].tile_x, information.maps.screen[i].tile_y);
		}
			
	}
}


void citiemap(sysinfo& information, std::vector<Player*>& tabplayer) {
	SDL_RenderClear(information.ecran.renderer);
	string buildName;
	unsigned int initspace = 96, space = 32;
	unsigned int valid = 12, checkButton = 0; // optimisation de la boucle for 
	unsigned int validBarreSpec = 10, checkBarre = 0;

	if (information.variable.select != selectcreate)
		valid = 2;

	for (unsigned int i = 0; i < information.allButton.citie.size(); i++){
		if (information.allButton.citie[i]->renderButtonTestString(information.ecran.renderer, information.variable.statescreen, (string)"Map")){ i++; checkButton++; }
		if (information.allButton.citie[i]->renderButtonTestString(information.ecran.renderer, information.variable.statescreen, (string)"Build")){ i++; checkButton++; }
		if (information.allButton.citie[i]->renderButtonTestString(information.ecran.renderer, information.variable.statescreen, (string)"Food")){ i++; checkButton++; }
		if (information.allButton.citie[i]->renderButtonTestString(information.ecran.renderer, information.variable.statescreen, (string)"Place Citizen")){ i++; checkButton++; }

		if (information.variable.select == selectcreate){
			initspace = 96;
			for (unsigned int j = 0; j < 10; j++){
				if (information.variable.s_player.unitToCreate + j < information.variable.s_player.unitNameMaxToCreate)
					buildName = information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate + j].name;
				else
					break;
				if (information.allButton.citie[i]->renderButtonTestString(information.ecran.renderer, information.variable.statescreen, buildName, SCREEN_WIDTH / 2, initspace += space)){ i++; checkButton++; }
			}
		}
		if (checkButton == valid) break;
	}

	for (unsigned int i = 0; i < information.allTextures.txtcitiemap.size(); i++) {
		initspace = 96;
		switch (information.variable.select){
		case selectcreate:
			information.allTextures.txtcitiemap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Scroll up or down", information.variable.statescreen);
			information.allTextures.txtcitiemap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Left click to Select", information.variable.statescreen);
			information.allTextures.txtcitiemap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "create : ", information.variable.statescreen);
			information.allTextures.txtcitiemap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "selectcreate", information.variable.statescreen);
			break;
		}
	}

	if (information.variable.select == selectcreate){
		for (unsigned int i = 0; i < information.allTextures.unit.size(); i++){
			initspace = 96;
			for (unsigned int j = 0; j < 10; j++){
				if (information.variable.s_player.unitToCreate + j < information.variable.s_player.unitNameMaxToCreate)
					buildName = information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate + j].name;
				else
					break;
				information.allTextures.unit[i]->renderTextureTestStringAndStates(information.ecran.renderer, buildName, STATEnothing, (SCREEN_WIDTH / 2) - 50, initspace += space);
			}
		}
		for (unsigned int i = 0; i < information.allTextures.txtcitiemap.size(); i++){
			initspace = 96;
			for (unsigned int j = 0; j < 10; j++){
				if (information.variable.s_player.unitToCreate + j < information.variable.s_player.unitNameMaxToCreate)
					buildName = information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate + j].name;
				else
					break;
				if (information.allTextures.txtcitiemap[i]->renderTextureTestStringAndStates(information.ecran.renderer,
					"life:" + to_string(information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate + j].life) +
					"/atq:" + to_string(information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate + j].atq) +
					"/def:" + to_string(information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate + j].def) +
					"/move:" + to_string(information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate + j].movement),
					information.variable.statescreen, (SCREEN_WIDTH / 2) + 200, initspace += space)){
					checkBarre++;
					break;
				}
			}
			if (checkBarre == validBarreSpec) break;
		}
	}

	tabplayer[information.variable.s_player.selectplayer]->GETthecitie(information.variable.s_player.selectCitie)->affichercitiemap(information);
}
