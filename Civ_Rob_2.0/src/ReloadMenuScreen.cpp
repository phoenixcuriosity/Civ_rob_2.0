/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.14.4
	file version : 1.5

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

#include "ReloadMenuScreen.h"

#include "ScreenIndices.h"

#include "App.h"
#include "SaveReload.h"
#include <string>

ReloadMenuScreen::ReloadMenuScreen
(
	File* file,
	SaveReload* SaveReload
)
:
RealEngine2D::IGameScreen(),
m_nextScreenIndexMenu(INIT_SCREEN_INDEX),
m_gLSLProgram(),
m_cameraHUD(),
m_gui(),
m_vectSavesRadioButton(),
m_widgetLabels(),
m_spriteFont(nullptr),
m_spriteBatchHUDDynamic(),
m_file(file),
m_SaveReload(SaveReload)
{
	m_screenIndex = MAINMENU_SCREEN_INDEX;
}

ReloadMenuScreen::~ReloadMenuScreen()
{
	m_gui.destroy();

	m_widgetLabels.clear();

	m_spriteFont.reset();
}

int ReloadMenuScreen::getNextScreenIndex()const
{
	return INIT_SCREEN_INDEX;
}
int ReloadMenuScreen::getPreviousScreenIndex()const
{
	return MAINMENU_SCREEN_INDEX;
}

void ReloadMenuScreen::build()
{

}
void ReloadMenuScreen::destroy()
{
	m_gui.destroy();
}

bool ReloadMenuScreen::onEntry()
{
	initOpenGLScreen();
	initShaders();
	initHUD();

	return true;
}



/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initOpenGLScreen															   */
/* ROLE : Init m_screen.openGLScreen and m_mainMap									   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void ReloadMenuScreen::initOpenGLScreen()
{
	m_cameraHUD.init(m_game->getWindow().GETscreenWidth(), m_game->getWindow().GETscreenHeight());
	m_cameraHUD.SETposition(glm::vec2(m_game->getWindow().GETscreenWidth() / 2, m_game->getWindow().GETscreenHeight() / 2));

	m_spriteBatchHUDDynamic.init();
	m_spriteFont = std::make_unique<RealEngine2D::SpriteFont>("times.ttf", 64);
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
void ReloadMenuScreen::initShaders()
{
	m_gLSLProgram.compileShaders(m_file->colorShadingVert, m_file->colorShadingFrag);
	m_gLSLProgram.addAttribut("vertexPosition");
	m_gLSLProgram.addAttribut("vertexColor");
	m_gLSLProgram.addAttribut("vertexUV");
	m_gLSLProgram.linkShaders();
}

void ReloadMenuScreen::initHUD()
{
	m_gui.init(m_file->GUIPath);

	m_gui.loadScheme("AlfiskoSkin.scheme");
	m_gui.loadScheme("TaharezLook.scheme");

	m_gui.setFont("DejaVuSans-10");

	CEGUI::PushButton* mainMenuButton = static_cast<CEGUI::PushButton*>
		(m_gui.createWidget(
			"AlfiskoSkin/Button",
			{ 0.0f, 0.0f, 0.1f, 0.05f },
			{ 0,0,0,0 },
			"TestButton"));

	mainMenuButton->setText("Main Menu");
	mainMenuButton->subscribeEvent
	(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&ReloadMenuScreen::onExitClicked, this)
	);


	CEGUI::PushButton* clearSavesButton = static_cast<CEGUI::PushButton*>
		(m_gui.createWidget(
			"AlfiskoSkin/Button",
			{ 0.45f, 0.5f, 0.1f, 0.05f },
			{ 0,0,0,0 },
			"ClearSaves"));

	clearSavesButton->setText("Clear Saves");
	clearSavesButton->subscribeEvent
	(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&ReloadMenuScreen::onClearSavesCliked, this)
	);


	float X_POS = 0.1f;
	float Y_POS = 0.20f;
	const float DIMS_PIXELS = 20.0f;
	const float PADDING = 0.035f;
	const float TEXT_SCALE = 0.6f;
	const int GROUP_ID = 2;

	m_vectSavesRadioButton.clear();
	m_widgetLabels.clear();
	m_vectSavesRadioButton.resize(m_SaveReload->GETtabSave().size());
	m_widgetLabels.resize(m_vectSavesRadioButton.size());
	for (size_t i(0); i < m_vectSavesRadioButton.size(); i++)
	{
		m_vectSavesRadioButton[i]
			= static_cast<CEGUI::RadioButton*>
			(m_gui.createWidget(
				"TaharezLook/RadioButton",
				glm::vec4(X_POS, Y_POS += PADDING, 0.0f, 0.0f),
				glm::vec4(0.0f, 0.0f, DIMS_PIXELS, DIMS_PIXELS),
				"Save " + std::to_string(m_SaveReload->GETtabSave()[i])));

		m_vectSavesRadioButton[i]->setSelected(false);

		m_vectSavesRadioButton[i]->subscribeEvent
		(CEGUI::RadioButton::EventMouseClick,
			CEGUI::Event::Subscriber(&ReloadMenuScreen::onOneSaveCliked, this));

		m_vectSavesRadioButton[i]->setGroupID(GROUP_ID);

		if (MAX_SAVE_BUTTON_VISISBLE > i)
		{
			m_vectSavesRadioButton[i]->setVisible(true);
		}
		else
		{
			m_vectSavesRadioButton[i]->setVisible(false);
		}

		m_widgetLabels[i] = RealEngine2D::WidgetLabel(
			m_vectSavesRadioButton[i],
			"Save " + std::to_string(m_SaveReload->GETtabSave()[i]),
			TEXT_SCALE);

	}



	m_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
	m_gui.showMouseCursor();

	/* HIDE normal mouse cursor */
	SDL_ShowCursor(0);
}


//----------------------------------------------------------GameLoop----------------------------------------------------------------//



void ReloadMenuScreen::draw()
{
	m_cameraHUD.update();


	/* line for CEGUI because CEGUI doesn't do it, do not remove  */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Back */
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_gLSLProgram.use();
	/* use GL_TEXTURE0 for 1 pipe; use GL_TEXTURE1/2/3 for multiple */
	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = m_gLSLProgram.getUnitformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	/* camera */
	GLint pLocation = m_gLSLProgram.getUnitformLocation("P");
	glm::mat4 cameraMatrix = m_cameraHUD.GETcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_spriteBatchHUDDynamic.begin();
	
	unsigned int butDrawn(0);
	for (size_t i(0); i < m_vectSavesRadioButton.size(); i++)
	{
		if (m_vectSavesRadioButton[i]->isVisible())
		{
			butDrawn++;
			m_widgetLabels[i].draw(m_spriteBatchHUDDynamic, *m_spriteFont, m_game->getWindow());
		}
	}

	m_spriteBatchHUDDynamic.end();

	m_spriteBatchHUDDynamic.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	m_gLSLProgram.unuse();

	m_gui.draw();
}


void ReloadMenuScreen::update()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		m_game->onSDLEvent(ev);
		m_gui.onSDLEvent(ev, m_game->getInputManager());
	}
}



void ReloadMenuScreen::onExit()
{
	destroy();
}

bool ReloadMenuScreen::onOneSaveCliked(const CEGUI::EventArgs& /* e */)
{
	for (size_t i(0); i < m_vectSavesRadioButton.size(); i++)
	{
		if (m_vectSavesRadioButton[i]->isPushed())
		{
			m_SaveReload->SETcurrentSave((int)i);
			return true;
		}
	}
	return true;
}

bool ReloadMenuScreen::onClearSavesCliked(const CEGUI::EventArgs& /* e */)
{
	m_SaveReload->clearSave(m_file->saveInfo);
	return true;
}

bool ReloadMenuScreen::onExitClicked(const CEGUI::EventArgs& /* e */)
{
	m_currentState = RealEngine2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}