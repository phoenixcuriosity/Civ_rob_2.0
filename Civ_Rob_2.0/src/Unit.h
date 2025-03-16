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

#ifndef Unit_H
#define Unit_H

#include "LIB.h"

#include "UnitTemplate.h"

#include <R2D/src/API_fwd.h>
#include <R2D/src/Window.h>
#include <glm/glm.hpp>

class Unit
{
public:
	/* Define movement for the Unit in case of tryToMove */
	enum class Move_Type
	{
		cannotMove,		/* The Unit cannot move to the next Tile */
		canMove,		/* The Unit can move to the next Tile */
		attackMove		/* The Unit can move to the next Tile and attack the other Unit standing on the this Tile */
	};

private:
	static constexpr char DEFAULT_UNIT_NAME[] = "DEFAULT_UNIT_NAME";
	static constexpr unsigned int NO_MOVEMENT = 0;
	static constexpr unsigned int ENOUGH_DAMAGE_TO_KILL = 0;
	static constexpr unsigned int ZERO_LIFE = 0;
	static constexpr unsigned int ZERO_BLIT = 0;
	static constexpr bool DEAD_UNIT = false;
	static constexpr unsigned int COEF_DIV_HEAL_NO_APPARTENANCE = 20;
	static constexpr unsigned int COEF_DIV_HEAL_APPARTENANCE = 5;
	static constexpr unsigned int COEF_DIV_LEVELUP = 4;
	static constexpr int FOOD_ADD_BY_IRRAGATION = 2;
	static constexpr int GOLD_ADD_BY_IRRAGATION = 1;

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
	Unit(const std::string& name,
		unsigned int x,
		unsigned int y,
		UnitTemplate::Movement_Type movementType,
		unsigned int life,
		unsigned int atq,
		unsigned int def,
		unsigned int move,
		unsigned int numberOfAttack,
		unsigned int level,
		double maintenance,
		Player* ptrToPlayer);

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

	virtual void
	levelup();

	virtual void
	RESETmovement() noexcept { m_movement = m_maxmovement; };

	virtual void
	RESETnumberOfAttack() noexcept { m_numberOfAttack = m_maxNumberOfAttack; };

	virtual bool
	irrigate(MatriceMap& map);

private:
	static constexpr unsigned int ZERO_NUMBER_OF_ATTACK = 0;
private:

	virtual bool testPos(const unsigned int mouse_x, const unsigned int mouse_y) const noexcept
	{return (m_x == mouse_x && m_y == mouse_y);};

	virtual bool isGroundMovement_Type() const noexcept		{ return m_movementType == UnitTemplate::Movement_Type::ground; };
	virtual bool isAirMovement_Type() const noexcept		{ return m_movementType == UnitTemplate::Movement_Type::air; };
	virtual bool isWaterMovement_Type()	const noexcept		{ return m_movementType == UnitTemplate::Movement_Type::water; };
	virtual bool isDeepWaterMovement_Type() const noexcept	{ return m_movementType == UnitTemplate::Movement_Type::deepwater; };
	virtual bool isPossibleToAttack()const noexcept			{ return m_numberOfAttack > ZERO_NUMBER_OF_ATTACK; };

public:

	virtual bool isThisUnitType(const std::string& nameToCompare) const noexcept { return m_name == nameToCompare; };

private:
	static constexpr unsigned int BLIT_RATE = 2;
public:

	virtual void cmpblit() noexcept { if ((++m_blit %= (R2D::SCREEN_REFRESH_RATE / BLIT_RATE)) == MODULO::ZERO){ m_show = !m_show;}};

public:

	jsoncons::ojson saveToOjson()const;

	void loadFromOjson(const jsoncons::ojson& jsonLoad);

public:

	inline const std::string& GETname()				const { return m_name; };
	inline unsigned int GETx()						const { return m_x; };
	inline unsigned int GETy()						const { return m_y; };
	inline UnitTemplate::Movement_Type GETmovementType()			const { return m_movementType; };
	inline int GETmaxlife()							const { return m_maxlife; };
	inline int GETmaxatq()							const { return m_maxatq; };
	inline int GETmaxdef()							const { return m_maxdef; };
	inline int GETmaxmovement()						const { return m_maxmovement; };
	inline int GETmaxNumberOfAttack()				const { return m_maxNumberOfAttack; };
	inline int GETmaxlevel()						const { return m_maxlevel; };
	inline int GETlife()							const { return m_life; };
	inline int GETatq()								const { return m_atq; };
	inline int GETdef()								const { return m_def; };
	inline int GETmovement()						const { return m_movement; };
	inline int GETnumberOfAttack()					const { return m_numberOfAttack; };
	inline int GETlevel()							const { return m_level; };
	inline bool GETalive()							const { return m_alive; };
	inline double GETmaintenance()					const { return m_maintenance; }
	inline unsigned int GETblit()					const { return m_blit; };
	inline bool GETshow()							const { return m_show; };
	inline bool GETshowStats()						const { return m_showStats; };
	inline Player* GETowner()							  { return m_owner; };

	inline void SETmovement(int movement) { m_movement = movement; };
	inline void SETshow(bool show) { m_show = show; };
	inline void SETowner(Player* owner) { m_owner = owner; };

private:

	std::string m_name;
	unsigned int m_x;
	unsigned int m_y;
	UnitTemplate::Movement_Type m_movementType;

	int m_maxlife;
	int m_maxatq;
	int m_maxdef;
	int m_maxmovement;
	int m_maxNumberOfAttack;
	int m_maxlevel;

	int m_life;
	int m_atq;
	int m_def;
	int m_movement;
	int m_numberOfAttack;
	int m_level;
	bool m_alive;

	double m_maintenance;

	unsigned int m_blit;
	bool m_show;
	bool m_showStats;

	Player* m_owner;
};

#endif /* Unit_H */

/*
*	End Of File : Unit.h
*/
