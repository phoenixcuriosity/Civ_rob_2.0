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

#include "GameInput.h"

#include "App.h"
#include "City/City.h"
#include "Screens/GamePlayScreen.h"
#include "Player.h"
#include "ScreenIndices.h"
#include "Unit/Unit.h"
#include "Unit/UnitService.h"
#include "Utility.h"

#include <iostream>

#include <R2D/src/CardinalDirection.h>
#include <R2D/src/InputManager.h>
#include <R2D/src/ResourceManager.h>

namespace GInput
{
	constexpr float KEY_SPEED_MOVE = 2.0f;

	constexpr int UNIT_NO_MOVEMENT = 0;

	constexpr SDL_KeyCode KEY_TO_FOUND_CITY = SDLK_b;
	constexpr SDL_KeyCode KEY_TO_IRRIGATE = SDLK_i;
	constexpr SDL_KeyCode KEY_NEXT_TURN = SDLK_SPACE;
}

namespace DELTA_TIME
{
	constexpr float MS_PER_SECOND(1000.0f);
	const float TARGET_FRAMETIME = MS_PER_SECOND / static_cast<float>(R2D::SCREEN_REFRESH_RATE);
	constexpr unsigned int MAX_PHYSICS_STEPS(6);
	constexpr float MAX_DELTA_TIME(1.0f);
}



void GameInput::updateSDLInputCycle
(
	SDL_Event& ev,
	R2D::InputManager& inputManager,
	R2D::Camera2D& camera,
	MainMap& mainMap,
	Players& players,
	const R2D::Window& window,
	int& nextScreenIndexMenu,
	R2D::ScreenState& currentState
)
{
	inputSDL(ev, inputManager, camera, mainMap, players, window, nextScreenIndexMenu, currentState);
}

void GameInput::processInput(GamePlayScreen& gamePlayScreen)
{
	actionByKey(gamePlayScreen);
	moveCameraByDeltaTime(gamePlayScreen.getInputManager(), gamePlayScreen.getCamera(), gamePlayScreen.GETmainMap(), gamePlayScreen.GETPlayers());
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
void GameInput::inputSDL
(
	SDL_Event& ev,
	R2D::InputManager& inputManager,
	R2D::Camera2D& camera,
	MainMap& mainMap,
	Players& players,
	const R2D::Window& window,
	int& nextScreenIndexMenu,
	R2D::ScreenState& currentState
)
{
	switch (ev.type)
	{

	case SDL_KEYDOWN:
		inputManager.pressKey(ev.key.keysym.sym);

		break;
	case SDL_KEYUP:
		inputManager.releaseKey(ev.key.keysym.sym);
		break;
		/* ---------------------------------------------------------------------- */
		/* test sur le type d'�v�nement click souris (enfonc�)					  */
		/* ---------------------------------------------------------------------- */

	case SDL_MOUSEBUTTONDOWN:
		inputManager.pressKey(ev.button.button);
		mouseClick(ev, inputManager, camera, players, window, nextScreenIndexMenu, currentState);
		break;
	case SDL_MOUSEBUTTONUP:
		inputManager.releaseKey(ev.button.button);
		break;

		/* ---------------------------------------------------------------------- */
		/* test sur le type d'�v�nement wheel									  */
		/* ---------------------------------------------------------------------- */

	case SDL_MOUSEWHEEL:
		wheel(ev, camera, mainMap, players);
		break;

		/* ---------------------------------------------------------------------- */
		/* test sur le type d'�v�nement motion									  */
		/* ---------------------------------------------------------------------- */

	case SDL_MOUSEMOTION:
		inputManager.setMouseCoords(ev.motion.x, ev.motion.y);
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
void GameInput::actionByKey
(
	GamePlayScreen& gamePlayScreen
)
{
	/* Next Turn */
	if (gamePlayScreen.getInputManager().isKeyDown(GInput::KEY_NEXT_TURN))
	{
		gamePlayScreen.getNextTurn().nextTurn(gamePlayScreen);
		gamePlayScreen.getInputManager().releaseKey(GInput::KEY_NEXT_TURN);
	}


	if (Utility::checkPlayerUnitSelection(gamePlayScreen.GETPlayers()))
	{
		/* Found City */
		if (gamePlayScreen.getInputManager().isKeyDown(GInput::KEY_TO_FOUND_CITY))
		{
			PlayerPtrT splayer(gamePlayScreen.GETPlayers().GETselectedPlayerPtr());
			UnitPtrT sUnit(splayer->GETtabUnit()[splayer->GETselectedUnit()]);

			if (sUnit->isThisUnitType("settler"))
			{
				city::City::createCity(gamePlayScreen);
				gamePlayScreen.GETmainMap().SETneedToUpdateDraw(true);
			}
		}

		/* Irragate */
		if (gamePlayScreen.getInputManager().isKeyDown(GInput::KEY_TO_IRRIGATE))
		{
			PlayerPtrT splayer(gamePlayScreen.GETPlayers().GETselectedPlayerPtr());
			UnitPtrT sUnit(splayer->GETtabUnit()[splayer->GETselectedUnit()]);

			if	(sUnit->GETname().starts_with("ouvrier_tier_") == STRINGS::START_WITH)
			{
				sUnit->irrigate(gamePlayScreen.GETmainMap().GETmatriceMap());
				gamePlayScreen.GETmainMap().SETneedToUpdateDraw(true);
			}
		}


		/* Move Unit */
		if (gamePlayScreen.getInputManager().isKeyDown(SDLK_KP_1))
		{
			/* ← + ↓ */
			unit::UnitService::tryToMove
			(
				gamePlayScreen.GETmainMap().GETmatriceMap(),
				gamePlayScreen.GETPlayers(),
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection(R2D::CardinalDirection::Directions::SouthWest)
			);
		}
		else
		if (gamePlayScreen.getInputManager().isKeyDown(SDLK_KP_2))
		{
			/* ↓ */
			unit::UnitService::tryToMove
			(
				gamePlayScreen.GETmainMap().GETmatriceMap(),
				gamePlayScreen.GETPlayers(),
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection(R2D::CardinalDirection::Directions::South)
			);
		}
		else
		if (gamePlayScreen.getInputManager().isKeyDown(SDLK_KP_3))
		{
			/* → + ↓ */
			unit::UnitService::tryToMove
			(
				gamePlayScreen.GETmainMap().GETmatriceMap(),
				gamePlayScreen.GETPlayers(),
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection(R2D::CardinalDirection::Directions::SouthEst)
			);
		}
		else
		if (gamePlayScreen.getInputManager().isKeyDown(SDLK_KP_4))
		{
			/* ← */
			unit::UnitService::tryToMove
			(
				gamePlayScreen.GETmainMap().GETmatriceMap(),
				gamePlayScreen.GETPlayers(),
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection(R2D::CardinalDirection::Directions::West)
			);
		}
		/* NO SDLK_KP_5 : Useless */
		else
		if (gamePlayScreen.getInputManager().isKeyDown(SDLK_KP_6))
		{
			/* → */
			unit::UnitService::tryToMove
			(
				gamePlayScreen.GETmainMap().GETmatriceMap(),
				gamePlayScreen.GETPlayers(),
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection(R2D::CardinalDirection::Directions::Est)
			);
		}
		else
		if (gamePlayScreen.getInputManager().isKeyDown(SDLK_KP_7))
		{
			/* ← + ↑ */
			unit::UnitService::tryToMove
			(
				gamePlayScreen.GETmainMap().GETmatriceMap(),
				gamePlayScreen.GETPlayers(),
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection(R2D::CardinalDirection::Directions::NorthWest)
			);
		}
		else
		if (gamePlayScreen.getInputManager().isKeyDown(SDLK_KP_8))
		{
			/* ↑ */
			unit::UnitService::tryToMove
			(
				gamePlayScreen.GETmainMap().GETmatriceMap(),
				gamePlayScreen.GETPlayers(),
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection(R2D::CardinalDirection::Directions::North)
			);
		}
		else
		if (gamePlayScreen.getInputManager().isKeyDown(SDLK_KP_9))
		{
			/* → + ↑ */
			unit::UnitService::tryToMove
			(
				gamePlayScreen.GETmainMap().GETmatriceMap(),
				gamePlayScreen.GETPlayers(),
				Select_Type::selectmove,
				R2D::ResourceManager::getCardinalDirection(R2D::CardinalDirection::Directions::NorthEst)
			);
		}
		else
		{
			/* Do nothing */
		}
	}

#ifdef _DEBUG
	if (gamePlayScreen.getInputManager().isKeyDown(SDL_BUTTON_RIGHT))
	{
		gamePlayScreen.GETPlayers().clickToSelectUnit
		(
			getMouseCoorNorm('X', gamePlayScreen.GETmainMap(), gamePlayScreen.getInputManager(), gamePlayScreen.getCamera(), gamePlayScreen.getParentWindow()),
			getMouseCoorNorm('Y', gamePlayScreen.GETmainMap(), gamePlayScreen.getInputManager(), gamePlayScreen.getCamera(), gamePlayScreen.getParentWindow())
		);
	}
#endif // _DEBUG

}


void GameInput::moveCameraByDeltaTime
(
	R2D::InputManager& inputManager,
	R2D::Camera2D& camera,
	MainMap& mainMap,
	Players& players
)
{
	static Uint32 prevTicks{ SDL_GetTicks() };
	Uint32 frameTime{ 0 }, newTicks{ 0 };
	float totalDeltaTime{ 0.0f }, deltaTime{ 0.0f };

	newTicks = SDL_GetTicks();
	frameTime = newTicks - prevTicks;
	prevTicks = newTicks;
	totalDeltaTime = (float)frameTime / DELTA_TIME::TARGET_FRAMETIME;
	int i{ 0 };

	while (totalDeltaTime > 0.0f && i < DELTA_TIME::MAX_PHYSICS_STEPS)
	{
		deltaTime = std::min(totalDeltaTime, DELTA_TIME::MAX_DELTA_TIME);
		moveCamera(deltaTime, inputManager, camera, mainMap, players);
		totalDeltaTime -= deltaTime;
		i++;
	}
}

void GameInput::moveCamera
(
	const float deltaTime,
	R2D::InputManager& inputManager,
	R2D::Camera2D& camera,
	MainMap& mainMap,
	Players& players
)
{
	if (inputManager.isKeyDown(SDLK_z) && !camera.isLockMoveUP())
	{
		camera.SETposition
			(
				camera.GETposition()
				+
				glm::vec2(0.0f, GInput::KEY_SPEED_MOVE * deltaTime)
			);
		updateDrawCameraMove(mainMap, players);
	}
	if (inputManager.isKeyDown(SDLK_s) && !camera.isLockMoveDOWN())
	{
		camera.SETposition
			(
				camera.GETposition()
				+
				glm::vec2(0.0f, -GInput::KEY_SPEED_MOVE * deltaTime)
			);
		updateDrawCameraMove(mainMap, players);
	}
	if (inputManager.isKeyDown(SDLK_q) && !camera.isLockMoveLEFT())
	{
		camera.SETposition
			(
				camera.GETposition()
				+
				glm::vec2(-GInput::KEY_SPEED_MOVE * deltaTime, 0.0f)
			);
		updateDrawCameraMove(mainMap, players);
	}
	if (inputManager.isKeyDown(SDLK_d) && !camera.isLockMoveRIGHT())
	{
		camera.SETposition
			(
				camera.GETposition()
				+
				glm::vec2(GInput::KEY_SPEED_MOVE * deltaTime, 0.0f)
			);
		updateDrawCameraMove(mainMap, players);
	}
}


void GameInput::updateDrawCameraMove
(
	MainMap& mainMap,
	Players& players
)
{
	mainMap.SETneedToUpdateDraw(true);
	players.SETneedToUpdateDrawUnit(true);
	players.SETneedToUpdateDrawCity(true);
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
void GameInput::wheel
(
	const SDL_Event& ev,
	R2D::Camera2D& camera,
	MainMap& mainMap,
	Players& players
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
		camera.zoom();
		mainMap.SETneedToUpdateDraw(true);
		players.SETneedToUpdateDrawUnit(true);
	}
	else if (R2D::GUI_MOUSE::MOUSE_SCROLL_DOWN == ev.wheel.y)
	{
		camera.deZoom();
		mainMap.SETneedToUpdateDraw(true);
		players.SETneedToUpdateDrawUnit(true);
	}
}


void GameInput::mouseClick
(
	const SDL_Event& ev,
	R2D::InputManager& inputManager,
	R2D::Camera2D& camera,
	Players& players,
	const R2D::Window& window,
	int& nextScreenIndexMenu,
	R2D::ScreenState& currentState
)
{

	if (ev.button.clicks == R2D::GUI_MOUSE::TWO_CLICKS && inputManager.isKeyDown(SDL_BUTTON_LEFT))
	{
		if	(
			players.searchCity
				(
					MainMap::convertPosXToIndex
					(
						(double)inputManager.GETmouseCoords().x
						+ (double)camera.GETposition().x
						- (double)window.GETscreenWidth() / 2
					)
					,
					MainMap::convertPosYToIndex
					(
						-(double)inputManager.GETmouseCoords().y
						+ (double)camera.GETposition().y
						+ (double)window.GETscreenHeight() / 2
					)
				)
			)
		{
			nextScreenIndexMenu = SCREEN_INDEX::CITY;
			currentState = R2D::ScreenState::CHANGE_NEXT;
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

unsigned int GameInput::getMouseCoorNorm
(
	const unsigned char c,
	const MainMap& mainMap,
	R2D::InputManager& inputManager,
	R2D::Camera2D& camera,
	const R2D::Window& window
)
{
	if (c == 'X')
	{
		return
		(
			mainMap.GETtileSize()
			*
			MainMap::convertPosXToIndex
			(
				(double)inputManager.GETmouseCoords().x
				+ (double)camera.GETposition().x
				- (double)window.GETscreenWidth() / 2
			)
		);
	}
	else
	if (c == 'Y')
	{
		return
		(
			mainMap.GETtileSize()
			*
			MainMap::convertPosYToIndex
			(
				-(double)inputManager.GETmouseCoords().y
				+ (double)camera.GETposition().y
				+ (double)window.GETscreenHeight() / 2
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