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
	newgame :
	Ce module permet la configuration du début de la partie
	Celui-ci comprend par ordre d'apparition:
		- Une demande du nombre de joueur ainsi que leur nom
		- La génération des positions des settlers -> fonction newGameSettlerSpawn
		- La génération de la map -> fonction groundgen
		- appel à la sauvegarde de l'état actuel des joueurs et de la map -> fonctions savePlayer et savemaps
		- Création des boutons aux noms des joueurs

*/

#ifndef newgame_H
#define newgame_H

#include "civ_lib.h"
#include "sdl.h"
#include "Player.h"
#include "renduecran.h"

typedef struct randomPos randomPos;
struct randomPos {
	int x;
	int y;
};


void newgame(sysinfo&, std::vector<Player*>&);
void groundgen(sysinfo&);
void tileAffectation(tile& tiles, unsigned int tile_ground, std::string& tile_stringground, unsigned int tile_spec, std::string& tile_stringspec, unsigned int food, unsigned int work, unsigned int gold);
void newGameSettlerSpawn(sysinfo&, std::vector<Player*>&);
void makeRandomPosTab(sysinfo& information, std::vector<randomPos>& tabRandom, unsigned int index);
void makeRandomPos(randomPos& RandomPOS);
bool conditionspace(randomPos& RandomPOS, std::vector<randomPos>& tabRandom, unsigned int i);
bool conditionground(sysinfo& information, randomPos& RandomPOS);


#endif