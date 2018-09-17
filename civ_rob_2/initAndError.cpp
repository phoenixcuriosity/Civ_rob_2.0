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


	clock_t t1, t2; // calcul du temps pour calculimage
	t1 = clock();



	unsigned int nbspecname = 0, nbcitie = 0;
	unsigned int ground = 0, spec = 0, unit = 0, barLife = 0, colorapp = 0, colorappTile = 0, miscTexture = 0;
	string inttostringTileSize = to_string(tileSize);
	string destroy, name, citie;
	const string IPath = "image/"; // répertoire de base de l'image

	// chargement des images du sol de la map
	loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "ground/grass.bmp", "grass.bmp", (Uint8)255, -1, -1, tileSize, tileSize);
	loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "ground/water.bmp", "water.bmp", (Uint8)255, -1, -1, tileSize, tileSize);
	loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "ground/deepwater.bmp", "water.bmp", (Uint8)255, -1, -1, tileSize, tileSize);
	// chargement de l'image de la toolbar
	loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "toolbar.bmp", "toolbar" + inttostringTileSize + ".bmp", (Uint8)255, -1, -1, tileSize, tileSize);

	// chargement des spécifications du sol de la map
	ifstream SPECNAME(information.file.SPECNAME);
	if (SPECNAME) {
		SPECNAME >> destroy;
		SPECNAME >> nbspecname;
		for (unsigned int i = 0; i < nbspecname; i++) {
			name = "";
			SPECNAME >> name;
			loadImage(information.ecran.renderer, information.allTextures.groundSpec, information.variable.statescreen, information.variable.select,
				IPath + "spec/" + name, name, (Uint8)255, -1, -1, tileSize, tileSize);
		}
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SPECNAME);

	// chargement du nombre d'unités ainsi que leur nom
	for (unsigned int i = 0; i < information.variable.s_player.unitNameMaxToCreate; i++)
		loadImage(information.ecran.renderer, information.allTextures.unit, information.variable.statescreen, information.variable.select,
			IPath + "units/" + information.variable.s_player.s_tabUnitAndSpec[i].name + ".bmp",
			information.variable.s_player.s_tabUnitAndSpec[i].name, (Uint8)255, 100, 432, tileSize, tileSize);


	information.variable.statescreen = STATEmainmap;
	loadImage(information.ecran.renderer, information.allTextures.barLife, information.variable.statescreen, information.variable.select,
		IPath + "barre de vie/maxlife.bmp", "maxlife.bmp", (Uint8)255, -1, -1, tileSize, tileSize / 10);
	for (unsigned int i = 0; i < 10; i++)
		loadImage(information.ecran.renderer, information.allTextures.barLife, information.variable.statescreen, information.variable.select,
			IPath + "barre de vie/0." + to_string(i) + "life.bmp", "0." + to_string(i) + "life.bmp", (Uint8)255, -1, -1, tileSize, tileSize / 10);

	for (unsigned int i = 0; i < 9; i++)
		loadImage(information.ecran.renderer, information.allTextures.colorapp, information.variable.statescreen, information.variable.select,
			IPath + "couleur d'apartenance/ColorPlayer" + to_string(i) + ".bmp", "ColorPlayer" + to_string(i) + ".bmp", (Uint8)255, -1, -1, tileSize / 4, tileSize / 4);
	for (unsigned int i = 0; i < 9; i++)
		loadImage(information.ecran.renderer, information.allTextures.colorappTile, information.variable.statescreen, information.variable.select,
			IPath + "couleur d'apartenance/ColorPlayer" + to_string(i) + ".bmp", "ColorPlayerTile" + to_string(i) + ".bmp", (Uint8)96, -1, -1, tileSize, tileSize);

	information.variable.statescreen = STATEecrantitre;
	loadImage(information.ecran.renderer, information.allTextures.txtecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "earth.jpg", "earth.jpg", (Uint8)255, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, NULL, NULL, center);
	loadImage(information.ecran.renderer, information.allTextures.txtecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "sdl_icone.bmp", "sdl_icone.bmp", (Uint8)255, SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, NULL, NULL, center_x);
	loadImage(information.ecran.renderer, information.allTextures.txtecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "signal/destroyed.bmp", "destroyed.bmp", (Uint8)255, SCREEN_WIDTH / 2, 0, NULL, NULL, center_x);

	information.variable.statescreen = STATEmainmap;
	loadImage(information.ecran.renderer, information.allTextures.miscTexture, information.variable.statescreen, information.variable.select,
		IPath + "citie/citie.png", "citie.png", (Uint8)255, -1, -1, tileSize, tileSize);

	// chargement du nombre de ville ainsi que leur nom
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

	//chargement du nombre de sauvegardes
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
	createbutton(information, information.allButton.ecrantitre,
		shaded, "New Game", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu, center);
	createbutton(information, information.allButton.ecrantitre,
		shaded, "Reload", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, information.allButton.ecrantitre,
		shaded, "Option", { 128, 128, 128, 255 }, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, information.allButton.ecrantitre,
		shaded, "Quit", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);

	information.variable.statescreen = STATEreload;
	initspacemenu = 300;
	createbutton(information, information.allButton.reload, 
		shaded, "Back", WriteColorButton, BackColorButton, 24, 96, 0, center_x);
	createbutton(information, information.allButton.reload,
		shaded, "Remove all saves", WriteColorButton, BackColorButton, 24, 256, 0, center_x);
	createbutton(information, information.allButton.reload,
		shaded, "Load", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2 - 200, 256, center_x);
	createbutton(information, information.allButton.reload,
		shaded, "Remove", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2 + 200, 256, center_x);
	for (unsigned int i = 0; i < information.variable.s_save.nbSave; i++) 
		createbutton(information, information.allButton.reload,
			shaded, "Save : " + to_string(information.variable.s_save.tabSave[i]), WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);


	information.variable.statescreen = STATEmainmap;
	createbutton(information, information.allButton.mainmap, 
		shaded, "Ecran Titre", WriteColorButton, BackColorButton, 24, 96, 0, center_x);
	information.variable.select = selectcreate;
	createbutton(information, information.allButton.mainmap, 
		shaded, "Create Unit", WriteColorButton, BackColorButton, 24, 0, 50);
	information.variable.select = selectmove;
	createbutton(information, information.allButton.mainmap, 
		shaded, "Move Unit", WriteColorButton, BackColorButton, 24, 0, 82);
	information.variable.select = selectinspect;
	createbutton(information, information.allButton.mainmap,
		shaded, "Inspect", WriteColorButton, BackColorButton, 24, 0, 114);
	information.variable.select = selectnothing;
	createbutton(information, information.allButton.mainmap, 
		shaded, "Delete Unit", WriteColorButton, BackColorButton, 24, 0, 146);
	createbutton(information, information.allButton.mainmap, 
		shaded, "Next Turn", WriteColorButton, BackColorButton, 24, 0, 800);

	information.variable.statescreen = STATEcitiemap;
	information.variable.select = selectnothing;
	createbutton(information, information.allButton.citie, 
		shaded, "Map", WriteColorButton, BackColorButton, 24, 96, 0, center_x);
	information.variable.select = selectcreate;
	createbutton(information, information.allButton.citie, 
		shaded, "Build", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 100, center_x);
	information.variable.select = selectnothing;
	createbutton(information, information.allButton.citie,
		shaded, "Food", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 132, center_x);
	information.variable.select = selectmoveCitizen;
	createbutton(information, information.allButton.citie, 
		shaded, "Place Citizen", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 164, center_x);
	for (unsigned int i = 0; i < information.variable.s_player.unitNameMaxToCreate; i++)
		createbutton(information, information.allButton.citie,
			shaded, information.variable.s_player.s_tabUnitAndSpec[i].name, { 255, 64, 0, 255 }, BackColorButton, 24, 64, 400);
	information.variable.select = selectnothing;


	// ______Writetxtshaded_____



	// ______Writetxt_____ 
	information.variable.statescreen = STATEecrantitre;
	loadwritetxt(information, information.allTextures.txtecrantitre, 
		blended ,"Game dev in c++ with SDL2.0.8", { 255, 127, 127, 255 }, NoColor, 24, 0, 0);
	loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "La mort n'est que le commencement", { 127, 255, 127, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 800, center_x);
	loadwritetxt(information, information.allTextures.txtecrantitre, 
		blended, "Je suis devenu la mort,", { 127, 255, 127, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 832, center_x);
	loadwritetxt(information, information.allTextures.txtecrantitre, 
		blended, "le destructeur des Mondes", { 127, 255, 127, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 864, center_x);
	loadwritetxt(information, information.allTextures.txtecrantitre, 
		blended, "CIVILIZATION", { 0, 64, 255, 255 }, NoColor, 70, SCREEN_WIDTH / 2, 100, center_x);

	information.variable.statescreen = STATEecrannewgame;
	loadwritetxt(information, information.allTextures.txtnewgame,
		blended, "Press Return or kpad_Enter to valid selection", { 255, 64, 64, 255 }, NoColor, 24, 0, 100);
	loadwritetxt(information, information.allTextures.txtnewgame,
		blended, "How many player(s) (max 9):", { 255, 0, 0, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 132, center_x);

	
	
	information.variable.statescreen = STATEmainmap;
	loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "Select:", { 0, 64, 255, 255 }, NoColor, 24, 0, 600);
	loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "Turn :", { 0, 64, 255, 255 }, NoColor, 24, 0, 850);
	information.variable.select = selectnothing;
	loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "selectnothing", { 0, 64, 255, 255 }, NoColor, 16, 78, 616, center_y);
	information.variable.select = NotToSelect;
	for (unsigned int i = 0; i < nbcitie; i++)
		loadwritetxt(information, information.allTextures.txtmainmap,
			blended, information.variable.s_player.tabCitieName[i], { 255, 64, 0, 255 }, NoColor, 12, -1, -1);
	
	information.variable.select = selectcreate;
	loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "Scroll up or down", { 0, 64, 255, 255 }, NoColor, 20, 0, 332);
	loadwritetxt(information, information.allTextures.txtmainmap, 
		blended, "Right click to create", { 0, 64, 255, 255 }, NoColor, 18, 0, 364);
	loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "create : ", { 0, 64, 255, 255 }, NoColor, 18, 0, 400);
	loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "selectcreate", { 0, 64, 255, 255 }, NoColor, 16, 78, 616, center_y);
	for (unsigned int i = 0; i < information.variable.s_player.unitNameMaxToCreate; i++)
		loadwritetxt(information, information.allTextures.citie,
			blended, information.variable.s_player.s_tabUnitAndSpec[i].name, { 0, 64, 255, 255 }, NoColor, 18, 64, 400);
	
	
	information.variable.select = selectmove;
	loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "Pick the unit to move", { 0, 64, 255, 255 }, NoColor, 20, 0, 332);
	loadwritetxt(information, information.allTextures.txtmainmap, 
		blended, "with Right click", { 0, 64, 255, 255 }, NoColor, 20, 0, 364);
	loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "selectmove", { 0, 64, 255, 255 }, NoColor, 16, 78, 616, center_y);
	information.variable.select = selectinspect;
	loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "selectinspect", { 0, 64, 255, 255 }, NoColor, 16, 78, 616, center_y);
	loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "Pick the unit to inspect", { 0, 64, 255, 255 }, NoColor, 20, 0, 332);
	loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "with Right click", { 0, 64, 255, 255 }, NoColor, 20, 0, 364);

	
	information.variable.statescreen = STATEcitiemap;
	information.variable.select = selectcreate;
	loadwritetxt(information, information.allTextures.txtcitiemap,
		blended, "Scroll up or down", { 64, 64, 255, 255 }, NoColor, 20, SCREEN_WIDTH - 300, 0);
	loadwritetxt(information, information.allTextures.txtcitiemap,
		blended, "Left click to Select", { 64, 64, 255, 255 }, NoColor, 20, SCREEN_WIDTH - 300, 32);
	loadwritetxt(information, information.allTextures.txtcitiemap,
		blended, "create : ", { 64, 64, 255, 255 }, NoColor, 20, SCREEN_WIDTH - 300, 64);
	loadwritetxt(information, information.allTextures.txtcitiemap,
		blended, "selectcreate", { 64, 64, 255, 255 }, NoColor, 16, SCREEN_WIDTH - 300, 96);
	for (unsigned int i = 0; i < information.variable.s_player.unitNameMaxToCreate; i++)
		loadwritetxt(information, information.allTextures.txtcitiemap,
			blended, "life:" + to_string(information.variable.s_player.s_tabUnitAndSpec[i].life) +
			"/atq:" + to_string(information.variable.s_player.s_tabUnitAndSpec[i].atq) +
			"/def:" + to_string(information.variable.s_player.s_tabUnitAndSpec[i].def) +
			"/move:" + to_string(information.variable.s_player.s_tabUnitAndSpec[i].movement), { 255, 64, 0, 255 }, NoColor, 24, 0, 0);



	information.variable.select = selectnothing;
	information.variable.statescreen = STATEecrantitre;
	t2 = clock();
	logfileconsole("temps d'execution de calculimage : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC));
}



