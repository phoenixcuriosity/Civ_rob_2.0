/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.7

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

#include "calculimage.h"

#include "createButton.h"
#include "write.h"
#include "sdl.h"

using namespace std;


void calculimage(sysinfo& information){
	
	
	clock_t t1, t2;
	t1 = clock();
	
	

	unsigned int nbspecname = 0, nbcitie = 0;
	unsigned int ground = 0, spec = 0, unit = 0, barLife = 0, colorapp = 0, colorappTile = 0, miscTexture = 0;
	string inttostringTileSize = to_string(tileSize);
	string destroy, name, citie;
	const string IPath = "image/"; // répertoire de base de l'image

	loadImage(information, ground, IPath + "ground" + inttostringTileSize + "/grass.bmp", "grass.bmp", (Uint8)255, -1 , -1);
	loadImage(information, ground, IPath + "ground" + inttostringTileSize + "/water.bmp", "water.bmp", (Uint8)255, -1, -1);
	loadImage(information, ground, IPath + "toolbar" + inttostringTileSize + ".bmp", "toolbar" + inttostringTileSize + ".bmp", (Uint8)255, -1, -1);
	
	ifstream SPECNAME(information.file.SPECNAME);
	if (SPECNAME) {
		SPECNAME >> destroy;
		SPECNAME >> nbspecname;
		unsigned int size = information.allTextures.tabTexture.size();
		for (unsigned int i = size; i < size + nbspecname; i++) {
			name = "";
			SPECNAME >> name;
			loadImage(information, spec, IPath + "spec" + inttostringTileSize + "/" + name, name, (Uint8)255, -1, -1);
		}
	}
	
	for (unsigned int i = 0; i < information.variable.unitNameMaxToCreate; i++)
		loadImage(information, unit,
			IPath + "units" + inttostringTileSize + "/" + information.variable.s_tabUnitAndSpec[i].name + ".bmp",
			information.variable.s_tabUnitAndSpec[i].name, (Uint8)255, 100, 432);
	

	information.ecran.statescreen = STATEmainmap;
	loadImage(information, barLife, IPath + "barre de vie" + inttostringTileSize + "/maxlife.bmp", "maxlife.bmp", (Uint8)255, -1, -1);
	for (unsigned int i = 0; i < 10; i++) 
		loadImage(information, barLife, IPath + "barre de vie" + inttostringTileSize + "/0." + to_string(i) + "life.bmp", "0." + to_string(i) + "life.bmp", (Uint8)255, -1, -1);
		
	for (unsigned int i = 0; i < 9; i++)
		loadImage(information, colorapp, IPath + "couleur d'apartenance" + inttostringTileSize + "/ColorPlayer" + to_string(i) + ".bmp", "ColorPlayer" + to_string(i) + ".bmp", (Uint8)255, -1, -1);
	for (unsigned int i = 0; i < 9; i++)
		loadImage(information, colorappTile, IPath + "couleur d'apartenance" + inttostringTileSize + "/ColorPlayerTile" + to_string(i) + ".bmp", "ColorPlayerTile" + to_string(i) + ".bmp", (Uint8)96, -1, -1);

	information.ecran.statescreen = STATEecrantitre;
	loadImage(information, miscTexture, IPath + "earth.jpg", "earth.jpg", (Uint8)255, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, center);
	loadImage(information, miscTexture, IPath + "sdl_icone.bmp", "sdl_icone.bmp", (Uint8)255,SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, center_x);
	loadImage(information, miscTexture, IPath + "signal64/destroyed.bmp", "destroyed.bmp", (Uint8)255, SCREEN_WIDTH / 2, 0, center_x);
	
	information.ecran.statescreen = STATEmainmap;
	loadImage(information, miscTexture, IPath +"citie" + inttostringTileSize + "/" + "citie.png", "citie.png", (Uint8)255, -1, -1);
	
	
	information.allTextures.indexEndGroundStartSpec = ground;
	information.allTextures.indexEndSpecStartUnit = information.allTextures.indexEndGroundStartSpec + spec;
	information.allTextures.indexEndUnitStartBarLife = information.allTextures.indexEndSpecStartUnit + unit;
	information.allTextures.indexEndBarLifeStartColorApp = information.allTextures.indexEndUnitStartBarLife + barLife;
	information.allTextures.indexEndColorAppStartColorAppTile = information.allTextures.indexEndBarLifeStartColorApp + colorapp;
	information.allTextures.indexEndColorAppTileStartMiscTexture = information.allTextures.indexEndColorAppStartColorAppTile + colorappTile;
	information.allTextures.indexEndMiscTextureStartWrite = information.allTextures.indexEndColorAppTileStartMiscTexture + miscTexture;



	ifstream CITIENAME(information.file.CITIENAME);
	if (CITIENAME) {
		CITIENAME >> destroy;
		CITIENAME >> nbcitie;
		information.variable.citieNameMaxToCreate = nbcitie;
		for (unsigned int i = 0; i < nbcitie; i++) {
			CITIENAME >> citie;
			information.variable.tabCitieName.push_back(citie);
		}
	}




	int spacemenu = 64, initspacemenu = 300;
	
	// ______Buttons_____
	information.ecran.statescreen = STATEecrantitre;
	createbutton(information, "New Game", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu, center);
	createbutton(information, "Reload", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, "Option", { 128, 128, 128, 255 }, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, "Quit", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);

	information.ecran.statescreen = STATEmainmap;
	createbutton(information, "Ecran Titre", WriteColorButton, BackColorButton, 24, 96, 0, center_x);
	information.variable.select = selectcreate;
	createbutton(information, "Create Unit", WriteColorButton, BackColorButton, 24, 0, 50);
	information.variable.select = selectmove;
	createbutton(information, "Move Unit", WriteColorButton, BackColorButton, 24, 0, 82);
	information.variable.select = selectinspect;
	createbutton(information, "Inspect", WriteColorButton, BackColorButton, 24, 0, 114);
	information.variable.select = selectnothing;
	createbutton(information, "Delete Unit", WriteColorButton, BackColorButton, 24, 0, 146);
	createbutton(information, "Next Turn", WriteColorButton, BackColorButton, 24, 0, 800);

	information.ecran.statescreen = STATEcitiemap;
	information.variable.select = selectnothing;
	createbutton(information, "Map", WriteColorButton, BackColorButton, 24, 96, 0, center_x);
	information.variable.select = selectcreate;
	createbutton(information, "Build", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 100, center_x);
	information.variable.select = selectnothing;
	createbutton(information, "Food", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 132, center_x);
	information.variable.select = selectmoveCitizen;
	createbutton(information, "Place Citizen", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 164, center_x);
	for (unsigned int i = 0; i < information.variable.unitNameMaxToCreate; i++)
		createbutton(information, information.variable.s_tabUnitAndSpec[i].name, { 255, 64, 0, 255 }, BackColorButton, 24, 64, 400);
	information.variable.select = selectnothing;
	// ______Writetxtshaded_____



	// ______Writetxt_____ 
	information.ecran.statescreen = STATEecrantitre;
	loadwritetxt(information, "Game dev in c++ with SDL2.0.8", { 255, 127, 127, 255 }, 24, 0, 0);
	loadwritetxt(information, "La mort n'est que le commencement", { 127, 255, 127, 255 }, 24, SCREEN_WIDTH / 2, 800, center_x);
	loadwritetxt(information, "Je suis devenu la mort,", { 127, 255, 127, 255 }, 24, SCREEN_WIDTH / 2, 832, center_x);
	loadwritetxt(information, "le destructeur des Mondes", { 127, 255, 127, 255 }, 24, SCREEN_WIDTH / 2, 864, center_x);
	loadwritetxt(information, "CIVILIZATION", { 0, 64, 255, 255 }, 70, SCREEN_WIDTH / 2, 100, center_x);

	information.ecran.statescreen = STATEecrannewgame;
	loadwritetxt(information, "Press Return or kpad_Enter to valid selection", { 255, 64, 64, 255 }, 24, 0, 100);
	loadwritetxt(information, "How many player(s) (max 9):", { 255, 0, 0, 255 }, 24, SCREEN_WIDTH / 2, 132, center_x);

	information.ecran.statescreen = STATEmainmap;
	loadwritetxt(information, "Select:", { 0, 64, 255, 255 }, 24, 0, 600);
	loadwritetxt(information, "Turn :", { 0, 64, 255, 255 }, 24, 0, 850);
	information.variable.select = selectnothing;
	loadwritetxt(information, "selectnothing", { 0, 64, 255, 255 }, 16, 78, 616, center_y);
	information.variable.select = NotToSelect;
	for (unsigned int i = 0; i < nbcitie; i++)
		loadwritetxt(information, information.variable.tabCitieName[i], { 255, 64, 0, 255 }, 12, -1, -1);
	information.variable.select = selectcreate;
	loadwritetxt(information, "Scroll up or down", { 0, 64, 255, 255 }, 20, 0, 332);
	loadwritetxt(information, "Right click to create", { 0, 64, 255, 255 }, 18, 0, 364);
	loadwritetxt(information, "create : ", { 0, 64, 255, 255 }, 18, 0, 400);
	loadwritetxt(information, "selectcreate", { 0, 64, 255, 255 }, 16, 78, 616, center_y);
	for (unsigned int i = 0; i < information.variable.unitNameMaxToCreate; i++)
		loadwritetxt(information, information.variable.s_tabUnitAndSpec[i].name, { 0, 64, 255, 255 }, 18, 64, 400);
	information.variable.select = selectmove;
	loadwritetxt(information, "Pick the unit to move", { 0, 64, 255, 255 }, 20, 0, 332);
	loadwritetxt(information, "with Right click", { 0, 64, 255, 255 }, 20, 0, 364);
	loadwritetxt(information, "selectmove", { 0, 64, 255, 255 }, 16, 78, 616, center_y);
	information.variable.select = selectinspect;
	loadwritetxt(information, "selectinspect", { 0, 64, 255, 255 }, 16, 78, 616, center_y);
	loadwritetxt(information, "Pick the unit to inspect", { 0, 64, 255, 255 }, 20, 0, 332);
	loadwritetxt(information, "with Right click", { 0, 64, 255, 255 }, 20, 0, 364);
	
	information.ecran.statescreen = STATEcitiemap;
	information.variable.select = selectcreate;
	loadwritetxt(information, "Scroll up or down", { 64, 64, 255, 255 }, 20, SCREEN_WIDTH - 300, 0);
	loadwritetxt(information, "Left click to Select", { 64, 64, 255, 255 }, 20, SCREEN_WIDTH - 300, 32);
	loadwritetxt(information, "create : ", { 64, 64, 255, 255 }, 20, SCREEN_WIDTH - 300, 64);
	loadwritetxt(information, "selectcreate", { 64, 64, 255, 255 }, 16, SCREEN_WIDTH - 300, 96);
	for (unsigned int i = 0; i < information.variable.unitNameMaxToCreate; i++)
		loadwritetxt(information, "life:" + to_string(information.variable.s_tabUnitAndSpec[i].life) +
			"/atq:" + to_string(information.variable.s_tabUnitAndSpec[i].atq) +
			"/def:" + to_string(information.variable.s_tabUnitAndSpec[i].def) +
			"/move:" + to_string(information.variable.s_tabUnitAndSpec[i].movement), { 255, 64, 0, 255 }, 24, 0, 0);



	information.variable.select = selectnothing;
	information.ecran.statescreen = STATEecrantitre;
	t2 = clock();
	logfileconsole("temps d'execution de calculimage : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC));
}
