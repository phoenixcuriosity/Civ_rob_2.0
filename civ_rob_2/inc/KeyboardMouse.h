/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.15
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

#ifndef KeyboardMouse_H
#define KeyboardMouse_H

#include "LIB.h"

class KeyboardMouse
{
public:
	/* *********************************************************
	 *			KeyboardMouse::STATIC::CIN
	 ********************************************************* */

	/*
	* NAME : cinDigit
	* ROLE : Recherche d'un digit rentré par le joueur
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* INPUT  PARAMETERS : unsigned int& digit : le digit a retourner
	* INPUT  PARAMETERS : unsigned int x : coordonnée en x pour l'affichage du digit
	* INPUT  PARAMETERS : unsigned int y : coordonnée en y pour l'affichage du digit
	* OUTPUT PARAMETERS : le digit
	* RETURNED VALUE    : void
	*/
	static void cinDigit(Sysinfo& sysinfo, unsigned int& digit, unsigned int x, unsigned int y);

	/*
	* NAME : cinAlphabet
	* ROLE : Recherche d'une chaine de caractères (finisant par \0) rentré par le joueur
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* INPUT  PARAMETERS : std::string &name : la chaine de caractères a retourner
	* INPUT  PARAMETERS : unsigned int x : coordonnée en x pour l'affichage
	* INPUT  PARAMETERS : unsigned int y : coordonnée en y pour l'affichage
	* OUTPUT PARAMETERS : la chaine de caractères a retourner
	* RETURNED VALUE    : void
	*/
	static void cinAlphabet(Sysinfo& sysinfo, std::string &name, unsigned int x, unsigned int y);


public:
	/* *********************************************************
	 *			KeyboardMouse::STATIC::UNE TOUCHE
	 ********************************************************* */


	 /*
	 * NAME : cinAlphabet
	 * ROLE : Recherche d'une chaine de caractères (finisant par \0) rentré par le joueur
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * INPUT  PARAMETERS : std::string &name : la chaine de caractères a retourner
	 * INPUT  PARAMETERS : unsigned int x : coordonnée en x pour l'affichage
	 * INPUT  PARAMETERS : unsigned int y : coordonnée en y pour l'affichage
	 * OUTPUT PARAMETERS : la chaine de caractères a retourner
	 * RETURNED VALUE    : void
	 */
	static void keySDLK_b(Sysinfo&);

	/*
	* NAME : cinAlphabet
	* ROLE : Recherche d'une chaine de caractères (finisant par \0) rentré par le joueur
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* INPUT  PARAMETERS : std::string &name : la chaine de caractères a retourner
	* INPUT  PARAMETERS : unsigned int x : coordonnée en x pour l'affichage
	* INPUT  PARAMETERS : unsigned int y : coordonnée en y pour l'affichage
	* OUTPUT PARAMETERS : la chaine de caractères a retourner
	* RETURNED VALUE    : void
	*/
	static void keySDLK_i(Sysinfo&);


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


public:
	/* *********************************************************
	 *			KeyboardMouse::STATIC::SOURIS
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
	 *				KeyboardMouse::METHODS
	 ********************************************************* */


	KeyboardMouse();
	~KeyboardMouse() {};

	
	
public:
	/* *********************************************************
	 *			KeyboardMouse::METHODS::GET/SET
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
	 *				KeyboardMouse::ATTIBUTS
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
