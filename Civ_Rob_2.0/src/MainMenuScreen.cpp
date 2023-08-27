/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.4.0
	file version : 1.10

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

#include "MainMenuScreen.h"
#include "ScreenIndices.h"

#include "App.h"

#include <RealEngine2D/src/ResourceManager.h> 
#include <RealEngine2D/src/ErrorLog.h> 
#include <RealEngine2D/src/SpriteFont.h> 


MainMenuScreen::MainMenuScreen
(
)
: 
RealEngine2D::IGameScreen(),
m_nextScreenIndexMenu(RealEngine2D::SCREEN_INDEX::INIT),
m_spriteBatchHUDStatic(),
m_gui(),
m_isInitialize(false)
{
	build();
	RealEngine2D::ErrorLog::logEvent("[INFO]___: build MainMenuScreen");
}

MainMenuScreen::~MainMenuScreen()
{
	destroy();
}

int MainMenuScreen::getNextScreenIndex()const
{
	return m_nextScreenIndexMenu;
}
int MainMenuScreen::getPreviousScreenIndex()const
{
	return RealEngine2D::SCREEN_INDEX::INIT;
}

void MainMenuScreen::build()
{
	m_screenIndex = SCREEN_INDEX::MAINMENU;
}

void MainMenuScreen::destroy()
{
	m_gui.destroy();
}

bool MainMenuScreen::onEntry()
{
	if (!m_isInitialize)
	{
		RealEngine2D::ErrorLog::logEvent("[INFO]___: Init MainMenuScreen");

		m_cameraHUD.init(m_game->getWindow().GETscreenWidth(), m_game->getWindow().GETscreenHeight());
		m_cameraHUD.SETposition(glm::vec2(m_game->getWindow().GETscreenWidth() / 2, m_game->getWindow().GETscreenHeight() / 2));


		m_spriteBatchHUDStatic.init();

		m_gui.init(RealEngine2D::ResourceManager::getFile(e_Files::GUIPath)->getPath());

		m_gui.loadScheme("AlfiskoSkin.scheme");

		m_gui.setFont("DejaVuSans-10");



		const float xC(0.45f), xL(0.1f), yL(0.05f), yDelta(0.1f);
		float yC(0.4f);

		CEGUI::PushButton* newGame = static_cast<CEGUI::PushButton*>
			(m_gui.createWidget(
				"AlfiskoSkin/Button",
				{ xC, yC, xL, yL },
				RealEngine2D::NOT_BY_PERCENT,
				"newGame"));

		newGame->setText("New Game");
		newGame->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&MainMenuScreen::onNewGameClicked, this)
		);

		CEGUI::PushButton* reloadButton = static_cast<CEGUI::PushButton*>
			(m_gui.createWidget(
				"AlfiskoSkin/Button",
				{ xC, yC += yDelta, xL, yL },
				RealEngine2D::NOT_BY_PERCENT,
				"Reload"));

		reloadButton->setText("Reload");
		reloadButton->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&MainMenuScreen::onReloadClicked, this)
		);

		CEGUI::PushButton* optionButton = static_cast<CEGUI::PushButton*>
			(m_gui.createWidget(
				"AlfiskoSkin/Button",
				{ xC, yC += yDelta, xL, yL },
				RealEngine2D::NOT_BY_PERCENT,
				"Option"));

		optionButton->setText("Option");
		optionButton->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&MainMenuScreen::onOptionClicked, this)
		);

		CEGUI::PushButton* quitGame = static_cast<CEGUI::PushButton*>
			(m_gui.createWidget(
				"AlfiskoSkin/Button",
				{ xC, yC += yDelta, xL, yL },
				RealEngine2D::NOT_BY_PERCENT,
				"QuitGame"));

		quitGame->setText("Quit Game");
		quitGame->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&MainMenuScreen::onExitClicked, this)
		);


		m_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
		m_gui.showMouseCursor();

		/* HIDE normal mouse cursor */
		SDL_ShowCursor(0);

		initHUD();

		m_isInitialize = true;
	}
	

	return true;
}

void MainMenuScreen::initHUD()
{
	m_spriteBatchHUDStatic.begin();


	MapTexts mapTexts;
	RealEngine2D::ResourceManager::getTextFromFile
	(
		e_Files::texts,
		mapTexts
	);

	for (const auto& text: mapTexts)
	{
		RealEngine2D::ResourceManager::getSpriteFont()->draw
		(
			m_spriteBatchHUDStatic,
			text.second.text.c_str(),
			glm::vec2
			(
				m_game->getWindow().getWidthPositionScaleToWindow(text.second.x),
				m_game->getWindow().getHeightPositionScaleToWindow(text.second.y)
			), // offset pos
			glm::vec2(RealEngine2D::SpriteFont::getScaleFontToScreen(text.second.size)), // size
			text.second.alpha,
			text.second.color,
			text.second.justification
		);
	}

	
	
	m_spriteBatchHUDStatic.end();
}


void MainMenuScreen::onExit()
{
	/* Do nothing */
}


//----------------------------------------------------------GameLoop----------------------------------------------------------------//



void MainMenuScreen::draw()
{
	m_cameraHUD.update();

	/* line for CEGUI because CEGUI doesn't do it, do not remove  */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Back */
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RealEngine2D::ResourceManager::getGLSLProgram().use();

	/* use GL_TEXTURE0 for 1 pipe; use GL_TEXTURE1/2/3 for multiple */
	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = RealEngine2D::ResourceManager::getGLSLProgram().getUnitformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	/* --- camera --- */
	/* GL - get parameter P */
	const GLint pLocation
		= RealEngine2D::ResourceManager::getGLSLProgram().getUnitformLocation("P");

	/* Copy camera matrix */
	glm::mat4 cameraMatrix = m_cameraHUD.GETcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_spriteBatchHUDStatic.renderBatch();

	/* --- GL unbind --- */
	glBindTexture(GL_TEXTURE_2D, 0);

	RealEngine2D::ResourceManager::getGLSLProgram().unuse();

	m_gui.draw();
}


void MainMenuScreen::update()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev))
	{
		m_gui.onSDLEvent(ev, m_game->getInputManager());
		m_game->onSDLEvent(ev);
	}
}


bool MainMenuScreen::onNewGameClicked(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = SCREEN_INDEX::NEWGAME;
	m_currentState = RealEngine2D::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreen::onReloadClicked(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = SCREEN_INDEX::RELOAD;
	m_currentState = RealEngine2D::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreen::onOptionClicked(const CEGUI::EventArgs& /* e */)
{
	return true;
}

bool MainMenuScreen::onExitClicked(const CEGUI::EventArgs& /* e */)
{
	m_currentState = RealEngine2D::ScreenState::EXIT_APPLICATION;
	return true;
}
