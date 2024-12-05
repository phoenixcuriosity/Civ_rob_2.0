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

#include "FoodManager.h"

#include "Citizen.h"
#include "MainMap.h"
#include "T_City.h"

#include <jsoncons/json.hpp>

namespace FOOD_MANAGER
{
	constexpr double ZERO_FOOD = 0.0;

	constexpr double OFFSET_FOOD_LEVEL = 15.0;
	constexpr double COEF1_MULT_FOOD_LEVEL = 6.0;
	constexpr double COEF2_MULT_FOOD_LEVEL = 1.8;

	constexpr double MULT_FOOD_CONSUMPTION = 2.0;

	constexpr size_t ONE_POP = 1;

	namespace EMOTION_RANGE
	{
		/* Define the maximum range of emotion */
		constexpr double MAX = 100.0;

		/* Define the minimum range of emotion */
		constexpr double MIN = 0.0;

		/* Define the mean emotion */
		constexpr double MEAN = ((MAX + MIN) / 2.0);

		/* Define the mean value of emotion range */
		const double SCALE_MEAN = ((abs(MAX) + abs(MIN)) / 2.0);
	}
}

FoodManager::FoodManager(const CitizenManager& citizenManager)
: 
m_citizenManager(citizenManager),
m_foodStock(FOOD_MANAGER::ZERO_FOOD),
m_foodBalance(FOOD_MANAGER::ZERO_FOOD),
m_foodConsumption(FOOD_MANAGER::ZERO_FOOD),
m_foodSurplusPreviousTurn(FOOD_MANAGER::ZERO_FOOD),
m_foodToLevelUp(FOOD_MANAGER::ZERO_FOOD),
m_emotionCoef(0.0),
m_foodManagerType(FoodManagerType::neutral)
{
	updateFoodBalance();
	updateFoodToLevelUp();
}

FoodManagerType FoodManager::updateGetFoodStatus()
{
	updateFoodBalance();
	updateFoodToLevelUp();

	m_foodStock += m_foodBalance;

	if (m_foodStock < FOOD_MANAGER::ZERO_FOOD)
	{
		return FoodManagerType::famine;
	}
	else
	if(m_foodStock >= m_foodToLevelUp)
	{
		return FoodManagerType::surplus;
	}
	else
	{
		return FoodManagerType::neutral;
	}
}

void FoodManager::updateFoodStockFromReducePop()
{
	m_foodToLevelUp = getFoodToLevelUpFromPop(m_citizenManager.getCitizens().size());
	m_foodStock = m_foodToLevelUp - 1.0;
}

void FoodManager::updateFoodStockFromIncreasePop()
{
	m_foodStock -= m_foodToLevelUp;
}

void FoodManager::emptyFoodStock()
{
	m_foodStock = FOOD_MANAGER::ZERO_FOOD;
}


/* ----------------------------------------------------------------------------------- */
/* NAME : convertWorkSurplusToFood													   */
/* ROLE : Convert work to food ; Place in m_foodSurplusPreviousTurn					   */
/* INPUT : double workSurplus : work surplus to convert into food					   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void FoodManager::convertWorkSurplusToFood
(
	const double workSurplus
)
{
	m_foodSurplusPreviousTurn = workSurplus * MULTIPLIER::CONVERSION::WORK_TO_FOOD;
}


void FoodManager::updateFoodBalance()
{
	/* Add Food from Citizen*/
	m_foodBalance = m_citizenManager.getFoodFromCitizen();

	/* Subtract consumption from Citizen */
	updateFoodConsumption();
	m_foodBalance -= m_foodConsumption;

	/* Add Surplus from conversion */
	m_foodBalance += m_foodSurplusPreviousTurn;
	m_foodSurplusPreviousTurn = FOOD_MANAGER::ZERO_FOOD;

	/* Multiply by emotion */
	updateEmotionCoef();
	m_foodBalance *= m_emotionCoef;
}

void FoodManager::updateFoodConsumption()
{
	m_foodConsumption =
		FOOD_MANAGER::MULT_FOOD_CONSUMPTION
		*
		(static_cast<double>(m_citizenManager.getCitizens().size()) - FOOD_MANAGER::ONE_POP);
}

void FoodManager::updateFoodToLevelUp()
{
	m_foodToLevelUp = getFoodToLevelUpFromPop(m_citizenManager.getCitizens().size());
}

double FoodManager::getFoodToLevelUpFromPop(const size_t nbPop) const
{
	if (nbPop > FOOD_MANAGER::ONE_POP)
	{
		return
			(
				FOOD_MANAGER::OFFSET_FOOD_LEVEL
				+ (static_cast<double>(nbPop - FOOD_MANAGER::ONE_POP) * FOOD_MANAGER::COEF1_MULT_FOOD_LEVEL)
				+ pow((nbPop - FOOD_MANAGER::ONE_POP), FOOD_MANAGER::COEF2_MULT_FOOD_LEVEL)
				);
	}
	else
	{
		return FOOD_MANAGER::OFFSET_FOOD_LEVEL;
	}
	
}

void FoodManager::updateEmotionCoef()
{
	m_emotionCoef = static_cast<double>(m_citizenManager.getEmotion()) / FOOD_MANAGER::EMOTION_RANGE::SCALE_MEAN;
}

jsoncons::ojson FoodManager::saveToOjson()
{
	jsoncons::ojson value;
	value.insert_or_assign("m_foodStock", m_foodStock);
	value.insert_or_assign("m_foodBalance", m_foodBalance);
	value.insert_or_assign("m_foodConsumption", m_foodConsumption);
	value.insert_or_assign("m_foodSurplusPreviousTurn", m_foodSurplusPreviousTurn);
	value.insert_or_assign("m_foodToLevelUp", m_foodToLevelUp);
	value.insert_or_assign("m_emotionCoef", m_emotionCoef);
	value.insert_or_assign("m_foodManagerType", static_cast<size_t>(m_foodManagerType));
	return value;
}

/*
*	End Of File : FoodManager.cpp
*/