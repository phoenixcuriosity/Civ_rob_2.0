#include "CityService.h"

#include "../MainMap.h"
#include "../Player.h"
#include "../Players.h"

#include "../T_MainMap.h"

void city::CityService::createCity
(
	Players& players,
	MainMap& mainMap,
	const unsigned int influenceLevel /* = CITY_INFLUENCE::MIN_INFLUENCE_LEVEL */
)
{
	const unsigned int selectedPlayer((unsigned int)players.GETselectedPlayerId());
	PlayerPtrT splayer(players.GETselectedPlayerPtr());
	const unsigned int selectedUnit((unsigned int)splayer->GETselectedUnit());
	const UnitPtrT sUnit(splayer->GETtabUnit()[selectedUnit]);

	VectMapPtr tabtiles;
	tabtiles.resize(City::INIT_AREA_VIEW);

	fillCitieTiles
	(
		MainMap::convertPosXToIndex(sUnit->getX()), MainMap::convertPosYToIndex(sUnit->getY()),
		selectedPlayer, mainMap.GETmatriceMap(), tabtiles, influenceLevel
	);

	splayer->addCity(std::move(tabtiles));

	players.SETneedToUpdateDrawUnit(true);
	players.SETneedToUpdateDrawCity(true);
	mainMap.SETneedToUpdateDraw(true);
}

void city::CityService::loadCity
(
	MatriceMap& matriceMap,
	const unsigned int selectplayer,
	CityPtrT& city,
	const modifAppartenance_Type modAppartenance /* = modifAppartenance_Type::modify */
)
{
	assert(city);

	VectMapPtr tiles;
	tiles.resize(City::INIT_AREA_VIEW);
	fillCitieTiles
	(
		MainMap::convertPosXToIndex(city->getCoor().x), MainMap::convertPosYToIndex(city->getCoor().y),
		selectplayer, matriceMap, tiles, city->GETinfluenceLevel(), modAppartenance
	);
	city->SETVectMapPtr(tiles);
}

void city::CityService::fillCitieTiles
(
	const unsigned int middletileX,
	const unsigned int middletileY,
	const unsigned int selectplayer,
	MatriceMap& matriceMap,
	VectMapPtr& tabtile,
	const unsigned int influenceLevel /* = MIN_INFLUENCE_LEVEL */,
	const modifAppartenance_Type modAppartenance /* = modifAppartenance_Type::modify */
)
{
	unsigned int k(0);
	for (int o(-INIT_SIZE_VIEW_DIV + 1); o < INIT_SIZE_VIEW_DIV; o++)
	{
		if (middletileX + o < 0 || middletileX + o >= matriceMap.size()) continue;

		for (int p(-INIT_SIZE_VIEW_DIV + 1); p < INIT_SIZE_VIEW_DIV; p++)
		{
			if (middletileY + p < 0 || middletileY + p >= matriceMap[0].size()) continue;

			if ((modAppartenance == modifAppartenance_Type::modify) && (initSizeInfluenceCondition(o, p, influenceLevel)))
			{
				matriceMap[middletileX + o][middletileY + p].appartenance = selectplayer;
			}

			tabtile[k] = &matriceMap[middletileX + o][middletileY + p];
			k++;
		}
	}
}

bool city::CityService::initSizeInfluenceCondition
(
	const int o,
	const int p,
	const unsigned int influenceLevel
)
{
	const int bound{ static_cast<int>(MIN_INFLUENCE_LEVEL * influenceLevel) };
	if (
		o >= -bound && o <= bound && p >= -bound && p <= bound
		&&
		cornerCheck(o, p, influenceLevel)
		)
	{
		return true;
	}
	return false;
}

bool city::CityService::cornerCheck
(
	const int o,
	const int p,
	const unsigned int influenceLevel
)
{
	if (
		(MIN_INFLUENCE_LEVEL < influenceLevel)
		&&
		(std::abs(o) == std::abs(p))
		&&
		(MIN_INFLUENCE_LEVEL * influenceLevel) == (unsigned int)std::abs(o)
		)
	{
		return false;
	}
	return true;
}
