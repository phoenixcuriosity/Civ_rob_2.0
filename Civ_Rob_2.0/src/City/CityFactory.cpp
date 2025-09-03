﻿/*

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

#include "CityFactory.h"

#include "CityNameTemplate.h"

city::CityFactory
::CityFactory() : m_loader(std::make_shared<R2D::RegisterLoadAbleOjson>())
{
	CityNameTemplate::getSingleton(addSubscriber());
	m_loader->load();
};

R2D::RegisterPairVector
city::CityFactory
::addSubscriber()
{
	R2D::RegisterPairVector registerLoad{ {m_loader, typeid(CityNameTemplate)} };
	return registerLoad;
};

city::CityFactory::CityPtrT
city::CityFactory
::CreateCity(const PlayerPtrT& player)
{
	return std::make_shared<City>(player);
}

city::CityFactory::CityPtrT
city::CityFactory
::CreateCity(const CityNamePlayerId& id, const Coor coor, VectMapPtr& tiles, const PlayerPtrT& player)
{
	return std::make_shared<City>(CityNameTemplate::getSingleton().getCityName(id.playerId, id.cityVectSize), coor, tiles, player);
}