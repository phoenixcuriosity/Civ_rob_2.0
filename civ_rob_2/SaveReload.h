/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.14
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

#ifndef SaveReload_H
#define SaveReload_H

#include "LIB.h"

class SaveReload
{
public:
	/* *********************************************************
		*					STATIC
	 ********************************************************* */


	/*
	* NAME : savemaps
	* ROLE : Sauvegardes des sys map.map et map.screen
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : Sauvegardes des maps : map.map dans SaveMap.txt
	* OUTPUT PARAMETERS : et map.screen dans SaveScreen.txt
	* RETURNED VALUE    : void
	*/
	static void savemaps(Sysinfo&);

	/*
	* NAME : savePlayer
	* ROLE : Sauvegarde des joueurs (units et cities)
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : Sauvegarde des joueurs (units et cities) dans SavePlayer.txt
	* RETURNED VALUE    : void
	*/
	static void savePlayer(Sysinfo&);

	/*
	* NAME : reload
	* ROLE : Chargement de la partie à patir des fichiers de sauvegarde
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : Chargement de la partie
	* RETURNED VALUE    : void
	*/
	static void reload(Sysinfo&);
	
	/*
	* NAME : createSave
	* ROLE : Création d'un emplacement de fichier de sauvegarde (courant)
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : Création d'un emplacement de fichier de sauvegarde
	* RETURNED VALUE    : void
	*/
	static void createSave(Sysinfo& sysinfo);
	
	/*
	* NAME : removeSave
	* ROLE : Supprime une sauvegarde du dossier de sauvegarde
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : Supprime une sauvegarde
	* RETURNED VALUE    : void
	*/
	static void removeSave(Sysinfo& sysinfo);
	
	/*
	* NAME : clearSave
	* ROLE : Supprime toutes les sauvegardes du dossier
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : Supprime toutes les sauvegardes du dossier
	* RETURNED VALUE    : void
	*/
	static void clearSave(Sysinfo& sysinfo);



public:
	/* *********************************************************
		*					CLASSE
	 ********************************************************* */

	SaveReload();
	~SaveReload();

	std::vector<unsigned int>& GETtabSave(); // attention n'est pas const
	unsigned int GETcurrentSave()const;
	unsigned int GETnbSave()const;

	void SETtabSave(std::vector<unsigned int>& tab);
	void SETcurrentSave(unsigned int currentSave);
	void SETnbSave(unsigned int nbSave);

private:
	std::vector<unsigned int> _tabSave;
	unsigned int _currentSave;
	unsigned int _nbSave;
};



#endif

/*
*	End Of File
*/