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

#include "ColorRGBA8.h"
#include "UV.h"

namespace R2D
{
struct dot2D
{
	float x;
	float y;
};

struct Vertex
{
	using ColorT = unsigned char;
	using ColorFloat = float;

	dot2D point;
	ColorRGBA8 color;
	UV uv;

	void setPoint(float x, float y)
	{
		point.x = x; point.y = y;
	}
	void setColor(ColorT r, ColorT g, ColorT b, ColorT a)
	{
		color.r = r; color.g = g; color.b = b; color.a = a;
	}
	void setUV(ColorFloat u, ColorFloat v)
	{
		uv.u = u; uv.v = v;
	}
};
}
