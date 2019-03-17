/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.14
	file version : 1.1

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
#include "HashTable.h"

void GamePlay::newgame(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_Newgame Start_");
	sysinfo.var.statescreen = STATEscreennewgame;

	unsigned int nbplayer = 0, initspace = 132, space = 32;

	// création d'une sauvegarde concernant la nouvelle partie
	SaveReload::createSave(sysinfo);

	// Fond noir
	SDL_RenderClear(sysinfo.screen.renderer);


	// Première demande au joueur : Le nombre de joueurs ?
	sysinfo.allTextes.newGame[searchIndex("Press Return or kpad_Enter to valid selection", sysinfo.allTextes.newGame)]->render();
	sysinfo.allTextes.newGame[searchIndex("How many player(s) (max 9):", sysinfo.allTextes.newGame)]->render();
	SDL_RenderPresent(sysinfo.screen.renderer);


	// Le joueur doit rentrer une valeur entre 1 et 9, par défaut 1
	KeyboardMouse::cinDigit(sysinfo, nbplayer, SCREEN_WIDTH / 2, initspace += space);

	// Deuxième demande au joueur : Le nom des joueurs
	for (unsigned int i = 1; i < nbplayer + 1; i++)
	{
		sysinfo.var.s_player.tabPlayerName.push_back("");

		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended,"Name of player nb:" + std::to_string(i), { 255, 0, 0, 255 }, NoColor, 24, SCREEN_WIDTH / 2, initspace += space, no_angle, center_x);
		SDL_RenderPresent(sysinfo.screen.renderer);

		// valeur par défaut avec incrémentation en fonction du nombre de joueur : noName 
		KeyboardMouse::cinAlphabet(sysinfo, sysinfo.var.s_player.tabPlayerName[i - 1], SCREEN_WIDTH / 2, initspace += space);
		sysinfo.tabplayer.push_back(new Player(sysinfo.var.s_player.tabPlayerName[i - 1]));
	}
	
	groundgen(sysinfo);
	newGameSettlerSpawn(sysinfo);

	/*** Sauvegarde des paramètres appliqués et de la génération de la map ***/
	SaveReload::savemaps(sysinfo);
	SaveReload::savePlayer(sysinfo);
	
	// Création des boutons pour séléctionner les joueurs
	int initspacename = 200, spacename = 24;
	sysinfo.var.statescreen = STATEmainmap;
	for (unsigned int i = 0; i < sysinfo.tabplayer.size(); i++)
	{
		ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.player,
			shaded, sysinfo.var.s_player.tabPlayerName[i], { 127, 255, 127, 255 }, { 64, 64, 64, 255 }, 16, 0, initspacename += spacename, nonTransparent, no_angle);
	}

	/* Hachage du tableau player */
	sysinfo.allButton.player.resize(sysinfo.allButton.player.size() + sysinfo.allButton.player.size() * INIT_SIZE_MULTIPLIER);
	fillTabHachage(sysinfo.allButton.player, sysinfo.allButton.playerIndex);
	
	sysinfo.screen.enableFPS = true;
	sysinfo.screen.fpsTimer.start();

	/* ### Don't put code below here ### */

	IHM::logfileconsole("_Newgame End_");
}
void GamePlay::groundgen(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_Groundgen Start_");
	unsigned int randomground = 0, randomspecgrass = 0, randomspecwater = 0, randomspecwater1 = 0, randomspecwater2 = 0, randomspecwaterborder = 0;

	for (Uint8 i = 0; i < sysinfo.map.mapSize / sysinfo.map.tileSize; i++)
	{
		for (Uint8 j = 0; j < sysinfo.map.mapSize / sysinfo.map.tileSize; j++)
		{
			
			sysinfo.map.maps[i][j].indexX = i;
			sysinfo.map.maps[i][j].indexY = j;
			sysinfo.map.maps[i][j].tile_x = sysinfo.map.tileSize * i;
			sysinfo.map.maps[i][j].tile_y = sysinfo.map.tileSize * j;
			
			/*
				bord de la map
			*/
			if ((i == 0) || (i == (sysinfo.map.mapSize / sysinfo.map.tileSize) - 1) || (j == 0) || ( j == (sysinfo.map.mapSize / sysinfo.map.tileSize) - 1))
					tileAffectation(sysinfo.map.maps[i][j], deepwater, (std::string)"deepwater.bmp", specnothing, (std::string)"specnothing", 0, 0, 0);
			else if ((i ==  1) || (i == (sysinfo.map.mapSize / sysinfo.map.tileSize) - 2) || (j == 1) || (j == (sysinfo.map.mapSize / sysinfo.map.tileSize) - 2) ||
				(i == 2) || (i == (sysinfo.map.mapSize / sysinfo.map.tileSize) - 3) || (j == 2) || (j == (sysinfo.map.mapSize / sysinfo.map.tileSize) - 3) ||
				(i == 3) || (i == (sysinfo.map.mapSize / sysinfo.map.tileSize) - 4) || (j == 3) || (j == (sysinfo.map.mapSize / sysinfo.map.tileSize) - 4))
			{
				
				randomspecwaterborder = rand() % 50 + 1;
				switch (randomspecwaterborder) {
				case 1:
					tileAffectation(sysinfo.map.maps[i][j], water, (std::string)"water.bmp", fish, (std::string)"fish.bmp", 3, 2, 1);
					break;
				case 2:
					tileAffectation(sysinfo.map.maps[i][j], water, (std::string)"water.bmp", petroleum, (std::string)"petroleum.bmp", 1, 3, 4);
					break;
				}
				if (randomspecwaterborder > 2)
					tileAffectation(sysinfo.map.maps[i][j], water, (std::string)"water.bmp", specnothing, (std::string)"specnothing", 1, 1, 1);
			}
			/*
				reste de la map
			*/
			else
			{
				randomground = rand() % 100 + 1;//the range 1 to 100
				if (randomground < 92)
				{
					sysinfo.map.maps[i][j].tile_ground = grass;
					sysinfo.map.maps[i][j].tile_stringground = "grass.bmp";
					randomspecgrass = rand() % 100 + 1;
					switch (randomspecgrass)
					{
					case 1:
						sysinfo.map.maps[i][j].tile_spec = coal;
						sysinfo.map.maps[i][j].tile_stringspec = "coal.png";
						break;
					case 2:
						sysinfo.map.maps[i][j].tile_spec = copper;
						sysinfo.map.maps[i][j].tile_stringspec = "copper.png";
						break;
					case 3:
						sysinfo.map.maps[i][j].tile_spec = iron;
						sysinfo.map.maps[i][j].tile_stringspec = "iron.png";
						break;
					case 4:
						sysinfo.map.maps[i][j].tile_spec = tree;
						sysinfo.map.maps[i][j].tile_stringspec = "tree1.bmp";
						break;
					case 5:
						sysinfo.map.maps[i][j].tile_spec = stone;
						sysinfo.map.maps[i][j].tile_stringspec = "stone.png";
						break;
					case 6:
						sysinfo.map.maps[i][j].tile_spec = uranium;
						sysinfo.map.maps[i][j].tile_stringspec = "uranium.png";
						break;
					case 7:
						sysinfo.map.maps[i][j].tile_spec = horse;
						sysinfo.map.maps[i][j].tile_stringspec = "horse.bmp";
						break;
					}
					if (randomspecgrass > 7 && randomspecgrass <= 32)
					{ // plus de chance d'avoir des arbres
						sysinfo.map.maps[i][j].tile_spec = tree;
						sysinfo.map.maps[i][j].tile_stringspec = "tree1.bmp";
						sysinfo.map.maps[i][j].food = 1;
						sysinfo.map.maps[i][j].work = 2;
						sysinfo.map.maps[i][j].gold = 1;
					}
					else if (randomspecgrass > 32)
					{
						sysinfo.map.maps[i][j].tile_spec = specnothing;
						sysinfo.map.maps[i][j].tile_stringspec = "specnothing";
						sysinfo.map.maps[i][j].food = 2;
						sysinfo.map.maps[i][j].work = 1;
						sysinfo.map.maps[i][j].gold = 1;
					}
					else if (randomspecgrass <= 7) 
					{
						sysinfo.map.maps[i][j].food = 1;
						sysinfo.map.maps[i][j].work = 2;
						sysinfo.map.maps[i][j].gold = 3;
					}
				}
				else
				{
					/*
						génération de l'eau -> forme en L (3 cases)
					*/
					if (i > 2 && j > 2)
					{
						randomspecwater = rand() % 20 + 1;
						switch (randomspecwater)
						{
						case 1:
							tileAffectation(sysinfo.map.maps[i][j], water, (std::string)"water.bmp", fish, (std::string)"fish.bmp", 3, 2, 1);
							break;
						case 2:
							tileAffectation(sysinfo.map.maps[i][j], water, (std::string)"water.bmp", petroleum, (std::string)"petroleum.bmp", 1, 3, 4);
							break;
						}
						if (randomspecwater > 2)
							tileAffectation(sysinfo.map.maps[i][j], water, (std::string)"water.bmp", specnothing, (std::string)"specnothing", 1, 1, 1);
					}
					if (sysinfo.map.maps[i - 1][j].tile_ground != deepwater)
					{
						randomspecwater1 = rand() % 10 + 1;
						switch (randomspecwater1)
						{
						case 1:
							tileAffectation(sysinfo.map.maps[i - 1][j], water, (std::string)"water.bmp", fish, (std::string)"fish.bmp", 3, 2, 1);
							break;
						case 2:
							tileAffectation(sysinfo.map.maps[i - 1][j], water, (std::string)"water.bmp", petroleum, (std::string)"petroleum.bmp", 1, 3, 4);
							break;
						}
						if (randomspecwater1 > 2)
							tileAffectation(sysinfo.map.maps[i - 1][j], water, (std::string)"water.bmp", specnothing, (std::string)"specnothing", 1, 1, 1);
					}
					if (sysinfo.map.maps[i - 1][j - 1].tile_ground != deepwater)
					{
						randomspecwater2 = rand() % 10 + 1;
						switch (randomspecwater2)
						{
						case 1:
							tileAffectation(sysinfo.map.maps[i - 1][j - 1], water, (std::string)"water.bmp", fish, (std::string)"fish.bmp", 3, 2, 1);
							break;
						case 2:
							tileAffectation(sysinfo.map.maps[i - 1][j - 1], water, (std::string)"water.bmp", petroleum, (std::string)"petroleum.bmp", 1, 3, 4);
							break;
						}
						if (randomspecwater2 > 2)
							tileAffectation(sysinfo.map.maps[i - 1][j - 1], water, (std::string)"water.bmp", specnothing, (std::string)"specnothing", 1, 1, 1);
					}
				}
			}
		}
	}
	Uint8 m = 0, n = 0;
	for (unsigned int i = 0; i < sysinfo.map.maps.size(); i++)
	{
		for (unsigned int j = 0; j < sysinfo.map.maps[i].size(); j++) {
			if (sysinfo.map.maps[i][j].tile_x >= 0 && sysinfo.map.maps[i][j].tile_x < SCREEN_WIDTH)
			{
				if (sysinfo.map.maps[i][j].tile_y >= 0 && sysinfo.map.maps[i][j].tile_y < SCREEN_HEIGHT)
				{
					sysinfo.map.screen[m][n] = sysinfo.map.maps[i][j];
					sysinfo.map.screen[m][n].indexX = m;
					sysinfo.map.screen[m][n].indexY = n;
					n = (n + 1) % sysinfo.map.screen[m].size();
					if (n == 0)
						m++;
				}
			}
		}
	}
	IHM::logfileconsole("_Groundgen End_");
}
void GamePlay::tileAffectation(Tile& tile, Uint8 tile_ground, std::string tile_stringground, Uint8 tile_spec, std::string tile_stringspec, int8_t food, int8_t work, int8_t gold)
{
	tile.tile_ground = tile_ground;
	tile.tile_stringground = tile_stringground;
	tile.tile_spec = tile_spec;
	tile.tile_stringspec = tile_stringspec;
	tile.food = food;
	tile.work = work;
	tile.gold = gold;
}
void GamePlay::newGameSettlerSpawn(Sysinfo& sysinfo)
{
	/*
		association des vecteurs de position (x,y) avec les settlers de départ
	*/
	unsigned int selectunit = 0;
	for (unsigned int p = 0; p < sysinfo.var.s_player.unitNameMaxToCreate; p++)
	{
		if (sysinfo.var.s_player.tabUnit_Struct[p].name.compare("settler") == 0)
		{
			selectunit = p;
			break;
		}
	}

	std::vector<randomPos> tabRandom;
	for (unsigned int i = 0; i < sysinfo.tabplayer.size(); i++)
	{
		makeRandomPosTab(sysinfo, tabRandom);
		sysinfo.tabplayer[i]->addUnit("settler", tabRandom[i].x, tabRandom[i].y,
			sysinfo.var.s_player.tabUnit_Struct[selectunit].life, sysinfo.var.s_player.tabUnit_Struct[selectunit].atq,
			sysinfo.var.s_player.tabUnit_Struct[selectunit].def, sysinfo.var.s_player.tabUnit_Struct[selectunit].movement,
			sysinfo.var.s_player.tabUnit_Struct[selectunit].level);
	}
}
void GamePlay::makeRandomPosTab(Sysinfo& sysinfo, std::vector<randomPos>& tabRandom)
{
	/*
		créér autant de vecteur de position (x,y) que de joueur initial
	*/
	randomPos RandomPOS;
	bool continuer = true;
	unsigned int nbConditionCheck = 0;
	unsigned int iteration = 0;

	while (continuer)
	{
		iteration++;
		if (iteration > 10000)
		{
			IHM::logfileconsole("__________ERROR : makeRandomPosTab, Too many Iterations");
			break;
		}
		makeRandomPos(RandomPOS, sysinfo.map.toolBarSize, sysinfo.map.tileSize);
		if (conditionground(sysinfo, RandomPOS))
		{
			if (tabRandom.size() > 1)
			{
				nbConditionCheck = 0;
				for (unsigned int i = 0; i < tabRandom.size(); i++)
				{
					if (conditionspace(RandomPOS, tabRandom, sysinfo.map.tileSize, i))
					{
						nbConditionCheck++;
						if (nbConditionCheck == tabRandom.size())
						{
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
void GamePlay::makeRandomPos(randomPos& RandomPOS, unsigned int toolBarSize, unsigned int tileSize)
{
	/*
		créér un vecteur de position (x,y) aléatoire respectant la taille de l'écran
	*/
	int x = (rand() % (SCREEN_WIDTH - toolBarSize * tileSize)) + (toolBarSize * tileSize);//the range toolBarSize * tileSize to SCREEN_WIDTH
	int y = (rand() % SCREEN_HEIGHT) + 0;//the range 0 to SCREEN_HEIGHT
	RandomPOS.x = (int)ceil(x / tileSize) * tileSize;
	RandomPOS.y = (int)ceil(y / tileSize) * tileSize;
}
bool GamePlay::conditionspace(randomPos& RandomPOS, std::vector<randomPos>& tabRandom, unsigned int tileSize, unsigned int i)
{
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
bool GamePlay::conditionground(Sysinfo& sysinfo, randomPos& RandomPOS)
{
	/*
		condition pour valider les coordonnées crées:
			- etre sur une tile possédant la caractéristique d'etre du sol
	*/
	for (unsigned int i = 0; i < sysinfo.map.screen.size(); i++) 
	{
		for (unsigned int j = 0; j < sysinfo.map.screen[i].size(); j++) 
		{
			if (sysinfo.map.screen[i][j].tile_x == RandomPOS.x && sysinfo.map.screen[i][j].tile_y == RandomPOS.y) 
			{
				if (sysinfo.map.screen[i][j].tile_ground == grass)
					return true;
				return false;
			}
		}
	}
	return false;
}
void GamePlay::nextTurn(Sysinfo& sysinfo)
{
	for (unsigned int i = 0; i < sysinfo.tabplayer.size(); i++) 
	{
		for (unsigned int j = 0; j < sysinfo.tabplayer[i]->GETtabunit().size(); j++) 
		{
			sysinfo.tabplayer[i]->GETtheunit(j)->RESETmovement();
			sysinfo.tabplayer[i]->GETtheunit(j)->heal(sysinfo.map.maps, i);
		}
		for (unsigned int j = 0; j < sysinfo.tabplayer[i]->GETtabcities().size(); j++)
		{
			sysinfo.tabplayer[i]->GETthecitie(j)->foodNextTurn();
		}
	}
	sysinfo.var.nbturn++;
}

/*
*	End Of File
*/
