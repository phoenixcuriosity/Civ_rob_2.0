/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.6

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Civ_rob_2

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

#include "initAndError.h"

using namespace std;


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
	7) boucle principale avec button() dans button.cpp
	8) depend de l'utilisateur si click de souris ou touche de clavier enfoncée
	9) après chaque action de l'utilisateur, la fonction alwaysrender est appellée et permettra à terme de faire du 30 images par seconde




	Pour une image centrée utiliser SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	comme dans cet exemple :

	const string resPath = "image/";
	int iW, iH;
	SDL_Texture *image = loadTexture(information, resPath + "fish.bmp", information.ecran.renderer);
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	renderTexture(image, information.ecran.renderer, 0, 0);

	les 5 lignes ci dessus sont encapsulées dans les différents write() dans write.cpp
	
	SDL_RenderClear(renderer);	  Clear the entire screen to our selected color
*/

int main(int, char**){
	initAndError();
	return 0;
}

