/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.18
	file version : 1.11

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
	 *						IN-GAME							   *
	 ********************************************************* */

	

	/*
	* NAME : titleScreen
	* ROLE : Desciption de la fenetre "titleScreen"
	* ROLE : fonctionnement selon l'état : enum State_Type = STATEtitleScreen
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : Ouverture de la fenetre "titleScreen"
	* RETURNED VALUE    : void
	*/
	static void titleScreen
	(
		Sysinfo&
	);


	static void refreshNbPlayerTxt
	(
		Sysinfo& sysinfo
	);

	static void refreshNamePlayerTxt
	(
		Sysinfo& sysinfo
	);


	/*
	 * NAME : reloadScreen
	 * ROLE : Desciption de la fenetre "reloadScreen"
	 * ROLE : fonctionnement selon l'état : enum State_Type = STATEreload
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : Ouverture de la fenetre "reloadScreen"
	 * RETURNED VALUE    : void
	 */
	static void reloadScreen
	(
		Sysinfo& sysinfo
	);

	/*
	 * NAME : alwaysrender
	 * ROLE : Tous les 1/SCREEN_REFRESH_RATE cette fonction permet ...
	 * ROLE : ... la désciption de la fenetre "STATEmainmap" ou "STATEcitiemap"
	 * ROLE : fonctionnement selon l'état : enum State_Type = STATEmainmap ou STATEcitiemap
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : Ouverture de la fenetre "STATEmainmap" ou "STATEcitiemap"
	 * RETURNED VALUE    : void
	 */
	static void alwaysrender
	(
		Sysinfo&
	);


	static void mainmap
	(
		Sysinfo& sysinfo
	);

	/*
	 * NAME : afficherSupertiles
	 * ROLE : Affichage de la map (tiles, spec, appartenance) aux dimensions map.screen 
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : Affichage de la map sur la fenetre "mainMap"
	 * RETURNED VALUE    : void
	 */
	static void afficherSupertiles
	(
		Sysinfo&
	);

	static bool checkPlayerUnitSelection
	(
		const SubcatPlayer& s_player
	);

	/*
	 * NAME : citiemap
	 * ROLE : Affichage de la fenetre citiemap
	 * ROLE : fonctionnement selon l'état : enum State_Type = STATEcitiemap
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS :  Affichage de la map sur la fenetre "citieMap"
	 * RETURNED VALUE    : void
	 */
	static void citiemap
	(
		Sysinfo&
	);

	/*
	 * NAME : countFrame
	 * ROLE : Compteur de frames durant le programme 
	 * ROLE : Début : à la fin de la fonction newGame(...)
	 * INPUT  PARAMETERS : Screen& screen : données concernant la fenetre SDL
	 * OUTPUT PARAMETERS : Incrémentation du nombre de frames comptées
	 * RETURNED VALUE    : void
	 */
	static void countFrame
	(
		Screen& screen
	);
};

#endif

/*
*	End Of File : IHM.h
*/
