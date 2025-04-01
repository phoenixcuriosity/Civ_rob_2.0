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

#include <R2D/src/IRegister.h>
#include "City.h"

class CityFactory : public R2D::IRegisterLoadAble<jsoncons::ojson>
{
private:
	using Coor = R2D::IMoveable::Coor;
	using CityName = std::string;
	using CityPtrT = std::shared_ptr<City>;
	R2D::RegisterPairVector addSubscriber();

public:
	CityFactory();

	CityPtrT CreateCity();
	CityPtrT CreateCity(const CityName& cityName, const Coor coor, VectMapPtr& tiles);
};