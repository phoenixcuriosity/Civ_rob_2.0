﻿/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)

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

#ifndef T_Player_H
#define T_Player_H

#include "LIB.h"


enum class MajorAge
{
	Nomade,
	Farming,
	Stone,
	Bronze,
	Iron,
	Antiquity,
	Vikings,
	Crusade,
	Renaissance,
	Colonization,
	Enlightenment,
	Industrial,
	Modern,
	Cyber,
	Stellar,
	Galactic
};

struct GoldStats
{
	double gold;
	double goldBalance;
	double income;
	double cost;

	double taxIncome;
	double commerceIncome;
	double goldConversionSurplus;

	double armiesCost;
	double buildingsCost;
};

struct OnOffDisplay
{
	bool showContextGoldStats;
};

#endif // !T_Player_H


