/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.6.0
	file version : 1.1

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

#ifndef TextureCache_H
#define TextureCache_H

#include "GLTexture.h"
#include <map>
#include <memory>

namespace RealEngine2D
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

	public:

		std::unique_ptr<GLTexture>& getTexture(const std::string& name);

	private:
		std::map<std::string, std::unique_ptr<GLTexture>> m_textureMap;
	};
}
#endif // !TextureCache_H
