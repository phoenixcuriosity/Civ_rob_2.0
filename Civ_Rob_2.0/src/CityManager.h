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

#pragma once

#include "CityFactory.h"

class CityManager
{
private:
	using Coor = R2D::IMoveable::Coor;
	using CityName = std::string;
	using CityPtrTVector = std::vector<std::shared_ptr<City>>;
	CityPtrTVector m_city;

	static CityFactory& getFactory()
	{
		static CityFactory factory;
		return factory;
	}

public:
	CityManager() : m_city()
	{
		getFactory();
	}

	void addCity(const CityName& cityName, const Coor coor, VectMapPtr& tiles)
	{
		m_city.push_back(getFactory().CreateCity(cityName, coor, tiles));
	}

	void addEmptyCity()
	{
		m_city.push_back(getFactory().CreateCity());
	}

	void removeCity(const size_t index)
	{
		if (index < m_city.size())
		{
			m_city.erase(m_city.begin() + index);
		}
	};

	const CityPtrTVector& getCities() const { return m_city; }
	CityPtrTVector& getCities() { return m_city; }
};