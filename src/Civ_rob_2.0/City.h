/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.18
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

#ifndef City_H
#define City_H

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "civ_lib.h"
#include "Player.h"

/* *********************************************************
 *					 Constantes							   *
 ********************************************************* */

/* taille de la carte transposée dans la citiemap */
const Uint8 INIT_SIZE_VIEW = 7;

/* taille de l'influence de la citie initialement */
const Uint8 INIT_SIZE_INFLUENCE = 2;

/* Population maximale dans une Citie */
const Uint8 MAX_POP = 50;

/* Todo : généralisation : compter nb Citie par player dans CITIENAME.txt */

/* Nombre de noms de Citie dans CITIENAME.txt */
const Uint8 MAX_CITY_PER_PLAYER = 5;

/* *********************************************************
 *						 Structs						   *
 ********************************************************* */

/* N/A */

/* *********************************************************
 *							 Enum						   *
 ********************************************************* */

enum class Religion_Type : Uint8
{
	catholic,
	protestant,
	reformed,
	anglican,
	orthodox,
	coptic,
	sunni,
	shiite,
	ibadi,
	buddhism,
	vajrayana,
	mahayana,
	confucianism,
	shinto,
	hinduism,
	sikhism,
	animism,
	shamanism,
	totemism,
	inti,
	nahuatl,
	jewish,
	zoroastrian
};

enum class Emotion_Type : int8_t
{
	ecstatic =	2,
	happy	 =	1,
	neutre	 =	0,
	sad		 = -1,
	angry	 = -2
};

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */
  
class City
{
public:
	/* *********************************************************
	 *					City::STATIC						   *
	 ********************************************************* */
	

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : createCity																   */
	/* ROLE : Création d'une City à partir d'un settler sur la carte					   */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	static void createCity
	(
		Sysinfo& sysinfo
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initSizeInfluenceCondition												   */
	/* ROLE : Conditions des cases de la ville à l'intérieur de zone d'influence		   */
	/* INPUT : unsigned int o :	index en x												   */
	/* INPUT : unsigned int p :	index en y												   */
	/* RETURNED VALUE : bool : false -> invalid / true -> valid							   */
	/* ----------------------------------------------------------------------------------- */
	static bool initSizeInfluenceCondition
	(
		unsigned int o,
		unsigned int p
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : searchCityTile															   */
	/* ROLE : Recherche la case de la City et renvoie vers cityMap						   */
	/* INPUT : const std::vector<Player*>& : Vecteur de joueurs							   */
	/* INPUT/OUTPUT : Var& : Structure Var												   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	static void searchCityTile
	(
		const std::vector<Player*>& tabplayer,
		Var& var
	);
	
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : createTiles																   */
	/* ROLE : Création d'un tableau de Tile pour la City								   */
	/* INPUT : Tile tile[] : données générale de la map									   */
	/* RETURNED VALUE : std::vector<Tile> : données générale de la cityMap				   */
	/* ----------------------------------------------------------------------------------- */
	static std::vector<Tile> createTiles
	(
		Tile tile[]
	);

	
public:
	/* *********************************************************
	 *					City::METHODS						   *
	 ********************************************************* */
	 

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : City																		   */
	/* ROLE : Constructeur complet														   */
	/* INPUT : const std::string &	: name de la Citie									   */
	/* INPUT : unsigned int x : index en x												   */
	/* INPUT : unsigned int y : index en y												   */
	/* INPUT : Tile tile[] : tableau de tile de la Citie								   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	City
	(
		const std::string &,
		unsigned int x,
		unsigned int y,
		Tile tile[]
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : ~City																		   */
	/* ROLE : Destructeur																   */
	/* INPUT : void																		   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	~City();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : foodNextTurn																   */
	/* ROLE : Calcul et application du niveau de Food pour le prochain tour				   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void foodNextTurn();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : testPos																	   */
	/* ROLE : Retourne si la position est valide										   */
	/* INPUT : unsigned int x : position de la souris en x								   */
	/* INPUT : unsigned int y : position de la souris en y								   */
	/* RETURNED VALUE : bool : false : invalid / true : valid							   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual bool testPos
	(
		unsigned int x,
		unsigned int y
	);


public:
	/* *********************************************************
	 *				City::METHODS::Affichage				   *
	 ********************************************************* */
	 

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : afficher																	   */
	/* ROLE : Affichage de la City (Texture et nom)										   */
	/* INPUT : truct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void afficher
	(
		Sysinfo&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : affichercitiemap															   */
	/* ROLE : Affichage des cases qui compose le secteur de la City						   */
	/* INPUT : truct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void affichercitiemap
	(
		Sysinfo&
	);
	 
	
public:
	/* *********************************************************
	 *				City::METHODS::GET/SET					   *
	 ********************************************************* */

	inline virtual unsigned int GETx()const { return _x; };
	inline virtual unsigned int GETy()const { return _y; };

	
private:
	/* *********************************************************
	 *					City::ATTRIBUTS						   *
	 ********************************************************* */
	 
	std::string _image;
	std::string _name;
	unsigned int _x;
	unsigned int _y;
	std::vector<Tile> _tile;
	std::vector<Citizen*> _citizens;
	unsigned int _influenceLevel;
	unsigned int _nbpop;
	unsigned int _atq;
	unsigned int _def;
	unsigned int _nbhappy;
	unsigned int _nbsad;
	unsigned int _nbstructurebuild;

	double _foodStock;
	double _foodBalance;
};



class Citizen
{
public:
	/* *********************************************************
	 *					Citizen::STATIC						   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : placeCitizen																   */
	/* ROLE : Placement d'un Citizen en fonction des cases occupées de la City			   */
	/* INPUT : std::vector<Tile> : carte de la City										   */
	/* INPUT : std::vector<Citizen> : tableau de Citizen								   */
	/* INPUT : int& _food, int& _work, int& _gold : spec de la case						   */
	/* RETURNED VALUE    : unsigned int : la place allouée								   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static unsigned int placeCitizen
	(
		std::vector<Tile>& tile,
		std::vector<Citizen*>& citizens,
		int& _food,
		int& _work,
		int& _gold
	);
		
	 
	/* *********************************************************
	 *					Citizen::METHODS					   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Citizen																	   */
	/* ROLE : Constructeur par défaut													   */
	/* INPUT : void																		   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	Citizen();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Citizen																	   */
	/* ROLE : Constructeur par une Tile													   */
	/* INPUT : Tile tile : tile centrale de la Citie									   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	Citizen
	(
		Tile tile
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Citizen																	   */
	/* ROLE : Constructeur par une Tile													   */
	/* INPUT : std::vector<Tile>& tile : tableau de Tile de la Citie					   */
	/* INPUT : std::vector<Citizen*>& citizens : tableau de Citizens					   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	Citizen
	(
		std::vector<Tile>& tile,
		std::vector<Citizen*>& citizens
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : ~Citizen																	   */
	/* ROLE : Destructeur																   */
	/* INPUT : void																		   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	~Citizen();

	
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : placeCitizenWithMouse														   */
	/* ROLE : TODO																		   */
	/* INPUT : void 																	   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void placeCitizenWithMouse();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : afficher																	   */
	/* ROLE : affichage du citizen sur la case de la citie map							   */
	/* INPUT : std::unordered_map<std::string,Texture*>& : tableau de Texture de la Citie  */
	/* INPUT : unsigned int x : index en x du Citizen									   */
	/* INPUT : unsigned int y : index en y du Citizen									   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void afficher
	(
		std::unordered_map<std::string,Texture*>& citieMap,
		unsigned int x,
		unsigned int y
	);



public:
	/* *********************************************************
	 *				Citizen::METHODS::GET/SET				   *
	 ********************************************************* */

	inline void SETtileOccupied(unsigned int tileOccupied)		{ _tileOccupied = tileOccupied; };
	inline void SEThappiness(Emotion_Type happiness)			{ _happiness = happiness; };
	inline void SETfood(int food)								{ _food = food; };
	inline void SETwork(int work)								{ _work = work; };
	inline void SETgold(int gold)								{ _gold = gold; };
	inline void SETrevolt(int revolt)							{ _revolt = revolt; };
	inline void SETreligion(Religion_Type religion)				{ _religion = religion; };
	inline void SETplace(bool place)							{ _place = place; };

	inline unsigned int GETtileOccupied()const		{ return _tileOccupied; };
	inline Emotion_Type GEThappiness()const			{ return _happiness; };
	inline int GETfood()const						{ return _food; };
	inline int GETwork()const						{ return _work; };
	inline int GETgold()const						{ return _gold; };
	inline int GETrevolt()const						{ return _revolt; };
	inline Religion_Type GETreligion()const			{ return _religion; };
	inline bool GETplace()const						{ return _place; };

private:
	/* *********************************************************
	 *					Citizen::ATTRIBUTS					   *
	 ********************************************************* */
	 
	unsigned int _tileOccupied;
	Emotion_Type _happiness;
	int _food;
	int _work;
	int _gold;
	int _revolt;
	Religion_Type _religion;

	bool _place;
};

#endif /* City_H */

/*
*	End Of File : City.h
*/