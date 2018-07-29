/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.9

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

#include "initAndError.h"

#include "mainLoop.h"
#include "sdl.h"
#include "renduecran.h"
#include "Player.h"
#include "unit.h"
#include "deleteAll.h"


using namespace std;





void initAndError(){
	sysinfo information;
	vector<Player*> tabplayer;

	srand((unsigned int)time(NULL));



	try{
		initfile(information);
	}
	catch (exception const& e){
		cerr << "ERREUR : " << e.what() << endl; 
	}



	logfileconsole("________PROGRAMME START________");

	try{
		initsdl(information.ecran.window, information.ecran.renderer, information.allTextures.font);
	}
	catch (exception const& e){
		cerr << "ERREUR : " << e.what() << endl;
	}

	
	loadUnitAndSpec(information);
	calculimage(information);
	ecrantitre(information);
	mainLoop(information, tabplayer);	// fonction principale (bloquante)

	deleteAll(information, tabplayer);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	logfileconsole("SDL_Quit Success");
	logfileconsole("________PROGRAMME FINISH________");
}





void calculimage(sysinfo& information) {


	clock_t t1, t2;
	t1 = clock();



	unsigned int nbspecname = 0, nbcitie = 0;
	unsigned int ground = 0, spec = 0, unit = 0, barLife = 0, colorapp = 0, colorappTile = 0, miscTexture = 0;
	string inttostringTileSize = to_string(tileSize);
	string destroy, name, citie;
	const string IPath = "image/"; // répertoire de base de l'image

	loadImage(information, ground, IPath + "ground" + inttostringTileSize + "/grass.bmp", "grass.bmp", (Uint8)255, -1, -1);
	loadImage(information, ground, IPath + "ground" + inttostringTileSize + "/water.bmp", "water.bmp", (Uint8)255, -1, -1);
	loadImage(information, ground, IPath + "ground" + inttostringTileSize + "/deepwater.bmp", "water.bmp", (Uint8)255, -1, -1);
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
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SPECNAME);

	for (unsigned int i = 0; i < information.variable.s_player.unitNameMaxToCreate; i++)
		loadImage(information, unit,
			IPath + "units" + inttostringTileSize + "/" + information.variable.s_player.s_tabUnitAndSpec[i].name + ".bmp",
			information.variable.s_player.s_tabUnitAndSpec[i].name, (Uint8)255, 100, 432);


	information.variable.statescreen = STATEmainmap;
	loadImage(information, barLife, IPath + "barre de vie" + inttostringTileSize + "/maxlife.bmp", "maxlife.bmp", (Uint8)255, -1, -1);
	for (unsigned int i = 0; i < 10; i++)
		loadImage(information, barLife, IPath + "barre de vie" + inttostringTileSize + "/0." + to_string(i) + "life.bmp", "0." + to_string(i) + "life.bmp", (Uint8)255, -1, -1);

	for (unsigned int i = 0; i < 9; i++)
		loadImage(information, colorapp, IPath + "couleur d'apartenance" + inttostringTileSize + "/ColorPlayer" + to_string(i) + ".bmp", "ColorPlayer" + to_string(i) + ".bmp", (Uint8)255, -1, -1);
	for (unsigned int i = 0; i < 9; i++)
		loadImage(information, colorappTile, IPath + "couleur d'apartenance" + inttostringTileSize + "/ColorPlayerTile" + to_string(i) + ".bmp", "ColorPlayerTile" + to_string(i) + ".bmp", (Uint8)96, -1, -1);

	information.variable.statescreen = STATEecrantitre;
	loadImage(information, miscTexture, IPath + "earth.jpg", "earth.jpg", (Uint8)255, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, center);
	loadImage(information, miscTexture, IPath + "sdl_icone.bmp", "sdl_icone.bmp", (Uint8)255, SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, center_x);
	loadImage(information, miscTexture, IPath + "signal64/destroyed.bmp", "destroyed.bmp", (Uint8)255, SCREEN_WIDTH / 2, 0, center_x);

	information.variable.statescreen = STATEmainmap;
	loadImage(information, miscTexture, IPath + "citie" + inttostringTileSize + "/" + "citie.png", "citie.png", (Uint8)255, -1, -1);


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
		information.variable.s_player.citieNameMaxToCreate = nbcitie;
		for (unsigned int i = 0; i < nbcitie; i++) {
			CITIENAME >> citie;
			information.variable.s_player.tabCitieName.push_back(citie);
		}
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.CITIENAME);

	ifstream loadInfo(information.file.SaveInfo);
	unsigned int currentSave = 0;
	if (loadInfo) {
		loadInfo >> destroy;
		loadInfo >> information.variable.s_save.nbSave;
		loadInfo >> destroy;
		for (unsigned int i = 0; i < information.variable.s_save.nbSave; i++) {
			loadInfo >> currentSave;
			information.variable.s_save.tabSave.push_back(currentSave);
		}
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SaveInfo);
	int spacemenu = 64, initspacemenu = 300;

	// ______Buttons_____
	information.variable.statescreen = STATEecrantitre;
	createbutton(information, "New Game", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu, center);
	createbutton(information, "Reload", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, "Option", { 128, 128, 128, 255 }, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, "Quit", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);

	information.variable.statescreen = STATEreload;
	initspacemenu = 300;
	createbutton(information, "Back", WriteColorButton, BackColorButton, 24, 96, 0, center_x);
	createbutton(information, "Remove all saves", WriteColorButton, BackColorButton, 24, 256, 0, center_x);
	createbutton(information, "Load", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2 - 200, 256, center_x);
	createbutton(information, "Remove", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2 + 200, 256, center_x);
	for (unsigned int i = 0; i < information.variable.s_save.nbSave; i++) 
		createbutton(information, "Save : " + to_string(information.variable.s_save.tabSave[i]), WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);


	information.variable.statescreen = STATEmainmap;
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

	information.variable.statescreen = STATEcitiemap;
	information.variable.select = selectnothing;
	createbutton(information, "Map", WriteColorButton, BackColorButton, 24, 96, 0, center_x);
	information.variable.select = selectcreate;
	createbutton(information, "Build", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 100, center_x);
	information.variable.select = selectnothing;
	createbutton(information, "Food", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 132, center_x);
	information.variable.select = selectmoveCitizen;
	createbutton(information, "Place Citizen", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 164, center_x);
	for (unsigned int i = 0; i < information.variable.s_player.unitNameMaxToCreate; i++)
		createbutton(information, information.variable.s_player.s_tabUnitAndSpec[i].name, { 255, 64, 0, 255 }, BackColorButton, 24, 64, 400);
	information.variable.select = selectnothing;


	// ______Writetxtshaded_____



	// ______Writetxt_____ 
	information.variable.statescreen = STATEecrantitre;
	loadwritetxt(information, "Game dev in c++ with SDL2.0.8", { 255, 127, 127, 255 }, 24, 0, 0);
	loadwritetxt(information, "La mort n'est que le commencement", { 127, 255, 127, 255 }, 24, SCREEN_WIDTH / 2, 800, center_x);
	loadwritetxt(information, "Je suis devenu la mort,", { 127, 255, 127, 255 }, 24, SCREEN_WIDTH / 2, 832, center_x);
	loadwritetxt(information, "le destructeur des Mondes", { 127, 255, 127, 255 }, 24, SCREEN_WIDTH / 2, 864, center_x);
	loadwritetxt(information, "CIVILIZATION", { 0, 64, 255, 255 }, 70, SCREEN_WIDTH / 2, 100, center_x);

	information.variable.statescreen = STATEecrannewgame;
	loadwritetxt(information, "Press Return or kpad_Enter to valid selection", { 255, 64, 64, 255 }, 24, 0, 100);
	loadwritetxt(information, "How many player(s) (max 9):", { 255, 0, 0, 255 }, 24, SCREEN_WIDTH / 2, 132, center_x);

	information.variable.statescreen = STATEmainmap;
	loadwritetxt(information, "Select:", { 0, 64, 255, 255 }, 24, 0, 600);
	loadwritetxt(information, "Turn :", { 0, 64, 255, 255 }, 24, 0, 850);
	information.variable.select = selectnothing;
	loadwritetxt(information, "selectnothing", { 0, 64, 255, 255 }, 16, 78, 616, center_y);
	information.variable.select = NotToSelect;
	for (unsigned int i = 0; i < nbcitie; i++)
		loadwritetxt(information, information.variable.s_player.tabCitieName[i], { 255, 64, 0, 255 }, 12, -1, -1);
	information.variable.select = selectcreate;
	loadwritetxt(information, "Scroll up or down", { 0, 64, 255, 255 }, 20, 0, 332);
	loadwritetxt(information, "Right click to create", { 0, 64, 255, 255 }, 18, 0, 364);
	loadwritetxt(information, "create : ", { 0, 64, 255, 255 }, 18, 0, 400);
	loadwritetxt(information, "selectcreate", { 0, 64, 255, 255 }, 16, 78, 616, center_y);
	for (unsigned int i = 0; i < information.variable.s_player.unitNameMaxToCreate; i++)
		loadwritetxt(information, information.variable.s_player.s_tabUnitAndSpec[i].name, { 0, 64, 255, 255 }, 18, 64, 400);
	information.variable.select = selectmove;
	loadwritetxt(information, "Pick the unit to move", { 0, 64, 255, 255 }, 20, 0, 332);
	loadwritetxt(information, "with Right click", { 0, 64, 255, 255 }, 20, 0, 364);
	loadwritetxt(information, "selectmove", { 0, 64, 255, 255 }, 16, 78, 616, center_y);
	information.variable.select = selectinspect;
	loadwritetxt(information, "selectinspect", { 0, 64, 255, 255 }, 16, 78, 616, center_y);
	loadwritetxt(information, "Pick the unit to inspect", { 0, 64, 255, 255 }, 20, 0, 332);
	loadwritetxt(information, "with Right click", { 0, 64, 255, 255 }, 20, 0, 364);

	information.variable.statescreen = STATEcitiemap;
	information.variable.select = selectcreate;
	loadwritetxt(information, "Scroll up or down", { 64, 64, 255, 255 }, 20, SCREEN_WIDTH - 300, 0);
	loadwritetxt(information, "Left click to Select", { 64, 64, 255, 255 }, 20, SCREEN_WIDTH - 300, 32);
	loadwritetxt(information, "create : ", { 64, 64, 255, 255 }, 20, SCREEN_WIDTH - 300, 64);
	loadwritetxt(information, "selectcreate", { 64, 64, 255, 255 }, 16, SCREEN_WIDTH - 300, 96);
	for (unsigned int i = 0; i < information.variable.s_player.unitNameMaxToCreate; i++)
		loadwritetxt(information, "life:" + to_string(information.variable.s_player.s_tabUnitAndSpec[i].life) +
			"/atq:" + to_string(information.variable.s_player.s_tabUnitAndSpec[i].atq) +
			"/def:" + to_string(information.variable.s_player.s_tabUnitAndSpec[i].def) +
			"/move:" + to_string(information.variable.s_player.s_tabUnitAndSpec[i].movement), { 255, 64, 0, 255 }, 24, 0, 0);



	information.variable.select = selectnothing;
	information.variable.statescreen = STATEecrantitre;
	t2 = clock();
	logfileconsole("temps d'execution de calculimage : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC));
}

void createbutton(sysinfo& information, const string& msg, SDL_Color color, SDL_Color backcolor, int size, int x, int y, int centerbutton) {
	int iW = 0, iH = 0;
	unsigned int i = 0;
	int xc = 0, yc = 0;
	SDL_Texture *image = nullptr;
	SDL_Texture *imageOn = nullptr;

	if (information.tabbutton.size() > 0) {
		i++;
	}
	for (i; i <= information.tabbutton.size(); i++) {
		if (i == information.tabbutton.size()) {
			image = renderTextShaded(information.ecran.renderer, msg, color, backcolor, information.allTextures.font[size]);
			imageOn = renderTextShaded(information.ecran.renderer, msg, color, { 64,128,64,255 }, information.allTextures.font[size]);
			SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
			searchcenter(x, y, xc, yc, iW, iH, centerbutton);
			information.tabbutton.push_back(new Buttons(image, msg, information.variable.statescreen, information.variable.select, xc, yc, iW, iH, imageOn, x, y, size, color, backcolor));

			logfileconsole("Create Button n:" + to_string(i) + " msg = " + information.tabbutton[i]->GETname() + " Success");
			break;
		}
	}
}

void searchcenter(int &x, int &y, int &xc, int &yc, int iW, int iH, int centerbutton) {
	switch (centerbutton) {
	case nocenter:
		xc = x + iW / 2;
		yc = y + iH / 2;
		break;
	case center_x:
		xc = x;
		yc = y + iH / 2;
		x = x - iW / 2;
		break;
	case center_y:
		xc = x + iW / 2;
		yc = y;
		y = y - iH / 2;
		break;
	case center:
		xc = x;
		yc = y;
		x = x - iW / 2;
		y = y - iH / 2;
		break;
	}
}



