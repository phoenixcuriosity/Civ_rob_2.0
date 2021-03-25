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
#include "NewGame.h"

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

	m_mainMap.initTile();

	/* Need initMain */
	computeSize();

	/* Need computeSize */
	if (!initSDL()) { exitError("[ERROR]___: MainGame::init : initSDL = false"); }

	initOpenGLScreen();

	initShaders();

	initHUDText();

	loadUnitAndSpec();

	m_saveReload.init(m_file.saveInfo);

	/* Need to be after loadUnitAndSpec */
	m_players.init(m_file.imagesPath);

	initUI();
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

	m_screen.screenWidth = 0;
	m_screen.screenHeight = 0;

	/* *********************************************************
	 *					   sysinfo.file						   *
	 ********************************************************* */

	 // sysinfo.file.log = "bin/log/log.txt"; // N/A : const
	m_file.buildings = EMPTY_STRING;
	m_file.citiesNames = EMPTY_STRING;
	m_file.readme = EMPTY_STRING;
	m_file.saveInfo = EMPTY_STRING;
	m_file.saveMaps = EMPTY_STRING;
	m_file.specNames = EMPTY_STRING;
	m_file.units = EMPTY_STRING;
	m_file.texts = EMPTY_STRING;
	m_file.colorShadingVert = EMPTY_STRING;
	m_file.colorShadingFrag = EMPTY_STRING;
	m_file.imagesPath = EMPTY_STRING;

	/* *********************************************************
	 *					   sysinfo.var						   *
	 ********************************************************* */

	 //sysinfo.var.argc = argc; /* Already setup in main */
	 //sysinfo.var.argv = argv; /* Already setup in main */
	m_var.continuer = true;
	m_var.tempPlayerName = EMPTY_STRING;
	m_var.select = Select_Type::selectnothing;
	m_var.statescreen = State_Type::error;
	m_var.cinState = CinState_Type::cinNothing;

	/* *********************************************************
	 *					 sysinfo.allTextures				   *
	 ********************************************************* */


	/* *********************************************************
	 *					    sysinfo							   *
	 ********************************************************* */

	initFile();

	ptrMainGame = this;
	ptrlogger = &m_logger;
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
	m_logger.open(m_file.log, std::ofstream::out | std::ofstream::trunc);
	if (!m_logger.is_open())
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
			* s_ImagesPath("ImagesPath"),
			* s_GUIPath("GUIPath");

		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_TileSize)->QueryUnsignedText(&tmp);
		m_mainMap.SETtileSize(tmp);
		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_MapSizeX)->QueryUnsignedText(&tmp);
		m_mainMap.SETmapSizePixX(tmp);
		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_MapSizeY)->QueryUnsignedText(&tmp);
		m_mainMap.SETmapSizePixY(tmp);

		m_file.readme = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Readme)->GetText();
		m_file.texts = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Texte)->GetText();
		m_file.buildings = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Building)->GetText();
		m_file.citiesNames = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_CitieName)->GetText();
		m_file.units = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Unit)->GetText();
		m_file.specNames = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SpecName)->GetText();
		m_file.saveInfo = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SaveInfo)->GetText();
		m_file.saveMaps = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SaveMaps)->GetText();
		m_file.savePlayers = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SavePlayer)->GetText();
		m_file.colorShadingVert = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ColorShadingVert)->GetText();
		m_file.colorShadingFrag = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ColorShadingFrag)->GetText();
		m_file.imagesPath = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ImagesPath)->GetText();
		m_file.GUIPath = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_GUIPath)->GetText();
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
	m_screen.screenWidth = RealEngine2D::Window::getHorizontal(m_mainMap.GETtileSize());
	m_screen.screenHeight = RealEngine2D::Window::getVertical(m_mainMap.GETtileSize());

	/* ---------------------------------------------------------------------- */
	/* 2° : Maimap														 	  */
	/* ---------------------------------------------------------------------- */
	m_mainMap.SETtoolBarSize((unsigned int)Utility::protectedDiv((m_screen.screenWidth / 10), m_mainMap.GETtileSize()));
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initSDL																	   */
/* ROLE : Init SDL, create window													   */
/* RETURNED VALUE    : bool : true = no Error										   */
/* RETURNED VALUE    : bool : flase = Error											   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool MainGame::initSDL()
{
	int rError(RealEngine2D::initSDLOpenGL());
	if (rError == 0)
	{
		m_screen.window.create
		(
			"Civ_Rob_2.0",
			m_screen.screenWidth,
			m_screen.screenHeight,
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

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initOpenGLScreen															   */
/* ROLE : Init m_screen.openGLScreen and m_mainMap									   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void MainGame::initOpenGLScreen()
{
	m_screen.openGLScreen.camera.init(m_screen.screenWidth, m_screen.screenHeight);
	m_screen.openGLScreen.cameraHUD.init(m_screen.screenWidth, m_screen.screenHeight);
	m_screen.openGLScreen.cameraHUD.SETposition(glm::vec2(m_screen.screenWidth/2, m_screen.screenHeight/2));

	m_mainMap.GETspriteBatch().init();
	m_screen.openGLScreen.spriteBatchHUDDynamic.init();
	m_screen.openGLScreen.spriteBatchHUDStatic.init();
	m_screen.openGLScreen.spriteFont = new RealEngine2D::SpriteFont("times.ttf", 64);

	m_screen.openGLScreen.fpsLimiter.init((float)6000.0);

	m_screen.openGLScreen.audioEngine.init();

	m_screen.openGLScreen.inputManager.init(m_mainMap.GETtileSizePtr());
	
	m_screen.openGLScreen.m_gui.init(m_file.GUIPath);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initShaders																   */
/* ROLE : Init shaders for OpenGL													   */
/* ROLE : 2 files : colorShadingVert and colorShadingFrag							   */
/* ROLE : 3 parameters : vertexPosition	, vertexColor , vertexUV					   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void MainGame::initShaders()
{
	m_screen.openGLScreen.gLSLProgram.compileShaders(m_file.colorShadingVert, m_file.colorShadingFrag);
	m_screen.openGLScreen.gLSLProgram.addAttribut("vertexPosition");
	m_screen.openGLScreen.gLSLProgram.addAttribut("vertexColor");
	m_screen.openGLScreen.gLSLProgram.addAttribut("vertexUV");
	m_screen.openGLScreen.gLSLProgram.linkShaders();
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initHUDText																   */
/* ROLE : Init static Text in HUD													   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void MainGame::initHUDText()
{
	char buffer[256];

	m_screen.openGLScreen.spriteBatchHUDStatic.begin();

	sprintf_s(buffer, "Civ_Rob_2.0 : version 0.23.3.0");
	m_screen.openGLScreen.spriteFont->draw
	(
		m_screen.openGLScreen.spriteBatchHUDStatic,
		buffer,
		glm::vec2(0.0f, 2.0f), // offset pos
		glm::vec2(0.32f), // size
		0.0f,
		RealEngine2D::COLOR_WHITE
	);

	/*
	static GLuint id = RealEngine2D::ResourceManager::getTexture("bin/image/toolbar.png")->GETid();
	m_screen.openGLScreen.spriteBatchHUDStatic.draw
	(
		glm::vec4(0.0f, 0.0f, (int)ceil((m_mainMap.GETtoolBarSize() + 1) * m_mainMap.GETtileSize()), m_screen.screenHeight),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		id,
		0.0f,
		RealEngine2D::COLOR_WHITE
	)*/

	m_screen.openGLScreen.spriteBatchHUDStatic.end();
}

void MainGame::initUI()
{
	m_screen.openGLScreen.m_gui.loadScheme("AlfiskoSkin.scheme");
	m_screen.openGLScreen.m_gui.loadScheme("TaharezLook.scheme");

	m_screen.openGLScreen.m_gui.setFont("DejaVuSans-10");
	CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>
		(m_screen.openGLScreen.m_gui.createWidget(
				"AlfiskoSkin/Button",
				{ 0.1f, 0.1f, 0.1f, 0.05f },
				{ 0,0,0,0 },
				"TestButton"));

	CEGUI::Combobox* testCobobox = static_cast<CEGUI::Combobox*>
		(m_screen.openGLScreen.m_gui.createWidget(
				"TaharezLook/Combobox",
				{ 0.2f, 0.2f, 0.1f, 0.05f },
				{ 0,0,0,0 },
				"TestCobobox"));

	testButton->setText("Hello World");
	m_screen.openGLScreen.m_gui.setMouseCursor("TaharezLook/MouseArrow");
	m_screen.openGLScreen.m_gui.showMouseCursor();

	/* HIDE normal mouse cursor */
	SDL_ShowCursor(0);
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
	texteFile.LoadFile(m_file.units.c_str());

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

		m_players.GETvectUnitTemplate().push_back(currentUnit);

		node = node->NextSibling();
	}
}


//----------------------------------------------------------GameLoop----------------------------------------------------------------//


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : runGameLoop																   */
/* ROLE : Run the game main's loop													   */
/* ROLE : fpsLimiter, update inputManager, inputSDL, moveCameraByDeltaTime			   */
/* ROLE : camera update, drawGame, fpsLimiter										   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void MainGame::runGameLoop()
{

	m_mainMap.generateMap();
	//m_mainMap.drawMap(m_screen.openGLScreen.camera);

	RealEngine2D::Music music = m_screen.openGLScreen.audioEngine.loadMusic("sounds/the_field_of_dreams.mp3");
	//music.play(-1);
	//Mix_VolumeMusic(16);

	NewGame::newGame(*this);

	while (m_var.continuer)
	{
		m_screen.openGLScreen.fpsLimiter.begin();

		m_screen.openGLScreen.inputManager.update();

		inputUpdate();
	
		/* exit game, avoid to draw */
		if (!m_var.continuer) return;

		if (m_screen.openGLScreen.inputManager.isKeyDown(SDLK_SPACE))
		{
			m_nextTurn.nextTurn(*this);
			m_screen.openGLScreen.inputManager.releaseKey(SDLK_SPACE);
		}

		moveCameraByDeltaTime();

		m_screen.openGLScreen.camera.update();
		m_screen.openGLScreen.cameraHUD.update();

		drawGame();

		m_screen.fps = m_screen.openGLScreen.fpsLimiter.end();
		
	}
}


void MainGame::inputUpdate()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		GameInput::inputSDL(*this, ev);
		m_screen.openGLScreen.m_gui.onSDLEvent(ev, m_screen.openGLScreen.inputManager);
	}
}

void MainGame::moveCameraByDeltaTime()
{
	static Uint32 prevTicks(SDL_GetTicks());
	Uint32 frameTime(0), newTicks(0);
	float totalDeltaTime(0.0f), deltaTime(0.0f);
	
	newTicks = SDL_GetTicks();
	frameTime = newTicks - prevTicks;
	prevTicks = newTicks;
	totalDeltaTime = (float)frameTime / TARGET_FRAMETIME;
	int i(0);

	while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS)
	{
		deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
		moveCamera(deltaTime);
		totalDeltaTime -= deltaTime;
		i++;
	}
}

void MainGame::moveCamera(float deltaTime)
{
	if (m_screen.openGLScreen.inputManager.isKeyDown(SDLK_z))
	{
		m_screen.openGLScreen.camera
			.SETposition
			(
				m_screen.openGLScreen.camera.GETposition()
				+
				glm::vec2(0.0f, KEY_SPEED_MOVE * deltaTime)
			);
		m_mainMap.SETneedToUpdateDraw(true);
		m_players.SETneedToUpdateDrawUnit(true);
	}
	if (m_screen.openGLScreen.inputManager.isKeyDown(SDLK_s))
	{
		m_screen.openGLScreen.camera
			.SETposition
			(
				m_screen.openGLScreen.camera.GETposition()
				+
				glm::vec2(0.0f, -KEY_SPEED_MOVE * deltaTime)
			);
		m_mainMap.SETneedToUpdateDraw(true);
		m_players.SETneedToUpdateDrawUnit(true);
	}
	if (m_screen.openGLScreen.inputManager.isKeyDown(SDLK_q))
	{
		m_screen.openGLScreen.camera
			.SETposition
			(
				m_screen.openGLScreen.camera.GETposition()
				+
				glm::vec2(-KEY_SPEED_MOVE * deltaTime, 0.0f)
			);
		m_mainMap.SETneedToUpdateDraw(true);
		m_players.SETneedToUpdateDrawUnit(true);
	}
	if (m_screen.openGLScreen.inputManager.isKeyDown(SDLK_d))
	{
		m_screen.openGLScreen.camera
			.SETposition
			(
				m_screen.openGLScreen.camera.GETposition()
				+
				glm::vec2(KEY_SPEED_MOVE * deltaTime, 0.0f)
			);
		m_mainMap.SETneedToUpdateDraw(true);
		m_players.SETneedToUpdateDrawUnit(true);
	}
}

void MainGame::drawGame()
{
	/* line for CEGUI because CEGUI doesn't do it, do not remove  */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Back */
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_screen.openGLScreen.gLSLProgram.use();
	/* use GL_TEXTURE0 for 1 pipe; use GL_TEXTURE1/2/3 for multiple */
	glActiveTexture(GL_TEXTURE0);

	GLuint textureLocation = m_screen.openGLScreen.gLSLProgram.getUnitformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	/* camera */
	GLuint pLocation = m_screen.openGLScreen.gLSLProgram.getUnitformLocation("P");
	glm::mat4 cameraMatrix = m_screen.openGLScreen.camera.GETcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_mainMap.drawMap(m_screen.openGLScreen.camera);
	m_players.drawUnit(m_mainMap, m_screen.openGLScreen.camera);

	m_mainMap.renderMap();
	m_players.renderUnit();

	drawHUD();

	glBindTexture(GL_TEXTURE_2D, 0);

	m_screen.openGLScreen.gLSLProgram.unuse();

	m_screen.openGLScreen.m_gui.draw();

	m_screen.window.swap();
}

void MainGame::drawHUD()
{
	/* camera HUD */
	GLuint pLocation = m_screen.openGLScreen.gLSLProgram.getUnitformLocation("P");
	glm::mat4 cameraMatrix = m_screen.openGLScreen.cameraHUD.GETcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];
	

	m_screen.openGLScreen.spriteBatchHUDDynamic.begin();

	sprintf_s(buffer, "FPS %f", m_screen.fps);
	m_screen.openGLScreen.spriteFont->draw
	(
		m_screen.openGLScreen.spriteBatchHUDDynamic,
		buffer,
		glm::vec2(0.0f, 32.0f), // offset pos
		glm::vec2(0.32f), // size
		0.0f,
		RealEngine2D::COLOR_WHITE
	);

	sprintf_s(buffer, "Nb Turn %d", m_nextTurn.GETnbTurn());
	m_screen.openGLScreen.spriteFont->draw
	(
		m_screen.openGLScreen.spriteBatchHUDDynamic,
		buffer,
		glm::vec2(0.0f, 64.0f), // offset pos
		glm::vec2(0.32f), // size
		0.0f,
		RealEngine2D::COLOR_BLUE
	);

	

	m_screen.openGLScreen.spriteBatchHUDDynamic.end();

	m_screen.openGLScreen.spriteBatchHUDDynamic.renderBatch();
	m_screen.openGLScreen.spriteBatchHUDStatic.renderBatch();
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
	char  buf[255];
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