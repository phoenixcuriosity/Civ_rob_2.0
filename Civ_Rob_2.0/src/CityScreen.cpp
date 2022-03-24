/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.1.0
	file version : 1.1

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

#include "Utility.h"

#include <RealEngine2D/src/ResourceManager.h>

const float CITY_IHM_BUILD_LIST_DIPSLAY_POS_X{ 0.75f };
const float CITY_IHM_BUILD_LIST_DIPSLAY_POS_Y{ 0.1f };
const float CITY_IHM_BUILD_LIST_DIPSLAY_DELTA_X{ 0.2f };
const float CITY_IHM_BUILD_LIST_DIPSLAY_DELTA_Y{ 0.026f };

const float CITY_IHM_BUILD_QUEUE_DIPSLAY_POS_X{ 0.8f };
const float CITY_IHM_BUILD_QUEUE_DIPSLAY_POS_Y{ 0.5f };
const float CITY_IHM_BUILD_QUEUE_DIPSLAY_DELTA_X{ 0.1f };
const float CITY_IHM_BUILD_QUEUE_DIPSLAY_DELTA_Y{ 0.026f };

const size_t OFFSET_INDEX_ERASE_BUTTON = 1;

/* ----------------------------------------------------------------------------------- */
/* NAME : CityScreen																   */
/* ROLE : CityScreen Constructor													   */
/* RETURNED VALUE : N/A																   */
/* ----------------------------------------------------------------------------------- */
CityScreen::CityScreen
(
	File* file,
	SaveReload* saveReload,
	Players* players,
	unsigned int* tileSize,
	Screen* screen
)
:
RealEngine2D::IGameScreen(),
m_nextScreenIndexMenu(INIT_SCREEN_INDEX),
m_gui(),
m_indexCycleBuilds(0),
m_buttonBuild(),
m_spriteBatch(),
m_needToUpdateDraw(true),
m_file(file),
m_SaveReload(saveReload),
m_players(players),
m_tileSize(tileSize),
m_screen(screen),
m_selectedCity(),
m_isInitialize(false)
{
	build();
}

CityScreen::~CityScreen()
{
	destroy();
}


void CityScreen::build()
{
	m_screenIndex = CITY_SCREEN_INDEX;
}

void CityScreen::destroy()
{
	m_gui.destroy();
}

/* ----------------------------------------------------------------------------------- */
/* NAME   : getNextScreenIndex														   */
/* ROLE   : Return next screen index : INIT_SCREEN_INDEX							   */
/* ROLE   : INIT_SCREEN_INDEX : in this case error -> return to initial screen		   */
/* RValue : int : const INIT_SCREEN_INDEX											   */
/* ----------------------------------------------------------------------------------- */
int CityScreen::getNextScreenIndex()const
{
	return INIT_SCREEN_INDEX;
}

/* ----------------------------------------------------------------------------------- */
/* NAME   : getPreviousScreenIndex													   */
/* ROLE   : Return previous screen index : depends context							   */
/* RValue : int : screen index														   */
/* ----------------------------------------------------------------------------------- */
int CityScreen::getPreviousScreenIndex()const
{
	return m_nextScreenIndexMenu;
}


bool CityScreen::onEntry()
{
	/* --- Add static city context --- */
	if (!m_isInitialize)
	{
		/* Check Errors / Critical Error */
		if (m_players->GETvectUnitTemplate().size() < (size_t)MIN_INDEX_CYCLE_BUILDS)
		{
			throw("Error : CityScreen::onEntry : m_players->GETvectUnitTemplate().size() < MIN_INDEX_CYCLE_BUILDS");
		}

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
		
		unsigned int i{ 0 };
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
								CITY_IHM_BUILD_LIST_DIPSLAY_POS_X,
								CITY_IHM_BUILD_LIST_DIPSLAY_POS_Y + CITY_IHM_BUILD_LIST_DIPSLAY_DELTA_Y * m_buttonBuild.size(),
								CITY_IHM_BUILD_LIST_DIPSLAY_DELTA_X,
								CITY_IHM_BUILD_LIST_DIPSLAY_DELTA_Y
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
			m_buttonBuild.back().buildG
				->setText(p.name + " : "
					+ std::to_string(p.life)
					+ "/"
					+ std::to_string(p.atq)
					+ "/"
					+ std::to_string(p.def)
					+ "/"
					+ std::to_string(p.movement)
					+ "/"
					+ Utility::to_string_with_precision(p.maintenance,1)
				);
			m_buttonBuild.back().buildG->subscribeEvent
			(
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber(&CityScreen::onBuildQueueClicked, this)
			);

			/* Do not render more than MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE */
			if (i > MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE)
			{
				m_buttonBuild.back().buildG->setVisible(HIDE_BUTTON);
				m_buttonBuild.back().buildG->disable();
			}

			i++;
		}

		m_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
		m_gui.showMouseCursor();

		/* HIDE normal mouse cursor */
		SDL_ShowCursor(0);

		m_spriteBatch.init();

		m_isInitialize = true;
	}

	resetInternalEntry();
	
	createDynamicContext();

	drawTextures();

	return true;
}

void CityScreen::onExit()
{
	/* Destroy dynamic context : buildQueue */
	for (auto& button : m_selectedCity->GETbuildQueue())
	{
		button.buildG->destroy();
		button.buildG = nullptr;
	}
}

void CityScreen::resetInternalEntry()
{
	m_selectedCity.reset();
	m_selectedCity = m_players->GETSelectedCity();

	m_indexCycleBuilds = 0;
}

void CityScreen::createDynamicContext()
{
	/* Create dynamic context : buildQueue */
	size_t j{ 0 };
	for (auto& button : m_selectedCity->GETbuildQueue())
	{
		if (button.buildG == nullptr)
		{
			button.buildG = static_cast<CEGUI::PushButton*>
				(
					m_gui.createWidget
					(
						"AlfiskoSkin/Button",
						{
							CITY_IHM_BUILD_QUEUE_DIPSLAY_POS_X,
							CITY_IHM_BUILD_QUEUE_DIPSLAY_POS_Y + CITY_IHM_BUILD_QUEUE_DIPSLAY_DELTA_Y * j,
							CITY_IHM_BUILD_QUEUE_DIPSLAY_DELTA_X,
							CITY_IHM_BUILD_QUEUE_DIPSLAY_DELTA_Y
						},
						RealEngine2D::NOT_BY_PERCENT,
						button.buildQ.name + std::to_string(rand())
					)
					);

			button.buildG->setText(button.buildQ.name);
			button.buildG->subscribeEvent
			(
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber(&CityScreen::onBuildQueueToBuildClicked, this)
			);
			j++;
		}
		else
		{
			throw("[ERROR]___: CityScreen::onEntry : button.buildG != nullptr");
		}
	}
}


void CityScreen::draw()
{
	/* line for CEGUI because CEGUI doesn't do it, do not remove  */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Back */
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_screen->gLSLProgram.use();
	/* use GL_TEXTURE0 for 1 pipe; use GL_TEXTURE1/2/3 for multiple */
	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = m_screen->gLSLProgram.getUnitformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	/* --- Draw --- */
	/* Nothing to draw every cycle */

	/* --- Render --- */
	m_spriteBatch.renderBatch();

	/* --- GL unbind --- */
	glBindTexture(GL_TEXTURE_2D, 0);
	m_screen->gLSLProgram.unuse();

	/* Need to be done after GL display */
	m_gui.draw();
}

void CityScreen::drawTextures()
{
	if (m_needToUpdateDraw)
	{
		GLuint id(UNUSED_ID);
		const static GLuint idGrass(RealEngine2D::ResourceManager::getTexture("bin/image/ground/hr-grass.png")->GETid());
		const static GLuint idWater(RealEngine2D::ResourceManager::getTexture("bin/image/ground/hr-water.png")->GETid());
		const static GLuint idDeepWater(RealEngine2D::ResourceManager::getTexture("bin/image/ground/hr-deepwater.png")->GETid());

		const static GLuint idCoal(RealEngine2D::ResourceManager::getTexture("bin/image/spec/coal.png")->GETid());
		const static GLuint idCopper(RealEngine2D::ResourceManager::getTexture("bin/image/spec/copper.png")->GETid());
		const static GLuint idFish(RealEngine2D::ResourceManager::getTexture("bin/image/spec/fish.png")->GETid());
		const static GLuint idHorse(RealEngine2D::ResourceManager::getTexture("bin/image/spec/horse.png")->GETid());
		const static GLuint idIron(RealEngine2D::ResourceManager::getTexture("bin/image/spec/iron.png")->GETid());
		const static GLuint idPetroleum(RealEngine2D::ResourceManager::getTexture("bin/image/spec/petroleum.png")->GETid());
		const static GLuint idStone(RealEngine2D::ResourceManager::getTexture("bin/image/spec/stone.png")->GETid());
		const static GLuint idtree1(RealEngine2D::ResourceManager::getTexture("bin/image/spec/tree1.png")->GETid());
		const static GLuint iduranium(RealEngine2D::ResourceManager::getTexture("bin/image/spec/uranium.png")->GETid());

		m_spriteBatch.begin();

		size_t k{ 0 };
		for (unsigned int i(0); i < INIT_SIZE_VIEW; i++)
		{
			for (unsigned int j(0); j < INIT_SIZE_VIEW; j++)
			{
				switch (m_players->GETSelectedCity()->GETtile()[k].tile_ground)
				{
				case Ground_Type::grass:
					id = idGrass;
					break;
				case Ground_Type::water:
					id = idWater;
					break;
				case Ground_Type::deepwater:
					id = idDeepWater;
					break;
				case Ground_Type::dirt:
					throw("[Error]___: drawMap : Ground_Type::dirt");
					break;
				case Ground_Type::sand:
					throw("[Error]___: drawMap : Ground_Type::sand");
					break;
				case Ground_Type::error:
					throw("[Error]___: drawMap : Ground_Type::error");
					break;
				default:
					throw("[Error]___: drawMap : default");
					break;
				}

				m_spriteBatch.draw
				(
					glm::vec4
					(
						m_players->GETSelectedCity()->GETtile()[k].tile_x,
						m_players->GETSelectedCity()->GETtile()[k].tile_y,
						*m_tileSize,
						*m_tileSize
					),
					RealEngine2D::FULL_RECT,
					id,
					0.0f,
					RealEngine2D::COLOR_WHITE
				);

				switch (m_players->GETSelectedCity()->GETtile()[k].tile_spec)
				{
				case GroundSpec_Type::coal:
					id = idCoal;
					break;
				case GroundSpec_Type::copper:
					id = idCopper;
					break;
				case GroundSpec_Type::fish:
					id = idFish;
					break;
				case GroundSpec_Type::horse:
					id = idHorse;
					break;
				case GroundSpec_Type::iron:
					id = idIron;
					break;
				case GroundSpec_Type::petroleum:
					id = idPetroleum;
					break;
				case GroundSpec_Type::stone:
					id = idStone;
					break;
				case GroundSpec_Type::tree:
					id = idtree1;
					break;
				case GroundSpec_Type::uranium:
					id = iduranium;
					break;
				case GroundSpec_Type::nothing:
					id = UNUSED_ID;
					break;
				}

				if (UNUSED_ID != id)
				{
					m_spriteBatch.draw
					(
						glm::vec4
						(
							m_players->GETSelectedCity()->GETtile()[k].tile_x,
							m_players->GETSelectedCity()->GETtile()[k].tile_y,
							*m_tileSize,
							*m_tileSize
						),
						RealEngine2D::FULL_RECT,
						id,
						0.0f,
						RealEngine2D::COLOR_WHITE
					);
				}

				k++;
			}
		}

		m_spriteBatch.end();

		m_needToUpdateDraw = false;
	}
}


void CityScreen::update()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev))
	{
		m_gui.onSDLEvent(ev, m_game->getInputManager());
		m_game->onSDLEvent(ev);
		input(ev);
	}
}

void CityScreen::input(SDL_Event& ev)
{
	if (MOUSE_SCROLL_UP == ev.wheel.y)
	{
		if (m_indexCycleBuilds >= MIN_INDEX_CYCLE_BUILDS)
		{
			m_indexCycleBuilds--;
			updatePositionCycleButton(CYCLE_BUTTON_DIR_UP);
		}
	}
	else if (MOUSE_SCROLL_DOWN == ev.wheel.y)
	{
		if (m_indexCycleBuilds < (m_buttonBuild.size() - MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE - MIN_INDEX_CYCLE_BUILDS))
		{
			m_indexCycleBuilds++;
			updatePositionCycleButton(CYCLE_BUTTON_DIR_DOWN);
		}
	}
	else
	{
		/* Do nothing */
	}
}

void CityScreen::updatePositionCycleButton(bool dir)
{

	CEGUI::UVector2 u{};

	/* Enable and Render new button / Disable and not Render old button */
	if (dir == CYCLE_BUTTON_DIR_UP)
	{
		m_buttonBuild[m_indexCycleBuilds].buildG->enable();
		m_buttonBuild[m_indexCycleBuilds].buildG->setVisible(SHOW_BUTTON);

		m_buttonBuild[m_indexCycleBuilds + MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE + 1].buildG->disable();
		m_buttonBuild[m_indexCycleBuilds + MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE + 1].buildG->setVisible(HIDE_BUTTON);
	}
	else
	{
		m_buttonBuild[m_indexCycleBuilds - 1].buildG->disable();
		m_buttonBuild[m_indexCycleBuilds - 1].buildG->setVisible(HIDE_BUTTON);

		m_buttonBuild[m_indexCycleBuilds + MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE].buildG->enable();
		m_buttonBuild[m_indexCycleBuilds + MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE].buildG->setVisible(SHOW_BUTTON);
	}
	
	/* Update Y positions */
	for (auto& c : m_buttonBuild)
	{
		u = c.buildG->getPosition();
		if (dir == CYCLE_BUTTON_DIR_UP)
		{
			u.d_y.d_scale += CITY_IHM_BUILD_QUEUE_DIPSLAY_DELTA_Y;
		}
		else
		{
			u.d_y.d_scale -= CITY_IHM_BUILD_QUEUE_DIPSLAY_DELTA_Y;
		}
		c.buildG->setPosition(u);
	}
}


bool CityScreen::onBuildQueueClicked(const CEGUI::EventArgs& /* e */)
{
	for (auto &button : m_buttonBuild)
	{
		if (button.buildG->isPushed())
		{
			m_selectedCity->addBuildToQueue
			(
				{
					static_cast<CEGUI::PushButton*>
					(
						m_gui.createWidget
						(
							"AlfiskoSkin/Button",
							{
								CITY_IHM_BUILD_QUEUE_DIPSLAY_POS_X,
								CITY_IHM_BUILD_QUEUE_DIPSLAY_POS_Y + CITY_IHM_BUILD_QUEUE_DIPSLAY_DELTA_Y * m_selectedCity->GETbuildQueue().size(),
								CITY_IHM_BUILD_QUEUE_DIPSLAY_DELTA_X,
								CITY_IHM_BUILD_QUEUE_DIPSLAY_DELTA_Y
							},
							RealEngine2D::NOT_BY_PERCENT,
							button.buildQ.name + std::to_string(rand())
						)
					),
					button.buildQ
				}
			);
			m_selectedCity->GETbuildQueue().back().buildG->setText(button.buildQ.name);
			m_selectedCity->GETbuildQueue().back().buildG->subscribeEvent
			(
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber(&CityScreen::onBuildQueueToBuildClicked, this)
			);

			break;
		}
	}
	return true;
}

bool CityScreen::onBuildQueueToBuildClicked(const CEGUI::EventArgs& /* e */)
{
	size_t removeIndex{ 0 }, changePosIndex{0};
	for (auto& button : m_selectedCity->GETbuildQueue())
	{
		if (button.buildG->isPushed())
		{
			/* Adjust new Y coor to the rest of deque */
			CEGUI::UVector2 coor{};
			changePosIndex = removeIndex + OFFSET_INDEX_ERASE_BUTTON;
			for (changePosIndex; changePosIndex < m_selectedCity->GETbuildQueue().size(); changePosIndex++)
			{
				coor = m_selectedCity->GETbuildQueue()[changePosIndex].buildG->getPosition();
				coor.d_y.d_scale -= CITY_IHM_BUILD_QUEUE_DIPSLAY_DELTA_Y;
				m_selectedCity->GETbuildQueue()[changePosIndex].buildG->setPosition(coor);
			}

			/* --- Destroy build from City --- */
			m_selectedCity->removeBuildToQueue(removeIndex);

			break;
		}
		removeIndex++;
	}
	return true;
}

bool CityScreen::onReturnToMapClicked(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = GAMEPLAY_SCREEN_INDEX;
	m_currentState = RealEngine2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}
