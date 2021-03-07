/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.2.0
	file version : 1.24

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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "GameInput.h"

#include "MainGame.h"


 /* *********************************************************
  *						 Classes						   *
  ********************************************************* */

  /* *********************************************************
   *					KeyboardMouse STATIC				   *
   ********************************************************* */


   
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : run_SDL																					    	  */
/* ROLE : Recherche infini des �venements d'entr� de type SDL_event : souris, clavier					      */
/* ROLE : Si aucun �venements n'est trouv� alors le programme continue									      */
/* INPUT : struct Sysinfo& : structure globale du programme									    			  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void GameInput::inputSDL(MainGame& mainGame)
{
	while (SDL_PollEvent(&mainGame.GETscreen().evnt))
	{
		switch (mainGame.GETscreen().evnt.type)
		{

			/* ---------------------------------------------------------------------- */
			/* Permet de quitter le jeu												  */
			/* ---------------------------------------------------------------------- */
		case SDL_QUIT:
			mainGame.GETvar().continuer = 0;
			break; 
		

			/* ---------------------------------------------------------------------- */
			/* Test sur le type d'�v�nement touche enfonc�							  */
			/* ---------------------------------------------------------------------- */
		case SDL_KEYDOWN:
			mainGame.GETscreen().openGLScreen.inputManager
				.pressKey(mainGame.GETscreen().evnt.key.keysym.sym);
			
			break;
		case SDL_KEYUP:
			mainGame.GETscreen().openGLScreen.inputManager
				.releaseKey(mainGame.GETscreen().evnt.key.keysym.sym);
			break;
			/* ---------------------------------------------------------------------- */
			/* test sur le type d'�v�nement click souris (enfonc�)					  */
			/* ---------------------------------------------------------------------- */
		case SDL_TEXTEDITING:

			break;
		case SDL_TEXTINPUT:
			mainGame.GETvar().nbturn++;
			mainGame.GETvar().tempPlayerName += mainGame.GETscreen().evnt.text.text;
			break;

		case SDL_MOUSEBUTTONDOWN:
			mainGame.GETscreen().openGLScreen.inputManager
				.releaseKey(mainGame.GETscreen().evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			mainGame.GETscreen().openGLScreen.inputManager
				.releaseKey(mainGame.GETscreen().evnt.button.button);
			break;

			/* ---------------------------------------------------------------------- */
			/* test sur le type d'�v�nement wheel									  */
			/* ---------------------------------------------------------------------- */

		case SDL_MOUSEWHEEL:
			wheel(mainGame);
			break;

			/* ---------------------------------------------------------------------- */
			/* test sur le type d'�v�nement motion									  */
			/* ---------------------------------------------------------------------- */

		case SDL_MOUSEMOTION:
			mainGame.GETscreen().openGLScreen.inputManager
				.setMouseCoords(mainGame.GETscreen().evnt.motion.x, mainGame.GETscreen().evnt.motion.y);
			break;

		default:
			/* N/A */
			break;
		}
	}

	if (mainGame.GETscreen().openGLScreen.inputManager.isKeyDown(SDLK_ESCAPE))
	{
		keySDLK_ESCAPE();
	}
	if (mainGame.GETscreen().openGLScreen.inputManager.isKeyDown(SDLK_z))
	{
		mainGame.GETscreen().openGLScreen.camera
			.SETposition
			(
				mainGame.GETscreen().openGLScreen.camera.GETposition()
				+
				glm::vec2(0.0f, KEY_SPEED_MOVE)
			);
	}
	if (mainGame.GETscreen().openGLScreen.inputManager.isKeyDown(SDLK_s))
	{
		mainGame.GETscreen().openGLScreen.camera
			.SETposition
			(
				mainGame.GETscreen().openGLScreen.camera.GETposition()
				+
				glm::vec2(0.0f, -KEY_SPEED_MOVE)
			);
	}
	if (mainGame.GETscreen().openGLScreen.inputManager.isKeyDown(SDLK_q))
	{
		mainGame.GETscreen().openGLScreen.camera
			.SETposition
			(
				mainGame.GETscreen().openGLScreen.camera.GETposition()
				+
				glm::vec2(-KEY_SPEED_MOVE, 0.0f)
			);
	}
	if (mainGame.GETscreen().openGLScreen.inputManager.isKeyDown(SDLK_d))
	{
		mainGame.GETscreen().openGLScreen.camera
			.SETposition
			(
				mainGame.GETscreen().openGLScreen.camera.GETposition()
				+
				glm::vec2(KEY_SPEED_MOVE, 0.0f)
			);
	}

	if (mainGame.GETscreen().openGLScreen.inputManager.isKeyDown(SDL_BUTTON_LEFT))
	{
		
	}
	if (mainGame.GETscreen().openGLScreen.inputManager.isKeyDown(SDL_BUTTON_RIGHT))
	{

	}

}

/* *********************************************************
 *		START KeyboardMouse::STATIC::UNE TOUCHE			   *
 ********************************************************* */



void GameInput::keySDLK_ESCAPE()
{
	MainGame::exitError("[INFO]__: keySDLK_ESCAPE");
}

 /* *********************************************************
  *			START KeyboardMouse::STATIC::SOURIS		       *
  ********************************************************* */


  /* ---------------------------------------------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------------------------------------------- */
  /* NAME : mouse																						    	  */
  /* ROLE : Dispatch entre clique droit ou clique gauche													      */
  /* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
  /* INPUT : SDL_Event : l'�venement du clique			    												  */
  /* RETURNED VALUE    : void																					  */
  /* ---------------------------------------------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------------------------------------------- */
void GameInput::mouse
(
	MainGame& mainGame
)
{
	/*

		Handle Mouse Event
		BUTTON_LEFT
		BUTTON_RIGHT

	*/

	if (SDL_BUTTON_LEFT == mainGame.GETscreen().evnt.button.button)
	{
		cliqueGauche(mainGame);
	}
	else
		if (
			SDL_BUTTON_RIGHT == mainGame.GETscreen().evnt.button.button
			&&
			State_Type::STATEmainMap == mainGame.GETvar().statescreen
			)
		{
			cliqueDroit(mainGame);
		}
		else
		{
			/* N/A */
		}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : cliqueGauche																				    	  */
/* ROLE : Recherche de la zone ou le clique � lieu sur chaque case de STATE								      */
/* ROLE : En fonction de la zone touch�e une action peut avoir lieu (boutons)							      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme											  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void GameInput::cliqueGauche
(
	MainGame& mainGame
)
{
	
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : cliqueDroit																				    	  */
/* ROLE : Recherche de la zone ou le clique � lieu														      */
/* ROLE : En fonction de la zone touch�e une action peut avoir lieu (boutons)							      */
/* INPUT : struct Sysinfo& : structure globale du programme													  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void GameInput::cliqueDroit
(
	MainGame& mainGame
)
{
	/*
	if (NO_PLAYER_SELECTED < mainGame.GETvar().s_player.selectplayer)
	{
		switch (mainGame.GETvar().statescreen)
		{
		case State_Type::STATEmainMap:
			switch (mainGame.GETvar().select)
			{
			case Select_Type::selectcreate:

				int selectunit(NO_UNIT_SELECTED);
				for (unsigned int p(0); (p < mainGame.GETvar().s_player.tabUnit_Template.size()) && (NO_UNIT_SELECTED == selectunit); p++)
				{
					if (mainGame.GETvar().s_player.unitNameToCreate.compare(mainGame.GETvar().s_player.tabUnit_Template[p].name) == 0)
					{
						selectunit = p;
					}
				}
				mainGame.GETvectPlayer()[mainGame.GETvar().s_player.selectplayer]->addUnit
				(mainGame.GETvar().s_player.unitNameToCreate,
					mainGame.GETgameInput().GETmouse_xNormalized(), mainGame.GETgameInput().GETmouse_yNormalized(),
					mainGame.GETvar().s_player.tabUnit_Template[selectunit].type,
					mainGame.GETvar().s_player.tabUnit_Template[selectunit].life, mainGame.GETvar().s_player.tabUnit_Template[selectunit].atq,
					mainGame.GETvar().s_player.tabUnit_Template[selectunit].def, mainGame.GETvar().s_player.tabUnit_Template[selectunit].movement,
					mainGame.GETvar().s_player.tabUnit_Template[selectunit].level, mainGame.GETvar().s_player.tabUnit_Template[selectunit].maintenance
				);
				break;
			}
			break;
		}
	}
	*/
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
void GameInput::wheel(MainGame& mainGame)
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
	if (MOUSE_SCROLL_UP == mainGame.GETscreen().evnt.wheel.y)
	{
		mainGame.GETscreen().openGLScreen.camera
			.SETscale(mainGame.GETscreen().openGLScreen.camera.GETscale()
						+ MOUSE_SCROLL_SPEED_PERC * mainGame.GETscreen().openGLScreen.camera.GETscale());
	}
	else if (MOUSE_SCROLL_DOWN == mainGame.GETscreen().evnt.wheel.y)
	{
		mainGame.GETscreen().openGLScreen.camera
			.SETscale(mainGame.GETscreen().openGLScreen.camera.GETscale() 
				- MOUSE_SCROLL_SPEED_PERC * mainGame.GETscreen().openGLScreen.camera.GETscale());
	}
}



/* *********************************************************
 *			END KeyboardMouse::STATIC::SOURIS			   *
 ********************************************************* */



 /* *********************************************************
  *				START KeyboardMouse::METHODS			   *
  ********************************************************* */


/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : KeyboardMouse																				    	  */
/* ROLE : Constructeur par d�faut de la classe KeyboardMouse											      */
/* INPUT : void																							      */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
GameInput::GameInput()
: _mouse_x(0), _mouse_y(0), _mouse_xNormalized(0), _mouse_yNormalized(0), _ywheel(0), _xwheel(0)
{
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : refreshMousePos																			    	  */
/* ROLE : Inspect les cases survol�es par la souris par la SDL_MOUSE_MOTION								      */
/* INPUT : Sint32 x	: position en x de la souris selon SDL												      */
/* INPUT : Sint32 y	: position en y de la souris selon SDL												      */
/* INPUT : unsigned int tileSize : taille d'une tile													      */
/* INPUT : unsigned int screenOffsetXIndexMin : offset en pixel sur l'axe X								      */
/* INPUT : unsigned int screenOffsetYIndexMin : offset en pixel sur l'axe Y									  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void GameInput::refreshMousePos
(
	Sint32 x,
	Sint32 y,
	unsigned int tileSize,
	unsigned int screenOffsetXIndexMin,
	unsigned int screenOffsetYIndexMin
)
{
	_mouse_x = x;
	_mouse_y = y;
	_mouse_xNormalized = ((unsigned int)ceil(x / tileSize) * tileSize) + (screenOffsetXIndexMin * tileSize);
	_mouse_yNormalized = ((unsigned int)ceil(y / tileSize) * tileSize) + (screenOffsetYIndexMin * tileSize);
}


/* *********************************************************
 *				END KeyboardMouse::METHODS				   *
 ********************************************************* */

 /*
 *	End Of File : KeyboardMouse.cpp
 */