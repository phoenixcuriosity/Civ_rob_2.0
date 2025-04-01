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

bool
R2D::Files
::initializePath(const e_Files name,
				 const FilePath& path)
{
	const auto it = m_map_FileConf.find(name);

	if ( it == m_map_FileConf.end()
		 ||
		 it->second->m_isInitilize == false)
	{
		m_map_FileConf.insert({ name, std::make_shared<File>(path) });
		return true;
	}
	return false;
}

void
R2D::Files
::modifyPath(const e_Files name,
			 const FilePath& path)
{
	const auto it = m_map_FileConf.find(name);

	if (it != m_map_FileConf.end()
		||
		it->second->m_isInitilize == true)
	{
		it->second->m_path = path;
	}
}

R2D::Files::FilePtrT
R2D::Files
::getFile(const e_Files name)
{
	const auto it = m_map_FileConf.find(name);

	if(it == m_map_FileConf.end()
	   ||
	   it->second->m_isInitilize == false)
	{
		return nullptr;
	}
	return it->second;
}