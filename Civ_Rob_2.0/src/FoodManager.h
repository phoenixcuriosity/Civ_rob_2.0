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

#ifndef FoodManager_H
#define FoodManager_H

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"

#include "T_Citizen.h"

enum class FoodManagerType 
{
	famine		= 0,
	neutral		= 1,
	surplus		= 2
};


class FoodManager
{
public:

	FoodManager
	(
		const VectCitizen& citizens,
		const unsigned int& emotion
	);
	~FoodManager() {};

public:

	FoodManagerType updateGetFoodStatus();

	void updateFoodStockFromReducePop();
	void updateFoodStockFromIncreasePop();

	void emptyFoodStock();

	double getFoodBalanceForConversion() const { return m_foodBalance; };
	void ResetFoodBalanceFromConversion() { m_foodBalance = 0.0; };
	void setFoodBalance(double foodBalance) { m_foodBalance = foodBalance; };

	inline void setFoodSurplusPreviousTurn(const double foodSurplusPreviousTurn)
	{
		m_foodSurplusPreviousTurn = foodSurplusPreviousTurn;
	};

	inline virtual double GETfoodStockPerc()const
	{
		return ((m_foodStock / m_foodToLevelUp) * PERCENTAGE::ONE_HUNDRED); 
	};

	double getFoodStock() const					{ return m_foodStock; };
	double getFoodSurplusPreviousTurn() const	{ return m_foodSurplusPreviousTurn; };
	double getFoodToLevelUp() const				{ return m_foodToLevelUp; };

	void setFoodStock(double foodStock)								{ m_foodStock = foodStock; };
	void setFoodToLevelUp(double foodToLevelUp)						{ m_foodToLevelUp = foodToLevelUp; };
	
private:

	void updateFoodBalance();
	void updateFoodConsumption();
	void updateFoodToLevelUp();

	double getFoodToLevelUpFromPop(const size_t nbPop) const;

	void updateEmotionCoef();


private:

	const VectCitizen& m_citizens;
	const unsigned int& m_emotion;

	double m_foodStock;

	double m_foodBalance;
	double m_foodConsumption;

	double m_foodSurplusPreviousTurn;

	double m_foodToLevelUp;

	double m_emotionCoef;

	FoodManagerType m_foodManagerType;
};


#endif /* FoodManager_H */

/*
*	End Of File : FoodManager.h
*/
