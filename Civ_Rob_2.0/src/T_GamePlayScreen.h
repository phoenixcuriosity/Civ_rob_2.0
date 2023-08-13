/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.1.0
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

#ifndef T_GamePlayScreen_H
#define T_GamePlayScreen_H


#include "LIB.h"

#include "GameInput.h"

#include <RealEngine2D/src/IGameScreen.h>
#include <RealEngine2D/src/Camera2D.h>
#include <RealEngine2D/src/WidgetLabel.h>
#include <RealEngine2D/src/GUI.h>
#include <RealEngine2D/src/SpriteBatch.h>
#include <RealEngine2D/src/AudioEngine.h>

/* *********************************************************
 *						 Structs						   *
 ********************************************************* */

/* 
	All RealEngine2D objects
	- Shaders
	- camera/cameraHUD
	- Sprite/font
	- audioEngine
	- GUI
*/
struct Screen
{
	RealEngine2D::Camera2D camera;
	RealEngine2D::Camera2D cameraHUD;

	RealEngine2D::SpriteBatch spriteBatchHUDDynamic;
	RealEngine2D::SpriteBatch spriteBatchHUDStatic;

	RealEngine2D::AudioEngine audioEngine;

	RealEngine2D::GUI m_gui;
	std::vector<CEGUI::RadioButton*> m_vectPlayerRadioButton;
	std::vector<RealEngine2D::WidgetLabel> m_widgetLabels;

	int m_nextScreenIndexMenu = RealEngine2D::SCREEN_INDEX::INIT;
};

struct Var
{

	std::string tempPlayerName = EMPTY_STRING;

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


