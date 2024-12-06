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

#include "ResourceManager.h"

#include "CardinalDirection.h"
#include "ErrorLog.h"
#include "GLTexture.h"
#include "Log.h"
#include "LogSentences.h"
#include "SpriteBatch.h"
#include "Window.h"

#include <iostream>
#include <stdexcept>

using namespace R2D;

TextureCache ResourceManager::m_textureCache;
Files ResourceManager::m_files;
Text ResourceManager::m_Text;
FileTools ResourceManager::m_fileTools;
std::shared_ptr<SpriteFont> ResourceManager::m_spriteFont;
GLSLProgram ResourceManager::m_gLSLProgram;
ColorRGBA8C ResourceManager::m_colorsRGBA8;
CardinalDirectionMapping ResourceManager::m_cardinalDirectionMapping;

void ResourceManager::loadTextureFromDir(const std::string& path)
{
	m_textureCache.loadTextureFromDir(path);
}

void ResourceManager::copyIdMap(IdMap& dest)
{
	m_textureCache.copyIdMap(dest);
}

GLuint ResourceManager::searchKeyInIdMap(const R2D::IdMap& idMap, const std::string& key)
{
	return TextureCache::searchKeyInIdMap(idMap, key);
}

File* ResourceManager::getFile(const e_Files name)
{
	return m_files.getFile(name);
}

void ResourceManager::initializeFilePath
(
	const e_Files name,
	const std::string& path
)
{
	m_files.initializePath(name, path);
}

std::string ResourceManager::loadFileToString
(
	const std::string& path
)
{
	return m_fileTools.loadFileToString(path);
}

std::shared_ptr<SpriteFont>& ResourceManager::getSpriteFont()
{
	return m_spriteFont;
}

GLSLProgram& ResourceManager::getGLSLProgram()
{
	return m_gLSLProgram;
}

void ResourceManager::getTextFromFile
(
	const e_Files name,
	MapTexts& mapTexts
)
{
	m_Text.getTextFromFile(name, mapTexts);
}

void ResourceManager::displayTextFromFile
(
	/* IN */
	const MapTexts& mapTexts,
	const Window& window,
	/* INOUT */
	SpriteBatch& spriteBatchHUDStatic
)
{
	m_Text.displayTextFromFile(mapTexts, window, spriteBatchHUDStatic);
}

void ResourceManager::initializeRGBA8Map()
{
	m_colorsRGBA8.initializeRGBA8Map();
}

ColorRGBA8& ResourceManager::getRGBA8Color
(
	const std::string& colorName
)
{
	return m_colorsRGBA8.getRGBA8Color(colorName);
}

Justification ResourceManager::getJustification
(
	/* in */
	const std::string& justificationN
)
{
	if (justificationN.compare("LEFT"))
	{
		return Justification::LEFT;
	}
	else
	if(justificationN.compare("MIDDLE"))
	{
		return Justification::MIDDLE;
	}
	else
	if (justificationN.compare("RIGHT"))
	{
		return Justification::RIGHT;
	}
	else
	{
		return Justification::LEFT;
	}
}


void ResourceManager::InitializeCardinalDirectionMapping
(
	/* IN */
	const unsigned int tileSize
)
{
	;
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirections::North,
			{
				NorthSouth::north,
				EstWest::neutral,
				int(tileSize),
				CARDINAL::PIXEL::DEFAULT
			}
		}
	);
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirections::NorthEst,
			{
				NorthSouth::north,
				EstWest::est,
				int(tileSize),
				int(tileSize)
			}
		}
	);
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirections::Est,
			{
				NorthSouth::neutral,
				EstWest::est,
				CARDINAL::PIXEL::DEFAULT,
				int(tileSize)
			}
		}
	);
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirections::SouthEst,
			{
				NorthSouth::south,
				EstWest::est,
				-int(tileSize),
				int(tileSize)
			}
		}
	);
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirections::South,
			{
				NorthSouth::south,
				EstWest::neutral,
				-int(tileSize),
				CARDINAL::PIXEL::DEFAULT
			}
		}
	);
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirections::SouthWest,
			{
				NorthSouth::south,
				EstWest::west,
				-int(tileSize),
				-int(tileSize)
			}
		}
	);
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirections::West,
			{
				NorthSouth::neutral,
				EstWest::west,
				CARDINAL::PIXEL::DEFAULT,
				-int(tileSize)
			}
		}
	);
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirections::NorthWest,
			{
				NorthSouth::north,
				EstWest::west,
				int(tileSize),
				-int(tileSize)
			}
		}
	);
}

CardinalDirection& ResourceManager::getCardinalDirection
(
	/* IN */
	const CardinalDirections cardinalDirections
)
{
	return m_cardinalDirectionMapping[cardinalDirections];
}