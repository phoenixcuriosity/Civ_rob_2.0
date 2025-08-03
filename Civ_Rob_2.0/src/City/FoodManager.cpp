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

#include "BuildManager.h"
#include "CitizenManager.h"
#include "Citizen.h"
#include "T_City.h"
#include "IFoodManagerVisitor.h"

#include <jsoncons/json.hpp>

city::FoodManager
::FoodManager(const CitizenManager& citizenManager)
:
m_citizenManager(citizenManager),
m_foodStock(ZERO_FOOD),
m_foodBalance(ZERO_FOOD),
m_foodConsumption(ZERO_FOOD),
m_foodSurplusPreviousTurn(ZERO_FOOD),
m_foodToLevelUp(ZERO_FOOD),
m_emotionCoef(0.0),
m_foodManagerType(FoodManagerType::neutral)
{
	updateFoodBalance();
	updateFoodToLevelUp();
}

city::FoodManager::FoodManagerType
city::FoodManager
::updateGetFoodStatus()
{
	updateFoodBalance();
	updateFoodToLevelUp();

	m_foodStock += m_foodBalance;

	if (m_foodStock < ZERO_FOOD)
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

void city::FoodManager::updateFoodStockFromReducePop()
{
	m_foodToLevelUp = getFoodToLevelUpFromPop(m_citizenManager.getCitizens().size());
	m_foodStock = m_foodToLevelUp - 1.0;
}

void city::FoodManager::updateFoodStockFromIncreasePop()
{
	m_foodStock -= m_foodToLevelUp;
}

void city::FoodManager::emptyFoodStock()
{
	m_foodStock = ZERO_FOOD;
}


/* ----------------------------------------------------------------------------------- */
/* NAME : convertWorkSurplusToFood													   */
/* ROLE : Convert work to food ; Place in m_foodSurplusPreviousTurn					   */
/* INPUT : double workSurplus : work surplus to convert into food					   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void city::FoodManager::convertWorkSurplusToFood
(
	const double workSurplus
)
{
	m_foodSurplusPreviousTurn = workSurplus * BuildManager::WORK_TO_FOOD;
}


void city::FoodManager::updateFoodBalance()
{
	/* Add Food from Citizen*/
	m_foodBalance = m_citizenManager.getFoodFromCitizen();

	/* Subtract consumption from Citizen */
	updateFoodConsumption();
	m_foodBalance -= m_foodConsumption;

	/* Add Surplus from conversion */
	m_foodBalance += m_foodSurplusPreviousTurn;
	m_foodSurplusPreviousTurn = ZERO_FOOD;

	/* Multiply by emotion */
	updateEmotionCoef();
	m_foodBalance *= m_emotionCoef;
}

void city::FoodManager::updateFoodConsumption()
{
	m_foodConsumption =
		MULT_FOOD_CONSUMPTION
		*
		(static_cast<double>(m_citizenManager.getCitizens().size()) - ONE_POP);
}

void city::FoodManager::updateFoodToLevelUp()
{
	m_foodToLevelUp = getFoodToLevelUpFromPop(m_citizenManager.getCitizens().size());
}

double city::FoodManager::getFoodToLevelUpFromPop(const size_t nbPop) const
{
	if (nbPop > ONE_POP)
	{
		return
			(
				OFFSET_FOOD_LEVEL
				+ (static_cast<double>(nbPop - ONE_POP) * COEF1_MULT_FOOD_LEVEL)
				+ pow((nbPop - ONE_POP), COEF2_MULT_FOOD_LEVEL)
				);
	}
	else
	{
		return OFFSET_FOOD_LEVEL;
	}

}

void city::FoodManager::updateEmotionCoef()
{
	m_emotionCoef = static_cast<double>(m_citizenManager.getEmotion()) / Citizen::EMOTION_MEAN;
}

void
city::FoodManager
::accept(IFoodManagerVisitor& visitor) const
{
	visitor.visit(*this);
}

void city::FoodManager::loadFromOjson(const jsoncons::ojson& jsonLoad)
{
	if	(
			jsonLoad.contains("m_foodStock") && jsonLoad.contains("m_foodBalance") && jsonLoad.contains("m_foodConsumption") &&
			jsonLoad.contains("m_foodSurplusPreviousTurn") && jsonLoad.contains("m_foodToLevelUp") && jsonLoad.contains("m_emotionCoef") &&
			jsonLoad.contains("m_foodManagerType")
		)
	{
		m_foodStock = jsonLoad["m_foodStock"].as<double>();
		m_foodBalance = jsonLoad["m_foodBalance"].as<double>();
		m_foodConsumption = jsonLoad["m_foodConsumption"].as<double>();
		m_foodSurplusPreviousTurn = jsonLoad["m_foodSurplusPreviousTurn"].as<double>();
		m_foodToLevelUp = jsonLoad["m_foodToLevelUp"].as<double>();
		m_emotionCoef = jsonLoad["m_emotionCoef"].as<double>();
		m_foodManagerType = static_cast<FoodManagerType>(jsonLoad["m_foodStock"].as<double>());
	}
}

/*
*	End Of File : FoodManager.cpp
*/