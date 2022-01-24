/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.0.0
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

#include "CityScreen.h"
#include "ScreenIndices.h"

#include "App.h"

CityScreen::CityScreen
(
	File* file,
	SaveReload* saveReload,
	Players* players
)
:
RealEngine2D::IGameScreen(),
m_nextScreenIndexMenu(INIT_SCREEN_INDEX),
m_gui(),
m_file(file),
m_SaveReload(saveReload),
m_players(players),
m_isInitialize(false)
{
	build();
}

CityScreen::~CityScreen()
{
	destroy();
}

int CityScreen::getNextScreenIndex()const
{
	return INIT_SCREEN_INDEX;
}
int CityScreen::getPreviousScreenIndex()const
{
	return m_nextScreenIndexMenu;
}

void CityScreen::build()
{
	m_screenIndex = CITY_SCREEN_INDEX;
	m_buttonBuild.clear();
}

void CityScreen::destroy()
{
	m_gui.destroy();
}

bool CityScreen::onEntry()
{
	if (!m_isInitialize)
	{
		m_gui.init(m_file->GUIPath);

		m_gui.loadScheme("AlfiskoSkin.scheme");

		m_gui.setFont("DejaVuSans-10");


		CEGUI::PushButton* returnToMap = static_cast<CEGUI::PushButton*>
			(m_gui.createWidget(
				"AlfiskoSkin/Button",
				{ 0.0f, 0.0f, 0.1f, 0.05f },
				RealEngine2D::NOT_BY_PERCENT,
				"ReturnToMap"));

		returnToMap->setText("Return To Map");
		returnToMap->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&CityScreen::onReturnToMapClicked, this)
		);



		const float CITY_IHM_BUILD_DIPSLAY_POS_X{ 0.35f };
		const float CITY_IHM_BUILD_DIPSLAY_POS_Y{ 0.05f };
		const float CITY_IHM_BUILD_DIPSLAY_DELTA_Y{ 0.025f };

		for (const auto p : m_players->GETvectUnitTemplate())
		{
			m_buttonBuild.push_back
			(
				{
					static_cast<CEGUI::PushButton*>
					(
						m_gui.createWidget
						(
							"AlfiskoSkin/Button",
							{
								CITY_IHM_BUILD_DIPSLAY_POS_X,
								CITY_IHM_BUILD_DIPSLAY_POS_Y + CITY_IHM_BUILD_DIPSLAY_DELTA_Y * m_buttonBuild.size(),
								0.0f,
								CITY_IHM_BUILD_DIPSLAY_DELTA_Y / 2.0f
							},
							RealEngine2D::NOT_BY_PERCENT,
							p.name
						)
					),
					{
						p.name,
						build_Type::unit,
						p.workToBuild
					}
				}
			);
			m_buttonBuild.back().button
				->setText(p.name + " : "
					+ std::to_string(p.life)
					+ "/"
					+ std::to_string(p.atq)
					+ "/"
					+ std::to_string(p.def)
					+ "/"
					+ std::to_string(p.movement)
					+ "/"
					+ std::to_string(p.maintenance)
				);
			m_buttonBuild.back().button->subscribeEvent
			(
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber(&CityScreen::onBuildQueueClicked, this)
			);

		}

		m_isInitialize = true;
	}
	
	return true;
}

void CityScreen::onExit()
{
	/* Do nothing */
}


void CityScreen::draw()
{
	/* line for CEGUI because CEGUI doesn't do it, do not remove  */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Back */
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_gui.draw();
}


void CityScreen::update()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev))
	{
		m_gui.onSDLEvent(ev, m_game->getInputManager());
		m_game->onSDLEvent(ev);
	}
}


bool CityScreen::onBuildQueueClicked(const CEGUI::EventArgs& /* e */)
{
	for (auto &button : m_buttonBuild)
	{
		if (button.button->isPushed())
		{
			m_players->GETvectPlayer()[m_players->GETselectedPlayer()]
				->GETtabCity()[m_players->GETvectPlayer()[m_players->GETselectedPlayer()]->GETselectedCity()]
					->addBuildToQueue(button);
			break;
		}
	}
	return true;
}

bool CityScreen::onReturnToMapClicked(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = GAMEPLAY_SCREEN_INDEX;
	m_currentState = RealEngine2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}