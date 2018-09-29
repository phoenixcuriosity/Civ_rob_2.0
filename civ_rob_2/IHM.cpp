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

#include "IHM.h"
#include "SaveReload.h"

void IHM::initTile(sysinfo& information) {
	tile kTile;

	for (unsigned int i = 0; i < SCREEN_WIDTH / information.maps.tileSize; i++) {
		for (unsigned int j = 0; j < SCREEN_HEIGHT / information.maps.tileSize; j++) {
			information.maps.screen.push_back(kTile);
		}
	}
	for (unsigned int i = 0; i < information.maps.mapSize / information.maps.tileSize; i++) {
		for (unsigned int j = 0; j < information.maps.mapSize / information.maps.tileSize; j++) {
			information.maps.maps.push_back(kTile);
		}
	}

}
void IHM::initfile(sysinfo& information) {
	std::ofstream log(information.file.log);
	if (log) {}
	else
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le fichier : " << information.file.log;
}
void IHM::logfileconsole(const std::string &msg) {
	const std::string logtxt = "bin/log/log.txt";
	std::ofstream log(logtxt, std::ios::app);

	//std::time_t result = std::time(nullptr);
	//<< std::asctime(std::localtime(&result))

	if (log) {
		std::cout << std::endl << msg;
		log << std::endl << msg;
	}
	else
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}
void IHM::logSDLError(std::ostream &os, const std::string &msg) {
	const std::string logtxt = "bin/log/log.txt";
	std::ofstream log(logtxt, std::ios::app);
	if (log) {
		os << msg << " error: " << SDL_GetError() << std::endl;
		log << msg << " error: " << SDL_GetError() << std::endl;
	}
	else
		std::cout << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt << std::endl;
}
void IHM::initsdl(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font* font[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		std::cout << std::endl << "SDL could not initialize! SDL_Error: " << SDL_GetError();
	else {
		window = SDL_CreateWindow("Civ_rob_2",
			0, 0,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL);

		//	SDL_WINDOW_FULLSCREEN_DESKTOP or SDL_WINDOW_FULLSCREEN
		if (window == nullptr) {
			logSDLError(std::cout, "CreateWindow");
			SDL_Quit();
		}
		else
			logfileconsole("CreateWindow Success");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		//| SDL_RENDERER_PRESENTVSYNC
		if (renderer == nullptr) {
			logSDLError(std::cout, "CreateRenderer");
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
		else
			logfileconsole("CreateRenderer Success");

		if (TTF_Init() != 0) {
			logSDLError(std::cout, "TTF_Init");
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
		else
			logfileconsole("TTF_Init Success");


		const std::string fontFile = "arial.ttf";

		for (unsigned int i = 1; i < 80; i++)
			font[i] = TTF_OpenFont(fontFile.c_str(), i);

		logfileconsole("SDL_Init Success");
	}
}
void IHM::calculimage(sysinfo& information) {






	unsigned int nbspecname = 0, nbcitie = 0;
	unsigned int ground = 0, spec = 0, unit = 0, barLife = 0, colorapp = 0, colorappTile = 0, miscTexture = 0;
	std::string destroy, name, citie;
	const std::string IPath = "image/"; // répertoire de base de l'image

	// chargement des images du sol de la map
	Texture::loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "ground/grass.bmp", "grass.bmp", (Uint8)255, -1, -1, information.maps.tileSize, information.maps.tileSize);
	Texture::loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "ground/water.bmp", "water.bmp", (Uint8)255, -1, -1, information.maps.tileSize, information.maps.tileSize);
	Texture::loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "ground/deepwater.bmp", "water.bmp", (Uint8)255, -1, -1, information.maps.tileSize, information.maps.tileSize);
	// chargement de l'image de la toolbar
	Texture::loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "toolbar.bmp", "toolbar.bmp", (Uint8)255, -1, -1, information.maps.tileSize, information.maps.tileSize);

	// chargement des spécifications du sol de la map
	std::ifstream SPECNAME(information.file.SPECNAME);
	if (SPECNAME) {
		SPECNAME >> destroy;
		SPECNAME >> nbspecname;
		for (unsigned int i = 0; i < nbspecname; i++) {
			name = "";
			SPECNAME >> name;
			Texture::loadImage(information.ecran.renderer, information.allTextures.groundSpec, information.variable.statescreen, information.variable.select,
				IPath + "spec/" + name, name, (Uint8)255, -1, -1, information.maps.tileSize, information.maps.tileSize);
		}
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SPECNAME);

	// chargement du nombre d'unités ainsi que leur nom
	for (unsigned int i = 0; i < information.variable.s_player.unitNameMaxToCreate; i++)
		Texture::loadImage(information.ecran.renderer, information.allTextures.unit, information.variable.statescreen, information.variable.select,
			IPath + "units/" + information.variable.s_player.s_tabUnitAndSpec[i].name + ".bmp",
			information.variable.s_player.s_tabUnitAndSpec[i].name, (Uint8)255, 100, 432, information.maps.tileSize, information.maps.tileSize);


	information.variable.statescreen = STATEmainmap;
	Texture::loadImage(information.ecran.renderer, information.allTextures.barLife, information.variable.statescreen, information.variable.select,
		IPath + "barre de vie/maxlife.bmp", "maxlife.bmp", (Uint8)255, -1, -1, information.maps.tileSize, information.maps.tileSize / 10);
	for (unsigned int i = 0; i < 10; i++)
		Texture::loadImage(information.ecran.renderer, information.allTextures.barLife, information.variable.statescreen, information.variable.select,
			IPath + "barre de vie/0." + std::to_string(i) + "life.bmp", "0." + std::to_string(i) + "life.bmp", (Uint8)255, -1, -1, information.maps.tileSize, information.maps.tileSize / 10);

	for (unsigned int i = 0; i < 9; i++)
		Texture::loadImage(information.ecran.renderer, information.allTextures.colorapp, information.variable.statescreen, information.variable.select,
			IPath + "couleur d'apartenance/ColorPlayer" + std::to_string(i) + ".bmp", "ColorPlayer" + std::to_string(i) + ".bmp", (Uint8)255, -1, -1, information.maps.tileSize / 4, information.maps.tileSize / 4);
	for (unsigned int i = 0; i < 9; i++)
		Texture::loadImage(information.ecran.renderer, information.allTextures.colorappTile, information.variable.statescreen, information.variable.select,
			IPath + "couleur d'apartenance/ColorPlayer" + std::to_string(i) + ".bmp", "ColorPlayerTile" + std::to_string(i) + ".bmp", (Uint8)96, -1, -1, information.maps.tileSize, information.maps.tileSize);

	information.variable.statescreen = STATEecrantitre;
	Texture::loadImage(information.ecran.renderer, information.allTextures.txtecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "earth.jpg", "earth.jpg", (Uint8)255, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, NULL, NULL, center);
	Texture::loadImage(information.ecran.renderer, information.allTextures.txtecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "sdl_icone.bmp", "sdl_icone.bmp", (Uint8)255, SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, NULL, NULL, center_x);
	Texture::loadImage(information.ecran.renderer, information.allTextures.txtecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "signal/destroyed.bmp", "destroyed.bmp", (Uint8)255, SCREEN_WIDTH / 2, 0, NULL, NULL, center_x);

	information.variable.statescreen = STATEmainmap;
	Texture::loadImage(information.ecran.renderer, information.allTextures.miscTexture, information.variable.statescreen, information.variable.select,
		IPath + "citie/citie.png", "citie.png", (Uint8)255, -1, -1, information.maps.tileSize, information.maps.tileSize);

	// chargement du nombre de ville ainsi que leur nom
	std::ifstream CITIENAME(information.file.CITIENAME);
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
	std::ifstream loadInfo(information.file.SaveInfo);
	unsigned int currentSave = 0, maxSave = 0;
	if (loadInfo) {
		loadInfo >> destroy;
		loadInfo >> maxSave;
		information.variable.save.SETnbSave(maxSave);
		loadInfo >> destroy;
		for (unsigned int i = 0; i < information.variable.save.GETnbSave(); i++) {
			loadInfo >> currentSave;
			information.variable.save.GETtabSave().push_back(currentSave);
		}
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.file.SaveInfo);
	int spacemenu = 64, initspacemenu = 300;

	// ______Buttons_____
	information.variable.statescreen = STATEecrantitre;
	Buttons::createbutton(information, information.allButton.ecrantitre,
		shaded, "New Game", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu, center);
	Buttons::createbutton(information, information.allButton.ecrantitre,
		shaded, "Reload", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	Buttons::createbutton(information, information.allButton.ecrantitre,
		shaded, "Option", { 128, 128, 128, 255 }, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	Buttons::createbutton(information, information.allButton.ecrantitre,
		shaded, "Quit", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);

	information.variable.statescreen = STATEreload;
	initspacemenu = 300;
	Buttons::createbutton(information, information.allButton.reload,
		shaded, "Back", WriteColorButton, BackColorButton, 24, 96, 0, center_x);
	Buttons::createbutton(information, information.allButton.reload,
		shaded, "Remove all saves", WriteColorButton, BackColorButton, 24, 256, 0, center_x);
	Buttons::createbutton(information, information.allButton.reload,
		shaded, "Load", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2 - 200, 256, center_x);
	Buttons::createbutton(information, information.allButton.reload,
		shaded, "Remove", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2 + 200, 256, center_x);
	for (unsigned int i = 0; i < information.variable.save.GETnbSave(); i++)
		Buttons::createbutton(information, information.allButton.reload,
			shaded, "Save : " + std::to_string(information.variable.save.GETtabSave()[i]), WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);


	information.variable.statescreen = STATEmainmap;
	Buttons::createbutton(information, information.allButton.mainmap,
		shaded, "Ecran Titre", WriteColorButton, BackColorButton, 24, 96, 0, center_x);
	information.variable.select = selectcreate;
	Buttons::createbutton(information, information.allButton.mainmap,
		shaded, "Create Unit", WriteColorButton, BackColorButton, 24, 0, 50);
	information.variable.select = selectmove;
	Buttons::createbutton(information, information.allButton.mainmap,
		shaded, "Move Unit", WriteColorButton, BackColorButton, 24, 0, 82);
	information.variable.select = selectinspect;
	Buttons::createbutton(information, information.allButton.mainmap,
		shaded, "Inspect", WriteColorButton, BackColorButton, 24, 0, 114);
	information.variable.select = selectnothing;
	Buttons::createbutton(information, information.allButton.mainmap,
		shaded, "Delete Unit", WriteColorButton, BackColorButton, 24, 0, 146);
	Buttons::createbutton(information, information.allButton.mainmap,
		shaded, "Next Turn", WriteColorButton, BackColorButton, 24, 0, 800);

	information.variable.statescreen = STATEcitiemap;
	information.variable.select = selectnothing;
	Buttons::createbutton(information, information.allButton.citie,
		shaded, "Map", WriteColorButton, BackColorButton, 24, 96, 0, center_x);
	information.variable.select = selectcreate;
	Buttons::createbutton(information, information.allButton.citie,
		shaded, "Build", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 100, center_x);
	information.variable.select = selectnothing;
	Buttons::createbutton(information, information.allButton.citie,
		shaded, "Food", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 132, center_x);
	information.variable.select = selectmoveCitizen;
	Buttons::createbutton(information, information.allButton.citie,
		shaded, "Place Citizen", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 164, center_x);
	for (unsigned int i = 0; i < information.variable.s_player.unitNameMaxToCreate; i++)
		Buttons::createbutton(information, information.allButton.citie,
			shaded, information.variable.s_player.s_tabUnitAndSpec[i].name, { 255, 64, 0, 255 }, BackColorButton, 24, 64, 400);
	information.variable.select = selectnothing;


	// ______Writetxtshaded_____



	// ______Writetxt_____ 
	information.variable.statescreen = STATEecrantitre;
	Texture::loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "Game dev in c++ with SDL2.0.8", { 255, 127, 127, 255 }, NoColor, 24, 0, 0);
	Texture::loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "La mort n'est que le commencement", { 127, 255, 127, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 800, center_x);
	Texture::loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "Je suis devenu la mort,", { 127, 255, 127, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 832, center_x);
	Texture::loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "le destructeur des Mondes", { 127, 255, 127, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 864, center_x);
	Texture::loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "CIVILIZATION", { 0, 64, 255, 255 }, NoColor, 70, SCREEN_WIDTH / 2, 100, center_x);

	information.variable.statescreen = STATEecrannewgame;
	Texture::loadwritetxt(information, information.allTextures.txtnewgame,
		blended, "Press Return or kpad_Enter to valid selection", { 255, 64, 64, 255 }, NoColor, 24, 0, 100);
	Texture::loadwritetxt(information, information.allTextures.txtnewgame,
		blended, "How many player(s) (max 9):", { 255, 0, 0, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 132, center_x);



	information.variable.statescreen = STATEmainmap;
	Texture::loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "Select:", { 0, 64, 255, 255 }, NoColor, 24, 0, 600);
	Texture::loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "Turn :", { 0, 64, 255, 255 }, NoColor, 24, 0, 850);
	information.variable.select = selectnothing;
	Texture::loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "selectnothing", { 0, 64, 255, 255 }, NoColor, 16, 78, 616, center_y);
	information.variable.select = NotToSelect;
	for (unsigned int i = 0; i < nbcitie; i++)
		Texture::loadwritetxt(information, information.allTextures.txtmainmap,
			blended, information.variable.s_player.tabCitieName[i], { 255, 64, 0, 255 }, NoColor, 12, -1, -1);

	information.variable.select = selectcreate;
	Texture::loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "Scroll up or down", { 0, 64, 255, 255 }, NoColor, 20, 0, 332);
	Texture::loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "Right click to create", { 0, 64, 255, 255 }, NoColor, 18, 0, 364);
	Texture::loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "create : ", { 0, 64, 255, 255 }, NoColor, 18, 0, 400);
	Texture::loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "selectcreate", { 0, 64, 255, 255 }, NoColor, 16, 78, 616, center_y);
	for (unsigned int i = 0; i < information.variable.s_player.unitNameMaxToCreate; i++)
		Texture::loadwritetxt(information, information.allTextures.citie,
			blended, information.variable.s_player.s_tabUnitAndSpec[i].name, { 0, 64, 255, 255 }, NoColor, 18, 64, 400);


	information.variable.select = selectmove;
	Texture::loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "Pick the unit to move", { 0, 64, 255, 255 }, NoColor, 20, 0, 332);
	Texture::loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "with Right click", { 0, 64, 255, 255 }, NoColor, 20, 0, 364);
	Texture::loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "selectmove", { 0, 64, 255, 255 }, NoColor, 16, 78, 616, center_y);
	information.variable.select = selectinspect;
	Texture::loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "selectinspect", { 0, 64, 255, 255 }, NoColor, 16, 78, 616, center_y);
	Texture::loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "Pick the unit to inspect", { 0, 64, 255, 255 }, NoColor, 20, 0, 332);
	Texture::loadwritetxt(information, information.allTextures.txtmainmap,
		blended, "with Right click", { 0, 64, 255, 255 }, NoColor, 20, 0, 364);


	information.variable.statescreen = STATEcitiemap;
	information.variable.select = selectcreate;
	Texture::loadwritetxt(information, information.allTextures.txtcitiemap,
		blended, "Scroll up or down", { 64, 64, 255, 255 }, NoColor, 20, SCREEN_WIDTH - 300, 0);
	Texture::loadwritetxt(information, information.allTextures.txtcitiemap,
		blended, "Left click to Select", { 64, 64, 255, 255 }, NoColor, 20, SCREEN_WIDTH - 300, 32);
	Texture::loadwritetxt(information, information.allTextures.txtcitiemap,
		blended, "create : ", { 64, 64, 255, 255 }, NoColor, 20, SCREEN_WIDTH - 300, 64);
	Texture::loadwritetxt(information, information.allTextures.txtcitiemap,
		blended, "selectcreate", { 64, 64, 255, 255 }, NoColor, 16, SCREEN_WIDTH - 300, 96);
	for (unsigned int i = 0; i < information.variable.s_player.unitNameMaxToCreate; i++)
		Texture::loadwritetxt(information, information.allTextures.txtcitiemap,
			blended, "life:" + std::to_string(information.variable.s_player.s_tabUnitAndSpec[i].life) +
			"/atq:" + std::to_string(information.variable.s_player.s_tabUnitAndSpec[i].atq) +
			"/def:" + std::to_string(information.variable.s_player.s_tabUnitAndSpec[i].def) +
			"/move:" + std::to_string(information.variable.s_player.s_tabUnitAndSpec[i].movement), { 255, 64, 0, 255 }, NoColor, 24, 0, 0);



	information.variable.select = selectnothing;
	information.variable.statescreen = STATEecrantitre;
}
void IHM::ecrantitre(sysinfo& information) {
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
void IHM::reloadScreen(sysinfo& information) {
	logfileconsole("_reloadScreen Start_");
	information.variable.statescreen = STATEreload;
	SDL_RenderClear(information.ecran.renderer);

	for (unsigned int i = 0; i < information.allButton.reload.size(); i++)
		information.allButton.reload[i]->renderButton(information.ecran.renderer, information.variable.statescreen);


	SDL_RenderPresent(information.ecran.renderer);
	logfileconsole("_reloadScreen End_");
}
void IHM::alwaysrender(sysinfo& information, std::vector<Player*>& tabplayer) {
	//clock_t t1, t2;
	//t1 = clock();

	switch (information.variable.statescreen) {
	case STATEmainmap:
		SDL_RenderClear(information.ecran.renderer);
		afficherSuperTiles(information);

		// affiche la texture grise de la toolbar
		for (unsigned int i = 0; i < information.maps.toolBarSize; i++) {
			for (unsigned int j = 0; j < SCREEN_HEIGHT / information.maps.tileSize; j++)
				information.allTextures.ground[3]->render(information.ecran.renderer, i * information.maps.tileSize, j * information.maps.tileSize);
		}

		for (unsigned int i = 0; i < information.allButton.mainmap.size(); i++)
			information.allButton.mainmap[i]->renderButton(information.ecran.renderer, information.variable.statescreen);
		for (unsigned int i = 0; i < information.allButton.player.size(); i++)
			information.allButton.player[i]->renderButton(information.ecran.renderer, information.variable.statescreen);



		Texture::writetxt(information, blended, std::to_string(information.variable.nbturn), { 0, 64, 255, 255 }, NoColor, 24, 80, 850);

		// affiche les unités pour rendre l'unité à créer
		if (information.variable.select == selectcreate) {
			for (unsigned int i = 0; i < information.allTextures.unit.size(); i++)
				information.allTextures.unit[i]->renderTextureTestString(information.ecran.renderer, information.variable.s_player.unitNameToCreate);
		}

		// affiche tous les textes selectionnés
		for (unsigned int i = 0; i < information.allTextures.txtmainmap.size(); i++) {
			information.allTextures.txtmainmap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Select:", information.variable.statescreen);
			information.allTextures.txtmainmap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Turn :", information.variable.statescreen);

			switch (information.variable.select) {
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

		if (tabplayer.size() != 0) {
			for (unsigned int i = 0; i < tabplayer.size(); i++) {
				if (tabplayer[i]->GETtabunit().size() != 0) {
					for (unsigned int j = 0; j < tabplayer[i]->GETtabunit().size(); j++) {
						// affiche pour chaque joueurs les unités existantes (avec les stats)
						tabplayer[i]->GETtheunit(j)->afficher(information);
						tabplayer[i]->GETtheunit(j)->afficherBardeVie(information);
						for (unsigned int h = 0; h < information.allTextures.colorapp.size(); h++)
							information.allTextures.colorapp[h]->renderTextureTestString(information.ecran.renderer, "ColorPlayer" + std::to_string(i) + ".bmp", tabplayer[i]->GETtheunit(j)->GETx(), tabplayer[i]->GETtheunit(j)->GETy() + information.maps.tileSize);
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
	Texture::writetxt(information, blended, std::to_string(information.ecran.avgFPS), { 0, 64, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 50, center_x);

	SDL_RenderPresent(information.ecran.renderer);
	//t2 = clock();
	//cout << endl << "temps d'execution de alwaysrender : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
}
void IHM::afficherSuperTiles(sysinfo& information) {
	unsigned int l = 0;
	for (unsigned int i = 0; i < information.maps.maps.size(); i++) {
		if (information.maps.maps[i].tile_x >= 0 && information.maps.maps[i].tile_x < SCREEN_WIDTH) {
			if (information.maps.maps[i].tile_y >= 0 && information.maps.maps[i].tile_y < SCREEN_HEIGHT) {
				information.maps.screen[l] = information.maps.maps[i];
				information.maps.screen[l].tile_nb = l;
				l++;
			}
		}
	}

	for (unsigned int i = 0; i < information.maps.screen.size(); i++) {
		if (information.maps.screen[i].tile_x >= 0 && information.maps.screen[i].tile_x < SCREEN_WIDTH) {
			if (information.maps.screen[i].tile_y >= 0 && information.maps.screen[i].tile_y < SCREEN_HEIGHT) {

				// attention tabtexture 0,1,2 sont réservés, à changer si nécessaire
				if (information.maps.screen[i].tile_ground == grass)
					information.allTextures.ground[0]->render(information.ecran.renderer, information.maps.screen[i].tile_x, information.maps.screen[i].tile_y);
				else if (information.maps.screen[i].tile_ground == water)
					information.allTextures.ground[1]->render(information.ecran.renderer, information.maps.screen[i].tile_x, information.maps.screen[i].tile_y);
				else if (information.maps.screen[i].tile_ground == deepwater)
					information.allTextures.ground[2]->render(information.ecran.renderer, information.maps.screen[i].tile_x, information.maps.screen[i].tile_y);

				if (information.maps.screen[i].tile_spec != 0) {
					for (unsigned int l = 0; l < information.allTextures.groundSpec.size(); l++)
						information.allTextures.groundSpec[l]->renderTextureTestString(information.ecran.renderer, information.maps.screen[i].tile_stringspec, information.maps.screen[i].tile_x, information.maps.screen[i].tile_y);
				}
				if (information.maps.screen[i].appartenance != -1) {
					for (unsigned int l = 0; l < information.allTextures.colorappTile.size(); l++)
						information.allTextures.colorappTile[l]->renderTextureTestString(information.ecran.renderer, "ColorPlayerTile" + std::to_string(information.maps.screen[i].appartenance) + ".bmp", information.maps.screen[i].tile_x, information.maps.screen[i].tile_y);
				}

			}
		}
	}
}
void IHM::citiemap(sysinfo& information, std::vector<Player*>& tabplayer) {
	SDL_RenderClear(information.ecran.renderer);
	std::string buildName;
	unsigned int initspace = 96, space = 32;
	unsigned int valid = 12, checkButton = 0; // optimisation de la boucle for 
	unsigned int validBarreSpec = 10, checkBarre = 0;

	if (information.variable.select != selectcreate)
		valid = 2;

	for (unsigned int i = 0; i < information.allButton.citie.size(); i++) {
		if (information.allButton.citie[i]->renderButtonTestString(information.ecran.renderer, information.variable.statescreen, (std::string)"Map")) { i++; checkButton++; }
		if (information.allButton.citie[i]->renderButtonTestString(information.ecran.renderer, information.variable.statescreen, (std::string)"Build")) { i++; checkButton++; }
		if (information.allButton.citie[i]->renderButtonTestString(information.ecran.renderer, information.variable.statescreen, (std::string)"Food")) { i++; checkButton++; }
		if (information.allButton.citie[i]->renderButtonTestString(information.ecran.renderer, information.variable.statescreen, (std::string)"Place Citizen")) { i++; checkButton++; }

		if (information.variable.select == selectcreate) {
			initspace = 96;
			for (unsigned int j = 0; j < 10; j++) {
				if (information.variable.s_player.unitToCreate + j < information.variable.s_player.unitNameMaxToCreate)
					buildName = information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate + j].name;
				else
					break;
				if (information.allButton.citie[i]->renderButtonTestString(information.ecran.renderer, information.variable.statescreen, buildName, SCREEN_WIDTH / 2, initspace += space)) { i++; checkButton++; }
			}
		}
		if (checkButton == valid) break;
	}

	for (unsigned int i = 0; i < information.allTextures.txtcitiemap.size(); i++) {
		initspace = 96;
		switch (information.variable.select) {
		case selectcreate:
			information.allTextures.txtcitiemap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Scroll up or down", information.variable.statescreen);
			information.allTextures.txtcitiemap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "Left click to Select", information.variable.statescreen);
			information.allTextures.txtcitiemap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "create : ", information.variable.statescreen);
			information.allTextures.txtcitiemap[i]->renderTextureTestStringAndStates(information.ecran.renderer, "selectcreate", information.variable.statescreen);
			break;
		}
	}

	if (information.variable.select == selectcreate) {
		for (unsigned int i = 0; i < information.allTextures.unit.size(); i++) {
			initspace = 96;
			for (unsigned int j = 0; j < 10; j++) {
				if (information.variable.s_player.unitToCreate + j < information.variable.s_player.unitNameMaxToCreate)
					buildName = information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate + j].name;
				else
					break;
				information.allTextures.unit[i]->renderTextureTestStringAndStates(information.ecran.renderer, buildName, STATEnothing, (SCREEN_WIDTH / 2) - 50, initspace += space);
			}
		}
		for (unsigned int i = 0; i < information.allTextures.txtcitiemap.size(); i++) {
			initspace = 96;
			for (unsigned int j = 0; j < 10; j++) {
				if (information.variable.s_player.unitToCreate + j < information.variable.s_player.unitNameMaxToCreate)
					buildName = information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate + j].name;
				else
					break;
				if (information.allTextures.txtcitiemap[i]->renderTextureTestStringAndStates(information.ecran.renderer,
					"life:" + std::to_string(information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate + j].life) +
					"/atq:" + std::to_string(information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate + j].atq) +
					"/def:" + std::to_string(information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate + j].def) +
					"/move:" + std::to_string(information.variable.s_player.s_tabUnitAndSpec[information.variable.s_player.unitToCreate + j].movement),
					information.variable.statescreen, (SCREEN_WIDTH / 2) + 200, initspace += space)) {
					checkBarre++;
					break;
				}
			}
			if (checkBarre == validBarreSpec) break;
		}
	}

	tabplayer[information.variable.s_player.selectplayer]->GETthecitie(information.variable.s_player.selectCitie)->affichercitiemap(information);
}
void IHM::deleteAll(sysinfo& information, std::vector<Player*>& tabplayer) {
	logfileconsole("*********_________ Start DeleteAll _________*********");

	for (unsigned int i = 1; i < 80; i++)
		TTF_CloseFont(information.allTextures.font[i]);

	deleteDyTabPlayerAndTextures(information.allTextures.ground, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.groundSpec, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.unit, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.barLife, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.colorapp, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.colorappTile, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.miscTexture, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.txtecrantitre, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.txtnewgame, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.txtmainmap, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.txtcitiemap, "Texture");

	deleteDyTabPlayerAndTextures(information.allButton.ecrantitre, "Button");
	deleteDyTabPlayerAndTextures(information.allButton.player, "Button");
	deleteDyTabPlayerAndTextures(information.allButton.reload, "Button");
	deleteDyTabPlayerAndTextures(information.allButton.mainmap, "Button");
	deleteDyTabPlayerAndTextures(information.allButton.citie, "Button");

	deleteDyTabPlayerAndTextures(tabplayer, "player");
	SDL_DestroyRenderer(information.ecran.renderer);
	SDL_DestroyWindow(information.ecran.window);
	information.ecran.renderer = nullptr;
	information.ecran.window = nullptr;
	logfileconsole("*********_________ End DeleteAll _________*********");
}