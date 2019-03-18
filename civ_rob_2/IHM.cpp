/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.14
	file version : 1.6

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
#include "GamePlay.h"
#include "SaveReload.h"
#include "HashTable.h"

void IHM::initTile(Map& map)
{
	Tile blankTile;
	std::vector<Tile> blank;
	for (unsigned int i = 0; i < SCREEN_WIDTH / map.tileSize; i++)
	{
		map.screen.push_back(blank);
		for (unsigned int j = 0; j < SCREEN_HEIGHT / map.tileSize; j++)
		{
			map.screen[i].push_back(blankTile);
		}
	}
	for (unsigned int i = 0; i < map.mapSize / map.tileSize; i++)
	{
		map.maps.push_back(blank);
		for (unsigned int j = 0; j < map.mapSize / map.tileSize; j++) 
		{
			map.maps[i].push_back(blankTile);
		}
	}

}
void IHM::initFile(File& file)
{
	std::ofstream log;
	log.open(file.log, std::ofstream::out | std::ofstream::trunc);
	log.close();
}
void IHM::logfileconsole(const std::string msg)
{
	const std::string logtxt = "bin/log/log.txt";
	std::ofstream log(logtxt, std::ios::app);

	//std::time_t result = std::time(nullptr);
	//<< std::asctime(std::localtime(&result))

	if (log)
	{
		std::cout << std::endl << msg;
		log << std::endl << msg;
	}
	else
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}
void IHM::logSDLError(std::ostream &os, const std::string &msg)
{
	const std::string logtxt = "bin/log/log.txt";
	std::ofstream log(logtxt, std::ios::app);
	if (log)
	{
		os << msg << " error: " << SDL_GetError() << std::endl;
		log << msg << " error: " << SDL_GetError() << std::endl;
	}
	else
		std::cout << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt << std::endl;
}
bool IHM::initSDL(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font* font[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << std::endl << "SDL could not initialize! SDL_Error: " << SDL_GetError();
		return false;
	}
	else
	{
		window = SDL_CreateWindow("Civ_Rob_2.0",
			0, 0,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL);

		//	SDL_WINDOW_FULLSCREEN_DESKTOP or SDL_WINDOW_FULLSCREEN
		if (window == nullptr)
		{
			logSDLError(std::cout, "CreateWindow");
			SDL_Quit();
			return false;
		}
		else
			logfileconsole("CreateWindow Success");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		//| SDL_RENDERER_PRESENTVSYNC
		if (renderer == nullptr)
		{
			logSDLError(std::cout, "CreateRenderer");
			SDL_DestroyWindow(window);
			SDL_Quit();
			return false;
		}
		else
			logfileconsole("CreateRenderer Success");

		if (TTF_Init() != 0)
		{
			logSDLError(std::cout, "TTF_Init");
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			return false;
		}
		else
			logfileconsole("TTF_Init Success");

		for (Uint8 i = 1; i < MAX_FONT; i++)
			font[i] = TTF_OpenFont(fontFile.c_str(), i);

		logfileconsole("SDL_Init Success");
		return true;
	}
}
void IHM::calculImage(Sysinfo& sysinfo)
{
	logfileconsole("_calculImage Start_");

	// répertoire de base de l'image
	const std::string IPath = "image/"; 


	/* *********************************************************
		*				sysinfo.allTextures
	 ********************************************************* */
	// chargement des images du sol de la map
	/*
		sysinfo.allTextures.ground
	*/


	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ground/grass.bmp", "grass.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ground/water.bmp", "water.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ground/deepwater.bmp", "water.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle);
	
	
	// chargement de l'image de la toolbar
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "toolbar.bmp", "toolbar.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle);



	// chargement des spécifications du sol de la map
	/*
		sysinfo.allTextures.groundSpec
	*/
	unsigned int nbspecname = 0;
	std::string destroy = "", name = "";
	std::ifstream SPECNAME(sysinfo.file.SPECNAME);
	if (SPECNAME)
	{
		SPECNAME >> destroy;
		SPECNAME >> nbspecname;
		for (unsigned int i = 0; i < nbspecname; i++)
		{
			name = "";
			SPECNAME >> name;
			Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.groundSpec, sysinfo.var.statescreen, sysinfo.var.select,
				IPath + "spec/" + name, name, nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle);
		}
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.SPECNAME);



	// chargement du nombre d'unités ainsi que leur nom
	/*
		sysinfo.allTextures.unit
	*/
	for (unsigned int i = 0; i < sysinfo.var.s_player.unitNameMaxToCreate; i++)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.unit, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "units/" + sysinfo.var.s_player.tabUnit_Struct[i].name + ".bmp",
			sysinfo.var.s_player.tabUnit_Struct[i].name, nonTransparent, 100, 432, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle);


	
	/*
		sysinfo.allTextures.barLife
	*/
	sysinfo.var.statescreen = STATEmainmap;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.barLife, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "barre de vie/maxlife.bmp", "maxlife.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize / 10, no_angle);
	for (int i = 9; i >= 0; i--)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.barLife, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "barre de vie/0." + std::to_string(i) + "life.bmp", "0." + std::to_string(i) + "life.bmp", nonTransparent,
			-1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize / 10, no_angle);



	/*
		sysinfo.allTextures.colorapp
	*/
	for (unsigned int i = 0; i < 9; i++)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.colorapp, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "couleur d'apartenance/ColorPlayer" + std::to_string(i) + ".bmp", "ColorPlayer" + std::to_string(i) + ".bmp", nonTransparent,
			-1, -1, sysinfo.map.tileSize / 4, sysinfo.map.tileSize / 4, no_angle);


	/*
		sysinfo.allTextures.colorapptile
	*/
	for (unsigned int i = 0; i < 9; i++)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.colorapptile, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "couleur d'apartenance/ColorPlayer" + std::to_string(i) + ".bmp", "ColorPlayertile" + std::to_string(i) + ".bmp", (Uint8)96,
			-1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle);


	/*
		sysinfo.allTextures.titleScreen
	*/
	sysinfo.var.statescreen = STATEtitleScreen;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.titleScreen, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "earth.jpg", "earth.jpg", nonTransparent, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, NULL, NULL, no_angle, center);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.titleScreen, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "sdl_icone.bmp", "sdl_icone.bmp", nonTransparent, SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, NULL, NULL, no_angle, center_x);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.titleScreen, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "signal/destroyed.bmp", "destroyed.bmp", nonTransparent, SCREEN_WIDTH / 2, 0, NULL, NULL, no_angle, center_x);



	/*
		sysinfo.allTextures.miscTexture
	*/
	sysinfo.var.statescreen = STATEmainmap;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.miscTexture, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citie/citie.png", "citie.png", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle);



	// chargement du nombre de ville ainsi que leur nom
	unsigned int nbcitie = 0;
	std::string citie = "";
	std::ifstream CITIENAME(sysinfo.file.CITIENAME);
	if (CITIENAME)
	{
		CITIENAME >> destroy;
		CITIENAME >> nbcitie;
		sysinfo.var.s_player.citieNameMaxToCreate = nbcitie;
		for (unsigned int i = 0; i < nbcitie; i++)
		{
			CITIENAME >> citie;
			sysinfo.var.s_player.tabCitieName.push_back(citie);
		}
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.CITIENAME);

	//chargement du nombre de sauvegardes
	std::ifstream loadInfo(sysinfo.file.SaveInfo);
	unsigned int currentSave = 0, maxSave = 0;
	if (loadInfo)
	{
		loadInfo >> destroy;
		loadInfo >> maxSave;
		sysinfo.var.save.SETnbSave(maxSave);
		loadInfo >> destroy;
		for (unsigned int i = 0; i < sysinfo.var.save.GETnbSave(); i++)
		{
			loadInfo >> currentSave;
			sysinfo.var.save.GETtabSave().push_back(currentSave);
		}
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.SaveInfo);
	int spacemenu = 64, initspacemenu = 300;

	
	
	
	/* *********************************************************
		*				sysinfo.allButtons
	 ********************************************************* */


	 /*** STATEtitleScreen ***/
	sysinfo.var.statescreen = STATEtitleScreen;


	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		shaded, "New Game", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu,
		nonTransparent, no_angle, center);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		shaded, "Reload", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu,
		nonTransparent, no_angle, center);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		shaded, "Option", { 128, 128, 128, 255 }, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu,
		nonTransparent, no_angle, center);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		shaded, "Quit", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu,
		nonTransparent, no_angle, center);



	/*** STATEreload ***/
	sysinfo.var.statescreen = STATEreload;
	initspacemenu = 300;

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
		shaded, "Back", WriteColorButton, BackColorButton, 24, 96, 0,
		nonTransparent, no_angle, center_x);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
		shaded, "Remove all saves", WriteColorButton, BackColorButton, 24, 256, 0,
		nonTransparent, no_angle, center_x);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
		shaded, "Load", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2 - 200, 256,
		nonTransparent, no_angle, center_x);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
		shaded, "Remove", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2 + 200, 256,
		nonTransparent, no_angle, center_x);

	for (unsigned int i = 0; i < sysinfo.var.save.GETnbSave(); i++)
	{
		ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
			shaded, "Save : " + std::to_string(sysinfo.var.save.GETtabSave()[i]),
			WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu,
			nonTransparent, no_angle, center);
	}
		


	/*** STATEmainmap ***/
	sysinfo.var.statescreen = STATEmainmap;

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "screen Titre", WriteColorButton, BackColorButton, 24, 0, 0,
		nonTransparent, no_angle);

	sysinfo.var.select = selectcreate;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Create Unit", WriteColorButton, BackColorButton, 24, 0, 50,
		nonTransparent, no_angle);

	sysinfo.var.select = selectmove;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Move Unit", WriteColorButton, BackColorButton, 24, 0, 82,
		nonTransparent, no_angle);

	sysinfo.var.select = selectinspect;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Inspect", WriteColorButton, BackColorButton, 24, 0, 114,
		nonTransparent, no_angle);

	sysinfo.var.select = selectnothing;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Delete Unit", WriteColorButton, BackColorButton, 24, 0, 146,
		nonTransparent, no_angle);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Next Turn", WriteColorButton, BackColorButton, 24, 0, 800,
		nonTransparent, no_angle);


	/*** STATEcitiemap ***/
	sysinfo.var.statescreen = STATEcitiemap;
	sysinfo.var.select = selectnothing;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
		shaded, "Map", WriteColorButton, BackColorButton, 24, 96, 0,
		nonTransparent, no_angle, center_x);

	sysinfo.var.select = selectcreate;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font
		, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
		shaded, "Build", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 100,
		nonTransparent, no_angle, center_x);

	sysinfo.var.select = selectnothing;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
		shaded, "Food", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 132,
		nonTransparent, no_angle, center_x);

	sysinfo.var.select = selectmoveCitizen;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
		shaded, "Place Citizen", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2 - 200, 164,
		nonTransparent, no_angle, center_x);
	
	for (unsigned int i = 0; i < sysinfo.var.s_player.unitNameMaxToCreate; i++)
	{
		ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
			shaded, sysinfo.var.s_player.tabUnit_Struct[i].name, { 255, 64, 0, 255 }, BackColorButton, 24, 64, 400,
			nonTransparent, no_angle);
	}
		
	
	
	sysinfo.var.select = selectnothing;


	
	
	
	/* *********************************************************
		*				sysinfo.allTexte
	 ********************************************************* */


	/*** STATEtitleScreen ***/
	sysinfo.var.statescreen = STATEtitleScreen;

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.titleScreen,
		blended, "Game dev in c++ with SDL2.0.8", { 255, 127, 127, 255 }, NoColor, 24, 0, 0,
		nonTransparent, no_angle);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.titleScreen,
		blended, "La mort n'est que le commencement", { 127, 255, 127, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 800,
		nonTransparent, no_angle, center_x);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.titleScreen,
		blended, "Je suis devenu la mort,", { 127, 255, 127, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 832,
		nonTransparent, no_angle, center_x);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.titleScreen,
		blended, "le destructeur des Mondes", { 127, 255, 127, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 864,
		nonTransparent, no_angle, center_x);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.titleScreen,
		blended, "CIVILIZATION", { 0, 64, 255, 255 }, NoColor, 70, SCREEN_WIDTH / 2, 100,
		nonTransparent, no_angle, center_x);


	/*** STATEscreennewgame ***/
	sysinfo.var.statescreen = STATEscreennewgame;

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.newGame,
		blended, "Press Return or kpad_Enter to valid selection", { 255, 64, 64, 255 }, NoColor, 24, 0, 100,
		nonTransparent, no_angle);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.newGame,
		blended, "How many player(s) (max 9):", { 255, 0, 0, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 132,
		nonTransparent, no_angle, center_x);


	/*** STATEscreennewgame ***/
	sysinfo.var.statescreen = STATEmainmap;

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
		blended, "Select:", { 0, 64, 255, 255 }, NoColor, 24, 0, 600,
		nonTransparent, no_angle);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
		blended, "Turn :", { 0, 64, 255, 255 }, NoColor, 24, 0, 850,
		nonTransparent, no_angle);

	sysinfo.var.select = selectnothing;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
		blended, "selectnothing", { 0, 64, 255, 255 }, NoColor, 16, 78, 616,
		nonTransparent, no_angle, center_y);

	sysinfo.var.select = NotToSelect;
	for (unsigned int i = 0; i < nbcitie; i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
			blended, sysinfo.var.s_player.tabCitieName[i], { 255, 64, 0, 255 }, NoColor, 12, -1, -1,
			nonTransparent, no_angle);
	}
		

	sysinfo.var.select = selectcreate;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
		blended, "Scroll up or down", { 0, 64, 255, 255 }, NoColor, 20, 0, 332,
		nonTransparent, no_angle);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
		blended, "Right click to create", { 0, 64, 255, 255 }, NoColor, 18, 0, 364,
		nonTransparent, no_angle);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
		blended, "create : ", { 0, 64, 255, 255 }, NoColor, 18, 0, 400,
		nonTransparent, no_angle);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
		blended, "selectcreate", { 0, 64, 255, 255 }, NoColor, 16, 78, 616,
		nonTransparent, no_angle, center_y);

	for (unsigned int i = 0; i < sysinfo.var.s_player.unitNameMaxToCreate; i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.citieMap,
			blended, sysinfo.var.s_player.tabUnit_Struct[i].name, { 0, 64, 255, 255 }, NoColor, 18, 64, 400,
			nonTransparent, no_angle);
	}
		

	sysinfo.var.select = selectmove;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
		blended, "Pick the unit to move", { 0, 64, 255, 255 }, NoColor, 20, 0, 332,
		nonTransparent, no_angle);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
		blended, "with Right click", { 0, 64, 255, 255 }, NoColor, 20, 0, 364,
		nonTransparent, no_angle);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
		blended, "selectmove", { 0, 64, 255, 255 }, NoColor, 16, 78, 616,
		nonTransparent, no_angle, center_y);

	sysinfo.var.select = selectinspect;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
		blended, "selectinspect", { 0, 64, 255, 255 }, NoColor, 16, 78, 616,
		nonTransparent, no_angle, center_y);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
		blended, "Pick the unit to inspect", { 0, 64, 255, 255 }, NoColor, 20, 0, 332,
		nonTransparent, no_angle);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
		blended, "with Right click", { 0, 64, 255, 255 }, NoColor, 20, 0, 364,
		nonTransparent, no_angle);



	/*** STATEcitiemap ***/
	sysinfo.var.statescreen = STATEcitiemap;

	sysinfo.var.select = selectcreate;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.citieMap,
		blended, "Scroll up or down", { 64, 64, 255, 255 }, NoColor, 20, SCREEN_WIDTH - 300, 0,
		nonTransparent, no_angle);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.citieMap,
		blended, "Left click to Select", { 64, 64, 255, 255 }, NoColor, 20, SCREEN_WIDTH - 300, 32,
		nonTransparent, no_angle);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.citieMap,
		blended, "create : ", { 64, 64, 255, 255 }, NoColor, 20, SCREEN_WIDTH - 300, 64,
		nonTransparent, no_angle);

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.citieMap,
		blended, "selectcreate", { 64, 64, 255, 255 }, NoColor, 16, SCREEN_WIDTH - 300, 96,
		nonTransparent, no_angle);

	for (unsigned int i = 0; i < sysinfo.var.s_player.unitNameMaxToCreate; i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.citieMap,
			blended, "life:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[i].life) +
			"/atq:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[i].atq) +
			"/def:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[i].def) +
			"/move:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[i].movement),
			{ 255, 64, 0, 255 }, NoColor, 24, 0, 0, nonTransparent, no_angle);
	}
		

	
	

	/* *********************************************************
		*				HashTable
	 ********************************************************* */
	
	/*
		Attention : Optimisation de cherche par nom,
		* complexité en O(1) au lieu de O(n)
		* NE PAS UTILISER pour : -> sysinfo.allTextures.ground : déja optimal en O(1)
		*						 -> ### mettre ici les autres cas  


	*/

	/*** sysinfo.allTextures ***/


	sysinfo.allTextures.titleScreen.resize(sysinfo.allTextures.titleScreen.size() + sysinfo.allTextures.titleScreen.size() * INIT_SIZE_MULTIPLIER);
	fillTabHachage(sysinfo.allTextures.titleScreen, sysinfo.allTextures.titleScreenIndex);

	sysinfo.allTextures.unit.resize(sysinfo.allTextures.unit.size() + sysinfo.allTextures.unit.size() * INIT_SIZE_MULTIPLIER);
	fillTabHachage(sysinfo.allTextures.unit, sysinfo.allTextures.unitIndex);

	/*
	sysinfo.allTextes.titleScreen.resize(sysinfo.allTextes.titleScreen.size() + sysinfo.allTextes.titleScreen.size() * INIT_SIZE_MULTIPLIER);
	fillTabHachage(sysinfo.allTextes.titleScreen, sysinfo.allTextes.titleScreenIndex);

	sysinfo.allTextes.titleScreen.resize(sysinfo.allTextes.titleScreen.size() + sysinfo.allTextes.titleScreen.size() * INIT_SIZE_MULTIPLIER);
	fillTabHachage(sysinfo.allTextes.titleScreen, sysinfo.allTextes.titleScreenIndex);
	*/

	/*
	std::vector<Texture*> citie;
	std::vector<Texture*> miscTexture;
	
	*/


	/*** sysinfo.allTextes ***/


	sysinfo.allTextes.titleScreen.resize(sysinfo.allTextes.titleScreen.size() + sysinfo.allTextes.titleScreen.size() * INIT_SIZE_MULTIPLIER);
	fillTabHachage(sysinfo.allTextes.titleScreen, sysinfo.allTextes.titleScreenIndex);

	sysinfo.allTextes.mainMap.resize(sysinfo.allTextes.mainMap.size() + sysinfo.allTextes.mainMap.size() * INIT_SIZE_MULTIPLIER);
	fillTabHachage(sysinfo.allTextes.mainMap, sysinfo.allTextes.mainMapIndex);

	sysinfo.allTextes.newGame.resize(sysinfo.allTextes.newGame.size() + sysinfo.allTextes.newGame.size() * INIT_SIZE_MULTIPLIER);
	fillTabHachage(sysinfo.allTextes.newGame, sysinfo.allTextes.newGameIndex);

	sysinfo.allTextes.citieMap.resize(sysinfo.allTextes.citieMap.size() + sysinfo.allTextes.citieMap.size() * INIT_SIZE_MULTIPLIER);
	fillTabHachage(sysinfo.allTextes.citieMap, sysinfo.allTextes.citieMapIndex);

	
	
	/*** sysinfo.allButtons ***/

	sysinfo.allButton.titleScreen.resize(sysinfo.allButton.titleScreen.size() + sysinfo.allButton.titleScreen.size() * INIT_SIZE_MULTIPLIER);
	fillTabHachage(sysinfo.allButton.titleScreen, sysinfo.allButton.titleScreenIndex);

	sysinfo.allButton.reload.resize(sysinfo.allButton.reload.size() + sysinfo.allButton.reload.size() * INIT_SIZE_MULTIPLIER);
	fillTabHachage(sysinfo.allButton.reload, sysinfo.allButton.reloadIndex);

	sysinfo.allButton.mainMap.resize(sysinfo.allButton.mainMap.size() + sysinfo.allButton.mainMap.size() * INIT_SIZE_MULTIPLIER);
	fillTabHachage(sysinfo.allButton.mainMap, sysinfo.allButton.mainMapIndex);

	sysinfo.allButton.citieMap.resize(sysinfo.allButton.citieMap.size() + sysinfo.allButton.citieMap.size() * INIT_SIZE_MULTIPLIER);
	fillTabHachage(sysinfo.allButton.citieMap, sysinfo.allButton.citieMapIndex);

	/* Ne pas mettre allButton.player car initialisé dans NewGame */


	/* ### Don't put code below here ### */


	/* title screen init */
	sysinfo.var.select = selectnothing;
	sysinfo.var.statescreen = STATEtitleScreen;

	logfileconsole("_calculImage End_");
}
void IHM::eventSDL(Sysinfo& sysinfo)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:	// permet de quitter le jeu
			sysinfo.var.continuer = 0;
			break;
		case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
			switch (event.key.keysym.sym)
			{
			case SDLK_F5:
				GamePlay::groundGen(sysinfo);
				break;
			case SDLK_F6:
				deleteDyTabPlayerAndTextures(sysinfo.tabplayer, "player");
				for (unsigned int i = 0; i < 4; i++)
				{
					sysinfo.tabplayer.push_back(new Player("NoName" + std::to_string(i)));
				}
				GamePlay::newGameSettlerSpawn(sysinfo);
				break;
			case SDLK_ESCAPE:
				sysinfo.var.continuer = 0;
				break;
			case SDLK_UP:
				if (sysinfo.map.screenOffsetY > 0)
					sysinfo.map.screenOffsetY -= sysinfo.map.tileSize;
				IHM::changeScreenOffset(sysinfo);
				break;
			case SDLK_LEFT:
				if (sysinfo.map.screenOffsetX > 0)
					sysinfo.map.screenOffsetX -= sysinfo.map.tileSize;
				IHM::changeScreenOffset(sysinfo);
				break;
			case SDLK_DOWN:
				if (sysinfo.map.screenOffsetY < (sysinfo.map.mapSize - SCREEN_HEIGHT))
					sysinfo.map.screenOffsetY += sysinfo.map.tileSize;
				IHM::changeScreenOffset(sysinfo);
				break;
			case SDLK_RIGHT:
				if (sysinfo.map.screenOffsetX < sysinfo.map.mapSize - SCREEN_WIDTH)
					sysinfo.map.screenOffsetX += sysinfo.map.tileSize;
				IHM::changeScreenOffset(sysinfo);
				break;
			case SDLK_SPACE:
				GamePlay::nextTurn(sysinfo);
				break;
			case SDLK_b:
				KeyboardMouse::keySDLK_b(sysinfo);
				break;
			case SDLK_i:
				KeyboardMouse::keySDLK_i(sysinfo);
				break;
			case SDLK_KP_1:
				KeyboardMouse::keySDLK_KP_1(sysinfo);
				break;
			case SDLK_KP_2:
				KeyboardMouse::keySDLK_KP_2(sysinfo);
				break;
			case SDLK_KP_3:
				KeyboardMouse::keySDLK_KP_3(sysinfo);
				break;
			case SDLK_KP_4:
				KeyboardMouse::keySDLK_KP_4(sysinfo);
				break;
			case SDLK_KP_5:
				KeyboardMouse::keySDLK_KP_5(sysinfo);
				break;
			case SDLK_KP_6:
				KeyboardMouse::keySDLK_KP_6(sysinfo);
				break;
			case SDLK_KP_7:
				KeyboardMouse::keySDLK_KP_7(sysinfo);
				break;
			case SDLK_KP_8:
				KeyboardMouse::keySDLK_KP_8(sysinfo);
				break;
			case SDLK_KP_9:
				KeyboardMouse::keySDLK_KP_9(sysinfo);
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN: // test sur le type d'événement click souris (enfoncé)
			KeyboardMouse::mouse(sysinfo, event);
			break;
		case SDL_MOUSEWHEEL:
			KeyboardMouse::wheel(sysinfo, event.wheel.y);

			break;
		}

	}
}
void IHM::titleScreen(Sysinfo& sysinfo)
{
	logfileconsole("_titleScreens Start_");

	sysinfo.var.statescreen = STATEtitleScreen;
	sysinfo.var.select = selectnothing;
	SDL_RenderClear(sysinfo.screen.renderer);



	for (unsigned int i = 0; i < sysinfo.allTextures.titleScreenIndex.size(); i++)
	{
		sysinfo.allTextures.titleScreen[sysinfo.allTextures.titleScreenIndex[i]]
			->renderTextureTestStates(sysinfo.var.statescreen, sysinfo.var.select);
	}
		

	for (unsigned int i = 0; i < sysinfo.allTextes.titleScreenIndex.size(); i++)
	{
		sysinfo.allTextes.titleScreen[sysinfo.allTextes.titleScreenIndex[i]]
			->renderTextureTestStates(sysinfo.var.statescreen, sysinfo.var.select);
	}

	for (unsigned int i = 0; i < sysinfo.allButton.titleScreenIndex.size(); i++)
	{
		sysinfo.allButton.titleScreen[sysinfo.allButton.titleScreenIndex[i]]
			->renderButtonTexte(sysinfo.var.statescreen);
	}

	/* ### Don't put code below here ### */

	SDL_RenderPresent(sysinfo.screen.renderer);
	logfileconsole("_titleScreens End_");
}
void IHM::reloadScreen(Sysinfo& sysinfo)
{
	logfileconsole("_reloadScreen Start_");
	sysinfo.var.statescreen = STATEreload;
	SDL_RenderClear(sysinfo.screen.renderer);


	for (unsigned int i = 0; i < sysinfo.allButton.reloadIndex.size(); i++)
	{
		sysinfo.allButton.reload[sysinfo.allButton.reloadIndex[i]]->renderButtonTexte(sysinfo.var.statescreen);
	}
		

	/* ### Don't put code below here ### */

	SDL_RenderPresent(sysinfo.screen.renderer);
	logfileconsole("_reloadScreen End_");
}
void IHM::alwaysrender(Sysinfo& sysinfo)
{
	//clock_t t1, t2;
	//t1 = clock();

	switch (sysinfo.var.statescreen)
	{
	case STATEmainmap:
		SDL_RenderClear(sysinfo.screen.renderer);
		afficherSupertiles(sysinfo);

		// affiche la texture grise de la toolbar
		for (unsigned int i = 0; i < sysinfo.map.toolBarSize; i++)
		{
			for (unsigned int j = 0; j < SCREEN_HEIGHT / sysinfo.map.tileSize; j++)
				sysinfo.allTextures.ground[3]->render(i * sysinfo.map.tileSize, j * sysinfo.map.tileSize);
		}



		for (unsigned int i = 0; i < sysinfo.allTextes.mainMapIndex.size(); i++)
		{
			sysinfo.allTextes.mainMap[sysinfo.allTextes.mainMapIndex[i]]->renderTextureTestStates(sysinfo.var.statescreen, sysinfo.var.select);
		}

		for (unsigned int i = 0; i < sysinfo.allButton.mainMapIndex.size(); i++)
		{
			sysinfo.allButton.mainMap[sysinfo.allButton.mainMapIndex[i]]->renderButtonTexte(sysinfo.var.statescreen);
		}
			
		for (unsigned int i = 0; i < sysinfo.allButton.playerIndex.size(); i++)
		{
			sysinfo.allButton.player[sysinfo.allButton.playerIndex[i]]->renderButtonTexte(sysinfo.var.statescreen);
		}
			



		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, std::to_string(sysinfo.var.nbturn), { 0, 64, 255, 255 }, NoColor, 24, 80, 850, no_angle);

		// affiche les unités pour rendre l'unité à créer
		if (sysinfo.var.select == selectcreate)
		{
			if (sysinfo.var.s_player.unitNameToCreate.compare("") != 0)
			{
				sysinfo.allTextures.unit[searchIndex(sysinfo.var.s_player.unitNameToCreate, sysinfo.allTextures.unit)]->render(100, 432);
			}
		}
		else if (sysinfo.var.select == selectmove)
		{
			if (sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
			{
				sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->cmpblit();
			}
		}
		else if (sysinfo.var.select == selectinspect)
		{
			// affiche les stats de l'unité inspecté
			if (sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
			{
				sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->afficherstat(sysinfo);
			}
		}

		if (sysinfo.tabplayer.size() != 0)
		{
			for (unsigned int i = 0; i < sysinfo.tabplayer.size(); i++) 
			{
				if (sysinfo.tabplayer[i]->GETtabunit().size() != 0) {
					for (unsigned int j = 0; j < sysinfo.tabplayer[i]->GETtabunit().size(); j++)
					{
						// affiche pour chaque joueurs les unités existantes (avec les stats)
						sysinfo.tabplayer[i]->GETtheunit(j)->afficher(sysinfo, i);
					}
				}
				if (sysinfo.tabplayer[i]->GETtabcities().size() != 0)
				{
					for (unsigned int j = 0; j < sysinfo.tabplayer[i]->GETtabcities().size(); j++)
					{
						// affiche pour chaque joueurs les cités existantes
						sysinfo.tabplayer[i]->GETthecitie(j)->afficher(sysinfo);
					}
				}
			}
		}
		break;
	case STATEcitiemap:
		if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabcities().size() > 0)
		{
			if (sysinfo.var.s_player.selectCitie != -1)
			{
				if (sysinfo.var.s_player.selectCitie < (int)sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabcities().size())
					citiemap(sysinfo);
			}
		}
		break;
	}
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		blended, std::to_string(sysinfo.screen.avgFPS), { 0, 64, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 50, center_x);

	/* ### Don't put code below here ### */

	SDL_RenderPresent(sysinfo.screen.renderer);
	//t2 = clock();
	//cout << endl << "temps d'execution de alwaysrender : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
}
void IHM::changeScreenOffset(Sysinfo& sysinfo)
{
	Uint8 m = 0, n = 0;
	for (unsigned int i = 0; i < sysinfo.map.maps.size(); i++) 
	{
		for (unsigned int j = 0; j < sysinfo.map.maps[i].size(); j++)
		{
			if (sysinfo.map.maps[i][j].tile_x >= sysinfo.map.screenOffsetX && sysinfo.map.maps[i][j].tile_x < (sysinfo.map.screenOffsetX + SCREEN_WIDTH)) 
			{
				if (sysinfo.map.maps[i][j].tile_y >= sysinfo.map.screenOffsetY && sysinfo.map.maps[i][j].tile_y < (sysinfo.map.screenOffsetY + SCREEN_HEIGHT))
				{
					sysinfo.map.screen[m][n] = sysinfo.map.maps[i][j];
					sysinfo.map.screen[m][n].indexX = m;
					sysinfo.map.screen[m][n].indexY = n;
					sysinfo.map.screen[m][n].tile_x -= sysinfo.map.screenOffsetX;
					sysinfo.map.screen[m][n].tile_y -= sysinfo.map.screenOffsetY;

					n = (n + 1) % sysinfo.map.screen[m].size();
					if (n == 0)
						m++;
					if (m == (sysinfo.map.screen.size() - 1) && (n == sysinfo.map.screen[m].size()))
						return;
				}
			}
		}
	}
}
void IHM::afficherSupertiles(Sysinfo& sysinfo)
{
	//clock_t t1, t2;
	//t1 = clock();
	
	for (unsigned int m = 0; m < sysinfo.map.screen.size(); m++)
	{
		for (unsigned int n = 0; n < sysinfo.map.screen[m].size(); n++)
		{
			switch (sysinfo.map.screen[m][n].tile_ground)
			{
			case grass:
				sysinfo.allTextures.ground[0]->render(sysinfo.map.screen[m][n].tile_x, sysinfo.map.screen[m][n].tile_y);
				break;
			case water:
				sysinfo.allTextures.ground[1]->render(sysinfo.map.screen[m][n].tile_x, sysinfo.map.screen[m][n].tile_y);
				break;
			case deepwater:
				sysinfo.allTextures.ground[2]->render(sysinfo.map.screen[m][n].tile_x, sysinfo.map.screen[m][n].tile_y);
				break;
			}

			if (sysinfo.map.screen[m][n].tile_spec > 0)
			{
				sysinfo.allTextures.groundSpec[sysinfo.map.screen[m][n].tile_spec - 1]
					->render(sysinfo.map.screen[m][n].tile_x, sysinfo.map.screen[m][n].tile_y);
			}
			if (sysinfo.map.screen[m][n].appartenance != -1)
			{
				sysinfo.allTextures.colorapptile[sysinfo.map.screen[m][n].appartenance]
					->render(sysinfo.map.screen[m][n].tile_x, sysinfo.map.screen[m][n].tile_y);
			}
		}
	}
	//t2 = clock();
	//std::cout << std::endl << "temps d'execution de alwaysrender : " + std::to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
	
}
void IHM::citiemap(Sysinfo& sysinfo)
{
	SDL_RenderClear(sysinfo.screen.renderer);
	std::string buildName;
	unsigned int initspace = 96, space = 32;

	
	sysinfo.allButton.citieMap[searchIndex("Map", sysinfo.allButton.citieMap)]->renderButtonTexte(sysinfo.var.statescreen);
	sysinfo.allButton.citieMap[searchIndex("Build", sysinfo.allButton.citieMap)]->renderButtonTexte(sysinfo.var.statescreen);
	sysinfo.allButton.citieMap[searchIndex("Food", sysinfo.allButton.citieMap)]->renderButtonTexte(sysinfo.var.statescreen);
	sysinfo.allButton.citieMap[searchIndex("Place Citizen", sysinfo.allButton.citieMap)]->renderButtonTexte(sysinfo.var.statescreen);

	if (sysinfo.var.select == selectcreate)
	{
		initspace = 96;
		for (unsigned int j = 0; j < 10; j++)
		{
			if (sysinfo.var.s_player.unitToCreate + j < sysinfo.var.s_player.unitNameMaxToCreate)
				buildName = sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].name;
			else
				break;

			sysinfo.allButton.citieMap[searchIndex(buildName, sysinfo.allButton.citieMap)]
				->renderButtonTexte(sysinfo.var.statescreen, SCREEN_WIDTH / 2, initspace += space);
			sysinfo.allTextures.unit[searchIndex(buildName, sysinfo.allTextures.unit)]
				->render((SCREEN_WIDTH / 2) - 50, initspace);
			sysinfo.allTextes.citieMap[searchIndex(
				"life:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].life) +
				"/atq:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].atq) +
				"/def:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].def) +
				"/move:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].movement),
				sysinfo.allTextes.citieMap)]
				->render((SCREEN_WIDTH / 2) + 200, initspace);
		}

		sysinfo.allTextes.citieMap[searchIndex("Scroll up or down", sysinfo.allTextes.citieMap)]->render();
		sysinfo.allTextes.citieMap[searchIndex("Left click to Select", sysinfo.allTextes.citieMap)]->render();
		sysinfo.allTextes.citieMap[searchIndex("create : ", sysinfo.allTextes.citieMap)]->render();
		sysinfo.allTextes.citieMap[searchIndex("selectcreate", sysinfo.allTextes.citieMap)]->render();
	}

	sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETthecitie(sysinfo.var.s_player.selectCitie)->affichercitiemap(sysinfo);
}
void IHM::countFrame(Screen& screen)
{
	if (screen.enableFPS)
	{
		screen.avgFPS = (int)ceil(screen.countedFrames / (screen.fpsTimer.getTicks() / 1000.f));
		if (screen.avgFPS > 20000)
			screen.avgFPS = 0;
		++screen.countedFrames;
	}
}
void IHM::deleteAll(Sysinfo& sysinfo)
{
	logfileconsole("*********_________ Start DeleteAll _________*********");

	for (unsigned int i = 1; i < MAX_FONT; i++)
		TTF_CloseFont(sysinfo.allTextures.font[i]);

	deleteDyTabPlayerAndTextures(sysinfo.allTextures.ground, "Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.groundSpec, "Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.unit, "Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.barLife, "Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.colorapp, "Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.colorapptile, "Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.miscTexture, "Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.titleScreen, "Texture");


	deleteDyTabPlayerAndTextures(sysinfo.allTextes.titleScreen, "Texte");
	deleteDyTabPlayerAndTextures(sysinfo.allTextes.newGame, "Texte");
	deleteDyTabPlayerAndTextures(sysinfo.allTextes.mainMap, "Texte");
	deleteDyTabPlayerAndTextures(sysinfo.allTextes.citieMap, "Texte");

	deleteDyTabPlayerAndTextures(sysinfo.allButton.titleScreen, "Button");
	deleteDyTabPlayerAndTextures(sysinfo.allButton.player, "Button");
	deleteDyTabPlayerAndTextures(sysinfo.allButton.reload, "Button");
	deleteDyTabPlayerAndTextures(sysinfo.allButton.mainMap, "Button");
	deleteDyTabPlayerAndTextures(sysinfo.allButton.citieMap, "Button");

	deleteDyTabPlayerAndTextures(sysinfo.tabplayer, "player");
	SDL_DestroyRenderer(sysinfo.screen.renderer);
	SDL_DestroyWindow(sysinfo.screen.window);
	sysinfo.screen.renderer = nullptr;
	sysinfo.screen.window = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	/* ### Don't put code below here ### */

	logfileconsole("*********_________ End DeleteAll _________*********");
}

/*
*	End Of File
*/