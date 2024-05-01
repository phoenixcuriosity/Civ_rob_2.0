/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.1.0
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

#ifndef CityScreen_H
#define CityScreen_H

#include "LIB.h"

#include <deque>

#include <R2D/src/IGameScreen.h>
#include <R2D/src/GUI.h>
#include <R2D/src/SpriteBatch.h>

#include "T_CityScreen.h"


class CityScreen : public R2D::IGameScreen
{
public:
	CityScreen
	(
		SaveReload* const SaveReload,
		Players* const players,
		unsigned int* const tileSize
	);
	~CityScreen();

	virtual int getNextScreenIndex()const override;
	virtual int getPreviousScreenIndex()const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual bool onEntry() override;
	virtual void onExit() override;

private:

	virtual void resetInternalEntry();

	virtual void createDynamicContext();



public:


	virtual void update() override;
	virtual void draw() override;

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

	void callDraw(const size_t kTile, const GLuint id);

private:

	bool onBuildQueueClicked(const CEGUI::EventArgs& e);
	bool onBuildQueueToBuildClicked(const CEGUI::EventArgs& e);
	bool onReturnToMapClicked(const CEGUI::EventArgs& e);


public:


private:
	int m_nextScreenIndexMenu;

	R2D::GUI m_gui;
	unsigned int m_indexCycleBuilds;

	std::deque<buildGUI> m_buttonBuild;

	/* Dedicated spriteBatch */
	R2D::SpriteBatch m_spriteBatch;
	R2D::SpriteBatch m_spriteBatchAppartenance;
	bool m_needToUpdateDraw;
	std::vector<GLuint> s_vectID;

	Players* m_players;
	unsigned int* m_tileSize;

	SaveReload* m_SaveReload;

	std::shared_ptr<City> m_selectedCity;

	bool m_isInitialize;
};

#endif // !CityScreen_H
