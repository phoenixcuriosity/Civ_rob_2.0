/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.22.0.0
	file version : 1.20

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

#include "KeyboardMouse.h"

#include "civ_lib.h"
#include "IHM.h"
#include "SaveReload.h"
#include "GamePlay.h"
#include "End.h"
#include "LoadConfig.h"
#include "Player.h"
#include "Utility.h"
#include "City.h"

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */

/* *********************************************************
 *					KeyboardMouse STATIC				   *
 ********************************************************* */


/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : checkCaseSDL																				    	  */
/* ROLE : Check du cas du type cinState, choix entre wait et run SDL event								      */
/* ROLE : Recherche les évenements d'entré de type SDL_event : souris, clavier							      */
/* INPUT : struct Sysinfo& : structure globale du programme									    			  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void KeyboardMouse::checkCaseSDL(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:

		break;
	case CinState_Type::cinTitleScreen:
		run_SDL(sysinfo);
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		wait_SDL(sysinfo);
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		wait_SDL(sysinfo);
		break;
	case CinState_Type::cinMainMap:
		run_SDL(sysinfo);
		break;
	default:
		/* N/A */
		break;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : wait_SDL																					    	  */
/* ROLE : Attente d'un évenement d'entrée de la SDL de type SDL_event : souris, clavier					      */
/* INPUT : struct Sysinfo& : structure globale du programme									    			  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void KeyboardMouse::wait_SDL(Sysinfo& sysinfo)
{
	SDL_Event event;
	while (sysinfo.var.waitEvent)
	{
		SDL_WaitEvent(&event);
		eventSDL(sysinfo, event);
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : run_SDL																					    	  */
/* ROLE : Recherche infini des évenements d'entré de type SDL_event : souris, clavier					      */
/* ROLE : Si aucun évenements n'est trouvé alors le programme continue									      */
/* INPUT : struct Sysinfo& : structure globale du programme									    			  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void KeyboardMouse::run_SDL(Sysinfo& sysinfo)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		eventSDL(sysinfo, event);
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : eventSDL																					    	  */
/* ROLE : Recherche d'entré de type SDL_event : souris, clavier											      */
/* INPUT : struct Sysinfo& : structure globale du programme									    			  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void KeyboardMouse::eventSDL(Sysinfo& sysinfo, SDL_Event event)
{
	switch (event.type)
	{

	/* ---------------------------------------------------------------------- */
	/* Permet de quitter le jeu												  */
	/* ---------------------------------------------------------------------- */
	case SDL_QUIT:
		sysinfo.var.continuer = 0;
		break;

	/* ---------------------------------------------------------------------- */
	/* Test sur le type d'événement touche enfoncé							  */
	/* ---------------------------------------------------------------------- */
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{


		/* ---------------------------------------------------------------------- */
		/* Specials Keys														  */
		/* ---------------------------------------------------------------------- */

		case SDLK_ESCAPE:
			keySDLK_ESCAPE();
			break;
		case SDLK_BACKSPACE:
			keySDLK_BACKSPACE(sysinfo);
			break;
		case SDLK_RETURN:
			keySDLK_RETURN(sysinfo);
			break;
		case SDLK_KP_ENTER:
			keySDLK_KP_ENTER(sysinfo);
			break;
		case SDLK_SPACE:
			keySDLK_SPACE(sysinfo);
			break;

		/* ---------------------------------------------------------------------- */
		/* F Keys																  */
		/* ---------------------------------------------------------------------- */

		case SDLK_F1:
			keySDLK_F1(sysinfo);
			break;
		case SDLK_F2:
			keySDLK_F2(sysinfo);
			break;
		case SDLK_F3:
			keySDLK_F3(sysinfo);
			break;
		case SDLK_F4:
			keySDLK_F4(sysinfo);
			break;
		case SDLK_F5:
			keySDLK_F5(sysinfo);
			break;
		case SDLK_F6:
			keySDLK_F6(sysinfo);
			break;
		case SDLK_F7:
			keySDLK_F7(sysinfo);
			break;
		case SDLK_F8:
			keySDLK_F8(sysinfo);
			break;
		case SDLK_F9:
			keySDLK_F9(sysinfo);
			break;
		case SDLK_F10:
			keySDLK_F10(sysinfo);
			break;
		case SDLK_F11:
			keySDLK_F11(sysinfo);
			break;
		case SDLK_F12:
			keySDLK_F12(sysinfo);
			break;

		/* ---------------------------------------------------------------------- */
		/* Arrow Keys															  */
		/* ---------------------------------------------------------------------- */

		case SDLK_UP:
			keySDLK_UP(sysinfo);
			break;
		case SDLK_LEFT:
			keySDLK_LEFT(sysinfo);
			break;
		case SDLK_DOWN:
			keySDLK_DOWN(sysinfo);
			break;
		case SDLK_RIGHT:
			keySDLK_RIGHT(sysinfo);
			break;

		/* ---------------------------------------------------------------------- */
		/* Alphabetic Keys														  */
		/* ---------------------------------------------------------------------- */

		case SDLK_a:
			keySDLK_a(sysinfo);
			break;
		case SDLK_b:
			keySDLK_b(sysinfo);
			break;
		case SDLK_c:
			keySDLK_c(sysinfo);
			break;
		case SDLK_d:
			keySDLK_d(sysinfo);
			break;
		case SDLK_e:
			keySDLK_e(sysinfo);
			break;
		case SDLK_f:
			keySDLK_f(sysinfo);
			break;
		case SDLK_g:
			keySDLK_g(sysinfo);
			break;
		case SDLK_h:
			keySDLK_h(sysinfo);
			break;
		case SDLK_i:
			keySDLK_i(sysinfo);
			break;
		case SDLK_j:
			keySDLK_j(sysinfo);
			break;
		case SDLK_k:
			keySDLK_k(sysinfo);
			break;
		case SDLK_l:
			keySDLK_l(sysinfo);
			break;
		case SDLK_m:
			keySDLK_m(sysinfo);
			break;
		case SDLK_n:
			keySDLK_n(sysinfo);
			break;
		case SDLK_o:
			keySDLK_o(sysinfo);
			break;
		case SDLK_p:
			keySDLK_p(sysinfo);
			break;
		case SDLK_q:
			keySDLK_q(sysinfo);
			break;
		case SDLK_r:
			keySDLK_r(sysinfo);
			break;
		case SDLK_s:
			keySDLK_s(sysinfo);
			break;
		case SDLK_t:
			keySDLK_t(sysinfo);
			break;
		case SDLK_u:
			keySDLK_u(sysinfo);
			break;
		case SDLK_v:
			keySDLK_v(sysinfo);
			break;
		case SDLK_w:
			keySDLK_w(sysinfo);
			break;
		case SDLK_x:
			keySDLK_x(sysinfo);
			break;
		case SDLK_y:
			keySDLK_y(sysinfo);
			break;
		case SDLK_z:
			keySDLK_z(sysinfo);
			break;

		/* ---------------------------------------------------------------------- */
		/* Numeric Keys															  */
		/* ---------------------------------------------------------------------- */

		case SDLK_KP_1:
			keySDLK_KP_1(sysinfo);
			break;
		case SDLK_KP_2:
			keySDLK_KP_2(sysinfo);
			break;
		case SDLK_KP_3:
			keySDLK_KP_3(sysinfo);
			break;
		case SDLK_KP_4:
			keySDLK_KP_4(sysinfo);
			break;
		case SDLK_KP_5:
			keySDLK_KP_5(sysinfo);
			break;
		case SDLK_KP_6:
			keySDLK_KP_6(sysinfo);
			break;
		case SDLK_KP_7:
			keySDLK_KP_7(sysinfo);
			break;
		case SDLK_KP_8:
			keySDLK_KP_8(sysinfo);
			break;
		case SDLK_KP_9:
			keySDLK_KP_9(sysinfo);
			break;
		default:
			/* N/A */
			break;
		}
		break;

	/* ---------------------------------------------------------------------- */
	/* test sur le type d'événement click souris (enfoncé)					  */
	/* ---------------------------------------------------------------------- */

	case SDL_MOUSEBUTTONDOWN:
		mouse(sysinfo, event);
		break;

	/* ---------------------------------------------------------------------- */
	/* test sur le type d'événement wheel									  */
	/* ---------------------------------------------------------------------- */

	case SDL_MOUSEWHEEL:
		wheel(sysinfo, event.wheel.y);
		break;

	/* ---------------------------------------------------------------------- */
	/* test sur le type d'événement motion									  */
	/* ---------------------------------------------------------------------- */

	case SDL_MOUSEMOTION:
		inspect(sysinfo, event);
		break;

	default:
		/* N/A */
		break;
	}
}





/* *********************************************************
 *		START KeyboardMouse::STATIC::UNE TOUCHE			   *
 ********************************************************* */



void KeyboardMouse::keySDLK_ESCAPE()
{
	End::exitError("[INFO]__: keySDLK_ESCAPE");
}
void KeyboardMouse::keySDLK_BACKSPACE(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		if (sysinfo.var.nbPlayer == 0)
		{
			sysinfo.var.nbPlayer = 1;
			IHM::refreshNbPlayerTxt
			(
				sysinfo.screen.renderer,
				sysinfo.allTextures.font,
				sysinfo.var
			);
		}
		sysinfo.var.waitEvent = false;
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		if (sysinfo.var.tempPlayerName.size() > 0)
		{
			sysinfo.var.tempPlayerName.pop_back();
			IHM::refreshNamePlayerTxt
			(
				sysinfo.screen.renderer,
				sysinfo.allTextures.font,
				sysinfo.var
			);
		}	
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_RETURN(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		if (sysinfo.var.nbPlayer == 0)
		{
			sysinfo.var.nbPlayer = 1;
			IHM::refreshNbPlayerTxt
			(
				sysinfo.screen.renderer,
				sysinfo.allTextures.font,
				sysinfo.var
			);
		}
		sysinfo.var.waitEvent = false;
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		if (sysinfo.var.tempPlayerName.compare("") == 0)
		{
			sysinfo.var.tempPlayerName = "NoName" + std::to_string(sysinfo.var.s_player.nbNoNamePlayer);
			sysinfo.var.s_player.nbNoNamePlayer++;
			IHM::refreshNamePlayerTxt
			(
				sysinfo.screen.renderer,
				sysinfo.allTextures.font,
				sysinfo.var
			);
		}
		sysinfo.var.waitEvent = false;
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_KP_ENTER(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		if (sysinfo.var.nbPlayer == 0)
		{
			sysinfo.var.nbPlayer = 1;
			IHM::refreshNbPlayerTxt
			(
				sysinfo.screen.renderer,
				sysinfo.allTextures.font,
				sysinfo.var
			);
		}
		sysinfo.var.waitEvent = false;
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		if (sysinfo.var.tempPlayerName.compare("") == 0)
		{
			sysinfo.var.tempPlayerName = "NoName" + std::to_string(sysinfo.var.s_player.nbNoNamePlayer);
			sysinfo.var.s_player.nbNoNamePlayer++;
			IHM::refreshNamePlayerTxt
			(
				sysinfo.screen.renderer,
				sysinfo.allTextures.font,
				sysinfo.var
			);
		}
		sysinfo.var.waitEvent = false;
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_SPACE(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		GamePlay::nextTurn(sysinfo);
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_F1(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_F2(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_F3(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_F4(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_F5(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		GamePlay::groundGen(sysinfo.map, sysinfo.screen.screenWidth);
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_F6(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		End::deletePlayer(sysinfo.tabplayer, "player");
		for (unsigned int i(0); i < 4; i++)
		{
			sysinfo.tabplayer.push_back(new Player("NoName" + std::to_string(i)));
		}
		GamePlay::newGameSettlerSpawn
		(
			sysinfo.var.s_player.tabUnit_Template,
			sysinfo.map,
			sysinfo.tabplayer
		);
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_F7(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_F8(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_F9(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_F10(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_F11(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_F12(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_UP(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		if (sysinfo.map.screenOffsetYIndexMin > 0)
		{
			sysinfo.map.screenOffsetYIndexMin--;
			sysinfo.map.screenOffsetYIndexMax--;
		}
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_LEFT(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		if (sysinfo.map.screenOffsetXIndexMin > 0)
		{
			sysinfo.map.screenOffsetXIndexMin--;
			sysinfo.map.screenOffsetXIndexMax--;
		}
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_DOWN(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		if (sysinfo.map.screenOffsetYIndexMax < sysinfo.map.maps[0].size())
		{
			sysinfo.map.screenOffsetYIndexMin++;
			sysinfo.map.screenOffsetYIndexMax++;
		}
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_RIGHT(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case CinState_Type::cinMainMap:
		if (sysinfo.map.screenOffsetXIndexMax < sysinfo.map.maps.size())
		{
			sysinfo.map.screenOffsetXIndexMin++;
			sysinfo.map.screenOffsetXIndexMax++;
		}
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_a(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'a';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_b(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'b';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		if (Utility::conditionTryToMove(sysinfo.var))
			City::createCity(sysinfo);
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_c(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'c';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_d(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'd';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_e(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'e';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_f(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'f';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_g(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'g';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_h(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'h';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_i(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'i';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		if (Utility::conditionTryToMove(sysinfo.var))
			Unit::irrigate(sysinfo);
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_j(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'j';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_k(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'k';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_l(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'l';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_m(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'm';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_n(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'n';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_o(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'o';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_p(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'p';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_q(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'q';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_r(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'r';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_s(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 's';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_t(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 't';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_u(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'u';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_v(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'v';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_w(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'w';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_x(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'x';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_y(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'y';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_z(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'z';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}


/*
* comm 0.14e : ce commentaire est commun au 9 boutons 
* NAME : keySDLK_KP_1
* ROLE : Appel la fonction dans le contexte de l'appuie sur la touche
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Appel une fonction
* RETURNED VALUE    : void
*/
void KeyboardMouse::keySDLK_KP_1(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 1;
		IHM::refreshNbPlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '1';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:

		if (Utility::conditionTryToMove(sysinfo.var))
		{
			Unit::tryToMove
			(
				sysinfo.map.maps,
				sysinfo.var.s_player,
				sysinfo.tabplayer,
				sysinfo.var.select,
				-(int)(sysinfo.map.tileSize),
				sysinfo.map.tileSize
			);
		}
			
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_KP_2(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 2;
		IHM::refreshNbPlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '2';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		if (Utility::conditionTryToMove(sysinfo.var))
		{
			Unit::tryToMove
			(
				sysinfo.map.maps,
				sysinfo.var.s_player,
				sysinfo.tabplayer,
				sysinfo.var.select,
				0,
				sysinfo.map.tileSize
			);
		}
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_KP_3(Sysinfo& sysinfo) 
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 3;
		IHM::refreshNbPlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '3';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:

		if (Utility::conditionTryToMove(sysinfo.var))
		{
			Unit::tryToMove
			(
				sysinfo.map.maps,
				sysinfo.var.s_player,
				sysinfo.tabplayer,
				sysinfo.var.select,
				sysinfo.map.tileSize,
				sysinfo.map.tileSize
			);
		}

		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_KP_4(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 4;
		IHM::refreshNbPlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '4';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:

		if (Utility::conditionTryToMove(sysinfo.var))
		{
			Unit::tryToMove
			(
				sysinfo.map.maps,
				sysinfo.var.s_player,
				sysinfo.tabplayer,
				sysinfo.var.select,
				-(int)sysinfo.map.tileSize,
				0
			);
		}

		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_KP_5(Sysinfo& sysinfo) 
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 5;
		IHM::refreshNbPlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '5';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:
		/* N/A */
		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_KP_6(Sysinfo& sysinfo) 
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 6;
		IHM::refreshNbPlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '6';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:

		if (Utility::conditionTryToMove(sysinfo.var))
		{
			Unit::tryToMove
			(
				sysinfo.map.maps,
				sysinfo.var.s_player,
				sysinfo.tabplayer,
				sysinfo.var.select,
				sysinfo.map.tileSize,
				0
			);
		}

		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_KP_7(Sysinfo& sysinfo) 
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 7;
		IHM::refreshNbPlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '7';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:

		if (Utility::conditionTryToMove(sysinfo.var))
		{
			Unit::tryToMove
			(
				sysinfo.map.maps,
				sysinfo.var.s_player,
				sysinfo.tabplayer,
				sysinfo.var.select,
				-(int)sysinfo.map.tileSize,
				-(int)sysinfo.map.tileSize
			);
		}

		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_KP_8(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 8;
		IHM::refreshNbPlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '8';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:

		if (Utility::conditionTryToMove(sysinfo.var))
		{
			Unit::tryToMove
			(
				sysinfo.map.maps,
				sysinfo.var.s_player,
				sysinfo.tabplayer,
				sysinfo.var.select,
				0,
				-(int)sysinfo.map.tileSize
			);
		}


		break;
	default:
		/* N/A */
		break;
	}
}
void KeyboardMouse::keySDLK_KP_9(Sysinfo& sysinfo) 
{
	switch (sysinfo.var.cinState)
	{
	case CinState_Type::cinNothing:
		/* N/A */
		break;
	case CinState_Type::cinTitleScreen:
		/* N/A */
		break;
	case CinState_Type::cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 9;
		IHM::refreshNbPlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '9';
		IHM::refreshNamePlayerTxt
		(
			sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var
		);
		break;
	case CinState_Type::cinMainMap:

		if (Utility::conditionTryToMove(sysinfo.var))
		{
			Unit::tryToMove
			(
				sysinfo.map.maps,
				sysinfo.var.s_player,
				sysinfo.tabplayer,
				sysinfo.var.select,
				sysinfo.map.tileSize,
				-(int)sysinfo.map.tileSize
			);
		}


		break;
	default:
		/* N/A */
		break;
	}
}


/* *********************************************************
 *			END KeyboardMouse::STATIC::UNE TOUCHE		   *
 ********************************************************* */


 

/* *********************************************************
 *			START KeyboardMouse::STATIC::SOURIS		       *
 ********************************************************* */


/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : mouse																						    	  */
/* ROLE : Dispatch entre clique droit ou clique gauche													      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
/* INPUT : SDL_Event : l'évenement du clique			    												  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void KeyboardMouse::mouse
(
	Sysinfo& sysinfo,
	SDL_Event event
)
{
	/*

		Handle Mouse Event
		BUTTON_LEFT
		BUTTON_RIGHT

	*/
	sysinfo.var.mouse.refreshMousePos
	(
		event.button.x,
		event.button.y,
		sysinfo.map.tileSize,
		sysinfo.map.screenOffsetXIndexMin,
		sysinfo.map.screenOffsetYIndexMin
	);

	if (SDL_BUTTON_LEFT == event.button.button)
	{
		cliqueGauche(sysinfo, event);
	}
	else
	if (
			SDL_BUTTON_RIGHT == event.button.button
			&&
			State_Type::STATEmainMap == sysinfo.var.statescreen
	   )
	{
		cliqueDroit(sysinfo);
	}
	else
	{
		/* N/A */
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : cliqueGauche																				    	  */
/* ROLE : Recherche de la zone ou le clique à lieu sur chaque case de STATE								      */
/* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)							      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme											  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void KeyboardMouse::cliqueGauche
(
	Sysinfo& sysinfo,
	SDL_Event event
) 
{
	// recherche du bouton par comparaison de string et des positions x et y du clic
	switch (sysinfo.var.statescreen)
	{
	case State_Type::STATEmainMap:
		
		if (checkSTATEmainmap(sysinfo)) return;

		if (ONE_CLICK == event.button.clicks)
		{
			if (Unit::searchUnitTile(sysinfo.var.s_player, sysinfo.var.mouse, sysinfo.tabplayer, &sysinfo.var.select)) return;
		}
		else if(TWO_CLICKS == event.button.clicks)
		{
			if (inspectCitie(sysinfo.tabplayer, sysinfo.var)) return;
		}
		else
		{
			/* N/A */
		}
		
		break;
	case State_Type::STATEtitleScreen:

		if (checkSTATEtitleScreen(sysinfo)) return;

		break;
	case State_Type::STATEreload:

		if (checkSTATEreload(sysinfo)) return;

		break;
	case State_Type::STATEcityMap:

		if (checkSTATEcitiemap(sysinfo)) return;

		break;
	default:
		/* N/A */
		/* TODO ERROR */
		break;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : checkSTATEmainmap																			    	  */
/* ROLE : Recherche de la zone ou le clique à lieu sur STATEmainmap										      */
/* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)							      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme											  */
/* RETURNED VALUE : bool -> false : aucun boutons ou fonctions utilisés										  */
/* RETURNED VALUE : bool -> true : un bouton ou une fonction utilisé										  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
bool KeyboardMouse::checkSTATEmainmap
(
	Sysinfo& sysinfo
)
{
	if (sysinfo.allButton.mainMap["screen Titre"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		sysinfo.var.cinState = CinState_Type::cinTitleScreen;
		SaveReload::save(sysinfo);
		resetButtonOn(sysinfo);
		LoadConfig::logfileconsole("__________________________");
		IHM::titleScreen(sysinfo);
		return true;
	}


#ifdef _DEBUG_MODE
	if (sysinfo.allButton.mainMap["Create Unit"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		sysinfo.allButton.mainMap["Create Unit"]->changeOn();
		if (sysinfo.var.select != Select_Type::selectcreate)
			sysinfo.var.select = Select_Type::selectcreate;
		else
			sysinfo.var.select = Select_Type::selectnothing;

		resetButtonOn(sysinfo);
		return true;
	}
	if (sysinfo.allButton.mainMap["Delete Unit"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		sysinfo.allButton.mainMap["Delete Unit"]
			->SETon(!sysinfo.allButton.mainMap["Delete Unit"]
				->GETon());
		resetButtonOn(sysinfo);
		return true;
	}
#endif // DEBUG_MODE
	
	if (sysinfo.allButton.mainMap["Next Turn"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		GamePlay::nextTurn(sysinfo);
		resetButtonOn(sysinfo);
		return true;
	}
	

	{
		unsigned int i(0);
		for (const auto& n : sysinfo.allButton.player)
		{
			if (sysinfo.allButton.player[n.second->GETname()]
					->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
			{

				Unit::resetShowWhenChangePU
				(
					sysinfo.tabplayer,
					sysinfo.var.s_player.selectplayer,
					sysinfo.var.s_player.selectunit
				);


				sysinfo.allButton.player[n.second->GETname()]->changeOn();
				if (sysinfo.var.s_player.selectplayer != (int)i)
					sysinfo.var.s_player.selectplayer = (int)i;
				else
					sysinfo.var.s_player.selectplayer = NO_PLAYER_SELECTED;
				LoadConfig::logfileconsole("sysinfo.var.selectplayer = " + sysinfo.tabplayer[i]->GETname());
				resetButtonPlayerOn(sysinfo);
				return true;
			}
			i++;
		}
	}
	return false;
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : inspectCitie																				    	  */
/* ROLE : Recherche de la position de la Citie sur tous les joueurs										      */
/* ROLE : Si aucun joueur n'existe la Citie ne peut pas etre trouvée									      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme											  */
/* RETURNED VALUE : bool -> false : la Citie n'est enregistrée chez aucun joueur ou il n'y aucun joueur		  */
/* RETURNED VALUE : bool -> true : la Citie est enregistrée chez joueur (et existance dui joueur)			  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
bool KeyboardMouse::inspectCitie
(
	const TabPlayer& tabplayer,
	Var& var
)
{
	if (NO_PLAYER_SELECTED < var.s_player.selectplayer)
	{
		if (!tabplayer[var.s_player.selectplayer]->GETtabCity().empty())
		{
			City::searchCityTile(tabplayer, var);
			return true;
		}
	}
	return false;
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : checkSTATEtitleScreen																		    	  */
/* ROLE : Recherche de la zone ou le clique à lieu sur STATEtitleScreen									      */
/* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)							      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme											  */
/* RETURNED VALUE : bool -> false : aucun boutons ou fonctions utilisés										  */
/* RETURNED VALUE : bool -> true : un bouton ou une fonction utilisé										  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
bool KeyboardMouse::checkSTATEtitleScreen
(
	Sysinfo& sysinfo
)
{
	if (sysinfo.allButton.titleScreen["New Game"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		GamePlay::newGame(sysinfo);
		return true;
	}
	if (sysinfo.allButton.titleScreen["Reload"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		IHM::reloadScreen(sysinfo);
		return true;
	}
	if (sysinfo.allButton.titleScreen["Option"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		//clearSave(sysinfo);
		return true;
	}
	if (sysinfo.allButton.titleScreen["Quit"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		sysinfo.var.continuer = false;
		return true;
	}
	return false;
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : checkSTATEreload																			    	  */
/* ROLE : Recherche de la zone ou le clique à lieu sur STATEreload										      */
/* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)							      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme											  */
/* RETURNED VALUE : bool -> false : aucun boutons ou fonctions utilisés										  */
/* RETURNED VALUE : bool -> true : un bouton ou une fonction utilisé										  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
bool KeyboardMouse::checkSTATEreload
(
	Sysinfo& sysinfo
)
{
	if (sysinfo.allButton.reload["Back"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		IHM::titleScreen(sysinfo);
		return true;
	}
	if (sysinfo.allButton.reload["Remove all saves"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		sysinfo.allButton.reload["Remove all saves"]
			->changeOn();
		SaveReload::clearSave(sysinfo);
		IHM::reloadScreen(sysinfo);
		return true;
	}
	if (sysinfo.allButton.reload["Load"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		if (sysinfo.var.save.GETcurrentSave() > NO_CURRENT_SAVE_SELECTED)
		{
			SaveReload::reload(sysinfo);
		}
		return true;
	}
	if (sysinfo.allButton.reload["Remove"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		SaveReload::removeSave(sysinfo);
		IHM::reloadScreen(sysinfo);
		return true;
	}

	for (unsigned int j(0); j < sysinfo.var.save.GETnbSave(); j++)
	{
		if (sysinfo.allButton.reload["Save : " + std::to_string(sysinfo.var.save.GETtabSave()[j])]
				->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
		{
			sysinfo.allButton.reload["Save : " + std::to_string(sysinfo.var.save.GETtabSave()[j])]
				->changeOn();
			sysinfo.var.save.SETcurrentSave(sysinfo.var.save.GETtabSave()[j]);
			sysinfo.file.saveMaps = "save/" + std::to_string(sysinfo.var.save.GETtabSave()[j]) + "/saveMaps.txt";
			sysinfo.file.savePlayers = "save/" + std::to_string(sysinfo.var.save.GETtabSave()[j]) + "/savePlayers.xml";
			IHM::reloadScreen(sysinfo);
			return true;
		}
	}
	return false;
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : checkSTATEcitiemap																		    	  */
/* ROLE : Recherche de la zone ou le clique à lieu sur STATEcitiemap									      */
/* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)							      */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme											  */
/* RETURNED VALUE : bool -> false : aucun boutons ou fonctions utilisés										  */
/* RETURNED VALUE : bool -> true : un bouton ou une fonction utilisé										  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
bool KeyboardMouse::checkSTATEcitiemap
(
	Sysinfo& sysinfo
)
{
	if (sysinfo.allButton.cityMap["Map"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		sysinfo.var.s_player.selectCity = NO_CITY_SELECTED;
		sysinfo.var.statescreen = State_Type::STATEmainMap;
		sysinfo.var.select = Select_Type::selectnothing;
		resetButtonCitieMap(sysinfo);
		return true;
	}
	if (sysinfo.allButton.cityMap["Build"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		sysinfo.allButton.cityMap["Build"]
			->changeOn();
		if (sysinfo.var.select != Select_Type::selectcreate)
			sysinfo.var.select = Select_Type::selectcreate;
		else
			sysinfo.var.select = Select_Type::selectnothing;
		resetButtonCitieMap(sysinfo);
		return true;
	}
	if (sysinfo.allButton.cityMap["Place Citizen"]
			->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
	{
		sysinfo.allButton.cityMap["Place Citizen"]
			->changeOn();
		if (sysinfo.var.select != Select_Type::selectmoveCitizen)
			sysinfo.var.select = Select_Type::selectmoveCitizen;
		else
			sysinfo.var.select = Select_Type::selectnothing;
		resetButtonCitieMap(sysinfo);
		return true;
	}

	for (
			unsigned int i(0);
			i < sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheCity(sysinfo.var.s_player.selectCity)->GETbuildQueue().buildQueue.size();
			i++
		)
	{
		if	(
				sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
					->GETtheCity(sysinfo.var.s_player.selectCity)
						->GETbuildQueue()
							.cityMapBuildQueue[i]
								->searchButtonTexte
						(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y())
			)
		{
			sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
				->GETtheCity(sysinfo.var.s_player.selectCity)
					->removeBuildToQueue(i);
			return true;
		}
	}


	if (Select_Type::selectcreate == sysinfo.var.select)
	{
		for (unsigned int i(0); i < sysinfo.var.s_player.tabUnit_Template.size(); i++)
		{
			if (sysinfo.allButton.cityMap[sysinfo.var.s_player.tabUnit_Template[i].name]
					->searchButtonTexte(sysinfo.var.statescreen, sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
			{
				sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
					->GETtheCity(sysinfo.var.s_player.selectCity)
						->addBuildToQueue
							(
								{
									sysinfo.var.s_player.tabUnit_Template[i].name,
									build_Type::unit,
									sysinfo.var.s_player.tabUnit_Template[i].workToBuild
								},
								sysinfo.screen.renderer,
								sysinfo.allTextures.font
							);

				sysinfo.var.select = Select_Type::selectnothing;
				return true;
			}
		}
	}
	return false;
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : cliqueDroit																				    	  */
/* ROLE : Recherche de la zone ou le clique à lieu														      */
/* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)							      */
/* INPUT : struct Sysinfo& : structure globale du programme													  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void KeyboardMouse::cliqueDroit
(
	Sysinfo& sysinfo
)
{
	if (NO_PLAYER_SELECTED < sysinfo.var.s_player.selectplayer)
	{
		switch (sysinfo.var.statescreen)
		{
		case State_Type::STATEmainMap:
			switch (sysinfo.var.select) 
			{
			case Select_Type::selectcreate:

				int selectunit(NO_UNIT_SELECTED);
				for (unsigned int p(0); (p < sysinfo.var.s_player.tabUnit_Template.size()) && (NO_UNIT_SELECTED == selectunit); p++)
				{
					if (sysinfo.var.s_player.unitNameToCreate.compare(sysinfo.var.s_player.tabUnit_Template[p].name) == 0)
					{
						selectunit = p;
					}
				}
				sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->addUnit
				(sysinfo.var.s_player.unitNameToCreate,
					sysinfo.var.mouse.GETmouse_xNormalized(), sysinfo.var.mouse.GETmouse_yNormalized(),
					sysinfo.var.s_player.tabUnit_Template[selectunit].type,
					sysinfo.var.s_player.tabUnit_Template[selectunit].life, sysinfo.var.s_player.tabUnit_Template[selectunit].atq,
					sysinfo.var.s_player.tabUnit_Template[selectunit].def, sysinfo.var.s_player.tabUnit_Template[selectunit].movement,
					sysinfo.var.s_player.tabUnit_Template[selectunit].level
				);
				break;
			}
			break;
		}
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : wheel																						    	  */
/* ROLE : Recherche l'incrémentation ou décrémentation du contexte										      */
/* INPUT : struct Sysinfo& : structure globale du programme												      */
/* INPUT : int& wheel : l'évenement de scroll de la souris													  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void KeyboardMouse::wheel(Sysinfo& sysinfo, int& wheel)
{
	if (Select_Type::selectcreate == sysinfo.var.select)
	{
		if (MOUSE_SCROLL_UP == wheel)
		{
			if (sysinfo.var.s_player.unitToCreate > 0)
				sysinfo.var.s_player.unitToCreate--;
		}
		else if (MOUSE_SCROLL_DOWN == wheel)
		{
			if (sysinfo.var.s_player.unitToCreate < sysinfo.var.s_player.tabUnit_Template.size() - 1)
				sysinfo.var.s_player.unitToCreate++;
		}
		Unit::searchUnit(sysinfo.var.s_player);
	}
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
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : resetButtonOn																				    	  */
/* ROLE : reset de l'affichage On des boutons															      */
/* INPUT : struct Sysinfo& : structure globale du programme												      */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void KeyboardMouse::resetButtonOn(Sysinfo& sysinfo)
{
	for (const auto& n : sysinfo.allButton.mainMap)
	{
		n.second->resetOnstateScreen(sysinfo.var.select);
		n.second->resetOnPlayer(sysinfo.var.s_player.selectplayer, sysinfo.var.s_player.tabPlayerName);
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : resetButtonPlayerOn																		    	  */
/* ROLE : reset de l'affichage On des boutons player													      */
/* INPUT : struct Sysinfo& : structure globale du programme												      */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void KeyboardMouse::resetButtonPlayerOn(Sysinfo& sysinfo)
{
	for (const auto& n : sysinfo.allButton.player)
	{
		n.second->resetOnstateScreen(sysinfo.var.select);
		n.second->resetOnPlayer(sysinfo.var.s_player.selectplayer, sysinfo.var.s_player.tabPlayerName);
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : resetButtonCitieMap																		    	  */
/* ROLE : reset de l'affichage On des boutons citieMap													      */
/* INPUT : struct Sysinfo& : structure globale du programme												      */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void KeyboardMouse::resetButtonCitieMap(Sysinfo& sysinfo)
{
	for (const auto& n : sysinfo.allButton.cityMap)
	{
		n.second->resetOnstateScreen(sysinfo.var.select);
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : inspect																					    	  */
/* ROLE : Inspect les cases survolées par la souris par la SDL_MOUSE_MOTION								      */
/* ROLE : Attention fonction appélée à chaque actions de la souris (potentiellement toutes les frames)	      */
/* INPUT : struct Sysinfo& : structure globale du programme												      */
/* INPUT : SDL_Event : l'évenement du clique			    												  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void KeyboardMouse::inspect
(
	Sysinfo& sysinfo,
	SDL_Event event
)
{
	switch (sysinfo.var.statescreen)
	{
	case State_Type::STATEmainMap:

		sysinfo.var.mouse.refreshMousePos
		(
			event.button.x,
			event.button.y,
			sysinfo.map.tileSize,
			sysinfo.map.screenOffsetXIndexMin,
			sysinfo.map.screenOffsetYIndexMin
		);


		if  (
				sysinfo.var.mouse.GETmouse_xNormalized()
				>
				(	
					sysinfo.map.screenOffsetXIndexMin * sysinfo.map.tileSize
					+ 
					(sysinfo.map.toolBarSize - 1) * sysinfo.map.tileSize
				)
			)
		{
			for (unsigned int selectedPlayer(0); selectedPlayer < sysinfo.tabplayer.size(); selectedPlayer++)
			{
				for (unsigned int i(0); i < sysinfo.tabplayer[selectedPlayer]->GETtabUnit().size(); i++)
				{
					if (sysinfo.tabplayer[selectedPlayer]->GETtheUnit(i)->testPos
							(sysinfo.var.mouse.GETmouse_xNormalized(), sysinfo.var.mouse.GETmouse_yNormalized())
						)
					{
						sysinfo.tabplayer[selectedPlayer]->GETtheUnit(i)->SETshowStats(true);
						return;
					}
					else
					{
						sysinfo.tabplayer[selectedPlayer]->GETtheUnit(i)->SETshowStats(false);
					}
				}
			}
		}
		else
		{
			if (NO_PLAYER_SELECTED < sysinfo.var.s_player.selectplayer)
			{
				if (sysinfo.var.mouse.GETmouse_y() > 900 && sysinfo.var.mouse.GETmouse_y() < 924)
				{
					sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
						->GETonOffDisplay().showContextGoldStats = true;
				}
				else
				{
					sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
						->GETonOffDisplay().showContextGoldStats = false;
				}

			}
		}
		
		break;
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
/* ROLE : Constructeur par défaut de la classe KeyboardMouse											      */
/* INPUT : void																							      */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
KeyboardMouse::KeyboardMouse()
: _mouse_x(0), _mouse_y(0), _mouse_xNormalized(0), _mouse_yNormalized(0), _ywheel(0), _xwheel(0)
{
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : refreshMousePos																			    	  */
/* ROLE : Inspect les cases survolées par la souris par la SDL_MOUSE_MOTION								      */
/* INPUT : Sint32 x	: position en x de la souris selon SDL												      */
/* INPUT : Sint32 y	: position en y de la souris selon SDL												      */
/* INPUT : unsigned int tileSize : taille d'une tile													      */
/* INPUT : unsigned int screenOffsetXIndexMin : offset en pixel sur l'axe X								      */
/* INPUT : unsigned int screenOffsetYIndexMin : offset en pixel sur l'axe Y									  */
/* RETURNED VALUE    : void																					  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
void KeyboardMouse::refreshMousePos
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