/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2024 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.10.0
	file version : 1.1

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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "FoodManager.h"
#include "Citizen.h"

namespace FOOD_MANAGER
{
	const double ZERO_FOOD = 0.0;

	const double OFFSET_FOOD_LEVEL = 15.0;
	const double COEF1_MULT_FOOD_LEVEL = 6.0;
	const double COEF2_MULT_FOOD_LEVEL = 1.8;

	const double MULT_FOOD_CONSUMPTION = 2.0;

	const size_t ONE_POP = 1;

	namespace EMOTION_RANGE
	{
		/* Define the maximum range of emotion */
		const double MAX = 100.0;

		/* Define the minimum range of emotion */
		const double MIN = 0.0;

		/* Define the mean emotion */
		const double MEAN = ((MAX + MIN) / 2.0);

		/* Define the mean value of emotion range */
		const double SCALE_MEAN = ((abs(MAX) + abs(MIN)) / 2.0);
	}
}

FoodManager::FoodManager
(
	const VectCitizen& citizens,
	const unsigned int& emotion
)
: 
m_citizens(citizens),
m_emotion(emotion),
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
	m_foodToLevelUp = getFoodToLevelUpFromPop(m_citizens.size());
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

void FoodManager::updateFoodBalance()
{
	/* Reset to Zero */
	m_foodBalance = FOOD_MANAGER::ZERO_FOOD;

	/* Add Food from Citizen*/
	for (const auto& c : m_citizens)
	{
		m_foodBalance += c->GETfood();
	}

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
		(static_cast<double>(m_citizens.size()) - FOOD_MANAGER::ONE_POP);
}

void FoodManager::updateFoodToLevelUp()
{
	m_foodToLevelUp = getFoodToLevelUpFromPop(m_citizens.size());
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
	m_emotionCoef = static_cast<double>(m_emotion) / FOOD_MANAGER::EMOTION_RANGE::SCALE_MEAN;
}

/*
*	End Of File : FoodManager.cpp
*/