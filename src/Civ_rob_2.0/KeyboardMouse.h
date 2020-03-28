/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.20.0.5
	file version : 1.8

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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

/* SDL : Define the number of mouse click ONE */
#define ONE_CLICK 1

/* SDL : Define the number of mouse clicks TWO */
#define TWO_CLICKS 2

/* SDL : Define if the wheel scroll up */
#define MOUSE_SCROLL_UP 1

/* SDL : Define if the wheel scroll down */
#define MOUSE_SCROLL_DOWN -1

/* *********************************************************
 *						 Enum							   *
 ********************************************************* */

/* Define input from keyboard in a context */
enum class CinState_Type : Uint8
{
	cinNothing,						/* Inputs from keyboards are discard */
	cinTitleScreen,					/* Inputs from keyboards are use in Title Screen */
	cinScreenNewGameNbPlayer,		/* Inputs from keyboards are use in New Game : for number of player */
	cinScreenNewGameNamePlayer,		/* Inputs from keyboards are use in New Game : for names of players */
	cinMainMap,						/* Inputs from keyboards are use in Main map */
};

/* *********************************************************
 *						Structures						   *
 ********************************************************* */

/* N/A */

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */

class KeyboardMouse
{
public:
	/* *********************************************************
	 *					KeyboardMouse STATIC				   *
	 ********************************************************* */

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : checkCaseSDL																				    	  */
	/* ROLE : Check du cas du type cinState, choix entre wait et run SDL event								      */
	/* ROLE : Recherche les évenements d'entré de type SDL_event : souris, clavier							      */
	/* INPUT : struct Sysinfo& : structure globale du programme									    			  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void checkCaseSDL
	(
		Sysinfo& sysinfo
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : wait_SDL																					    	  */
	/* ROLE : Attente d'un évenement d'entrée de la SDL de type SDL_event : souris, clavier					      */
	/* INPUT : struct Sysinfo& : structure globale du programme									    			  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void wait_SDL
	(
		Sysinfo& sysinfo
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : run_SDL																					    	  */
	/* ROLE : Recherche infini des évenements d'entré de type SDL_event : souris, clavier					      */
	/* ROLE : Si aucun évenements n'est trouvé alors le programme continue									      */
	/* INPUT : struct Sysinfo& : structure globale du programme									    			  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void run_SDL
	(
		Sysinfo& sysinfo
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : eventSDL																					    	  */
	/* ROLE : Recherche d'entré de type SDL_event : souris, clavier											      */
	/* INPUT : struct Sysinfo& : structure globale du programme									    			  */
	/* INPUT : SDL_Event event : entré de type SDL_event 										    			  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void eventSDL
	(
		Sysinfo& sysinfo,
		SDL_Event event
	);


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
	 *			KeyboardMouse::STATIC::SOURIS				   *
	 ********************************************************* */


	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : mouse																						    	  */
	/* ROLE : Dispatch entre clique droit ou clique gauche													      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
	/* INPUT : SDL_Event : l'évenement du clique			    												  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void mouse
	(
		Sysinfo&,
		SDL_Event
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : cliqueGauche																				    	  */
	/* ROLE : Recherche de la zone ou le clique à lieu sur chaque case de STATE								      */
	/* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)							      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme											  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void cliqueGauche
	(
		Sysinfo& sysinfo,
		SDL_Event event
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : checkSTATEmainmap																			    	  */
	/* ROLE : Recherche de la zone ou le clique à lieu sur STATEmainmap										      */
	/* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)							      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme											  */
	/* RETURNED VALUE : bool -> false : aucun boutons ou fonctions utilisés										  */
	/* RETURNED VALUE : bool -> true : un bouton ou une fonction utilisé										  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static bool checkSTATEmainmap
	(
		Sysinfo& sysinfo
	); 

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : inspectCitie																				    	  */
	/* ROLE : Recherche de la position de la Citie sur tous les joueurs										      */
	/* ROLE : Si aucun joueur n'existe la Citie ne peut pas etre trouvée									      */
	/* INPUT : const TabPlayer& tabplayer : tableau de ptr de joueurs											  */
	/* INPUT/OUTPUT : Var& var : Structure des Variables non organisées											  */
	/* RETURNED VALUE : bool -> false : la Citie n'est enregistrée chez aucun joueur ou il n'y aucun joueur		  */
	/* RETURNED VALUE : bool -> true : la Citie est enregistrée chez joueur (et existance dui joueur)			  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static bool inspectCitie
	(
		const TabPlayer& tabplayer,
		Var& var
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : checkSTATEtitleScreen																		    	  */
	/* ROLE : Recherche de la zone ou le clique à lieu sur STATEtitleScreen									      */
	/* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)							      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme											  */
	/* RETURNED VALUE : bool -> false : aucun boutons ou fonctions utilisés										  */
	/* RETURNED VALUE : bool -> true : un bouton ou une fonction utilisé										  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static bool checkSTATEtitleScreen
	(
		Sysinfo& sysinfo
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : checkSTATEreload																			    	  */
	/* ROLE : Recherche de la zone ou le clique à lieu sur STATEreload										      */
	/* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)							      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme											  */
	/* RETURNED VALUE : bool -> false : aucun boutons ou fonctions utilisés										  */
	/* RETURNED VALUE : bool -> true : un bouton ou une fonction utilisé										  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static bool checkSTATEreload
	(
		Sysinfo& sysinfo
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : checkSTATEcitiemap																		    	  */
	/* ROLE : Recherche de la zone ou le clique à lieu sur STATEcitiemap									      */
	/* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)							      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme											  */
	/* RETURNED VALUE : bool -> false : aucun boutons ou fonctions utilisés										  */
	/* RETURNED VALUE : bool -> true : un bouton ou une fonction utilisé										  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static bool checkSTATEcitiemap
	(
		Sysinfo& sysinfo
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : cliqueDroit																				    	  */
	/* ROLE : Recherche de la zone ou le clique à lieu														      */
	/* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)							      */
	/* INPUT : struct Sysinfo& : structure globale du programme													  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void cliqueDroit
	(
		Sysinfo&
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : wheel																						    	  */
	/* ROLE : Recherche l'incrémentation ou décrémentation du contexte										      */
	/* INPUT : struct Sysinfo& : structure globale du programme												      */
	/* INPUT : int& wheel : l'évenement de scroll de la souris													  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void wheel
	(
		Sysinfo&,
		int& wheel
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : resetButtonOn																				    	  */
	/* ROLE : reset de l'affichage On des boutons															      */
	/* INPUT : struct Sysinfo& : structure globale du programme												      */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void resetButtonOn
	(
		Sysinfo& sysinfo
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : resetButtonPlayerOn																		    	  */
	/* ROLE : reset de l'affichage On des boutons player													      */
	/* INPUT : struct Sysinfo& : structure globale du programme												      */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void resetButtonPlayerOn
	(
		Sysinfo& sysinfo
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : resetButtonCitieMap																		    	  */
	/* ROLE : reset de l'affichage On des boutons citieMap													      */
	/* INPUT : struct Sysinfo& : structure globale du programme												      */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void resetButtonCitieMap(Sysinfo& sysinfo);
	
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : inspect																					    	  */
	/* ROLE : Inspect les cases survolées par la souris par la SDL_MOUSE_MOTION								      */
	/* ROLE : Attention fonction appélée à chaque actions de la souris (potentiellement toutes les frames)	      */
	/* INPUT : struct Sysinfo& : structure globale du programme												      */
	/* INPUT : SDL_Event : l'évenement du clique			    												  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void inspect
	(
		Sysinfo& sysinfo,
		SDL_Event event
	);



public:
	/* *********************************************************
	 *				KeyboardMouse::METHODS			  		   *
	 ********************************************************* */


	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : KeyboardMouse																				    	  */
	/* ROLE : Constructeur par défaut de la classe KeyboardMouse											      */
	/* INPUT : void																							      */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	KeyboardMouse();

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : ~KeyboardMouse																			    	  */
	/* ROLE : Destructeur par défaut de la classe KeyboardMouse												      */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	~KeyboardMouse() {};

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : refreshMousePos																			    	  */
	/* ROLE : Inspect les cases survolées par la souris par la SDL_MOUSE_MOTION								      */
	/* INPUT : Sint32 x	: position en x de la souris selon SDL												      */
	/* INPUT : Sint32 y	: position en y de la souris selon SDL												      */
	/* INPUT : unsigned int tileSize : taille d'une tile													      */
	/* INPUT : unsigned int screenOffsetXIndexMin : offset en pixel sur l'axe X								      */
	/* INPUT : unsigned int screenOffsetYIndexMin : offset en pixel sur l'axe Y									  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	void refreshMousePos
	(
		Sint32 x,
		Sint32 y,
		unsigned int tileSize,
		unsigned int screenOffsetXIndexMin,
		unsigned int screenOffsetYIndexMin
	);

	
	
public:
	/* *********************************************************
	 *			KeyboardMouse::METHODS::GET/SET				   *
	 ********************************************************* */
	 
	 
	inline unsigned int GETmouse_x()const				{ return _mouse_x; };
	inline unsigned int GETmouse_y()const				{ return _mouse_y; };
	inline unsigned int GETmouse_xNormalized()const		{ return _mouse_xNormalized; };
	inline unsigned int GETmouse_yNormalized()const		{ return _mouse_yNormalized; };
	inline unsigned int GETywheel()const				{ return _ywheel; };
	inline unsigned int GETxwheel()const				{ return _xwheel; };

	inline void SETmouse_x(unsigned int mouse_x)						{ _mouse_x = mouse_x; };
	inline void SETmouse_y(unsigned int mouse_y)						{ _mouse_y = mouse_y; };
	inline void SETmouse_xNormalized(unsigned int mouse_xNormalized)	{ _mouse_xNormalized = mouse_xNormalized; };
	inline void SETmouse_yNormalized(unsigned int mouse_yNormalized)	{ _mouse_yNormalized = mouse_yNormalized; };
	inline void SETywheel(unsigned int ywheel)							{ _ywheel = ywheel; };
	inline void SETxwheel(unsigned int xwheel)							{ _xwheel = xwheel; };
	

private:
	/* *********************************************************
	 *				KeyboardMouse::ATTIBUTS					   *
	 ********************************************************* */

	unsigned int _mouse_x;
	unsigned int _mouse_y;
	unsigned int _mouse_xNormalized;
	unsigned int _mouse_yNormalized;
	unsigned int _ywheel;
	unsigned int _xwheel;
};

#endif /* KeyboardMouse_H */


/*
*	End Of File : KeyboardMouse.h
*/
