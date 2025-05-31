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

#include "LIB.h"

#include "UnitStats.h"
#include "UnitTemplate.h"

#include <R2D/src/IBlick.h>
#include <R2D/src/IMove.h>

#include <glm/glm.hpp>


class Player;
class Players;
struct Tile;

namespace unit
{


class Unit : public R2D::IBlickable, public R2D::IMoveable, public UnitStats
{
private:
	using PlayerPtrT = std::shared_ptr<Player>;
	using UnitPtrT = std::shared_ptr<Unit>;
	using VectMap = std::vector<Tile>;
	using MatriceMap = std::vector<VectMap>;

public:
	/* Define movement for the Unit in case of tryToMove */
	enum class Move_Type
	{
		cannotMove,		/* The Unit cannot move to the next Tile */
		canMove,		/* The Unit can move to the next Tile */
		attackMove		/* The Unit can move to the next Tile and attack the other Unit standing on the this Tile */
	};

	using Coor = R2D::Coor;
	using UnitStat = UnitTemplate::UnitStat;
	using UnitName = std::string;

private:
	static constexpr char DEFAULT_UNIT_NAME[] = "DEFAULT_UNIT_NAME";
	static constexpr unsigned int ENOUGH_DAMAGE_TO_KILL = 0;
	static constexpr unsigned int ZERO_LIFE = 0;
	static constexpr bool DEAD_UNIT = false;
	static constexpr int FOOD_ADD_BY_IRRAGATION = 2;
	static constexpr int GOLD_ADD_BY_IRRAGATION = 1;
	static constexpr unsigned int BLIT_RATE = 2;
	using MovementType = UnitTemplate::Movement_Type;

public:
	static bool
	searchUnitTile(	Players& players,
					const glm::i32vec2& mouseCoorNorm,
					Select_Type* select);

	static void
	tryToMove(	const MatriceMap& maps,
				Players& players,
				Select_Type select,
				const R2D::CardinalDirection& cardinalDirection);

private:
	static Move_Type
	searchToMove(const MatriceMap& maps,
				 Players& players,
				 const R2D::CardinalDirection& cardinalDirection,
				 int* const playerToAttack,
				 int* const unitToAttack);

	static bool
	checkUnitNextTile(const Unit& from,
					  const Unit& to,
					  const int x,
					  const int y);

	static bool
	checkNextTile(const Unit& from,
				  const Tile& to,
				  const int x,
				  const int y);

public:

	Unit();
	Unit(const UnitName& name,
		 const Coor& coor,
		 const UnitStat& unitStat,
		 double maintenance,
		 PlayerPtrT ptrToPlayer);

	virtual ~Unit();

private:
	virtual void
	attack(Unit& defender);

	virtual void
	defend(const int dmg);

	virtual void
	move(Select_Type& select,
		 int& selectunit,
		 const R2D::CardinalDirection& cardinalDirection);

public:
	virtual void
	heal(const MatriceMap& tiles,
		 const unsigned int selectplayer);

	virtual bool
	irrigate(MatriceMap& map);

public:
	virtual bool isThisUnitType(const std::string& nameToCompare) const noexcept { return m_name == nameToCompare; };

public:
	jsoncons::ojson saveToOjson()const;
	void loadFromOjson(const jsoncons::ojson& jsonLoad);

public:
	inline const std::string& GETname()				const { return m_name; };
	inline bool GETalive()							const { return m_alive; };
	inline double GETmaintenance()					const { return m_maintenance; }
	inline PlayerPtrT GETowner()							  { return m_owner; };

	inline void SETowner(PlayerPtrT owner) { m_owner = owner; };

private:
	UnitName m_name;
	bool m_alive;
	double m_maintenance;

	PlayerPtrT m_owner;
};

}