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

#include "SpriteBatch.h"

namespace RealEngine2D
{
	
SpriteBatch::SpriteBatch()
: _vbo(0), _vao(0), _sortType(GlyphSortType::NONE)
{

}
SpriteBatch::~SpriteBatch()
{
	for (unsigned int i(0); i < _glyphs.size(); i++)
	{
		if (nullptr != _glyphs[i])
		{
			delete _glyphs[i];
		}
	}
	_glyphs.clear();
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
	_sortType = sortType;
	_renderBatches.clear();
	for (unsigned int i(0); i < _glyphs.size(); i++)
	{
		if (nullptr != _glyphs[i])
		{
			delete _glyphs[i];
		}
	}
	_glyphs.clear();
}

void SpriteBatch::end()
{
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
	Glyph* nGlyph = new Glyph;
	nGlyph->texture = texture;
	nGlyph->depth = depth;

	nGlyph->topLeft.color = color;
	nGlyph->topLeft.setPoint(destRec.x, destRec.y + destRec.w);
	nGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
	
	nGlyph->BottomLeft.color = color;
	nGlyph->BottomLeft.setPoint(destRec.x, destRec.y);
	nGlyph->BottomLeft.setUV(uvRect.x, uvRect.y);
		
	nGlyph->BottomRight.color = color;
	nGlyph->BottomRight.setPoint(destRec.x + destRec.z, destRec.y);
	nGlyph->BottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
		  
	nGlyph->topRight.color = color;
	nGlyph->topRight.setPoint(destRec.x + destRec.z, destRec.y + destRec.w);
	nGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	_glyphs.push_back(nGlyph);
}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(_vao);

	for (unsigned int i(0); i < _renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i]._texture);

		glDrawArrays(GL_TRIANGLES, _renderBatches[i]._offset, _renderBatches[i]._numVertices);
	}
	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches()
{
	if (_glyphs.empty()) return;

	std::vector<Vertex> vertices;
	vertices.resize(_glyphs.size() * 6);

	int cv(0);
	int offset(0);
	_renderBatches.emplace_back(0, 6, _glyphs[0]->texture);
	vertices[cv++] = _glyphs[0]->topLeft;
	vertices[cv++] = _glyphs[0]->BottomLeft;
	vertices[cv++] = _glyphs[0]->BottomRight;
	vertices[cv++] = _glyphs[0]->BottomRight;
	vertices[cv++] = _glyphs[0]->topRight;
	vertices[cv++] = _glyphs[0]->topLeft;
	offset += 6;

	for (unsigned int cg(1); cg < _glyphs.size(); cg++)
	{
		if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture)
		{
			_renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
		}
		else
		{
			_renderBatches.back()._numVertices += 6;
		}
		
		vertices[cv++] = _glyphs[cg]->topLeft;
		vertices[cv++] = _glyphs[cg]->BottomLeft;
		vertices[cv++] = _glyphs[cg]->BottomRight;
		vertices[cv++] = _glyphs[cg]->BottomRight;
		vertices[cv++] = _glyphs[cg]->topRight;
		vertices[cv++] = _glyphs[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW); /* delete data */
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void SpriteBatch::createVertexArray()
{
	if (_vao == 0)
	{
		glGenVertexArrays(1, &_vao);
	}
	glBindVertexArray(_vao);


	if (_vbo == 0)
	{
		glGenBuffers(1, &_vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

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
	switch (_sortType)
	{
	case GlyphSortType::NONE :
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
		break;
	case GlyphSortType::BACK_TO_FRONT :
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
		break;
	case GlyphSortType::TEXTURE :
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
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




