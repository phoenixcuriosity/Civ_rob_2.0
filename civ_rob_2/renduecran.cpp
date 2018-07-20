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

#include "renduecran.h"
#include "sdl.h"
#include "mainLoop.h"

using namespace std;

void ecrantitre(sysinfo& information){
	/*
	
		affiche toutes les textures ainsi que les boutons ayant l'attribut _statescreen == STATEecrantitre

	*/
	logfileconsole("_Ecrantitres Start_");
	
	information.ecran.statescreen = STATEecrantitre;
	SDL_RenderClear(information.ecran.renderer);

	for (unsigned int i = 0; i < information.allTextures.tabTexture.size(); i++)
		information.allTextures.tabTexture[i]->renderTextureTestStates(information.ecran.renderer, information.ecran.statescreen, information.variable.select);
	for (unsigned int i = 0; i < information.tabbutton.size(); i++)
		information.tabbutton[i]->renderButton(information.ecran.renderer, information.ecran.statescreen);
	
	
	SDL_RenderPresent(information.ecran.renderer);
	logfileconsole("_Ecrantitres End_");
}

void alwaysrender(sysinfo& information, vector<Player*>& tabplayer){
	//clock_t t1, t2;
	//t1 = clock();

	switch (information.ecran.statescreen){
	case STATEmainmap:
		SDL_RenderClear(information.ecran.renderer);
		afficherSuperTiles(information);

		// affiche la texture grise de la toolbar
		for (unsigned int i = 0; i < toolBarSize; i++){
			for (int j = 0; j < SCREEN_HEIGHT / tileSize; j++)
				information.allTextures.tabTexture[3]->renderTexture(information.ecran.renderer, i * tileSize, j * tileSize);
		}

		for (unsigned int i = 0; i < information.tabbutton.size(); i++)
			information.tabbutton[i]->renderButton(information.ecran.renderer, information.ecran.statescreen);



		writetxt(information, to_string(information.variable.nbturn), { 0, 64, 255, 255 }, 24, 80, 850);

		// affiche les unités pour rendre l'unité à créer
		if (information.variable.select == selectcreate) {
			for (unsigned int i = information.allTextures.indexEndSpecStartUnit; i < information.allTextures.indexEndUnitStartBarLife; i++)
				information.allTextures.tabTexture[i]->renderTextureTestString(information.ecran.renderer, information.variable.unitNameToCreate);
		}

		// affiche tous les textes selectionnés
		for (unsigned int i = information.allTextures.indexEndMiscTextureStartWrite; i < information.allTextures.tabTexture.size(); i++) {
			information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Select:", information.ecran.statescreen);
			information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Turn :", information.ecran.statescreen);

			switch (information.variable.select){
			case selectnothing:
				information.allTextures.tabTexture[i]->renderTextureTestString(information.ecran.renderer, "selectnothing");
				break;
			case selectcreate:
				information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Scroll up or down", information.ecran.statescreen);
				information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Right click to create", information.ecran.statescreen);
				information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "create : ", information.ecran.statescreen);
				information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "selectcreate", information.ecran.statescreen);
				information.allTextures.tabTexture[i]->renderTextureTestString(information.ecran.renderer, information.variable.unitNameToCreate);
				break;
			case selectmove:
				information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Pick the unit to move", information.ecran.statescreen);
				information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "with Right click", information.ecran.statescreen);
				information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "selectmove", information.ecran.statescreen);
				if (information.variable.selectunit != -1)
					tabplayer[information.variable.selectplayer]->GETtheunit(information.variable.selectunit)->cmpblit();
				break;
			case selectinspect:
				information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Pick the unit to inspect", information.ecran.statescreen);
				information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "with Right click", information.ecran.statescreen);
				information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "selectinspect", information.ecran.statescreen);
				if (information.variable.selectunit != -1)
					tabplayer[information.variable.selectplayer]->GETtheunit(information.variable.selectunit)->afficherstat(information);
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
						for (unsigned int h = information.allTextures.indexEndBarLifeStartColorApp; h < information.allTextures.indexEndColorAppTileStartMiscTexture; h++)
							information.allTextures.tabTexture[h]->renderTextureTestString(information.ecran.renderer, "ColorPlayer" + to_string(i) + ".bmp", tabplayer[i]->GETtheunit(j)->GETx(), tabplayer[i]->GETtheunit(j)->GETy() + tileSize);
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
		if (tabplayer[information.variable.selectplayer]->GETtabcities().size() > 0) {
			if (information.variable.selectCitie != -1) {
				if (information.variable.selectCitie < (int)tabplayer[information.variable.selectplayer]->GETtabcities().size())
					citiemap(information, tabplayer);
			}
		}
		break;
	}
	writetxt(information, to_string(information.ecran.avgFPS), { 0, 64, 255, 255 }, 24, SCREEN_WIDTH / 2, 50, center_x);

	SDL_RenderPresent(information.ecran.renderer);
	//t2 = clock();
	//cout << endl << "temps d'execution de alwaysrender : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
}


void afficherSuperTiles(sysinfo& information) {
	int k = 0;

	for (int i = toolBarSize; i < SCREEN_WIDTH / tileSize; i++) {
		for (int j = 0; j < SCREEN_HEIGHT / tileSize; j++) {
			// attention tabtexture 0,1,2 sont réservés, à changer si nécessaire
			if (information.maps.tiles[k].tile_ground == grass)
				information.allTextures.tabTexture[0]->renderTexture(information.ecran.renderer, i * tileSize, j * tileSize);
			else if (information.maps.tiles[k].tile_ground == water)
				information.allTextures.tabTexture[1]->renderTexture(information.ecran.renderer, i * tileSize, j * tileSize);
			else if (information.maps.tiles[k].tile_ground == deepwater)
				information.allTextures.tabTexture[2]->renderTexture(information.ecran.renderer, i * tileSize, j * tileSize);


			if (information.maps.tiles[k].tile_spec != 0) {
				for (unsigned int l = information.allTextures.indexEndGroundStartSpec; l < information.allTextures.indexEndSpecStartUnit; l++)
					information.allTextures.tabTexture[l]->renderTextureTestString(information.ecran.renderer, information.maps.tiles[k].tile_stringspec, information.maps.tiles[k].tile_x, information.maps.tiles[k].tile_y);
			}
			if (information.maps.tiles[k].appartenance != -1) {
				for (unsigned int l = information.allTextures.indexEndColorAppStartColorAppTile; l < information.allTextures.indexEndColorAppTileStartMiscTexture; l++)
					information.allTextures.tabTexture[l]->renderTextureTestString(information.ecran.renderer, "ColorPlayerTile" + to_string(information.maps.tiles[k].appartenance) + ".bmp", information.maps.tiles[k].tile_x, information.maps.tiles[k].tile_y);
			}
			
			k++;
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

	for (unsigned int i = 0; i < information.tabbutton.size(); i++){
		if (information.tabbutton[i]->renderButtonTestString(information.ecran.renderer, information.ecran.statescreen, (string)"Map")){ i++; checkButton++; }
		if (information.tabbutton[i]->renderButtonTestString(information.ecran.renderer, information.ecran.statescreen, (string)"Build")){ i++; checkButton++; }
		if (information.tabbutton[i]->renderButtonTestString(information.ecran.renderer, information.ecran.statescreen, (string)"Food")){ i++; checkButton++; }
		if (information.tabbutton[i]->renderButtonTestString(information.ecran.renderer, information.ecran.statescreen, (string)"Place Citizen")){ i++; checkButton++; }

		if (information.variable.select == selectcreate){
			initspace = 96;
			for (unsigned int j = 0; j < 10; j++){
				if (information.variable.unitToCreate + j < information.variable.unitNameMaxToCreate)
					buildName = information.variable.s_tabUnitAndSpec[information.variable.unitToCreate + j].name;
				else
					break;
				if (information.tabbutton[i]->renderButtonTestString(information.ecran.renderer, information.ecran.statescreen, buildName, SCREEN_WIDTH / 2, initspace += space)){ i++; checkButton++; }
			}
		}
		if (checkButton == valid) break;
	}

	for (unsigned int i = information.allTextures.indexEndMiscTextureStartWrite; i < information.allTextures.tabTexture.size(); i++) {
		initspace = 96;
		switch (information.variable.select){
		case selectcreate:
			information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Scroll up or down", information.ecran.statescreen);
			information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Left click to Select", information.ecran.statescreen);
			information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "create : ", information.ecran.statescreen);
			information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, "selectcreate", information.ecran.statescreen);
			
			
			break;
		}
	}

	if (information.variable.select == selectcreate){
		for (unsigned int i = information.allTextures.indexEndSpecStartUnit; i < information.allTextures.indexEndUnitStartBarLife; i++){
			initspace = 96;
			for (unsigned int j = 0; j < 10; j++){
				if (information.variable.unitToCreate + j < information.variable.unitNameMaxToCreate)
					buildName = information.variable.s_tabUnitAndSpec[information.variable.unitToCreate + j].name;
				else
					break;
				information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer, buildName, STATEnothing, (SCREEN_WIDTH / 2) - 50, initspace += space);
			}
		}
		for (unsigned int i = information.allTextures.indexEndMiscTextureStartWrite; i < information.allTextures.tabTexture.size(); i++){
			initspace = 96;
			for (unsigned int j = 0; j < 10; j++){
				if (information.variable.unitToCreate + j < information.variable.unitNameMaxToCreate)
					buildName = information.variable.s_tabUnitAndSpec[information.variable.unitToCreate + j].name;
				else
					break;
				if (information.allTextures.tabTexture[i]->renderTextureTestStringAndStates(information.ecran.renderer,
					"life:" + to_string(information.variable.s_tabUnitAndSpec[information.variable.unitToCreate + j].life) +
					"/atq:" + to_string(information.variable.s_tabUnitAndSpec[information.variable.unitToCreate + j].atq) +
					"/def:" + to_string(information.variable.s_tabUnitAndSpec[information.variable.unitToCreate + j].def) +
					"/move:" + to_string(information.variable.s_tabUnitAndSpec[information.variable.unitToCreate + j].movement),
					information.ecran.statescreen, (SCREEN_WIDTH / 2) + 200, initspace += space)){
					checkBarre++;
					break;
				}
			}
			if (checkBarre == validBarreSpec) break;
		}
	}

	tabplayer[information.variable.selectplayer]->GETthecitie(information.variable.selectCitie)->affichercitiemap(information);
}
