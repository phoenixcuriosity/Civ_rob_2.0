/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.14
	file version : 1.0

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
	static void cinDigit(Sysinfo&, unsigned int&, unsigned int, unsigned int&);
	static void cinAlphabet(Sysinfo&, std::string&, unsigned int, unsigned int&);

	static void keySDLK_b(Sysinfo&);
	static void keySDLK_i(Sysinfo&);

	static void keySDLK_KP_1(Sysinfo&);
	static void keySDLK_KP_2(Sysinfo&);
	static void keySDLK_KP_3(Sysinfo&);
	static void keySDLK_KP_4(Sysinfo&);
	static void keySDLK_KP_5(Sysinfo&);
	static void keySDLK_KP_6(Sysinfo&);
	static void keySDLK_KP_7(Sysinfo&);
	static void keySDLK_KP_8(Sysinfo&);
	static void keySDLK_KP_9(Sysinfo&);

	static void mouse(Sysinfo&, SDL_Event);
	static void cliqueGauche(Sysinfo&, SDL_Event);
	static void cliqueDroit(Sysinfo&, SDL_Event);
	static void wheel(Sysinfo&, int&);

	KeyboardMouse();
	~KeyboardMouse() {};

	unsigned int GETmouse_x()const;
	unsigned int GETmouse_y()const;
	unsigned int GETywheel()const;
	unsigned int GETxwheel()const;

	void SETmouse_x(unsigned int mouse_x);
	void SETmouse_y(unsigned int mouse_y);
	void SETywheel(unsigned int ywheel);
	void SETxwheel(unsigned int xwheel);

private:
	unsigned int _mouse_x;
	unsigned int _mouse_y;
	unsigned int _ywheel;
	unsigned int _xwheel;
};

#endif


/*
*	End Of File
*/
