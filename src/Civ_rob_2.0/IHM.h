/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.16
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

	/*
	* NAME : initTile
	* ROLE : Initialisation des cases de la map en fonction de sa taille
	* INPUT  PARAMETERS : struct Map& : donn�es g�n�rale de la map : taille
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
	static bool initSDL(SDL_Window*&, SDL_Renderer*&, TTF_Font*[]);

	/*
	* NAME : calculImage
	* ROLE : Initialisation des Textures, des Textes et des Buttons 
	* ROLE : Enregistrement des pointeurs dans des tableaux
	* ROLE : Hachage des noms des Textures (et classes filles) pour une recherche en complexit� en O(1)
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
	static void readXmlTexte(tinyxml2::XMLDocument& texteFile, SDL_Renderer*& renderer, TTF_Font* font[],AllTextes& allTextes);

	static int determineCoor(std::string line);


public:
	/* *********************************************************
	 *						IN-GAME							   *
	 ********************************************************* */

	 /*
	 * NAME : eventSDL
	 * ROLE : Recherche infini des �venements d'entr� de type SDL_event : souris, clavier
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : �venements d'entr� utilisateur
	 * RETURNED VALUE    : void
	 */
	static void eventSDL(Sysinfo& sysinfo);

	/*
	* NAME : titleScreen
	* ROLE : Desciption de la fenetre "titleScreen"
	* ROLE : fonctionnement selon l'�tat : enum State_Type = STATEtitleScreen
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : Ouverture de la fenetre "titleScreen"
	* RETURNED VALUE    : void
	*/
	static void titleScreen(Sysinfo&);

	/*
	 * NAME : reloadScreen
	 * ROLE : Desciption de la fenetre "reloadScreen"
	 * ROLE : fonctionnement selon l'�tat : enum State_Type = STATEreload
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : Ouverture de la fenetre "reloadScreen"
	 * RETURNED VALUE    : void
	 */
	static void reloadScreen(Sysinfo& sysinfo);

	/*
	 * NAME : alwaysrender
	 * ROLE : Tous les 1/SCREEN_REFRESH_RATE cette fonction permet ...
	 * ROLE : ... la d�sciption de la fenetre "STATEmainmap" ou "STATEcitiemap"
	 * ROLE : fonctionnement selon l'�tat : enum State_Type = STATEmainmap ou STATEcitiemap
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
	 * ROLE : fonctionnement selon l'�tat : enum State_Type = STATEcitiemap
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS :  Affichage de la map sur la fenetre "citieMap"
	 * RETURNED VALUE    : void
	 */
	static void citiemap(Sysinfo&);

	/*
	 * NAME : countFrame
	 * ROLE : Compteur de frames durant le programme 
	 * ROLE : D�but : � la fin de la fonction newGame(...)
	 * INPUT  PARAMETERS : Screen& screen : donn�es concernant la fenetre SDL
	 * OUTPUT PARAMETERS : Incr�mentation du nombre de frames compt�es
	 * RETURNED VALUE    : void
	 */
	static void countFrame(Screen& screen);




public:
	/* *********************************************************
	 *						END-GAME						   *
	 ********************************************************* */

	static void exitError(const std::string msg);

	/*
	 * NAME : deleteAll
	 * ROLE : Destruction des allocations dynamique du programme
	 * ROLE : Destruction de la fenetre et du Renderer de la SDL
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : Destruction des allocations dynamique du programme
	 * RETURNED VALUE    : void
	 */
	static void deleteAll(Sysinfo&);
};



/*
	 * NAME : deleteDyTabPlayerAndTextures
	 * ROLE : Destruction des allocations dynamique du tableau de pointeurs
	 * INPUT  PARAMETERS : T& dytab : template<class T> : Texture et classes filles
	 * INPUT  PARAMETERS : const std::string& name : nom du tableau � d�truire
	 * OUTPUT PARAMETERS : Destruction des allocations dynamique
	 * RETURNED VALUE    : void
*/
template<class T>
void deleteDyTabPlayerAndTextures(T& dytab, const std::string& name)
{
	unsigned int size = dytab.size();
	for (unsigned int i = 0; i < size; i++)
	{
		if (dytab[i] != nullptr)
		{
			IHM::logfileconsole("[INFO]___: Delete " + name + " name = " + dytab[i]->GETname() + " Success");
			delete dytab[i];
		}
	}
	for (unsigned int i = 0; i < size; i++)
		dytab.pop_back();
	if (dytab.size() != 0)
		IHM::logfileconsole("[ERROR]___:___________ERROR : " + name + ".size() != 0");
	else
		IHM::logfileconsole("[INFO]___: Delete ALL " + name + " Success");
}


#endif

/*
*	End Of File : IHM.h
*/