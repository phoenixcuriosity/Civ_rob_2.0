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

#ifndef Files_H
#define Files_H

#include "API_fwd.h"

#include "ColorRGBA8.h"
#include "SpriteFont.h"

namespace R2D
{

enum class e_Files
{
	error				= 0,

	log					= 1, 

	readme				= 10,

	mainMap				= 12,
	citiesNames			= 14,
	units				= 15,

	saveInfo			= 20,

	saveMaps			= 30,
	savePlayers			= 31,

	colorShadingVert	= 50,
	colorShadingFrag	= 51,

	imagesPath			= 100,
	GUIPath				= 101,

	texts_MainMenu		= 200,
	texts_NewGame		= 201,
	texts_GamePlay		= 202,
	texts_City			= 203,
	texts_Reload		= 204
};

const e_Files tab_e_Files[]=
{
	e_Files::readme,
	e_Files::mainMap,
	e_Files::citiesNames,
	e_Files::units,
	e_Files::saveInfo,
	e_Files::saveMaps,
	e_Files::savePlayers,
	e_Files::colorShadingVert,
	e_Files::colorShadingFrag,
	e_Files::imagesPath,
	e_Files::GUIPath,
	e_Files::texts_MainMenu,
	e_Files::texts_NewGame,
	e_Files::texts_GamePlay,
	e_Files::texts_City,
	e_Files::texts_Reload
};

constexpr size_t NUMBER_OF_FILEPATH = sizeof(tab_e_Files) / sizeof(tab_e_Files[0]);



class File
{
public:
	File() = delete;
	File(const std::string& path);
	~File();

public:

	std::string& getPath() { return m_path; };
	bool isInitilize() { return m_isInitilize; };
	void modifyPath(const std::string& path) { m_path = path; };

private:

	std::string m_path;
	bool m_isInitilize;

};

class Files
{

public:

	Files();
	~Files();

public:

	bool initializePath
	(
		const e_Files name,
		const std::string& path
	);

	File* getFile(const e_Files name);

private:

	std::map<e_Files, File*> m_map_FileConf;
};

}


#endif // !Files_H

