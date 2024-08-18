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

using namespace R2D;

TextureCache::TextureCache()
{

}

TextureCache::~TextureCache()
{
	for (auto& n : m_textureMap)
	{
		n.second.reset();
	}
	m_textureMap.clear();
}

std::unique_ptr<GLTexture>& TextureCache::getTexture(const std::string& name)
{
	auto it =  m_textureMap.find(name);

	if (it == m_textureMap.end())
	{
		m_textureMap.insert({ name, std::make_unique<GLTexture>(name) });
		return m_textureMap[name];
	}
	return it->second;
}