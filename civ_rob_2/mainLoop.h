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

/*

	button :
	Ce module est la fonction principale bloquante
	tant que l'utilisateur ne ferme pas l'application
	ou appuie sur exit

	Ce module appelle continuellement :
		- la fonction alwaysrender qui permet l'affichage sur l'écran des textures
		- la recherche d'un évenement comme défini par la librairie SDL2.0.6
		- une incrémentation permettant de savoir le nombre d'images par seconde

*/

#ifndef mainLoop_H
#define mainLoop_H
#include "civ_lib.h"
#include "Player.h"

void mainLoop(sysinfo&, std::vector<Player*>&);

#endif