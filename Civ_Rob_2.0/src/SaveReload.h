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

#include <tinyxml2/tinyxml2.h>

class SaveReload
{
public:

	void init(const std::string& filePath);

	 /* ---------------------------------------------------------------------------------------------------------- */
	 /* ---------------------------------------------------------------------------------------------------------- */
	 /* NAME : reload																					    	   */
	 /* ROLE : Chargement de la partie � patir des fichiers de sauvegarde									       */
	 /* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							       */
	 /* RETURNED VALUE    : void																				   */
	 /* ---------------------------------------------------------------------------------------------------------- */
	 /* ---------------------------------------------------------------------------------------------------------- */
	static void save
	(
		GamePlayScreen& mainGame
	);

private:
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : savemaps																					    	  */
	/* ROLE : Sauvegardes des sys map.map et map.screen														      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void																	    			  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void saveMaps
	(
		GamePlayScreen& mainGame
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : savePlayer																				    	  */
	/* ROLE : Sauvegarde des joueurs (units et cities) dans SavePlayer.txt									      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void 																				  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void savePlayer
	(
		GamePlayScreen& mainGame
	);

public:
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : reload																					    	  */
	/* ROLE : Chargement de la partie � patir des fichiers de sauvegarde									      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void reload
	(
		GamePlayScreen& mainGame
	);

private:
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : loadMaps																					    	  */
	/* ROLE : Chargement des sys map.map et map.screen														      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void								    												  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void loadMaps
	(
		GamePlayScreen& mainGame
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : loadPlayer																				    	  */
	/* ROLE : Chargement des joueurs (units et cities) dans SavePlayer.txt									      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void loadPlayer
	(
		GamePlayScreen& mainGame
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : loadGoldStatsXML																			    	  */
	/* ROLE : Load Gold Stats reference to Player															      */
	/* ROLE : Player->GETgoldStats() should be used instead of Player->GETgoldStatsConst()						  */
	/* ROLE : Data type : double ; use std::stod															      */
	/* INPUT/OUTPUT : GoldStats& goldStats : Structure of the Player's gold stats 							      */
	/* INPUT/OUTPUT : tinyxml2::XMLNode* nGoldStats : Ptr on the GoldStats node in the XML document			      */
	/* RETURNED VALUE    : void								    												  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void loadGoldStatsXML
	(
		GoldStats& goldStats,
		tinyxml2::XMLNode* nGoldStats
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : loadUnitXML																				    	  */
	/* ROLE : Load Unit reference to Player																	      */
	/* ROLE : While Loop : load all Units to a Player														      */
	/* INPUT/OUTPUT : MainGame& mainGame sysinfo : General struct							 				      */
	/* INPUT/OUTPUT : tinyxml2::XMLNode* nUnit : Ptr on the Unit node in the XML document					      */
	/* RETURNED VALUE    : void								    												  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void loadUnitXML
	(
		GamePlayScreen& mainGame,
		tinyxml2::XMLNode* nUnit
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : loadCityXML																				    	  */
	/* ROLE : Load City reference to Player																	      */
	/* ROLE : While Loop : load all Cities to a Player														      */
	/* INPUT/OUTPUT : MainGame& mainGame sysinfo : General struct							 				      */
	/* INPUT/OUTPUT : tinyxml2::XMLNode* nCity : Ptr on the City node in the XML document					      */
	/* RETURNED VALUE    : void								    												  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void loadCityXML
	(
		GamePlayScreen& mainGame,
		tinyxml2::XMLNode* nCity
	);

public:

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : createSave																				    	  */
	/* ROLE : Cr�ation d'un emplacement de fichier de sauvegarde (courant)									      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	void createSave();

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : removeSave																				    	  */
	/* ROLE : Supprime une sauvegarde du dossier de sauvegarde												      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	void removeSave();

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : clearSave																					    	  */
	/* ROLE : Supprime toutes les sauvegardes du dossier													      */
	/* INPUT/OUTPUT : struct MainGame& mainGame : structure globale du programme							      */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	void clearSave();



public:

	 /* ---------------------------------------------------------------------------------------------------------- */
	 /* ---------------------------------------------------------------------------------------------------------- */
	 /* NAME : SaveReload																				    	   */
	 /* ROLE : Constructeur par d�faut																		       */
	 /* INPUT : void																							   */
	 /* ---------------------------------------------------------------------------------------------------------- */
	 /* ---------------------------------------------------------------------------------------------------------- */
	SaveReload();

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : ~SaveReload																				    	  */
	/* ROLE : Destructeur par d�faut																		      */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	~SaveReload();

private:

	void removeSaveDir(const size_t index);

	void removeSaveFile(const std::string& file);

	void unselectCurrentSave();

	bool isSelectCurrentSave();

	bool isSelectCurrentSaveInTab();

	void rewriteSaveInfoFile();

public:

	inline std::vector<unsigned int>& GETtabSave() { return m_tabSave; };
	inline int GETcurrentSave()const { return m_currentSave; };

	inline void SETtabSave(std::vector<unsigned int>& tab) { m_tabSave = tab; };
	inline void SETcurrentSave(int currentSave) { m_currentSave = currentSave; };



private:

	R2D::VectID m_tabSave;
	int m_currentSave;
};


#endif /* SaveReload_H */

/*
*	End Of File : SaveReload.h
*/
