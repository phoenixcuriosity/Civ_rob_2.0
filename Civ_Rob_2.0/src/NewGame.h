/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)

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

/* ---------------------------------------------------------------------- */
/* Structure d'un couple de positions									  */
/* Positions en x et y permettant le spawn des settlers					  */
/* ---------------------------------------------------------------------- */
struct randomPos
{
	unsigned int x;
	unsigned int y;
};

class NewGameManager 
{

public:

	static void newGame(GamePlayScreen& gamePlayScreen);

private:

	/* NAME : pushNewPlayer															   	   */
	/* ROLE : For every name in struct UserInputNewGame push new player in m_players	   */
	/* attribut in : UserInputNewGame* m_userInputNewGame								   */
	/* attribut out : m_players															   */
	/* RETURNED VALUE : void														       */
	static void pushNewPlayer(const VectCityName& vectCityName, Players& players);


	/* NAME : newGameSettlerSpawn														   */
	/* ROLE : Création des position pour les settlers de chaque joueurs					   */
	/* INPUT : const std::vector<Unit_Template>& : tableau des statistiques ...			   */
	/* INPUT : ...  par défauts des unités												   */
	/* INPUT : const struct Map& map : structure globale de la map						   */
	/* INPUT/OUTPUT : std::vector<Player*>& : vecteurs de joueurs						   */
	/* RETURNED VALUE    : void															   */
	static void newGameSettlerSpawn
	(
		Players& players,
		const MainMap& mainMap
	);

	/* NAME : makeRandomPosTab															   */
	/* ROLE : WHILE new positions are not valid, create new ones						   */
	/* ROLE : --- create new positions with matriceMap & tileSize						   */
	/* ROLE : --- IF positions are valid - on ground THEN quit loop						   */
	/* ROLE : --- IF IN_DEBUG && iteration loop > MAX_RANDOM_POS_ITERATION THEN THROW	   */
	/* ROLE : Push new valid position to vector of new positions						   */
	/* IN : const Map& map : struct main map : map & tileSize							   */
	/* IN/OUT : std::vector<randomPos>& : New vector positions							   */
	/* RETURNED VALUE    : void															   */
	static void makeRandomPosTab
	(
		const MainMap& mainMap,
		std::vector<randomPos>& tabRandom
	);

	/* NAME : makeRandomPos																   */
	/* ROLE : Create random positions between matriceMap								   */
	/* ROLE : pos === size - 2 * MAP_BORDER_MAX * tileSize								   */
	/* ROLE : Ceil value with tileSize													   */
	/* OUT : randomPos& RandomPOS :	New random positions								   */
	/* IN : const MatriceMap& matriceMap : matriceMap for size							   */
	/* IN : const unsigned int tileSize	: Globale tileSize								   */
	/* RETURNED VALUE    : void															   */
	static void makeRandomPos
	(
		randomPos& RandomPOS,
		const MatriceMap& matriceMap,
		const unsigned int tileSize
	);

	/* NAME : conditionspace															   */
	/* ROLE : IF empty tab return TRUE													   */
	/* ROLE : ELSE test every positions with new positions  							   */
	/* ROLE : --- IF new position is in a square of spaceBetweenSettler THEN return FALSE  */
	/* ROLE : --- ELSE new position is not in a square with every positions				   */
	/* ROLE : ---			of spaceBetweenSettler THEN return TRUE						   */
	/* INPUT : const randomPos& RandomPOS : Positions to test							   */
	/* INPUT : const std::vector<randomPos>& tabRandom : tab of positions				   */
	/* INPUT : const unsigned int tileSize : Globale tileSize							   */
	/* RETURNED VALUE : TRUE -> New positions valid									       */
	/* RETURNED VALUE : FALSE -> New positions not valid						           */
	static bool conditionspace
	(
		const randomPos& RandomPOS,
		const std::vector<randomPos>& tabRandom,
		const unsigned int tileSize
	);

	/* NAME : conditionground															   */
	/* ROLE : Convert new positions to index											   */
	/* ROLE : IF Assert index to maticeMap size && tile index is ground THEN return TRUE   */
	/* ROLE : ELSE return FALSE															   */
	/* INPUT : const MatriceMap& matriceMap	: Map matrice								   */
	/* INPUT : const randomPos& RandomPOS :	New positions								   */
	/* RETURNED VALUE : TRUE -> New positions valid									       */
	/* RETURNED VALUE : FALSE -> New positions not valid						           */
	static bool conditionground
	(
		const MatriceMap& matriceMap,
		const randomPos& RandomPOS
	);
};


#endif // !NewGame_H
