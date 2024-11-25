/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2024 (robin.sauter@orange.fr)

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

#include "LogSentences.h"
#include "ScreenIndices.h"

#include "App.h"
#include "SaveReload.h"
#include <string>

#include <R2D/src/ResourceManager.h> 
#include <R2D/src/Log.h> 

namespace IHM_SAVE_BUTTON
{
	constexpr unsigned int MAX_VISISBLE = 10;
}

ReloadMenuScreen::ReloadMenuScreen
(
	SaveReloadPtrT SaveReload
)
:
R2D::IGameScreen(),
R2D::CScreen(),
m_nextScreenIndexMenu(R2D::SCREEN_INDEX::INIT),
m_vectSavesRadioButton(),
m_widgetLabels(),
m_SaveReload(SaveReload),
m_isInitialize(false)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::RELOAD_MENU, logS::WHAT::CONSTRUCTOR, logS::DATA::SCREEN);
	build();
}

ReloadMenuScreen::~ReloadMenuScreen()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::RELOAD_MENU, logS::WHAT::DESTRUCTOR, logS::DATA::SCREEN);
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
	end();

	m_widgetLabels.clear();
}

bool ReloadMenuScreen::onEntry()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::RELOAD_MENU, logS::WHAT::ON_ENTRY, logS::DATA::START);
	if (!m_isInitialize)
	{
		init(m_game->getWindow().GETscreenWidth(), m_game->getWindow().GETscreenHeight());

		m_isInitialize = true;
	}
	LOG(R2D::LogLevelType::info, 0, logS::WHO::RELOAD_MENU, logS::WHAT::ON_ENTRY, logS::DATA::END);
	return true;
}

void ReloadMenuScreen::onExit()
{
	/* Do nothing */
}

void ReloadMenuScreen::doInitOptimizeTexture()
{
	/* Do nothing */
}

void ReloadMenuScreen::doInitUI()
{
	buttonDisplay();
	radioButtonDisplay();
}

void ReloadMenuScreen::buttonDisplay()
{
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
}

void ReloadMenuScreen::radioButtonDisplay()
{
	float X_POS = 0.1f;
	float Y_POS = 0.20f;
	constexpr float DIMS_PIXELS = 20.0f;
	constexpr float PADDING = 0.035f;
	constexpr float TEXT_SCALE = 0.6f;
	constexpr int GROUP_ID = 2;

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
}

void ReloadMenuScreen::updateRadioButtonPosition()
{
	float X_POS = 0.1f;
	float Y_POS = 0.20f;
	constexpr float PADDING = 0.035f;
	constexpr float TEXT_SCALE = 0.6f;

	for (size_t i(0); i < m_vectSavesRadioButton.size(); i++)
	{
		m_vectSavesRadioButton[i]->setPosition
			(CEGUI::UVector2
				(
					CEGUI::UDim(X_POS, 0.0f),
					CEGUI::UDim(Y_POS += PADDING, 0.0f)
				)
			);

		m_widgetLabels[i] = R2D::WidgetLabel(
			m_vectSavesRadioButton[i],
			"Save " + std::to_string(m_SaveReload->GETtabSave()[i]),
			TEXT_SCALE);

	}
}

void ReloadMenuScreen::doInitHUDText()
{

}

//----------------------------------------------------------GameLoop----------------------------------------------------------------//

void ReloadMenuScreen::draw()
{
	drawAll();
}

void ReloadMenuScreen::doDrawAll()
{
	for (size_t i(0); i < m_vectSavesRadioButton.size(); i++)
	{
		if (m_vectSavesRadioButton[i]->isVisible())
		{
			m_widgetLabels[i].draw(m_spriteBatchHUDDynamic, *R2D::ResourceManager::getSpriteFont(), m_game->getWindow());
		}
	}
}

void ReloadMenuScreen::update()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev))
	{
		m_game->onSDLEvent(ev);
		updateInputManager(ev, m_game->getInputManager());
	}
}

void ReloadMenuScreen::updateVisibilityIfSaveSelected()
{
	if (m_SaveReload->isSelectCurrentSave())
	{
		(static_cast<CEGUI::PushButton*>(m_gui.getWidget("LoadSelectedSave")))->show();
		(static_cast<CEGUI::PushButton*>(m_gui.getWidget("removeSelectedSaveButton")))->show();
	}
	else
	{
		(static_cast<CEGUI::PushButton*>(m_gui.getWidget("LoadSelectedSave")))->hide();
		(static_cast<CEGUI::PushButton*>(m_gui.getWidget("removeSelectedSaveButton")))->hide();
	}
	
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

			updateVisibilityIfSaveSelected();

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

			m_gui.destroyWidget(button);

			m_vectSavesRadioButton.erase(m_vectSavesRadioButton.begin() + index);
			m_widgetLabels.erase(m_widgetLabels.begin() + index);

			updateRadioButtonPosition();

			updateVisibilityIfSaveSelected();
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
		m_gui.destroyWidget(button);
	}
	m_vectSavesRadioButton.clear();
	m_widgetLabels.clear();
	
	m_SaveReload->clearSave();

	updateVisibilityIfSaveSelected();

	return true;
}

bool ReloadMenuScreen::onExitClicked(const CEGUI::EventArgs& /* e */)
{
	m_currentState = R2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}