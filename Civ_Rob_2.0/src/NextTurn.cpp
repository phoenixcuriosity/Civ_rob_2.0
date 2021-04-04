/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.6.0
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

#include "NextTurn.h"

#include "GamePlaySrceen.h"
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
	VectPlayer& vectPlayer = mainGame.GETPlayers().GETvectPlayer();

	for (unsigned int i(0); i < vectPlayer.size(); i++)
	{
		vectPlayer[i]->resetGoldStats();
		for (unsigned int j(0); j < vectPlayer[i]->GETtabUnit().size(); j++)
		{
			vectPlayer[i]->GETtabUnit()[j]->RESETmovement();
			vectPlayer[i]->GETtabUnit()[j]->heal(mainGame.GETmainMap().GETmatriceMap(), i);
		}
		for (unsigned int j(0); j < vectPlayer[i]->GETtabCity().size(); j++)
		{
			/* computeEmotion must be in first : Emotion use on other computations */
			vectPlayer[i]->GETtabCity()[j]->computeEmotion();

			/* Food */
			vectPlayer[i]->GETtabCity()[j]->foodNextTurn(vectPlayer[i]->GETgoldStats());

			/* Work */
			vectPlayer[i]->GETtabCity()[j]->computeWork();
			vectPlayer[i]->GETtabCity()[j]->computeWorkToBuild
			(
				*vectPlayer[i],
				mainGame.GETPlayers().GETvectUnitTemplate(),
				mainGame.GETPlayers().GETneedToUpdateDrawUnitPtr()
			);

			/* Gold */
			vectPlayer[i]->GETtabCity()[j]->computeGold();
			vectPlayer[i]->GETtabCity()[j]->addCityGoldToTaxIncome(vectPlayer[i]->GETgoldStats());
		}
		vectPlayer[i]->computeGold();
	}
	m_nbTurn++;
}