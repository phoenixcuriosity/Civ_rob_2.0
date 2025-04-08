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

#ifndef CityScreenEnumTexture_H
#define CityScreenEnumTexture_H

#include "TemplateEnumTexture.h"

enum class CityScreenEnumTexture
{
	deepwater,
	grass,
	grassIrr,
	water,
	coal,
	copper,
	fish,
	horse,
	iron,
	petroleum,
	stone,
	tree1,
	uranium,
	ColorPlayer0,
	ColorPlayer1,
	ColorPlayer2,
	ColorPlayer3,
	ColorPlayer4,
	ColorPlayer5,
	ColorPlayer6,
	ColorPlayer7,
	ColorPlayer8,
	ecstatic,
	happy,
	neutral,
	sad,
	angry,
	food,
	Hammer
};

typedef EnumArray<CityScreenEnumTexture, CityScreenEnumTexture::deepwater, CityScreenEnumTexture::Hammer> CityScreenTexture;

#endif // !CityScreenEnumTexture_H
