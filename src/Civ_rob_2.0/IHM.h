/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.20.0.5
	file version : 1.14

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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"

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

class IHM
{
public:
	/* *********************************************************
	 *						IN-GAME							   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : titleScreen																   */
	/* ROLE : Desciption de la fenetre "titleScreen"									   */
	/* ROLE : fonctionnement selon l'état : enum State_Type = STATEtitleScreen			   */
	/* INPUT  : struct Sysinfo& : structure globale du programme						   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void titleScreen
	(
		Sysinfo&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : refreshNbPlayerTxt														   */
	/* ROLE : Maj du nombre de joueurs lors de la saisie								   */
	/* INPUT/OUTPUT : SDL_Renderer*& : Ptr sur le SDL_Renderer							   */
	/* INPUT/OUTPUT : TTF_Font* font[] : ptr sur tableau de font						   */
	/* INPUT : const Var& var : structure globale pour les variables					   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void refreshNbPlayerTxt
	(
		SDL_Renderer*& renderer,
		TTF_Font* font[],
		const Var& var
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : refreshNamePlayerTxt														   */
	/* ROLE : Maj du noms du joueur lors de la saisie									   */
	/* INPUT/OUTPUT : SDL_Renderer*& : Ptr sur le SDL_Renderer							   */
	/* INPUT/OUTPUT : TTF_Font* font[] : ptr sur tableau de font						   */
	/* INPUT : const Var& var : structure globale pour les variables					   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void refreshNamePlayerTxt
	(
		SDL_Renderer*& renderer,
		TTF_Font* font[],
		const Var& var
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : reloadScreen																   */
	/* ROLE : Desciption de la fenetre "reloadScreen"									   */
	/* ROLE : fonctionnement selon l'état : enum State_Type = STATEreload				   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void reloadScreen
	(
		Sysinfo& sysinfo
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : alwaysrender																   */
	/* ROLE : Tous les 1/SCREEN_REFRESH_RATE cette fonction permet ...					   */
	/* ROLE : ... la désciption de la fenetre "STATEmainmap" ou "STATEcitiemap"			   */
	/* ROLE : fonctionnement selon l'état : enum State_Type = STATEmainmap ou STATEcitiemap*/
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void														       */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void alwaysrender
	(
		Sysinfo&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : mainmap																	   */
	/* ROLE : Affichage de la mainmap													   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void														       */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void mainmap
	(
		Sysinfo& sysinfo
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : afficherSupertiles														   */
	/* ROLE : Affichage de la map (tiles, spec, appartenance) aux dimensions map.screen	   */
	/* INPUT : struct Sysinfo& : structure globale du programme						       */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void afficherSupertiles
	(
		Sysinfo&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : citiemap																	   */
	/* ROLE : Affichage de la fenetre citiemap											   */
	/* ROLE : fonctionnement selon l'état : enum State_Type = STATEcitiemap				   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void citiemap
	(
		Sysinfo&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : countFrame																   */
	/* ROLE : Compteur de frames durant le programme 									   */
	/* ROLE : Début : à la fin de la fonction newGame(...)								   */
	/* INPUT : Screen& screen : données concernant la fenetre SDL						   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void countFrame
	(
		Screen& screen
	);
};

#endif

/*
*	End Of File : IHM.h
*/
