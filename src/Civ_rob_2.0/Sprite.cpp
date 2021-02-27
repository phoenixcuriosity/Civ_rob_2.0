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

#include "Sprite.h"

Sprite::Sprite
(
	float x,
	float y,
	float width,
	float height
)
: _vboID(0), _coor{0,0,0,0}
{
	init(x, y, width, height);
}

Sprite::~Sprite()
{
	if (_vboID)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init
(
	float x,
	float y,
	float width,
	float height
)
{
	_coor.origin.x = x;
	_coor.origin.y = y;
	_coor.width = width;
	_coor.height = height;

	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];

	vertexData[0].point.x = _coor.origin.x + _coor.width;
	vertexData[0].point.y = _coor.origin.y + _coor.height;
	vertexData[0].color.r = 0; vertexData[0].color.g = 255; vertexData[0].color.b = 0; vertexData[0].color.a = 255;

	vertexData[1].point.x = _coor.origin.x;
	vertexData[1].point.y = _coor.origin.y + _coor.height;
	vertexData[1].color.r = 0; vertexData[1].color.g = 0; vertexData[1].color.b = 66; vertexData[1].color.a = 255;

	vertexData[2].point.x = _coor.origin.x;
	vertexData[2].point.y = _coor.origin.y;
	vertexData[2].color.r = 127; vertexData[2].color.g = 0; vertexData[2].color.b = 0; vertexData[2].color.a = 255;

	vertexData[3].point.x = _coor.origin.x;
	vertexData[3].point.y = _coor.origin.y;
	vertexData[3].color.r = 127; vertexData[3].color.g = 0; vertexData[3].color.b = 0; vertexData[3].color.a = 255;

	vertexData[4].point.x = _coor.origin.x + _coor.width;
	vertexData[4].point.y = _coor.origin.y;
	vertexData[4].color.r = 0; vertexData[4].color.g = 0; vertexData[4].color.b = 66; vertexData[4].color.a = 255;

	vertexData[5].point.x = _coor.origin.x + _coor.width;
	vertexData[5].point.y = _coor.origin.y + _coor.height;
	vertexData[5].color.r = 0; vertexData[5].color.g = 255; vertexData[5].color.b = 0; vertexData[5].color.a = 255;

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);

	//pos
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, point));
	//color
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}