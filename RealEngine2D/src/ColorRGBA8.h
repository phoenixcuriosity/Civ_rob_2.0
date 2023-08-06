/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.0.0
	file version : 1.3

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

#ifndef ColorRGBA8_H
#define ColorRGBA8_H

#include <SDL\glew.h>
#include <map>
#include <string>

namespace RealEngine2D
{

struct ColorRGBA8
{
	ColorRGBA8() : r(0), g(0), b(0), a(255) {};
	ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A)
		: r(R), g(G), b(B), a(A) {};

	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

const ColorRGBA8 COLOR_WHITE(255, 255, 255, 255);
const ColorRGBA8 COLOR_BLACK(0, 0, 0, 255);

const ColorRGBA8 COLOR_LIGHT_GREY(192, 192, 192, 255);
const ColorRGBA8 COLOR_GREY(127, 127, 127, 255);
const ColorRGBA8 COLOR_DARK_GREY(63, 63, 63, 255);

const ColorRGBA8 COLOR_RED(255, 0, 0, 255);
const ColorRGBA8 COLOR_GREEN(0, 255, 0, 255);
const ColorRGBA8 COLOR_BLUE(0, 0, 255, 255);

const ColorRGBA8 COLOR_GOLD(205, 127, 50, 255);

const ColorRGBA8 COLOR_WHITE_T50(255, 255, 255, 128);
const ColorRGBA8 COLOR_WHITE_T25(255, 255, 255, 64);

typedef std::map<std::string, ColorRGBA8> ColorRGBA8Map;

class ColorRGBA8C
{
public:
	ColorRGBA8C() {};
	~ColorRGBA8C() {};

	void initializeRGBA8Map();
	ColorRGBA8& getRGBA8Color
	(
		const std::string colorName
	);

private:

	ColorRGBA8Map m_colorRGBA8Map;
};

}

#endif