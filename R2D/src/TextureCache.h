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

#ifndef TextureCache_H
#define TextureCache_H

#include "API_fwd.h"

namespace R2D
{

class TextureCache
{
public:
	using GLTextureUptr = std::unique_ptr<GLTexture>;
	using GLTextureUptrMap = std::map<std::string, GLTextureUptr>;
public:
	TextureCache() = default;
	~TextureCache();

private:

	GLTextureUptr& getTexture(const std::string& name);

public:

	void loadTextureFromDir(const std::string& path);

	inline void copyIdMap(IdMap& dest)const { dest = m_idMap; };

public:

	static GLuint searchKeyInIdMap(const R2D::IdMap& idMap, const std::string& key);

private:
	GLTextureUptrMap m_textureMap;
	IdMap m_idMap;
};

}
#endif // !TextureCache_H
