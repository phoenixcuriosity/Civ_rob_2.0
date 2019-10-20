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

#ifndef IHM_H
#define IHM_H

#include "LIB.h"
#include "Player.h"

class IHM
{
public:
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
	* NAME : logSDLError
	* ROLE : SDL erreur
	* INPUT  PARAMETERS : std::ostream &os, const std::string &msg
	* OUTPUT PARAMETERS : message d'erreur dans la console
	* RETURNED VALUE    : void
	*/
	static void logSDLError(std::ostream &os, const std::string &msg);

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

public:
	/* *********************************************************
	 *						IN-GAME							   *
	 ********************************************************* */

	 /*
	 * NAME : eventSDL
	 * ROLE : Recherche infini des évenements d'entré de type SDL_event : souris, clavier
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : évenements d'entré utilisateur
	 * RETURNED VALUE    : void
	 */
	static void eventSDL(Sysinfo& sysinfo);

	/*
	* NAME : titleScreen
	* ROLE : Desciption de la fenetre "titleScreen"
	* ROLE : fonctionnement selon l'état : enum State_Type = STATEtitleScreen
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : Ouverture de la fenetre "titleScreen"
	* RETURNED VALUE    : void
	*/
	static void titleScreen(Sysinfo&);

	/*
	 * NAME : reloadScreen
	 * ROLE : Desciption de la fenetre "reloadScreen"
	 * ROLE : fonctionnement selon l'état : enum State_Type = STATEreload
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : Ouverture de la fenetre "reloadScreen"
	 * RETURNED VALUE    : void
	 */
	static void reloadScreen(Sysinfo& sysinfo);

	/*
	 * NAME : alwaysrender
	 * ROLE : Tous les 1/SCREEN_REFRESH_RATE cette fonction permet ...
	 * ROLE : ... la désciption de la fenetre "STATEmainmap" ou "STATEcitiemap"
	 * ROLE : fonctionnement selon l'état : enum State_Type = STATEmainmap ou STATEcitiemap
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : Ouverture de la fenetre "STATEmainmap" ou "STATEcitiemap"
	 * RETURNED VALUE    : void
	 */
	static void alwaysrender(Sysinfo&);

	/*
	 * NAME : afficherSupertiles
	 * ROLE : Affichage de la map (tiles, spec, appartenance) aux dimensions map.screen 
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : Affichage de la map sur la fenetre "mainMap"
	 * RETURNED VALUE    : void
	 */
	static void afficherSupertiles(Sysinfo&);

	/*
	 * NAME : citiemap
	 * ROLE : Affichage de la fenetre citiemap
	 * ROLE : fonctionnement selon l'état : enum State_Type = STATEcitiemap
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS :  Affichage de la map sur la fenetre "citieMap"
	 * RETURNED VALUE    : void
	 */
	static void citiemap(Sysinfo&);

	/*
	 * NAME : countFrame
	 * ROLE : Compteur de frames durant le programme 
	 * ROLE : Début : à la fin de la fonction newGame(...)
	 * INPUT  PARAMETERS : Screen& screen : données concernant la fenetre SDL
	 * OUTPUT PARAMETERS : Incrémentation du nombre de frames comptées
	 * RETURNED VALUE    : void
	 */
	static void countFrame(Screen& screen);
};





/*
	 * NAME : deleteDyTabPlayerAndTextures
	 * ROLE : Destruction des allocations dynamique du tableau de pointeurs
	 * INPUT  PARAMETERS : T& dytab : template<class T> : Texture et classes filles
	 * INPUT  PARAMETERS : const std::string& name : nom du tableau à détruire
	 * OUTPUT PARAMETERS : Destruction des allocations dynamique
	 * RETURNED VALUE    : void
*/
/*
template<typename T>
void deleteDyTabPlayerAndTextures(T& dytab, const std::string& name)
{
	for (const auto& n : a)
	{
		if (n.second != nullptr)
		{
			IHM::logfileconsole("[INFO]___: Delete " + name + " name = " + n.second->GETname() + " Success");
			delete n.second;
		}
	}
}
*/


#endif

/*
*	End Of File : IHM.h
*/
