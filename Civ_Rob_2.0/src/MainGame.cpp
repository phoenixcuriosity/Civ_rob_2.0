/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.2.0
	file version : 1.2

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

#include <iostream>

#include "MainMap.h"
#include "Utility.h"
#include "XmlConvertValue.h"

#include <RealEngine2D\src\ResourceManager.h>

static std::ofstream* ptrlogger;
static MainGame* ptrMainGame;

//----------------------------------------------------------Const/Destr----------------------------------------------------------------//

MainGame::MainGame()
{
	init();
}

MainGame::~MainGame()
{

}

void MainGame::init()
{
	initStructsNULL();

	initMain();

	_mainMap.initTile();

	computeSize();

	if (!initSDL()) { exitError("[ERROR]___: MainGame::init : initSDL = false"); }

	initOpenGLScreen();

	initShaders();
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initStructs																   */
/* ROLE : Initialisation des données par défaut des structures						   */
/* INPUT : struct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void MainGame::initStructsNULL()
{
	/* ### Mettre ici les cas d'inialisation des structures ### */

	/* *********************************************************
	 *					   sysinfo.screen					   *
	 ********************************************************* */

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
	_file.colorShadingVert = EMPTY_STRING;
	_file.colorShadingFrag = EMPTY_STRING;
	_file.imagesPath = EMPTY_STRING;

	/* *********************************************************
	 *					   sysinfo.var						   *
	 ********************************************************* */

	 //sysinfo.var.argc = argc; /* Already setup in main */
	 //sysinfo.var.argv = argv; /* Already setup in main */
	_var.continuer = true;
	_var.nbturn = 0;
	_var.tempPlayerName = EMPTY_STRING;
	_var.tempX = 0;
	_var.tempY = 0;
	_var.select = Select_Type::selectnothing;
	_var.statescreen = State_Type::error;
	_var.cinState = CinState_Type::cinNothing;

	/* *********************************************************
	 *					 sysinfo.allTextures				   *
	 ********************************************************* */


	/* *********************************************************
	 *					    sysinfo							   *
	 ********************************************************* */

	initFile();

	ptrMainGame = this;
	ptrlogger = &_logger;
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
void MainGame::initMain()
{
	logfileconsole("[INFO]___: [START] : initMain");

	tinyxml2::XMLDocument config;
	config.LoadFile(configFilePath.c_str());
	unsigned int tmp(0);

	if (config.ErrorID() == 0)
	{
		const char* root("Config");


		const char* s_Map("Map"),
			* s_TileSize("TileSize"),
			* s_MapSizeX("MapSizeX"),
			* s_MapSizeY("MapSizeY"),

			* s_FilePaths("FilePaths"),
			* s_Readme("Readme"),
			* s_Texte("Texts"),
			* s_Building("Buildings"),
			* s_CitieName("CitiesNames"),
			* s_Unit("Units"),
			* s_SpecName("SpecNames"),
			* s_SaveInfo("SaveInfo"),
			* s_SaveMaps("SaveMaps"),
			* s_SavePlayer("SavePlayers"),
			* s_ColorShadingVert("ColorShadingVert"),
			* s_ColorShadingFrag("ColorShadingFrag"),
			* s_ImagesPath("ImagesPath");

		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_TileSize)->QueryUnsignedText(&tmp);
		_mainMap.SETtileSize(tmp);
		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_MapSizeX)->QueryUnsignedText(&tmp);
		_mainMap.SETmapSizePixX(tmp);
		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_MapSizeY)->QueryUnsignedText(&tmp);
		_mainMap.SETmapSizePixY(tmp);

		_file.readme = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Readme)->GetText();
		_file.texts = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Texte)->GetText();
		_file.buildings = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Building)->GetText();
		_file.citiesNames = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_CitieName)->GetText();
		_file.units = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Unit)->GetText();
		_file.specNames = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SpecName)->GetText();
		_file.saveInfo = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SaveInfo)->GetText();
		_file.saveMaps = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SaveMaps)->GetText();
		_file.savePlayers = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SavePlayer)->GetText();
		_file.colorShadingVert = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ColorShadingVert)->GetText();
		_file.colorShadingFrag = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ColorShadingFrag)->GetText();
		_file.imagesPath = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ImagesPath)->GetText();
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
void MainGame::computeSize()
{
	/* ---------------------------------------------------------------------- */
	/* 1° : Screen														 	  */
	/* ---------------------------------------------------------------------- */
	_screen.screenWidth = getHorizontal(_mainMap.GETtileSize());
	_screen.screenHeight = getVertical(_mainMap.GETtileSize());

	/* ---------------------------------------------------------------------- */
	/* 2° : Maimap														 	  */
	/* ---------------------------------------------------------------------- */
	_mainMap.SETtoolBarSize((unsigned int)Utility::protectedDiv((_screen.screenWidth / 10), _mainMap.GETtileSize()));
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
	int rError(RealEngine2D::initSDLOpenGL());
	if (rError == 0)
	{
		_screen.window.create
		(
			"Civ_Rob_2.0",
			_screen.screenWidth,
			_screen.screenHeight,
			0
		);
		return true;
	}
	else
	{
		exitError("[ERROR]___: initSDL : code error : " + std::to_string(rError));
		return false;
	}
}

void MainGame::initOpenGLScreen()
{
	_screen.openGLScreen.camera.init(_screen.screenWidth, _screen.screenHeight);
	_screen.openGLScreen.spriteBatch.init();
	_screen.openGLScreen.fpsLimiter.init((float)SCREEN_REFRESH_RATE);
}

void MainGame::initShaders()
{
	_screen.openGLScreen.gLSLProgram.compileShaders(_file.colorShadingVert, _file.colorShadingFrag);
	_screen.openGLScreen.gLSLProgram.addAttribut("vertexPosition");
	_screen.openGLScreen.gLSLProgram.addAttribut("vertexColor");
	_screen.openGLScreen.gLSLProgram.addAttribut("vertexUV");
	_screen.openGLScreen.gLSLProgram.linkShaders();
}

//----------------------------------------------------------Screen width/height----------------------------------------------------------------//

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

//----------------------------------------------------------Load----------------------------------------------------------------//

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

		_players.GETvectUnitTemplate().push_back(currentUnit);

		node = node->NextSibling();
	}
}

//----------------------------------------------------------GameLoop----------------------------------------------------------------//

void MainGame::runGameLoop()
{
	_mainMap.generateMap();

	while (_var.continuer)
	{
		_screen.openGLScreen.fpsLimiter.begin();

		_screen.openGLScreen.inputManager.update();

		GameInput::inputSDL(*this);

		_screen.openGLScreen.camera.update();

		drawGame();

		_screen.fps = _screen.openGLScreen.fpsLimiter.end();
	}
}

void MainGame::drawGame()
{
	/* Back */
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_screen.openGLScreen.gLSLProgram.use();
	/* use GL_TEXTURE0 for 1 pipe; use GL_TEXTURE1/2/3 for multiple */
	glActiveTexture(GL_TEXTURE0);

	GLuint textureLocation = _screen.openGLScreen.gLSLProgram.getUnitformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	/* camera */
	GLuint pLocation = _screen.openGLScreen.gLSLProgram.getUnitformLocation("P");
	glm::mat4 cameraMatrix = _screen.openGLScreen.camera.GETcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));


	_screen.openGLScreen.spriteBatch.begin();

	_mainMap.drawMap(_screen.openGLScreen.spriteBatch);

	_screen.openGLScreen.spriteBatch.end();

	_screen.openGLScreen.spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	_screen.openGLScreen.gLSLProgram.unuse();

	_screen.window.swap();
}

//----------------------------------------------------------NewGame----------------------------------------------------------------//

void MainGame::newGame()
{
	logfileconsole("[INFO]___: Newgame Start");
	_var.statescreen = State_Type::STATEscreenNewgame;

	SaveReload::createSave(*this);

	//SDL_RenderClear(sysinfo.screen.renderer);

	/* *********************************************************
	 *						Nb player ?						   *
	 ********************************************************* */

	 /* ---------------------------------------------------------------------- */
	 /* Première demande au joueur : 										  */
	 /* Le nombre de joueurs ?												  */
	 /* ---------------------------------------------------------------------- */
	

	/* ---------------------------------------------------------------------- */
	/* Le joueur doit rentrer une valeur entre 1 et 9, par défaut 1 		  */
	/* ---------------------------------------------------------------------- */
	

	/* *********************************************************
	 *					Name of player ?					   *
	 ********************************************************* */

	

	/* ---------------------------------------------------------------------- */
	/* Deuxième demande au joueur : 										  */
	/* Le nom des joueurs													  */
	/* ---------------------------------------------------------------------- */
	

	/* *********************************************************
	 *					Map Generation						   *
	 ********************************************************* */

	_mainMap.generateMap();

	newGameSettlerSpawn();

	/* *********************************************************
	 *							Save						   *
	 ********************************************************* */

	SaveReload::save(*this);

	/* *********************************************************
	 *					 Button Creation					   *
	 ********************************************************* */

	 /* ---------------------------------------------------------------------- */
	 /* Création des boutons pour séléctionner les joueurs			 		  */
	 /* ---------------------------------------------------------------------- */

	_var.statescreen = State_Type::STATEmainMap;
	_var.cinState = CinState_Type::cinMainMap;

	

	/* ### Don't put code below here ### */

	logfileconsole("[INFO]___: Newgame End");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : newGameSettlerSpawn														   */
/* ROLE : Création des position pour les settlers de chaque joueurs					   */
/* INPUT : const std::vector<Unit_Template>& : tableau des statistiques ...			   */
/* INPUT : ...  par défauts des unités												   */
/* INPUT : const struct Map& map : structure globale de la map						   */
/* INPUT/OUTPUT : std::vector<Player*>& : vecteurs de joueurs						   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void MainGame::newGameSettlerSpawn()
{
	/* ---------------------------------------------------------------------- */
	/* association des vecteurs de position (x,y)							  */
	/* avec les settlers de départ											  */
	/* ---------------------------------------------------------------------- */
	unsigned int selectunit(0);
	selectunit = Unit::searchUnitByName("settler", _players.GETvectUnitTemplate());

	std::vector<randomPos> tabRandom;
	for (unsigned int i(0); i < _players.GETvectPlayer().size(); i++)
	{

		makeRandomPosTab(_mainMap, tabRandom);

		_players.GETvectPlayer()[i]->addUnit
		("settler",
			tabRandom[i].x,
			tabRandom[i].y,
			_players.GETvectUnitTemplate()[selectunit].type,
			_players.GETvectUnitTemplate()[selectunit].life,
			_players.GETvectUnitTemplate()[selectunit].atq,
			_players.GETvectUnitTemplate()[selectunit].def,
			_players.GETvectUnitTemplate()[selectunit].movement,
			_players.GETvectUnitTemplate()[selectunit].level,
			MAINTENANCE_COST_1TH_SETTLER);
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : makeRandomPosTab															   */
/* ROLE : Créér autant de vecteur de position (x,y) que de joueur initial			   */
/* INPUT : const Map& map : structure globale de la map								   */
/* INPUT/OUTPUT : std::vector<randomPos>& : vecteurs de positions					   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void MainGame::makeRandomPosTab
(
	const MainMap& mainMap,
	std::vector<randomPos>& tabRandom
)
{
	randomPos RandomPOS;
	bool continuer(true);
	unsigned int iteration(0);

	while (continuer)
	{
		if (iteration >= MAX_RANDOM_POS_ITERATION)
		{
#ifdef _DEBUG
			exitError("[ERROR]___: makeRandomPosTab, Too many Iterations");
#endif // DEBUG_MODE
			/*
			TODO : remove existing settlers and players
				 : return to main menu with error message "too many player with this map size"
			*/
		}
		iteration++;

		makeRandomPos(RandomPOS, mainMap.GETmatriceMapConst(), mainMap.GETtoolBarSize(), mainMap.GETtileSize());
		if (conditionground(mainMap.GETmatriceMapConst(), RandomPOS))
		{
			continuer = !conditionspace(RandomPOS, tabRandom, mainMap.GETtileSize());
		}
	}
	tabRandom.push_back(RandomPOS);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : makeRandomPos																   */
/* ROLE : créér un vecteur de position (x,y) aléatoire respectant la taille de l'écran */
/* OUTPUT : randomPos& RandomPOS : couple de positions								   */
/* INPUT : const std::vector<std::vector<Tile>>& maps : Matrice maps				   */
/* INPUT : unsigned int toolBarSize: taille de la barre d'outil						   */
/* INPUT : unsigned int tileSize													   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void MainGame::makeRandomPos
(
	randomPos& RandomPOS,
	const MatriceMap& matriceMap,
	unsigned int toolBarSize,
	unsigned int tileSize
)
{
	int x((rand() % ((unsigned int)(matriceMap.size() * tileSize) - (unsigned int)(toolBarSize * tileSize))) + (toolBarSize * tileSize));
	int y((rand() % (matriceMap[0].size() * tileSize)));
	RandomPOS.x = (int)ceil(x / tileSize) * tileSize;
	RandomPOS.y = (int)ceil(y / tileSize) * tileSize;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : conditionspace															   */
/* ROLE : condition pour valider les coordonnées crées:								   */
/* ROLE : etre en dehors d'un carré d'influence (ici tileSize * 8) d'une autre entitée */
/* INPUT : const randomPos& RandomPOS : couple de positions							   */
/* INPUT : const std::vector<randomPos>& : vecteurs de positions					   */
/* INPUT : unsigned int tileSize													   */
/* INPUT : unsigned int i : couple de positions courant								   */
/* RETURNED VALUE    : true -> condition de position validée / false -> non valide     */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
bool MainGame::conditionspace
(
	const randomPos& RandomPOS,
	const std::vector<randomPos>& tabRandom,
	unsigned int tileSize
)
{
	int spaceBetweenSettler(tileSize * MIN_SPACE_BETWEEN_SETTLER);

	for (unsigned int i(0); i < tabRandom.size(); i++)
	{
		if (
			(RandomPOS.x >= (tabRandom[i].x - spaceBetweenSettler)) /* West */
			&&
			(RandomPOS.x <= (tabRandom[i].x + spaceBetweenSettler)) /* East */
			&&
			(RandomPOS.y >= (tabRandom[i].y - spaceBetweenSettler)) /* North */
			&&
			(RandomPOS.y <= (tabRandom[i].y + spaceBetweenSettler)) /* South */
			)
		{
			return false;
		}
	}
	return true;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : conditionground															   */
/* ROLE : condition pour valider les coordonnées crées:								   */
/* ROLE : - etre sur une tile possédant la caractéristique d'etre du sol			   */
/* INPUT : const std::vector<std::vector<Tile>>& : Matrice de la map				   */
/* INPUT : const std::vector<randomPos>& : vecteurs de positions					   */
/* RETURNED VALUE    : true -> condition de position validée / false -> non valide	   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
bool MainGame::conditionground
(
	const MatriceMap& matriceMap,
	const randomPos& RandomPOS
)
{
	unsigned int x(MainMap::convertPosXToIndex(RandomPOS.x));
	unsigned int y(MainMap::convertPosYToIndex(RandomPOS.y));

	if (
			MainMap::assertRangeMapIndex(x, matriceMap.size())
			&&
			MainMap::assertRangeMapIndex(y, matriceMap[x].size())
		)
	{
		if (
			matriceMap[x][y].tile_ground
			==
			Ground_Type::grass
			)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		throw("[ERROR]___: GamePlay::conditionground : assertRangeMapIndex == false");
	}
}


//----------------------------------------------------------Destroy----------------------------------------------------------------//

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
	const std::string& msg
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

//----------------------------------------------------------Logger----------------------------------------------------------------//


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
	const std::string& msg
)
{
	time_t now(time(0));
	struct tm  tstruct;
	char  buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%F %X", &tstruct);

#ifdef _DEBUG
	std::cout << std::endl << buf << "      " << msg;
#endif // DEBUG_MODE
	*ptrlogger << std::endl << buf << "      " << msg;
}


/*
*	End Of File : MainGame.cpp
*/