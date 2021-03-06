/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.22.0.0
	file version : 1.5

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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"

#include "City.h"
#include "Citizen.h"

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

#define NO_CURRENT_SAVE_SELECTED -1

/* *********************************************************
 *						 Enum							   *
 ********************************************************* */

/* N/A */

/* *********************************************************
 *						Structures						   *
 ********************************************************* */

/* N/A */

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */

class SaveReload
{
public:
	/* *********************************************************
	 *					SaveReload::STATIC					   *
	 ********************************************************* */

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : reload																					    	  */
	/* ROLE : Chargement de la partie � patir des fichiers de sauvegarde									      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void save
	(
		Sysinfo&
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : savemaps																					    	  */
	/* ROLE : Sauvegardes des sys map.map et map.screen														      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
	/* RETURNED VALUE    : void																	    			  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void saveMaps
	(
		Sysinfo&
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : savePlayer																				    	  */
	/* ROLE : Sauvegarde des joueurs (units et cities) dans SavePlayer.txt									      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
	/* RETURNED VALUE    : void 																				  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void savePlayer
	(
		Sysinfo&
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : reload																					    	  */
	/* ROLE : Chargement de la partie � patir des fichiers de sauvegarde									      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void reload
	(
		Sysinfo&
	);


	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : loadMaps																					    	  */
	/* ROLE : Chargement des sys map.map et map.screen														      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
	/* RETURNED VALUE    : void								    												  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void loadMaps
	(
		Sysinfo&
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : loadPlayer																				    	  */
	/* ROLE : Chargement des joueurs (units et cities) dans SavePlayer.txt									      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void loadPlayer
	(
		Sysinfo&
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
	/* INPUT/OUTPUT : Sysinfo& sysinfo : General struct							 							      */
	/* INPUT/OUTPUT : tinyxml2::XMLNode* nUnit : Ptr on the Unit node in the XML document					      */
	/* RETURNED VALUE    : void								    												  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void loadUnitXML
	(
		Sysinfo& sysinfo,
		tinyxml2::XMLNode* nUnit
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : loadCityXML																				    	  */
	/* ROLE : Load City reference to Player																	      */
	/* ROLE : While Loop : load all Cities to a Player														      */
	/* INPUT/OUTPUT : Sysinfo& sysinfo : General struct							 							      */
	/* INPUT/OUTPUT : tinyxml2::XMLNode* nCity : Ptr on the City node in the XML document					      */
	/* RETURNED VALUE    : void								    												  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void loadCityXML
	(
		Sysinfo& sysinfo,
		tinyxml2::XMLNode* nCity
	);
	
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : createSave																				    	  */
	/* ROLE : Cr�ation d'un emplacement de fichier de sauvegarde (courant)									      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void createSave
	(
		Sysinfo& sysinfo
	);
	
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : removeSave																				    	  */
	/* ROLE : Supprime une sauvegarde du dossier de sauvegarde												      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void removeSave
	(
		Sysinfo& sysinfo
	);
	
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : clearSave																					    	  */
	/* ROLE : Supprime toutes les sauvegardes du dossier													      */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme										      */
	/* RETURNED VALUE    : void																					  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static void clearSave
	(
		Sysinfo& sysinfo
	);

	

public:
	/* *********************************************************
	 *				SaveReload::METHODS						   *
	 ********************************************************* */

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : SaveReload																				    	  */
	/* ROLE : Constructeur par d�faut																		      */
	/* INPUT : void																							      */
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
	
public:
	/* *********************************************************
	 *			SaveReload::METHODS::GET/SET				   *
	 ********************************************************* */

	inline std::vector<unsigned int>& GETtabSave() 		{ return _tabSave;}; 
	inline int GETcurrentSave()const					{ return _currentSave;}; 
	inline unsigned int GETnbSave()const				{ return _nbSave;}; 

	inline void SETtabSave(std::vector<unsigned int>& tab) 	{_tabSave = tab;};
	inline void SETcurrentSave(int currentSave)	{_currentSave = currentSave;};
	inline void SETnbSave(unsigned int nbSave)				{_nbSave = nbSave;};
	

	
private:
	/* *********************************************************
	 *				SaveReload::ATTRIBUTS					   *
	 ********************************************************* */
	 
	 
	std::vector<unsigned int> _tabSave;
	int _currentSave;
	unsigned int _nbSave;
};


#endif /* SaveReload_H */

/*
*	End Of File : SaveReload.h
*/