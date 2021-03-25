/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.3.0
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

#include "ResourceManager.h"

using namespace RealEngine2D;

Sprite::Sprite
(
	float x,
	float y,
	float width,
	float height,
	const std::string& filePath
)
: m_vboID(0), m_coor{0,0,0,0}, m_gLTexture(nullptr)
{
	init(x, y, width, height, filePath);
}

Sprite::~Sprite()
{
	if (m_vboID)
	{
		glDeleteBuffers(1, &m_vboID);
	}
	if (nullptr != m_gLTexture)
	{
		delete m_gLTexture;
	}
}

void Sprite::init
(
	float x,
	float y,
	float width,
	float height,
	const std::string& filePath
)
{
	m_coor.origin.x = x;
	m_coor.origin.y = y;
	m_coor.width = width;
	m_coor.height = height;

	if (m_vboID == 0)
	{
		glGenBuffers(1, &m_vboID);
	}

	m_gLTexture = ResourceManager::getTexture(filePath);

	Vertex vertexData[6] = {};

	vertexData[0].setPoint(m_coor.origin.x + m_coor.width, m_coor.origin.y + m_coor.height);
	vertexData[0].setColor(255, 255, 255, 255);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].setPoint(m_coor.origin.x, m_coor.origin.y + m_coor.height);
	vertexData[1].setColor(255, 255, 255, 0255);
	vertexData[1].setUV(0.0f, 1.0f);
	 
	vertexData[2].setPoint(m_coor.origin.x, m_coor.origin.y);
	vertexData[2].setColor(255, 255, 255, 255);
	vertexData[2].setUV(0.0f, 0.0f);

	vertexData[3] = vertexData[2];

	vertexData[4].setPoint(m_coor.origin.x + m_coor.width, m_coor.origin.y);
	vertexData[4].setColor(255, 255, 255, 255);
	vertexData[4].setUV(1.0f, 0.0f);

	vertexData[5] = vertexData[0];

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, m_gLTexture->GETid());

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}