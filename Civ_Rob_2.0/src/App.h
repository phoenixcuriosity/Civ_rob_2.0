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

#ifndef App_H
#define App_H

#include "LIB.h"

#include "SaveReload.h"

#include <R2D/src/IMainGame.h>

class App : public R2D::IMainGame
{
public:
	App();
	~App();

	virtual void onInit() override;
	virtual void InitShaders() override;
	virtual void onExit() override;
	virtual void addScreens() override;

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initMain																	   */
	/* ROLE : Chargement des informations de la configuration du jeu					   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void initMain();

	void destroy();


private:
	MainMenuScreenPtrT m_mainMenuScreen;
	NewGameScreenPtrT m_newGameScreen;
	ReloadMenuScreenPtrT m_reloadMenuScreen;
	GamePlayScreenPtrT m_gamePlayScreen;
	CityScreenPtrT m_CityScreen;

	SaveReload m_saveReload;
};

#endif // !App_H

