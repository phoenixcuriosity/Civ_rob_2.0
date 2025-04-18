﻿/*

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

#include "UnitFactory.h"

#include "Player.h"

UnitFactory
::UnitFactory() : IRegisterLoadAble(), IRegister()
{
	UnitTemplate::getSingleton(addSubscriber());
	IRegisterLoadAble::load();
};

R2D::RegisterPairVector
UnitFactory
::addSubscriber()
{
	R2D::RegisterPairVector registerLoad{ {this, typeid(UnitTemplate)} };
	return registerLoad;
};

UnitFactory::UnitPtrT
UnitFactory
::createUnit(const Unit::UnitName& name, const Unit::Coor& coor, PlayerPtrT owner)
{
	const UnitTemplate::Template unitToBuild{ UnitTemplate::getSingleton().getTemplate(name) };

	return std::make_shared<Unit>
		(
			name,
			coor,
			UnitTemplate::UnitStat
			{
				unitToBuild.type,
				unitToBuild.life,
				unitToBuild.atq,
				unitToBuild.def,
				unitToBuild.movement,
				unitToBuild.numberOfAttack,
				unitToBuild.level
			},
			unitToBuild.maintenance,
			owner);
}

UnitFactory::UnitPtrT
UnitFactory
::createUnit()
{
	return std::make_shared<Unit>();
}