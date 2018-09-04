/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.6

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

	initAndError :
	Ce module permet l'initialisation du projet
	Celui-ci comprend par ordre d'apparition :
		- création de la structure sysinfo sous le nom information
		- création du tableau de joueur vide
		- initialisation ou création des fichiers utilisés -> initfile
		- initialisation de la fenetre de jeu -> initsdl
		- création des textures prévisibles -> calculimage
		- affichage de l'écran titre -> ecrantitre
		- entrée dans la fonction principale bloquante

*/

#ifndef initAndError_H
#define initAndError_H

#include "civ_lib.h"
#include "Cities.h"



void initAndError();
void calculimage(sysinfo&);
void createbutton(sysinfo&, std::vector<Buttons*>& tabbutton, const std::string &msg, SDL_Color, SDL_Color, int, int, int, int = 0); // parametre par defaut -> nocenter
void searchcenter(int &x, int &y, int &xc, int &yc, int iW, int iH, int centerbutton);

#endif