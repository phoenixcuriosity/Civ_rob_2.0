/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.7.0
	file version : 1.22

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

#include "GamePlayScreen.h"

#include <tinyxml2/tinyxml2.h>

#include "Utility.h"

#include "App.h"
#include "ScreenIndices.h"

#include <RealEngine2D/src/ResourceManager.h> 

GamePlayScreen::GamePlayScreen
(
	SaveReload* SaveReload,
	UserInputNewGame* userInputNewGame
)
: 
RealEngine2D::IGameScreen(),
m_screen(),
m_var(),
m_mainMap(),
m_nextTurn(),
m_players(),
m_SaveReload(SaveReload),
m_isInitialize(false),
m_userInputNewGame(userInputNewGame)
{
	build();
}

GamePlayScreen::~GamePlayScreen()
{
	destroy();
}

int GamePlayScreen::getNextScreenIndex()const
{
	return m_screen.m_nextScreenIndexMenu;
}
int GamePlayScreen::getPreviousScreenIndex()const
{
	return MAINMENU_SCREEN_INDEX;
}

void GamePlayScreen::build()
{
	m_screenIndex = GAMEPLAY_SCREEN_INDEX;
}

void GamePlayScreen::destroy()
{
	m_screen.m_gui.destroy();

	m_screen.m_widgetLabels.clear();

	m_players.deleteAllPlayers();
}

bool GamePlayScreen::onEntry()
{
	if (!m_isInitialize)
	{
		loadFile();

		initStructsNULL();

		computeSize();

		initOpenGLScreen();

		initHUDText();

		loadUnitAndSpec();

		loadCitiesNames();

		/* Need to be after loadUnitAndSpec */
		m_players.init(RealEngine2D::ResourceManager::getFile(e_Files::imagesPath)->getPath());

		initUI();

		try
		{
			m_mainMap.initMainMap(m_screen.camera);

			//RealEngine2D::Music music = m_screen.audioEngine.loadMusic("sounds/the_field_of_dreams.mp3");

			if (m_SaveReload->GETcurrentSave() != NO_CURRENT_SAVE_SELECTED)
			{
				m_SaveReload->reload(*this);
			}
			else
			{
				newGame();
			}

		}
		catch (const std::string& msg)
		{
			App::logfileconsole("[ERROR]___: GamePlayScreen::onEntry : " + msg);
			return false;
		}

		m_isInitialize = true;
	}
	return true;
}

void GamePlayScreen::onExit()
{

}


/*--------------------------------------------------------------------START-CYCLE----------------------------------------------------------------------------*/

/* ----------------------------------------------------------------------------------- */
/* NAME : update																	   */
/* ROLE : Call each cycle 															   */
/* ROLE : Update input from SDL and game / Update GUI input							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
void GamePlayScreen::update()
{
	SDL_Event ev{};

	/* Get Input */
	while (SDL_PollEvent(&ev))
	{
		m_game->onSDLEvent(ev);
		inputSDL(ev);
		mouseClick(ev);
		m_screen.m_gui.onSDLEvent(ev, m_game->getInputManager());
	}

	/* Process Input */
	actionByKey();
	moveCameraByDeltaTime();
}

/* ----------------------------------------------------------------------------------- */
/* NAME : draw																		   */
/* ROLE : Call each cycle 															   */
/* ROLE : Update picture from game and GUI 											   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
void GamePlayScreen::draw()
{
	m_screen.camera.update();
	m_screen.cameraHUD.update();

	drawGame();
}

/*---------------------------------------------------------------------END-CYCLE---------------------------------------------------------------------------------*/


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : loadFile																	   */
/* ROLE : 										   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void GamePlayScreen::loadFile()
{
	App::logfileconsole("[INFO]___: [START] : initMain");

	tinyxml2::XMLDocument config{};
	config.LoadFile(RealEngine2D::ResourceManager::getFile(e_Files::mainMap)->getPath().c_str());
	unsigned int tmp{ 0 };

	if (config.ErrorID() == 0)
	{
		const char* root{ "Config" };


		const char
			* s_Map{ "Map" },
				* s_TileSize{ "TileSize" },
				* s_MapSizeX{ "MapSizeX" },
				* s_MapSizeY{ "MapSizeY" };


		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_TileSize)->QueryUnsignedText(&tmp);
		m_mainMap.SETtileSize(tmp);
		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_MapSizeX)->QueryUnsignedText(&tmp);
		m_mainMap.SETmapSizePixX(tmp);
		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_MapSizeY)->QueryUnsignedText(&tmp);
		m_mainMap.SETmapSizePixY(tmp);
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + (std::string)configFilePath);
	}

	App::logfileconsole("[INFO]___: [END] : initMain");
}



/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initStructs																   */
/* ROLE : Initialisation des données par défaut des structures						   */
/* INPUT : struct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void GamePlayScreen::initStructsNULL()
{
	/* ### Mettre ici les cas d'inialisation des structures ### */

	/* *********************************************************
	 *					   sysinfo.var						   *
	 ********************************************************* */

	m_var.tempPlayerName = EMPTY_STRING;
	m_var.select = Select_Type::selectnothing;
	m_var.statescreen = State_Type::error;
	m_var.cinState = CinState_Type::cinNothing;

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
void GamePlayScreen::computeSize()
{
	m_mainMap.SETtoolBarSize
	(
		(unsigned int)std::ceil
		(
			(double)(m_game->getWindow().GETscreenWidth() / 8)
			/
			(double)m_mainMap.GETtileSize()
		)
	);
}


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initOpenGLScreen															   */
/* ROLE : Init m_screen.openGLScreen and m_mainMap									   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void GamePlayScreen::initOpenGLScreen()
{
	m_screen.camera.init(m_game->getWindow().GETscreenWidth(), m_game->getWindow().GETscreenHeight());
	m_screen.camera.SETposition(glm::vec2(m_game->getWindow().GETscreenWidth() / 2, m_game->getWindow().GETscreenHeight() / 2));
	m_screen.cameraHUD.init(m_game->getWindow().GETscreenWidth(), m_game->getWindow().GETscreenHeight());
	m_screen.cameraHUD.SETposition(glm::vec2(m_game->getWindow().GETscreenWidth() / 2, m_game->getWindow().GETscreenHeight() / 2));

	m_screen.spriteBatchHUDDynamic.init();
	m_screen.spriteBatchHUDStatic.init();

	m_screen.audioEngine.init();

	m_game->getInputManager().init(m_mainMap.GETtileSizePtr());

	m_screen.m_gui.init(RealEngine2D::ResourceManager::getFile(e_Files::GUIPath)->getPath());
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initHUDText																   */
/* ROLE : Init static Text in HUD													   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void GamePlayScreen::initHUDText()
{
	char buffer[256]{};

	m_screen.spriteBatchHUDStatic.begin();

	sprintf_s(buffer, "Civ_Rob_2.0 : version 0.23.10.0");
	RealEngine2D::ResourceManager::getSpriteFont()->draw
	(
		m_screen.spriteBatchHUDStatic,
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

	m_screen.spriteBatchHUDStatic.end();
}

void GamePlayScreen::initUI()
{
	m_screen.m_gui.loadScheme("AlfiskoSkin.scheme");
	m_screen.m_gui.loadScheme("TaharezLook.scheme");

	m_screen.m_gui.setFont("DejaVuSans-10");

	/* MainMenuButton */
	CEGUI::PushButton* mainMenuButton = static_cast<CEGUI::PushButton*>
		(m_screen.m_gui.createWidget(
			"AlfiskoSkin/Button",
			{ 0.0f, 0.0f, 0.1f, 0.05f },
			{ 0,0,0,0 },
			"TestButton"));

	mainMenuButton->setText("Main Menu");
	mainMenuButton->subscribeEvent
	(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GamePlayScreen::onExitClicked, this)
	);
	
	m_screen.m_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
	m_screen.m_gui.showMouseCursor();

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
void GamePlayScreen::loadUnitAndSpec()
{
	tinyxml2::XMLDocument texteFile{};
	
	texteFile.LoadFile(RealEngine2D::ResourceManager::getFile(e_Files::units)->getPath().c_str());

	const char* root("Root");

	const char* s_Unit("Unit"),
		* s_Name("Name"),
		* s_MovementType("MovementType"),
		* s_Life("Life"),
		* s_Atq("Atq"),
		* s_Def("Def"),
		* s_Mouvement("Mouvement"),
		* s_NumberOfAttack("NumberOfAttack"),
		* s_Level("Level"),
		* s_WorkToBuild("WorkToBuild"),
		* s_Maintenance("Maintenance");

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
		node->FirstChildElement(s_NumberOfAttack)->QueryIntText((int*)&currentUnit.numberOfAttack);
		node->FirstChildElement(s_Level)->QueryIntText((int*)&currentUnit.level);
		node->FirstChildElement(s_WorkToBuild)->QueryDoubleText((double*)&currentUnit.workToBuild);
		node->FirstChildElement(s_Maintenance)->QueryDoubleText((double*)&currentUnit.maintenance);

		m_players.GETvectUnitTemplate().push_back(currentUnit);

		node = node->NextSibling();
	}
}

void GamePlayScreen::loadCitiesNames()
{
	unsigned int nbcity{ 0 };
	std::string city{EMPTY_STRING}, dummy{ EMPTY_STRING };
	std::ifstream CITIENAME{ RealEngine2D::ResourceManager::getFile(e_Files::citiesNames)->getPath() };


	if (CITIENAME)
	{
		CITIENAME >> dummy;

		CITIENAME >> nbcity;
		m_players.GETvectCityName().resize(nbcity);

		for (auto& c : m_players.GETvectCityName())
		{
			CITIENAME >> c;
		}
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + RealEngine2D::ResourceManager::getFile(e_Files::citiesNames)->getPath());
	}
}

//----------------------------------------------------------GameLoop----------------------------------------------------------------//


void GamePlayScreen::moveCameraByDeltaTime()
{
	static Uint32 prevTicks{ SDL_GetTicks() };
	Uint32 frameTime{ 0 }, newTicks{ 0 };
	float totalDeltaTime{ 0.0f }, deltaTime{ 0.0f };

	newTicks = SDL_GetTicks();
	frameTime = newTicks - prevTicks;
	prevTicks = newTicks;
	totalDeltaTime = (float)frameTime / TARGET_FRAMETIME;
	int i{ 0 };

	while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS)
	{
		deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
		moveCamera(deltaTime);
		totalDeltaTime -= deltaTime;
		i++;
	}
}


void GamePlayScreen::drawGame()
{
	/* line for CEGUI because CEGUI doesn't do it, do not remove  */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Back */
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RealEngine2D::ResourceManager::getGLSLProgram().use();
	/* use GL_TEXTURE0 for 1 pipe; use GL_TEXTURE1/2/3 for multiple */
	glActiveTexture(GL_TEXTURE0);

	const GLint textureLocation
		= RealEngine2D::ResourceManager::getGLSLProgram().getUnitformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	/* --- camera --- */
	/* GL - get parameter P */
	const GLint pLocation
		= RealEngine2D::ResourceManager::getGLSLProgram().getUnitformLocation("P");

	/* Copy camera matrix */
	glm::mat4 cameraMatrix = m_screen.camera.GETcameraMatrix();

	/*  */
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	/* --- Draw --- */
	m_mainMap.drawMap(m_screen.camera, m_game->getWindow());

	m_players.isAUnitSelected();
	m_players.drawUnit(m_mainMap, m_screen.camera);
	m_players.drawCity(m_mainMap, m_screen.camera, RealEngine2D::ResourceManager::getSpriteFont());

	/* --- Render --- */
	m_mainMap.renderMap();
	m_players.renderUnit();
	m_players.renderCity();


	drawHUD();

	/* --- GL unbind --- */
	glBindTexture(GL_TEXTURE_2D, 0);
	RealEngine2D::ResourceManager::getGLSLProgram().unuse();

	/* --- Draw UI --- */
	m_screen.m_gui.draw();
}

void GamePlayScreen::drawHUD()
{
	/* camera HUD */
	const GLint pLocation
		= RealEngine2D::ResourceManager::getGLSLProgram().getUnitformLocation("P");
	glm::mat4 cameraMatrix = m_screen.cameraHUD.GETcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];


	m_screen.spriteBatchHUDDynamic.begin();

	sprintf_s(buffer, "FPS %f", m_game->getFPS());
	RealEngine2D::ResourceManager::getSpriteFont()->draw
	(
		m_screen.spriteBatchHUDDynamic,
		buffer,
		glm::vec2(0.0f, 32.0f), // offset pos
		glm::vec2(0.32f), // size
		0.0f,
		RealEngine2D::COLOR_WHITE
	);



	sprintf_s(buffer, "Nb Turn %d", m_nextTurn.GETnbTurn());
	RealEngine2D::ResourceManager::getSpriteFont()->draw
	(
		m_screen.spriteBatchHUDDynamic,
		buffer,
		glm::vec2(0.0f, 64.0f), // offset pos
		glm::vec2(0.32f), // size
		0.0f,
		RealEngine2D::COLOR_BLUE
	);

#ifdef _DEBUG

	sprintf_s(buffer, "Scale %lf", m_screen.camera.GETscale());
	RealEngine2D::ResourceManager::getSpriteFont()->draw
	(
		m_screen.spriteBatchHUDDynamic,
		buffer,
		glm::vec2(0.0f, 500.0f), // offset pos
		glm::vec2(0.32f), // size
		0.0f,
		RealEngine2D::COLOR_RED
	);

#endif // _DEBUG

	

	for (auto& l : m_screen.m_widgetLabels) 
		l.draw(m_screen.spriteBatchHUDDynamic, *RealEngine2D::ResourceManager::getSpriteFont(), m_game->getWindow());


	m_screen.spriteBatchHUDDynamic.end();

	m_screen.spriteBatchHUDDynamic.renderBatch();
	m_screen.spriteBatchHUDStatic.renderBatch();
}


bool GamePlayScreen::onPlayerButtonClicked(const CEGUI::EventArgs& /* e */)
{
	for (size_t i(0); i < m_screen.m_vectPlayerRadioButton.size(); i++)
	{
		if (m_screen.m_vectPlayerRadioButton[i]->isSelected())
		{
			if (i != m_players.GETselectedPlayerId())
			{
				/* Reset if needed SHOW for the unit previously selected */
				if (m_players.GETselectedPlayerId() != NO_PLAYER_SELECTED && m_players.GETselectedPlayerPtr() != nullptr)
				{			
					if (m_players.GETselectedPlayerPtr()->GETselectedUnit() != NO_UNIT_SELECTED)
					{
						m_players.GETselectedPlayerPtr()->GETSelectedUnitPtr()->SETshow(true);
						m_players.SETneedToUpdateDrawUnit(true);

						m_players.GETselectedPlayerPtr()->SETselectedUnit(NO_UNIT_SELECTED);
					}
				}

				/* Select player i */
				m_players.SETselectedPlayerId((int)i);
				m_players.SETselectedPlayerPtr(m_players.GETvectPlayer()[i]);
			}
			
			return true;
		}
	}
	return true;
}

bool GamePlayScreen::onExitClicked(const CEGUI::EventArgs& /* e */)
{
	SaveReload::save(*this);

	m_currentState = RealEngine2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}



