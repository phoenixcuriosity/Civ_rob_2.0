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

template <typename Enum, Enum Count>
class EnumArray 
{
	static_assert(std::is_enum_v<Enum>, "Template parameter must be an enum type");
	static_assert(static_cast<size_t>(Count) > 0, "Enum Count must be greater than 0");

private:
	std::array<GLuint, static_cast<size_t>(Count)> values;

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
