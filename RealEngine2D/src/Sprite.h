/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.2.0
	file version : 1.0

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

#ifndef Sprite_H
#define Sprite_H


#include "GLTexture.h"

namespace RealEngine2D
{
	struct dot2D
	{
		float x;
		float y;
	};

	struct sprite_square
	{
		dot2D origin;
		float width;
		float height;
	};

	struct ColorRGBA8
	{
		ColorRGBA8() : r(0), g(0), b(0), a(255){};
		ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A)
		: r(R), g(G), b(B), a(A) {};

		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	const ColorRGBA8 COLOR_WHITE(255, 255, 255, 255);
	const ColorRGBA8 COLOR_BLACK(0, 0, 0, 255);

	struct UV
	{
		float u;
		float v;
	};

	struct Vertex
	{
		dot2D point;
		ColorRGBA8 color;
		UV uv;

		void setPoint(float x, float y)
		{
			point.x = x; point.y = y;
		}
		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r; color.g = g; color.b = b; color.a = a;
		}
		void setUV(GLfloat u, GLfloat v)
		{
			uv.u = u; uv.v = v;
		}
	};

	class Sprite
	{
	public:
		Sprite
		(
			float x,
			float y,
			float width,
			float height,
			const std::string& filePath
		);
		~Sprite();

	private:
		void init
		(
			float x,
			float y,
			float width,
			float height,
			const std::string& filePath
		);

	public:

		void draw();

	public:

		inline GLTexture* GETgLTexture() { return _gLTexture; };

	private:

		GLuint _vboID;
		sprite_square _coor;
		GLTexture* _gLTexture;
	};
}

#endif // !Sprite_H

