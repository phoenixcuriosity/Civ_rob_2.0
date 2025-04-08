/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)

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

#ifndef GameInput_H
#define GameInput_H

#include <R2D/src/API_fwd.h>
#include <SDL/SDL.h>

#include <memory>
#include <string>
#include <vector>

 /* Define input from keyboard in a context */
enum class CinState_Type : unsigned int
{
	cinNothing,						/* Inputs from keyboards are discard */
	cinTitleScreen,					/* Inputs from keyboards are use in Title Screen */
	cinScreenNewGameNbPlayer,		/* Inputs from keyboards are use in New Game : for number of player */
	cinScreenNewGameNamePlayer,		/* Inputs from keyboards are use in New Game : for names of players */
	cinMainMap,						/* Inputs from keyboards are use in Main map */
};

class Player;
class Players;
class MainMap;
class Unit;
class GamePlayScreen;

class GameInput
{
private:
	using PlayerPtrT = std::shared_ptr<Player>;
	using UnitPtrT = std::shared_ptr<Unit>;

public:

	static void updateSDLInputCycle
	(
		SDL_Event& ev,
		R2D::InputManager& inputManager,
		R2D::Camera2D& camera,
		MainMap& mainMap,
		Players& players,
		const R2D::Window& window,
		int& nextScreenIndexMenu,
		R2D::ScreenState& currentState
	);
	static void processInput(GamePlayScreen& gamePlayScreen);

private:

	static void moveCameraByDeltaTime
	(
		R2D::InputManager& inputManager,
		R2D::Camera2D& camera,
		MainMap& mainMap,
		Players& players
	);

	static void moveCamera
	(
		const float deltaTime,
		R2D::InputManager& inputManager,
		R2D::Camera2D& camera,
		MainMap& mainMap,
		Players& players
	);

	static void updateDrawCameraMove
	(
		MainMap& mainMap,
		Players& players
	);

private:

	/* NAME : run_SDL																					    	  */
	/* ROLE : Recherche infini des �venements d'entr� de type SDL_event : souris, clavier					      */
	/* ROLE : Si aucun �venements n'est trouv� alors le programme continue									      */
	/* INPUT : struct Sysinfo& : structure globale du programme									    			  */
	/* RETURNED VALUE    : void																					  */
	static void inputSDL
	(
		SDL_Event& ev,
		R2D::InputManager& inputManager,
		R2D::Camera2D& camera,
		MainMap& mainMap,
		Players& players,
		const R2D::Window& window,
		int& nextScreenIndexMenu,
		R2D::ScreenState& currentState
	);

	/* NAME : actionByKey																				    	  */
	/* ROLE : Define action for each key press																      */
	/* INPUT : SDL_Event& ev : Event from SDL input												    			  */
	/* RETURNED VALUE    : void																					  */
	static void actionByKey(GamePlayScreen& gamePlayScreen);

	/* NAME : wheel																						    	  */
	/* ROLE : Recherche l'incr�mentation ou d�cr�mentation du contexte										      */
	/* INPUT : struct Sysinfo& : structure globale du programme												      */
	/* INPUT : int& wheel : l'�venement de scroll de la souris													  */
	/* RETURNED VALUE    : void																					  */
	static void wheel
	(
		const SDL_Event& ev,
		R2D::Camera2D& camera,
		MainMap& mainMap,
		Players& players
	);

	static void mouseClick
	(
		const SDL_Event& ev,
		R2D::InputManager& inputManager,
		R2D::Camera2D& camera,
		Players& players,
		const R2D::Window& window,
		int& nextScreenIndexMenu,
		R2D::ScreenState& currentState
	);

	static unsigned int getMouseCoorNorm
	(
		const unsigned char c,
		const MainMap& mainMap,
		R2D::InputManager& inputManager,
		R2D::Camera2D& camera,
		const R2D::Window& window
	);

};

#endif /* GameInput_H */

/*
*	End Of File : GameInput.h
*/
