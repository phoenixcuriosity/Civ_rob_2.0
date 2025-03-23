/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2025 (robin.sauter@orange.fr)

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

#include "UnitTemplate.h"

class UnitStats : public UnitTemplate::UnitStat
{
private:
	using MovementType = UnitTemplate::Movement_Type;
	static constexpr unsigned int ZERO_NUMBER_OF_ATTACK = 0;
	static constexpr unsigned int COEF_DIV_LEVELUP = 4;
	static constexpr unsigned int COEF_DIV_HEAL_NO_APPARTENANCE = 20;
	static constexpr unsigned int COEF_DIV_HEAL_APPARTENANCE = 5;
	static constexpr unsigned int NO_MOVEMENT = 0;
public:
	UnitStats()noexcept : UnitStat(), stats_max() {};
	UnitStats(const MovementType qtype, const unsigned int qlife, const unsigned int qatq, const unsigned int qdef,
				const unsigned int qmovement, const unsigned int qnumberOfAttack, const unsigned int qlevel)
		:   UnitStat(qtype, qlife, qatq, qdef, qmovement, qnumberOfAttack, qlevel),
			stats_max(qtype, qlife, qatq, qdef, qmovement, qnumberOfAttack, qlevel) {};

	void resetStatsToMax() noexcept{ set(stats_max.movementType, stats_max.life, stats_max.atq, stats_max.def, stats_max.movement, stats_max.numberOfAttack, stats_max.level);};
	void resetMovement() noexcept { movement = stats_max.movement; };
	void resetNumberOfAttack() noexcept { numberOfAttack = stats_max.numberOfAttack; };

	bool isGroundMovement_Type() const noexcept		{ return movementType == MovementType::ground; };
	bool isAirMovement_Type() const noexcept		{ return movementType == MovementType::air; };
	bool isWaterMovement_Type()	const noexcept		{ return movementType == MovementType::water; };
	bool isDeepWaterMovement_Type() const noexcept  { return movementType == MovementType::deepwater; };
	bool isPossibleToAttack()const noexcept			{ return numberOfAttack > ZERO_NUMBER_OF_ATTACK; };
	bool isFullLife()const noexcept					{ return life == stats_max.life; };
	bool canMove()const noexcept					{ return movement > NO_MOVEMENT; };

	inline int GETlife() const noexcept { return life; };
	inline int GETmaxlife()	const noexcept { return stats_max.life; };

	void levelup()noexcept;
	void healNeutral()noexcept;
	void healFriendly()noexcept;

	inline void Blockmovement() noexcept { movement = NO_MOVEMENT; };

protected:
	UnitStat stats_max;
};