/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.14
	file version : 1.0

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
	Ce module permet la configuration du d�but de la partie
	Celui-ci comprend par ordre d'apparition:
		- Une demande du nombre de joueur ainsi que leur nom
		- La g�n�ration des positions des settlers -> fonction newGameSettlerSpawn
		- La g�n�ration de la map -> fonction groundgen
		- appel � la sauvegarde de l'�tat actuel des joueurs et de la map -> fonctions savePlayer et savemaps
		- Cr�ation des boutons aux noms des joueurs

*/

#ifndef GamePlay_H
#define GamePlay_H

#include "civ_lib.h"
#include "Player.h"

typedef struct randomPos randomPos;
struct randomPos
{
	unsigned int x;
	unsigned int y;
};

class GamePlay
{
public:
	static void newgame(Sysinfo&);
	static void groundgen(Sysinfo&);
	static void tileAffectation(Tile& tile, Uint8 tile_ground, std::string tile_stringground, Uint8 tile_spec, std::string tile_stringspec, int8_t food, int8_t work, int8_t gold);
	static void newGameSettlerSpawn(Sysinfo&);
	static void makeRandomPosTab(Sysinfo& sysinfo, std::vector<randomPos>& tabRandom);
	static void makeRandomPos(randomPos& RandomPOS, unsigned int toolBarSize, unsigned int tileSize);
	static bool conditionspace(randomPos& RandomPOS, std::vector<randomPos>& tabRandom, unsigned int tileSize, unsigned int i);
	static bool conditionground(Sysinfo& sysinfo, randomPos& RandomPOS);

	static void nextTurn(Sysinfo&);
};

#endif

/*
*	End Of File
*/