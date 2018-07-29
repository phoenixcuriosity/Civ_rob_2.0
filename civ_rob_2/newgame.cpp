/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.8

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

#include "newgame.h"

#include "unit.h"
#include "saveAndReload.h"
#include "keyboardAndMouse.h"
#include "initAndError.h"

using namespace std;

void newgame(sysinfo& information, vector<Player*>& tabplayer){
	logfileconsole("_Newgame Start_");
	information.variable.statescreen = STATEecrannewgame;

	unsigned int nbplayer = 0, initspace = 132, space = 32;

	createSave(information);

	SDL_RenderClear(information.ecran.renderer);

	for (unsigned int i = 0; i < information.allTextures.tabTexture.size(); i++) {
		information.allTextures.tabTexture[i]->renderTextureTestString(information.ecran.renderer, "Press Return or kpad_Enter to valid selection");
		information.allTextures.tabTexture[i]->renderTextureTestString(information.ecran.renderer, "How many player(s) (max 9):");
	}
	SDL_RenderPresent(information.ecran.renderer);
	cinDigit(information, nbplayer, SCREEN_WIDTH / 2, initspace += space);

	for (unsigned int i = 1; i < nbplayer + 1; i++){
		information.variable.s_player.tabPlayerName.push_back("");
		writetxt(information, "Name of player nb:" + to_string(i), { 255, 0, 0, 255 }, 24, SCREEN_WIDTH / 2, initspace += space, center_x);
		SDL_RenderPresent(information.ecran.renderer);
		cinAlphabet(information, information.variable.s_player.tabPlayerName[i - 1], SCREEN_WIDTH / 2, initspace += space);
		tabplayer.push_back(new Player(information.variable.s_player.tabPlayerName[i - 1]));
	}
	groundgen(information);
	newGameSettlerSpawn(information, tabplayer);
	savemaps(information);
	savePlayer(information, tabplayer);
	
	int initspacename = 200, spacename = 24;
	information.variable.statescreen = STATEmainmap;
	for(unsigned int i = 0; i < tabplayer.size(); i++)
		createbutton(information, information.variable.s_player.tabPlayerName[i], { 127, 255, 127, 255 }, { 64, 64, 64, 255 }, 16, 0, initspacename += spacename);

	
	information.ecran.enableFPS = true;
	information.ecran.fpsTimer.start();

	logfileconsole("_Newgame End_");
}

void groundgen(sysinfo& information){
	logfileconsole("_Groundgen Start_");
	unsigned int k = 0, randomground = 0, randomspecgrass = 0, randomspecwater = 0, randomspecwater1 = 0, randomspecwater2 = 0, randomspecwaterborder = 0;

	for (unsigned int i = toolBarSize; i < SCREEN_WIDTH / tileSize; i++){
		for (unsigned int j = 0; j < SCREEN_HEIGHT / tileSize; j++){
			information.maps.tiles[k].tile_nb = k;
			information.maps.tiles[k].tile_x = tileSize * i;
			information.maps.tiles[k].tile_y = tileSize * j;

			/*
				bord de la map
			*/
			if ((i == toolBarSize) || (i == (SCREEN_WIDTH / tileSize) - 1) || (j == 0) || ( j == (SCREEN_HEIGHT / tileSize) - 1))
					tileAffectation(information.maps.tiles[k], deepwater, (string)"deepwater.bmp", specnothing, (string)"specnothing", 0, 0, 0);
			else if ((i == toolBarSize + 1) || (i == (SCREEN_WIDTH / tileSize) - 2) || (j == 1) || (j == (SCREEN_HEIGHT / tileSize) - 2) ||
				(i == toolBarSize + 2) || (i == (SCREEN_WIDTH / tileSize) - 3) || (j == 2) || (j == (SCREEN_HEIGHT / tileSize) - 3) ||
				(i == toolBarSize + 3) || (i == (SCREEN_WIDTH / tileSize) - 4) || (j == 3) || (j == (SCREEN_HEIGHT / tileSize) - 4)) {
				randomspecwaterborder = rand() % 50 + 1;
				switch (randomspecwaterborder) {
				case 1:
					tileAffectation(information.maps.tiles[k], water, (string)"water.bmp", fish, (string)"fish.bmp", 3, 2, 1);
					break;
				case 2:
					tileAffectation(information.maps.tiles[k], water, (string)"water.bmp", petroleum, (string)"petroleum.bmp", 1, 3, 4);
					break;
				}
				if (randomspecwaterborder > 2)
					tileAffectation(information.maps.tiles[k], water, (string)"water.bmp", specnothing, (string)"specnothing", 1, 1, 1);
			}
			/*
				reste de la map
			*/
			else {
				randomground = rand() % 100 + 1;//the range 1 to 100
				if (randomground < 92) {
					information.maps.tiles[k].tile_ground = grass;
					information.maps.tiles[k].tile_stringground = "grass.bmp";
					randomspecgrass = rand() % 100 + 1;
					switch (randomspecgrass) {
					case 1:
						information.maps.tiles[k].tile_spec = coal;
						information.maps.tiles[k].tile_stringspec = "coal.bmp";
						break;
					case 2:
						information.maps.tiles[k].tile_spec = copper;
						information.maps.tiles[k].tile_stringspec = "copper.bmp";
						break;
					case 3:
						information.maps.tiles[k].tile_spec = iron;
						information.maps.tiles[k].tile_stringspec = "iron.bmp";
						break;
					case 4:
						information.maps.tiles[k].tile_spec = tree;
						information.maps.tiles[k].tile_stringspec = "tree1.bmp";
						break;
					case 5:
						information.maps.tiles[k].tile_spec = stone;
						information.maps.tiles[k].tile_stringspec = "stone.bmp";
						break;
					case 6:
						information.maps.tiles[k].tile_spec = uranium;
						information.maps.tiles[k].tile_stringspec = "uranium.bmp";
						break;
					case 7:
						information.maps.tiles[k].tile_spec = horse;
						information.maps.tiles[k].tile_stringspec = "horse.bmp";
						break;
					}
					if (randomspecgrass > 7 && randomspecgrass <= 32) { // plus de chance d'avoir des arbres
						information.maps.tiles[k].tile_spec = tree;
						information.maps.tiles[k].tile_stringspec = "tree1.bmp";
						information.maps.tiles[k].food = 1;
						information.maps.tiles[k].work = 2;
						information.maps.tiles[k].gold = 1;
					}
					else if (randomspecgrass > 32) {
						information.maps.tiles[k].tile_spec = specnothing;
						information.maps.tiles[k].tile_stringspec = "specnothing";
						information.maps.tiles[k].food = 2;
						information.maps.tiles[k].work = 1;
						information.maps.tiles[k].gold = 1;
					}
					else if (randomspecgrass <= 7) {
						information.maps.tiles[k].food = 1;
						information.maps.tiles[k].work = 2;
						information.maps.tiles[k].gold = 3;
					}
				}
				else {
					/*
						génération de l'eau -> forme en L (3 cases)
					*/
					randomspecwater = rand() % 20 + 1;
					switch (randomspecwater) {
					case 1:
						tileAffectation(information.maps.tiles[k], water, (string)"water.bmp", fish, (string)"fish.bmp", 3, 2, 1);
						break;
					case 2:
						tileAffectation(information.maps.tiles[k], water, (string)"water.bmp", petroleum, (string)"petroleum.bmp", 1, 3, 4);
						break;
					}
					if (randomspecwater > 2)
						tileAffectation(information.maps.tiles[k], water, (string)"water.bmp", specnothing, (string)"specnothing", 1, 1, 1);

					if (i > toolBarSize) {
						randomspecwater1 = rand() % 10 + 1;
						switch (randomspecwater1) {
						case 1:
							tileAffectation(information.maps.tiles[k - SCREEN_HEIGHT / tileSize], water, (string)"water.bmp", fish, (string)"fish.bmp", 3, 2, 1);
							break;
						case 2:
							tileAffectation(information.maps.tiles[k - SCREEN_HEIGHT / tileSize], water, (string)"water.bmp", petroleum, (string)"petroleum.bmp", 1, 3, 4);
							break;
						}
						if (randomspecwater1 > 2)
							tileAffectation(information.maps.tiles[k - SCREEN_HEIGHT / tileSize], water, (string)"water.bmp", specnothing, (string)"specnothing", 1, 1, 1);
					}
					if (i > toolBarSize && j > 0) {
						randomspecwater2 = rand() % 10 + 1;
						switch (randomspecwater2) {
						case 1:
							tileAffectation(information.maps.tiles[k - (SCREEN_HEIGHT / tileSize) - 1], water, (string)"water.bmp", fish, (string)"fish.bmp", 3, 2, 1);
							break;
						case 2:
							tileAffectation(information.maps.tiles[k - (SCREEN_HEIGHT / tileSize) - 1], water, (string)"water.bmp", petroleum, (string)"petroleum.bmp", 1, 3, 4);
							break;
						}
						if (randomspecwater2 > 2)
							tileAffectation(information.maps.tiles[k - (SCREEN_HEIGHT / tileSize) - 1], water, (string)"water.bmp", specnothing, (string)"specnothing", 1, 1, 1);
					}
				}
			}
			k++;
		}
	}
	logfileconsole("_Groundgen End_");
}

void tileAffectation(tile& tiles, unsigned int tile_ground, std::string& tile_stringground, unsigned int tile_spec, std::string& tile_stringspec, unsigned int food, unsigned int work, unsigned int gold) {
	tiles.tile_ground = tile_ground;
	tiles.tile_stringground = tile_stringground;
	tiles.tile_spec = tile_spec;
	tiles.tile_stringspec = tile_stringspec;
	tiles.food = food;
	tiles.work = work;
	tiles.gold = gold;
}



void newGameSettlerSpawn(sysinfo& information, std::vector<Player*>& tabplayer){
	/*
		association des vecteurs de position (x,y) avec les settlers de départ
	*/
	unsigned int selectunit = 0;
	for (unsigned int p = 0; p < information.variable.s_player.unitNameMaxToCreate; p++){
		if (information.variable.s_player.s_tabUnitAndSpec[p].name.compare("settler") == 0){
			selectunit = p;
			break;
		}
	}

	vector<randomPos> tabRandom;
	for (unsigned int i = 0; i < tabplayer.size(); i++){
		makeRandomPosTab(information, tabRandom, i);
		tabplayer[i]->addUnit("settler", tabRandom[i].x, tabRandom[i].y,
			information.variable.s_player.s_tabUnitAndSpec[selectunit].life, information.variable.s_player.s_tabUnitAndSpec[selectunit].atq,
			information.variable.s_player.s_tabUnitAndSpec[selectunit].def, information.variable.s_player.s_tabUnitAndSpec[selectunit].movement,
			information.variable.s_player.s_tabUnitAndSpec[selectunit].level);
	}
}

void makeRandomPosTab(sysinfo& information, vector<randomPos>& tabRandom, unsigned int index){
	/*
		créér autant de vecteur de position (x,y) que de joueur initial
	*/
	randomPos RandomPOS;
	bool continuer = true;
	unsigned int nbConditionCheck = 0;
	unsigned int iteration = 0;

	while (continuer){
		iteration++;
		if (iteration > 10000){
			logfileconsole("__________ERROR : makeRandomPosTab, Too many Iterations");
			break;
		}
		makeRandomPos(RandomPOS);
		if (conditionground(information, RandomPOS)){
			if (tabRandom.size() > 1){
				nbConditionCheck = 0;
				for (unsigned int i = 0; i < tabRandom.size(); i++){
					if (conditionspace(RandomPOS, tabRandom, i)){
						nbConditionCheck++;
						if (nbConditionCheck == tabRandom.size()){
							continuer = false;
							break;
						}
					}
				}
			}
			else
				continuer = false;
		}
	}
	tabRandom.push_back(RandomPOS);
}




void makeRandomPos(randomPos& RandomPOS){
	/*
		créér un vecteur de position (x,y) aléatoire respectant la taille de l'écran
	*/
	int x = (rand() % (SCREEN_WIDTH - toolBarSize * tileSize)) + (toolBarSize * tileSize);//the range toolBarSize * tileSize to SCREEN_WIDTH
	int y = (rand() % SCREEN_HEIGHT) + 0;//the range 0 to SCREEN_HEIGHT
	RandomPOS.x = (int)ceil(x / tileSize) * tileSize;
	RandomPOS.y = (int)ceil(y / tileSize) * tileSize;
}

bool conditionspace(randomPos& RandomPOS, vector<randomPos>& tabRandom, unsigned int i){
	/*
		condition pour valider les coordonnées crées:
					- etre en dehors d'un carré d'influence (ici tileSize * 8) d'une autre entitée
	*/
	int spaceBetweenSettler = tileSize * 8;

	if (RandomPOS.x < (tabRandom[i].x - spaceBetweenSettler))
		return true;
	else if (RandomPOS.x >(tabRandom[i].x + spaceBetweenSettler))
		return true;
	else if (RandomPOS.y < (tabRandom[i].y - spaceBetweenSettler))
		return true;
	else if (RandomPOS.y >(tabRandom[i].y + spaceBetweenSettler))
		return true;
	else
		return false;
}

bool conditionground(sysinfo& information, randomPos& RandomPOS){
	/*
		condition pour valider les coordonnées crées:
			- etre sur une tile possédant la caractéristique d'etre du sol
	*/
	unsigned int k = 0;
	for (unsigned int i = toolBarSize; i < SCREEN_WIDTH / tileSize; i++){
		for (unsigned int j = 0; j < SCREEN_HEIGHT / tileSize; j++){
			if (information.maps.tiles[k].tile_x == RandomPOS.x && information.maps.tiles[k].tile_y == RandomPOS.y){
				if (information.maps.tiles[k].tile_ground == grass)
					return true;
				return false;
			}
			k++;
		}
	}
	return false;
}





