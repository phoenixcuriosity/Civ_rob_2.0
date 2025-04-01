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

#include "CityFactory.h"

#include "CityNameTemplate.h"

CityFactory
::CityFactory() : IRegisterLoadAble(), IRegister()
{
	CityNameTemplate::getSingleton(addSubscriber());
	IRegisterLoadAble::load();
};

R2D::RegisterPairVector
CityFactory
::addSubscriber()
{
	R2D::RegisterPairVector registerLoad{ {this, typeid(CityNameTemplate)} };
	return registerLoad;
};

CityFactory::CityPtrT
CityFactory
::CreateCity()
{
	return std::make_shared<City>();
}

CityFactory::CityPtrT
CityFactory
::CreateCity(const CityName& cityName, const Coor coor, VectMapPtr& tiles)
{
	return std::make_shared<City>(cityName, coor, tiles);
}