/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.6.0
	file version : 1.5

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

#include "NextTurn.h"

#include "GamePlayScreen.h"
#include "Player.h"
#include "City.h"

NextTurn::NextTurn()
: m_nbTurn(0)
{

}

NextTurn::~NextTurn()
{

}

void NextTurn::nextTurn(GamePlayScreen& mainGame)
{
	unsigned int indexPlayer{ 0 };
	for (auto& player : mainGame.GETPlayers().GETvectPlayer())
	{
		player->resetGoldStats();
		for (auto& unit : player->GETtabUnit())
		{
			unit->RESETmovement();
			unit->RESETnumberOfAttack();
			unit->heal(mainGame.GETmainMap().GETmatriceMap(), indexPlayer);
		}
		for (auto& city : player->GETtabCity())
		{
			/* computeEmotion must be in first : Emotion use on other computations */
			city->computeEmotion();

			city->foodNextTurn(player->GETgoldStats());
			city->computeWork();
			city->computeWorkToBuild
			(
				*player,
				mainGame.GETPlayers().GETvectUnitTemplate(),
				mainGame.GETPlayers().GETneedToUpdateDrawUnitPtr()
			);
			city->computeGold();
			city->addCityGoldToTaxIncome(player->GETgoldStats());
		}
		player->computeGold();

		indexPlayer++;
	}
	m_nbTurn++;
}