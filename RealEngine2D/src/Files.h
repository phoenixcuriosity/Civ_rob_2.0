/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.3.0
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

#ifndef Files_H
#define Files_H


#include <map>
#include <string>
#include "ColorRGBA8.h"
#include "SpriteFont.h"


enum class e_Files
{
	error				= 0,

	log					= 1, 

	readme				= 10,
	texts				= 11,
	mainMap				= 12,
	buildings			= 13,
	citiesNames			= 14,
	units				= 15,
	specNames			= 16,

	saveInfo			= 20,

	saveMaps			= 30,
	savePlayers			= 31,

	colorShadingVert	= 50,
	colorShadingFrag	= 51,

	imagesPath			= 100,
	GUIPath				= 101
};

struct Text
{
	std::string text;
	double x;
	double y;
	float size;
	float alpha;
	RealEngine2D::ColorRGBA8 color;
	RealEngine2D::Justification justification;
};


typedef std::map<std::string, Text> MapTexts;

class File
{
public:
	File();
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

	bool modifyPath
	(
		const e_Files name,
		const std::string& path
	);

	File* getFile(const e_Files name);

private:

	std::map<e_Files, File*> m_map_FileConf;
};




#endif // !Files_H

