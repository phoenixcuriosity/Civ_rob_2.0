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

#ifndef IHM_H
#define IHM_H

#include "LIB.h"
#include "Player.h"

class IHM
{
public:
	static void inittile(Sysinfo&);
	static void initfile(Sysinfo&);
	static void logfileconsole(const std::string msg);
	static void logSDLError(std::ostream &os, const std::string &msg);
	static bool initsdl(SDL_Window*&, SDL_Renderer*&, TTF_Font*[]);



	static void calculimage(Sysinfo&);

	static void eventSDL(Sysinfo& sysinfo);

	static void titleScreen(Sysinfo&);
	static void reloadScreen(Sysinfo& sysinfo);
	static void changeScreenOffset(Sysinfo& sysinfo);
	static void alwaysrender(Sysinfo&);
	static void afficherSupertiles(Sysinfo&);
	static void citiemap(Sysinfo&);

	static void deleteAll(Sysinfo&);
};
template<class T>
void deleteDyTabPlayerAndTextures(T& dytab, const std::string& name)
{
	unsigned int size = dytab.size();
	for (unsigned int i = 0; i < size; i++)
	{
		if (dytab[i] != nullptr)
		{
			IHM::logfileconsole("Delete " + name + " name = " + dytab[i]->GETname() + " Success");
			delete dytab[i];
		}
	}
	for (unsigned int i = 0; i < size; i++)
		dytab.pop_back();
	if (dytab.size() != 0)
		IHM::logfileconsole("___________ERROR : " + name + ".size() != 0");
	else
		IHM::logfileconsole("Delete ALL " + name + " Success");
}


#endif

/*
*	End Of File
*/
