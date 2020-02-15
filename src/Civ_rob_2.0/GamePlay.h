/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.18
	file version : 1.3

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

#ifndef GamePlay_H
#define GamePlay_H

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

/* For struct Sysinfo and derived structs */
#include "LIB.h"

/* For class Player */
#include "Player.h"

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

 /* MAP -> taille max - min de la mer */
const Uint8 MAP_BORDER_MAX = 4;
const Uint8 MAP_BORDER_MIN = 1;

/* MAP -> valeur deep_water */
const Uint8 MAP_BORDER_ZERO = 0;

/* MAP_GEN_RANDOM */
const Uint8 MAP_GEN_RANDOM_RANGE_GROUND = 100;
const Uint8 MAP_GEN_RANDOM_OFFSET_GROUND = 1;

const Uint8 MAP_GEN_RANDOM_RANGE_SPEC_GRASS = 100;
const Uint8 MAP_GEN_RANDOM_OFFSET_SPEC_GRASS = 1;

const Uint8 MAP_GEN_RANDOM_RANGE_SPEC_WATER = 20;
const Uint8 MAP_GEN_RANDOM_OFFSET_SPEC_WATER = 1;

const Uint8 MAP_GEN_RANDOM_RANGE_SPEC_WATER1 = 10;
const Uint8 MAP_GEN_RANDOM_OFFSET_SPEC_WATER1 = 1;

const Uint8 MAP_GEN_RANDOM_RANGE_SPEC_WATER2 = 10;
const Uint8 MAP_GEN_RANDOM_OFFSET_SPEC_WATER2 = 1;

const Uint8 MAP_GEN_RANDOM_RANGE_SPEC_WATER_BORDER = 50;
const Uint8 MAP_GEN_RANDOM_OFFSET_SPEC_WATER_BORDER = 1;

const unsigned int MAX_RANDOM_POS_ITERATION = 10000;

/* Minimum space beetween two or more settlers */
const Uint8 MIN_SPACE_BETWEEN_SETTLER = 16;

/* *********************************************************
 *						 Enum							   *
 ********************************************************* */

/* N/A */

/* *********************************************************
 *						 Structs						   *
 ********************************************************* */

/* ---------------------------------------------------------------------- */
/* Structure d'un couple de positions									  */
/* Positions en x et y permettant le spawn des settlers					  */
/* ---------------------------------------------------------------------- */
typedef struct randomPos randomPos;
struct randomPos
{
	unsigned int x;
	unsigned int y;
};

/* *********************************************************
 *						  Classe						   *
 ********************************************************* */

class GamePlay
{
public:
	/* *********************************************************
	 *				GamePlay::STATIC::NEW-GAME				   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : newGame																	   */
	/* ROLE : Initialisation de la nouvelle partie										   */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
	/* RETURNED VALUE : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void newGame
	(
		Sysinfo&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : groundGen																	   */
	/* ROLE : Génération du sol et des spec de la map									   */
	/* INPUT/OUTPUT : Map& map : structure de la MAP									   */
	/* INPUT : Uint16 screenWidth : taille en de l'écran en pixel (axe x)				   */
	/* RETURNED VALUE : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void groundGen
	(
		Map& map,
		Uint16 screenWidth
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : mapBordersConditions														   */
	/* ROLE : Boucle For de conditions													   */
	/* ROLE : Nombre de conditions = (MAP_BORDER_MAX - MAP_BORDER_MIN) * 2				   */
	/* INPUT : const Map& map : structure de la MAP										   */
	/* INPUT : unsigned int i : index en X												   */
	/* INPUT : unsigned int j : index en Y												   */
	/* RETURNED VALUE : bool : valid = true / not valid = false							   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static bool mapBordersConditions
	(
		const Map& map,
		unsigned int i,
		unsigned int j
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : mapBorders																   */
	/* ROLE : Affectation des caractéristiques de la case en fonction ...				   */
	/* ROLE : ... de la fonction rand, dans la bordure de la map entre ...				   */
	/* ROLE : ... MAP_BORDER_MIN et MAP_BORDER_MAX										   */
	/* OUTPUT : Tile& tile : tile à affecter											   */
	/* RETURNED VALUE : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void mapBorders
	(
		Tile& tile
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : mapIntern																	   */
	/* ROLE : Affectation des caractéristiques de la case en fonction ...				   */
	/* ROLE : ... de la fonction rand, dans le reste de la map							   */
	/* ROLE : Si la case est de type water alors création de 2 autres ...				   */
	/* ROLE : ... cases de type water pour obtenir une forme en L						   */
	/* INPUT/OUTPUT : std::vector<std::vector<Tile>>& maps : matrice de la map			   */
	/* INPUT : unsigned int i : index en X												   */
	/* INPUT : unsigned int j : index en Y												   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void mapIntern
	(
		std::vector<std::vector<Tile>>& maps,
		unsigned int i,
		unsigned int j
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : tileAffectation															   */
	/* ROLE : Affectation des caractéristiques à une case								   */
	/* OUTPUT : Tile& tile, : la case à affecter										   */
	/* INPUT : Uint8 tile_ground, std::string tile_stringground,						   */
	/* INPUT : Uint8 tile_spec, std::string tile_stringspec,							   */
	/* INPUT : int8_t food, int8_t work, int8_t gold									   */
	/* RETURNED VALUE : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void tileAffectation
	(
		Tile& tile,
		Uint8 tile_ground,
		std::string tile_stringground,
		Uint8 tile_spec,
		std::string tile_stringspec,
		int8_t food,
		int8_t work,
		int8_t gold
	);
	
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : newGameSettlerSpawn														   */
	/* ROLE : Création des position pour les settlers de chaque joueurs					   */
	/* INPUT : const std::vector<Unit_Struct>& : tableau des statistiques ...			   */
	/* INPUT : ...  par défauts des unités												   */
	/* INPUT : const struct Map& map : structure globale de la map						   */
	/* INPUT/OUTPUT : std::vector<Player*>& : vecteurs de joueurs						   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void newGameSettlerSpawn
	(
		const std::vector<Unit_Struct>& tabUnit_Struct,
		const Map& map,
		std::vector<Player*>& tabplayer
	);
	
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : makeRandomPosTab															   */
	/* ROLE : Créér autant de vecteur de position (x,y) que de joueur initial			   */
	/* INPUT : const Map& map : structure globale de la map								   */
	/* INPUT/OUTPUT : std::vector<randomPos>& : vecteurs de positions					   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void makeRandomPosTab
	(
		const Map& map,
		std::vector<randomPos>& tabRandom
	);
	
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : makeRandomPos																   */
	/* ROLE : créér un vecteur de position (x,y) aléatoire respectant la taille de l'écran */
	/* OUTPUT : randomPos& RandomPOS : couple de positions								   */
	/* INPUT : const std::vector<std::vector<Tile>>& maps : Matrice maps				   */
	/* INPUT : unsigned int toolBarSize: taille de la barre d'outil						   */
	/* INPUT : unsigned int tileSize													   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void makeRandomPos
	(
		randomPos& RandomPOS,
		const std::vector<std::vector<Tile>>& maps,
		unsigned int toolBarSize,
		unsigned int tileSize
	);
	
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : conditionspace															   */
	/* ROLE : condition pour valider les coordonnées crées:								   */
	/* ROLE : etre en dehors d'un carré d'influence (ici tileSize * 8) d'une autre entitée */
	/* INPUT : const randomPos& RandomPOS : couple de positions							   */
	/* INPUT : const std::vector<randomPos>& : vecteurs de positions					   */
	/* INPUT : unsigned int tileSize													   */
	/* INPUT : unsigned int i : couple de positions courant								   */
	/* RETURNED VALUE    : true -> condition de position validée / false -> non valide     */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static bool conditionspace
	(
		const randomPos& RandomPOS,
		const std::vector<randomPos>& tabRandom,
		unsigned int tileSize,
		unsigned int i
	);
	
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : conditionground															   */
	/* ROLE : condition pour valider les coordonnées crées:								   */
	/* ROLE : - etre sur une tile possédant la caractéristique d'etre du sol			   */
	/* INPUT : const std::vector<std::vector<Tile>>& : Matrice de la map				   */
	/* INPUT : const std::vector<randomPos>& : vecteurs de positions					   */
	/* RETURNED VALUE    : true -> condition de position validée / false -> non valide	   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static bool conditionground
	(
		const std::vector<std::vector<Tile>>& maps,
		const randomPos& RandomPOS
	);



public:
	/* *********************************************************
	 *				GamePlay::STATIC::NextTurn				   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : nextTurn																	   */
	/* ROLE : Action à réaliser lors du passage à un nouveau tour					       */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void nextTurn
	(
		Sysinfo&
	);
};

#endif /* GamePlay_H */

/*
*	End Of File : GamePlay.h
*/