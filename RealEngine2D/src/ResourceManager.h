/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.7.0
	file version : 1.4

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

#include "TextureCache.h"
#include "Files.h"
#include "SpriteFont.h"
#include "GLSLProgram.h"
#include "CardinalDirection.h"

#define EXTENSION_PNG ".png"

namespace RealEngine2D
{
	typedef std::map<CardinalDirections, CardinalDirection> CardinalDirectionMapping;


	/* STATIC CLASS */
	class ResourceManager
	{

	public:
		static std::unique_ptr<GLTexture>& getTexture(const std::string& name);

		static File* getFile(const e_Files name);
		static void initializeFilePath
		(
			const e_Files name,
			const std::string& path
		);
		static void modifyFilePath
		(
			const e_Files name,
			const std::string& path
		);

		static std::shared_ptr<RealEngine2D::SpriteFont>& getSpriteFont();
		static GLSLProgram& getGLSLProgram();

		static bool getTextFromFile
		(
			const e_Files name,
			MapTexts& mapTexts
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
		static std::shared_ptr<RealEngine2D::SpriteFont> m_spriteFont;
		static GLSLProgram m_gLSLProgram;
		static ColorRGBA8C m_colorsRGBA8;
		static CardinalDirectionMapping m_cardinalDirectionMapping;
	};
}

#endif // !ResourceManager_H

