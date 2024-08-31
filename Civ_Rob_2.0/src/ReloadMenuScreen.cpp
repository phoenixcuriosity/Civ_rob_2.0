/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.1.0
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

#include "ReloadMenuScreen.h"

#include "ScreenIndices.h"

#include "App.h"
#include "SaveReload.h"
#include <string>

#include <R2D/src/ResourceManager.h> 

namespace IHM_SAVE_BUTTON
{
	const unsigned int MAX_VISISBLE = 10;
}

ReloadMenuScreen::ReloadMenuScreen
(
	SaveReload* SaveReload
)
:
R2D::IGameScreen(),
m_nextScreenIndexMenu(R2D::SCREEN_INDEX::INIT),
m_cameraHUD(),
m_gui(),
m_vectSavesRadioButton(),
m_widgetLabels(),
m_spriteBatchHUDDynamic(),
m_SaveReload(SaveReload),
m_isInitialize(false)
{
	build();
}

ReloadMenuScreen::~ReloadMenuScreen()
{
	destroy();
}

int ReloadMenuScreen::getNextScreenIndex()const
{
	return m_nextScreenIndexMenu;
}
int ReloadMenuScreen::getPreviousScreenIndex()const
{
	return SCREEN_INDEX::MAINMENU;
}

void ReloadMenuScreen::build()
{
	m_screenIndex = SCREEN_INDEX::MAINMENU;
}

void ReloadMenuScreen::destroy()
{
	m_gui.destroy();

	m_widgetLabels.clear();
}

bool ReloadMenuScreen::onEntry()
{
	if (!m_isInitialize)
	{
		initOpenGLScreen();
		initHUD();

		m_isInitialize = true;
	}

	return true;
}

void ReloadMenuScreen::onExit()
{
	/* Do nothing */
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
}

void ReloadMenuScreen::initHUD()
{

	m_gui.init(R2D::ResourceManager::getFile(R2D::e_Files::GUIPath)->getPath());

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


	CEGUI::PushButton* loadSelectedSave = static_cast<CEGUI::PushButton*>
		(m_gui.createWidget(
			"AlfiskoSkin/Button",
			{ 0.45f, 0.55f, 0.2f, 0.05f },
			{ 0,0,0,0 },
			"LoadSelectedSave"));

	loadSelectedSave->setText("Load Selected Save");
	loadSelectedSave->subscribeEvent
	(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&ReloadMenuScreen::onLoadSave, this)
	);
	loadSelectedSave->hide();

	CEGUI::PushButton* removeSelectedSaveButton = static_cast<CEGUI::PushButton*>
		(m_gui.createWidget(
			"AlfiskoSkin/Button",
			{ 0.45f, 0.5f, 0.2f, 0.05f },
			{ 0,0,0,0 },
			"removeSelectedSaveButton"));

	removeSelectedSaveButton->setText("Remove Selected Save");
	removeSelectedSaveButton->subscribeEvent
	(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&ReloadMenuScreen::onClearASaveCliked, this)
	);
	removeSelectedSaveButton->hide();

	CEGUI::PushButton* clearSavesButton = static_cast<CEGUI::PushButton*>
		(m_gui.createWidget(
			"AlfiskoSkin/Button",
			{ 0.45f, 0.45f, 0.1f, 0.05f },
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

		if (IHM_SAVE_BUTTON::MAX_VISISBLE > i)
		{
			m_vectSavesRadioButton[i]->setVisible(true);
		}
		else
		{
			m_vectSavesRadioButton[i]->setVisible(false);
		}

		m_widgetLabels[i] = R2D::WidgetLabel(
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

	R2D::ResourceManager::getGLSLProgram().use();
	/* use GL_TEXTURE0 for 1 pipe; use GL_TEXTURE1/2/3 for multiple */
	glActiveTexture(GL_TEXTURE0);

	const GLint textureLocation =
		R2D::ResourceManager::getGLSLProgram().getUnitformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	/* camera */
	const GLint pLocation
		= R2D::ResourceManager::getGLSLProgram().getUnitformLocation("P");
	glm::mat4 cameraMatrix = m_cameraHUD.GETcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_spriteBatchHUDDynamic.begin();
	
	for (size_t i(0); i < m_vectSavesRadioButton.size(); i++)
	{
		if (m_vectSavesRadioButton[i]->isVisible())
		{
			m_widgetLabels[i].draw(m_spriteBatchHUDDynamic, *R2D::ResourceManager::getSpriteFont(), m_game->getWindow());
		}
	}

	m_spriteBatchHUDDynamic.end();

	m_spriteBatchHUDDynamic.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	R2D::ResourceManager::getGLSLProgram().unuse();

	m_gui.draw();
}


void ReloadMenuScreen::update()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev))
	{
		m_game->onSDLEvent(ev);
		m_gui.onSDLEvent(ev, m_game->getInputManager());
	}
}

void ReloadMenuScreen::showIfSaveSelected()
{
	(static_cast<CEGUI::PushButton*>(m_gui.getWidget("LoadSelectedSave")))->show();
	(static_cast<CEGUI::PushButton*>(m_gui.getWidget("removeSelectedSaveButton")))->show();
}

void ReloadMenuScreen::hideIfSaveSelected()
{
	(static_cast<CEGUI::PushButton*>(m_gui.getWidget("LoadSelectedSave")))->hide();
	(static_cast<CEGUI::PushButton*>(m_gui.getWidget("removeSelectedSaveButton")))->hide();
}


bool ReloadMenuScreen::onOneSaveCliked(const CEGUI::EventArgs& /* e */)
{
	for (size_t i(0); i < m_vectSavesRadioButton.size(); i++)
	{
		if	(m_vectSavesRadioButton[i]->isSelected())
		{	
			std::string dummy(m_vectSavesRadioButton[i]->getName().c_str());
			/* erase "Save ", keep after the space */
			dummy.erase(0, 5);

			m_SaveReload->SETcurrentSave((int)std::stoul(dummy));
			R2D::ResourceManager::modifyFilePath(R2D::e_Files::saveMaps, "save/" + dummy + "/saveMaps.txt");
			R2D::ResourceManager::modifyFilePath(R2D::e_Files::savePlayers, "save/" + dummy + "/savePlayers.xml");

			showIfSaveSelected();

			return true;
		}
	}
	return true;
}

bool ReloadMenuScreen::onLoadSave(const CEGUI::EventArgs& /* e */)
{
	if (m_SaveReload->GETcurrentSave() != SELECTION::NO_CURRENT_SAVE_SELECTED)
	{
		m_nextScreenIndexMenu = SCREEN_INDEX::GAMEPLAY;
		m_currentState = R2D::ScreenState::CHANGE_NEXT;
	}
	return true;
}

bool ReloadMenuScreen::onClearASaveCliked(const CEGUI::EventArgs& /* e */)
{
	size_t index{ 0 };
	for (auto& button : m_vectSavesRadioButton)
	{
		if (button->isSelected())
		{
			m_SaveReload->removeSave();
			button->destroy();
			break;
		};
		index++;
	}
	return true;
}

bool ReloadMenuScreen::onClearSavesCliked(const CEGUI::EventArgs& /* e */)
{
	/* Remove saves from GUI */
	for (auto& button : m_vectSavesRadioButton)
	{
		button->destroy();
	}
	m_vectSavesRadioButton.clear();
	m_widgetLabels.clear();
	
	m_SaveReload->clearSave();

	return true;
}

bool ReloadMenuScreen::onExitClicked(const CEGUI::EventArgs& /* e */)
{
	m_currentState = R2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}