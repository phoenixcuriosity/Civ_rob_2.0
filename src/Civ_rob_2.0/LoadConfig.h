/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.19
	file version : 1.5

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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"
#include "civ_lib.h"
#include "Texture.h"

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

/* N/A */

/* *********************************************************
 *						 Enum							   *
 ********************************************************* */

/* N/A */

/* *********************************************************
 *						Structures						   *
 ********************************************************* */

/* N/A */

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */
class LoadConfig
{
public:
	/* *********************************************************
	 *					INITIALISATION						   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initPtrSysinfo															   */
	/* ROLE : Initialisation des ptr sur sysinfo et logger								   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void initPtrSysinfo
	(
		Sysinfo& sysinfo
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initStructs																   */
	/* ROLE : Initialisation des données par défaut des structures						   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void initStructs
	(
		Sysinfo& sysinfo
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initFile																	   */
	/* ROLE : Initialisation des fichiers : log											   */
	/* INPUT : struct File& : nom des fichiers											   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void initFile
	(
		File& file
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initMain																	   */
	/* ROLE : Chargement des informations de la configuration du jeu					   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void initMain
	(
		Sysinfo& sysinfo
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : computeSize																   */
	/* ROLE : Calcul des différentes tailles de fenetre en fonction de tileSize			   */
	/* INPUT/OUTPUT : Screen& screen : longueur et hauteur écran						   */
	/* INPUT/OUTPUT : struct Sysinfo& : différentes tailles de fenetre					   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void computeSize
	(
		Screen& screen,
		Map& map
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : getHorizontal																   */
	/* ROLE : Calcul de la longueur en pixels de la fenetre								   */
	/* INPUT : unsigned int tileSize : taille en pixel d'une tile 						   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static Uint16 getHorizontal
	(
		unsigned int tileSize
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : getVertical																   */
	/* ROLE : Calcul de la hauteur en pixels de la fenetre								   */
	/* INPUT : unsigned int tileSize : taille en pixel d'une tile 						   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static Uint16 getVertical
	(
		unsigned int tileSize
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initTile																	   */
	/* ROLE : Initialisation des cases de la map en fonction de sa taille				   */
	/* INPUT : struct Map& : données générale de la map : taille						   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void initTile
	(
		Map& map
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : loadUnitAndSpec															   */
	/* ROLE : Chargement des informations concernant les unités à partir d'un fichier	   */
	/* INPUT : const std::string& : nom du fichier à ouvrir								   */
	/* OUTPUT : std::vector<Unit_Struct>& : Vecteur des Unit							   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void loadUnitAndSpec
	(
		const std::string& UNIT,
		std::vector<Unit_Struct>& tabUnit_Struct
	);

	static Unit_Movement_Type xmlGiveMovementType
	(
		std::string type
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : logfileconsole															   */
	/* ROLE : Transmission du message sur la console et dans le fichier log.txt			   */
	/* INPUT : const std::string msg : message											   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void logfileconsole
	(
		const std::string msg
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initSDL																	   */
	/* ROLE : Initialisation de la SDL fenetre et renderer ...							   */
	/* ROLE : ... ainsi que le tableau de police de font								   */
	/* INPUT : SDL_Window*& : pointeur sur la fenetre de la SDL							   */
	/* INPUT : SDL_Renderer*& : pointeur sur le Renderer de la SDL						   */
	/* INPUT : TTF_Font*[] : pointeur sur le tableau de police de font					   */
	/* RETURNED VALUE    : bool : true = pas d'erreur lors de l'initialisation de la SDL   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static bool initSDL
	(
		Screen& screen,
		TTF_Font* font[]
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : calculImage																   */
	/* ROLE : Initialisation des Textures, des Textes et des Buttons					   */
	/* ROLE : Enregistrement des pointeurs dans des unorder_map							   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void calculImage
	(
		Sysinfo& sysinfo
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : readXmlTexte																   */
	/* ROLE : Initialisation des Textes par la lecture du fichier Texte.xml				   */
	/* ROLE : Enregistrement des pointeurs dans des unorder_map							   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void readXmlTexte
	(
		tinyxml2::XMLDocument& texteFile,
		SDL_Renderer*& renderer,
		TTF_Font* font[],
		AllTextes& allTextes,
		Uint16 screenWidth,
		Uint16 screenHeight
	);

	static State_Type xmlGiveStateType
	(
		std::string type
	);

	static Select_Type xmlGiveSelectType
	(
		std::string type
	);

	static std::unordered_map<std::string, Texte*>& xmlGiveTexteConteneur
	(
		AllTextes& allTextes,
		std::string type
	);

	static Texte_Type xmlGiveTexteType
	(
		std::string type
	);

	static SDL_Color xmlGiveColor
	(
		std::string type
	);

	static Transparance_Type xmlGiveAlpha
	(
		std::string type
	);

	static Uint16 xmlGiveAngle
	(
		std::string type
	);

	static Center_Type xmlGiveCenter
	(
		std::string type
	);

	static int determineCoor
	(
		std::string line, 
		Uint16 screenWidth,
		Uint16 screenHeight
	);
};


#endif // !LoadConfig_H


/*
*	End Of File : LoadConfig.h
*/

