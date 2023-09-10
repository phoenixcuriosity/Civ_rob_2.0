/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.6.0
	file version : 1.2

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

#ifndef SpriteBatch_H
#define SpriteBatch_H

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
		GLuint Texture,
		float Depth,
		const  ColorRGBA8& color
	);

	GLuint texture;
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
		GLuint offset,
		GLuint numVertices,
		GLuint texture
	);

	GLuint _offset;
	GLuint _numVertices;
	GLuint _texture;

};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();

	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();

	void draw
	(
		const glm::vec4& destRec,
		const  glm::vec4& uvRect,
		GLuint texture,
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

	GLuint m_vbo;
	GLuint m_vao;
	GlyphSortType m_sortType;

	std::vector<Glyph*> m_glyphsPtr;
	std::vector<Glyph> m_glyphs;
	std::vector<RenderBatch> m_renderBatches;
};

}

#endif // !SpriteBatch_H



