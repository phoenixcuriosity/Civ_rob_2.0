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

R2D::TextureCache R2D::ResourceManager::m_textureCache;
R2D::Files R2D::ResourceManager::m_files;
R2D::Text R2D::ResourceManager::m_Text;
R2D::FileTools R2D::ResourceManager::m_fileTools;
std::shared_ptr<R2D::SpriteFont> R2D::ResourceManager::m_spriteFont;
R2D::GLSLProgram R2D::ResourceManager::m_gLSLProgram;
R2D::ColorRGBA8C R2D::ResourceManager::m_colorsRGBA8;
R2D::ResourceManager::CardinalDirectionMapping R2D::ResourceManager::m_cardinalDirectionMapping;

void R2D::ResourceManager::loadTextureFromDir(const std::string& path)
{
	m_textureCache.loadTextureFromDir(path);
}

void R2D::ResourceManager::copyIdMap(R2D::IdMap& dest)
{
	m_textureCache.copyIdMap(dest);
}

GLuint R2D::ResourceManager::searchKeyInIdMap(const R2D::IdMap& idMap, const std::string& key)
{
	return TextureCache::searchKeyInIdMap(idMap, key);
}

R2D::File* R2D::ResourceManager::getFile(const R2D::e_Files name)
{
	return m_files.getFile(name);
}

void R2D::ResourceManager::initializeFilePath
(
	const R2D::e_Files name,
	const std::string& path
)
{
	m_files.initializePath(name, path);
}

std::string R2D::ResourceManager::loadFileToString
(
	const std::string& path
)
{
	return m_fileTools.loadFileToString(path);
}

std::shared_ptr<R2D::SpriteFont>& R2D::ResourceManager::getSpriteFont()
{
	return m_spriteFont;
}

R2D::GLSLProgram& R2D::ResourceManager::getGLSLProgram()
{
	return m_gLSLProgram;
}

void 
R2D::ResourceManager
::getTextFromFile(const e_Files name, MapTexts& mapTexts)
{
	m_Text.getTextFromFile(name, mapTexts);
}

void 
R2D::ResourceManager
::displayTextFromFile(	const R2D::MapTexts& mapTexts,
						const R2D::Window& window,
						R2D::SpriteBatch& spriteBatchHUDStatic)
{
	m_Text.displayTextFromFile(mapTexts, window, spriteBatchHUDStatic);
}

void R2D::ResourceManager::initializeRGBA8Map()
{
	m_colorsRGBA8.initializeRGBA8Map();
}

R2D::ColorRGBA8& R2D::ResourceManager::getRGBA8Color
(
	const std::string& colorName
)
{
	return m_colorsRGBA8.getRGBA8Color(colorName);
}

R2D::Justification
R2D::ResourceManager
::getJustification(const std::string& justificationN)
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

void 
R2D::ResourceManager
::InitializeCardinalDirectionMapping(const unsigned int tileSize)
{
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirection::Directions::North,
			{
				CardinalDirection::NorthSouth::north,
				CardinalDirection::EstWest::neutral,
				int(tileSize),
				CardinalDirection::PIXEL_DEFAULT
			}
		}
	);
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirection::Directions::NorthEst,
			{
				CardinalDirection::NorthSouth::north,
				CardinalDirection::EstWest::est,
				int(tileSize),
				int(tileSize)
			}
		}
	);
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirection::Directions::Est,
			{
				CardinalDirection::NorthSouth::neutral,
				CardinalDirection::EstWest::est,
				CardinalDirection::PIXEL_DEFAULT,
				int(tileSize)
			}
		}
	);
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirection::Directions::SouthEst,
			{
				CardinalDirection::NorthSouth::south,
				CardinalDirection::EstWest::est,
				-int(tileSize),
				int(tileSize)
			}
		}
	);
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirection::Directions::South,
			{
				CardinalDirection::NorthSouth::south,
				CardinalDirection::EstWest::neutral,
				-int(tileSize),
				CardinalDirection::PIXEL_DEFAULT
			}
		}
	);
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirection::Directions::SouthWest,
			{
				CardinalDirection::NorthSouth::south,
				CardinalDirection::EstWest::west,
				-int(tileSize),
				-int(tileSize)
			}
		}
	);
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirection::Directions::West,
			{
				CardinalDirection::NorthSouth::neutral,
				CardinalDirection::EstWest::west,
				CardinalDirection::PIXEL_DEFAULT,
				-int(tileSize)
			}
		}
	);
	m_cardinalDirectionMapping.insert
	(
		{
			CardinalDirection::Directions::NorthWest,
			{
				CardinalDirection::NorthSouth::north,
				CardinalDirection::EstWest::west,
				int(tileSize),
				-int(tileSize)
			}
		}
	);
}

const R2D::CardinalDirection&
R2D::ResourceManager
::getCardinalDirection(const CardinalDirection::Directions cardinalDirections)
{
	try 
	{
		return m_cardinalDirectionMapping.at(cardinalDirections);
	}
	catch (const std::out_of_range& e) 
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::RESSOURCES_MANAGER, logS::WHAT::DIRECTION, logS::DATA::ERROR_DIRECTION, e.what());
		throw std::runtime_error("Direction not found");
	}
}