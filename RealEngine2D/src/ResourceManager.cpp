/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.7.0
	file version : 1.3

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

using namespace RealEngine2D;

TextureCache ResourceManager::m_textureCache;
Files ResourceManager::m_files;
std::shared_ptr<SpriteFont> ResourceManager::m_spriteFont;
GLSLProgram ResourceManager::m_gLSLProgram;

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