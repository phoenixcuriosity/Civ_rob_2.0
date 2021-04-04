/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.7.0
	file version : 1.26

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
#include "GamePlayScreen.h"


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
void GamePlayScreen::inputSDL
(
	SDL_Event& ev
)
{
	switch (ev.type)
	{

	case SDL_KEYDOWN:
		m_inputManager->pressKey(ev.key.keysym.sym);
			
		break;
	case SDL_KEYUP:
		m_inputManager->releaseKey(ev.key.keysym.sym);
		break;
		/* ---------------------------------------------------------------------- */
		/* test sur le type d'�v�nement click souris (enfonc�)					  */
		/* ---------------------------------------------------------------------- */

	case SDL_MOUSEBUTTONDOWN:
		m_inputManager->pressKey(ev.button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		m_inputManager->releaseKey(ev.button.button);
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
		m_inputManager->setMouseCoords(ev.motion.x, ev.motion.y);
		break;

	default:
		/* N/A */
		break;
	}
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
	SDL_Event& ev
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
	if (MOUSE_SCROLL_UP == ev.wheel.y)
	{
		m_screen.camera
			.SETscale(m_screen.camera.GETscale()
						+ MOUSE_SCROLL_SPEED_PERC * m_screen.camera.GETscale());
	}
	else if (MOUSE_SCROLL_DOWN == ev.wheel.y)
	{
		m_screen.camera
			.SETscale(m_screen.camera.GETscale()
				- MOUSE_SCROLL_SPEED_PERC * m_screen.camera.GETscale());
	}
}

 /*
 *	End Of File : KeyboardMouse.cpp
 */