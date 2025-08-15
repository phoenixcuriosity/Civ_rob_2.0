#pragma once

#include <memory>
#include <vector>

class MatriceMap;
struct Tile;
class Player;
class GamePlayScreen;

namespace unit
{
	class Unit;
}

namespace city
{

class City;

class CityService
{
public: /* STATIC */

private:
	/* Minimal population in City */
	static constexpr unsigned int MIN_POP = 1;
	/* Minimal influence level in City */
	static constexpr unsigned int MIN_INFLUENCE_LEVEL = 1;

public:
	/* taille de la carte transpos�e dans la citiemap */
	static constexpr unsigned int INIT_SIZE_VIEW = 9;
	static constexpr int INIT_SIZE_VIEW_DIV = (INIT_SIZE_VIEW + 1) / 2;
	static constexpr unsigned int INIT_AREA_VIEW = INIT_SIZE_VIEW * INIT_SIZE_VIEW;

private:
	using PlayerPtrT = std::shared_ptr<Player>;
	using CityPtrT = std::shared_ptr<City>;
	using UnitPtrT = std::shared_ptr<unit::Unit>;

	using VectMapPtr = std::vector<Tile*>;
	using VectMap = std::vector<Tile>;
	using MatriceMap = std::vector<VectMap>;

public:
	enum class modifAppartenance_Type : bool
	{
		modify = true,
		dontModify = false
	};
public:
	static void createCity
	(
		GamePlayScreen& mainGame,
		const unsigned int influenceLevel = MIN_INFLUENCE_LEVEL
	);

	static void loadCity
	(
		MatriceMap& matriceMap,
		const unsigned int selectplayer,
		CityPtrT& city,
		const modifAppartenance_Type modAppartenance = modifAppartenance_Type::modify
	);

private:

	static void fillCitieTiles
	(
		const unsigned int middletileX,
		const unsigned int middletileY,
		const unsigned int selectplayer,
		MatriceMap& matriceMap,
		VectMapPtr& tabtile,
		const unsigned int influenceLevel = MIN_INFLUENCE_LEVEL,
		const modifAppartenance_Type modAppartenance = modifAppartenance_Type::modify
	);

	static bool initSizeInfluenceCondition
	(
		const int o,
		const int p,
		const unsigned int influenceLevel = MIN_INFLUENCE_LEVEL
	);

	static bool cornerCheck
	(
		const int o,
		const int p,
		const unsigned int influenceLevel
	);

};

}



