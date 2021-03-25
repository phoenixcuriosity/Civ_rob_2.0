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

#include "SpriteBatch.h"

namespace RealEngine2D
{
	
SpriteBatch::SpriteBatch()
: m_vbo(0), m_vao(0), m_sortType(GlyphSortType::NONE)
{

}
SpriteBatch::~SpriteBatch()
{
	m_glyphsPtr.clear();
}
void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin
(
	GlyphSortType sortType /* = GlyphSortType::TEXTURE */
)
{
	m_sortType = sortType;
	m_renderBatches.clear();
	m_glyphs.clear();
}

void SpriteBatch::end()
{
	m_glyphsPtr.resize(m_glyphs.size());
	for (unsigned int i(0); i < m_glyphs.size(); i++)
	{
		m_glyphsPtr[i] = &m_glyphs[i];
	}

	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::draw
(
	const glm::vec4& destRec,
	const  glm::vec4& uvRect,
	GLuint texture,
	float depth,
	const  ColorRGBA8& color
)
{
	m_glyphs.emplace_back(destRec, uvRect, texture, depth, color);
}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(m_vao);

	for (unsigned int i(0); i < m_renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_renderBatches[i]._texture);

		glDrawArrays(GL_TRIANGLES, m_renderBatches[i]._offset, m_renderBatches[i]._numVertices);
	}
	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches()
{
	if (m_glyphs.empty()) return;

	std::vector<Vertex> vertices;
	vertices.resize(m_glyphs.size() * 6);

	int cv(0);
	int offset(0);
	m_renderBatches.emplace_back(0, 6, m_glyphsPtr[0]->texture);
	vertices[cv++] = m_glyphsPtr[0]->topLeft;
	vertices[cv++] = m_glyphsPtr[0]->BottomLeft;
	vertices[cv++] = m_glyphsPtr[0]->BottomRight;
	vertices[cv++] = m_glyphsPtr[0]->BottomRight;
	vertices[cv++] = m_glyphsPtr[0]->topRight;
	vertices[cv++] = m_glyphsPtr[0]->topLeft;
	offset += 6;

	for (unsigned int cg(1); cg < m_glyphs.size(); cg++)
	{
		if (m_glyphsPtr[cg]->texture != m_glyphsPtr[cg - 1]->texture)
		{
			m_renderBatches.emplace_back(offset, 6, m_glyphsPtr[cg]->texture);
		}
		else
		{
			m_renderBatches.back()._numVertices += 6;
		}
		
		vertices[cv++] = m_glyphsPtr[cg]->topLeft;
		vertices[cv++] = m_glyphsPtr[cg]->BottomLeft;
		vertices[cv++] = m_glyphsPtr[cg]->BottomRight;
		vertices[cv++] = m_glyphsPtr[cg]->BottomRight;
		vertices[cv++] = m_glyphsPtr[cg]->topRight;
		vertices[cv++] = m_glyphsPtr[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW); /* delete data */
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void SpriteBatch::createVertexArray()
{
	if (m_vao == 0)
	{
		glGenVertexArrays(1, &m_vao);
	}
	glBindVertexArray(m_vao);


	if (m_vbo == 0)
	{
		glGenBuffers(1, &m_vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//pos
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, point));
	//color
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}

void SpriteBatch::sortGlyphs()
{
	switch (m_sortType)
	{
	case GlyphSortType::NONE :
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(m_glyphsPtr.begin(), m_glyphsPtr.end(), compareFrontToBack);
		break;
	case GlyphSortType::BACK_TO_FRONT :
		std::stable_sort(m_glyphsPtr.begin(), m_glyphsPtr.end(), compareBackToFront);
		break;
	case GlyphSortType::TEXTURE :
		std::stable_sort(m_glyphsPtr.begin(), m_glyphsPtr.end(), compareTexture);
		break;
	default:
		break;
	}

}

bool SpriteBatch::compareFrontToBack(const Glyph* a, const Glyph* b)
{
	return (a->depth < b->depth);
}
bool SpriteBatch::compareBackToFront(const Glyph* a, const Glyph* b)
{
	return (a->depth > b->depth);
}
bool SpriteBatch::compareTexture(const Glyph* a, const Glyph* b)
{
	return (a->texture < b->texture);
}

}




