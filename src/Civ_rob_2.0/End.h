/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.17
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

#ifndef End_H
#define End_H

#include "LIB.h"
#include "civ_lib.h"

class End
{
public:
	static void initPtrSysinfoLogger(Sysinfo& sysinfo, std::ofstream& logger);


	/*
	 * NAME : exitError
	 * ROLE : Enregistre l'erreur survenue et termine le programme de façon sécurisée
	 * INPUT  PARAMETERS : const std::string msg : message de l'erreur
	 * OUTPUT PARAMETERS : EXIT_FAILURE
	 * RETURNED VALUE    : void
	 */
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

	static void deleteTexture(std::unordered_map<std::string, Texture*>& unmap, const std::string& name);

	static void deleteTexte(std::unordered_map<std::string, Texte*>& unmap, const std::string& name);

	static void deleteButtonTexte(std::unordered_map<std::string, ButtonTexte*>& unmap, const std::string& name);

	static void deletePlayer(std::vector<Player*>& vect, const std::string& name);
};



#endif //End_H




/*
*	End Of File : End.h
*/
