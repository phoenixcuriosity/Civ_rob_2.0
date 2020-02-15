/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

/* N/A */

/* *********************************************************
 *						  Classe						   *
 ********************************************************* */

class End
{
public:

	/* *********************************************************
	 *						  STATIC						   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initPtrSysinfoLogger														   */
	/* ROLE : Initialisation des ptr sysinfo et logger									   */
	/* INPUT : Sysinfo& sysinfo: structure globale du programme							   */
	/* INPUT : std::ofstream& logger : fichier log										   */
	/* RETURNED VALUE : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void initPtrSysinfoLogger
	(
		Sysinfo& sysinfo,
		std::ofstream& logger
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : exitError																	   */
	/* ROLE : Enregistre l'erreur survenue et termine le programme de façon sécurisée	   */
	/* INPUT : const std::string msg : message de l'erreur								   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void exitError
	(
		const std::string msg
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deleteAll																	   */
	/* ROLE : Destruction des allocations dynamique du programme						   */
	/* ROLE : Destruction de la fenetre et du Renderer de la SDL						   */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void deleteAll
	(
		Sysinfo&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deleteTexture																   */
	/* ROLE : Destruction des allocations dynamiques de la unordered_map				   */
	/* INPUT/OUTPUT : std::unordered_map<std::string, Texture*>& unmap : map Texture	   */
	/* INPUT : const std::string name : name de la Texture								   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void deleteTexture
	(
		std::unordered_map<std::string, Texture*>& unmap,
		const std::string& name
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deleteTexte																   */
	/* ROLE : Destruction des allocations dynamiques de la unordered_map				   */
	/* INPUT/OUTPUT : std::unordered_map<std::string, Texture*>& unmap : map Texte		   */
	/* INPUT : const std::string name : name de la Texture								   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void deleteTexte
	(
		std::unordered_map<std::string, Texte*>& unmap,
		const std::string& name
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deleteButtonTexte															   */
	/* ROLE : Destruction des allocations dynamiques de la unordered_map				   */
	/* INPUT/OUTPUT : std::unordered_map<std::string, ButtonTexte*>& unmap: map ButtonTexte*/
	/* INPUT : const std::string name : name de la Texture								   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void deleteButtonTexte
	(
		std::unordered_map<std::string, ButtonTexte*>& unmap,
		const std::string& name
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deletePlayer																   */
	/* ROLE : Destruction des allocations dynamiques du vecteur							   */
	/* INPUT/OUTPUT : std::vector<Player*>& vect : vecteur de joueurs					   */
	/* INPUT : const std::string name : name de la Texture								   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void deletePlayer
	(
		std::vector<Player*>& vect,
		const std::string& name
	);
};

#endif //End_H

/*
*	End Of File : End.h
*/
