﻿/*

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

#include "GameInput.h"

#include "App.h"
#include "City.h"
#include "GamePlayScreen.h"
#include "Player.h"
#include "ScreenIndices.h"
#include "Unit.h"
#include "Utility.h"

#include <iostream>

#include <R2D/src/CardinalDirection.h> 
#include <R2D/src/ResourceManager.h> 

namespace GInput
{
	const float KEY_SPEED_MOVE = 2.0f;

	const int UNIT_NO_MOVEMENT = 0;

	const SDL_KeyCode KEY_TO_FOUND_CITY = SDLK_b;
	const SDL_KeyCode KEY_TO_IRRIGATE = SDLK_i;
	const SDL_KeyCode KEY_NEXT_TURN = SDLK_SPACE;
}
   
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : run_SDL																					    	  */
/* ROLE : Recherche infini des �venements d'entr� de type SDL_event : souris, clavier					      */
/* ROLE : Si aucun �venements n'est trouv� alors le programme continue									      */
/* INPUT : struct Sysinfo& : structure globale du programme									    			  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void GamePlayScreen::inputSDL
(
	SDL_Event& ev
)
{
	switch (ev.type)
	{

	case SDL_KEYDOWN:
		m_game->getInputManager().pressKey(ev.key.keysym.sym);
			
		break;
	case SDL_KEYUP:
		m_game->getInputManager().releaseKey(ev.key.keysym.sym);
		break;
		/* ---------------------------------------------------------------------- */
		/* test sur le type d'�v�nement click souris (enfonc�)					  */
		/* ---------------------------------------------------------------------- */

	case SDL_MOUSEBUTTONDOWN:
		m_game->getInputManager().pressKey(ev.button.button);
		mouseClick(ev);
		break;
	case SDL_MOUSEBUTTONUP:
		m_game->getInputManager().releaseKey(ev.button.button);
		break;

		/* ---------------------------------------------------------------------- */
		/* test sur le type d'�v�nement wheel									  */
		/* ---------------------------------------------------------------------- */

	case SDL_MOUSEWHEEL:
		wheel(ev);
		break;

		/* ---------------------------------------------------------------------- */
		/* test sur le type d'�v�nement motion									  */
		/* ---------------------------------------------------------------------- */

	case SDL_MOUSEMOTION:
		m_game->getInputManager().setMouseCoords(ev.motion.x, ev.motion.y);
		break;

	default:
		/* N/A */
		break;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : actionByKey																				    	  */
/* ROLE : Define action for each key press																      */
/* INPUT : SDL_Event& ev : Event from SDL input												    			  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
void GamePlayScreen::actionByKey()
{
	/* Next Turn */
	if (m_game->getInputManager().isKeyDown(GInput::KEY_NEXT_TURN))
	{
		m_nextTurn.nextTurn(*this);
		m_game->getInputManager().releaseKey(GInput::KEY_NEXT_TURN);
	}


	if (Utility::checkPlayerUnitSelection(m_players))
	{
		/* Found City */
		if (m_game->getInputManager().isKeyDown(GInput::KEY_TO_FOUND_CITY))
		{
			PlayerPtrT splayer(m_players.GETselectedPlayerPtr());
			UnitPtrT sUnit(splayer->GETtabUnit()[splayer->GETselectedUnit()]);

			if (sUnit->isThisUnitType("settler"))
			{
				City::createCity(*this);
				m_mainMap.SETneedToUpdateDraw(true);
			}
		}

		/* Irragate */
		if (m_game->getInputManager().isKeyDown(GInput::KEY_TO_IRRIGATE))
		{
			PlayerPtrT splayer(m_players.GETselectedPlayerPtr());
			UnitPtrT sUnit(splayer->GETtabUnit()[splayer->GETselectedUnit()]);

			if	(sUnit->GETname().starts_with("ouvrier_tier_") == STRINGS::START_WITH)
			{
				sUnit->irrigate(m_mainMap.GETmatriceMap());
				m_mainMap.SETneedToUpdateDraw(true);
			}
		}


		/* Move Unit */
		if (m_game->getInputManager().isKeyDown(SDLK_KP_1))
		{
			/* ← + ↓ */
			Unit::tryToMove
			(
				m_mainMap.GETmatriceMap(),
				m_players,
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection
					(R2D::CardinalDirections::SouthWest)
			);
		}
		else
		if (m_game->getInputManager().isKeyDown(SDLK_KP_2))
		{
			/* ↓ */
			Unit::tryToMove
			(
				m_mainMap.GETmatriceMap(),
				m_players,
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection
					(R2D::CardinalDirections::South)
			);
		}
		else
		if (m_game->getInputManager().isKeyDown(SDLK_KP_3))
		{
			/* → + ↓ */
			Unit::tryToMove
			(
				m_mainMap.GETmatriceMap(),
				m_players,
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection
					(R2D::CardinalDirections::SouthEst)
			);
		}
		else
		if (m_game->getInputManager().isKeyDown(SDLK_KP_4))
		{
			/* ← */
			Unit::tryToMove
			(
				m_mainMap.GETmatriceMap(),
				m_players,
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection
					(R2D::CardinalDirections::West)
			);
		}
		/* NO SDLK_KP_5 : Useless */
		else
		if (m_game->getInputManager().isKeyDown(SDLK_KP_6))
		{
			/* → */
			Unit::tryToMove
			(
				m_mainMap.GETmatriceMap(),
				m_players,
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection
					(R2D::CardinalDirections::Est)
			);
		}
		else
		if (m_game->getInputManager().isKeyDown(SDLK_KP_7))
		{
			/* ← + ↑ */
			Unit::tryToMove
			(
				m_mainMap.GETmatriceMap(),
				m_players,
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection
					(R2D::CardinalDirections::NorthWest)
			);
		}
		else
		if (m_game->getInputManager().isKeyDown(SDLK_KP_8))
		{
			/* ↑ */
			Unit::tryToMove
			(
				m_mainMap.GETmatriceMap(),
				m_players,
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection
					(R2D::CardinalDirections::North)
			);
		}
		else
		if (m_game->getInputManager().isKeyDown(SDLK_KP_9))
		{
			/* → + ↑ */
			Unit::tryToMove
			(
				m_mainMap.GETmatriceMap(),
				m_players,
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection
					(R2D::CardinalDirections::NorthEst)
			);
		}
		else
		{
			/* Do nothing */
		}
	}
}

void GamePlayScreen::moveCamera
(
	const float deltaTime
)
{
	if (m_game->getInputManager().isKeyDown(SDLK_z) && !m_camera.isLockMoveUP())
	{
		m_camera.SETposition
			(
				m_camera.GETposition()
				+
				glm::vec2(0.0f, GInput::KEY_SPEED_MOVE * deltaTime)
			);
		updateDrawCameraMove();
	}
	if (m_game->getInputManager().isKeyDown(SDLK_s) && !m_camera.isLockMoveDOWN())
	{
		m_camera.SETposition
			(
				m_camera.GETposition()
				+
				glm::vec2(0.0f, -GInput::KEY_SPEED_MOVE * deltaTime)
			);
		updateDrawCameraMove();
	}
	if (m_game->getInputManager().isKeyDown(SDLK_q) && !m_camera.isLockMoveLEFT())
	{
		m_camera.SETposition
			(
				m_camera.GETposition()
				+
				glm::vec2(-GInput::KEY_SPEED_MOVE * deltaTime, 0.0f)
			);
		updateDrawCameraMove();
	}
	if (m_game->getInputManager().isKeyDown(SDLK_d) && !m_camera.isLockMoveRIGHT())
	{
		m_camera.SETposition
			(
				m_camera.GETposition()
				+
				glm::vec2(GInput::KEY_SPEED_MOVE * deltaTime, 0.0f)
			);
		updateDrawCameraMove();
	}
}

void GamePlayScreen::updateDrawCameraMove()
{
	m_mainMap.SETneedToUpdateDraw(true);
	m_players.SETneedToUpdateDrawUnit(true);
	m_players.SETneedToUpdateDrawCity(true);
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : wheel																						    	  */
/* ROLE : Recherche l'incr�mentation ou d�cr�mentation du contexte										      */
/* INPUT : struct Sysinfo& : structure globale du programme												      */
/* INPUT : int& wheel : l'�venement de scroll de la souris													  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void GamePlayScreen::wheel
(
	const SDL_Event& ev
)
{
	/*
	if (Select_Type::selectcreate == mainGame.GETvar().select)
	{
		if (MOUSE_SCROLL_UP == wheel)
		{
			if (mainGame.GETvar().s_player.unitToCreate > 0)
				mainGame.GETvar().s_player.unitToCreate--;
		}
		else if (MOUSE_SCROLL_DOWN == wheel)
		{
			if (mainGame.GETvar().s_player.unitToCreate < mainGame.GETvar().s_player.tabUnit_Template.size() - 1)
				mainGame.GETvar().s_player.unitToCreate++;
		}
		Unit::searchUnit(sysinfo.var.s_player);
	}
	*/
	/*
	else if (sysinfo.var.statescreen == STATEreload)
	{
		if (wheel == 1)
		{
			if (sysinfo.var.currentSave > 0)
				sysinfo.var.currentSave--;
		}
		else if (wheel == -1)
		{
			if (sysinfo.var.currentSave < sysinfo.var.nbSave)
				sysinfo.var.currentSave++;
		}
	}
	*/
	if (R2D::GUI_MOUSE::MOUSE_SCROLL_UP == ev.wheel.y)
	{
		m_camera.zoom();
		m_mainMap.SETneedToUpdateDraw(true);
		m_players.SETneedToUpdateDrawUnit(true);
	}
	else if (R2D::GUI_MOUSE::MOUSE_SCROLL_DOWN == ev.wheel.y)
	{
		m_camera.deZoom();
		m_mainMap.SETneedToUpdateDraw(true);
		m_players.SETneedToUpdateDrawUnit(true);
	}
}


void GamePlayScreen::mouseClick
(
	const SDL_Event& ev
)
{
	
	if (ev.button.clicks == R2D::GUI_MOUSE::TWO_CLICKS && m_game->getInputManager().isKeyDown(SDL_BUTTON_LEFT))
	{
		if	(
				m_players.searchCity
				(
					MainMap::convertPosXToIndex
					(
						(double)m_game->getInputManager().GETmouseCoords().x
						+ (double)m_camera.GETposition().x
						- (double)m_game->getWindow().GETscreenWidth() / 2
					)
					,
					MainMap::convertPosYToIndex
					(
						-(double)m_game->getInputManager().GETmouseCoords().y
						+ (double)m_camera.GETposition().y
						+ (double)m_game->getWindow().GETscreenHeight() / 2
					)
				)
			)
		{
			m_screen.m_nextScreenIndexMenu = SCREEN_INDEX::CITY;
			m_currentState = R2D::ScreenState::CHANGE_NEXT;
		}
		else
		{
			/* Do nothing */
		}
	}
	else
	{
		/* Do nothing */
	}
}

unsigned int GamePlayScreen::getMouseCoorNorm(const unsigned char c)
{
	if (c == 'X')
	{
		return
		(
			m_mainMap.GETtileSize()
			*
			MainMap::convertPosXToIndex
			(
				(double)m_game->getInputManager().GETmouseCoords().x
				+ (double)m_camera.GETposition().x
				- (double)m_game->getWindow().GETscreenWidth() / 2
			)
		);
	}
	else
	if (c == 'Y')
	{
		return 
		(
			m_mainMap.GETtileSize()
			*
			MainMap::convertPosYToIndex
			(
				-(double)m_game->getInputManager().GETmouseCoords().y
				+ (double)m_camera.GETposition().y
				+ (double)m_game->getWindow().GETscreenHeight() / 2
			)
		);
	}
	else
	{
		throw("[ERROR]___: GamePlayScreen::getMouseCoorNorm");
	}
}

 /*
 *	End Of File : KeyboardMouse.cpp
 */