/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2024 (robin.sauter@orange.fr)

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

#include "NewGame.h"

#include "App.h"
#include "GamePlayScreen.h"
#include "NewGameScreen.h"
#include "Player.h"
#include "SaveReload.h"
#include "Unit.h"
#include "T_Unit.h"

#include <R2D/src/GUI.h>
#include <R2D/src/ErrorLog.h> 

//----------------------------------------------------------NewGame----------------------------------------------------------------//

namespace NGC
{
	/* Minimum space beetween two or more settlers */
	constexpr unsigned int MIN_SPACE_BETWEEN_SETTLER = 8;

	constexpr unsigned int MAX_RANDOM_POS_ITERATION = 10000;

	/* The first settler to spawn in the map for each Player does not cost maintenance */
	constexpr double MAINTENANCE_COST_1TH_SETTLER = 0.0;
}


/* ----------------------------------------------------------------------------------- */
/* NAME : newGame																	   */
/* ROLE : Create a new save with new spaw settlers		 							   */
/* ROLE : Players names are associate to radio button		 						   */
/* ROLE : Save the new game set								 						   */
/* INPUT : void																		   */
/* RETURNED VALUE : void														       */
/* ------------------------------------------------------------------------------------*/
void NewGameManager::newGame(GamePlayScreen& gamePlayScreen)
{
	R2D::ErrorLog::logEvent("[INFO]___: Newgame Start");
	
	gamePlayScreen.getSaveReload()->createSave();

	pushNewPlayer(gamePlayScreen.getUserInputNewGame()->vectPlayerName, gamePlayScreen.GETPlayers());

	newGameSettlerSpawn(gamePlayScreen.GETPlayers(), gamePlayScreen.GETmainMap());

	SaveReload::save(gamePlayScreen);

	/* ### Don't put code below here ### */

	R2D::ErrorLog::logEvent("[INFO]___: Newgame End");
}

/* ----------------------------------------------------------------------------------- */
/* NAME : pushNewPlayer															   	   */
/* ROLE : For every name in struct UserInputNewGame push new player in m_players	   */
/* attribut in : UserInputNewGame* m_userInputNewGame								   */
/* attribut out : m_players															   */
/* RETURNED VALUE : void														       */
/* ------------------------------------------------------------------------------------*/
void NewGameManager::pushNewPlayer
(
	const VectCityName& vectCityName,
	Players& players
)
{
	int index{ 0 };
	for (const auto& p : vectCityName)
	{
		players.addPlayer(p, index);
		index++;
	}
}



/* ----------------------------------------------------------------------------------- */
/* NAME : newGameSettlerSpawn														   */
/* ROLE : Création des position pour les settlers de chaque joueurs					   */
/* IN/OUT : Players& players			   */
/* IN : const MainMap& mainMap												   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
void NewGameManager::newGameSettlerSpawn
(
	Players& players,
	const MainMap& mainMap
)
{
	/* ---------------------------------------------------------------------- */
	/* association des vecteurs de position (x,y)							  */
	/* avec les settlers de départ											  */
	/* ---------------------------------------------------------------------- */
	const size_t selectunit{ Unit::searchUnitByName("settler", players.GETvectUnitTemplate()) };

	std::vector<randomPos> tabRandom;
	for (size_t i(0); i < players.GETvectPlayer().size(); i++)
	{

		makeRandomPosTab(mainMap, tabRandom);

		players.GETvectPlayer()[i]->addUnit
		("settler",
			tabRandom[i].x,
			tabRandom[i].y,
			players.GETvectUnitTemplate()[selectunit].type,
			players.GETvectUnitTemplate()[selectunit].life,
			players.GETvectUnitTemplate()[selectunit].atq,
			players.GETvectUnitTemplate()[selectunit].def,
			players.GETvectUnitTemplate()[selectunit].movement,
			players.GETvectUnitTemplate()[selectunit].numberOfAttack,
			players.GETvectUnitTemplate()[selectunit].level,
			NGC::MAINTENANCE_COST_1TH_SETTLER);
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME : makeRandomPosTab															   */
/* ROLE : WHILE new positions are not valid, create new ones						   */
/* ROLE : --- create new positions with matriceMap & tileSize						   */
/* ROLE : --- IF positions are valid - on ground THEN quit loop						   */
/* ROLE : --- IF IN_DEBUG && iteration loop > MAX_RANDOM_POS_ITERATION THEN THROW	   */
/* ROLE : Push new valid position to vector of new positions						   */
/* IN : const Map& map : struct main map : map & tileSize							   */
/* IN/OUT : std::vector<randomPos>& : New vector positions							   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
void NewGameManager::makeRandomPosTab
(
	const MainMap& mainMap,
	std::vector<randomPos>& tabRandom
)
{
	randomPos RandomPOS;
	bool continuer(true);
	unsigned int iteration(0);

	while (continuer)
	{
		if (iteration >= NGC::MAX_RANDOM_POS_ITERATION)
		{
#ifdef _DEBUG
			throw(NGC::MAX_RANDOM_POS_ITERATION);
#endif // DEBUG_MODE
			/*
			TODO : remove existing settlers and players
				 : return to main menu with error message "too many player with this map size"
			*/
		}
		iteration++;

		makeRandomPos(RandomPOS, mainMap.GETmatriceMapConst(), mainMap.GETtileSize());
		if (conditionground(mainMap.GETmatriceMapConst(), RandomPOS))
		{
			continuer = !conditionspace(RandomPOS, tabRandom, mainMap.GETtileSize());
		}
	}
	tabRandom.push_back(RandomPOS);
}

/* ----------------------------------------------------------------------------------- */
/* NAME : makeRandomPos																   */
/* ROLE : Create random positions between matriceMap								   */
/* ROLE : pos === size - 2 * MAP_BORDER_MAX * tileSize								   */
/* ROLE : Ceil value with tileSize													   */
/* OUT : randomPos& RandomPOS :	New random positions								   */
/* IN : const MatriceMap& matriceMap : matriceMap for size							   */
/* IN : const unsigned int tileSize	: Globale tileSize								   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
void NewGameManager::makeRandomPos
(
	randomPos& RandomPOS,
	const MatriceMap& matriceMap,
	const unsigned int tileSize
)
{
	const unsigned int SEA_BORDER_MAP(MAPH::MAP_BORDER_MAX * tileSize);

	const unsigned int x((rand() % ((matriceMap.size() * tileSize) - SEA_BORDER_MAP)) + SEA_BORDER_MAP);
	const unsigned int y((rand() % ((matriceMap[0].size() * tileSize) - SEA_BORDER_MAP)) + SEA_BORDER_MAP);

	RandomPOS.x = (unsigned int)ceil(x / tileSize) * tileSize;
	RandomPOS.y = (unsigned int)ceil(y / tileSize) * tileSize;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : conditionspace															   */
/* ROLE : IF empty tab return TRUE													   */
/* ROLE : ELSE test every positions with new positions  							   */
/* ROLE : --- IF new position is in a square of spaceBetweenSettler THEN return FALSE  */
/* ROLE : --- ELSE new position is not in a square with every positions				   */
/* ROLE : ---			of spaceBetweenSettler THEN return TRUE						   */
/* INPUT : const randomPos& RandomPOS : Positions to test							   */
/* INPUT : const std::vector<randomPos>& tabRandom : tab of positions				   */
/* INPUT : unsigned int tileSize : Globale tileSize									   */
/* RETURNED VALUE : TRUE -> New positions valid									       */
/* RETURNED VALUE : FALSE -> New positions not valid						           */
/* ------------------------------------------------------------------------------------*/
bool NewGameManager::conditionspace
(
	const randomPos& RandomPOS,
	const std::vector<randomPos>& tabRandom,
	const unsigned int tileSize
)
{
	/* Return true : Empty tab */
	if (tabRandom.empty()) return true;

	const unsigned int spaceBetweenSettler(tileSize * NGC::MIN_SPACE_BETWEEN_SETTLER);

	bool condition(false);
	for (size_t i(0); i < tabRandom.size(); i++)
	{
		if (
			((int)RandomPOS.x >= (int)((int)tabRandom[i].x + (int)spaceBetweenSettler)) /* West */
			||
			((int)RandomPOS.x <= (int)((int)tabRandom[i].x - (int)spaceBetweenSettler)) /* East */
			||
			((int)RandomPOS.y >= (int)((int)tabRandom[i].y + (int)spaceBetweenSettler)) /* North */
			||
			((int)RandomPOS.y <= (int)((int)tabRandom[i].y - (int)spaceBetweenSettler)) /* South */
			)
		{
			condition = true;
		}
		else
		{
			return false;
		}
	}
	return condition;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : conditionground															   */
/* ROLE : Convert new positions to index											   */
/* ROLE : IF Assert index to maticeMap size && tile index is ground THEN return TRUE   */
/* ROLE : ELSE return FALSE															   */
/* INPUT : const MatriceMap& matriceMap	: Map matrice								   */
/* INPUT : const randomPos& RandomPOS :	New positions								   */
/* RETURNED VALUE : TRUE -> New positions valid									       */
/* RETURNED VALUE : FALSE -> New positions not valid						           */
/* ------------------------------------------------------------------------------------*/
bool NewGameManager::conditionground
(
	const MatriceMap& matriceMap,
	const randomPos& RandomPOS
)
{
	const unsigned int x(MainMap::convertPosXToIndex(RandomPOS.x));
	const unsigned int y(MainMap::convertPosYToIndex(RandomPOS.y));

	if	(
			MainMap::assertRangeMapIndex(x, matriceMap.size())
			&&
			MainMap::assertRangeMapIndex(y, matriceMap[x].size())
		)
	{
		if	(
				matriceMap[x][y].tile_ground
				==
				Ground_Type::grass
			)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		throw("[ERROR]___: GamePlay::conditionground : assertRangeMapIndex == false");
	}
}
