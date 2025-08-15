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
#include "UnitService.h"

#include "../MainMap.h"
#include "../Player.h"
#include "../Players.h"

void
unit::UnitService
::tryToMove(const MatriceMap& maps,
	Players& players,
	Select_Type select,
	const R2D::CardinalDirection& cardinalDirection)
{
	if (players.GETselectedPlayerId() != SELECTION::NO_PLAYER_SELECTED)
	{
		const PlayerPtrT selPlayer(players.GETselectedPlayerPtr());
		int playerToAttack(SELECTION::NO_PLAYER_SELECTED), unitToAttack(SELECTION::NO_UNIT_SELECTED), selectunit(selPlayer->GETselectedUnit());

		switch (searchToMove(maps, players, cardinalDirection, &playerToAttack, &unitToAttack))
		{
		case Unit::Move_Type::canMove:

			selPlayer->GETtabUnit()[selectunit]->move(select, selectunit, cardinalDirection);
			selPlayer->SETselectedUnit(selectunit);
			players.SETneedToUpdateDrawUnit(PlayerH::NEED_TO_UPDATE_DRAW_UNIT);
			break;
		case Unit::Move_Type::attackMove:
		{
			/* safe index playerToAttack / unitToAttack : filled by searchToMove */
			const PlayerPtrT attackPlayer(players.GETvectPlayer()[playerToAttack]);
			const UnitPtrT attackUnit{ selPlayer->GETtabUnit()[selectunit] };
			const UnitPtrT defenderUnit{ attackPlayer->GETtabUnit()[unitToAttack] };

			if (attackUnit->isPossibleToAttack())
			{
				attackUnit->attack(*(defenderUnit.get()));

				/* if the opposite Unit is destroy, try to move to its position */
				if (defenderUnit->GETalive() == false)
				{
					attackPlayer->deleteUnit(unitToAttack);
					tryToMove(maps, players, select, cardinalDirection);
				}
			}

			/* Cannot move further for this turn */
			attackUnit->Blockmovement();
			break;
		}
		case Unit::Move_Type::cannotMove:
		default:
			/*
			* Do nothing
			*/
			break;
		}
	}
}

unit::Unit::Move_Type
unit::UnitService
::searchToMove(const MatriceMap& maps,
	Players& players,
	const R2D::CardinalDirection& cardinalDirection,
	int* const playerToAttack,
	int* const unitToAttack)
{

	/* --------------------------------------------------------------------------------------- */
	/* conditions de mouvement :														 	   */
	/*	- que la case cible soit du ground si l'Unit et de type ground						   */
	/*	- ou que la case cible soit de l'air ou water et si l'Unit et de type air		   	   */
	/*	- ou que la case cible soit de la water et si l'Unit et de type water				   */
	/*	- ou que la case cible soit de la deepwater ou water et si l'Unit et de type deepwater */
	/*		- que la case cible est libre													   */
	/*		- ou que la case cible est occup�e par un ennemi								   */
	/*		  susceptible de mourrir par l'attaque											   */
	/* --------------------------------------------------------------------------------------- */

	const PlayerPtrT selPlayer(players.GETselectedPlayerPtr());
	const UnitPtrT unit(selPlayer->GETtabUnit()[selPlayer->GETselectedUnit()]);

	bool nextTileValidToMove(false);
	const unsigned int xIndex(MainMap::convertPosXToIndex(unit->getX() + cardinalDirection.m_pixelValueEW));
	const unsigned int yIndex(MainMap::convertPosYToIndex(unit->getX() + cardinalDirection.m_pixelValueNS));

	if (
		unit->isGroundMovement_Type()
		&&
		maps[xIndex][yIndex].tile_ground == Ground_Type::grass
		)
	{
		nextTileValidToMove = true;
	}
	else
		if (
			unit->isAirMovement_Type()
			&&
			(
				maps[xIndex][yIndex].tile_ground == Ground_Type::grass
				||
				maps[xIndex][yIndex].tile_ground == Ground_Type::water
				)
			)
		{
			nextTileValidToMove = true;
		}
		else
			if (
				unit->isWaterMovement_Type()
				&&
				maps[xIndex][yIndex].tile_ground == Ground_Type::water
				)
			{
				nextTileValidToMove = true;
			}
			else
				if (
					unit->isDeepWaterMovement_Type()
					&&
					(
						maps[xIndex][yIndex].tile_ground == Ground_Type::deepwater
						||
						maps[xIndex][yIndex].tile_ground == Ground_Type::water
						)
					)
				{
					nextTileValidToMove = true;
				}
				else
				{
					/* ---------------------------------------------------------------------- */
					/* nextTileValidToMove = false : Unit cannot move						  */
					/* ---------------------------------------------------------------------- */

					/* N/A */
				}



	bool condition(false);
	if (nextTileValidToMove)
	{
		/* ---------------------------------------------------------------------- */
		/* Next Tile is a ground Tile 											  */
		/* ---------------------------------------------------------------------- */

		for (unsigned int i{ 0 }; i < players.GETvectPlayer().size(); i++)
		{
			for (unsigned int j{ 0 }; j < players.GETvectPlayer()[i]->GETtabUnit().size(); j++)
			{
				condition = checkUnitNextTile
				(
					*unit,
					*(players.GETvectPlayer()[i]->GETtabUnit()[j]),
					cardinalDirection.m_pixelValueEW,
					cardinalDirection.m_pixelValueNS
				);
				if (true == condition)
				{
					if (players.GETselectedPlayerId() == (int)i)
					{
						return Unit::Move_Type::cannotMove;
					}
					else
					{
						*playerToAttack = (int)i;
						*unitToAttack = (int)j;
						return Unit::Move_Type::attackMove;
					}
				}
			}
		}
	}
	else
	{
		/* ---------------------------------------------------------------------- */
		/* Next Tile is not a ground Tile 										  */
		/* ---------------------------------------------------------------------- */

		return Unit::Move_Type::cannotMove;
	}
	return Unit::Move_Type::canMove;
}

bool unit::UnitService::checkUnitNextTile
(
	const Unit& from,
	const Unit& to,
	const int x,
	const int y
)
{
	if ((from.getX() + x) == to.getX())
	{
		if ((from.getY() + y) == to.getY())
		{
			return true;
		}
	}
	return false;
}

bool unit::UnitService::checkNextTile
(
	const Unit& from,
	const Tile& to,
	const int x,
	const int y
)
{
	if ((from.getX() + x) == (to.tile_x))
	{
		if ((from.getY() + y) == (to.tile_y))
		{
			return true;
		}
	}
	return false;
}
