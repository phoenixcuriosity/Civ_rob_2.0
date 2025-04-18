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

#include "TextureCache.h"

#include "GLTexture.h"
#include "Log.h"
#include "LogSentences.h"

#include <filesystem>

R2D::TextureCache::~TextureCache()
{
	for (auto& n : m_textureMap)
	{
		n.second.reset();
	}
	m_textureMap.clear();
}

R2D::TextureCache::GLTextureUptr&
R2D::TextureCache
::getTexture(const std::string& name)
{
	auto it =  m_textureMap.find(name);

	if (it == m_textureMap.end())
	{
		m_textureMap.insert({ name, std::make_unique<GLTexture>(name) });
		return m_textureMap[name];
	}
	return it->second;
}

void
R2D::TextureCache
::loadTextureFromDir(const std::string& path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			if (entry.is_directory() == false)
			{
				auto result = m_idMap.try_emplace(entry.path().stem().string(), getTexture(entry.path().generic_string())->GETid());
				if (result.second)
				{
					LOG(R2D::LogLevelType::info, 0, logR::WHO::RESSOURCES_MANAGER, logR::WHAT::TEXTURE, logR::DATA::LOAD_TEXTURE, entry.path().generic_string());
				}
				else
				{
					LOG(R2D::LogLevelType::error, 0, logR::WHO::RESSOURCES_MANAGER, logR::WHAT::TEXTURE, logR::DATA::ERROR_LOAD_TEXTURE, entry.path().generic_string());
				}
			}
			else
			{
				loadTextureFromDir(entry.path().generic_string());
			}
		}
	}
}

GLuint
R2D::TextureCache
::searchKeyInIdMap(const R2D::IdMap& idMap, const std::string& key)
{
	if (auto search = idMap.find(key); search != idMap.end())
	{
		return search->second;
	}
	else
	{
		LOG(R2D::LogLevelType::error, 0, logR::WHO::RESSOURCES_MANAGER, logR::WHAT::TEXTURE, logR::DATA::ERROR_FIND_TEXTURE, key);
		return 0;
	}
}