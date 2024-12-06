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

#ifndef API_fwd_H
#define API_fwd_H

#include <map>
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>

#include <SDL\glew.h>

namespace R2D
{
	struct ColorRGBA8;
	struct dot2D;
	struct Text_t;
	struct UV;
	struct Vertex;

	class AudioEngine;
	class Camera2D;
	class CardinalDirection;
	class ColorRGBA8C;
	class ErrorLog;
	class ExitFromError;
	class Glyph;
	class GLSLProgram;
	class GLTexture;
	class IGameScreen;
	class IMainGame;
	class InputManager;
	class Music;
	class RenderBatch;
	class ResourceManager;
	class CScreen;
	class ScreenList;
	class SpriteBatch;
	class Text;
	class TextureCache;
	class tinyXml2;
	class WidgetLabel;
	class Window;

	enum WindowFlags : unsigned int;

	enum class CardinalDirections;
	enum class e_Files;
	enum class EstWest;
	enum class GlyphSortType;
	enum class NorthSouth;
	enum class ScreenState;

	typedef std::map<CardinalDirections, CardinalDirection> CardinalDirectionMapping;
	typedef std::map<std::string, ColorRGBA8> ColorRGBA8Map;
	typedef std::unordered_map<std::string, GLuint> IdMap;
	typedef std::map<std::string, Text_t> MapTexts;
	typedef std::vector<GLuint> VectID;
}

#endif // !API_fwd_H

