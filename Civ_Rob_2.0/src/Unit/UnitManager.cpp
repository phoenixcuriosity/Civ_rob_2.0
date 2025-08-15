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

#include "UnitManager.h"

void
unit::UnitManager
::addUnit(const Unit::UnitName& name, const Unit::Coor& coor, PlayerPtrT owner)
{
	m_units.push_back(getFactory().createUnit(name, coor, owner));
}

void
unit::UnitManager
::addEmptyUnit(PlayerPtrT owner)
{
	m_units.push_back(getFactory().createUnit(owner));
}

void
unit::UnitManager
::removeUnit(const size_t index)
{
	if (index < m_units.size())
	{
		m_units.erase(m_units.begin() + index);
	}
};

void
unit::UnitManager
::nextTurn(const unsigned int index, const MatriceMap& matriceMap)
{
	for (auto& unit : m_units)
	{
		unit->nextTurn(index, matriceMap);
	}
}
