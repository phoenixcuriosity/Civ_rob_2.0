/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.1.0
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

#include "LIB.h"

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

struct Vertex
{
	dot2D point;
	struct Color
	{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	} color;
};

class Sprite
{
public:
	Sprite
	(
		float x,
		float y,
		float width,
		float height
	);
	~Sprite();

private:
	void init
	(
		float x,
		float y,
		float width,
		float height
	);

public:

	void draw();

private:

	GLuint _vboID;
	sprite_square _coor;

};


#endif // !Sprite_H

