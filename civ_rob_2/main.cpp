/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.13

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

/*
--------------- Readme ---------------

_Contenu de civ_lib.h_ :
		- tout les include des .h standard
		- toutes les constantes
		- toutes les stuctures

_Class_ :
		Player :
				Units -> Biter, Car, ....
				Cities
		Buttons



Chainage d'appel :
	1) main() dans main.cpp
	2) initAndError() dans initAndError.cpp
	3) instanciation de "sysinfo" et "tabplayer"
	4) utilisation de logfileconsole() pour écricre sur la console ainsi que sur le fichier log qui se trouve dans bin/log/log.txt
	5) check de l'ouverture des fichiers avec initfile() et initialisation de la sdl() dans sdl.cpp
	6) affichage de l'screen titre avec titleScreen() dans renduscreen.cpp
	7) boucle principale avec mainloop() dans mainloop.cpp
	8) depend de l'utilisateur si click de souris ou touche de clavier enfoncée
	9) après chaque action de l'utilisateur, la fonction alwaysrender est appellée et permettra à terme de faire du 30 images par seconde




	Pour une image centrée utiliser SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	comme dans cet exemple :

	const string resPath = "image/";
	int iW, iH;
	SDL_Texture *image = loadTexture(sysinfo, resPath + "fish.bmp", sysinfo.screen.renderer);
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	renderTexture(image, sysinfo.screen.renderer, 0, 0);



	SDL_RenderClear(renderer);	  Clear the entire screen to our selected color
*/

#include "IHM.h"
#include "GamePlay.h"
#include "KeyboardMouse.h"

void mainLoop(Sysinfo& sysinfo);

int main(int, char**){
	Sysinfo sysinfo;

	srand((unsigned int)time(NULL));

	clock_t t1, t2; // calcul du temps pour calculimage
	t1 = clock();

	try {
		IHM::initfile(sysinfo);
		IHM::inittile(sysinfo);
	}
	catch (std::exception const& e) {
		std::cerr << "ERREUR : " << e.what() << std::endl;
	}
	IHM::logfileconsole("________PROGRAMME START________");

	try {
		IHM::initsdl(sysinfo.screen.window, sysinfo.screen.renderer, sysinfo.allTextures.font);
	}
	catch (std::exception const& e) {
		std::cerr << "ERREUR : " << e.what() << std::endl;
	}


	Units::loadUnitAndSpec(sysinfo);
	IHM::calculimage(sysinfo);
	t2 = clock();
	IHM::logfileconsole("temps d'execution de l'initialisation : " + std::to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC));

	IHM::titleScreen(sysinfo);
	mainLoop(sysinfo);	// fonction principale (bloquante)

	IHM::deleteAll(sysinfo);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	IHM::logfileconsole("SDL_Quit Success");
	IHM::logfileconsole("________PROGRAMME FINISH________");
	return 0;
}

void mainLoop(Sysinfo& sysinfo) {
	IHM::logfileconsole("_mainLoop Start_");
	SDL_Event event;

	int countedFrames = 0;

	int SDL_EnableUNICODE(1); // on azerty

	while (sysinfo.var.continuer) {
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:	// permet de quitter le jeu
				sysinfo.var.continuer = 0;
				break;
			case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
				switch (event.key.keysym.sym) {
				case SDLK_F5:
					GamePlay::groundgen(sysinfo);
					break;
				case SDLK_F6:
					deleteDyTabPlayerAndTextures(sysinfo.tabplayer, "player");
					for (unsigned int i = 0; i < 4; i++) {
						sysinfo.tabplayer.push_back(new Player("NoName" + std::to_string(i)));
					}
					GamePlay::newGameSettlerSpawn(sysinfo);
					break;
				case SDLK_ESCAPE:
					sysinfo.var.continuer = 0;
					break;
				case SDLK_UP:
					if (sysinfo.map.screenOffsetY > 0)
						sysinfo.map.screenOffsetY -= sysinfo.map.tileSize;
					IHM::changeScreenOffset(sysinfo);
					break;
				case SDLK_LEFT:
					if (sysinfo.map.screenOffsetX > 0)
						sysinfo.map.screenOffsetX -= sysinfo.map.tileSize;
					IHM::changeScreenOffset(sysinfo);
					break;
				case SDLK_DOWN:
					if (sysinfo.map.screenOffsetY < (sysinfo.map.mapSize - SCREEN_HEIGHT))
						sysinfo.map.screenOffsetY += sysinfo.map.tileSize;
					IHM::changeScreenOffset(sysinfo);
					break;
				case SDLK_RIGHT:
					if (sysinfo.map.screenOffsetX < sysinfo.map.mapSize - SCREEN_WIDTH)
						sysinfo.map.screenOffsetX += sysinfo.map.tileSize;
					IHM::changeScreenOffset(sysinfo);
					break;
				case SDLK_SPACE:
					GamePlay::nextTurn(sysinfo);
					break;
				case SDLK_b:
					KeyboardMouse::keySDLK_b(sysinfo);
					break;
				case SDLK_i:
					KeyboardMouse::keySDLK_i(sysinfo);
					break;
				case SDLK_KP_1:
					KeyboardMouse::keySDLK_KP_1(sysinfo);
					break;
				case SDLK_KP_2:
					KeyboardMouse::keySDLK_KP_2(sysinfo);
					break;
				case SDLK_KP_3:
					KeyboardMouse::keySDLK_KP_3(sysinfo);
					break;
				case SDLK_KP_4:
					KeyboardMouse::keySDLK_KP_4(sysinfo);
					break;
				case SDLK_KP_5:
					KeyboardMouse::keySDLK_KP_5(sysinfo);
					break;
				case SDLK_KP_6:
					KeyboardMouse::keySDLK_KP_6(sysinfo);
					break;
				case SDLK_KP_7:
					KeyboardMouse::keySDLK_KP_7(sysinfo);
					break;
				case SDLK_KP_8:
					KeyboardMouse::keySDLK_KP_8(sysinfo);
					break;
				case SDLK_KP_9:
					KeyboardMouse::keySDLK_KP_9(sysinfo);
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN: // test sur le type d'événement click souris (enfoncé)
				KeyboardMouse::mouse(sysinfo, event);
				break;
			case SDL_MOUSEWHEEL:
				KeyboardMouse::wheel(sysinfo, event.wheel.y);

				break;
			}

		}

		if (sysinfo.screen.enableFPS) {
			sysinfo.screen.avgFPS = (int)ceil(countedFrames / (sysinfo.screen.fpsTimer.getTicks() / 1000.f));
			if (sysinfo.screen.avgFPS > 20000)
				sysinfo.screen.avgFPS = 0;
			++countedFrames;
		}
		IHM::alwaysrender(sysinfo);


	}
	IHM::logfileconsole("_mainLoop End_");
}

