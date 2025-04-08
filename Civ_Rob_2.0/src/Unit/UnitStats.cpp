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

#include "UnitStats.h"

void
UnitStats
::levelup()noexcept
{
	level++;

	stats_max.life += static_cast<unsigned int>(ceil(static_cast<double>(stats_max.life) / static_cast<double>(COEF_DIV_LEVELUP)));
	life = stats_max.life;

	/* Todo */
	//heal();
}

void
UnitStats
::healNeutral()noexcept
{
	life += static_cast<unsigned int>(ceil(static_cast<double>(stats_max.life) / static_cast<double>(COEF_DIV_HEAL_NO_APPARTENANCE)));
	if (life > stats_max.life)
	{
		life = stats_max.life;
	}
};

void
UnitStats
::healFriendly()noexcept
{
	life += static_cast<unsigned int>(ceil(static_cast<double>(stats_max.life) / static_cast<double>(COEF_DIV_HEAL_APPARTENANCE)));
	if (life > stats_max.life)
	{
		life = stats_max.life;
	}
};