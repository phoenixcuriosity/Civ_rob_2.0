/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.5.0
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

#ifndef NewGame_H
#define NewGame_H

#include "LIB.h"
#include "MainMap.h"

#include <RealEngine2D/src/SpriteBatch.h>
#include <RealEngine2D/src/SpriteFont.h>
#include <RealEngine2D/src/Window.h>
#include <RealEngine2D\src\Vertex.h>

#include <vector>
#include <CEGUI/CEGUI.h>

class GamePlayScreen;
class Players;

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

/* The first settler to spawn in the map for each Player does not cost maintenance */
const double MAINTENANCE_COST_1TH_SETTLER = 0.0;

/* *********************************************************
 *						 Structs						   *
 ********************************************************* */

/* ---------------------------------------------------------------------- */
/* Structure d'un couple de positions									  */
/* Positions en x et y permettant le spawn des settlers					  */
/* ---------------------------------------------------------------------- */
struct randomPos
{
	unsigned int x;
	unsigned int y;
};

/* *********************************************************
 *						  Classe						   *
 ********************************************************* */

class NewGame
{
public:

	static void newGame(GamePlayScreen& mainGame);

private:

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : newGameSettlerSpawn														   */
	/* ROLE : Création des position pour les settlers de chaque joueurs					   */
	/* INPUT : const std::vector<Unit_Template>& : tableau des statistiques ...			   */
	/* INPUT : ...  par défauts des unités												   */
	/* INPUT : const struct Map& map : structure globale de la map						   */
	/* INPUT/OUTPUT : std::vector<Player*>& : vecteurs de joueurs						   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void newGameSettlerSpawn
	(
		Players& players,
		const MainMap& mainMap
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
		const MainMap& mainMap,
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
		const MatriceMap& matriceMap,
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
		unsigned int tileSize
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
		const MatriceMap& matriceMap,
		const randomPos& RandomPOS
	);

};

#endif // !NewGame_H
