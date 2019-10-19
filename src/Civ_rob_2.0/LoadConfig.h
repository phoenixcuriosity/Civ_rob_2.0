/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.16
	file version : 1.2

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

#ifndef LoadConfig_H
#define LoadConfig_H


#include "LIB.h"

class LoadConfig
{
public:
	/* *********************************************************
	 *					INITIALISATION						   *
	 ********************************************************* */

	 /*
	 * NAME : initStructs
	 * ROLE : Initialisation des données par défaut des structures
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : données par défaut des structures
	 * RETURNED VALUE    : void
	 */
	static void initStructs(Sysinfo& sysinfo);

	/*
	* NAME : initMain
	* ROLE : Chargement des informations de la configuration du jeu
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : configuration du jeu
	* RETURNED VALUE    : void
	*/
	static void initMain(Sysinfo& sysinfo);

	static Uint16 getHorizontal(unsigned int tileSize);

	static Uint16 getVertical(unsigned int tileSize);

private:

};


#endif // !LoadConfig_H


/*
*	End Of File : LoadConfig.h
*/

