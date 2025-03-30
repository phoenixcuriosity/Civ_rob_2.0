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

#include <vector>
#include <memory>
#include "Unit.h"
#include "UnitFactory.h"

class UnitManager
{
private:
	std::vector<std::shared_ptr<Unit>> m_units;

	static UnitFactory& getFactory()
	{
		static UnitFactory factory;
		return factory;
	}

public:

	UnitManager() : m_units()
	{
		getFactory();
	}

	void addUnit(const Unit::UnitName& name, const Unit::Coor& coor, Player* owner)
	{
		m_units.push_back(getFactory().createUnit(name, coor, owner));
	}

	void addEmptyUnit()
	{
		m_units.push_back(getFactory().createUnit());
	}

	void removeUnit(const size_t index)
	{
		if (index < m_units.size())
		{
			m_units.erase(m_units.begin() + index);
		}
	};

	const std::vector<std::shared_ptr<Unit>>& getUnits() const { return m_units; }
};