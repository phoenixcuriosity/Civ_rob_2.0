/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.17
	file version : 1.2

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


#include "LoadConfig.h"
#include "civ_lib.h"
#include  "IHM.h"

/*
* NAME : initTile
* ROLE : Initialisation des cases de la map en fonction de sa taille
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : Initialisation de map.screen et map.maps
* RETURNED VALUE    : void
*/
void LoadConfig::initMain(Sysinfo& sysinfo)
{
	IHM::logfileconsole("[INFO]___: [START] : initMain");

	tinyxml2::XMLDocument config;
	config.LoadFile(configFilePath);

	if (config.ErrorID() == 0)
	{
		const char* root("Config");


		const char	* s_Map("Map"),
						* s_TileSize("TileSize"),
						* s_MapSize("MapSize"),

					* s_FilePaths("FilePaths"),
						* s_Readme("Readme"),
						* s_Texte("Texte"),
						* s_Building("Building"),
						* s_CitieName("CitieName"),
						* s_Unit("Unit"),
						* s_SpecName("SpecName"),
						* s_SaveInfo("SaveInfo"),
						* s_SaveMaps("SaveMaps"),
						* s_SavePlayer("SavePlayer");




		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_TileSize)->QueryUnsignedText(&sysinfo.map.tileSize);
		sysinfo.screen.screenWidth = getHorizontal(sysinfo.map.tileSize);
		sysinfo.screen.screenHeight = getVertical(sysinfo.map.tileSize);


		config.FirstChildElement(root)->FirstChildElement(s_Map)->FirstChildElement(s_MapSize)->QueryUnsignedText(&sysinfo.map.mapSize);
		sysinfo.map.toolBarSize = (sysinfo.screen.screenWidth / 10) / sysinfo.map.tileSize;
		sysinfo.map.screenOffsetXIndexMax = ((sysinfo.screen.screenWidth * 9) / 10) / sysinfo.map.tileSize;
		sysinfo.map.screenOffsetYIndexMax = sysinfo.screen.screenHeight / sysinfo.map.tileSize;


		sysinfo.file.readme = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Readme)->GetText();
		sysinfo.file.Texte = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Texte)->GetText();
		sysinfo.file.BUILDING = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Building)->GetText();
		sysinfo.file.CITIENAME = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_CitieName)->GetText();
		sysinfo.file.UNIT = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Unit)->GetText();
		sysinfo.file.SPECNAME = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SpecName)->GetText();
		sysinfo.file.SaveInfo = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SaveInfo)->GetText();
		sysinfo.file.SaveMaps = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SaveMaps)->GetText();
		sysinfo.file.SavePlayer = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_SavePlayer)->GetText();



	}
	IHM::logfileconsole("[INFO]___: [END] : initMain");
}

Uint16 LoadConfig::getHorizontal(unsigned int tileSize)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	Uint16 complete = 0;
	if ((complete = ((Uint16)desktop.right % tileSize)) == 0)
		return (Uint16)desktop.right;
	return (Uint16)desktop.right + (tileSize - complete);
}

Uint16 LoadConfig::getVertical(unsigned int tileSize)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	Uint16 complete = 0;
	if ((complete = ((Uint16)desktop.bottom % tileSize)) == 0)
		return (Uint16)desktop.bottom;
	return (Uint16)desktop.bottom + (tileSize - complete);
}



/*
*	End Of File : LoadConfig.cpp
*/