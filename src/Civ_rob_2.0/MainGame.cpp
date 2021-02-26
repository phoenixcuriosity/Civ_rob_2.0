/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.0.0
	file version : 1.0

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

#include "MainGame.h"


static std::ofstream* ptrlogger;
static MainGame* ptrMainGame;



MainGame::MainGame()
{
	init();
}

MainGame::~MainGame()
{

}

void MainGame::init()
{
	initStructs();
	initMain();
	computeSize();
	if (!initSDL())
	{
		exitError("[ERROR]___: MainGame::init : initSDL = false");
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initStructs																   */
/* ROLE : Initialisation des données par défaut des structures						   */
/* INPUT : struct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void MainGame::initStructs()
{
	/* ### Mettre ici les cas d'inialisation des structures ### */

	/* *********************************************************
	 *					   sysinfo.screen					   *
	 ********************************************************* */

	_screen.window = nullptr;
	_screen.screenWidth = 0;
	_screen.screenHeight = 0;

	/* *********************************************************
	 *					   sysinfo.file						   *
	 ********************************************************* */

	 // sysinfo.file.log = "bin/log/log.txt"; // N/A : const
	_file.buildings = EMPTY_STRING;
	_file.citiesNames = EMPTY_STRING;
	_file.readme = EMPTY_STRING;
	_file.saveInfo = EMPTY_STRING;
	_file.saveMaps = EMPTY_STRING;
	_file.specNames = EMPTY_STRING;
	_file.units = EMPTY_STRING;
	_file.texts = EMPTY_STRING;

	/* *********************************************************
	 *					   sysinfo.var						   *
	 ********************************************************* */

	 //sysinfo.var.argc = argc; /* Already setup in main */
	 //sysinfo.var.argv = argv; /* Already setup in main */
	_var.continuer = true;
	_var.waitEvent = true;
	_var.nbturn = 0;
	_var.nbPlayer = 0;
	_var.tempPlayerName = EMPTY_STRING;
	_var.tempX = 0;
	_var.tempY = 0;
	_var.select = Select_Type::selectnothing;
	_var.statescreen = State_Type::error;
	//_var.cinState = CinState_Type::cinNothing;

	/* sysinfo.var.s_player */

	_var.s_player.selectCity = NO_CITY_SELECTED;
	_var.s_player.selectplayer = NO_PLAYER_SELECTED;
	_var.s_player.selectPlayerToAttack = NO_PLAYER_SELECTED;
	_var.s_player.selectunit = NO_UNIT_SELECTED;
	_var.s_player.selectUnitToAttack = NO_UNIT_SELECTED;
	_var.s_player.unitToCreate = 0;
	_var.s_player.toBuild = EMPTY_STRING;
	_var.s_player.unitNameToCreate = EMPTY_STRING;
	_var.s_player.unitNameToMove = EMPTY_STRING;

	_var.s_player.tabCitiesName.clear();
	_var.s_player.tabPlayerName.clear();
	//_var.s_player.tabUnit_Template.clear();

	_var.s_player.nbNoNamePlayer = 0;
	_var.s_player.citiesNameMaxToCreate = 0;

	/* sysinfo.var.mouse */

	//KeyboardMouse mouse;
	//_var.mouse = mouse;

	/* sysinfo.var.save */

	//SaveReload save;
	//_var.save = save;

	/* *********************************************************
	 *					 sysinfo.allTextures				   *
	 ********************************************************* */



	 /* *********************************************************
	  *					    sysinfo.map						   *
	  ********************************************************* */

	_map.mapSize = 0;
	_map.tileSize = 0;
	_map.toolBarSize = 0;
	_map.screenOffsetXIndexMin = 0;
	_map.screenOffsetYIndexMin = 0;
	_map.screenOffsetXIndexMax = 0;
	_map.screenOffsetYIndexMax = 0;
	//_map.matriceMap.clear();
	initTile(_map);


	/* *********************************************************
	 *					    sysinfo							   *
	 ********************************************************* */

	_vectPlayer.clear();

	initFile();

	ptrMainGame = this;
	ptrlogger = &_logger;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initTile																	   */
/* ROLE : Initialisation des cases de la map en fonction de sa taille				   */
/* INPUT : struct Map& : données générale de la map : taille						   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void MainGame::initTile
(
	Map& map
)
{
	/*
	Tile blankTile;
	std::vector<Tile> blank;
	for (unsigned int i(0); i < map.mapSize / map.tileSize; i++)
	{
		map.matriceMap.push_back(blank);
		for (unsigned int j(0); j < map.mapSize / map.tileSize; j++)
		{
			map.matriceMap[i].push_back(blankTile);
		}
	}
	*/
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initFile																	   */
/* ROLE : Initialisation des fichiers : log											   */
/* INPUT : struct File& : nom des fichiers											   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void MainGame::initFile()
{
	_logger.open(_file.log, std::ofstream::out | std::ofstream::trunc);
	if (!_logger.is_open())
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
void MainGame::initMain
(

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
			* s_Texte("Texts"),
			* s_Building("Buildings"),
			* s_CitieName("CitiesNames"),
			* s_Unit("Units"),
			* s_SpecName("SpecNames"),
			* s_SaveInfo("SaveInfo"),
			* s_SaveMaps("SaveMaps"),
			* s_SavePlayer("SavePlayers");

		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_TileSize)->QueryUnsignedText(&_map.tileSize);
		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_MapSize)->QueryUnsignedText(&_map.mapSize);

		_file.readme = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Readme)->GetText();
		_file.texts = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Texte)->GetText();
		_file.buildings = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Building)->GetText();
		_file.citiesNames = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_CitieName)->GetText();
		_file.units = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Unit)->GetText();
		_file.specNames = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SpecName)->GetText();
		_file.saveInfo = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SaveInfo)->GetText();
		_file.saveMaps = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SaveMaps)->GetText();
		_file.savePlayers = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SavePlayer)->GetText();
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
void MainGame::computeSize
(

)
{
	/* ---------------------------------------------------------------------- */
	/* 1° : Screen														 	  */
	/* ---------------------------------------------------------------------- */
	_screen.screenWidth = getHorizontal(_map.tileSize);
	_screen.screenHeight = getVertical(_map.tileSize);

	/* ---------------------------------------------------------------------- */
	/* 2° : Maimap														 	  */
	/* ---------------------------------------------------------------------- */
	//_map.toolBarSize = (unsigned int)Utility::protectedDiv((_screen.screenWidth / 10), _map.tileSize);
	//_map.screenOffsetXIndexMax = (unsigned int)Utility::protectedDiv(((_screen.screenWidth * 9) / 10), _map.tileSize);
	//_map.screenOffsetYIndexMax = (unsigned int)Utility::protectedDiv(_screen.screenHeight, _map.tileSize);

	/* ---------------------------------------------------------------------- */
	/* 3° : CitieMap													 	  */
	/* ---------------------------------------------------------------------- */
	_map.sizeCityMap.ToolbarButtonsH = (_screen.screenWidth / 3);
	_map.sizeCityMap.ToolbarButtonsW = (_screen.screenHeight / 3);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : getHorizontal																   */
/* ROLE : Calcul de la longueur en pixels de la fenetre								   */
/* INPUT : unsigned int tileSize : taille en pixel d'une tile 						   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Uint16 MainGame::getHorizontal
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
Uint16 MainGame::getVertical
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
/* NAME : initSDL																	   */
/* ROLE : Initialisation de la SDL fenetre et renderer ...							   */
/* ROLE : ... ainsi que le tableau de police de font								   */
/* INPUT : SDL_Window*& : pointeur sur la fenetre de la SDL							   */
/* INPUT : SDL_Renderer*& : pointeur sur le Renderer de la SDL						   */
/* INPUT : TTF_Font*[] : pointeur sur le tableau de police de font					   */
/* RETURNED VALUE    : bool : true = pas d'erreur lors de l'initialisation de la SDL   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool MainGame::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		/* ---------------------------------------------------------------------- */
		/* 1° : Si l'initialisation de tous les services de la SDL est failed	  */
		/* ---------------------------------------------------------------------- */

		logfileconsole("[ERROR]: SDL could not initialize! SDL_Error: " + (std::string)SDL_GetError());
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

		_screen.window = SDL_CreateWindow(	"Civ_Rob_2.0",
											SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
											500, 500,
											SDL_WINDOW_OPENGL);

		if (nullptr == _screen.window)
		{
			logfileconsole("[ERROR]___: CreateWindow Failed");
			return false;
		}
		else
		{
			logfileconsole("[INFO]___: CreateWindow Success");

			SDL_GLContext glContext = SDL_GL_CreateContext(_screen.window);

			if (nullptr == glContext)
			{
				logfileconsole("[ERROR]___: glContext Failed");
				return false;
			}
			logfileconsole("[INFO]___: glContext Success");

			GLenum error = glewInit();
			if (GLEW_OK != error)
			{
				logfileconsole("[ERROR]___: GLenum Failed");
			}
			logfileconsole("[ERROR]___: GLenum Success");

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		}

		logfileconsole("[INFO]___: SDL_Init Success");
		return true;
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
void MainGame::loadUnitAndSpec()
{
	/*
	tinyxml2::XMLDocument texteFile;
	texteFile.LoadFile(_file.units.c_str());

	const char* root("Root");

	const char* s_Unit("Unit"),
		* s_Name("Name"),
		* s_MovementType("MovementType"),
		* s_Life("Life"),
		* s_Atq("Atq"),
		* s_Def("Def"),
		* s_Mouvement("Mouvement"),
		* s_Level("Level"),
		* s_WorkToBuild("WorkToBuild"),
		* s_Maintenance("Maintenance");

	tinyxml2::XMLNode* node(texteFile.FirstChildElement(root)->FirstChildElement(s_Unit));
	Unit_Template currentUnit;

	while (nullptr != node)
	{
		currentUnit.name = node->FirstChildElement(s_Name)->GetText();
		currentUnit.type = XmlConvertValue::xmlGiveMovementType(node->FirstChildElement(s_MovementType)->GetText());
		node->FirstChildElement(s_Life)->QueryIntText((int*)&currentUnit.life);
		node->FirstChildElement(s_Atq)->QueryIntText((int*)&currentUnit.atq);
		node->FirstChildElement(s_Def)->QueryIntText((int*)&currentUnit.def);
		node->FirstChildElement(s_Mouvement)->QueryIntText((int*)&currentUnit.movement);
		node->FirstChildElement(s_Level)->QueryIntText((int*)&currentUnit.level);
		node->FirstChildElement(s_Level)->QueryIntText((int*)&currentUnit.level);
		node->FirstChildElement(s_WorkToBuild)->QueryDoubleText((double*)&currentUnit.workToBuild);
		node->FirstChildElement(s_Maintenance)->QueryDoubleText((double*)&currentUnit.maintenance);

		_var.s_player.tabUnit_Template.push_back(currentUnit);

		node = node->NextSibling();
	}
	*/

}

void MainGame::runGameLoop()
{
	while (_var.continuer)
	{
		//_var.mouse.run_SDL(*this);


	}

}



void MainGame::destroy()
{
	deleteAll(*this);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : exitError																	   */
/* ROLE : Enregistre l'erreur survenue et termine le programme de façon sécurisée	   */
/* INPUT : const std::string msg : message de l'erreur								   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void MainGame::exitError
(
	const std::string msg
)
{
	logfileconsole("[ERROR]___: " + msg);
	deleteAll(*ptrMainGame);
	logfileconsole("[ERROR]___: Last msg before exitError : " + msg);
	ptrlogger->close();
	exit(EXIT_FAILURE);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : deleteAll																	   */
/* ROLE : Destruction des allocations dynamique du programme						   */
/* ROLE : Destruction de la fenetre et du Renderer de la SDL						   */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void MainGame::deleteAll
(
	MainGame& mainGame
)
{
	logfileconsole("[INFO]___: [START] *********_________ DeleteAll _________*********");

	
	

	/* *********************************************************
	 *				 START delete SDL						   *
	 ********************************************************* */

	
	if (nullptr != mainGame.GETscreen().window)
	{
		SDL_DestroyWindow(mainGame.GETscreen().window);
		mainGame.GETscreen().window = nullptr;
	}
	else
	{
		logfileconsole("[ERROR]___: [END] : nullptr == sysinfo.screen.window");
	}

	SDL_Quit();

	/* *********************************************************
	 *				 END delete SDL							   *
	 ********************************************************* */

	 /* ### Don't put code below here ### */

	logfileconsole("[INFO]___: [END] : *********_________ DeleteAll _________*********");

	logfileconsole("[INFO]___: SDL_Quit Success");
	logfileconsole("[INFO]___:________PROGRAMME FINISH________");
	ptrlogger->close();
}


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : logfileconsole															   */
/* ROLE : Transmission du message sur la console et dans le fichier log.txt			   */
/* INPUT : const std::string msg : message											   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void MainGame::logfileconsole
(
	const std::string msg
)
{
	time_t now(time(0));
	struct tm  tstruct;
	char  buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%F %X", &tstruct);

#ifdef _DEBUG_MODE
	std::cout << std::endl << buf << "      " << msg;
#endif // DEBUG_MODE
	*ptrlogger << std::endl << buf << "      " << msg;
}


/*
*	End Of File : MainGame.cpp
*/