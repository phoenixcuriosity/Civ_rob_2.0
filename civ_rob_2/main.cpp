/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.12

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
	3) instanciation de "information" et "tabplayer"
	4) utilisation de logfileconsole() pour écricre sur la console ainsi que sur le fichier log qui se trouve dans bin/log/log.txt
	5) check de l'ouverture des fichiers avec initfile() et initialisation de la sdl() dans sdl.cpp
	6) affichage de l'ecran titre avec ecrantitre() dans renduecran.cpp
	7) boucle principale avec mainloop() dans mainloop.cpp
	8) depend de l'utilisateur si click de souris ou touche de clavier enfoncée
	9) après chaque action de l'utilisateur, la fonction alwaysrender est appellée et permettra à terme de faire du 30 images par seconde




	Pour une image centrée utiliser SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	comme dans cet exemple :

	const string resPath = "image/";
	int iW, iH;
	SDL_Texture *image = loadTexture(information, resPath + "fish.bmp", information.ecran.renderer);
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	renderTexture(image, information.ecran.renderer, 0, 0);



	SDL_RenderClear(renderer);	  Clear the entire screen to our selected color
*/

#include "IHM.h"
#include "GamePlay.h"
#include "KeyboardMouse.h"

void mainLoop(sysinfo& information, std::vector<Player*>& tabplayer);

int main(int, char**){
	sysinfo information;
	std::vector<Player*> tabplayer;

	srand((unsigned int)time(NULL));

	clock_t t1, t2; // calcul du temps pour calculimage
	t1 = clock();

	try {
		IHM::initfile(information);
		IHM::initTile(information);
	}
	catch (std::exception const& e) {
		std::cerr << "ERREUR : " << e.what() << std::endl;
	}
	IHM::logfileconsole("________PROGRAMME START________");

	try {
		IHM::initsdl(information.ecran.window, information.ecran.renderer, information.allTextures.font);
	}
	catch (std::exception const& e) {
		std::cerr << "ERREUR : " << e.what() << std::endl;
	}


	Units::loadUnitAndSpec(information);
	IHM::calculimage(information);
	t2 = clock();
	IHM::logfileconsole("temps d'execution de l'initialisation : " + std::to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC));

	IHM::ecrantitre(information);
	mainLoop(information, tabplayer);	// fonction principale (bloquante)

	IHM::deleteAll(information, tabplayer);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	IHM::logfileconsole("SDL_Quit Success");
	IHM::logfileconsole("________PROGRAMME FINISH________");
	return 0;
}

void mainLoop(sysinfo& information, std::vector<Player*>& tabplayer) {
	IHM::logfileconsole("_mainLoop Start_");
	SDL_Event event;

	int countedFrames = 0;

	int SDL_EnableUNICODE(1); // on azerty

	while (information.variable.continuer) {
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:	// permet de quitter le jeu
				information.variable.continuer = 0;
				break;
			case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
				switch (event.key.keysym.sym) {
				case SDLK_F5:
					GamePlay::groundgen(information);
					break;
				case SDLK_F6:
					deleteDyTabPlayerAndTextures(tabplayer, "player");
					for (unsigned int i = 0; i < 4; i++) {
						tabplayer.push_back(new Player("NoName" + std::to_string(i)));
					}
					GamePlay::newGameSettlerSpawn(information, tabplayer);
					break;
				case SDLK_ESCAPE:
					information.variable.continuer = 0;
					break;
				case SDLK_SPACE:
					GamePlay::nextTurn(information, tabplayer);
					break;
				case SDLK_b:
					KeyboardMouse::keySDLK_b(information, tabplayer);
					break;
				case SDLK_i:
					KeyboardMouse::keySDLK_i(information, tabplayer);
					break;
				case SDLK_KP_1:
					KeyboardMouse::keySDLK_KP_1(information, tabplayer);
					break;
				case SDLK_KP_2:
					KeyboardMouse::keySDLK_KP_2(information, tabplayer);
					break;
				case SDLK_KP_3:
					KeyboardMouse::keySDLK_KP_3(information, tabplayer);
					break;
				case SDLK_KP_4:
					KeyboardMouse::keySDLK_KP_4(information, tabplayer);
					break;
				case SDLK_KP_5:
					KeyboardMouse::keySDLK_KP_5(information, tabplayer);
					break;
				case SDLK_KP_6:
					KeyboardMouse::keySDLK_KP_6(information, tabplayer);
					break;
				case SDLK_KP_7:
					KeyboardMouse::keySDLK_KP_7(information, tabplayer);
					break;
				case SDLK_KP_8:
					KeyboardMouse::keySDLK_KP_8(information, tabplayer);
					break;
				case SDLK_KP_9:
					KeyboardMouse::keySDLK_KP_9(information, tabplayer);
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN: // test sur le type d'événement click souris (enfoncé)
				KeyboardMouse::mouse(information, tabplayer, event);
				break;
			case SDL_MOUSEWHEEL:
				KeyboardMouse::wheel(information, event.wheel.y);

				break;
			}

		}

		if (information.ecran.enableFPS) {
			information.ecran.avgFPS = (int)ceil(countedFrames / (information.ecran.fpsTimer.getTicks() / 1000.f));
			if (information.ecran.avgFPS > 20000)
				information.ecran.avgFPS = 0;
			++countedFrames;
		}
		IHM::alwaysrender(information, tabplayer);


	}
	IHM::logfileconsole("_mainLoop End_");
}

