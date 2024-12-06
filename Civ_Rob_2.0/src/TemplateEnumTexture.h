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

#ifndef TemplateEnumTexture_H
#define TemplateEnumTexture_H

#include "LIB.h"

#include <SDL/glew.h>
#include <type_traits>

constexpr size_t ARRAY_SIZE_OFFSET = 1;

template <typename Enum, Enum firstValue, Enum lastValue>
class EnumArray 
{
	static_assert(std::is_enum_v<Enum>, "Template parameter must be an enum type");
	static_assert(static_cast<size_t>(firstValue) == 0, "First Enum value must be 0");
	static_assert(static_cast<size_t>(lastValue) > static_cast<size_t>(firstValue), "Last Enum value must be greater than 0");

private:
	std::array<GLuint, (static_cast<size_t>(lastValue) + ARRAY_SIZE_OFFSET)> values;

public:
	EnumArray() : values{} {}

	GLuint& operator[](Enum index)
	{
		return values[static_cast<size_t>(index)];
	}

	const GLuint& operator[](Enum index) const
	{
		return values[static_cast<size_t>(index)];
	}
};


#endif // !TemplateEnumTexture_H
