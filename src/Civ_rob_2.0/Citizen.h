/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.20.4.5
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

#ifndef Citizen_H
#define Citizen_H

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"

/* *********************************************************
 *					 Constantes							   *
 ********************************************************* */

/* N/A */

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
	ecstatic	=	2,
	happy		=	1,
	neutre		=	0,
	sad			=  -1,
	angry		=  -2
};

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */

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
	virtual ~Citizen();


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
		std::unordered_map<std::string, Texture*>& citieMap,
		unsigned int x,
		unsigned int y
	);



public:
	/* *********************************************************
	 *				Citizen::METHODS::GET/SET				   *
	 ********************************************************* */

	inline void SETtileOccupied(unsigned int tileOccupied) { _tileOccupied = tileOccupied; };
	inline void SEThappiness(Emotion_Type happiness) { _happiness = happiness; };
	inline void SETfood(int food) { _food = food; };
	inline void SETwork(int work) { _work = work; };
	inline void SETgold(int gold) { _gold = gold; };
	inline void SETrevolt(int revolt) { _revolt = revolt; };
	inline void SETreligion(Religion_Type religion) { _religion = religion; };
	inline void SETplace(bool place) { _place = place; };

	inline unsigned int GETtileOccupied()const { return _tileOccupied; };
	inline Emotion_Type GEThappiness()const { return _happiness; };
	inline int GETfood()const { return _food; };
	inline int GETwork()const { return _work; };
	inline int GETgold()const { return _gold; };
	inline int GETrevolt()const { return _revolt; };
	inline Religion_Type GETreligion()const { return _religion; };
	inline bool GETplace()const { return _place; };

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

#endif /* Citizen_H */

/*
*	End Of File : Citizen.h
*/