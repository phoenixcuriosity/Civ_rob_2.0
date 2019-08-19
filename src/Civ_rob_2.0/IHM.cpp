/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.17
	file version : 1.14

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


/* *********************************************************
 *					Variable Globale					   *
 ********************************************************* */

std::ofstream logger;
Sysinfo* ptrSysinfo;

/* *********************************************************
 *				START INITIALISATION					   *
 ********************************************************* */


/*
* NAME : initTile
* ROLE : Initialisation des cases de la map en fonction de sa taille
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : Initialisation de map.screen et map.maps
* RETURNED VALUE    : void
*/
void IHM::initTile(Map& map)
{
	Tile blankTile;
	std::vector<Tile> blank;
	for (unsigned int i(0); i < map.mapSize / map.tileSize; i++)
	{
		map.maps.push_back(blank);
		for (unsigned int j(0); j < map.mapSize / map.tileSize; j++) 
		{
			map.maps[i].push_back(blankTile);
		}
	}

}

Uint8 xmlGiveStateType(std::string type)
{
	if (type.compare("STATEnothing") == 0)
	{
		return STATEnothing;
	}
	else if(type.compare("STATEtitleScreen") == 0)
	{
		return STATEtitleScreen;
	}
	else if (type.compare("STATEscreennewgame") == 0)
	{
		return STATEscreennewgame;
	}
	else if (type.compare("STATEreload") == 0)
	{
		return STATEreload;
	}
	else if (type.compare("STATEmainmap") == 0)
	{
		return STATEmainmap;
	}
	else if (type.compare("STATEscience") == 0)
	{
		return STATEscience;
	}
	else if (type.compare("STATEcitiemap") == 0)
	{
		return STATEcitiemap;
	}
	else
	{
		return STATEnothing;
	}
}

Uint8 xmlGiveSelectType(std::string type)
{
	if (type.compare("selectnothing") == 0)
	{
		return selectnothing;
	}
	else if (type.compare("NotToSelect") == 0)
	{
		return NotToSelect;
	}
	else if (type.compare("selectcreate") == 0)
	{
		return selectcreate;
	}
	else if (type.compare("selectinspect") == 0)
	{
		return selectinspect;
	}
	else if (type.compare("selectmove") == 0)
	{
		return selectmove;
	}
	else if (type.compare("selectmoveCitizen") == 0)
	{
		return selectmoveCitizen;
	}
	else
	{
		return selectnothing;
	}
}

std::unordered_map<std::string, Texte*>& xmlGiveTexteConteneur(AllTextes& allTextes, std::string type)
{
	if (type.compare("titleScreen") == 0)
	{
		return allTextes.titleScreen;
	}
	else if (type.compare("newGame") == 0)
	{
		return allTextes.newGame;
	}
	else if (type.compare("mainMap") == 0)
	{
		return allTextes.mainMap;
	}
	else if (type.compare("citieMap") == 0)
	{
		return allTextes.citieMap;
	}
	else
	{
		return allTextes.titleScreen;
	}
}

Texte_Type xmlGiveTexteType(std::string type)
{
	if (type.compare("blended") == 0)
	{
		return blended;
	}
	else if (type.compare("shaded") == 0)
	{
		return shaded;
	}
	else
	{
		return blended;
	}
}

SDL_Color xmlGiveColor(std::string type)
{
	if (type.compare("Black") == 0)
	{
		return Black;
	}
	else if (type.compare("White") == 0)
	{
		return White;
	}
	else if (type.compare("Red") == 0)
	{
		return Red;
	}
	else if (type.compare("Green") == 0)
	{
		return Green;
	}
	else if (type.compare("Blue") == 0)
	{
		return Blue;
	}
	else if (type.compare("Blue") == 0)
	{
		return Blue;
	}
	else if (type.compare("Yellow") == 0)
	{
		return Yellow;
	}
	else if (type.compare("WriteColorButton") == 0)
	{
		return WriteColorButton;
	}
	else if (type.compare("BackColorButton") == 0)
	{
		return BackColorButton;
	}
	else if (type.compare("NoColor") == 0)
	{
		return NoColor;
	}
	else
	{
		return NoColor;
	}
}

Transparance_Type xmlGiveAlpha(std::string type)
{
	if (type.compare("nonTransparent") == 0)
	{
		return nonTransparent;
	}
	else if (type.compare("semiTransparent") == 0)
	{
		return semiTransparent;
	}
	else if (type.compare("transparent") == 0)
	{
		return transparent;
	}
	else
	{
		return nonTransparent;
	}
}

Rotation_Type xmlGiveAngle(std::string type)
{
	if (type.compare("no_angle") == 0)
	{
		return no_angle;
	}
	else if (type.compare("inverse") == 0)
	{
		return inverse;
	}
	else
	{
		return no_angle;
	}
}

Center_Type xmlGiveCenter(std::string type)
{
	if (type.compare("nocenter") == 0)
	{
		return nocenter;
	}
	else if (type.compare("center_x") == 0)
	{
		return center_x;
	}
	else if (type.compare("center_y") == 0)
	{
		return center_y;
	}
	else if (type.compare("center") == 0)
	{
		return center;
	}
	else
	{
		return nocenter;
	}
}

/*
* NAME : initFile
* ROLE : Initialisation des fichiers : log
* INPUT  PARAMETERS : struct File& : nom des fichiers
* OUTPUT PARAMETERS : Initialisation de log.txt
* RETURNED VALUE    : void
*/
void IHM::initFile(File& file)
{
	logger.open(file.log, std::ofstream::out | std::ofstream::trunc);
	if (!logger.is_open())
	{
		exit(EXIT_FAILURE);
	}
}


/*
* NAME : logfileconsole
* ROLE : Transmission du message sur la console et dans le fichier log.txt
* INPUT  PARAMETERS : const std::string msg : message
* OUTPUT PARAMETERS : message dans la console et le log.txt
* RETURNED VALUE    : void
*/
void IHM::logfileconsole(const std::string msg)
{
	time_t now(time(0));
	struct tm  tstruct;
	char  buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%F %X", &tstruct);

	std::cout << std::endl << buf << "      " << msg;
	logger << std::endl << buf << "      " << msg;

}


/*
* NAME : logSDLError
* ROLE : SDL erreur
* INPUT  PARAMETERS : std::ostream &os, const std::string &msg
* OUTPUT PARAMETERS : message d'erreur dans la console
* RETURNED VALUE    : void
*/
void IHM::logSDLError(std::ostream &os, const std::string &msg)
{
	
	os << msg << " error: " << SDL_GetError() << std::endl;
	logger << msg << " error: " << SDL_GetError() << std::endl;
	
}





/*
* NAME : initSDL
* ROLE : Initialisation de la SDL fenetre et renderer ainsi que le tableau de police de font
* INPUT  PARAMETERS : SDL_Window*& : pointeur sur la fenetre de la SDL
* INPUT  PARAMETERS : SDL_Renderer*& : pointeur sur le Renderer de la SDL
* INPUT  PARAMETERS : TTF_Font*[] : pointeur sur le tableau de police de font
* OUTPUT PARAMETERS : message dans la console et le log.txt
* RETURNED VALUE    : bool : true = pas de d'erreur lors de l'initialisation de la SDL
*/
bool IHM::initSDL(Screen& screen, TTF_Font* font[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << std::endl << "SDL could not initialize! SDL_Error: " << SDL_GetError();
		return false;
	}
	else
	{
		

		screen.window = SDL_CreateWindow("Civ_Rob_2.0",
			0, 0,
			screen.screenWidth, screen.screenHeight,
			SDL_WINDOW_OPENGL);

		//	SDL_WINDOW_FULLSCREEN_DESKTOP or SDL_WINDOW_FULLSCREEN
		if (screen.window == nullptr)
		{
			logSDLError(std::cout, "CreateWindow");
			SDL_Quit();
			return false;
		}
		else
			logfileconsole("CreateWindow Success");
		screen.renderer = SDL_CreateRenderer(screen.window, -1, SDL_RENDERER_ACCELERATED);
		//| SDL_RENDERER_PRESENTVSYNC
		if (screen.renderer == nullptr)
		{
			logSDLError(std::cout, "CreateRenderer");
			SDL_DestroyWindow(screen.window);
			SDL_Quit();
			return false;
		}
		else
			logfileconsole("[INFO]___: CreateRenderer Success");

		if (TTF_Init() != 0)
		{
			logSDLError(std::cout, "TTF_Init");
			SDL_DestroyRenderer(screen.renderer);
			SDL_DestroyWindow(screen.window);
			SDL_Quit();
			return false;
		}
		else
			logfileconsole("[INFO]___: TTF_Init Success");

		for (Uint8 i(1); i < MAX_FONT; i++)
			font[i] = TTF_OpenFont(fontFile.c_str(), i);

		logfileconsole("[INFO]___: SDL_Init Success");
		return true;
	}
}


/*
* NAME : calculImage
* ROLE : Initialisation des Textures, des Textes et des Buttons
* ROLE : Enregistrement des pointeurs dans des tableaux
* ROLE : Hachage des noms des Textures (et classes filles) pour une recherche en complexité en O(1)
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Tableaux de pointeurs vers les Textures (et classes filles)
* RETURNED VALUE    : void
*/
void IHM::calculImage(Sysinfo& sysinfo)
{
	logfileconsole("[INFO]___: [START] : calculImage");

	ptrSysinfo = &sysinfo;

	// répertoire de base de l'image
	const std::string IPath = "bin/image/"; 


	/* *********************************************************
	 *				START sysinfo.allTextures				   *
	 ********************************************************* */


	// chargement des images du sol de la map
	/*
		sysinfo.allTextures.ground
	*/
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ground/grass.bmp", "grass.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ground/water.bmp", "water.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ground/deepwater.bmp", "deepwater.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);
	
	
	// chargement de l'image de la toolbar
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "toolbar.bmp", "toolbar.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);



	// chargement des spécifications du sol de la map
	/*
		sysinfo.allTextures.groundSpec
	*/
	unsigned int nbspecname(0);
	std::string destroy(""), name("");
	std::ifstream SPECNAME(sysinfo.file.SPECNAME);
	if (SPECNAME)
	{
		SPECNAME >> destroy;
		SPECNAME >> nbspecname;
		for (unsigned int i(0); i < nbspecname; i++)
		{
			name = "";
			SPECNAME >> name;
			Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.groundSpec, sysinfo.var.statescreen, sysinfo.var.select,
				IPath + "spec/" + name, name, nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);
		}
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.SPECNAME);



	// chargement du nombre d'unités ainsi que leur nom
	/*
		sysinfo.allTextures.unit
	*/
	for (unsigned int i(0); i < sysinfo.var.s_player.tabUnit_Struct.size(); i++)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.unit, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "units/" + sysinfo.var.s_player.tabUnit_Struct[i].name + ".bmp",
			sysinfo.var.s_player.tabUnit_Struct[i].name, nonTransparent, 100, 432, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);


	
	/*
		sysinfo.allTextures.barLife
	*/
	sysinfo.var.statescreen = STATEmainmap;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.barLife, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "barre de vie/maxlife.bmp", "maxlife.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize / 10, no_angle);
	for (int i(9); i >= 0; i--)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.barLife, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "barre de vie/0." + std::to_string(i) + "life.bmp", "0." + std::to_string(i) + "life.bmp", nonTransparent,
			-1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize / 10, no_angle, nocenter);



	/*
		sysinfo.allTextures.colorapp
	*/
	for (unsigned int i(0); i < 9; i++)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.colorapp, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "couleur d'apartenance/ColorPlayer" + std::to_string(i) + ".bmp", "ColorPlayer" + std::to_string(i) + ".bmp", nonTransparent,
			-1, -1, sysinfo.map.tileSize / 4, sysinfo.map.tileSize / 4, no_angle, nocenter);


	/*
		sysinfo.allTextures.colorapptile
	*/
	for (unsigned int i(0); i < 9; i++)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.colorapptile, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "couleur d'apartenance/ColorPlayer" + std::to_string(i) + ".bmp", "ColorPlayertile" + std::to_string(i) + ".bmp", (Transparance_Type)96,
			-1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);


	/*
		sysinfo.allTextures.titleScreen
	*/
	sysinfo.var.statescreen = STATEtitleScreen;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.titleScreen, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "earth.jpg", "earth.jpg", nonTransparent, sysinfo.screen.screenWidth / 2, sysinfo.screen.screenHeight / 2, NULL, NULL, no_angle, center);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.titleScreen, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "sdl_icone.bmp", "sdl_icone.bmp", nonTransparent, sysinfo.screen.screenWidth / 2, sysinfo.screen.screenHeight - 100, NULL, NULL, no_angle, center_x);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.titleScreen, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "signal/destroyed.bmp", "destroyed.bmp", nonTransparent, sysinfo.screen.screenWidth / 2, 0, NULL, NULL, no_angle, center_x);



	/*
		sysinfo.allTextures.citieMap
	*/
	sysinfo.var.statescreen = STATEmainmap;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citie/citie.png", "citie.png", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);



	// chargement du nombre de ville ainsi que leur nom
	unsigned int nbcitie(0);
	std::string citie("");
	std::ifstream CITIENAME(sysinfo.file.CITIENAME);
	if (CITIENAME)
	{
		CITIENAME >> destroy;
		CITIENAME >> nbcitie;
		sysinfo.var.s_player.citieNameMaxToCreate = nbcitie;
		for (unsigned int i(0); i < nbcitie; i++)
		{
			CITIENAME >> citie;
			sysinfo.var.s_player.tabCitieName.push_back(citie);
		}
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.CITIENAME);

	//chargement du nombre de sauvegardes
	std::ifstream loadInfo(sysinfo.file.SaveInfo);
	unsigned int currentSave(0), maxSave(0);
	if (loadInfo)
	{
		loadInfo >> destroy;
		loadInfo >> maxSave;
		sysinfo.var.save.SETnbSave(maxSave);
		loadInfo >> destroy;
		for (unsigned int i(0); i < sysinfo.var.save.GETnbSave(); i++)
		{
			loadInfo >> currentSave;
			sysinfo.var.save.GETtabSave().push_back(currentSave);
		}
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.SaveInfo);
	int spacemenu(64), initspacemenu(300);

	
	/* *********************************************************
	 *				END sysinfo.allTextures					   *
	 ********************************************************* */


	/* *********************************************************
	 *				START sysinfo.allButtons				   *
	 ********************************************************* */


	 /*** STATEtitleScreen ***/
	sysinfo.var.statescreen = STATEtitleScreen;


	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		shaded, "New Game", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu,
		nonTransparent, no_angle, center);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		shaded, "Reload", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu += spacemenu,
		nonTransparent, no_angle, center);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		shaded, "Option", { 128, 128, 128, 255 }, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu += spacemenu,
		nonTransparent, no_angle, center);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		shaded, "Quit", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu += spacemenu,
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
		shaded, "Load", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2 - 200, 256,
		nonTransparent, no_angle, center_x);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
		shaded, "Remove", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2 + 200, 256,
		nonTransparent, no_angle, center_x);

	for (unsigned int i(0); i < sysinfo.var.save.GETnbSave(); i++)
	{
		ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
			shaded, "Save : " + std::to_string(sysinfo.var.save.GETtabSave()[i]),
			WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu += spacemenu,
			nonTransparent, no_angle, center);
	}
		


	/*** STATEmainmap ***/
	sysinfo.var.statescreen = STATEmainmap;

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "screen Titre", WriteColorButton, BackColorButton, 24, 0, 0,
		nonTransparent, no_angle, nocenter);

	sysinfo.var.select = selectcreate;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Create Unit", WriteColorButton, BackColorButton, 24, 0, 50,
		nonTransparent, no_angle, nocenter);

	sysinfo.var.select = selectmove;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Move Unit", WriteColorButton, BackColorButton, 24, 0, 82,
		nonTransparent, no_angle, nocenter);

	sysinfo.var.select = selectinspect;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Inspect", WriteColorButton, BackColorButton, 24, 0, 114,
		nonTransparent, no_angle, nocenter);

	sysinfo.var.select = selectnothing;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Delete Unit", WriteColorButton, BackColorButton, 24, 0, 146,
		nonTransparent, no_angle, nocenter);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Next Turn", WriteColorButton, BackColorButton, 24, 0, 800,
		nonTransparent, no_angle, nocenter);


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
		shaded, "Build", WriteColorButton, BackColorButton, 24, sysinfo.screen.screenWidth / 2 - 200, 100,
		nonTransparent, no_angle, center_x);

	sysinfo.var.select = selectnothing;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
		shaded, "Food", WriteColorButton, BackColorButton, 24, sysinfo.screen.screenWidth / 2 - 200, 132,
		nonTransparent, no_angle, center_x);

	sysinfo.var.select = selectmoveCitizen;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
		shaded, "Place Citizen", WriteColorButton, BackColorButton, 24, sysinfo.screen.screenWidth / 2 - 200, 164,
		nonTransparent, no_angle, center_x);
	
	for (unsigned int i(0); i < sysinfo.var.s_player.tabUnit_Struct.size(); i++)
	{
		ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
			shaded, sysinfo.var.s_player.tabUnit_Struct[i].name, { 255, 64, 0, 255 }, BackColorButton, 24, 64, 400,
			nonTransparent, no_angle, nocenter);
	}
		
	
	
	sysinfo.var.select = selectnothing;


	/* *********************************************************
	 *				END sysinfo.allButtons					   *
	 ********************************************************* */
	
	
	/* *********************************************************
	 *				START sysinfo.allTexte					   *
	 ********************************************************* */


	tinyxml2::XMLDocument texteFile;
	texteFile.LoadFile(sysinfo.file.Texte.c_str());

	if (texteFile.ErrorID() == 0)
	{
		readXmlTexte(texteFile, sysinfo.screen.renderer, sysinfo.allTextures.font, sysinfo.allTextes, sysinfo.screen.screenWidth, sysinfo.screen.screenHeight);
	}

	/*** STATEmainmap ***/
	sysinfo.var.statescreen = STATEmainmap;

	for (unsigned int i(0); i < MAX_POP; i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.number,
			blended, std::to_string(i), { 255, 255, 255, 255 }, NoColor, 18, 1000, 1000,
			nonTransparent, no_angle, nocenter);
	}

	sysinfo.var.select = NotToSelect;
	for (unsigned int i(0); i < nbcitie; i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
			blended, sysinfo.var.s_player.tabCitieName[i], { 255, 64, 0, 255 }, NoColor, 12, -1, -1,
			nonTransparent, no_angle, nocenter);
	}
		

	sysinfo.var.select = selectcreate;
	for (unsigned int i(0); i < sysinfo.var.s_player.tabUnit_Struct.size(); i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.citieMap,
			blended, sysinfo.var.s_player.tabUnit_Struct[i].name, { 0, 64, 255, 255 }, NoColor, 18, 64, 400,
			nonTransparent, no_angle, nocenter);
	}
		
	/*** STATEcitiemap ***/
	sysinfo.var.statescreen = STATEcitiemap;
	sysinfo.var.select = selectcreate;
	for (unsigned int i(0); i < sysinfo.var.s_player.tabUnit_Struct.size(); i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.citieMap,
			blended, "life:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[i].life) +
			"/atq:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[i].atq) +
			"/def:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[i].def) +
			"/move:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[i].movement),
			{ 255, 64, 0, 255 }, NoColor, 24, 0, 0, nonTransparent, no_angle, nocenter);
	}
		
	/* *********************************************************
	 *					END sysinfo.allTexte				   *
	 ********************************************************* */
	

	/* ### Don't put code below here ### */

	logfileconsole("[INFO]___: [END] : calculImage");
}

/*
* NAME : readXmlTexte
* ROLE : Initialisation des Textes par la lecture du fichier Texte.xml
* ROLE : Enregistrement des pointeurs dans des tableaux
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Tableau de pointeurs vers les Texte
* RETURNED VALUE    : void
*/
void IHM::readXmlTexte(	tinyxml2::XMLDocument& texteFile,
						SDL_Renderer*& renderer,
						TTF_Font* font[],
						AllTextes& allTextes,
						Uint16 screenWidth,
						Uint16 screenHeight)
{
	const char* root("Config");


	const char* s_M_Texte("Texte"),
		* s_Statescreen("Statescreen"),
		* s_Select("Select"),
		* s_TexteName("TexteName"),
		* s_Type("Type"),
		* s_Texte("Texte"),
		* s_FontColor("FontColor"),
		* s_FontColor_Simple("Simple"),
		* s_FontColor_Simple_Condition("Condition"),
		* s_FontColor_Simple_Color("Color"),
		* s_FontColor_Complexe("Complexe"),
		* s_FontColor_Complexe_condition("Condition"),
		* s_FontColor_Complexe_R("R"),
		* s_FontColor_Complexe_G("G"),
		* s_FontColor_Complexe_B("B"),
		* s_FontColor_Complexe_Alpha("Alpha"),
		* s_BackColor("FontColor"),
		* s_BackColor_Simple("Simple"),
		* s_BackColor_Simple_Condition("Condition"),
		* s_BackColor_Simple_Color("Color"),
		* s_BackColor_Complexe("Complexe"),
		* s_BackColor_Complexe_condition("Condition"),
		* s_BackColor_Complexe_R("R"),
		* s_BackColor_Complexe_G("G"),
		* s_BackColor_Complexe_B("B"),
		* s_BackColor_Complexe_Alpha("Alpha"),
		* s_Size("Size"),
		* s_X("X"),
		* s_Y("Y"),
		* s_Alpha("Alpha"),
		* s_Angle("Angle"),
		* s_Center("Center");

	tinyxml2::XMLNode* node(texteFile.FirstChildElement(root)->FirstChildElement(s_M_Texte));

	SDL_Color fontColor, backColor;
	int r(0), g(0), b(0), alpha(0), size(0);
	int x(0), y(0);

	while (node != nullptr)
	{
		if (strcmp(node->FirstChildElement(s_FontColor)->FirstChildElement(s_FontColor_Simple)
			->FirstChildElement(s_FontColor_Simple_Condition)->GetText(), "true") == 0)
		{
			fontColor = xmlGiveColor(node->FirstChildElement(s_FontColor)->FirstChildElement(s_FontColor_Simple)
				->FirstChildElement(s_FontColor_Simple_Color)->GetText());
		}
		else
		{
			node->FirstChildElement(s_FontColor)->FirstChildElement(s_FontColor_Complexe)
				->FirstChildElement(s_FontColor_Complexe_R)->QueryIntText((int*)&r);
			node->FirstChildElement(s_FontColor)->FirstChildElement(s_FontColor_Complexe)
				->FirstChildElement(s_FontColor_Complexe_G)->QueryIntText((int*)&g);
			node->FirstChildElement(s_FontColor)->FirstChildElement(s_FontColor_Complexe)
				->FirstChildElement(s_FontColor_Complexe_B)->QueryIntText((int*)&b);
			node->FirstChildElement(s_FontColor)->FirstChildElement(s_FontColor_Complexe)
				->FirstChildElement(s_FontColor_Complexe_Alpha)->QueryIntText((int*)&alpha);
			fontColor.r = (Uint8)r;
			fontColor.g = (Uint8)g;
			fontColor.b = (Uint8)b;
			fontColor.a = (Uint8)alpha;
		}

		if (strcmp(node->FirstChildElement(s_BackColor)->FirstChildElement(s_BackColor_Simple)
			->FirstChildElement(s_BackColor_Simple_Condition)->GetText(), "true") == 0)
		{
			backColor = xmlGiveColor(node->FirstChildElement(s_BackColor)->FirstChildElement(s_BackColor_Simple)
				->FirstChildElement(s_BackColor_Simple_Color)->GetText());
		}
		else
		{
			node->FirstChildElement(s_BackColor)->FirstChildElement(s_BackColor_Complexe)
				->FirstChildElement(s_BackColor_Complexe_R)->QueryIntText((int*)&r);
			node->FirstChildElement(s_BackColor)->FirstChildElement(s_BackColor_Complexe)
				->FirstChildElement(s_BackColor_Complexe_G)->QueryIntText((int*)&g);
			node->FirstChildElement(s_BackColor)->FirstChildElement(s_BackColor_Complexe)
				->FirstChildElement(s_BackColor_Complexe_B)->QueryIntText((int*)&b);
			node->FirstChildElement(s_BackColor)->FirstChildElement(s_BackColor_Complexe)
				->FirstChildElement(s_BackColor_Complexe_Alpha)->QueryIntText((int*)&alpha);
			backColor.r = (Uint8)r;
			backColor.g = (Uint8)g;
			backColor.b = (Uint8)b;
			backColor.a = (Uint8)alpha;
		}

		node->FirstChildElement(s_Size)->QueryIntText((int*)&size);
		node->FirstChildElement(s_X)->QueryIntText(&x);
		node->FirstChildElement(s_Y)->QueryIntText(&y);


		try
		{
			Texte::loadTexte(renderer, font,
				xmlGiveStateType(node->FirstChildElement(s_Statescreen)->GetText()),
				xmlGiveSelectType(node->FirstChildElement(s_Select)->GetText()),
				xmlGiveTexteConteneur(allTextes, node->FirstChildElement(s_TexteName)->GetText()),
				xmlGiveTexteType(node->FirstChildElement(s_Type)->GetText()),
				node->FirstChildElement(s_Texte)->GetText(),
				fontColor,
				backColor,
				(Uint8)size,
				determineCoor(node->FirstChildElement(s_X)->GetText(), screenWidth, screenHeight),
				determineCoor(node->FirstChildElement(s_Y)->GetText(), screenWidth, screenHeight),
				xmlGiveAlpha(node->FirstChildElement(s_Alpha)->GetText()),
				xmlGiveAngle(node->FirstChildElement(s_Angle)->GetText()),
				xmlGiveCenter(node->FirstChildElement(s_Center)->GetText()));
		}
		catch (const std::string& msg)
		{
			exitError("[ERROR]___: IHM::determineCoor : " + msg);
		}

		/* Recherche du noeud Model suivant */
		node = node->NextSibling();
	}
}

int IHM::determineCoor(std::string line, Uint16 screenWidth, Uint16 screenHeight)
{
	std::string num(""), den(""), buffer("");
	unsigned int somme(0), numI(0), denI(0);
	unsigned int i(1);

	if (line[0] == '(')
	{
		while (line[i] != ')')
		{
			num += line[i];
			i++;
		}
		i +=3 ;
		while (line[i] != ')')
		{
			den += line[i];
			i++;
		}

		std::string::size_type n(0);
		n = num.find("SCREEN_WIDTH");
		while (n != std::string::npos)
		{
			num.replace(n, 12, std::to_string(screenWidth));
			n = num.find("SCREEN_WIDTH");
		}
		
		n = num.find("SCREEN_HEIGHT");
		while (n != std::string::npos)
		{
			num.replace(n, 13, std::to_string(screenHeight));
			n = num.find("SCREEN_HEIGHT");
		}

		numI = std::stoi(num);
		denI = std::stoi(den);

		if (denI == 0)
		{
			throw(" div/0 -> den == 0");
		}

		return somme = (unsigned int)(numI / denI);
	}
	else
	{
		return std::stoi(line);
	}
}


/* *********************************************************
 *					END INITIALISATION					   *
 ********************************************************* */







/* *********************************************************
 *					START IN-GAME						   *
 ********************************************************* */


/*
* NAME : eventSDL
* ROLE : Recherche infini des évenements d'entré de type SDL_event : souris, clavier
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : évenements d'entré utilisateur
* RETURNED VALUE    : void
*/
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
				deletePlayer(sysinfo.tabplayer, "player");
				for (unsigned int i(0); i < 4; i++)
				{
					sysinfo.tabplayer.push_back(new Player("NoName" + std::to_string(i)));
				}
				GamePlay::newGameSettlerSpawn(sysinfo);
				break;
			case SDLK_ESCAPE:
				sysinfo.var.continuer = 0;
				break;
			case SDLK_UP:
				if (sysinfo.map.screenOffsetYIndexMin > 0)
				{
					sysinfo.map.screenOffsetYIndexMin--;
					sysinfo.map.screenOffsetYIndexMax--;
				}
				break;
			case SDLK_LEFT:
				if (sysinfo.map.screenOffsetXIndexMin > 0)
				{
					sysinfo.map.screenOffsetXIndexMin--;
					sysinfo.map.screenOffsetXIndexMax--;
				}
				break;
			case SDLK_DOWN:
				if (sysinfo.map.screenOffsetYIndexMax < sysinfo.map.maps[0].size())
				{
					sysinfo.map.screenOffsetYIndexMin++;
					sysinfo.map.screenOffsetYIndexMax++;
				}
				break;
			case SDLK_RIGHT:
				if (sysinfo.map.screenOffsetXIndexMax < sysinfo.map.maps.size())
				{
					sysinfo.map.screenOffsetXIndexMin++;
					sysinfo.map.screenOffsetXIndexMax++;
				}
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


/*
* NAME : titleScreen
* ROLE : Desciption de la fenetre "titleScreen"
* ROLE : fonctionnement selon l'état : enum State_Type = STATEtitleScreen
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Ouverture de la fenetre "titleScreen"
* RETURNED VALUE    : void
*/
void IHM::titleScreen(Sysinfo& sysinfo)
{
	logfileconsole("[INFO]___: [START] : titleScreen");

	/* title screen init */
	sysinfo.var.statescreen = STATEtitleScreen;
	sysinfo.var.select = selectnothing;

	// applique une surface de la taille de l'écran de couleur noir
	SDL_RenderClear(sysinfo.screen.renderer);


	for (const auto& n : sysinfo.allTextures.titleScreen)
	{
		n.second->renderTextureTestStates(sysinfo.var.statescreen, sysinfo.var.select);
	}

	for (const auto& n : sysinfo.allTextes.titleScreen)
	{
		n.second->renderTextureTestStates(sysinfo.var.statescreen, sysinfo.var.select);
	}

	for (const auto& n : sysinfo.allButton.titleScreen)
	{
		n.second->renderButtonTexte(sysinfo.var.statescreen);
	}

	/* ### Don't put code below here ### */

	SDL_RenderPresent(sysinfo.screen.renderer);
	logfileconsole("[INFO]___: [END] : titleScreen");
}


/*
 * NAME : reloadScreen
 * ROLE : Desciption de la fenetre "reloadScreen"
 * ROLE : fonctionnement selon l'état : enum State_Type = STATEreload
 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
 * OUTPUT PARAMETERS : Ouverture de la fenetre "reloadScreen"
 * RETURNED VALUE    : void
 */
void IHM::reloadScreen(Sysinfo& sysinfo)
{
	logfileconsole("[INFO]___: [START] : reloadScreen");
	sysinfo.var.statescreen = STATEreload;
	SDL_RenderClear(sysinfo.screen.renderer);

	for (const auto& n : sysinfo.allButton.reload)
	{
		n.second->renderButtonTexte(sysinfo.var.statescreen);
	}
		

	/* ### Don't put code below here ### */

	SDL_RenderPresent(sysinfo.screen.renderer);
	logfileconsole("[INFO]___: [END] : reloadScreen");
}


/*
 * NAME : alwaysrender
 * ROLE : Tous les 1/SCREEN_REFRESH_RATE cette fonction permet ...
 * ROLE : ... la désciption de la fenetre "STATEmainmap" ou "STATEcitiemap"
 * ROLE : fonctionnement selon l'état : enum State_Type = STATEmainmap ou STATEcitiemap
 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
 * OUTPUT PARAMETERS : Ouverture de la fenetre "STATEmainmap" ou "STATEcitiemap"
 * RETURNED VALUE    : void
 */
void IHM::alwaysrender(Sysinfo& sysinfo)
{
	/*
	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	*/

	switch (sysinfo.var.statescreen)
	{
	case STATEmainmap:
		SDL_RenderClear(sysinfo.screen.renderer);

		/* *********************************************************
		 *					START background					   *
		 ********************************************************* */

		afficherSupertiles(sysinfo);

		// affiche la texture grise de la toolbar
		for (unsigned int i(0); i < sysinfo.map.toolBarSize; i++)
		{
			for (unsigned int j(0); j < sysinfo.screen.screenHeight / sysinfo.map.tileSize; j++)
			{
				sysinfo.allTextures.ground["toolbar.bmp"]->render(i * sysinfo.map.tileSize, j * sysinfo.map.tileSize);
			}
				
		}

		/* *********************************************************
		 *					END background						   *
		 ********************************************************* */


		/* *********************************************************
		 *					START Texte							   *
		 ********************************************************* */

		for (const auto& n : sysinfo.allTextes.mainMap)
		{
			n.second->renderTextureTestStates(sysinfo.var.statescreen, sysinfo.var.select);
		}

		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, std::to_string(sysinfo.var.nbturn), { 0, 64, 255, 255 }, NoColor, 24, 80, 850, no_angle);

		/* *********************************************************
		 *					END Texte							   *		
		 ********************************************************* */


		/* *********************************************************
		 *					START Button						   *
		 ********************************************************* */

		for (const auto& n : sysinfo.allButton.mainMap)
		{
			n.second->renderButtonTexte(sysinfo.var.statescreen);
		}

		for (const auto& n : sysinfo.allButton.player)
		{
			n.second->renderButtonTexte(sysinfo.var.statescreen);
		}

		/* *********************************************************
		 *					END Button							   *
		 ********************************************************* */

		
		/* *********************************************************
		 *					START UnitInfo						   *
		 ********************************************************* */

		// affiche les unités pour rendre l'unité à créer
		if (sysinfo.var.select == selectcreate)
		{
			if (sysinfo.var.s_player.unitNameToCreate.compare("") != 0)
			{
				sysinfo.allTextures.unit[sysinfo.var.s_player.unitNameToCreate]->render(100, 432);
			}
		}
		else if (sysinfo.var.select == selectmove)
		{
			if (sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
			{
				sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(sysinfo.var.s_player.selectunit)->cmpblit();
			}
		}
		else if (sysinfo.var.select == selectinspect)
		{
			// affiche les stats de l'unité inspecté
			if (sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
			{
				sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(sysinfo.var.s_player.selectunit)->afficherstat(sysinfo);
			}
		}

		/* *********************************************************
		 *					END UnitInfo						   * 
		 ********************************************************* */



		/* *********************************************************
		 *			START Affichage Unit/Citie/Player			   *
		 ********************************************************* */

		if (sysinfo.tabplayer.size() != 0)
		{
			for (unsigned int i(0); i < sysinfo.tabplayer.size(); i++) 
			{
				if (sysinfo.tabplayer[i]->GETtabUnit().size() != 0)
				{
					for (unsigned int j(0); j < sysinfo.tabplayer[i]->GETtabUnit().size(); j++)
					{
						// affiche pour chaque joueurs les unités existantes (avec les stats)
						sysinfo.tabplayer[i]->GETtheUnit(j)->afficher(sysinfo, i);
					}
				}
				if (sysinfo.tabplayer[i]->GETtabCity().size() != 0)
				{
					for (unsigned int j(0); j < sysinfo.tabplayer[i]->GETtabCity().size(); j++)
					{
						// affiche pour chaque joueurs les cités existantes
						sysinfo.tabplayer[i]->GETtheCity(j)->afficher(sysinfo);
					}
				}
			}
		}

		/* *********************************************************
		 *			END Affichage Unit/Citie/Player				   *
		 ********************************************************* */


		break;
	case STATEcitiemap:

		/* *********************************************************
		 *				START Affichage citieMap				   *
		 ********************************************************* */

		if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabCity().size() > 0)
		{
			if (sysinfo.var.s_player.selectCitie != -1)
			{
				if (sysinfo.var.s_player.selectCitie < (int)sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabCity().size())
					citiemap(sysinfo);
			}
		}

		/* *********************************************************
		 *				END Affichage citieMap					   *
		 ********************************************************* */


		break;
	}
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		blended, std::to_string(sysinfo.screen.avgFPS), { 0, 64, 255, 255 }, NoColor, 24, sysinfo.screen.screenWidth / 2, 50, no_angle, center_x);

	/* ### Don't put code below here ### */

	SDL_RenderPresent(sysinfo.screen.renderer);
	/*
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	std::cout << std::endl << "temps d'execution de alwaysrender : " << std::setprecision(10) << elapsed_seconds.count();
	*/
}


/*
 * NAME : afficherSupertiles
 * ROLE : Affichage de la map (tiles, spec, appartenance) aux dimensions map.screen
 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
 * OUTPUT PARAMETERS : Affichage de la map sur la fenetre "mainMap"
 * RETURNED VALUE    : void
 */
void IHM::afficherSupertiles(Sysinfo& sysinfo)
{
	//clock_t t1, t2;
	//t1 = clock();
	
	unsigned int x(0), y(0);

	for (unsigned int m(sysinfo.map.screenOffsetXIndexMin); m < sysinfo.map.screenOffsetXIndexMax; m++)
	{
		for (unsigned int n(sysinfo.map.screenOffsetYIndexMin); n < sysinfo.map.screenOffsetYIndexMax; n++)
		{
			x = sysinfo.map.maps[m][n].tile_x - sysinfo.map.screenOffsetXIndexMin * sysinfo.map.tileSize;
			y = sysinfo.map.maps[m][n].tile_y - sysinfo.map.screenOffsetYIndexMin * sysinfo.map.tileSize;

			switch (sysinfo.map.maps[m][n].tile_ground)
			{
			case grass:
				sysinfo.allTextures.ground["grass.bmp"]->render(x, y);
				break;
			case water:
				sysinfo.allTextures.ground["water.bmp"]->render(x, y);
				break;
			case deepwater:
				sysinfo.allTextures.ground["deepwater.bmp"]->render(x, y);
				break;
			}

			if (sysinfo.map.maps[m][n].tile_spec > 0)
			{
				sysinfo.allTextures.groundSpec[sysinfo.map.maps[m][n].tile_stringspec]->render(x, y);
			}
			if (sysinfo.map.maps[m][n].appartenance != -1)
			{
				sysinfo.allTextures.colorapptile["ColorPlayertile" + std::to_string(sysinfo.map.maps[m][n].appartenance) + ".bmp"]->render(x, y);
			}
		}
	}
	//t2 = clock();
	//std::cout << std::endl << "temps d'execution de alwaysrender : " + std::to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
	
}


/*
 * NAME : citiemap
 * ROLE : Affichage de la fenetre citiemap
 * ROLE : fonctionnement selon l'état : enum State_Type = STATEcitiemap
 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
 * OUTPUT PARAMETERS :  Affichage de la map sur la fenetre "citieMap"
 * RETURNED VALUE    : void
 */
void IHM::citiemap(Sysinfo& sysinfo)
{
	SDL_RenderClear(sysinfo.screen.renderer);
	
	/* *********************************************************
	 *					START Button						   *				
	 ********************************************************* */
	
	sysinfo.allButton.citieMap["Map"]->renderButtonTexte(sysinfo.var.statescreen);
	sysinfo.allButton.citieMap["Build"]->renderButtonTexte(sysinfo.var.statescreen);
	sysinfo.allButton.citieMap["Food"]->renderButtonTexte(sysinfo.var.statescreen);
	sysinfo.allButton.citieMap["Place Citizen"]->renderButtonTexte(sysinfo.var.statescreen);


	/* *********************************************************
	 *					END Button							   *
	 ********************************************************* */

	/* *********************************************************
	 *			 START select = selectcreate				   *
	 ********************************************************* */

	std::string buildName("");
	unsigned int initspace(96), space(32);
	if (sysinfo.var.select == selectcreate)
	{
		initspace = 96;
		for (unsigned int j(0); j < 10; j++)
		{
			if (sysinfo.var.s_player.unitToCreate + j < sysinfo.var.s_player.tabUnit_Struct.size())
				buildName = sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].name;
			else
				break;

			sysinfo.allButton.citieMap[buildName]
				->renderButtonTexte(sysinfo.var.statescreen, sysinfo.screen.screenWidth / 2, initspace += space);
			sysinfo.allTextures.unit[buildName]
				->render((sysinfo.screen.screenWidth / 2) - 50, initspace);
			sysinfo.allTextes.citieMap[
				"life:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].life) +
				"/atq:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].atq) +
				"/def:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].def) +
				"/move:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].movement)]
				->render((sysinfo.screen.screenWidth / 2) + 200, initspace);
		}

		sysinfo.allTextes.citieMap["Scroll up or down"]->render();
		sysinfo.allTextes.citieMap["Left click to Select"]->render();
		sysinfo.allTextes.citieMap["create : "]->render();
		sysinfo.allTextes.citieMap["selectcreate"]->render();
	}

	/* *********************************************************
	 *			 END select = selectcreate					   *
	 ********************************************************* */

	sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheCity(sysinfo.var.s_player.selectCitie)->affichercitiemap(sysinfo);

}


/*
 * NAME : countFrame
 * ROLE : Compteur de frames durant le programme
 * ROLE : Début : à la fin de la fonction newGame(...)
 * INPUT  PARAMETERS : Screen& screen : données concernant la fenetre SDL
 * OUTPUT PARAMETERS : Incrémentation du nombre de frames comptées
 * RETURNED VALUE    : void
 */
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


/* *********************************************************
 *						END IN-GAME						   *
 ********************************************************* */




/* *********************************************************
 *					START END-GAME						   *
 ********************************************************* */


void IHM::exitError(const std::string msg)
{
	logfileconsole("[ERROR]___: " + msg);
	deleteAll(*ptrSysinfo);
	logfileconsole("[ERROR]___: Last msg before exitError : " + msg);
	exit(1);
}


/*
 * NAME : deleteAll
 * ROLE : Destruction des allocations dynamique du programme
 * ROLE : Destruction de la fenetre et du Renderer de la SDL
 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
 * OUTPUT PARAMETERS : Destruction des allocations dynamique du programme
 * RETURNED VALUE    : void
 */
void IHM::deleteAll(Sysinfo& sysinfo)
{
	logfileconsole("[INFO]___: [START] *********_________ DeleteAll _________*********");

	/* *********************************************************
	 *					START delete font*					   *
	 ********************************************************* */

	for (unsigned int i(1); i < MAX_FONT; i++)
	{
		TTF_CloseFont(sysinfo.allTextures.font[i]);
	}
		
	/* *********************************************************
	 *					END delete font*					   *
	 ********************************************************* */


	/* *********************************************************
	 *				 START delete Texture*					   *
	 ********************************************************* */

	deleteTexture(sysinfo.allTextures.ground, "Texture");
	deleteTexture(sysinfo.allTextures.groundSpec, "Texture");
	deleteTexture(sysinfo.allTextures.barLife, "Texture");
	deleteTexture(sysinfo.allTextures.colorapp, "Texture");
	deleteTexture(sysinfo.allTextures.colorapptile, "Texture");

	deleteTexture(sysinfo.allTextures.titleScreen, "Texture");
	deleteTexture(sysinfo.allTextures.unit, "Texture");
	deleteTexture(sysinfo.allTextures.citieMap, "Texture");

	/* *********************************************************
	 *				 END delete Texture*					   *
	 ********************************************************* */


	/* *********************************************************
	 *				 START delete Texte*					   *
	 ********************************************************* */

	deleteTexte(sysinfo.allTextes.number, "Texte");
	deleteTexte(sysinfo.allTextes.titleScreen, "Texte");
	deleteTexte(sysinfo.allTextes.newGame, "Texte");
	deleteTexte(sysinfo.allTextes.mainMap, "Texte");
	deleteTexte(sysinfo.allTextes.citieMap, "Texte");

	/* *********************************************************
	 *					END delete Texte*					   *
	 ********************************************************* */


	/* *********************************************************
	 *				 START delete Button*					   *
	 ********************************************************* */

	deleteButtonTexte(sysinfo.allButton.titleScreen, "Button");
	deleteButtonTexte(sysinfo.allButton.player, "Button");
	deleteButtonTexte(sysinfo.allButton.reload, "Button");
	deleteButtonTexte(sysinfo.allButton.mainMap, "Button");
	deleteButtonTexte(sysinfo.allButton.citieMap, "Button");

	/* *********************************************************
	 *				 END delete Button*						   *
	 ********************************************************* */

	deletePlayer(sysinfo.tabplayer, "player");

	/* *********************************************************
	 *				 START delete SDL						   *
	 ********************************************************* */

	SDL_DestroyRenderer(sysinfo.screen.renderer);
	SDL_DestroyWindow(sysinfo.screen.window);
	sysinfo.screen.renderer = nullptr;
	sysinfo.screen.window = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	/* *********************************************************
	 *				 END delete SDL							   *
	 ********************************************************* */

	/* ### Don't put code below here ### */

	logfileconsole("[INFO]___: [END] : *********_________ DeleteAll _________*********");

	IHM::logfileconsole("[INFO]___: SDL_Quit Success");
	IHM::logfileconsole("[INFO]___:________PROGRAMME FINISH________");

	logger.close();
}



void IHM::deleteTexture(std::unordered_map<std::string, Texture*>& unmap, const std::string& name)
{
	for (const auto& n : unmap)
	{
		if (n.second != nullptr)
		{
			IHM::logfileconsole("[INFO]___: Delete " + name + " name = " + n.second->GETname() + " Success");
			delete n.second;
		}
	}
}

void IHM::deleteTexte(std::unordered_map<std::string, Texte*>& unmap, const std::string& name)
{
	for (const auto& n : unmap)
	{
		if (n.second != nullptr)
		{
			IHM::logfileconsole("[INFO]___: Delete " + name + " name = " + n.second->GETname() + " Success");
			delete n.second;
		}
	}
}

void IHM::deleteButtonTexte(std::unordered_map<std::string, ButtonTexte*>& unmap, const std::string& name)
{
	for (const auto& n : unmap)
	{
		if (n.second != nullptr)
		{
			IHM::logfileconsole("[INFO]___: Delete " + name + " name = " + n.second->GETname() + " Success");
			delete n.second;
		}
	}
}

void IHM::deletePlayer(std::vector<Player*>& vect, const std::string& name)
{
	for (unsigned int i(0); i < vect.size(); i++)
	{
		if (vect[i] != nullptr)
		{
			IHM::logfileconsole("[INFO]___: Delete " + name + " name = " + vect[i]->GETname() + " Success");
			delete vect[i];
		}
	}
}

/* *********************************************************
 *						END END-GAME					   *
 ********************************************************* */

/*
*	End Of File : IHM.cpp
*/