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

#ifndef CityScreen_H
#define CityScreen_H

#include "../LIB.h"

#include "../Screens/CityScreenEnumTexture.h"
#include "../City/BuildManager.h"

#include <R2D/src/IGameScreen.h>
#include <R2D/src/GUI.h>
#include <R2D/src/Screen.h>
#include <R2D/src/SpriteBatch.h>
#include <R2D/src/T_Coor.h>


class Players;

namespace city
{
	class City;
}

class CityScreen : public R2D::IGameScreen, public R2D::CScreen
{
private:
	using dequeBuild = std::deque<city::BuildManager::buildGUI>;
	using CityPtrT = std::shared_ptr<city::City>;
	using VectCoor = std::vector<R2D::Coor>;

	/* Define an ID which is unused */
	static constexpr GLuint UNUSED_ID = 0;

	static constexpr size_t OFFSET_INDEX_ERASE_BUTTON = 1;

	/* Define minimum size to cycle builds */
	static constexpr unsigned int MIN_INDEX_CYCLE_BUILDS = 1;
	static constexpr unsigned int MAX_BUTTONS_BUILDS_DISPLAY_AT_ONCE = 7;
	static constexpr bool HIDE_BUTTON = false;
	static constexpr bool SHOW_BUTTON = true;
	static constexpr bool CYCLE_BUTTON_DIR_UP = false;
	static constexpr bool CYCLE_BUTTON_DIR_DOWN = true;

	static constexpr float DIPSLAY_BUILD_LIST_POS_X = 0.75f;
	static constexpr float DIPSLAY_BUILD_LIST_POS_Y = 0.1f;
	static constexpr float DIPSLAY_BUILD_LIST_DELTA_X = 0.2f;
	static constexpr float DIPSLAY_BUILD_LIST_DELTA_Y = 0.026f;

	static constexpr float	DIPSLAY_BUILD_QUEUE_POS_X = 0.8f;
	static constexpr float	DIPSLAY_BUILD_QUEUE_POS_Y = 0.5f;
	static constexpr float	DIPSLAY_BUILD_QUEUE_DELTA_X = 0.1f;
	static constexpr float	DIPSLAY_BUILD_QUEUE_DELTA_Y = 0.026f;

	static constexpr unsigned int DIPSLAY_FOOD_POS_X = 50;
	static constexpr unsigned int DIPSLAY_FOOD_POS_Y = 300;
	static constexpr unsigned int DIPSLAY_FOOD_DELTA_X = 32;
	static constexpr unsigned int DIPSLAY_FOOD_DELTA_Y = 32;

	static constexpr unsigned int DIPSLAY_WORK_POS_X = 50;
	static constexpr unsigned int DIPSLAY_WORK_POS_Y = 700;
	static constexpr unsigned int DIPSLAY_WORK_DELTA_X = 32;
	static constexpr unsigned int DIPSLAY_WORK_DELTA_Y = 32;

	static constexpr unsigned int OFFSET_EMOTION{ 8 };

	static constexpr unsigned int MODULO_TEN{ 10 };

public:
	CityScreen
	(
		Players* const players,
		unsigned int* const tileSize
	);
	~CityScreen();

public: /* Override from R2D::IGameScreen */

	int getNextScreenIndex()const override;
	int getPreviousScreenIndex()const override;

	void build() override;
	void destroy() override;

	bool onEntry() override;
	void onExit() override;

	void update() override;
	void draw() override;

private: /* Override from R2D::CScreen */

	void doInitOptimizeTexture()override;
	void doInitUI() override;
	void doInitHUDText() override;
	void doDrawAll() override;

private: /* Helper to Override from R2D::CScreen */

	virtual void initCoorVectTilePos();

	virtual void resetInternalEntry();

	virtual void createDynamicContext();

private:

	virtual void input(const SDL_Event& ev);

	virtual void updatePositionCycleButton(const bool dir);

	virtual void drawTextures();

	void drawTile(const size_t kTile);

	void drawTileSpec(const size_t kTile);

	void drawTileApp(const size_t kTile);

	void drawFood();

	void drawBuild();

	void drawCitizen();

	void drawCityName();

	void drawNbPop();

	void callDraw(const size_t kTile, const GLuint id, const float depth);

private:

	bool onBuildQueueClicked(const CEGUI::EventArgs& e);
	bool onBuildQueueToBuildClicked(const CEGUI::EventArgs& e);
	bool onReturnToMapClicked(const CEGUI::EventArgs& e);

private:
	int m_nextScreenIndexMenu;

	unsigned int m_indexCycleBuilds;

	dequeBuild m_buttonBuild;

	CityScreenTexture m_idTexture;

	Players* m_players;
	VectCoor m_displayTileVect;
	unsigned int* m_tileSize;

	CityPtrT m_selectedCity;

	bool m_isInitialize;
};

#endif // !CityScreen_H
