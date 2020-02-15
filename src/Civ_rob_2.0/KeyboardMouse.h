/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.18
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

#ifndef KeyboardMouse_H
#define KeyboardMouse_H

#include "LIB.h"

class KeyboardMouse
{
public:


	/*
	* NAME : eventSDL
	* ROLE : Recherche infini des évenements d'entré de type SDL_event : souris, clavier
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : évenements d'entré utilisateur
	* RETURNED VALUE    : void
	*/
	static void eventSDL(Sysinfo& sysinfo);

	static void eventSDL_bis(Sysinfo& sysinfo, SDL_Event event);

	static void wait_SDL(Sysinfo& sysinfo);

	static void run_SDL(Sysinfo& sysinfo);

	


public:
	/* *********************************************************
	 *			KeyboardMouse::STATIC::UNE TOUCHE			   *
	 ********************************************************* */

	static void keySDLK_ESCAPE();
	static void keySDLK_BACKSPACE(Sysinfo& sysinfo);
	static void keySDLK_RETURN(Sysinfo& sysinfo);
	static void keySDLK_KP_ENTER(Sysinfo& sysinfo);
	static void keySDLK_SPACE(Sysinfo& sysinfo);

	static void keySDLK_F1(Sysinfo& sysinfo);
	static void keySDLK_F2(Sysinfo& sysinfo);
	static void keySDLK_F3(Sysinfo& sysinfo);
	static void keySDLK_F4(Sysinfo& sysinfo);
	static void keySDLK_F5(Sysinfo& sysinfo);
	static void keySDLK_F6(Sysinfo& sysinfo);
	static void keySDLK_F7(Sysinfo& sysinfo);
	static void keySDLK_F8(Sysinfo& sysinfo);
	static void keySDLK_F9(Sysinfo& sysinfo);
	static void keySDLK_F10(Sysinfo& sysinfo);
	static void keySDLK_F11(Sysinfo& sysinfo);
	static void keySDLK_F12(Sysinfo& sysinfo);

	static void keySDLK_UP(Sysinfo& sysinfo);
	static void keySDLK_LEFT(Sysinfo& sysinfo);
	static void keySDLK_DOWN(Sysinfo& sysinfo);
	static void keySDLK_RIGHT(Sysinfo& sysinfo);

	static void keySDLK_a(Sysinfo& sysinfo);
	static void keySDLK_b(Sysinfo& sysinfo);
	static void keySDLK_c(Sysinfo& sysinfo);
	static void keySDLK_d(Sysinfo& sysinfo);
	static void keySDLK_e(Sysinfo& sysinfo);
	static void keySDLK_f(Sysinfo& sysinfo);
	static void keySDLK_g(Sysinfo& sysinfo);
	static void keySDLK_h(Sysinfo& sysinfo);
	static void keySDLK_i(Sysinfo& sysinfo);
	static void keySDLK_j(Sysinfo& sysinfo);
	static void keySDLK_k(Sysinfo& sysinfo);
	static void keySDLK_l(Sysinfo& sysinfo);
	static void keySDLK_m(Sysinfo& sysinfo);
	static void keySDLK_n(Sysinfo& sysinfo);
	static void keySDLK_o(Sysinfo& sysinfo);
	static void keySDLK_p(Sysinfo& sysinfo);
	static void keySDLK_q(Sysinfo& sysinfo);
	static void keySDLK_r(Sysinfo& sysinfo);
	static void keySDLK_s(Sysinfo& sysinfo);
	static void keySDLK_t(Sysinfo& sysinfo);
	static void keySDLK_u(Sysinfo& sysinfo);
	static void keySDLK_v(Sysinfo& sysinfo);
	static void keySDLK_w(Sysinfo& sysinfo);
	static void keySDLK_x(Sysinfo& sysinfo);
	static void keySDLK_y(Sysinfo& sysinfo);
	static void keySDLK_z(Sysinfo& sysinfo);


	/*
	* comm 0.14e : ce commentaire est commun au 9 boutons 
	* NAME : keySDLK_KP_1
	* ROLE : Appel la fonction dans le contexte de l'appuie sur la touche
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : Appel une fonction
	* RETURNED VALUE    : void
	*/
	static void keySDLK_KP_1(Sysinfo&);
	static void keySDLK_KP_2(Sysinfo&);
	static void keySDLK_KP_3(Sysinfo&);
	static void keySDLK_KP_4(Sysinfo&);
	static void keySDLK_KP_5(Sysinfo&);
	static void keySDLK_KP_6(Sysinfo&);
	static void keySDLK_KP_7(Sysinfo&);
	static void keySDLK_KP_8(Sysinfo&);
	static void keySDLK_KP_9(Sysinfo&);

	static bool conditionTryToMove
	(
		const Var var
	);


public:
	/* *********************************************************
	 *			KeyboardMouse::STATIC::SOURIS				   *
	 ********************************************************* */

	 /*
	 * NAME : mouse
	 * ROLE : Dispatch entre clique droit ou clique gauche
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * INPUT  PARAMETERS : SDL_Event : l'évenement du clique
	 * OUTPUT PARAMETERS : choix du clique
	 * RETURNED VALUE    : void
	 */
	static void mouse(Sysinfo&, SDL_Event);

	/*
	* NAME : cliqueGauche
	* ROLE : Recherche de la zone ou le clique à lieu
	* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* INPUT  PARAMETERS : SDL_Event : l'évenement du clique
	* OUTPUT PARAMETERS : la chaine de caractères a retourner
	* RETURNED VALUE    : void
	*/
	static void cliqueGauche(Sysinfo&, SDL_Event);

	/*
	* NAME : cliqueDroit
	* ROLE : Recherche de la zone ou le clique à lieu
	* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* INPUT  PARAMETERS : SDL_Event : l'évenement du clique
	* OUTPUT PARAMETERS : la chaine de caractères a retourner
	* RETURNED VALUE    : void
	*/
	static void cliqueDroit(Sysinfo&, SDL_Event);

	/*
	* NAME : wheel
	* ROLE : Recherche l'incrémentation ou décrémentation du contexte
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* INPUT  PARAMETERS : int& wheel : l'évenement de scroll de la souris
	* OUTPUT PARAMETERS : une action suivant l'incrémentation ou décrémentation du contexte
	* RETURNED VALUE    : void
	*/
	static void wheel(Sysinfo&, int& wheel);

	/*
	* NAME : resetButtonOn
	* ROLE : reset de l'affichage On des boutons
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : reset de l'affichage On des boutons
	* RETURNED VALUE    : void
	*/
	static void resetButtonOn(Sysinfo& sysinfo);

	/*
	* NAME : resetButtonPlayerOn
	* ROLE : reset de l'affichage On des boutons player
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : reset de l'affichage On des boutons player
	* RETURNED VALUE    : void
	*/
	static void resetButtonPlayerOn(Sysinfo& sysinfo);

	/*
	* NAME : resetButtonCitieMap
	* ROLE : reset de l'affichage On des boutons citieMap
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : reset de l'affichage On des boutons citieMap
	* RETURNED VALUE    : void
	*/
	static void resetButtonCitieMap(Sysinfo& sysinfo);



public:
	/* *********************************************************
	 *				KeyboardMouse::METHODS			  		   *
	 ********************************************************* */


	KeyboardMouse();
	~KeyboardMouse() {};

	
	
public:
	/* *********************************************************
	 *			KeyboardMouse::METHODS::GET/SET				   *
	 ********************************************************* */
	 
	 
	inline unsigned int GETmouse_x()const	{ return _mouse_x; };
	inline unsigned int GETmouse_y()const	{ return _mouse_y; };
	inline unsigned int GETywheel()const	{ return _ywheel; };
	inline unsigned int GETxwheel()const	{ return _xwheel; };

	inline void SETmouse_x(unsigned int mouse_x)	{ _mouse_x = mouse_x; };
	inline void SETmouse_y(unsigned int mouse_y)	{ _mouse_y = mouse_y; };
	inline void SETywheel(unsigned int ywheel)		{ _ywheel = ywheel; };
	inline void SETxwheel(unsigned int xwheel)		{ _xwheel = xwheel; };
	

private:
	/* *********************************************************
	 *				KeyboardMouse::ATTIBUTS					   *
	 ********************************************************* */

	unsigned int _mouse_x;
	unsigned int _mouse_y;
	unsigned int _ywheel;
	unsigned int _xwheel;
};

#endif /* KeyboardMouse_H */


/*
*	End Of File : KeyboardMouse.h
*/
