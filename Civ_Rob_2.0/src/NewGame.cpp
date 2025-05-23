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
#include "LogSentences.h"
#include "NewGameScreen.h"
#include "Player.h"
#include "SaveReload.h"
#include "Unit.h"

#include <R2D/src/GUI.h>
#include <R2D/src/Log.h>

namespace NGC
{
	/* Minimum space beetween two or more settlers */
	constexpr unsigned int MIN_SPACE_BETWEEN_SETTLER = 8;

	constexpr unsigned int MAX_RANDOM_POS_ITERATION = 10000;

	/* The first settler to spawn in the map for each Player does not cost maintenance */
	constexpr double MAINTENANCE_COST_1TH_SETTLER = 0.0;
}

void NewGameManager::newGame(GamePlayScreen& gamePlayScreen)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::NEWGAME, logS::DATA::START);

	SaveReload::getInstance().createSave();

	pushNewPlayer(gamePlayScreen.getUserInputNewGame()->vectPlayerName, gamePlayScreen.GETPlayers());

	newGameSettlerSpawn(gamePlayScreen.GETPlayers(), gamePlayScreen.GETmainMap());

	SaveReload::getInstance().save();

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::NEWGAME, logS::DATA::END);
}

void NewGameManager::pushNewPlayer
(
	const PlayerNameVector& vectCityName,
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

void NewGameManager::newGameSettlerSpawn
(
	Players& players,
	const MainMap& mainMap
)
{
	std::vector<randomPos> tabRandom;
	for (size_t i(0); i < players.GETvectPlayer().size(); i++)
	{
		makeRandomPosTab(mainMap, tabRandom);
		players.GETvectPlayer()[i]->addUnit("settler", { tabRandom[i].x, tabRandom[i].y} );
	}
}

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
