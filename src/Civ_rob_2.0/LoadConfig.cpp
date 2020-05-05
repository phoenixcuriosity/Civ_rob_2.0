/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.20.2.1
	file version : 1.15

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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LoadConfig.h"
#include "civ_lib.h"
#include "IHM.h"
#include "End.h"
#include "Player.h"
#include "Utility.h"

/* *********************************************************
 *					Variable Globale					   *
 ********************************************************* */

static std::ofstream logger;
static Sysinfo* ptrSysinfo;

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initPtrSysinfo															   */
/* ROLE : Initialisation des ptr sur sysinfo et logger								   */
/* INPUT : struct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void LoadConfig::initPtrSysinfo(Sysinfo& sysinfo)
{
	ptrSysinfo = &sysinfo;
	End::initPtrSysinfoLogger(sysinfo, logger);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initStructs																   */
/* ROLE : Initialisation des données par défaut des structures						   */
/* INPUT : struct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void LoadConfig::initStructs
(
	Sysinfo& sysinfo
)
{
	/* ### Mettre ici les cas d'inialisation des structures ### */

	/* *********************************************************
	 *					   sysinfo.screen					   *
	 ********************************************************* */

	sysinfo.screen.window = nullptr;
	sysinfo.screen.renderer = nullptr;
	sysinfo.screen.screenWidth = 0;
	sysinfo.screen.screenHeight = 0;
	sysinfo.screen.enableFPS = false;
	// sysinfo.screen.fpsTimer // N/A
	sysinfo.screen.avgFPS = 0;
	sysinfo.screen.countedFrames = 0;
	
	/* *********************************************************
	 *					   sysinfo.file						   *
	 ********************************************************* */

	// sysinfo.file.log = "bin/log/log.txt"; // N/A : const
	sysinfo.file.BUILDING = EMPTY_STRING;
	sysinfo.file.CITIENAME = EMPTY_STRING;
	sysinfo.file.readme = EMPTY_STRING;
	sysinfo.file.SaveInfo = EMPTY_STRING;
	sysinfo.file.SaveMaps = EMPTY_STRING;
	sysinfo.file.SPECNAME = EMPTY_STRING;
	sysinfo.file.UNIT = EMPTY_STRING;
	sysinfo.file.Texte = EMPTY_STRING;

	/* *********************************************************
	 *					   sysinfo.var						   *
	 ********************************************************* */

	//sysinfo.var.argc = argc; /* Already setup in main */
	//sysinfo.var.argv = argv; /* Already setup in main */
	sysinfo.var.continuer = true;
	sysinfo.var.waitEvent = true;
	sysinfo.var.nbturn = 0;
	sysinfo.var.nbPlayer = 0;
	sysinfo.var.tempPlayerName = EMPTY_STRING;
	sysinfo.var.tempX = 0;
	sysinfo.var.tempY = 0;
	sysinfo.var.select = Select_Type::selectnothing;
	sysinfo.var.statescreen = State_Type::error;
	sysinfo.var.cinState = CinState_Type::cinNothing;

	/* sysinfo.var.s_player */

	sysinfo.var.s_player.selectCitie = NO_CITIE_SELECTED;
	sysinfo.var.s_player.selectplayer = NO_PLAYER_SELECTED;
	sysinfo.var.s_player.selectPlayerToAttack = NO_PLAYER_SELECTED;
	sysinfo.var.s_player.selectunit = NO_UNIT_SELECTED;
	sysinfo.var.s_player.selectUnitToAttack = NO_UNIT_SELECTED;
	sysinfo.var.s_player.unitToCreate = 0;
	sysinfo.var.s_player.toBuild = EMPTY_STRING;
	sysinfo.var.s_player.unitNameToCreate = EMPTY_STRING;
	sysinfo.var.s_player.unitNameToMove = EMPTY_STRING;

	sysinfo.var.s_player.tabCitieName.clear();
	sysinfo.var.s_player.tabPlayerName.clear();
	sysinfo.var.s_player.tabUnit_Template.clear();

	sysinfo.var.s_player.nbNoNamePlayer = 0;
	sysinfo.var.s_player.citieNameMaxToCreate = 0;

	/* sysinfo.var.mouse */

	KeyboardMouse mouse;
	sysinfo.var.mouse = mouse;

	/* sysinfo.var.save */

	SaveReload save;
	sysinfo.var.save = save;

	/* *********************************************************
	 *					 sysinfo.allTextures				   *
	 ********************************************************* */

	for (unsigned int i(0); i < MAX_FONT; i++)
	{
		sysinfo.allTextures.font[i] = nullptr;
	}

	sysinfo.allTextures.ground.clear();
	sysinfo.allTextures.groundSpec.clear();
	sysinfo.allTextures.colorapp.clear();
	sysinfo.allTextures.colorapptile.clear();
	sysinfo.allTextures.barLife.clear();


	sysinfo.allTextures.titleScreen.clear();
	sysinfo.allTextures.unit.clear();
	sysinfo.allTextures.citieMap.clear();

	/* *********************************************************
	 *					  sysinfo.allTextes					   *
	 ********************************************************* */

	sysinfo.allTextes.number.clear();
	sysinfo.allTextes.titleScreen.clear();
	sysinfo.allTextes.newGame.clear();
	sysinfo.allTextes.mainMap.clear();
	sysinfo.allTextes.citieMap.clear();

	/* *********************************************************
	 *					  sysinfo.allButton					   *
	 ********************************************************* */

	sysinfo.allButton.titleScreen.clear();
	sysinfo.allButton.reload.clear();
	sysinfo.allButton.mainMap.clear();
	sysinfo.allButton.citieMap.clear();

	sysinfo.allButton.player.clear();

	/* *********************************************************
	 *					    sysinfo.map						   *
	 ********************************************************* */

	sysinfo.map.mapSize = 0;
	sysinfo.map.tileSize = 0;
	sysinfo.map.toolBarSize = 0;
	sysinfo.map.screenOffsetXIndexMin = 0;
	sysinfo.map.screenOffsetYIndexMin = 0;
	sysinfo.map.screenOffsetXIndexMax = 0;
	sysinfo.map.screenOffsetYIndexMax = 0;
	sysinfo.map.maps.clear();

	/* *********************************************************
	 *					    sysinfo							   *
	 ********************************************************* */

	sysinfo.tabplayer.clear();
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initFile																	   */
/* ROLE : Initialisation des fichiers : log											   */
/* INPUT : struct File& : nom des fichiers											   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void LoadConfig::initFile
(
	File& file
)
{
	logger.open(file.log, std::ofstream::out | std::ofstream::trunc);
	if (!logger.is_open())
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		/* N/A */
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initMain																	   */
/* ROLE : Chargement des informations de la configuration du jeu					   */
/* INPUT : struct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void LoadConfig::initMain
(
	Sysinfo& sysinfo
)
{
	logfileconsole("[INFO]___: [START] : initMain");

	tinyxml2::XMLDocument config;
	config.LoadFile(configFilePath.c_str());

	if (config.ErrorID() == 0)
	{
		const char* root("Config");


		const char* s_Map("Map"),
			* s_TileSize("TileSize"),
			* s_MapSize("MapSize"),

			* s_FilePaths("FilePaths"),
			* s_Readme("Readme"),
			* s_Texte("Texte"),
			* s_Building("Building"),
			* s_CitieName("CitieName"),
			* s_Unit("Unit"),
			* s_SpecName("SpecName"),
			* s_SaveInfo("SaveInfo"),
			* s_SaveMaps("SaveMaps"),
			* s_SavePlayer("SavePlayer");

		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_TileSize)->QueryUnsignedText(&sysinfo.map.tileSize);
		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_MapSize)->QueryUnsignedText(&sysinfo.map.mapSize);

		sysinfo.file.readme = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Readme)->GetText();
		sysinfo.file.Texte = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Texte)->GetText();
		sysinfo.file.BUILDING = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Building)->GetText();
		sysinfo.file.CITIENAME = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_CitieName)->GetText();
		sysinfo.file.UNIT = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Unit)->GetText();
		sysinfo.file.SPECNAME = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SpecName)->GetText();
		sysinfo.file.SaveInfo = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SaveInfo)->GetText();
		sysinfo.file.SaveMaps = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SaveMaps)->GetText();
		sysinfo.file.SavePlayer = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SavePlayer)->GetText();
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + (std::string)configFilePath);
	}

	logfileconsole("[INFO]___: [END] : initMain");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : computeSize																   */
/* ROLE : Calcul des différentes tailles de fenetre en fonction de tileSize			   */
/* INPUT/OUTPUT : Screen& screen : longueur et hauteur écran						   */
/* INPUT/OUTPUT : struct Sysinfo& : différentes tailles de fenetre					   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void LoadConfig::computeSize
(
	Screen& screen,
	Map& map
)
{
	/* ---------------------------------------------------------------------- */
	/* 1° : Screen														 	  */
	/* ---------------------------------------------------------------------- */
	screen.screenWidth = getHorizontal(map.tileSize);
	screen.screenHeight = getVertical(map.tileSize);

	/* ---------------------------------------------------------------------- */
	/* 2° : Maimap														 	  */
	/* ---------------------------------------------------------------------- */
	map.toolBarSize = (unsigned int)Utility::protectedDiv((screen.screenWidth / 10), map.tileSize);
	map.screenOffsetXIndexMax = (unsigned int)Utility::protectedDiv(((screen.screenWidth * 9) / 10), map.tileSize);
	map.screenOffsetYIndexMax = (unsigned int)Utility::protectedDiv(screen.screenHeight, map.tileSize);

	/* ---------------------------------------------------------------------- */
	/* 3° : CitieMap													 	  */
	/* ---------------------------------------------------------------------- */
	map.citieMap.ToolbarButtonsH = (screen.screenWidth / 3);
	map.citieMap.ToolbarButtonsW = (screen.screenHeight / 3);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : getHorizontal																   */
/* ROLE : Calcul de la longueur en pixels de la fenetre								   */
/* INPUT : unsigned int tileSize : taille en pixel d'une tile 						   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Uint16 LoadConfig::getHorizontal
(
	unsigned int tileSize
)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	Uint16 complete = 0;
	if ((complete = ((Uint16)desktop.right % (Uint16)tileSize)) == 0)
		return (Uint16)desktop.right;
	return (Uint16)desktop.right + ((Uint16)tileSize - complete);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : getVertical																   */
/* ROLE : Calcul de la hauteur en pixels de la fenetre								   */
/* INPUT : unsigned int tileSize : taille en pixel d'une tile 						   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Uint16 LoadConfig::getVertical
(
	unsigned int tileSize
)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	Uint16 complete = 0;
	if ((complete = ((Uint16)desktop.bottom % (Uint16)tileSize)) == 0)
		return (Uint16)desktop.bottom;
	return (Uint16)desktop.bottom + ((Uint16)tileSize - complete);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initTile																	   */
/* ROLE : Initialisation des cases de la map en fonction de sa taille				   */
/* INPUT : struct Map& : données générale de la map : taille						   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void LoadConfig::initTile
(
	Map& map
)
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


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : loadUnitAndSpec															   */
/* ROLE : Chargement des informations concernant les unités à partir d'un fichier	   */
/* INPUT : const std::string& : nom du fichier à ouvrir								   */
/* OUTPUT : std::vector<Unit_Template>& : Vecteur des Unit							   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void LoadConfig::loadUnitAndSpec
(
	const std::string& UNIT,
	std::vector<Unit_Template>& tabUnit_Template
)
{
	tinyxml2::XMLDocument texteFile;
	texteFile.LoadFile(UNIT.c_str());

	const char* root("Root");

	const char		* s_Unit("Unit"),
						* s_Name("Name"),
						* s_MovementType("MovementType"),
						* s_Life("Life"),
						* s_Atq("Atq"),
						* s_Def("Def"),
						* s_Mouvement("Mouvement"),
						* s_Level("Level"),
						* s_WorkToBuild("WorkToBuild");

	tinyxml2::XMLNode* node(texteFile.FirstChildElement(root)->FirstChildElement(s_Unit));
	Unit_Template currentUnit;

	while (nullptr != node)
	{
		currentUnit.name = node->FirstChildElement(s_Name)->GetText();
		currentUnit.type = xmlGiveMovementType(node->FirstChildElement(s_MovementType)->GetText());
		node->FirstChildElement(s_Life)->QueryIntText((int*)&currentUnit.life);
		node->FirstChildElement(s_Atq)->QueryIntText((int*)&currentUnit.atq);
		node->FirstChildElement(s_Def)->QueryIntText((int*)&currentUnit.def);
		node->FirstChildElement(s_Mouvement)->QueryIntText((int*)&currentUnit.movement);
		node->FirstChildElement(s_Level)->QueryIntText((int*)&currentUnit.level);
		node->FirstChildElement(s_Level)->QueryIntText((int*)&currentUnit.level);
		node->FirstChildElement(s_WorkToBuild)->QueryDoubleText((double*)&currentUnit.workToBuild);

		tabUnit_Template.push_back(currentUnit);

		/* Recherche du noeud Model suivant */
		node = node->NextSibling();
	}
}

Unit_Movement_Type LoadConfig::xmlGiveMovementType
(
	std::string type
)
{
	if (type.compare("ground") == IDENTICAL_STRINGS)
	{
		return Unit_Movement_Type::ground;
	}
	else if(type.compare("air") == IDENTICAL_STRINGS)
	{
		return Unit_Movement_Type::air;
	}
	else if (type.compare("water") == IDENTICAL_STRINGS)
	{
		return Unit_Movement_Type::water;
	}
	else if (type.compare("deepwater") == IDENTICAL_STRINGS)
	{
		return Unit_Movement_Type::deepwater;
	}
	else
	{
		return Unit_Movement_Type::ground;
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : logfileconsole															   */
/* ROLE : Transmission du message sur la console et dans le fichier log.txt			   */
/* INPUT : const std::string msg : message											   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void LoadConfig::logfileconsole
(
	const std::string msg
)
{
	time_t now(time(0));
	struct tm  tstruct;
	char  buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%F %X", &tstruct);

#ifdef _DEBUG_MODE
	std::cout << std::endl << buf << "      " << msg;
#endif // DEBUG_MODE
	logger << std::endl << buf << "      " << msg;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initSDL																	   */
/* ROLE : Initialisation de la SDL fenetre et renderer ...							   */
/* ROLE : ... ainsi que le tableau de police de font								   */
/* INPUT : SDL_Window*& : pointeur sur la fenetre de la SDL							   */
/* INPUT : SDL_Renderer*& : pointeur sur le Renderer de la SDL						   */
/* INPUT : TTF_Font*[] : pointeur sur le tableau de police de font					   */
/* RETURNED VALUE    : bool : true = pas d'erreur lors de l'initialisation de la SDL   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool LoadConfig::initSDL
(
	Screen& screen,
	TTF_Font* font[]
)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		/* ---------------------------------------------------------------------- */
		/* 1° : Si l'initialisation de tous les services de la SDL est failed	  */
		/* ---------------------------------------------------------------------- */

		logfileconsole("[ERROR]___: SDL could not initialize! SDL_Error: " + (std::string)SDL_GetError());
		return false;
	}
	else
	{
		/* ---------------------------------------------------------------------- */
		/* 2° : Si l'initialisation de tous les services de la SDL est success	  */
		/* ---------------------------------------------------------------------- */

		/* ---------------------------------------------------------------------- */
		/* 2.1° : Création du context de la fenetre de jeu						  */
		/*      : Titre, position pa défaut et taille   						  */
		/*      : Test validité du context				   						  */
		/* ---------------------------------------------------------------------- */

		screen.window = SDL_CreateWindow("Civ_Rob_2.0",
			0, 0,
			screen.screenWidth, screen.screenHeight,
			SDL_WINDOW_OPENGL);

		if (nullptr == screen.window)
		{
			SDL_Quit();
			return false;
		}
		else
		{
			logfileconsole("[INFO]___: CreateWindow Success");
		}

		/* ---------------------------------------------------------------------- */
		/* 2.2° : Création du context du SDL_Renderer							  */
		/*      : Option non utilisée en debug :  SDL_RENDERER_PRESENTVSYNC       */
		/*      : permettant la	synchronisation avec la fréquence de l'écran	  */
		/*      : Test validité du context				   						  */
		/* ---------------------------------------------------------------------- */

#ifdef _DEBUG_MODE
		screen.renderer = SDL_CreateRenderer(screen.window, -1, SDL_RENDERER_ACCELERATED);
#else
		screen.renderer = SDL_CreateRenderer(screen.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#endif // DEBUG_MODE

		if (nullptr == screen.renderer)
		{
			SDL_DestroyWindow(screen.window);
			SDL_Quit();
			return false;
		}
		else
		{
			logfileconsole("[INFO]___: CreateRenderer Success");
		}

		/* ---------------------------------------------------------------------- */
		/* 2.3° : Initialisation de la SDL pour les textes						  */
		/*      : Test validité du context				   						  */
		/* ---------------------------------------------------------------------- */

		if (TTF_Init() != 0)
		{
			SDL_DestroyRenderer(screen.renderer);
			SDL_DestroyWindow(screen.window);
			SDL_Quit();
			return false;
		}
		else
		{
			logfileconsole("[INFO]___: TTF_Init Success");
		}

		/* ---------------------------------------------------------------------- */
		/* 2.4° : Création d'un tableau de ptr vers les différentes tailles de 	  */
		/*      : de la font utilisée				   						      */
		/* ---------------------------------------------------------------------- */

		for (Uint8 i(1); i < MAX_FONT; i++)
		{
			font[i] = TTF_OpenFont(fontFile.c_str(), i);
		}

		logfileconsole("[INFO]___: SDL_Init Success");
		return true;
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : calculImage																   */
/* ROLE : Initialisation des Textures, des Textes et des Buttons					   */
/* ROLE : Enregistrement des pointeurs dans des unorder_map							   */
/* INPUT : struct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void LoadConfig::calculImage
(
	Sysinfo& sysinfo
)
{
	logfileconsole("[INFO]___: [START] : calculImage");

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
		IPath + "ground/grass.bmp", "grass.bmp", nonTransparent,
		SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, Center_Type::nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ground/water.bmp", "water.bmp", nonTransparent,
		SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, Center_Type::nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ground/deepwater.bmp", "deepwater.bmp", nonTransparent,
		SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, Center_Type::nocenter);


	// chargement de l'image de la toolbar
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "toolbar.bmp", "toolbar.bmp", nonTransparent, 0, 0,
		sysinfo.map.tileSize * sysinfo.map.toolBarSize, sysinfo.map.tileSize * sysinfo.screen.screenHeight, no_angle, Center_Type::nocenter);


	// chargement des spécifications du sol de la map
	/*
		sysinfo.allTextures.groundSpec
	*/
	unsigned int nbspecname(0);
	std::string destroy(EMPTY_STRING), name(EMPTY_STRING);
	std::ifstream SPECNAME(sysinfo.file.SPECNAME);
	if (SPECNAME)
	{
		SPECNAME >> destroy;
		SPECNAME >> nbspecname;
		for (unsigned int i(0); i < nbspecname; i++)
		{
			name = EMPTY_STRING;
			SPECNAME >> name;
			Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.groundSpec, sysinfo.var.statescreen, sysinfo.var.select,
				IPath + "spec/" + name, name, nonTransparent,
				SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, Center_Type::nocenter);
		}
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + sysinfo.file.SPECNAME);
	}




	// chargement du nombre d'unités ainsi que leur nom
	/*
		sysinfo.allTextures.unit
	*/
	for (unsigned int i(0); i < sysinfo.var.s_player.tabUnit_Template.size(); i++)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.unit, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "units/" + sysinfo.var.s_player.tabUnit_Template[i].name + ".bmp",
			sysinfo.var.s_player.tabUnit_Template[i].name, nonTransparent, 100, 432, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, Center_Type::nocenter);



	/*
		sysinfo.allTextures.barLife
	*/
	sysinfo.var.statescreen = State_Type::STATEmainmap;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.barLife, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "barre de vie/maxlife.bmp", "maxlife.bmp", nonTransparent,
		SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE, sysinfo.map.tileSize, sysinfo.map.tileSize / 10, no_angle);
	for (int i(9); i >= 0; i--)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.barLife, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "barre de vie/0." + std::to_string(i) + "life.bmp", "0." + std::to_string(i) + "life.bmp", nonTransparent,
			SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE, sysinfo.map.tileSize, sysinfo.map.tileSize / 10, no_angle, Center_Type::nocenter);



	/*
		sysinfo.allTextures.colorapp
	*/
	for (unsigned int i(0); i < 9; i++)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.colorapp, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "couleur d'apartenance/ColorPlayer" + std::to_string(i) + ".bmp", "ColorPlayer" + std::to_string(i) + ".bmp", nonTransparent,
			SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE, sysinfo.map.tileSize / 4, sysinfo.map.tileSize / 4, no_angle, Center_Type::nocenter);


	/*
		sysinfo.allTextures.colorapptile
	*/
	for (unsigned int i(0); i < 9; i++)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.colorapptile, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "couleur d'apartenance/ColorPlayer" + std::to_string(i) + ".bmp", "ColorPlayertile" + std::to_string(i) + ".bmp", (Transparance_Type)96,
			SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, Center_Type::nocenter);


	/*
		sysinfo.allTextures.titleScreen
	*/
	sysinfo.var.statescreen = State_Type::STATEtitleScreen;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.titleScreen, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "earth.jpg", "earth.jpg", nonTransparent, sysinfo.screen.screenWidth / 2, sysinfo.screen.screenHeight / 2, NULL, NULL, no_angle, Center_Type::center);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.titleScreen, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "sdl_icone.bmp", "sdl_icone.bmp", nonTransparent, sysinfo.screen.screenWidth / 2, sysinfo.screen.screenHeight - 100, NULL, NULL, no_angle, Center_Type::center_x);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.titleScreen, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "signal/destroyed.bmp", "destroyed.bmp", nonTransparent, sysinfo.screen.screenWidth / 2, 0, NULL, NULL, no_angle, Center_Type::center_x);



	/*
		sysinfo.allTextures.citieMap
	*/
	sysinfo.var.statescreen = State_Type::STATEcitiemap;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citie/citie.png", "citie.png", nonTransparent, SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE,
		sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, Center_Type::nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citie/food.png", "food.png", nonTransparent, SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE,
		sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, Center_Type::nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citizen/Adore.png", "Adore.png", nonTransparent, SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE,
		sysinfo.map.tileSize / 2, sysinfo.map.tileSize / 2, no_angle, Center_Type::nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citizen/Laugh.png", "Laugh.png", nonTransparent, SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE,
		sysinfo.map.tileSize / 2, sysinfo.map.tileSize / 2, no_angle, Center_Type::nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citizen/Cool.png", "Cool.png", nonTransparent, SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE,
		sysinfo.map.tileSize / 2, sysinfo.map.tileSize / 2, no_angle, Center_Type::nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citizen/Cry.png", "Cry.png", nonTransparent, SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE,
		sysinfo.map.tileSize / 2, sysinfo.map.tileSize / 2, no_angle, Center_Type::nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citizen/Furious.png", "Furious.png", nonTransparent, SCREEN_MIN_X_OUT_OF_RANGE, SCREEN_MIN_Y_OUT_OF_RANGE,
		sysinfo.map.tileSize / 2, sysinfo.map.tileSize / 2, no_angle, Center_Type::nocenter);


	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "toolbar.bmp", "CitieToolbarButtons", nonTransparent, sysinfo.map.tileSize, sysinfo.map.tileSize,
		sysinfo.map.citieMap.ToolbarButtonsH, sysinfo.map.citieMap.ToolbarButtonsW, no_angle, Center_Type::nocenter);

	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "toolbar.bmp", "CitieToolbarStats", nonTransparent,
		sysinfo.map.tileSize + sysinfo.map.citieMap.ToolbarButtonsH + 2 * sysinfo.map.tileSize + INIT_SIZE_VIEW * sysinfo.map.tileSize,
		sysinfo.map.tileSize,
		sysinfo.map.citieMap.ToolbarButtonsH - sysinfo.map.tileSize,
		sysinfo.map.citieMap.ToolbarButtonsW, no_angle, Center_Type::nocenter);


	// chargement du nombre de ville ainsi que leur nom
	unsigned int nbcitie(0);
	std::string citie(EMPTY_STRING);
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
	{
		throw("Impossible d'ouvrir le fichier " + sysinfo.file.CITIENAME);
	}

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
	{
		throw("Impossible d'ouvrir le fichier " + sysinfo.file.SaveInfo);
	}

	/* *********************************************************
	 *				END sysinfo.allTextures					   *
	 ********************************************************* */


	 /* *********************************************************
	  *				START sysinfo.allButtons				    *
	  ********************************************************* */

	int spacemenu(64), initspacemenu(300);

	/*** STATEtitleScreen ***/
	sysinfo.var.statescreen = State_Type::STATEtitleScreen;


	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		Texte_Type::shaded, "New Game", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu,
		nonTransparent, no_angle, Center_Type::center);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		Texte_Type::shaded, "Reload", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu += spacemenu,
		nonTransparent, no_angle, Center_Type::center);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		Texte_Type::shaded, "Option", { 128, 128, 128, 255 }, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu += spacemenu,
		nonTransparent, no_angle, Center_Type::center);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		Texte_Type::shaded, "Quit", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu += spacemenu,
		nonTransparent, no_angle, Center_Type::center);



	/*** STATEreload ***/
	sysinfo.var.statescreen = State_Type::STATEreload;
	initspacemenu = 300;

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
		Texte_Type::shaded, "Back", WriteColorButton, BackColorButton, 24, 96, 0,
		nonTransparent, no_angle, Center_Type::center_x);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
		Texte_Type::shaded, "Remove all saves", WriteColorButton, BackColorButton, 24, 256, 0,
		nonTransparent, no_angle, Center_Type::center_x);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
		Texte_Type::shaded, "Load", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2 - 200, 256,
		nonTransparent, no_angle, Center_Type::center_x);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
		Texte_Type::shaded, "Remove", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2 + 200, 256,
		nonTransparent, no_angle, Center_Type::center_x);

	for (unsigned int i(0); i < sysinfo.var.save.GETnbSave(); i++)
	{
		ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
			Texte_Type::shaded, "Save : " + std::to_string(sysinfo.var.save.GETtabSave()[i]),
			WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu += spacemenu,
			nonTransparent, no_angle, Center_Type::center);
	}



	/*** STATEmainmap ***/
	sysinfo.var.statescreen = State_Type::STATEmainmap;

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		Texte_Type::shaded, "screen Titre", WriteColorButton, BackColorButton, 24, 0, 0,
		nonTransparent, no_angle, Center_Type::nocenter);

#ifdef _DEBUG_MODE
	sysinfo.var.select = Select_Type::selectcreate;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		Texte_Type::shaded, "Create Unit", WriteColorButton, BackColorButton, 24, 0, 50,
		nonTransparent, no_angle, Center_Type::nocenter);

	sysinfo.var.select = Select_Type::selectnothing;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		Texte_Type::shaded, "Delete Unit", WriteColorButton, BackColorButton, 24, 0, 146,
		nonTransparent, no_angle, Center_Type::nocenter);
#endif // DEBUG_MODE

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		Texte_Type::shaded, "Next Turn", WriteColorButton, BackColorButton, 24, 0, 800,
		nonTransparent, no_angle, Center_Type::nocenter);


	/*** STATEcitiemap ***/
	sysinfo.var.statescreen = State_Type::STATEcitiemap;
	sysinfo.var.select = Select_Type::selectnothing;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
		Texte_Type::shaded, "Map", WriteColorButton, BackColorButton, 24, 96, 0,
		nonTransparent, no_angle, Center_Type::center_x);

	sysinfo.var.select = Select_Type::selectcreate;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font
		, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
		Texte_Type::shaded, "Build", WriteColorButton, BackColorButton, 24, sysinfo.screen.screenWidth / 2 - 200, 100,
		nonTransparent, no_angle, Center_Type::center_x);

	sysinfo.var.select = Select_Type::selectnothing;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
		Texte_Type::shaded, "Food", WriteColorButton, BackColorButton, 24, sysinfo.screen.screenWidth / 2 - 200, 132,
		nonTransparent, no_angle, Center_Type::center_x);

	sysinfo.var.select = Select_Type::selectmoveCitizen;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
		Texte_Type::shaded, "Place Citizen", WriteColorButton, BackColorButton, 24, sysinfo.screen.screenWidth / 2 - 200, 164,
		nonTransparent, no_angle, Center_Type::center_x);

	for (unsigned int i(0); i < sysinfo.var.s_player.tabUnit_Template.size(); i++)
	{
		ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
			Texte_Type::shaded, sysinfo.var.s_player.tabUnit_Template[i].name, { 255, 64, 0, 255 }, BackColorButton, 24, 64, 400,
			nonTransparent, no_angle, Center_Type::nocenter);
	}



	sysinfo.var.select = Select_Type::selectnothing;


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
		LoadConfig::readXmlTexte
			(	texteFile,
				sysinfo.screen.renderer,
				sysinfo.allTextures.font,
				sysinfo.allTextes,
				sysinfo.screen.screenWidth,
				sysinfo.screen.screenHeight
			);
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + sysinfo.file.Texte);
	}

	/*** STATEmainmap ***/
	sysinfo.var.statescreen = State_Type::STATEmainmap;

	for (unsigned int i(0); i < MAX_POP; i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.number,
			Texte_Type::blended, std::to_string(i), { 255, 255, 255, 255 }, NoColor, 18, 1000, 1000,
			nonTransparent, no_angle, Center_Type::nocenter);
	}

	for (unsigned int i(0); i < nbcitie; i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
			Texte_Type::blended, sysinfo.var.s_player.tabCitieName[i], { 255, 64, 0, 255 }, NoColor, 12, -1, -1,
			nonTransparent, no_angle, Center_Type::nocenter);
	}


	sysinfo.var.select = Select_Type::selectcreate;
	for (unsigned int i(0); i < sysinfo.var.s_player.tabUnit_Template.size(); i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.citieMap,
			Texte_Type::blended, sysinfo.var.s_player.tabUnit_Template[i].name, { 0, 64, 255, 255 }, NoColor, 18, 64, 400,
			nonTransparent, no_angle, Center_Type::nocenter);
	}

	/*** STATEcitiemap ***/
	sysinfo.var.statescreen = State_Type::STATEcitiemap;
	sysinfo.var.select = Select_Type::selectcreate;
	for (unsigned int i(0); i < sysinfo.var.s_player.tabUnit_Template.size(); i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.citieMap,
			Texte_Type::blended, "life:" + std::to_string(sysinfo.var.s_player.tabUnit_Template[i].life) +
			"/atq:" + std::to_string(sysinfo.var.s_player.tabUnit_Template[i].atq) +
			"/def:" + std::to_string(sysinfo.var.s_player.tabUnit_Template[i].def) +
			"/move:" + std::to_string(sysinfo.var.s_player.tabUnit_Template[i].movement),
			{ 255, 64, 0, 255 }, NoColor, 24, 0, 0, nonTransparent, no_angle, Center_Type::nocenter);
	}

	/* *********************************************************
	 *					END sysinfo.allTexte				   *
	 ********************************************************* */


	 /* ### Don't put code below here ### */

	logfileconsole("[INFO]___: [END] : calculImage");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : readXmlTexte																   */
/* ROLE : Initialisation des Textes par la lecture du fichier Texte.xml				   */
/* ROLE : Enregistrement des pointeurs dans des unorder_map							   */
/* INPUT : struct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void LoadConfig::readXmlTexte
(
	tinyxml2::XMLDocument& texteFile,
	SDL_Renderer*& renderer,
	TTF_Font* font[],
	AllTextes& allTextes,
	Uint16 screenWidth,
	Uint16 screenHeight
)
{
	const char* root("Config");


	const char	* s_M_Texte("Texte"),
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
						//* s_FontColor_Complexe_condition("Condition"), // not use
							* s_FontColor_Complexe_R("R"),
							* s_FontColor_Complexe_G("G"),
							* s_FontColor_Complexe_B("B"),
							* s_FontColor_Complexe_Alpha("Alpha"),
					* s_BackColor("FontColor"),
						* s_BackColor_Simple("Simple"),
						* s_BackColor_Simple_Condition("Condition"),
							* s_BackColor_Simple_Color("Color"),
						* s_BackColor_Complexe("Complexe"),
						//* s_BackColor_Complexe_condition("Condition"), //not use
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
			Texte::loadTexte
				(	renderer,
					font,
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
					xmlGiveCenter(node->FirstChildElement(s_Center)->GetText())
				);
		}
		catch (const std::string & msg)
		{
			End::exitError("[ERROR]___: IHM::determineCoor : " + msg);
		}

		/* Recherche du noeud Model suivant */
		node = node->NextSibling();
	}
}

State_Type LoadConfig::xmlGiveStateType
(
	std::string type
)
{
	if (type.compare("error") == IDENTICAL_STRINGS)
	{
		return State_Type::error;
	}
	else if (type.compare("STATEtitleScreen") == IDENTICAL_STRINGS)
	{
		return State_Type::STATEtitleScreen;
	}
	else if (type.compare("STATEscreennewgame") == IDENTICAL_STRINGS)
	{
		return State_Type::STATEscreennewgame;
	}
	else if (type.compare("STATEreload") == IDENTICAL_STRINGS)
	{
		return State_Type::STATEreload;
	}
	else if (type.compare("STATEmainmap") == IDENTICAL_STRINGS)
	{
		return State_Type::STATEmainmap;
	}
	else if (type.compare("STATEscience") == IDENTICAL_STRINGS)
	{
		return State_Type::STATEscience;
	}
	else if (type.compare("STATEcitiemap") == IDENTICAL_STRINGS)
	{
		return State_Type::STATEcitiemap;
	}
	else
	{
		return State_Type::error;
	}
}

Select_Type LoadConfig::xmlGiveSelectType
(
	std::string type
)
{
	if (type.compare("selectnothing") == IDENTICAL_STRINGS)
	{
		return Select_Type::selectnothing;
	}
	else if (type.compare("selectcreate") == IDENTICAL_STRINGS)
	{
		return Select_Type::selectcreate;
	}
	else if (type.compare("selectinspect") == IDENTICAL_STRINGS)
	{
		return Select_Type::selectinspect;
	}
	else if (type.compare("selectmove") == IDENTICAL_STRINGS)
	{
		return Select_Type::selectmove;
	}
	else if (type.compare("selectmoveCitizen") == IDENTICAL_STRINGS)
	{
		return Select_Type::selectmoveCitizen;
	}
	else
	{
		return Select_Type::selectnothing;
	}
}

std::unordered_map<std::string, Texte*>& LoadConfig::xmlGiveTexteConteneur
(
	AllTextes& allTextes,
	std::string type
)
{
	if (type.compare("titleScreen") == IDENTICAL_STRINGS)
	{
		return allTextes.titleScreen;
	}
	else if (type.compare("newGame") == IDENTICAL_STRINGS)
	{
		return allTextes.newGame;
	}
	else if (type.compare("mainMap") == IDENTICAL_STRINGS)
	{
		return allTextes.mainMap;
	}
	else if (type.compare("citieMap") == IDENTICAL_STRINGS)
	{
		return allTextes.citieMap;
	}
	else
	{
		return allTextes.titleScreen;
	}
}

Texte_Type LoadConfig::xmlGiveTexteType
(
	std::string type
)
{
	if (type.compare("blended") == IDENTICAL_STRINGS)
	{
		return Texte_Type::blended;
	}
	else if (type.compare("shaded") == IDENTICAL_STRINGS)
	{
		return Texte_Type::shaded;
	}
	else
	{
		return Texte_Type::blended;
	}
}

SDL_Color LoadConfig::xmlGiveColor
(
	std::string type
)
{
	if (type.compare("Black") == IDENTICAL_STRINGS)
	{
		return Black;
	}
	else if (type.compare("White") == IDENTICAL_STRINGS)
	{
		return White;
	}
	else if (type.compare("Red") == IDENTICAL_STRINGS)
	{
		return Red;
	}
	else if (type.compare("Green") == IDENTICAL_STRINGS)
	{
		return Green;
	}
	else if (type.compare("Blue") == IDENTICAL_STRINGS)
	{
		return Blue;
	}
	else if (type.compare("Blue") == IDENTICAL_STRINGS)
	{
		return Blue;
	}
	else if (type.compare("Yellow") == IDENTICAL_STRINGS)
	{
		return Yellow;
	}
	else if (type.compare("WriteColorButton") == IDENTICAL_STRINGS)
	{
		return WriteColorButton;
	}
	else if (type.compare("BackColorButton") == IDENTICAL_STRINGS)
	{
		return BackColorButton;
	}
	else if (type.compare("NoColor") == IDENTICAL_STRINGS)
	{
		return NoColor;
	}
	else
	{
		return NoColor;
	}
}

Transparance_Type LoadConfig::xmlGiveAlpha
(
	std::string type
)
{
	if (type.compare("nonTransparent") == IDENTICAL_STRINGS)
	{
		return nonTransparent;
	}
	else if (type.compare("semiTransparent") == IDENTICAL_STRINGS)
	{
		return semiTransparent;
	}
	else if (type.compare("transparent") == IDENTICAL_STRINGS)
	{
		return transparent;
	}
	else
	{
		return nonTransparent;
	}
}

Uint16 LoadConfig::xmlGiveAngle
(
	std::string type
)
{
	if (type.compare("no_angle") == IDENTICAL_STRINGS)
	{
		return no_angle;
	}
	else if (type.compare("inverse") == IDENTICAL_STRINGS)
	{
		return inverse;
	}
	else
	{
		return no_angle;
	}
}

Center_Type LoadConfig::xmlGiveCenter
(
	std::string type
)
{
	if (type.compare("nocenter") == IDENTICAL_STRINGS)
	{
		return Center_Type::nocenter;
	}
	else if (type.compare("center_x") == IDENTICAL_STRINGS)
	{
		return Center_Type::center_x;
	}
	else if (type.compare("center_y") == IDENTICAL_STRINGS)
	{
		return Center_Type::center_y;
	}
	else if (type.compare("center") == IDENTICAL_STRINGS)
	{
		return Center_Type::center;
	}
	else
	{
		return Center_Type::nocenter;
	}
}

int LoadConfig::determineCoor
(
	std::string line,
	Uint16 screenWidth,
	Uint16 screenHeight
)
{
	std::string num(EMPTY_STRING), den(EMPTY_STRING), buffer(EMPTY_STRING);
	unsigned int somme(0), numI(0), denI(0);
	unsigned int i(1);

	if (line[0] == '(')
	{
		while (line[i] != ')')
		{
			num += line[i];
			i++;
		}
		i += 3;
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

		return somme = (unsigned int)Utility::protectedDiv(numI, denI);
	}
	else
	{
		return std::stoi(line);
	}
}

/*
*	End Of File : LoadConfig.cpp
*/