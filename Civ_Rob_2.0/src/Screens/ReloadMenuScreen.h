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


#ifndef ReloadMenuScreen_H
#define ReloadMenuScreen_H

#include "../LIB.h"

#include <R2D\src\Camera2D.h>
#include <R2D\src\GUI.h>
#include <R2D/src/IGameScreen.h>
#include <R2D/src/Screen.h>
#include <R2D/src/WidgetLabel.h>

class ReloadMenuScreen : public R2D::IGameScreen, public R2D::CScreen
{
public:
	ReloadMenuScreen();
	~ReloadMenuScreen();

private: /* Override from R2D::IGameScreen */

	int getNextScreenIndex()const override;
	int getPreviousScreenIndex()const override;

	void build() override;
	void destroy() override;

	bool onEntry() override;
	void onExit() override;

	void update() override;
	void draw() override;

private:

	void updateVisibilityIfSaveSelected();

private: /* Override from R2D::CScreen */

	void doInitOptimizeTexture()override;
	void doInitUI() override;
	void doInitHUDText()override;
	void doDrawAll()override;

private: /* doInitUI helpers */

	void buttonDisplay();
	void radioButtonDisplay();

	void updateRadioButtonPosition();

private: /* subscribeEvent from Button */

	bool onOneSaveCliked(const CEGUI::EventArgs& e);
	bool onLoadSave(const CEGUI::EventArgs& e);
	bool onClearASaveCliked(const CEGUI::EventArgs& e);
	bool onClearSavesCliked(const CEGUI::EventArgs& e);
	bool onExitClicked(const CEGUI::EventArgs& e);

private:
	int m_nextScreenIndexMenu;

	std::vector<CEGUI::RadioButton*> m_vectSavesRadioButton;
	std::vector<R2D::WidgetLabel> m_widgetLabels;

	bool m_isInitialize;
};


#endif // !ReloadMenuScreen_H


