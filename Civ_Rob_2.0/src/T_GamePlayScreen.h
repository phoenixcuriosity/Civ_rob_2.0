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

#ifndef T_GamePlayScreen_H
#define T_GamePlayScreen_H

#include "GameInput.h"

#include <R2D/src/IGameScreen.h>
#include <R2D/src/Camera2D.h>
#include <R2D/src/WidgetLabel.h>
#include <R2D/src/GUI.h>
#include <R2D/src/SpriteBatch.h>
#include <R2D/src/AudioEngine.h>

/* *********************************************************
 *						 Structs						   *
 ********************************************************* */

/* 
	All R2D objects
	- Shaders
	- camera/cameraHUD
	- Sprite/font
	- audioEngine
	- GUI
*/
struct Screen
{
	R2D::Camera2D camera;
	R2D::Camera2D cameraHUD;

	R2D::SpriteBatch spriteBatchHUDDynamic;
	R2D::SpriteBatch spriteBatchHUDStatic;

	R2D::AudioEngine audioEngine;

	R2D::GUI m_gui;
	std::vector<CEGUI::RadioButton*> m_vectPlayerRadioButton;
	std::vector<R2D::WidgetLabel> m_widgetLabels;

	int m_nextScreenIndexMenu = R2D::SCREEN_INDEX::INIT;
};

struct Var
{

	std::string tempPlayerName = STRINGS::EMPTY;

	/*
		état de la sélection du joueur
		enum Select_Type : unsigned int
		{
			selectnothing,
			selectcreate,
			selectinspect,
			selectmove,
			selectmoveCitizen
		};
	*/
	Select_Type select = Select_Type::selectnothing;

	/*
		état de l'écran du joueur
		enum State_Type : unsigned int
		{
			STATEnothing,
			STATEtitleScreen,
			STATEscreennewgame,
			STATEreload,
			STATEmainmap,
			STATEscience,
			STATEcitiemap
		};
	*/
	State_Type statescreen = State_Type::error;

	/*
			état de l'entrée clavier
			enum CinState_Type : unsigned int
			{
				cinNothing,
				cinTitleScreen,
				cinScreenNewGameNbPlayer,
				cinScreenNewGameNamePlayer,
				cinMainMap,
			};
		*/
	CinState_Type cinState = CinState_Type::cinNothing;

};

#endif // !T_GamePlayScreen_H


