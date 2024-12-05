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

#include "LIB.h"

#include "CityScreenEnumTexture.h"
#include "T_CityScreen.h"
#include "T_Coor.h"

#include <R2D/src/API_fwd.h>
#include <R2D/src/IGameScreen.h>
#include <R2D/src/GUI.h>
#include <R2D/src/Screen.h>
#include <R2D/src/SpriteBatch.h>

class CityScreen : public R2D::IGameScreen, public R2D::CScreen
{
public:
	CityScreen
	(
		SaveReloadPtrT const SaveReload,
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
	unsigned int* m_tileSize;

	SaveReloadPtrT m_SaveReload;

	CityPtrT m_selectedCity;

	bool m_isInitialize;
};

#endif // !CityScreen_H
