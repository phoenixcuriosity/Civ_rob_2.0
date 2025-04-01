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

#include "Text.h"

#include "Log.h"
#include "LogSentences.h"
#include "ResourceManager.h"

#include <jsoncons/json.hpp>

using namespace R2D;

constexpr char KEY_TEXTS[] = "Texts";

JSONCONS_ALL_MEMBER_NAME_TRAITS(Text_json,
	(text, "Text"),
	(x, "X"),
	(y, "Y"),
	(size, "Size"),
	(alpha, "Alpha"),
	(color, "Color"),
	(justification, "Justification"))


void Text::getTextFromFile
(
	const e_Files name,
	MapTexts& mapTexts
)
{
	try
	{
		const std::string textFromFile{ ResourceManager::loadFileToString(ResourceManager::getFile(name)) };

		const jsoncons::ojson configuration = jsoncons::ojson::parse(textFromFile);

		if (configuration.contains(KEY_TEXTS) && configuration[KEY_TEXTS].is_array())
		{
			const auto texts = configuration[KEY_TEXTS].as<std::vector<Text_json>>();
			for (const auto& text : texts)
			{
				Text_t t;
				t.text = text.text;
				t.x = text.x;
				t.y = text.y;
				t.size = text.size;
				t.alpha = text.alpha;
				t.color = ResourceManager::getRGBA8Color(text.color);
				t.justification = ResourceManager::getJustification(text.justification);
				mapTexts.emplace(t.text, t);
			}
		}
		else
		{
			LOG(R2D::LogLevelType::error, 0, logR::WHO::RESSOURCES_MANAGER, logR::WHAT::FILE, logR::DATA::ERROR_KEY_TEXT_MISSING,
				KEY_TEXTS);
		}
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logR::WHO::RESSOURCES_MANAGER, logR::WHAT::FILE, logR::DATA::ERROR_KEY_TEXT_MISSING, e.what());
	}
}

void Text::displayTextFromFile
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