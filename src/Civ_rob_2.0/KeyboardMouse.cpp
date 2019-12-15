/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.18
	file version : 1.10

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

#include "KeyboardMouse.h"
#include "civ_lib.h"
#include "IHM.h"
#include "SaveReload.h"
#include "GamePlay.h"
#include "End.h"


/*
* NAME : eventSDL
* ROLE : Recherche infini des évenements d'entré de type SDL_event : souris, clavier
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : évenements d'entré utilisateur
* RETURNED VALUE    : void
*/
void KeyboardMouse::eventSDL(Sysinfo& sysinfo)
{
	switch (sysinfo.var.cinState)
	{
	case cinNothing:

		break;
	case cinTitleScreen:
		run_SDL(sysinfo);
		break;
	case cinScreenNewGameNbPlayer:
		wait_SDL(sysinfo);
		break;
	case cinScreenNewGameNamePlayer:
		wait_SDL(sysinfo);
		break;
	case cinMainMap:
		run_SDL(sysinfo);
		break;
	default:
		/* N/A */
		break;
	}
}

void KeyboardMouse::wait_SDL(Sysinfo& sysinfo)
{
	SDL_Event event;
	while (sysinfo.var.waitEvent)
	{
		SDL_WaitEvent(&event);
		eventSDL_bis(sysinfo, event);
	}
}
void KeyboardMouse::run_SDL(Sysinfo& sysinfo)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		eventSDL_bis(sysinfo, event);
	}
}

void KeyboardMouse::eventSDL_bis(Sysinfo& sysinfo, SDL_Event event)
{
	switch (event.type)
	{
	case SDL_QUIT:	// permet de quitter le jeu
		sysinfo.var.continuer = 0;
		break;
	case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
		switch (event.key.keysym.sym)
		{




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
	case SDL_MOUSEBUTTONDOWN: // test sur le type d'événement click souris (enfoncé)
		mouse(sysinfo, event);
		break;
	case SDL_MOUSEWHEEL:
		wheel(sysinfo, event.wheel.y);
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		if (sysinfo.var.nbPlayer == 0)
		{
			sysinfo.var.nbPlayer = 1;
			IHM::refreshNbPlayerTxt(sysinfo);
		}
		sysinfo.var.waitEvent = false;
		break;
	case cinScreenNewGameNamePlayer:
		if (sysinfo.var.tempPlayerName.compare("") != 0)
		{
			sysinfo.var.tempPlayerName.pop_back();
			IHM::refreshNamePlayerTxt(sysinfo);
		}	
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		if (sysinfo.var.nbPlayer == 0)
		{
			sysinfo.var.nbPlayer = 1;
			IHM::refreshNbPlayerTxt(sysinfo);
		}
		sysinfo.var.waitEvent = false;
		break;
	case cinScreenNewGameNamePlayer:
		if (sysinfo.var.tempPlayerName.compare("") == 0)
		{
			sysinfo.var.tempPlayerName = "NoName" + std::to_string(sysinfo.var.s_player.nbNoNamePlayer);
			sysinfo.var.s_player.nbNoNamePlayer++;
			IHM::refreshNamePlayerTxt(sysinfo);
		}
		sysinfo.var.waitEvent = false;
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		if (sysinfo.var.nbPlayer == 0)
		{
			sysinfo.var.nbPlayer = 1;
			IHM::refreshNbPlayerTxt(sysinfo);
		}
		sysinfo.var.waitEvent = false;
		break;
	case cinScreenNewGameNamePlayer:
		if (sysinfo.var.tempPlayerName.compare("") == 0)
		{
			sysinfo.var.tempPlayerName = "NoName" + std::to_string(sysinfo.var.s_player.nbNoNamePlayer);
			sysinfo.var.s_player.nbNoNamePlayer++;
			IHM::refreshNamePlayerTxt(sysinfo);
		}
		sysinfo.var.waitEvent = false;
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
		GamePlay::groundGen(sysinfo);
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
		End::deletePlayer(sysinfo.tabplayer, "player");
		for (unsigned int i(0); i < 4; i++)
		{
			sysinfo.tabplayer.push_back(new Player("NoName" + std::to_string(i)));
		}
		GamePlay::newGameSettlerSpawn(sysinfo);
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		/* N/A */
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'a';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'b';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
		if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
			&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'c';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'd';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'e';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'f';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'g';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'h';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'i';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
		if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
			&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'j';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'k';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'l';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'm';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'n';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'o';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'p';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'q';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'r';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 's';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 't';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'u';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'v';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'w';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'x';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'y';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		/* N/A */
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += 'z';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 1;
		IHM::refreshNbPlayerTxt(sysinfo);
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '1';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:

		if (	sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
			&&	sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
		{
			Unit::tryToMove(sysinfo, -(int)(sysinfo.map.tileSize), sysinfo.map.tileSize);
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 2;
		IHM::refreshNbPlayerTxt(sysinfo);
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '2';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:

		if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
			&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
			Unit::tryToMove(sysinfo, 0, sysinfo.map.tileSize);

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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 3;
		IHM::refreshNbPlayerTxt(sysinfo);
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '3';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:

		if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
			&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
			Unit::tryToMove(sysinfo, sysinfo.map.tileSize, sysinfo.map.tileSize);

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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 4;
		IHM::refreshNbPlayerTxt(sysinfo);
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '4';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:

		if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
			&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
			Unit::tryToMove(sysinfo, -(int)(sysinfo.map.tileSize), 0);

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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 5;
		IHM::refreshNbPlayerTxt(sysinfo);
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '5';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:
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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 6;
		IHM::refreshNbPlayerTxt(sysinfo);
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '6';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:

		if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
			&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
			Unit::tryToMove(sysinfo, sysinfo.map.tileSize, 0);

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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 7;
		IHM::refreshNbPlayerTxt(sysinfo);
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '7';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:

		if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
			&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
			Unit::tryToMove(sysinfo, -(int)(sysinfo.map.tileSize), -(int)(sysinfo.map.tileSize));

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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 8;
		IHM::refreshNbPlayerTxt(sysinfo);
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '8';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:

		if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
			&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
			Unit::tryToMove(sysinfo, 0, -(int)(sysinfo.map.tileSize));

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
	case cinNothing:
		/* N/A */
		break;
	case cinTitleScreen:
		/* N/A */
		break;
	case cinScreenNewGameNbPlayer:
		sysinfo.var.nbPlayer = 9;
		IHM::refreshNbPlayerTxt(sysinfo);
		break;
	case cinScreenNewGameNamePlayer:
		sysinfo.var.tempPlayerName += '9';
		IHM::refreshNamePlayerTxt(sysinfo);
		break;
	case cinMainMap:

		if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
			&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
			Unit::tryToMove(sysinfo, sysinfo.map.tileSize, -(int)(sysinfo.map.tileSize));

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

 
/*
* NAME : mouse
* ROLE : Dispatch entre clique droit ou clique gauche
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* INPUT  PARAMETERS : SDL_Event : l'évenement du clique
* OUTPUT PARAMETERS : choix du clique
* RETURNED VALUE    : void
*/
void KeyboardMouse::mouse(Sysinfo& sysinfo, SDL_Event event)
{
	/*

		Handle Mouse Event
		BUTTON_LEFT
		BUTTON_RIGHT

	*/

	if (event.button.button == SDL_BUTTON_LEFT)
		cliqueGauche(sysinfo, event);
	else if (event.button.button == SDL_BUTTON_RIGHT && sysinfo.var.statescreen == STATEmainmap)
		cliqueDroit(sysinfo, event);

}

/*
* NAME : cliqueGauche
* ROLE : Recherche de la zone ou le clique à lieu
* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* INPUT  PARAMETERS : SDL_Event : l'évenement du clique
* OUTPUT PARAMETERS : la chaine de caractères a retourner
* RETURNED VALUE    : void
*/
void KeyboardMouse::cliqueGauche(Sysinfo& sysinfo, SDL_Event event) 
{

	

	// inspect citie
	if (sysinfo.var.statescreen == STATEmainmap)
	{
		if (sysinfo.var.s_player.selectplayer > -1) 
		{
			if (sysinfo.var.select == selectinspect && sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabCity().size() != 0) 
			{
				sysinfo.var.mouse.SETmouse_x((
					(unsigned int)ceil(event.button.x / sysinfo.map.tileSize) * sysinfo.map.tileSize)
					+ sysinfo.map.screenOffsetXIndexMin * sysinfo.map.tileSize);
				sysinfo.var.mouse.SETmouse_y((
					(unsigned int)ceil(event.button.y / sysinfo.map.tileSize) * sysinfo.map.tileSize)
					+ sysinfo.map.screenOffsetYIndexMin * sysinfo.map.tileSize);
				City::searchCityTile(sysinfo);
			}
		}
	}
	// recherche du bouton par comparaison de string et des positions x et y du clic

	switch (sysinfo.var.statescreen)
	{
	case STATEmainmap:

		if (sysinfo.allButton.mainMap["screen Titre"]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.var.cinState = cinTitleScreen;
			SaveReload::savemaps(sysinfo);
			SaveReload::savePlayer(sysinfo);
			resetButtonOn(sysinfo);
			IHM::logfileconsole("__________________________");
			IHM::titleScreen(sysinfo);
			return;
		}
		
		if (sysinfo.allButton.mainMap["Create Unit"]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.allButton.mainMap["Create Unit"]->changeOn();
			if (sysinfo.var.select != selectcreate)
				sysinfo.var.select = selectcreate;
			else
				sysinfo.var.select = selectnothing;

			resetButtonOn(sysinfo);
			return;
		}
		if (sysinfo.allButton.mainMap["Move Unit"]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.allButton.mainMap["Move Unit"]->changeOn();
			if (sysinfo.var.select != selectmove)
				sysinfo.var.select = selectmove;
			else
			{
				sysinfo.var.s_player.selectunit = -1;
				sysinfo.var.select = selectnothing;
			}
			resetButtonOn(sysinfo);
			return;
		}
		if (sysinfo.allButton.mainMap["Inspect"]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.allButton.mainMap["Inspect"]->changeOn();
			if (sysinfo.var.select != selectinspect)
				sysinfo.var.select = selectinspect;
			else
			{
					sysinfo.var.s_player.selectunit = -1;
				sysinfo.var.select = selectnothing;
			}
			resetButtonOn(sysinfo);
			return;
		}
		if (sysinfo.allButton.mainMap["Next Turn"]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			GamePlay::nextTurn(sysinfo);
			resetButtonOn(sysinfo);
			return;
		}
		if (sysinfo.allButton.mainMap["Delete Unit"]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.allButton.mainMap["Delete Unit"]->SETon(!sysinfo.allButton.mainMap["Delete Unit"]->GETon());
			resetButtonOn(sysinfo);
			return;
		}

		{
			unsigned int i(0);
			for (const auto& n : sysinfo.allButton.player)
			{
				if (sysinfo.allButton.player[n.second->GETname()]->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
				{
					sysinfo.allButton.player[n.second->GETname()]->changeOn();
					if (sysinfo.var.s_player.selectplayer != (int)i)
						sysinfo.var.s_player.selectplayer = (int)i;
					else
						sysinfo.var.s_player.selectplayer = -1;
					IHM::logfileconsole("sysinfo.var.selectplayer = " + sysinfo.tabplayer[i]->GETname());
					resetButtonPlayerOn(sysinfo);
					return;
				}
				i++;
			}
		}
		
		
		break;
	case STATEtitleScreen:
		if (sysinfo.allButton.titleScreen["New Game"]->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			GamePlay::newGame(sysinfo);
			return;
		}
		if (sysinfo.allButton.titleScreen["Reload"]->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			IHM::reloadScreen(sysinfo);
			return;
		}
		if (sysinfo.allButton.titleScreen["Option"]->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			//clearSave(sysinfo);
			return;
		}
		if (sysinfo.allButton.titleScreen["Quit"]->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.var.continuer = false;
			return;
		}
		break;
	case STATEreload:
		if (sysinfo.allButton.reload["Back"]->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y)) 
		{
			IHM::titleScreen(sysinfo);
			return;
		}
		if (sysinfo.allButton.reload["Remove all saves"]->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.allButton.reload["Remove all saves"]->changeOn();
			SaveReload::clearSave(sysinfo);
			IHM::reloadScreen(sysinfo);
			return;
		}
		if (sysinfo.allButton.reload["Load"]->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			SaveReload::reload(sysinfo);
			return;
		}
		if (sysinfo.allButton.reload["Remove"]->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			SaveReload::removeSave(sysinfo);
			IHM::reloadScreen(sysinfo);
			return;
		}

		for (unsigned int j = 0; j < sysinfo.var.save.GETnbSave(); j++)
		{
			if (sysinfo.allButton.reload["Save : " + std::to_string(sysinfo.var.save.GETtabSave()[j])]->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
			{
				sysinfo.allButton.reload["Save : " + std::to_string(sysinfo.var.save.GETtabSave()[j])]->changeOn();
				sysinfo.var.save.SETcurrentSave(sysinfo.var.save.GETtabSave()[j]);
				sysinfo.file.SaveMaps = "save/" + std::to_string(sysinfo.var.save.GETtabSave()[j]) + "/SaveMaps.txt";
				sysinfo.file.SavePlayer = "save/" + std::to_string(sysinfo.var.save.GETtabSave()[j]) + "/SavePlayer.txt";
				IHM::reloadScreen(sysinfo);
				return;
			}
		}
		break;
	case STATEcitiemap:
		if (sysinfo.allButton.citieMap["Map"]->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.var.s_player.selectCitie = -1;
			sysinfo.var.statescreen = STATEmainmap;
			sysinfo.var.select = selectnothing;
			resetButtonCitieMap(sysinfo);
			return;
		}
		if (sysinfo.allButton.citieMap["Build"]->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.allButton.citieMap["Build"]->changeOn();
			if (sysinfo.var.select != selectcreate)
				sysinfo.var.select = selectcreate;
			else
				sysinfo.var.select = selectnothing;
			resetButtonCitieMap(sysinfo);
			return;
		}
		if (sysinfo.allButton.citieMap["Place Citizen"]->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.allButton.citieMap["Place Citizen"]->changeOn();
			if (sysinfo.var.select != selectmoveCitizen)
				sysinfo.var.select = selectmoveCitizen;
			else
				sysinfo.var.select = selectnothing;
			resetButtonCitieMap(sysinfo);
			return;
		}


		if (sysinfo.var.select == selectcreate)
		{
			for (unsigned int i(0); i < sysinfo.var.s_player.tabUnit_Struct.size(); i++)
			{
				if (sysinfo.allButton.citieMap[sysinfo.var.s_player.tabUnit_Struct[i].name]->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
				{
					sysinfo.var.s_player.toBuild = sysinfo.var.s_player.tabUnit_Struct[i].name;
					sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->addUnit(sysinfo.var.s_player.tabUnit_Struct[i].name,
						sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheCity(sysinfo.var.s_player.selectCitie)->GETx(),
						sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheCity(sysinfo.var.s_player.selectCitie)->GETy(),
						sysinfo.var.s_player.tabUnit_Struct[i].life, sysinfo.var.s_player.tabUnit_Struct[i].atq,
						sysinfo.var.s_player.tabUnit_Struct[i].def, sysinfo.var.s_player.tabUnit_Struct[i].movement,
						sysinfo.var.s_player.tabUnit_Struct[i].level);

					sysinfo.var.select = selectnothing;
					break;
				}
			}
		}
		break;
	}
}

/*
* NAME : cliqueDroit
* ROLE : Recherche de la zone ou le clique à lieu
* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* INPUT  PARAMETERS : SDL_Event : l'évenement du clique
* OUTPUT PARAMETERS : la chaine de caractères a retourner
* RETURNED VALUE    : void
*/
void KeyboardMouse::cliqueDroit(Sysinfo& sysinfo, SDL_Event event)
{
	unsigned int selectunit = 0;
	sysinfo.var.mouse.SETmouse_x((unsigned int)ceil(event.button.x / sysinfo.map.tileSize) * sysinfo.map.tileSize);
	sysinfo.var.mouse.SETmouse_y((unsigned int)ceil(event.button.y / sysinfo.map.tileSize) * sysinfo.map.tileSize);
	if (sysinfo.var.s_player.selectplayer > -1)
	{
		switch (sysinfo.var.statescreen)
		{
		case STATEmainmap:
			switch (sysinfo.var.select) 
			{
			case selectcreate:
				for (unsigned int p = 0; p < sysinfo.var.s_player.tabUnit_Struct.size(); p++) {
					if (sysinfo.var.s_player.unitNameToCreate.compare(sysinfo.var.s_player.tabUnit_Struct[p].name) == 0)
					{
						selectunit = p;
						break;
					}
				}
				sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->addUnit(sysinfo.var.s_player.unitNameToCreate,
					sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y(),
					sysinfo.var.s_player.tabUnit_Struct[selectunit].life, sysinfo.var.s_player.tabUnit_Struct[selectunit].atq,
					sysinfo.var.s_player.tabUnit_Struct[selectunit].def, sysinfo.var.s_player.tabUnit_Struct[selectunit].movement,
					sysinfo.var.s_player.tabUnit_Struct[selectunit].level);
				break;
			case selectmove:
				if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabUnit().size() != 0)
				{
					Unit::searchUnitTile(sysinfo);
					IHM::logfileconsole("Unit select to move n:" + std::to_string(sysinfo.var.s_player.selectunit));
				}
				break;
			case selectinspect:
				if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabUnit().size() != 0) 
				{
					Unit::searchUnitTile(sysinfo);
					IHM::logfileconsole("Unit select to Inspect n:" + std::to_string(sysinfo.var.s_player.selectunit));
				}
				break;
			}
			break;
		}
	}
}

/*
* NAME : wheel
* ROLE : Recherche l'incrémentation ou décrémentation du contexte
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* INPUT  PARAMETERS : int& wheel : l'évenement de scroll de la souris
* OUTPUT PARAMETERS : une action suivant l'incrémentation ou décrémentation du contexte
* RETURNED VALUE    : void
*/
void KeyboardMouse::wheel(Sysinfo& sysinfo, int& wheel)
{
	if (sysinfo.var.select == selectcreate)
	{
		if (wheel == 1)
		{
			if (sysinfo.var.s_player.unitToCreate > 0)
				sysinfo.var.s_player.unitToCreate--;
		}
		else if (wheel == -1) 
		{
			if (sysinfo.var.s_player.unitToCreate < sysinfo.var.s_player.tabUnit_Struct.size() - 1)
				sysinfo.var.s_player.unitToCreate++;
		}
		Unit::searchUnit(sysinfo);
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

/*
* NAME : resetButtonOn
* ROLE : reset de l'affichage On des boutons
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : reset de l'affichage On des boutons
* RETURNED VALUE    : void
*/
void KeyboardMouse::resetButtonOn(Sysinfo& sysinfo)
{
	for (const auto& n : sysinfo.allButton.mainMap)
	{
		n.second->resetOnstateScreen(sysinfo.var.select, selectnothing);
		n.second->resetOnPlayer(sysinfo.var.s_player.selectplayer, sysinfo.var.s_player.tabPlayerName);
	}
}

/*
* NAME : resetButtonPlayerOn
* ROLE : reset de l'affichage On des boutons player
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : reset de l'affichage On des boutons player
* RETURNED VALUE    : void
*/
void KeyboardMouse::resetButtonPlayerOn(Sysinfo& sysinfo)
{
	for (const auto& n : sysinfo.allButton.player)
	{
		n.second->resetOnstateScreen(sysinfo.var.select, selectnothing);
		n.second->resetOnPlayer(sysinfo.var.s_player.selectplayer, sysinfo.var.s_player.tabPlayerName);
	}
}

/*
* NAME : resetButtonCitieMap
* ROLE : reset de l'affichage On des boutons citieMap
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : reset de l'affichage On des boutons citieMap
* RETURNED VALUE    : void
*/
void KeyboardMouse::resetButtonCitieMap(Sysinfo& sysinfo)
{
	for (const auto& n : sysinfo.allButton.citieMap)
	{
		n.second->resetOnstateScreen(sysinfo.var.select, selectnothing);
	}
}


/* *********************************************************
 *			END KeyboardMouse::STATIC::SOURIS			   *
 ********************************************************* */

 

/* *********************************************************
 *				START KeyboardMouse::METHODS			   *
 ********************************************************* */
 

KeyboardMouse::KeyboardMouse(): _mouse_x(0), _mouse_y(0), _ywheel(0), _xwheel(0)
{
}


/* *********************************************************
 *				END KeyboardMouse::METHODS				   *
 ********************************************************* */

/*
*	End Of File : KeyboardMouse.cpp
*/