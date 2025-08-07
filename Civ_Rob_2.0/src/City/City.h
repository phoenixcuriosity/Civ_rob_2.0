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
#pragma once

#include "../LIB.h"

#include "BuildManager.h"
#include "CitizenManager.h"
#include "FoodManager.h"
#include "T_City.h"
#include "../T_MainMap.h"

#include <R2D/src/IMove.h>

struct GoldStats;
class GamePlayScreen;


namespace unit
{
	class Unit;
}

namespace city
{

class Citizen;
class ICityVisitor;

class City : public R2D::IMoveable
{
	friend class JsonCitySerializerVisitor;

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
	using dequeBuild = std::deque<BuildManager::buildGUI>;
	using PlayerPtrT = std::shared_ptr<Player>;
	using CityPtrT = std::shared_ptr<City>;
	using CitizenPtrT = std::shared_ptr<Citizen>;
	using VectCitizen = std::vector<CitizenPtrT>;
	using UnitPtrT = std::shared_ptr<unit::Unit>;

	using VectMapPtr = std::vector<Tile*>;
	using VectMap = std::vector<Tile>;
	using MatriceMap = std::vector<VectMap>;


public: /* STATIC */

	using Coor = R2D::Coor;
	enum class modifAppartenance_Type : bool
	{
		modify = true,
		dontModify = false
	};

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

private:

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


public:
	City();
	City(const std::string& name,
		 const Coor coor,
		 VectMapPtr& tiles,
		 const PlayerPtrT& player);

	virtual ~City();

	virtual bool searchCityTile(const unsigned int indexX, const unsigned int indexY);

public:
	void nextTurn(bool& needToUpdateDrawUnit);

private:
	virtual void computefood();
	virtual void computeWork(bool& needToUpdateDrawUnit);
	virtual void computeGold();
	virtual void addCityGoldToTaxIncome();

	virtual void convertFoodSurplusToGold(const double foodSurplus);

public:
	void addBuildToQueue(const BuildManager::buildGUI& buildToQueue)	{ m_buildManager.addBuildToQueue(buildToQueue); };
	void removeBuildToQueue(const size_t index)			{ m_buildManager.removeBuildToQueue(index); };
	void clearDynamicContextBuildToQueue()				{ m_buildManager.clearDynamicContextBuildToQueue(); };
	double GETBuildPerc()const							{ return m_buildManager.GETBuildPerc(); };

	void resetTabCitizen()								{ m_citizenManager.resetTabCitizen(); };
	void computeEmotion()								{ m_citizenManager.computeEmotion(); };

public:
	void accept(ICityVisitor& visitor) const;
	void loadFromOjson(const jsoncons::ojson& jsonLoad);

public:
	/* const & */
	inline virtual const std::string& GETname()const		{ return m_name; };
	inline virtual const VectMapPtr& GETtile()const			{ return m_tileMap; };
	inline virtual const VectCitizen& GETcitizens()const	{ return m_citizenManager.getCitizens(); };
	inline virtual const FoodManager& GETFoodManager()const { return m_foodManager; };
	inline virtual const dequeBuild& GETbuildQueue()const	{ return m_buildManager.getBuildQueue(); };

	/* & */
	inline virtual dequeBuild& GETbuildQueue() { return m_buildManager.getBuildQueue(); };

	/* implicit const */
	inline virtual size_t GETnbpop()const					{ return m_citizenManager.getCitizens().size(); };
	inline virtual unsigned int GETinfluenceLevel()const	{ return m_influenceLevel; };


	inline virtual void SETVectMapPtr(const VectMapPtr& tileMap)	{ m_tileMap = tileMap; };

	const PlayerPtrT& getOwner()const { return m_owner; }

private:

	std::string m_image;
	std::string m_name;
	VectMapPtr m_tileMap;
	unsigned int m_influenceLevel;
	unsigned int m_atq;
	unsigned int m_def;
	unsigned int m_nbstructurebuild;

	conversionSurplus_Type m_conversionToApply;

	CitizenManager m_citizenManager;
	FoodManager m_foodManager;
	BuildManager m_buildManager;

	double m_goldBalance;

	PlayerPtrT m_owner;
};

}