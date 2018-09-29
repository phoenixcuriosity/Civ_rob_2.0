/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.12

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

#include "GamePlay.h"
#include "IHM.h"
#include "SaveReload.h"
#include "KeyboardMouse.h"

void GamePlay::newgame(sysinfo& information, std::vector<Player*>& tabplayer){
	IHM::logfileconsole("_Newgame Start_");
	information.variable.statescreen = STATEecrannewgame;

	unsigned int nbplayer = 0, initspace = 132, space = 32;

	SaveReload::createSave(information);

	SDL_RenderClear(information.ecran.renderer);

	for (unsigned int i = 0; i < information.allTextures.txtnewgame.size(); i++) {
		information.allTextures.txtnewgame[i]->renderTextureTestString(information.ecran.renderer, "Press Return or kpad_Enter to valid selection");
		information.allTextures.txtnewgame[i]->renderTextureTestString(information.ecran.renderer, "How many player(s) (max 9):");
	}
	SDL_RenderPresent(information.ecran.renderer);
	KeyboardMouse::cinDigit(information, nbplayer, SCREEN_WIDTH / 2, initspace += space);

	for (unsigned int i = 1; i < nbplayer + 1; i++){
		information.variable.s_player.tabPlayerName.push_back("");
		Texture::writetxt(information, blended,"Name of player nb:" + std::to_string(i), { 255, 0, 0, 255 }, NoColor, 24, SCREEN_WIDTH / 2, initspace += space, center_x);
		SDL_RenderPresent(information.ecran.renderer);
		KeyboardMouse::cinAlphabet(information, information.variable.s_player.tabPlayerName[i - 1], SCREEN_WIDTH / 2, initspace += space);
		tabplayer.push_back(new Player(information.variable.s_player.tabPlayerName[i - 1]));
	}
	groundgen(information);
	newGameSettlerSpawn(information, tabplayer);
	SaveReload::savemaps(information);
	SaveReload::savePlayer(information, tabplayer);
	
	int initspacename = 200, spacename = 24;
	information.variable.statescreen = STATEmainmap;
	for(unsigned int i = 0; i < tabplayer.size(); i++)
		Buttons::createbutton(information, information.allButton.player,
			shaded, information.variable.s_player.tabPlayerName[i], { 127, 255, 127, 255 }, { 64, 64, 64, 255 }, 16, 0, initspacename += spacename);

	
	information.ecran.enableFPS = true;
	information.ecran.fpsTimer.start();

	IHM::logfileconsole("_Newgame End_");
}
void GamePlay::groundgen(sysinfo& information){
	IHM::logfileconsole("_Groundgen Start_");
	unsigned int k = 0, randomground = 0, randomspecgrass = 0, randomspecwater = 0, randomspecwater1 = 0, randomspecwater2 = 0, randomspecwaterborder = 0;

	for (unsigned int i = 0; i < information.maps.mapSize / information.maps.tileSize; i++){
		for (unsigned int j = 0; j < information.maps.mapSize / information.maps.tileSize; j++){
			
			information.maps.maps[k].tile_nb = k;
			information.maps.maps[k].tile_x = information.maps.tileSize * i;
			information.maps.maps[k].tile_y = information.maps.tileSize * j;
			
			/*
				bord de la map
			*/
			if ((i == 0) || (i == (information.maps.mapSize / information.maps.tileSize) - 1) || (j == 0) || ( j == (information.maps.mapSize / information.maps.tileSize) - 1))
					tileAffectation(information.maps.maps[k], deepwater, (std::string)"deepwater.bmp", specnothing, (std::string)"specnothing", 0, 0, 0);
			else if ((i ==  1) || (i == (information.maps.mapSize / information.maps.tileSize) - 2) || (j == 1) || (j == (information.maps.mapSize / information.maps.tileSize) - 2) ||
				(i == 2) || (i == (information.maps.mapSize / information.maps.tileSize) - 3) || (j == 2) || (j == (information.maps.mapSize / information.maps.tileSize) - 3) ||
				(i == 3) || (i == (information.maps.mapSize / information.maps.tileSize) - 4) || (j == 3) || (j == (information.maps.mapSize / information.maps.tileSize) - 4)) {
				
				randomspecwaterborder = rand() % 50 + 1;
				switch (randomspecwaterborder) {
				case 1:
					tileAffectation(information.maps.maps[k], water, (std::string)"water.bmp", fish, (std::string)"fish.bmp", 3, 2, 1);
					break;
				case 2:
					tileAffectation(information.maps.maps[k], water, (std::string)"water.bmp", petroleum, (std::string)"petroleum.bmp", 1, 3, 4);
					break;
				}
				if (randomspecwaterborder > 2)
					tileAffectation(information.maps.maps[k], water, (std::string)"water.bmp", specnothing, (std::string)"specnothing", 1, 1, 1);
			}
			/*
				reste de la map
			*/
			else {
				randomground = rand() % 100 + 1;//the range 1 to 100
				if (randomground < 92) {
					information.maps.maps[k].tile_ground = grass;
					information.maps.maps[k].tile_stringground = "grass.bmp";
					randomspecgrass = rand() % 100 + 1;
					switch (randomspecgrass) {
					case 1:
						information.maps.maps[k].tile_spec = coal;
						information.maps.maps[k].tile_stringspec = "coal.png";
						break;
					case 2:
						information.maps.maps[k].tile_spec = copper;
						information.maps.maps[k].tile_stringspec = "copper.png";
						break;
					case 3:
						information.maps.maps[k].tile_spec = iron;
						information.maps.maps[k].tile_stringspec = "iron.png";
						break;
					case 4:
						information.maps.maps[k].tile_spec = tree;
						information.maps.maps[k].tile_stringspec = "tree1.bmp";
						break;
					case 5:
						information.maps.maps[k].tile_spec = stone;
						information.maps.maps[k].tile_stringspec = "stone.png";
						break;
					case 6:
						information.maps.maps[k].tile_spec = uranium;
						information.maps.maps[k].tile_stringspec = "uranium.png";
						break;
					case 7:
						information.maps.maps[k].tile_spec = horse;
						information.maps.maps[k].tile_stringspec = "horse.bmp";
						break;
					}
					if (randomspecgrass > 7 && randomspecgrass <= 32) { // plus de chance d'avoir des arbres
						information.maps.maps[k].tile_spec = tree;
						information.maps.maps[k].tile_stringspec = "tree1.bmp";
						information.maps.maps[k].food = 1;
						information.maps.maps[k].work = 2;
						information.maps.maps[k].gold = 1;
					}
					else if (randomspecgrass > 32) {
						information.maps.maps[k].tile_spec = specnothing;
						information.maps.maps[k].tile_stringspec = "specnothing";
						information.maps.maps[k].food = 2;
						information.maps.maps[k].work = 1;
						information.maps.maps[k].gold = 1;
					}
					else if (randomspecgrass <= 7) {
						information.maps.maps[k].food = 1;
						information.maps.maps[k].work = 2;
						information.maps.maps[k].gold = 3;
					}
				}
				else {
					/*
						génération de l'eau -> forme en L (3 cases)
					*/
					if (i > 2 && j > 2) {
						randomspecwater = rand() % 20 + 1;
						switch (randomspecwater) {
						case 1:
							tileAffectation(information.maps.maps[k], water, (std::string)"water.bmp", fish, (std::string)"fish.bmp", 3, 2, 1);
							break;
						case 2:
							tileAffectation(information.maps.maps[k], water, (std::string)"water.bmp", petroleum, (std::string)"petroleum.bmp", 1, 3, 4);
							break;
						}
						if (randomspecwater > 2)
							tileAffectation(information.maps.maps[k], water, (std::string)"water.bmp", specnothing, (std::string)"specnothing", 1, 1, 1);
					}
					if (information.maps.maps[k - SCREEN_HEIGHT / information.maps.tileSize].tile_ground != deepwater) {
						randomspecwater1 = rand() % 10 + 1;
						switch (randomspecwater1) {
						case 1:
							tileAffectation(information.maps.maps[k - SCREEN_HEIGHT / information.maps.tileSize], water, (std::string)"water.bmp", fish, (std::string)"fish.bmp", 3, 2, 1);
							break;
						case 2:
							tileAffectation(information.maps.maps[k - SCREEN_HEIGHT / information.maps.tileSize], water, (std::string)"water.bmp", petroleum, (std::string)"petroleum.bmp", 1, 3, 4);
							break;
						}
						if (randomspecwater1 > 2)
							tileAffectation(information.maps.maps[k - SCREEN_HEIGHT / information.maps.tileSize], water, (std::string)"water.bmp", specnothing, (std::string)"specnothing", 1, 1, 1);
					}
					if (information.maps.maps[k - (SCREEN_HEIGHT / information.maps.tileSize) - 1].tile_ground != deepwater) {
						randomspecwater2 = rand() % 10 + 1;
						switch (randomspecwater2) {
						case 1:
							tileAffectation(information.maps.maps[k - (SCREEN_HEIGHT / information.maps.tileSize) - 1], water, (std::string)"water.bmp", fish, (std::string)"fish.bmp", 3, 2, 1);
							break;
						case 2:
							tileAffectation(information.maps.maps[k - (SCREEN_HEIGHT / information.maps.tileSize) - 1], water, (std::string)"water.bmp", petroleum, (std::string)"petroleum.bmp", 1, 3, 4);
							break;
						}
						if (randomspecwater2 > 2)
							tileAffectation(information.maps.maps[k - (SCREEN_HEIGHT / information.maps.tileSize) - 1], water, (std::string)"water.bmp", specnothing, (std::string)"specnothing", 1, 1, 1);
					}
				}
			}
			k++;
		}
	}
	unsigned int l = 0;
	for (unsigned int i = 0; i < information.maps.maps.size(); i++) {
		if (information.maps.maps[i].tile_x >= 0 && information.maps.maps[i].tile_x < SCREEN_WIDTH ) {
			if (information.maps.maps[i].tile_y >= 0 && information.maps.maps[i].tile_y < SCREEN_HEIGHT) {
				information.maps.screen[l] = information.maps.maps[i];
				information.maps.screen[l].tile_nb = l;
				information.maps.screen[l].tile_x = information.maps.maps[i].tile_x;
				l++;
			}
		}
	}
	IHM::logfileconsole("_Groundgen End_");
}
void GamePlay::tileAffectation(tile& tiles, unsigned int tile_ground, std::string& tile_stringground, unsigned int tile_spec, std::string& tile_stringspec, unsigned int food, unsigned int work, unsigned int gold) {
	tiles.tile_ground = tile_ground;
	tiles.tile_stringground = tile_stringground;
	tiles.tile_spec = tile_spec;
	tiles.tile_stringspec = tile_stringspec;
	tiles.food = food;
	tiles.work = work;
	tiles.gold = gold;
}
void GamePlay::newGameSettlerSpawn(sysinfo& information, std::vector<Player*>& tabplayer){
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

	std::vector<randomPos> tabRandom;
	for (unsigned int i = 0; i < tabplayer.size(); i++){
		makeRandomPosTab(information, tabRandom, i);
		tabplayer[i]->addUnit("settler", tabRandom[i].x, tabRandom[i].y,
			information.variable.s_player.s_tabUnitAndSpec[selectunit].life, information.variable.s_player.s_tabUnitAndSpec[selectunit].atq,
			information.variable.s_player.s_tabUnitAndSpec[selectunit].def, information.variable.s_player.s_tabUnitAndSpec[selectunit].movement,
			information.variable.s_player.s_tabUnitAndSpec[selectunit].level);
	}
}
void GamePlay::makeRandomPosTab(sysinfo& information, std::vector<randomPos>& tabRandom, unsigned int index){
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
			IHM::logfileconsole("__________ERROR : makeRandomPosTab, Too many Iterations");
			break;
		}
		makeRandomPos(RandomPOS, information.maps.toolBarSize, information.maps.tileSize);
		if (conditionground(information, RandomPOS)){
			if (tabRandom.size() > 1){
				nbConditionCheck = 0;
				for (unsigned int i = 0; i < tabRandom.size(); i++){
					if (conditionspace(RandomPOS, tabRandom, information.maps.tileSize, i)){
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
void GamePlay::makeRandomPos(randomPos& RandomPOS, unsigned int toolBarSize, unsigned int tileSize){
	/*
		créér un vecteur de position (x,y) aléatoire respectant la taille de l'écran
	*/
	int x = (rand() % (SCREEN_WIDTH - toolBarSize * tileSize)) + (toolBarSize * tileSize);//the range toolBarSize * tileSize to SCREEN_WIDTH
	int y = (rand() % SCREEN_HEIGHT) + 0;//the range 0 to SCREEN_HEIGHT
	RandomPOS.x = (int)ceil(x / tileSize) * tileSize;
	RandomPOS.y = (int)ceil(y / tileSize) * tileSize;
}
bool GamePlay::conditionspace(randomPos& RandomPOS, std::vector<randomPos>& tabRandom, unsigned int tileSize, unsigned int i){
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
bool GamePlay::conditionground(sysinfo& information, randomPos& RandomPOS){
	/*
		condition pour valider les coordonnées crées:
			- etre sur une tile possédant la caractéristique d'etre du sol
	*/
	for (unsigned int i = 0; i <information.maps.screen.size(); i++){
		if (information.maps.screen[i].tile_x == RandomPOS.x && information.maps.screen[i].tile_y == RandomPOS.y){
			if (information.maps.screen[i].tile_ground == grass)
				return true;
			return false;
		}
	}
	return false;
}
void GamePlay::nextTurn(sysinfo& information, std::vector<Player*>& tabplayer) {
	for (unsigned int i = 0; i < tabplayer.size(); i++) {
		for (unsigned int j = 0; j < tabplayer[i]->GETtabunit().size(); j++) {
			tabplayer[i]->GETtheunit(j)->RESETmovement();
			tabplayer[i]->GETtheunit(j)->heal(information.maps.maps, i);
		}
		for (unsigned int j = 0; j < tabplayer[i]->GETtabcities().size(); j++) {
			tabplayer[i]->GETthecitie(j)->foodNextTurn();
		}
	}
	information.variable.nbturn++;
}
