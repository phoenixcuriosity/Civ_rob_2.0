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

#include "Files.h"

using namespace R2D;

File::File
(
	const std::string& path
)
:
m_path(path),
m_isInitilize(true)
{
}


File::~File()
{

}


Files::Files()
{

}

Files::~Files()
{
	for (auto& n : m_map_FileConf)
	{
		if (n.second != nullptr)
		{
			delete n.second;
			n.second = nullptr;
		}
	}
	m_map_FileConf.clear();
}


bool Files::initializePath
(
	const e_Files name,
	const std::string& path
)
{
	const auto it = m_map_FileConf.find(name);

	if  (
			it == m_map_FileConf.end()
			||
			it->second->isInitilize() == false
		)
	{
		m_map_FileConf.insert({ name, new File{path} });
		return true;
	}
	return false;
}

bool Files::modifyPath
(
	const e_Files name,
	const std::string& path
)
{
	const auto it = m_map_FileConf.find(name);

	if	(it == m_map_FileConf.end())
	{
		return false;
	}
	it->second->modifyPath(path);
	return true;
}

File* Files::getFile(const e_Files name)
{
	const auto it = m_map_FileConf.find(name);

	if	(
			it == m_map_FileConf.end()
			||
			it->second->isInitilize() == false
		)
	{
		return nullptr;
	}
	return it->second;
}