/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.8

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

#include "mainLoop.h"

#include "sdl.h"
#include "renduecran.h"
#include "unit.h"
#include "saveAndReload.h"
#include "newgame.h"
#include "keyboardAndMouse.h"
#include "nextTurn.h"
#include "deleteAll.h"


using namespace std;

void mainLoop(sysinfo& information, vector<Player*>& tabplayer){
	logfileconsole("_mainLoop Start_");
	SDL_Event event;

	int countedFrames = 0;
	
	int SDL_EnableUNICODE(1); // on azerty

	while (information.variable.continuer){
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type){
			case SDL_QUIT:	// permet de quitter le jeu
				information.variable.continuer = 0;
				break;
			case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
				switch (event.key.keysym.sym) {
				case SDLK_F5:
					groundgen(information);
					break;
				case SDLK_F6:
					deleteDyTabPlayerAndTextures(tabplayer, "player");
					for (unsigned int i = 0; i < 4; i++){
						tabplayer.push_back(new Player("NoName" + to_string(i)));
					}
					newGameSettlerSpawn(information, tabplayer);
					break;
				case SDLK_ESCAPE:
					information.variable.continuer = 0;
					break;
				case SDLK_SPACE:
					nextTurn(information, tabplayer);
					break;
				case SDLK_b:
					keySDLK_b(information, tabplayer);
					break;
				case SDLK_i:
					keySDLK_i(information, tabplayer);
					break;
				case SDLK_KP_1:
					keySDLK_KP_1(information, tabplayer);
					break;
				case SDLK_KP_2:
					keySDLK_KP_2(information, tabplayer);
					break;
				case SDLK_KP_3:
					keySDLK_KP_3(information, tabplayer);
					break;
				case SDLK_KP_4:
					keySDLK_KP_4(information, tabplayer);
					break;
				case SDLK_KP_5:
					keySDLK_KP_5(information, tabplayer);
					break;
				case SDLK_KP_6:
					keySDLK_KP_6(information, tabplayer);
					break;
				case SDLK_KP_7:
					keySDLK_KP_7(information, tabplayer);
					break;
				case SDLK_KP_8:
					keySDLK_KP_8(information, tabplayer);
					break;
				case SDLK_KP_9:
					keySDLK_KP_9(information, tabplayer);
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN: // test sur le type d'événement click souris (enfoncé)
				mouse(information, tabplayer, event);
				break;
			case SDL_MOUSEWHEEL:
				wheel(information, event.wheel.y);
				
				break;
			}
			
		}

		if (information.ecran.enableFPS) {
			information.ecran.avgFPS = (int)ceil(countedFrames / (information.ecran.fpsTimer.getTicks() / 1000.f));
			if (information.ecran.avgFPS > 20000)
				information.ecran.avgFPS = 0;
			++countedFrames;
		}
		alwaysrender(information, tabplayer);
		
		
	}
	logfileconsole("_mainLoop End_");
}

