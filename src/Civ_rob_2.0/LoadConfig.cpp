/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.17
	file version : 1.7

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
#include "End.h"



/*
* NAME : initStructs
* ROLE : Initialisation des données par défaut des structures
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : données par défaut des structures
* RETURNED VALUE    : void
*/
void LoadConfig::initStructs(Sysinfo& sysinfo)
{
	/* ### Mettre ici les cas d'inialisation des structures ### */

	/* *********************************************************
	 *					   sysinfo.screen					   *
	 ********************************************************* */

	sysinfo.screen.window = nullptr;
	sysinfo.screen.renderer = nullptr;
	sysinfo.screen.screenWidth = 0;
	sysinfo.screen.screenHeight = 0;
	sysinfo.screen.enableFPS = false;
	// sysinfo.screen.fpsTimer // N/A
	sysinfo.screen.avgFPS = 0;
	sysinfo.screen.countedFrames = 0;
	
	/* *********************************************************
	 *					   sysinfo.file						   *
	 ********************************************************* */

	// sysinfo.file.log = "bin/log/log.txt"; // N/A : const
	sysinfo.file.BUILDING = "";
	sysinfo.file.CITIENAME = "";
	sysinfo.file.readme = "";
	sysinfo.file.SaveInfo = "";
	sysinfo.file.SaveMaps = "";
	sysinfo.file.SPECNAME = "";
	sysinfo.file.UNIT = "";
	sysinfo.file.Texte = "";

	/* *********************************************************
	 *					   sysinfo.var						   *
	 ********************************************************* */

	sysinfo.var.continuer = true;
	sysinfo.var.nbturn = 0;
	sysinfo.var.select = selectnothing;
	sysinfo.var.statescreen = 0;

	/* sysinfo.var.s_player */

	sysinfo.var.s_player.selectCitie = -1;
	sysinfo.var.s_player.selectplayer = -1;
	sysinfo.var.s_player.selectPlayerToAttack = -1;
	sysinfo.var.s_player.selectunit = -1;
	sysinfo.var.s_player.selectUnitToAttack = -1;
	sysinfo.var.s_player.unitToCreate = 0;
	sysinfo.var.s_player.toBuild = "";
	sysinfo.var.s_player.unitNameToCreate = "";
	sysinfo.var.s_player.unitNameToMove = "";

	sysinfo.var.s_player.tabCitieName.clear();
	sysinfo.var.s_player.tabPlayerName.clear();
	sysinfo.var.s_player.tabUnit_Struct.clear();

	sysinfo.var.s_player.nbNoNamePlayer = 0;
	sysinfo.var.s_player.citieNameMaxToCreate = 0;

	/* sysinfo.var.mouse */

	KeyboardMouse mouse;
	sysinfo.var.mouse = mouse;

	/* sysinfo.var.save */

	SaveReload save;
	sysinfo.var.save = save;

	/* *********************************************************
	 *					 sysinfo.allTextures				   *
	 ********************************************************* */

	for (unsigned int i(0); i < MAX_FONT; i++)
	{
		sysinfo.allTextures.font[i] = nullptr;
	}

	sysinfo.allTextures.ground.clear();
	sysinfo.allTextures.groundSpec.clear();
	sysinfo.allTextures.colorapp.clear();
	sysinfo.allTextures.colorapptile.clear();
	sysinfo.allTextures.barLife.clear();


	sysinfo.allTextures.titleScreen.clear();
	sysinfo.allTextures.unit.clear();
	sysinfo.allTextures.citieMap.clear();

	/* *********************************************************
	 *					  sysinfo.allTextes					   *
	 ********************************************************* */

	sysinfo.allTextes.number.clear();
	sysinfo.allTextes.titleScreen.clear();
	sysinfo.allTextes.newGame.clear();
	sysinfo.allTextes.mainMap.clear();
	sysinfo.allTextes.citieMap.clear();

	/* *********************************************************
	 *					  sysinfo.allButton					   *
	 ********************************************************* */

	sysinfo.allButton.titleScreen.clear();
	sysinfo.allButton.reload.clear();
	sysinfo.allButton.mainMap.clear();
	sysinfo.allButton.citieMap.clear();

	sysinfo.allButton.player.clear();

	/* *********************************************************
	 *					    sysinfo.map						   *
	 ********************************************************* */

	sysinfo.map.mapSize = 0;
	sysinfo.map.tileSize = 0;
	sysinfo.map.toolBarSize = 0;
	sysinfo.map.screenOffsetXIndexMin = 0;
	sysinfo.map.screenOffsetYIndexMin = 0;
	sysinfo.map.screenOffsetXIndexMax = 0;
	sysinfo.map.screenOffsetYIndexMax = 0;
	sysinfo.map.maps.clear();

	/* *********************************************************
	 *					    sysinfo							   *
	 ********************************************************* */

	sysinfo.tabplayer.clear();
}




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
	else
	{
		throw("Impossible d'ouvrir le fichier " + (std::string)configFilePath);
	}


	IHM::logfileconsole("[INFO]___: [END] : initMain");
}

Uint16 LoadConfig::getHorizontal(unsigned int tileSize)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	Uint16 complete = 0;
	if ((complete = ((Uint16)desktop.right % (Uint16)tileSize)) == 0)
		return (Uint16)desktop.right;
	return (Uint16)desktop.right + ((Uint16)tileSize - complete);
}

Uint16 LoadConfig::getVertical(unsigned int tileSize)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	Uint16 complete = 0;
	if ((complete = ((Uint16)desktop.bottom % (Uint16)tileSize)) == 0)
		return (Uint16)desktop.bottom;
	return (Uint16)desktop.bottom + ((Uint16)tileSize - complete);
}


/*
* NAME : calculImage
* ROLE : Initialisation des Textures, des Textes et des Buttons
* ROLE : Enregistrement des pointeurs dans des tableaux
* ROLE : Hachage des noms des Textures (et classes filles) pour une recherche en complexité en O(1)
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Tableaux de pointeurs vers les Textures (et classes filles)
* RETURNED VALUE    : void
*/
void LoadConfig::calculImage(Sysinfo& sysinfo)
{
	IHM::logfileconsole("[INFO]___: [START] : calculImage");

	// répertoire de base de l'image
	const std::string IPath = "bin/image/";


	/* *********************************************************
	 *				START sysinfo.allTextures				   *
	 ********************************************************* */


	 // chargement des images du sol de la map
	 /*
		 sysinfo.allTextures.ground
	 */
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ground/grass.bmp", "grass.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ground/water.bmp", "water.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ground/deepwater.bmp", "deepwater.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);


	// chargement de l'image de la toolbar
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "toolbar.bmp", "toolbar.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);



	// chargement des spécifications du sol de la map
	/*
		sysinfo.allTextures.groundSpec
	*/
	unsigned int nbspecname(0);
	std::string destroy(""), name("");
	std::ifstream SPECNAME(sysinfo.file.SPECNAME);
	if (SPECNAME)
	{
		SPECNAME >> destroy;
		SPECNAME >> nbspecname;
		for (unsigned int i(0); i < nbspecname; i++)
		{
			name = "";
			SPECNAME >> name;
			Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.groundSpec, sysinfo.var.statescreen, sysinfo.var.select,
				IPath + "spec/" + name, name, nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);
		}
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + sysinfo.file.SPECNAME);
	}




	// chargement du nombre d'unités ainsi que leur nom
	/*
		sysinfo.allTextures.unit
	*/
	for (unsigned int i(0); i < sysinfo.var.s_player.tabUnit_Struct.size(); i++)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.unit, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "units/" + sysinfo.var.s_player.tabUnit_Struct[i].name + ".bmp",
			sysinfo.var.s_player.tabUnit_Struct[i].name, nonTransparent, 100, 432, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);



	/*
		sysinfo.allTextures.barLife
	*/
	sysinfo.var.statescreen = STATEmainmap;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.barLife, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "barre de vie/maxlife.bmp", "maxlife.bmp", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize / 10, no_angle);
	for (int i(9); i >= 0; i--)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.barLife, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "barre de vie/0." + std::to_string(i) + "life.bmp", "0." + std::to_string(i) + "life.bmp", nonTransparent,
			-1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize / 10, no_angle, nocenter);



	/*
		sysinfo.allTextures.colorapp
	*/
	for (unsigned int i(0); i < 9; i++)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.colorapp, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "couleur d'apartenance/ColorPlayer" + std::to_string(i) + ".bmp", "ColorPlayer" + std::to_string(i) + ".bmp", nonTransparent,
			-1, -1, sysinfo.map.tileSize / 4, sysinfo.map.tileSize / 4, no_angle, nocenter);


	/*
		sysinfo.allTextures.colorapptile
	*/
	for (unsigned int i(0); i < 9; i++)
		Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.colorapptile, sysinfo.var.statescreen, sysinfo.var.select,
			IPath + "couleur d'apartenance/ColorPlayer" + std::to_string(i) + ".bmp", "ColorPlayertile" + std::to_string(i) + ".bmp", (Transparance_Type)96,
			-1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);


	/*
		sysinfo.allTextures.titleScreen
	*/
	sysinfo.var.statescreen = STATEtitleScreen;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.titleScreen, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "earth.jpg", "earth.jpg", nonTransparent, sysinfo.screen.screenWidth / 2, sysinfo.screen.screenHeight / 2, NULL, NULL, no_angle, center);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.titleScreen, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "sdl_icone.bmp", "sdl_icone.bmp", nonTransparent, sysinfo.screen.screenWidth / 2, sysinfo.screen.screenHeight - 100, NULL, NULL, no_angle, center_x);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.titleScreen, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "signal/destroyed.bmp", "destroyed.bmp", nonTransparent, sysinfo.screen.screenWidth / 2, 0, NULL, NULL, no_angle, center_x);



	/*
		sysinfo.allTextures.citieMap
	*/
	sysinfo.var.statescreen = STATEmainmap;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citie/citie.png", "citie.png", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citie/food.png", "food.png", nonTransparent, -1, -1, sysinfo.map.tileSize, sysinfo.map.tileSize, no_angle, nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citizen/Adore.png", "Adore.png", nonTransparent, -1, -1, sysinfo.map.tileSize / 2, sysinfo.map.tileSize / 2, no_angle, nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citizen/Laugh.png", "Laugh.png", nonTransparent, -1, -1, sysinfo.map.tileSize / 2, sysinfo.map.tileSize / 2, no_angle, nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citizen/Cool.png", "Cool.png", nonTransparent, -1, -1, sysinfo.map.tileSize / 2, sysinfo.map.tileSize / 2, no_angle, nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citizen/Cry.png", "Cry.png", nonTransparent, -1, -1, sysinfo.map.tileSize / 2, sysinfo.map.tileSize / 2, no_angle, nocenter);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.citieMap, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "citizen/Furious.png", "Furious.png", nonTransparent, -1, -1, sysinfo.map.tileSize / 2, sysinfo.map.tileSize / 2, no_angle, nocenter);


	// chargement du nombre de ville ainsi que leur nom
	unsigned int nbcitie(0);
	std::string citie("");
	std::ifstream CITIENAME(sysinfo.file.CITIENAME);
	if (CITIENAME)
	{
		CITIENAME >> destroy;
		CITIENAME >> nbcitie;
		sysinfo.var.s_player.citieNameMaxToCreate = nbcitie;
		for (unsigned int i(0); i < nbcitie; i++)
		{
			CITIENAME >> citie;
			sysinfo.var.s_player.tabCitieName.push_back(citie);
		}
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + sysinfo.file.CITIENAME);
	}

	//chargement du nombre de sauvegardes
	std::ifstream loadInfo(sysinfo.file.SaveInfo);
	unsigned int currentSave(0), maxSave(0);
	if (loadInfo)
	{
		loadInfo >> destroy;
		loadInfo >> maxSave;
		sysinfo.var.save.SETnbSave(maxSave);
		loadInfo >> destroy;
		for (unsigned int i(0); i < sysinfo.var.save.GETnbSave(); i++)
		{
			loadInfo >> currentSave;
			sysinfo.var.save.GETtabSave().push_back(currentSave);
		}
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + sysinfo.file.SaveInfo);
	}

	/* *********************************************************
	 *				END sysinfo.allTextures					   *
	 ********************************************************* */


	 /* *********************************************************
	  *				START sysinfo.allButtons				   *
	  ********************************************************* */

	int spacemenu(64), initspacemenu(300);

	/*** STATEtitleScreen ***/
	sysinfo.var.statescreen = STATEtitleScreen;


	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		shaded, "New Game", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu,
		nonTransparent, no_angle, center);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		shaded, "Reload", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu += spacemenu,
		nonTransparent, no_angle, center);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		shaded, "Option", { 128, 128, 128, 255 }, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu += spacemenu,
		nonTransparent, no_angle, center);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.titleScreen,
		shaded, "Quit", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu += spacemenu,
		nonTransparent, no_angle, center);



	/*** STATEreload ***/
	sysinfo.var.statescreen = STATEreload;
	initspacemenu = 300;

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
		shaded, "Back", WriteColorButton, BackColorButton, 24, 96, 0,
		nonTransparent, no_angle, center_x);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
		shaded, "Remove all saves", WriteColorButton, BackColorButton, 24, 256, 0,
		nonTransparent, no_angle, center_x);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
		shaded, "Load", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2 - 200, 256,
		nonTransparent, no_angle, center_x);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
		shaded, "Remove", WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2 + 200, 256,
		nonTransparent, no_angle, center_x);

	for (unsigned int i(0); i < sysinfo.var.save.GETnbSave(); i++)
	{
		ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.reload,
			shaded, "Save : " + std::to_string(sysinfo.var.save.GETtabSave()[i]),
			WriteColorButton, BackColorButton, 32, sysinfo.screen.screenWidth / 2, initspacemenu += spacemenu,
			nonTransparent, no_angle, center);
	}



	/*** STATEmainmap ***/
	sysinfo.var.statescreen = STATEmainmap;

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "screen Titre", WriteColorButton, BackColorButton, 24, 0, 0,
		nonTransparent, no_angle, nocenter);

	sysinfo.var.select = selectcreate;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Create Unit", WriteColorButton, BackColorButton, 24, 0, 50,
		nonTransparent, no_angle, nocenter);

	sysinfo.var.select = selectmove;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Move Unit", WriteColorButton, BackColorButton, 24, 0, 82,
		nonTransparent, no_angle, nocenter);

	sysinfo.var.select = selectinspect;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Inspect", WriteColorButton, BackColorButton, 24, 0, 114,
		nonTransparent, no_angle, nocenter);

	sysinfo.var.select = selectnothing;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Delete Unit", WriteColorButton, BackColorButton, 24, 0, 146,
		nonTransparent, no_angle, nocenter);

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.mainMap,
		shaded, "Next Turn", WriteColorButton, BackColorButton, 24, 0, 800,
		nonTransparent, no_angle, nocenter);


	/*** STATEcitiemap ***/
	sysinfo.var.statescreen = STATEcitiemap;
	sysinfo.var.select = selectnothing;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
		shaded, "Map", WriteColorButton, BackColorButton, 24, 96, 0,
		nonTransparent, no_angle, center_x);

	sysinfo.var.select = selectcreate;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font
		, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
		shaded, "Build", WriteColorButton, BackColorButton, 24, sysinfo.screen.screenWidth / 2 - 200, 100,
		nonTransparent, no_angle, center_x);

	sysinfo.var.select = selectnothing;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
		shaded, "Food", WriteColorButton, BackColorButton, 24, sysinfo.screen.screenWidth / 2 - 200, 132,
		nonTransparent, no_angle, center_x);

	sysinfo.var.select = selectmoveCitizen;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
		shaded, "Place Citizen", WriteColorButton, BackColorButton, 24, sysinfo.screen.screenWidth / 2 - 200, 164,
		nonTransparent, no_angle, center_x);

	for (unsigned int i(0); i < sysinfo.var.s_player.tabUnit_Struct.size(); i++)
	{
		ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButton.citieMap,
			shaded, sysinfo.var.s_player.tabUnit_Struct[i].name, { 255, 64, 0, 255 }, BackColorButton, 24, 64, 400,
			nonTransparent, no_angle, nocenter);
	}



	sysinfo.var.select = selectnothing;


	/* *********************************************************
	 *				END sysinfo.allButtons					   *
	 ********************************************************* */


	 /* *********************************************************
	  *				START sysinfo.allTexte					   *
	  ********************************************************* */


	tinyxml2::XMLDocument texteFile;
	texteFile.LoadFile(sysinfo.file.Texte.c_str());

	if (texteFile.ErrorID() == 0)
	{
		LoadConfig::readXmlTexte(texteFile, sysinfo.screen.renderer, sysinfo.allTextures.font, sysinfo.allTextes, sysinfo.screen.screenWidth, sysinfo.screen.screenHeight);
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + sysinfo.file.Texte);
	}

	/*** STATEmainmap ***/
	sysinfo.var.statescreen = STATEmainmap;

	for (unsigned int i(0); i < MAX_POP; i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.number,
			blended, std::to_string(i), { 255, 255, 255, 255 }, NoColor, 18, 1000, 1000,
			nonTransparent, no_angle, nocenter);
	}

	sysinfo.var.select = NotToSelect;
	for (unsigned int i(0); i < nbcitie; i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.mainMap,
			blended, sysinfo.var.s_player.tabCitieName[i], { 255, 64, 0, 255 }, NoColor, 12, -1, -1,
			nonTransparent, no_angle, nocenter);
	}


	sysinfo.var.select = selectcreate;
	for (unsigned int i(0); i < sysinfo.var.s_player.tabUnit_Struct.size(); i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.citieMap,
			blended, sysinfo.var.s_player.tabUnit_Struct[i].name, { 0, 64, 255, 255 }, NoColor, 18, 64, 400,
			nonTransparent, no_angle, nocenter);
	}

	/*** STATEcitiemap ***/
	sysinfo.var.statescreen = STATEcitiemap;
	sysinfo.var.select = selectcreate;
	for (unsigned int i(0); i < sysinfo.var.s_player.tabUnit_Struct.size(); i++)
	{
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.citieMap,
			blended, "life:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[i].life) +
			"/atq:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[i].atq) +
			"/def:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[i].def) +
			"/move:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[i].movement),
			{ 255, 64, 0, 255 }, NoColor, 24, 0, 0, nonTransparent, no_angle, nocenter);
	}

	/* *********************************************************
	 *					END sysinfo.allTexte				   *
	 ********************************************************* */


	 /* ### Don't put code below here ### */

	IHM::logfileconsole("[INFO]___: [END] : calculImage");
}

/*
* NAME : readXmlTexte
* ROLE : Initialisation des Textes par la lecture du fichier Texte.xml
* ROLE : Enregistrement des pointeurs dans des tableaux
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Tableau de pointeurs vers les Texte
* RETURNED VALUE    : void
*/
void LoadConfig::readXmlTexte(tinyxml2::XMLDocument& texteFile,
	SDL_Renderer*& renderer,
	TTF_Font* font[],
	AllTextes& allTextes,
	Uint16 screenWidth,
	Uint16 screenHeight)
{
	const char* root("Config");


	const char* s_M_Texte("Texte"),
		* s_Statescreen("Statescreen"),
		* s_Select("Select"),
		* s_TexteName("TexteName"),
		* s_Type("Type"),
		* s_Texte("Texte"),
		* s_FontColor("FontColor"),
		* s_FontColor_Simple("Simple"),
		* s_FontColor_Simple_Condition("Condition"),
		* s_FontColor_Simple_Color("Color"),
		* s_FontColor_Complexe("Complexe"),
		//* s_FontColor_Complexe_condition("Condition"), // not use
		* s_FontColor_Complexe_R("R"),
		* s_FontColor_Complexe_G("G"),
		* s_FontColor_Complexe_B("B"),
		* s_FontColor_Complexe_Alpha("Alpha"),
		* s_BackColor("FontColor"),
		* s_BackColor_Simple("Simple"),
		* s_BackColor_Simple_Condition("Condition"),
		* s_BackColor_Simple_Color("Color"),
		* s_BackColor_Complexe("Complexe"),
		//* s_BackColor_Complexe_condition("Condition"), //not use
		* s_BackColor_Complexe_R("R"),
		* s_BackColor_Complexe_G("G"),
		* s_BackColor_Complexe_B("B"),
		* s_BackColor_Complexe_Alpha("Alpha"),
		* s_Size("Size"),
		* s_X("X"),
		* s_Y("Y"),
		* s_Alpha("Alpha"),
		* s_Angle("Angle"),
		* s_Center("Center");

	tinyxml2::XMLNode* node(texteFile.FirstChildElement(root)->FirstChildElement(s_M_Texte));

	SDL_Color fontColor, backColor;
	int r(0), g(0), b(0), alpha(0), size(0);
	int x(0), y(0);

	while (node != nullptr)
	{
		if (strcmp(node->FirstChildElement(s_FontColor)->FirstChildElement(s_FontColor_Simple)
			->FirstChildElement(s_FontColor_Simple_Condition)->GetText(), "true") == 0)
		{
			fontColor = xmlGiveColor(node->FirstChildElement(s_FontColor)->FirstChildElement(s_FontColor_Simple)
				->FirstChildElement(s_FontColor_Simple_Color)->GetText());
		}
		else
		{
			node->FirstChildElement(s_FontColor)->FirstChildElement(s_FontColor_Complexe)
				->FirstChildElement(s_FontColor_Complexe_R)->QueryIntText((int*)&r);
			node->FirstChildElement(s_FontColor)->FirstChildElement(s_FontColor_Complexe)
				->FirstChildElement(s_FontColor_Complexe_G)->QueryIntText((int*)&g);
			node->FirstChildElement(s_FontColor)->FirstChildElement(s_FontColor_Complexe)
				->FirstChildElement(s_FontColor_Complexe_B)->QueryIntText((int*)&b);
			node->FirstChildElement(s_FontColor)->FirstChildElement(s_FontColor_Complexe)
				->FirstChildElement(s_FontColor_Complexe_Alpha)->QueryIntText((int*)&alpha);
			fontColor.r = (Uint8)r;
			fontColor.g = (Uint8)g;
			fontColor.b = (Uint8)b;
			fontColor.a = (Uint8)alpha;
		}

		if (strcmp(node->FirstChildElement(s_BackColor)->FirstChildElement(s_BackColor_Simple)
			->FirstChildElement(s_BackColor_Simple_Condition)->GetText(), "true") == 0)
		{
			backColor = xmlGiveColor(node->FirstChildElement(s_BackColor)->FirstChildElement(s_BackColor_Simple)
				->FirstChildElement(s_BackColor_Simple_Color)->GetText());
		}
		else
		{
			node->FirstChildElement(s_BackColor)->FirstChildElement(s_BackColor_Complexe)
				->FirstChildElement(s_BackColor_Complexe_R)->QueryIntText((int*)&r);
			node->FirstChildElement(s_BackColor)->FirstChildElement(s_BackColor_Complexe)
				->FirstChildElement(s_BackColor_Complexe_G)->QueryIntText((int*)&g);
			node->FirstChildElement(s_BackColor)->FirstChildElement(s_BackColor_Complexe)
				->FirstChildElement(s_BackColor_Complexe_B)->QueryIntText((int*)&b);
			node->FirstChildElement(s_BackColor)->FirstChildElement(s_BackColor_Complexe)
				->FirstChildElement(s_BackColor_Complexe_Alpha)->QueryIntText((int*)&alpha);
			backColor.r = (Uint8)r;
			backColor.g = (Uint8)g;
			backColor.b = (Uint8)b;
			backColor.a = (Uint8)alpha;
		}

		node->FirstChildElement(s_Size)->QueryIntText((int*)&size);
		node->FirstChildElement(s_X)->QueryIntText(&x);
		node->FirstChildElement(s_Y)->QueryIntText(&y);


		try
		{
			Texte::loadTexte(renderer, font,
				xmlGiveStateType(node->FirstChildElement(s_Statescreen)->GetText()),
				xmlGiveSelectType(node->FirstChildElement(s_Select)->GetText()),
				xmlGiveTexteConteneur(allTextes, node->FirstChildElement(s_TexteName)->GetText()),
				xmlGiveTexteType(node->FirstChildElement(s_Type)->GetText()),
				node->FirstChildElement(s_Texte)->GetText(),
				fontColor,
				backColor,
				(Uint8)size,
				determineCoor(node->FirstChildElement(s_X)->GetText(), screenWidth, screenHeight),
				determineCoor(node->FirstChildElement(s_Y)->GetText(), screenWidth, screenHeight),
				xmlGiveAlpha(node->FirstChildElement(s_Alpha)->GetText()),
				xmlGiveAngle(node->FirstChildElement(s_Angle)->GetText()),
				xmlGiveCenter(node->FirstChildElement(s_Center)->GetText()));
		}
		catch (const std::string & msg)
		{
			End::exitError("[ERROR]___: IHM::determineCoor : " + msg);
		}

		/* Recherche du noeud Model suivant */
		node = node->NextSibling();
	}
}

Uint8 LoadConfig::xmlGiveStateType(std::string type)
{
	if (type.compare("STATEnothing") == 0)
	{
		return STATEnothing;
	}
	else if (type.compare("STATEtitleScreen") == 0)
	{
		return STATEtitleScreen;
	}
	else if (type.compare("STATEscreennewgame") == 0)
	{
		return STATEscreennewgame;
	}
	else if (type.compare("STATEreload") == 0)
	{
		return STATEreload;
	}
	else if (type.compare("STATEmainmap") == 0)
	{
		return STATEmainmap;
	}
	else if (type.compare("STATEscience") == 0)
	{
		return STATEscience;
	}
	else if (type.compare("STATEcitiemap") == 0)
	{
		return STATEcitiemap;
	}
	else
	{
		return STATEnothing;
	}
}

Uint8 LoadConfig::xmlGiveSelectType(std::string type)
{
	if (type.compare("selectnothing") == 0)
	{
		return selectnothing;
	}
	else if (type.compare("NotToSelect") == 0)
	{
		return NotToSelect;
	}
	else if (type.compare("selectcreate") == 0)
	{
		return selectcreate;
	}
	else if (type.compare("selectinspect") == 0)
	{
		return selectinspect;
	}
	else if (type.compare("selectmove") == 0)
	{
		return selectmove;
	}
	else if (type.compare("selectmoveCitizen") == 0)
	{
		return selectmoveCitizen;
	}
	else
	{
		return selectnothing;
	}
}

std::unordered_map<std::string, Texte*>& LoadConfig::xmlGiveTexteConteneur(AllTextes& allTextes, std::string type)
{
	if (type.compare("titleScreen") == 0)
	{
		return allTextes.titleScreen;
	}
	else if (type.compare("newGame") == 0)
	{
		return allTextes.newGame;
	}
	else if (type.compare("mainMap") == 0)
	{
		return allTextes.mainMap;
	}
	else if (type.compare("citieMap") == 0)
	{
		return allTextes.citieMap;
	}
	else
	{
		return allTextes.titleScreen;
	}
}

Texte_Type LoadConfig::xmlGiveTexteType(std::string type)
{
	if (type.compare("blended") == 0)
	{
		return blended;
	}
	else if (type.compare("shaded") == 0)
	{
		return shaded;
	}
	else
	{
		return blended;
	}
}

SDL_Color LoadConfig::xmlGiveColor(std::string type)
{
	if (type.compare("Black") == 0)
	{
		return Black;
	}
	else if (type.compare("White") == 0)
	{
		return White;
	}
	else if (type.compare("Red") == 0)
	{
		return Red;
	}
	else if (type.compare("Green") == 0)
	{
		return Green;
	}
	else if (type.compare("Blue") == 0)
	{
		return Blue;
	}
	else if (type.compare("Blue") == 0)
	{
		return Blue;
	}
	else if (type.compare("Yellow") == 0)
	{
		return Yellow;
	}
	else if (type.compare("WriteColorButton") == 0)
	{
		return WriteColorButton;
	}
	else if (type.compare("BackColorButton") == 0)
	{
		return BackColorButton;
	}
	else if (type.compare("NoColor") == 0)
	{
		return NoColor;
	}
	else
	{
		return NoColor;
	}
}

Transparance_Type LoadConfig::xmlGiveAlpha(std::string type)
{
	if (type.compare("nonTransparent") == 0)
	{
		return nonTransparent;
	}
	else if (type.compare("semiTransparent") == 0)
	{
		return semiTransparent;
	}
	else if (type.compare("transparent") == 0)
	{
		return transparent;
	}
	else
	{
		return nonTransparent;
	}
}

Rotation_Type LoadConfig::xmlGiveAngle(std::string type)
{
	if (type.compare("no_angle") == 0)
	{
		return no_angle;
	}
	else if (type.compare("inverse") == 0)
	{
		return inverse;
	}
	else
	{
		return no_angle;
	}
}

Center_Type LoadConfig::xmlGiveCenter(std::string type)
{
	if (type.compare("nocenter") == 0)
	{
		return nocenter;
	}
	else if (type.compare("center_x") == 0)
	{
		return center_x;
	}
	else if (type.compare("center_y") == 0)
	{
		return center_y;
	}
	else if (type.compare("center") == 0)
	{
		return center;
	}
	else
	{
		return nocenter;
	}
}

int LoadConfig::determineCoor(std::string line, Uint16 screenWidth, Uint16 screenHeight)
{
	std::string num(""), den(""), buffer("");
	unsigned int somme(0), numI(0), denI(0);
	unsigned int i(1);

	if (line[0] == '(')
	{
		while (line[i] != ')')
		{
			num += line[i];
			i++;
		}
		i += 3;
		while (line[i] != ')')
		{
			den += line[i];
			i++;
		}

		std::string::size_type n(0);
		n = num.find("SCREEN_WIDTH");
		while (n != std::string::npos)
		{
			num.replace(n, 12, std::to_string(screenWidth));
			n = num.find("SCREEN_WIDTH");
		}

		n = num.find("SCREEN_HEIGHT");
		while (n != std::string::npos)
		{
			num.replace(n, 13, std::to_string(screenHeight));
			n = num.find("SCREEN_HEIGHT");
		}

		numI = std::stoi(num);
		denI = std::stoi(den);

		if (denI == 0)
		{
			throw(" div/0 -> den == 0");
		}
		else
		{
			/* N/A */
		}

		return somme = (unsigned int)(numI / denI);
	}
	else
	{
		return std::stoi(line);
	}
}


/*
*	End Of File : LoadConfig.cpp
*/