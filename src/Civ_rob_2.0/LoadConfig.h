/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.17
	file version : 1.4

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

#ifndef LoadConfig_H
#define LoadConfig_H


#include "LIB.h"
#include "civ_lib.h"
#include "Texture.h"

class LoadConfig
{
public:
	/* *********************************************************
	 *					INITIALISATION						   *
	 ********************************************************* */

	 /*
	 * NAME : initStructs
	 * ROLE : Initialisation des données par défaut des structures
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : données par défaut des structures
	 * RETURNED VALUE    : void
	 */
	static void initStructs(Sysinfo& sysinfo);

	/*
	* NAME : initMain
	* ROLE : Chargement des informations de la configuration du jeu
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : configuration du jeu
	* RETURNED VALUE    : void
	*/
	static void initMain(Sysinfo& sysinfo);

	static Uint16 getHorizontal(unsigned int tileSize);

	static Uint16 getVertical(unsigned int tileSize);

	/*
	* NAME : calculImage
	* ROLE : Initialisation des Textures, des Textes et des Buttons
	* ROLE : Enregistrement des pointeurs dans des tableaux
	* ROLE : Hachage des noms des Textures (et classes filles) pour une recherche en complexité en O(1)
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : Tableaux de pointeurs vers les Textures (et classes filles)
	* RETURNED VALUE    : void
	*/
	static void calculImage(Sysinfo&);

	/*
	* NAME : readXmlTexte
	* ROLE : Initialisation des Textes par la lecture du fichier Texte.xml
	* ROLE : Enregistrement des pointeurs dans des tableaux
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : Tableau de pointeurs vers les Texte
	* RETURNED VALUE    : void
	*/
	static void readXmlTexte(tinyxml2::XMLDocument& texteFile,
								SDL_Renderer*& renderer,
								TTF_Font* font[],
								AllTextes& allTextes,
								Uint16 screenWidth,
								Uint16 screenHeight);

	static Uint8 xmlGiveStateType(std::string type);
	static Uint8 xmlGiveSelectType(std::string type);
	static std::unordered_map<std::string, Texte*>& xmlGiveTexteConteneur(AllTextes& allTextes, std::string type);
	static Texte_Type xmlGiveTexteType(std::string type);
	static SDL_Color xmlGiveColor(std::string type);
	static Transparance_Type xmlGiveAlpha(std::string type);
	static Rotation_Type xmlGiveAngle(std::string type);
	static Center_Type xmlGiveCenter(std::string type);

	static int determineCoor(std::string line, Uint16 screenWidth, Uint16 screenHeight);


	/* *********************************************************
	 *					INITIALISATION						   *
	 ********************************************************* */

	static void initPtrSysinfo(Sysinfo& sysinfo);

	/*
	* NAME : initTile
	* ROLE : Initialisation des cases de la map en fonction de sa taille
	* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
	* OUTPUT PARAMETERS : Initialisation de map.screen et map.maps
	* RETURNED VALUE    : void
	*/
	static void initTile(Map& map);

	/*
	* NAME : initFile
	* ROLE : Initialisation des fichiers : log
	* INPUT  PARAMETERS : struct File& : nom des fichiers
	* OUTPUT PARAMETERS : Initialisation de log.txt
	* RETURNED VALUE    : void
	*/
	static void initFile(File& file);

	/*
	* NAME : logfileconsole
	* ROLE : Transmission du message sur la console et dans le fichier log.txt
	* INPUT  PARAMETERS : const std::string msg : message
	* OUTPUT PARAMETERS : message dans la console et le log.txt
	* RETURNED VALUE    : void
	*/
	static void logfileconsole(const std::string msg);

	/*
	* NAME : initSDL
	* ROLE : Initialisation de la SDL fenetre et renderer ainsi que le tableau de police de font
	* INPUT  PARAMETERS : SDL_Window*& : pointeur sur la fenetre de la SDL
	* INPUT  PARAMETERS : SDL_Renderer*& : pointeur sur le Renderer de la SDL
	* INPUT  PARAMETERS : TTF_Font*[] : pointeur sur le tableau de police de font
	* OUTPUT PARAMETERS : message dans la console et le log.txt
	* RETURNED VALUE    : bool : true = pas de d'erreur lors de l'initialisation de la SDL
	*/
	static bool initSDL(Screen& screen, TTF_Font* font[]);

private:

};


#endif // !LoadConfig_H


/*
*	End Of File : LoadConfig.h
*/

