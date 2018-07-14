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

#ifndef mouse_H
#define mouse_H

#include "civ_lib.h"
#include "Player.h"

void mouse(sysinfo&, std::vector<Player*>&, SDL_Event);
void cliqueGauche(sysinfo&, std::vector<Player*>&, SDL_Event);
void cliqueDroit(sysinfo&, std::vector<Player*>&, SDL_Event);
void wheel(sysinfo&, int&);


#endif