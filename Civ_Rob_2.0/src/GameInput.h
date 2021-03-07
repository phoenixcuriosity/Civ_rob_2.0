/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.2.0
	file version : 1.1

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

#ifndef GameInput_H
#define GameInput_H

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"

class MainGame;

 /* *********************************************************
  *						Constantes						   *
  ********************************************************* */

  /* SDL : Define the number of mouse click ONE */
const int ONE_CLICK = 1;

/* SDL : Define the number of mouse clicks TWO */
const int TWO_CLICKS = 2;

/* SDL : Define if the wheel scroll up */
const int MOUSE_SCROLL_UP = 1;

/* SDL : Define if the wheel scroll down */
const int MOUSE_SCROLL_DOWN = - 1;


const float KEY_SPEED_MOVE = 2.0f;
const float MOUSE_SCROLL_SPEED_PERC = 0.25f;

/* *********************************************************
 *						 Enum							   *
 ********************************************************* */

 /* Define input from keyboard in a context */
enum class CinState_Type : unsigned int
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

class GameInput
{
public:
	/* *********************************************************
	 *					KeyboardMouse STATIC				   *
	 ********************************************************* */

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : run_SDL																					    	  */
	/* ROLE : Recherche infini des �venements d'entr� de type SDL_event : souris, clavier					      */
	/* ROLE : Si aucun �venements n'est trouv� alors le programme continue									      */
	/* INPUT : struct Sysinfo& : structure globale du programme									    			  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void inputSDL
	(
		MainGame& mainGame
	);


public:
	/* *********************************************************
	 *			KeyboardMouse::STATIC::UNE TOUCHE			   *
	 ********************************************************* */

	static void keySDLK_ESCAPE();
	


public:
	/* *********************************************************
	 *			KeyboardMouse::STATIC::SOURIS				   *
	 ********************************************************* */


	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : mouse																						    	  */
	/* ROLE : Dispatch entre clique droit ou clique gauche													      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
	/* INPUT : SDL_Event : l'�venement du clique			    												  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void mouse
	(
		MainGame& mainGame
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : cliqueGauche																				    	  */
	/* ROLE : Recherche de la zone ou le clique � lieu sur chaque case de STATE								      */
	/* ROLE : En fonction de la zone touch�e une action peut avoir lieu (boutons)							      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme											  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void cliqueGauche
	(
		MainGame& mainGame
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : cliqueDroit																				    	  */
	/* ROLE : Recherche de la zone ou le clique � lieu														      */
	/* ROLE : En fonction de la zone touch�e une action peut avoir lieu (boutons)							      */
	/* INPUT : struct Sysinfo& : structure globale du programme													  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void cliqueDroit
	(
		MainGame& mainGame
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : wheel																						    	  */
	/* ROLE : Recherche l'incr�mentation ou d�cr�mentation du contexte										      */
	/* INPUT : struct Sysinfo& : structure globale du programme												      */
	/* INPUT : int& wheel : l'�venement de scroll de la souris													  */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void wheel
	(
		MainGame& mainGame
	);



public:
	/* *********************************************************
	 *				KeyboardMouse::METHODS			  		   *
	 ********************************************************* */


	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : KeyboardMouse																				    	  */
	/* ROLE : Constructeur par d�faut de la classe KeyboardMouse											      */
	/* INPUT : void																							      */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	GameInput();

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : ~KeyboardMouse																			    	  */
	/* ROLE : Destructeur par d�faut de la classe KeyboardMouse												      */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	~GameInput() {};

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : refreshMousePos																			    	  */
	/* ROLE : Inspect les cases survol�es par la souris par la SDL_MOUSE_MOTION								      */
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
		int x,
		int y,
		unsigned int tileSize,
		unsigned int screenOffsetXIndexMin,
		unsigned int screenOffsetYIndexMin
	);



public:
	/* *********************************************************
	 *			KeyboardMouse::METHODS::GET/SET				   *
	 ********************************************************* */


	inline unsigned int GETmouse_x()const { return _mouse_x; };
	inline unsigned int GETmouse_y()const { return _mouse_y; };
	inline unsigned int GETmouse_xNormalized()const { return _mouse_xNormalized; };
	inline unsigned int GETmouse_yNormalized()const { return _mouse_yNormalized; };
	inline unsigned int GETywheel()const { return _ywheel; };
	inline unsigned int GETxwheel()const { return _xwheel; };

	inline void SETmouse_x(unsigned int mouse_x) { _mouse_x = mouse_x; };
	inline void SETmouse_y(unsigned int mouse_y) { _mouse_y = mouse_y; };
	inline void SETmouse_xNormalized(unsigned int mouse_xNormalized) { _mouse_xNormalized = mouse_xNormalized; };
	inline void SETmouse_yNormalized(unsigned int mouse_yNormalized) { _mouse_yNormalized = mouse_yNormalized; };
	inline void SETywheel(unsigned int ywheel) { _ywheel = ywheel; };
	inline void SETxwheel(unsigned int xwheel) { _xwheel = xwheel; };


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

#endif /* GameInput_H */


/*
*	End Of File : GameInput.h
*/
