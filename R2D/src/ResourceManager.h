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

#ifndef ResourceManager_H
#define ResourceManager_H

#include "API_fwd.h"

#include "Files.h"
#include "GLSLProgram.h"
#include "LoadingFileToString.h"
#include "SpriteFont.h"
#include "Text.h"
#include "TextureCache.h"

namespace R2D
{

	/* STATIC CLASS */
	class ResourceManager
	{

	public:
		static void loadTextureFromDir(const std::string& path);
		static void copyIdMap(IdMap& dest);
		static GLuint searchKeyInIdMap(const R2D::IdMap& idMap, const std::string& key);

		static File* getFile(const e_Files name);
		static void initializeFilePath
		(
			const e_Files name,
			const std::string& path
		);

		static std::string loadFileToString(const std::string& path);

		static SpriteFont_PtrT& getSpriteFont();
		static GLSLProgram& getGLSLProgram();

		static void getTextFromFile
		(
			const e_Files name,
			MapTexts& mapTexts
		);

		static void displayTextFromFile
		(
			/* IN */
			const MapTexts& mapTexts,
			const Window& window,
			/* INOUT */
			SpriteBatch& spriteBatchHUDStatic
		);
		
		static void initializeRGBA8Map();
		static ColorRGBA8& getRGBA8Color
		(
			/* IN */
			const std::string& colorName
		);

		static Justification getJustification
		(
			/* in */
			const std::string& justificationN
		);

		static void InitializeCardinalDirectionMapping
		(
			/* IN */
			const unsigned int tileSize
		);

		static CardinalDirection& getCardinalDirection
		(
			/* IN */
			const CardinalDirections cardinalDirections
		);

	private:
		static TextureCache m_textureCache;
		static Files m_files;
		static Text m_Text;
		static FileTools m_fileTools;
		static SpriteFont_PtrT m_spriteFont;
		static GLSLProgram m_gLSLProgram;
		static ColorRGBA8C m_colorsRGBA8;
		static CardinalDirectionMapping m_cardinalDirectionMapping;
	};
}

#endif // !ResourceManager_H

