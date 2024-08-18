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

#include "..\..\Dependencies\tinyxml2\tinyxml2.h"

#include "CardinalDirection.h"
#include "ErrorLog.h"
#include "GLTexture.h"
#include "SpriteBatch.h"
#include "Window.h"

#include <iostream>
#include <stdexcept>

using namespace R2D;

TextureCache ResourceManager::m_textureCache;
Files ResourceManager::m_files;
std::shared_ptr<SpriteFont> ResourceManager::m_spriteFont;
GLSLProgram ResourceManager::m_gLSLProgram;
ColorRGBA8C ResourceManager::m_colorsRGBA8;
CardinalDirectionMapping ResourceManager::m_cardinalDirectionMapping;

std::unique_ptr<GLTexture>& ResourceManager::getTexture(const std::string& name)
{
	return m_textureCache.getTexture(name);
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

void ResourceManager::modifyFilePath
(
	const e_Files name,
	const std::string& path
)
{
	m_files.modifyPath(name, path);
}

std::shared_ptr<SpriteFont>& ResourceManager::getSpriteFont()
{
	return m_spriteFont;
}

GLSLProgram& ResourceManager::getGLSLProgram()
{
	return m_gLSLProgram;
}

bool ResourceManager::getTextFromFile
(
	/* IN */
	const e_Files name,
	/* OUT */
	MapTexts& mapTexts
)
{
	std::string errCheck("");
	tinyxml2::XMLDocument xmlDoc;
	Text blankText;

	/* Clear previous Texts */
	mapTexts.clear();

	if (xmlDoc.LoadFile(R2D::ResourceManager::getFile(name)->getPath().c_str()) == tinyxml2::XML_SUCCESS)
	{
		tinyxml2::XMLNode* pRoot = xmlDoc.FirstChild();
		if (nullptr == pRoot)
		{
			R2D::ErrorLog::logEvent("Error on getTextFromFile : nullptr == pRoot");
			return false;
		}

		tinyxml2::XMLNode* nTextRoot = pRoot->FirstChild();
		errCheck = nTextRoot->Value();
		if (errCheck.compare("Text") != 0) 
		{
			R2D::ErrorLog::logEvent("Error on getTextFromFile : errCheck.compare(Text) != 0");
			return false;
		}

		while (nullptr != nTextRoot)
		{
			tinyxml2::XMLNode* nText = nTextRoot->FirstChild();
			tinyxml2::XMLNode* nX = nText->NextSibling();
			tinyxml2::XMLNode* nY = nX->NextSibling();
			tinyxml2::XMLNode* nSize = nY->NextSibling();
			tinyxml2::XMLNode* nAlpha = nSize->NextSibling();
			tinyxml2::XMLNode* nColor = nAlpha->NextSibling();
			tinyxml2::XMLNode* nCenter = nColor->NextSibling();

			try
			{
				blankText.text = nText->FirstChild()->Value();
				blankText.x = std::stod(nX->FirstChild()->Value());
				blankText.y = std::stod(nY->FirstChild()->Value());
				blankText.size = std::stof(nSize->FirstChild()->Value());
				blankText.alpha = std::stof(nAlpha->FirstChild()->Value());
				blankText.color = getRGBA8Color(nColor->FirstChild()->Value());
				blankText.justification = getJustification(nCenter->FirstChild()->Value());
			}
			catch (const std::invalid_argument error)
			{
				R2D::ErrorLog::logEvent("Error on getTextFromFile : invalid_argument : " + std::string(error.what()));
				return false;
			}
			catch (const std::out_of_range error)
			{
				R2D::ErrorLog::logEvent("Error on getTextFromFile : out_of_range : " + std::string(error.what()));
				return false;
			}
			

			mapTexts.emplace(blankText.text, blankText);

			nTextRoot = nTextRoot->NextSibling();
		}
	}
	return true;
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
	for (const auto& text : mapTexts)
	{
		R2D::ResourceManager::getSpriteFont()->draw
		(
			spriteBatchHUDStatic,
			text.second.text.c_str(),
			glm::vec2
			(
				window.getWidthPositionScaleToWindow(text.second.x),
				window.getHeightPositionScaleToWindow(text.second.y)
			), // offset pos
			glm::vec2(R2D::SpriteFont::getScaleFontToScreen(text.second.size)), // size
			text.second.alpha,
			text.second.color,
			text.second.justification
		);
	}
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