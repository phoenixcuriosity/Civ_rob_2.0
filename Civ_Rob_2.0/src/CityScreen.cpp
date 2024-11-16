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

#include "CityScreen.h"

#include "App.h"
#include "Citizen.h"
#include "City.h"
#include "LogSentences.h"
#include "Player.h"
#include "Players.h"
#include "ScreenIndices.h"
#include "Utility.h"
#include "T_Citizen.h"
#include "T_MainMap.h"
#include "T_Unit.h"

#include <R2D/src/GLTexture.h>
#include <R2D/src/ResourceManager.h>
#include <R2D/src/Log.h>

#include <format>


namespace CITY_IHM
{
	namespace DIPSLAY
	{
		namespace BUILD
		{
			namespace LIST
			{
				constexpr float POS_X = 0.75f;
				constexpr float POS_Y = 0.1f;
				constexpr float DELTA_X = 0.2f;
				constexpr float DELTA_Y = 0.026f;
			}

			namespace QUEUE
			{
				constexpr float	POS_X = 0.8f;
				constexpr float	POS_Y = 0.5f;
				constexpr float	DELTA_X = 0.1f;
				constexpr float	DELTA_Y = 0.026f;
			}
		}

		namespace FOOD
		{
			constexpr unsigned int POS_X = 50;
			constexpr unsigned int POS_Y = 300;
			constexpr unsigned int DELTA_X = 32;
			constexpr unsigned int DELTA_Y = 32;
		}

		namespace WORK
		{
			constexpr unsigned int POS_X = 50;
			constexpr unsigned int POS_Y = 700;
			constexpr unsigned int DELTA_X = 32;
			constexpr unsigned int DELTA_Y = 32;
		}
	}

	constexpr unsigned int OFFSET_EMOTION{ 8 };

	constexpr unsigned int MODULO_TEN{ 10 };
}

namespace CitySC
{
	/* Define an ID which is unused */
	constexpr GLuint UNUSED_ID = 0;

	constexpr size_t OFFSET_INDEX_ERASE_BUTTON = 1;

	/* Define minimum size to cycle builds */
	constexpr unsigned int MIN_INDEX_CYCLE_BUILDS = 1;

	/*  */
	constexpr unsigned int MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE = 7;

	constexpr bool HIDE_BUTTON = false;

	constexpr bool SHOW_BUTTON = true;

	constexpr bool CYCLE_BUTTON_DIR_UP = false;
	constexpr bool CYCLE_BUTTON_DIR_DOWN = true;
}

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
	SaveReloadPtrT const SaveReload,
	Players* const players,
	unsigned int* const tileSize
)
:
R2D::IGameScreen(),
R2D::CScreen(),
m_nextScreenIndexMenu(R2D::SCREEN_INDEX::INIT),
m_indexCycleBuilds(0),
m_buttonBuild(),
m_idMap(),
m_SaveReload(SaveReload),
m_players(players),
m_tileSize(tileSize),
m_selectedCity(),
m_isInitialize(false)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::CITY_MENU, logS::WHAT::CONSTRUCTOR, logS::DATA::SCREEN);
}

CityScreen::~CityScreen()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::CITY_MENU, logS::WHAT::DESTRUCTOR, logS::DATA::SCREEN);
	destroy();
}


void CityScreen::build()
{
	m_screenIndex = SCREEN_INDEX::CITY;

	using R2D::ResourceManager;
	static const std::string CITY_IMAGE_PATH{ R2D::ResourceManager::getFile(R2D::e_Files::imagesPath)->getPath() };

	ResourceManager::getTextureIdFromDir(CITY_IMAGE_PATH, m_idMap);
}

void CityScreen::destroy()
{
	end();
}

/* ----------------------------------------------------------------------------------- */
/* NAME   : getNextScreenIndex														   */
/* ROLE   : Return next screen index : INIT_SCREEN_INDEX							   */
/* ROLE   : INIT_SCREEN_INDEX : in this case error -> return to initial screen		   */
/* RValue : int : const INIT_SCREEN_INDEX											   */
/* ----------------------------------------------------------------------------------- */
int CityScreen::getNextScreenIndex()const
{
	return R2D::SCREEN_INDEX::INIT;
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
	LOG(R2D::LogLevelType::info, 0, logS::WHO::CITY_MENU, logS::WHAT::ON_ENTRY, logS::DATA::START);
	init(m_game->getWindow().GETscreenWidth(), m_game->getWindow().GETscreenHeight());
	LOG(R2D::LogLevelType::info, 0, logS::WHO::CITY_MENU, logS::WHAT::ON_ENTRY, logS::DATA::END);
	return true;
}

void CityScreen::doInitUI()
{
	/* --- Add static city context --- */
	if (!m_isInitialize)
	{
		/* Check Errors / Critical Error */
		if (m_players->GETvectUnitTemplate().size() < (size_t)CitySC::MIN_INDEX_CYCLE_BUILDS)
		{
			throw("Error : CityScreen::onEntry : m_players->GETvectUnitTemplate().size() < MIN_INDEX_CYCLE_BUILDS");
		}

		CEGUI::PushButton* returnToMap = static_cast<CEGUI::PushButton*>
			(m_gui.createWidget(
				"AlfiskoSkin/Button",
				{ 0.0f, 0.0f, 0.1f, 0.05f },
				R2D::NOT_BY_PERCENT,
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
								CITY_IHM::DIPSLAY::BUILD::LIST::POS_X,
								CITY_IHM::DIPSLAY::BUILD::LIST::POS_Y + CITY_IHM::DIPSLAY::BUILD::LIST::DELTA_Y * m_buttonBuild.size(),
								CITY_IHM::DIPSLAY::BUILD::LIST::DELTA_X,
								CITY_IHM::DIPSLAY::BUILD::LIST::DELTA_Y
							},
							R2D::NOT_BY_PERCENT,
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
					+ Utility::to_string_with_precision(p.maintenance, 1)
				);
			m_buttonBuild.back().buildG->subscribeEvent
			(
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber(&CityScreen::onBuildQueueClicked, this)
			);

			/* Do not render more than MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE */
			if (i > CitySC::MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE)
			{
				m_buttonBuild.back().buildG->setVisible(CitySC::HIDE_BUTTON);
				m_buttonBuild.back().buildG->disable();
			}

			i++;
		}

		m_isInitialize = true;
	}

	resetInternalEntry();

	createDynamicContext();
}

void CityScreen::doInitHUDText()
{
	drawTextures();
}

void CityScreen::onExit()
{
	m_selectedCity->clearDynamicContextBuildToQueue();
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
							CITY_IHM::DIPSLAY::BUILD::QUEUE::POS_X,
							CITY_IHM::DIPSLAY::BUILD::QUEUE::POS_Y + CITY_IHM::DIPSLAY::BUILD::QUEUE::DELTA_Y * j,
							CITY_IHM::DIPSLAY::BUILD::QUEUE::DELTA_X,
							CITY_IHM::DIPSLAY::BUILD::QUEUE::DELTA_Y
						},
						R2D::NOT_BY_PERCENT,
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
	drawAll();
}

void CityScreen::doDrawAll()
{
	/* Nothing yet */
}

void CityScreen::drawTile(const size_t kTile)
{
	GLuint id(CitySC::UNUSED_ID);

	switch (m_players->GETSelectedCity()->GETtile()[kTile].tile_ground)
	{
	case Ground_Type::grass:
		id = m_idMap["grass"];
		break;
	case Ground_Type::water:
		id = m_idMap["water"];
		break;
	case Ground_Type::deepwater:
		id = m_idMap["deepwater"];
		break;
	case Ground_Type::irragated:
		id = m_idMap["grassIrr"];
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

	callDraw(kTile, id, 0.0f);
}
void CityScreen::drawTileSpec(const size_t kTile)
{
	GLuint id(CitySC::UNUSED_ID);

	switch (m_players->GETSelectedCity()->GETtile()[kTile].tile_spec)
	{
	case GroundSpec_Type::coal:
		id = m_idMap["coal"];
		break;
	case GroundSpec_Type::copper:
		id = m_idMap["copper"];
		break;
	case GroundSpec_Type::iron:
		id = m_idMap["iron"];
		break;
	case GroundSpec_Type::tree:
		id = m_idMap["tree1"];
		break;
	case GroundSpec_Type::stone:
		id = m_idMap["stone"];
		break;
	case GroundSpec_Type::uranium:
		id = m_idMap["uranium"];
		break;
	case GroundSpec_Type::horse:
		id = m_idMap["horse"];
		break;
	case GroundSpec_Type::fish:
		id = m_idMap["fish"];
		break;
	case GroundSpec_Type::petroleum:
		id = m_idMap["petroleum"];
		break;
	case GroundSpec_Type::nothing:
		id = CitySC::UNUSED_ID;
		break;
	}

	callDraw(kTile, id, 0.1f);
}
void CityScreen::drawTileApp(const size_t kTile)
{
	if (m_players->GETSelectedCity()->GETtile()[kTile].appartenance != SELECTION::NO_APPARTENANCE)
	{
		m_spriteBatchHUDStatic.draw
		(
			glm::vec4
			(
				m_players->GETSelectedCity()->GETtile()[kTile].tileXCityScreen,
				m_players->GETSelectedCity()->GETtile()[kTile].tileYCityScreen,
				*m_tileSize,
				*m_tileSize
			),
			R2D::FULL_RECT,
			m_idMap[std::format("ColorPlayer{}", m_players->GETSelectedCity()->GETtile()[kTile].appartenance)],
			0.5f,
			R2D::COLOR_WHITE_T25
		);
	}
}
void CityScreen::drawFood()
{
	unsigned int foodL{ 0 };
	unsigned int foodC{ 0 };
	for (
			unsigned int i{ 0 };
			i < (unsigned int)std::floor(m_players->GETSelectedCity()->GETFoodManager().GETfoodStockPerc());
			i++
		)
	{
		m_spriteBatchHUDStatic.draw
		(
			glm::vec4
			(
				CITY_IHM::DIPSLAY::FOOD::POS_X + foodC * CITY_IHM::DIPSLAY::FOOD::DELTA_X,
				CITY_IHM::DIPSLAY::FOOD::POS_Y - foodL * CITY_IHM::DIPSLAY::FOOD::DELTA_Y,
				CITY_IHM::DIPSLAY::FOOD::DELTA_X,
				CITY_IHM::DIPSLAY::FOOD::DELTA_Y
			),
			R2D::FULL_RECT,
			searchKeyInIdMap("food"),
			1.f,
			R2D::COLOR_WHITE
		);

		foodC++;
		if ((foodC % CITY_IHM::MODULO_TEN) == 0)
		{
			foodL++;
			foodC = 0;
		}
	}
}

void CityScreen::callDraw(const size_t kTile, const GLuint id, const float depth)
{
	if (CitySC::UNUSED_ID != id)
	{
		m_spriteBatchHUDStatic.draw
		(
			glm::vec4
			(
				m_players->GETSelectedCity()->GETtile()[kTile].tileXCityScreen,
				m_players->GETSelectedCity()->GETtile()[kTile].tileYCityScreen,
				*m_tileSize,
				*m_tileSize
			),
			R2D::FULL_RECT,
			id,
			depth,
			R2D::COLOR_WHITE
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
		m_spriteBatchHUDStatic.draw
		(
			glm::vec4
			(
				CITY_IHM::DIPSLAY::WORK::POS_X + workC * CITY_IHM::DIPSLAY::WORK::DELTA_X,
				CITY_IHM::DIPSLAY::WORK::POS_Y - workL * CITY_IHM::DIPSLAY::WORK::DELTA_Y,
				CITY_IHM::DIPSLAY::WORK::DELTA_X,
				CITY_IHM::DIPSLAY::WORK::DELTA_Y
			),
			R2D::FULL_RECT,
			searchKeyInIdMap("Hammer"),
			1.f,
			R2D::COLOR_WHITE
		);

		workC++;
		if ((workC % CITY_IHM::MODULO_TEN) == 0)
		{
			workL++;
			workC = 0;
		}
	}
}

void CityScreen::drawCitizen()
{
	GLuint id(CitySC::UNUSED_ID);

	for (const auto& citizen: m_players->GETSelectedCity()->GETcitizens())
	{
		switch (citizen->GEThappiness())
		{
		case Emotion_Type::ecstatic:
			id = searchKeyInIdMap("ecstatic");
			break;
		case Emotion_Type::happy:
			id = searchKeyInIdMap("happy");
			break;
		case Emotion_Type::neutral:
			id = searchKeyInIdMap("neutral");
			break;
		case Emotion_Type::sad:
			id = searchKeyInIdMap("sad");
			break;
		case Emotion_Type::angry:
			id = searchKeyInIdMap("angry");
			break;
		default:
			id = searchKeyInIdMap("neutral");
			break;
		}

		m_spriteBatchHUDStatic.draw
		(
			glm::vec4
			(
				m_players->GETSelectedCity()->GETtile()[citizen->GETtileOccupied()].tileXCityScreen + CITY_IHM::OFFSET_EMOTION / 2,
				m_players->GETSelectedCity()->GETtile()[citizen->GETtileOccupied()].tileYCityScreen + CITY_IHM::OFFSET_EMOTION / 2,
				*m_tileSize - CITY_IHM::OFFSET_EMOTION,
				*m_tileSize - CITY_IHM::OFFSET_EMOTION
			),
			R2D::FULL_RECT,
			id,
			1.f,
			R2D::COLOR_WHITE
		);
	}
}

void CityScreen::drawCityName()
{
	/* City Name */
	R2D::ResourceManager::getSpriteFont()->draw
	(
		m_spriteBatchHUDStatic,
		m_players->GETSelectedCity()->GETname().c_str(),
		glm::vec2(900.0f, 1020.0f), // offset pos
		glm::vec2(3.2f), // size
		1.f,
		R2D::COLOR_GOLD
	);
}

void CityScreen::drawNbPop()
{
	/* City Nb POP */
	R2D::ResourceManager::getSpriteFont()->draw
	(
		m_spriteBatchHUDStatic,
		std::to_string(m_players->GETSelectedCity()->GETnbpop()).c_str(),
		glm::vec2(900.0f, 920.0f), // offset pos
		glm::vec2(1.28f), // size
		1.f,
		R2D::COLOR_LIGHT_GREY
	);
}

void CityScreen::drawTextures()
{
	size_t k{ 0 };
	for (unsigned int i(0); i < CITY_INFLUENCE::INIT_SIZE_VIEW; i++)
	{
		for (unsigned int j(0); j < CITY_INFLUENCE::INIT_SIZE_VIEW; j++)
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
}



void CityScreen::update()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev))
	{
		m_game->onSDLEvent(ev);
		updateInputManager(ev, m_game->getInputManager());
		input(ev);
	}
}

void CityScreen::input(const SDL_Event& ev)
{
	if (R2D::GUI_MOUSE::MOUSE_SCROLL_UP == ev.wheel.y)
	{
		if (m_indexCycleBuilds >= CitySC::MIN_INDEX_CYCLE_BUILDS)
		{
			m_indexCycleBuilds--;
			updatePositionCycleButton(CitySC::CYCLE_BUTTON_DIR_UP);
		}
	}
	else if (R2D::GUI_MOUSE::MOUSE_SCROLL_DOWN == ev.wheel.y)
	{
		if (m_indexCycleBuilds < (m_buttonBuild.size() - CitySC::MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE - CitySC::MIN_INDEX_CYCLE_BUILDS))
		{
			m_indexCycleBuilds++;
			updatePositionCycleButton(CitySC::CYCLE_BUTTON_DIR_DOWN);
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
	if (dir == CitySC::CYCLE_BUTTON_DIR_UP)
	{
		m_buttonBuild[m_indexCycleBuilds].buildG->enable();
		m_buttonBuild[m_indexCycleBuilds].buildG->setVisible(CitySC::SHOW_BUTTON);

		m_buttonBuild[m_indexCycleBuilds + CitySC::MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE + CitySC::MIN_INDEX_CYCLE_BUILDS].buildG->disable();
		m_buttonBuild[m_indexCycleBuilds + CitySC::MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE + CitySC::MIN_INDEX_CYCLE_BUILDS].buildG->setVisible(CitySC::HIDE_BUTTON);
	}
	else
	{
		m_buttonBuild[m_indexCycleBuilds - CitySC::MIN_INDEX_CYCLE_BUILDS].buildG->disable();
		m_buttonBuild[m_indexCycleBuilds - CitySC::MIN_INDEX_CYCLE_BUILDS].buildG->setVisible(CitySC::HIDE_BUTTON);

		m_buttonBuild[m_indexCycleBuilds + CitySC::MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE].buildG->enable();
		m_buttonBuild[m_indexCycleBuilds + CitySC::MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE].buildG->setVisible(CitySC::SHOW_BUTTON);
	}
	
	/* Update Y positions */
	for (auto& c : m_buttonBuild)
	{
		u = c.buildG->getPosition();
		if (dir == CitySC::CYCLE_BUTTON_DIR_UP)
		{
			u.d_y.d_scale += CITY_IHM::DIPSLAY::BUILD::QUEUE::DELTA_Y;
		}
		else
		{
			u.d_y.d_scale -= CITY_IHM::DIPSLAY::BUILD::QUEUE::DELTA_Y;
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
								CITY_IHM::DIPSLAY::BUILD::QUEUE::POS_X,
								CITY_IHM::DIPSLAY::BUILD::QUEUE::POS_Y + CITY_IHM::DIPSLAY::BUILD::QUEUE::DELTA_Y * m_selectedCity->GETbuildQueue().size(),
								CITY_IHM::DIPSLAY::BUILD::QUEUE::DELTA_X,
								CITY_IHM::DIPSLAY::BUILD::QUEUE::DELTA_Y
							},
							R2D::NOT_BY_PERCENT,
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
			changePosIndex = removeIndex + CitySC::OFFSET_INDEX_ERASE_BUTTON;
			for (changePosIndex; changePosIndex < m_selectedCity->GETbuildQueue().size(); changePosIndex++)
			{
				coor = m_selectedCity->GETbuildQueue()[changePosIndex].buildG->getPosition();
				coor.d_y.d_scale -= CITY_IHM::DIPSLAY::BUILD::QUEUE::DELTA_Y;
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
	m_nextScreenIndexMenu = SCREEN_INDEX::GAMEPLAY;
	m_currentState = R2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}

GLuint CityScreen::searchKeyInIdMap(const std::string& key)
{
	if (auto search = m_idMap.find(key); search != m_idMap.end())
	{
		return search->second;
	}
	else
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::CITY_MENU, logS::WHAT::TEXTURE, logS::DATA::ERROR_FIND_TEXTURE, key);
		return 0;
	}
}
