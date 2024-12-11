/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)

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

#include <R2D/src/API_fwd.h>

class SaveReload
{
public:

	void init();

	 /* NAME : reload																					    	   */
	 /* ROLE : Chargement de la partie � patir des fichiers de sauvegarde									       */
	 /* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							       */
	 /* RETURNED VALUE    : void																				   */
	void save
	(
		const MainMap& mainMap,
		const Players& players
	);

private:
	/* NAME : savemaps																					    	  */
	/* ROLE : Sauvegardes des sys map.map et map.screen														      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void																	    			  */
	void saveMaps
	(
		const MainMap& mainMap
	);

	/* NAME : savePlayer																				    	  */
	/* ROLE : Sauvegarde des joueurs (units et cities) dans SavePlayer.txt									      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void 																				  */
	void savePlayer
	(
		const Players& players
	);

public:
	/* NAME : reload																					    	  */
	/* ROLE : Chargement de la partie � patir des fichiers de sauvegarde									      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void																					  */
	void reload
	(
		GamePlayScreen& mainGame
	);

private:
	/* NAME : loadMaps																					    	  */
	/* ROLE : Chargement des sys map.map et map.screen														      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void								    												  */
	void loadMaps
	(
		MainMap& mainMap
	);

	/* NAME : loadPlayer																				    	  */
	/* ROLE : Chargement des joueurs (units et cities) dans SavePlayer.txt									      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void																					  */
	void loadPlayer
	(
	    MatriceMap& matriceMap,
		Players& players
	);

public:

	/* NAME : createSave																				    	  */
	/* ROLE : Cr�ation d'un emplacement de fichier de sauvegarde (courant)									      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void																					  */
	void createSave();

	/* NAME : removeSave																				    	  */
	/* ROLE : Supprime une sauvegarde du dossier de sauvegarde												      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void																					  */
	void removeSave();

	/* NAME : clearSave																					    	  */
	/* ROLE : Supprime toutes les sauvegardes du dossier													      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void																					  */
	void clearSave();

public:

	 /* NAME : SaveReload																				    	   */
	 /* ROLE : Constructeur par d�faut																		       */
	 /* INPUT : void																							   */
	SaveReload();

	/* NAME : ~SaveReload																				    	  */
	/* ROLE : Destructeur par d�faut																		      */
	~SaveReload();

private:

	void createSaveDir();

	void removeSaveDir(const size_t index);

	void removeSaveFile(const std::string& file);

	void removeIndex(const size_t index);

	void unselectCurrentSave();

	bool isSelectCurrentSaveInTab();

public:

	bool isSelectCurrentSave();

public:

	inline std::vector<unsigned int>& GETtabSave() { return m_tabSave; };
	inline int GETcurrentSave()const { return m_currentSave; };

	inline void SETtabSave(std::vector<unsigned int>& tab) { m_tabSave = tab; };
	inline void SETcurrentSave(int currentSave) { m_currentSave = currentSave; };

	inline void resetCurrentSave();

private:

	R2D::VectID m_tabSave;
	int m_currentSave;
};


#endif /* SaveReload_H */

/*
*	End Of File : SaveReload.h
*/
