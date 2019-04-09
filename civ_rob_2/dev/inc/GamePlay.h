/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.15
	file version : 1.2

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

#ifndef GamePlay_H
#define GamePlay_H

#include "civ_lib.h"
#include "Player.h"


/*
* Structure d'un couple de positions
* Positions en x et y permettant le spawn des settlers	
*/
typedef struct randomPos randomPos;
struct randomPos
{
	unsigned int x;
	unsigned int y;
};

class GamePlay
{
public:
	/* *********************************************************
	 *				GamePlay::STATIC::NEW-GAME				   *
	 ********************************************************* */


	/*
	* NAME : newGame
	* ROLE : Initialisation de la nouvelle partie
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : Noms des joueurs, groundGen, positions des settlers
	* RETURNED VALUE    : void
	*/
	static void newGame(Sysinfo&);

	/*
	* NAME : groundGen
	* ROLE : Génération du sol et des spec de la map
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : Génération du sol et des spec de la map
	* RETURNED VALUE    : void
	*/
	static void groundGen(Sysinfo&);

	/*
	* NAME : tileAffectation
	* ROLE : Affectation des caractéristiques à une case
	* INPUT  PARAMETERS : Tile& tile, : la case à affecter
	* INPUT  PARAMETERS : Uint8 tile_ground, std::string tile_stringground,
	* INPUT  PARAMETERS : Uint8 tile_spec, std::string tile_stringspec,
	* INPUT  PARAMETERS : int8_t food, int8_t work, int8_t gold
	* OUTPUT PARAMETERS : Affectation
	* RETURNED VALUE    : void
	*/
	static void tileAffectation(Tile& tile, Uint8 tile_ground, std::string tile_stringground, Uint8 tile_spec, std::string tile_stringspec, int8_t food, int8_t work, int8_t gold);
	
	/*
	* NAME : newGameSettlerSpawn
	* ROLE : Création des position pour les settlers de chaque joueurs
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : position pour les settlers de chaque joueurs
	* RETURNED VALUE    : void
	*/
	static void newGameSettlerSpawn(Sysinfo&);
	
	/*
	* NAME : makeRandomPosTab
	* ROLE : Créér autant de vecteur de position (x,y) que de joueur initial
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* INPUT  PARAMETERS : std::vector<randomPos>& : vecteurs de positions
	* OUTPUT PARAMETERS : std::vector<randomPos>& : vecteurs de positions
	* RETURNED VALUE    : void
	*/
	static void makeRandomPosTab(Sysinfo& sysinfo, std::vector<randomPos>& tabRandom);
	
	/*
	* NAME : makeRandomPos
	* ROLE : créér un vecteur de position (x,y) aléatoire respectant la taille de l'écran
	* INPUT  PARAMETERS : randomPos& RandomPOS : couple de positions
	* INPUT  PARAMETERS : unsigned int toolBarSize: taille de la barre d'outil
	* INPUT  PARAMETERS : unsigned int tileSize
	* OUTPUT PARAMETERS : un vecteur de position
	* RETURNED VALUE    : void
	*/
	static void makeRandomPos(randomPos& RandomPOS, std::vector<std::vector<Tile>> maps, unsigned int toolBarSize, unsigned int tileSize);
	
	/*
	* NAME : conditionspace
	* ROLE : condition pour valider les coordonnées crées:
	* ROLE : - etre en dehors d'un carré d'influence (ici tileSize * 8) d'une autre entitée
	* INPUT  PARAMETERS : randomPos& RandomPOS : couple de positions
	* INPUT  PARAMETERS : std::vector<randomPos>& : vecteurs de positions
	* INPUT  PARAMETERS : unsigned int tileSize
	* INPUT  PARAMETERS : couple de positions courant
	* OUTPUT PARAMETERS : validation des positions
	* RETURNED VALUE    : true -> condition de position validée / false -> non valide
	*/
	static bool conditionspace(randomPos& RandomPOS, std::vector<randomPos>& tabRandom, unsigned int tileSize, unsigned int i);
	
	/*
	* NAME : conditionground
	* ROLE : condition pour valider les coordonnées crées:
	* ROLE : - etre sur une tile possédant la caractéristique d'etre du sol
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* INPUT  PARAMETERS : std::vector<randomPos>& : vecteurs de positions
	* OUTPUT PARAMETERS : validation des positions
	* RETURNED VALUE    : true -> condition de position validée / false -> non valide
	*/
	static bool conditionground(Sysinfo& sysinfo, randomPos& RandomPOS);



public:
	/* *********************************************************
	 *				GamePlay::STATIC::NextTurn				   *
	 ********************************************************* */


	/*
	* NAME : nextTurn
	* ROLE : Action à réaliser lors du passage à un nouveau tour 
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : passage à un nouveau tour 
	* RETURNED VALUE    : void
	*/
	static void nextTurn(Sysinfo&);
};

#endif /* GamePlay_H */

/*
*	End Of File : GamePlay.h
*/