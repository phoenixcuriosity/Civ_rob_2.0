/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.17
	file version : 1.3

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

#include "civ_lib.h"
#include "Player.h"


/* *********************************************************
 *					 Constantes							   *
 ********************************************************* */

  
  
// taille de la carte transposée dans la citiemap
const int initSizeView = 7;

// taille de l'influence de la citie initialement
const int initSizeInfluence = 2;

const unsigned int MAX_POP = 50;




/* *********************************************************
 *						 Classes						   *
 ********************************************************* */
  
class City
{
public:
	/* *********************************************************
	 *					City::STATIC						   *
	 ********************************************************* */
	
	
	/*
	 * NAME : createCity
	 * ROLE : Création d'une City à partir d'un settler sur la carte
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : Création d'une City
	 * RETURNED VALUE    : void
	 */
	static void createCity(Sysinfo& sysinfo);
	
		
	/*
	 * NAME : searchCityTile
	 * ROLE : Recherche la case de la City et renvoie vers cityMap
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : la case de la City et renvoie vers cityMap
	 * RETURNED VALUE    : void
	 */
	static void searchCityTile(Sysinfo& sysinfo);
	
		
	/*
	 * NAME : createTiles
	 * ROLE : Création d'un tableau de Tile pour la City
	 * INPUT  PARAMETERS : Tile tile[] : données générale de la map
	 * OUTPUT PARAMETERS : std::vector<Tile>
	 * RETURNED VALUE    : std::vector<Tile> : données générale de la cityMap
	 */
	static std::vector<Tile> createTiles(Tile tile[]);
	
		
	/*
	 * NAME : createCitizen
	 * ROLE : Création d'un Citizen sur une case précise
	 * INPUT  PARAMETERS : Tile tile : données d'une case
	 * OUTPUT PARAMETERS : std::vector<Citizen>
	 * RETURNED VALUE    : std::vector<Citizen> : ajout du Citizen
	 */
	static std::vector<Citizen> createCitizen(Tile tile);

	
public:
	/* *********************************************************
	 *					City::METHODS						   *
	 ********************************************************* */
	 
	
	//City() {}; // garder le constructeur par défaut
	City(const std::string &, unsigned int, unsigned int, Tile[]);
	~City();

		
	/*
	 * NAME : foodNextTurn
	 * ROLE : Calcul et application du niveau de Food pour le prochain tour
	 * INPUT  PARAMETERS : void
	 * OUTPUT PARAMETERS : Calcul et application du niveau de Food
	 * RETURNED VALUE    : void
	 */
	virtual void foodNextTurn();

		
	/*
	 * NAME : testPos
	 * ROLE : Retourne si la position est valide
	 * INPUT  PARAMETERS : unsigned int x, unsigned int y : position de la souris
	 * OUTPUT PARAMETERS : Retourne si la position est valide
	 * RETURNED VALUE    : int : 0 : pas valide / 1 : valide
	 */
	virtual int testPos(unsigned int x, unsigned int y);


public:
	/* *********************************************************
	 *				City::METHODS::Affichage				   *
	 ********************************************************* */
	 
		
	/*
	 * NAME : afficher
	 * ROLE : Affichage de la City (Texture et nom)
	 * INPUT  PARAMETERS : truct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : Affichage de la City (Texture et nom)
	 * RETURNED VALUE    : void
	 */
	virtual void afficher(Sysinfo&);
	
		
	/*
	 * NAME : affichercitiemap
	 * ROLE : Affichage des cases qui compose le secteur de la City
	 * INPUT  PARAMETERS : truct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : Affichage des cases de la City
	 * RETURNED VALUE    : void
	 */
	virtual void affichercitiemap(Sysinfo&);
	 
	
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
	std::vector<Citizen> _citizens;
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


enum class Religion_Type : Uint8	{
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

enum class Emotion_Type : int8_t{
									ecstatic	=  2,
									happy		=  1,
									neutre		=  0,
									sad			= -1,
									angry		= -2
								};

class Citizen
{
public:
	/* *********************************************************
	 *					Citizen::STATIC						   *
	 ********************************************************* */
	 
	
	/*
	 * NAME : placeCitizen
	 * ROLE : Placement d'un Citizen en fonction des cases occupées de la City
	 * INPUT  PARAMETERS : std::vector<Tile> : carte de la City
	 * INPUT  PARAMETERS : std::vector<Citizen> : tableau de Citizen
	 * INPUT  PARAMETERS : int& _food, int& _work, int& _gold : spec de la case
	 * OUTPUT PARAMETERS : Placement d'un Citizen
	 * RETURNED VALUE    : unsigned int : la place allouée
	 */
	static unsigned int placeCitizen(std::vector<Tile> tile,
		std::vector<Citizen> citizens, int& _food, int& _work, int& _gold);
		
	 
	/* *********************************************************
	 *					Citizen::METHODS					   *
	 ********************************************************* */
	Citizen();
	Citizen(Tile tiles);
	Citizen(std::vector<Tile> tile, std::vector<Citizen> citizens);
	~Citizen();

	
		
	/*
	 * NAME : placeCitizenWithMouse
	 * ROLE : TODO
	 * INPUT  PARAMETERS : void 
	 * OUTPUT PARAMETERS : 
	 * RETURNED VALUE    : void
	 */
	virtual void placeCitizenWithMouse();

	/*
	 * NAME : afficher
	 * ROLE : affichage du citizen sur la case de la citie map
	 * INPUT  PARAMETERS : void
	 * OUTPUT PARAMETERS : affichage sur la map
	 * RETURNED VALUE    : void
	 */
	virtual void afficher(std::unordered_map<std::string, Texture*>& citieMap, unsigned int x, unsigned int y);



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