/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.4.0
	file version : 1.4

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

#include <memory>
#include "MainMap.h"

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

enum class Religion_Type
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

enum class Emotion_Type
{
	ecstatic = 2,
	happy = 1,
	neutral = 0,
	sad = -1,
	angry = -2
};

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */

class Citizen;
typedef std::vector<std::unique_ptr<Citizen>> VectCitizen;

class Citizen
{
public:
	/* *********************************************************
	 *					Citizen::STATIC						   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : placeCitizen																   */
	/* ROLE : Placement d'un Citizen en fonction des cases occup�es de la City			   */
	/* INPUT : std::vector<Tile> : carte de la City										   */
	/* INPUT : std::vector<Citizen> : tableau de Citizen								   */
	/* INPUT : int& m_food, int& m_work, int& m_gold : spec de la case						   */
	/* RETURNED VALUE    : unsigned int : la place allou�e								   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static unsigned int placeCitizen
	(
		VectMap& tile,
		VectCitizen& citizens,
		int& m_food,
		int& m_work,
		int& m_gold
	);


	/* *********************************************************
	 *					Citizen::METHODS					   *
	 ********************************************************* */


	 /* ----------------------------------------------------------------------------------- */
	 /* ----------------------------------------------------------------------------------- */
	 /* NAME : Citizen																	   */
	 /* ROLE : Constructeur par d�faut													   */
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
		VectMap& tile,
		VectCitizen& citizens
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

	);



public:
	/* *********************************************************
	 *				Citizen::METHODS::GET/SET				   *
	 ********************************************************* */

	inline void SETtileOccupied(unsigned int tileOccupied) { m_tileOccupied = tileOccupied; };
	inline void SEThappiness(Emotion_Type happiness) { m_happiness = happiness; };
	inline void SETfood(int food) { m_food = food; };
	inline void SETwork(int work) { m_work = work; };
	inline void SETgold(int gold) { m_gold = gold; };
	inline void SETrevolt(int revolt) { m_revolt = revolt; };
	inline void SETreligion(Religion_Type religion) { m_religion = religion; };
	inline void SETplace(bool place) { m_place = place; };

	inline unsigned int GETtileOccupied()const { return m_tileOccupied; };
	inline Emotion_Type GEThappiness()const { return m_happiness; };
	inline int GETfood()const { return m_food; };
	inline int GETwork()const { return m_work; };
	inline int GETgold()const { return m_gold; };
	inline int GETrevolt()const { return m_revolt; };
	inline Religion_Type GETreligion()const { return m_religion; };
	inline bool GETplace()const { return m_place; };

private:
	/* *********************************************************
	 *					Citizen::ATTRIBUTS					   *
	 ********************************************************* */

	unsigned int m_tileOccupied;
	Emotion_Type m_happiness;
	int m_food;
	int m_work;
	int m_gold;
	int m_revolt;
	Religion_Type m_religion;

	bool m_place;
};



#endif /* Citizen_H */

/*
*	End Of File : Citizen.h
*/
