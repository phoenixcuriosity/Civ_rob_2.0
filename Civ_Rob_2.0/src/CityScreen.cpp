/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.7.0
	file version : 1.7

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

#define CITY_IHM_BUILD_LIST_DIPSLAY_POS_X 0.75f
#define CITY_IHM_BUILD_LIST_DIPSLAY_POS_Y 0.1f 
#define CITY_IHM_BUILD_LIST_DIPSLAY_DELTA_X 0.2f
#define CITY_IHM_BUILD_LIST_DIPSLAY_DELTA_Y 0.026f 

#define CITY_IHM_BUILD_QUEUE_DIPSLAY_POS_X 0.8f
#define CITY_IHM_BUILD_QUEUE_DIPSLAY_POS_Y 0.5f 
#define CITY_IHM_BUILD_QUEUE_DIPSLAY_DELTA_X 0.1f
#define CITY_IHM_BUILD_QUEUE_DIPSLAY_DELTA_Y 0.026f

#define CITY_IHM_FOOD_DIPSLAY_POS_X 50
#define CITY_IHM_FOOD_DIPSLAY_POS_Y 300
#define CITY_IHM_FOOD_DIPSLAY_DELTA_X 32
#define CITY_IHM_FOOD_DIPSLAY_DELTA_Y 32

#define CITY_IHM_WORK_DIPSLAY_POS_X 50
#define CITY_IHM_WORK_DIPSLAY_POS_Y 700
#define CITY_IHM_WORK_DIPSLAY_DELTA_X 32
#define CITY_IHM_WORK_DIPSLAY_DELTA_Y 32

const unsigned int CITY_IHM_OFFSET_EMOTION{ 8 };

const unsigned int MODULO_TEN{ 10 };

const size_t OFFSET_INDEX_ERASE_BUTTON = 1;

static size_t START_APPARTENANCE_INDEX = 0;
static size_t START_EMOTION_INDEX = 0;
static size_t START_ICON_INDEX = 0;

/* ----------------------------------------------------------------------------------- */
/* NAME : CityScreen																   */
/* ROLE : CityScreen Constructor													   */
/* RETURNED VALUE : N/A																   */
/* ----------------------------------------------------------------------------------- */
CityScreen::CityScreen
(
	SaveReload* const SaveReload,
	Players* const players,
	unsigned int* const tileSize
)
:
RealEngine2D::IGameScreen(),
m_nextScreenIndexMenu(INIT_SCREEN_INDEX),
m_gui(),
m_indexCycleBuilds(0),
m_buttonBuild(),
m_spriteBatch(),
m_spriteBatchAppartenance(),
m_needToUpdateDraw(true),
s_vectID(),
m_SaveReload(SaveReload),
m_players(players),
m_tileSize(tileSize),
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

		const std::string CITY_IMAGE_PATH{RealEngine2D::ResourceManager::getFile(e_Files::imagesPath)->getPath()};
		const std::string DIR_GROUND {"ground/"};
		const std::string DIR_SPEC {"spec/"};
		const std::string DIR_CA {"couleur d'apartenance/"};
		const std::string DIR_CITIZEN {"citizen/"};
		const std::string DIR_CITY {"city/"};

		using RealEngine2D::ResourceManager;

		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_GROUND + "hr-grass" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_GROUND + "hr-water" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_GROUND + "hr-deepwater" + EXTENSION_PNG)->GETid());

		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_SPEC + "coal" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_SPEC + "copper" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_SPEC + "fish" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_SPEC + "horse" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_SPEC + "iron" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_SPEC + "petroleum" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_SPEC + "stone" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_SPEC + "tree1" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_SPEC + "uranium" + EXTENSION_PNG)->GETid());
		START_APPARTENANCE_INDEX = s_vectID.size();

		for (unsigned int i(0); i < NB_MAX_PLAYER; i++)
		{
			s_vectID.push_back
			(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_CA + "ColorPlayer" + std::to_string(i) + EXTENSION_PNG)->GETid());
		}

		START_EMOTION_INDEX = s_vectID.size();
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_CITIZEN + "ecstatic" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_CITIZEN + "happy" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_CITIZEN + "neutral" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_CITIZEN + "sad" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_CITIZEN + "angry" + EXTENSION_PNG)->GETid());


		START_ICON_INDEX = s_vectID.size();

		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_CITY + "food" + EXTENSION_PNG)->GETid());
		s_vectID.push_back(ResourceManager::getTexture(CITY_IMAGE_PATH + DIR_CITY + "Hammer" + EXTENSION_PNG)->GETid());

		
		m_gui.init(RealEngine2D::ResourceManager::getFile(e_Files::GUIPath)->getPath());
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
		for (const auto& p : m_players->GETvectUnitTemplate())
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
						p.workToBuild,
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
		m_spriteBatchAppartenance.init();

		m_isInitialize = true;
	}

	m_needToUpdateDraw = true;

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

	RealEngine2D::ResourceManager::getGLSLProgram().use();
	/* use GL_TEXTURE0 for 1 pipe; use GL_TEXTURE1/2/3 for multiple */
	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = RealEngine2D::ResourceManager::getGLSLProgram().getUnitformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	/* --- Draw --- */
	/* Nothing to draw every cycle */
	
	/* --- Render --- */
	m_spriteBatch.renderBatch();
	m_spriteBatchAppartenance.renderBatch();

	/* --- GL unbind --- */
	glBindTexture(GL_TEXTURE_2D, 0);
	RealEngine2D::ResourceManager::getGLSLProgram().unuse();

	/* Need to be done after GL display */
	m_gui.draw();
}

void CityScreen::drawTile(const size_t kTile)
{
	GLuint id(UNUSED_ID);

	switch (m_players->GETSelectedCity()->GETtile()[kTile].tile_ground)
	{
	case Ground_Type::grass:
		id = s_vectID[0];
		break;
	case Ground_Type::water:
		id = s_vectID[1];
		break;
	case Ground_Type::deepwater:
		id = s_vectID[2];
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

	callDraw(kTile, id);
}
void CityScreen::drawTileSpec(const size_t kTile)
{
	GLuint id(UNUSED_ID);

	switch (m_players->GETSelectedCity()->GETtile()[kTile].tile_spec)
	{
	case GroundSpec_Type::coal:
		id = s_vectID[3];
		break;
	case GroundSpec_Type::copper:
		id = s_vectID[4];
		break;
	case GroundSpec_Type::fish:
		id = s_vectID[5];
		break;
	case GroundSpec_Type::horse:
		id = s_vectID[6];
		break;
	case GroundSpec_Type::iron:
		id = s_vectID[7];
		break;
	case GroundSpec_Type::petroleum:
		id = s_vectID[8];
		break;
	case GroundSpec_Type::stone:
		id = s_vectID[9];
		break;
	case GroundSpec_Type::tree:
		id = s_vectID[10];
		break;
	case GroundSpec_Type::uranium:
		id = s_vectID[11];
		break;
	case GroundSpec_Type::nothing:
		id = UNUSED_ID;
		break;
	}

	callDraw(kTile, id);
}
void CityScreen::drawTileApp(const size_t kTile)
{
	if (m_players->GETSelectedCity()->GETtile()[kTile].appartenance != NO_APPARTENANCE)
	{
		m_spriteBatchAppartenance.draw
		(
			glm::vec4
			(
				m_players->GETSelectedCity()->GETtile()[kTile].tileXCityScreen,
				m_players->GETSelectedCity()->GETtile()[kTile].tileYCityScreen,
				*m_tileSize,
				*m_tileSize
			),
			RealEngine2D::FULL_RECT,
			s_vectID[START_APPARTENANCE_INDEX + m_players->GETSelectedCity()->GETtile()[kTile].appartenance],
			0.0f,
			RealEngine2D::COLOR_WHITE_T25
		);
	}
}
void CityScreen::drawFood()
{
	unsigned int foodL{ 0 };
	unsigned int foodC{ 0 };
	for (
			unsigned int i{ 0 };
			i < (unsigned int)std::floor(m_players->GETSelectedCity()->GETfoodStockPerc());
			i++
		)
	{
		m_spriteBatch.draw
		(
			glm::vec4
			(
				CITY_IHM_FOOD_DIPSLAY_POS_X + foodC * CITY_IHM_FOOD_DIPSLAY_DELTA_X,
				CITY_IHM_FOOD_DIPSLAY_POS_Y - foodL * CITY_IHM_FOOD_DIPSLAY_DELTA_Y,
				CITY_IHM_FOOD_DIPSLAY_DELTA_X,
				CITY_IHM_FOOD_DIPSLAY_DELTA_Y
			),
			RealEngine2D::FULL_RECT,
			s_vectID[START_ICON_INDEX],
			0.0f,
			RealEngine2D::COLOR_WHITE
		);

		foodC++;
		if ((foodC % MODULO_TEN) == 0)
		{
			foodL++;
			foodC = 0;
		}
	}
}

void CityScreen::callDraw(const size_t kTile, const GLuint id)
{
	if (UNUSED_ID != id)
	{
		m_spriteBatch.draw
		(
			glm::vec4
			(
				m_players->GETSelectedCity()->GETtile()[kTile].tileXCityScreen,
				m_players->GETSelectedCity()->GETtile()[kTile].tileYCityScreen,
				*m_tileSize,
				*m_tileSize
			),
			RealEngine2D::FULL_RECT,
			id,
			0.0f,
			RealEngine2D::COLOR_WHITE
		);
	}
}

void CityScreen::drawBuild()
{
	unsigned int workL{ 0 };
	unsigned int workC{ 0 };
	for (
			unsigned int i{ 0 };
			i < (unsigned int)std::floor(m_players->GETSelectedCity()->GETBuildPerc());
			i++
		)
	{
		m_spriteBatch.draw
		(
			glm::vec4
			(
				CITY_IHM_WORK_DIPSLAY_POS_X + workC * CITY_IHM_WORK_DIPSLAY_DELTA_X,
				CITY_IHM_WORK_DIPSLAY_POS_Y - workL * CITY_IHM_WORK_DIPSLAY_DELTA_Y,
				CITY_IHM_WORK_DIPSLAY_DELTA_X,
				CITY_IHM_WORK_DIPSLAY_DELTA_Y
			),
			RealEngine2D::FULL_RECT,
			s_vectID[START_ICON_INDEX + 1],
			0.0f,
			RealEngine2D::COLOR_WHITE
		);

		workC++;
		if ((workC % MODULO_TEN) == 0)
		{
			workL++;
			workC = 0;
		}
	}
}

void CityScreen::drawCitizen()
{
	GLuint id(UNUSED_ID);

	for (const auto& citizen: m_players->GETSelectedCity()->GETcitizens())
	{
		switch (citizen->GEThappiness())
		{
		case Emotion_Type::ecstatic:
			id = s_vectID[START_EMOTION_INDEX];
			break;
		case Emotion_Type::happy:
			id = s_vectID[START_EMOTION_INDEX + 1];
			break;
		case Emotion_Type::neutral:
			id = s_vectID[START_EMOTION_INDEX + 2];
			break;
		case Emotion_Type::sad:
			id = s_vectID[START_EMOTION_INDEX + 3];
			break;
		case Emotion_Type::angry:
			id = s_vectID[START_EMOTION_INDEX + 4];
			break;
		default:
			id = s_vectID[START_EMOTION_INDEX + 2];
			break;
		}

		m_spriteBatch.draw
		(
			glm::vec4
			(
				m_players->GETSelectedCity()->GETtile()[citizen->GETtileOccupied()].tileXCityScreen + CITY_IHM_OFFSET_EMOTION / 2,
				m_players->GETSelectedCity()->GETtile()[citizen->GETtileOccupied()].tileYCityScreen + CITY_IHM_OFFSET_EMOTION / 2,
				*m_tileSize - CITY_IHM_OFFSET_EMOTION,
				*m_tileSize - CITY_IHM_OFFSET_EMOTION
			),
			RealEngine2D::FULL_RECT,
			id,
			0.0f,
			RealEngine2D::COLOR_WHITE
		);
	}
}

void CityScreen::drawCityName()
{
	/* City Name */
	RealEngine2D::ResourceManager::getSpriteFont()->draw
	(
		m_spriteBatch,
		m_players->GETSelectedCity()->GETname().c_str(),
		glm::vec2(900.0f, 1020.0f), // offset pos
		glm::vec2(0.64f), // size
		0.0f,
		RealEngine2D::COLOR_GOLD
	);
}

void CityScreen::drawNbPop()
{
	/* City Nb POP */
	RealEngine2D::ResourceManager::getSpriteFont()->draw
	(
		m_spriteBatch,
		std::to_string(m_players->GETSelectedCity()->GETnbpop()).c_str(),
		glm::vec2(900.0f, 920.0f), // offset pos
		glm::vec2(0.48f), // size
		0.0f,
		RealEngine2D::COLOR_LIGHT_GREY
	);
}

void CityScreen::drawTextures()
{
	if (m_needToUpdateDraw)
	{
		m_spriteBatch.begin();
		m_spriteBatchAppartenance.begin();

		size_t k{ 0 };
		for (unsigned int i(0); i < INIT_SIZE_VIEW; i++)
		{
			for (unsigned int j(0); j < INIT_SIZE_VIEW; j++)
			{
				drawTile(k);

				drawTileSpec(k);

				drawTileApp(k);

				k++;
			}
		}

		drawFood();

		drawBuild();

		drawCitizen();

		drawCityName();

		drawNbPop();

		m_spriteBatch.end();
		m_spriteBatchAppartenance.end();

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

void CityScreen::input(const SDL_Event& ev)
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

void CityScreen::updatePositionCycleButton(const bool dir)
{

	CEGUI::UVector2 u{};

	/* Enable and Render new button / Disable and not Render old button */
	if (dir == CYCLE_BUTTON_DIR_UP)
	{
		m_buttonBuild[m_indexCycleBuilds].buildG->enable();
		m_buttonBuild[m_indexCycleBuilds].buildG->setVisible(SHOW_BUTTON);

		m_buttonBuild[m_indexCycleBuilds + MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE + MIN_INDEX_CYCLE_BUILDS].buildG->disable();
		m_buttonBuild[m_indexCycleBuilds + MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE + MIN_INDEX_CYCLE_BUILDS].buildG->setVisible(HIDE_BUTTON);
	}
	else
	{
		m_buttonBuild[m_indexCycleBuilds - MIN_INDEX_CYCLE_BUILDS].buildG->disable();
		m_buttonBuild[m_indexCycleBuilds - MIN_INDEX_CYCLE_BUILDS].buildG->setVisible(HIDE_BUTTON);

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

			m_needToUpdateDraw = true;
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

			m_needToUpdateDraw = true;
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
