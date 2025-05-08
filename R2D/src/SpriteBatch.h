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

#include "Vertex.h"
#include <glm\glm.hpp>
#include <vector>
#include <algorithm>

namespace R2D
{

/* Define to use for full Rect to draw */
const glm::vec4 FULL_RECT = { 0.0f, 0.0f, 1.0f, 1.0f };

enum class GlyphSortType
{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

class Glyph
{
public:
	Glyph
	(
		const glm::vec4& destRec,
		const  glm::vec4& uvRect,
		unsigned int Texture,
		float Depth,
		const  ColorRGBA8& color
	);

	unsigned int texture;
	float depth;

	Vertex topLeft;
	Vertex BottomLeft;
	Vertex BottomRight;
	Vertex topRight;
};

class RenderBatch
{
public:
	RenderBatch
	(
		unsigned int offset,
		unsigned int numVertices,
		unsigned int texture
	);

	unsigned int _offset;
	unsigned int _numVertices;
	unsigned int _texture;

};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();

	void begin(GlyphSortType sortType = GlyphSortType::FRONT_TO_BACK);
	void end();

	void draw
	(
		const glm::vec4& destRec,
		const  glm::vec4& uvRect,
		unsigned int texture,
		float depth,
		const  ColorRGBA8& color
	);

	void renderBatch();

private:
	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();

	static bool compareFrontToBack(const Glyph* a, const Glyph* b);
	static bool compareBackToFront(const Glyph* a, const Glyph* b);
	static bool compareTexture(const Glyph* a, const Glyph* b);

private:

	unsigned int m_vbo;
	unsigned int m_vao;
	GlyphSortType m_sortType;

	std::vector<Glyph*> m_glyphsPtr;
	std::vector<Glyph> m_glyphs;
	std::vector<RenderBatch> m_renderBatches;
};

}