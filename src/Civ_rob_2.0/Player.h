/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.15
	file version : 1.2

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

#ifndef Player_H
#define Player_H

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"
#include "Unit.h"

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

 /* N/A */

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

class Player
{
public:
	/* *********************************************************
	 *					Player::METHODS						   *
	 ********************************************************* */
	 

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Player																	   */
	/* ROLE : Constructeur par défaut													   */
	/* INPUT : void																		   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	Player();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Player																	   */
	/* ROLE : Constructeur par nom du joueur											   */
	/* INPUT : const std::string&														   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	Player
	(
		const std::string&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : ~Player																	   */
	/* ROLE : Initialisation d'une Unit vide											   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	~Player();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator=																	   */
	/* ROLE : Redéfinition de l'opérateur =												   */
	/* INPUT : const Player& player : l'objet à copier									   */
	/* RETURNED VALUE : Player&	: l'objet recopié										   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	Player& operator=
	(
		const Player& player
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deletePlayer																   */
	/* ROLE : Destruction de l'objet et de ses ptr										   */
	/* INPUT : void																		   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void deletePlayer();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : addEmptyUnit																   */
	/* ROLE : Initialisation d'une Unit vide											   */
	/* INPUT : void																		   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void addEmptyUnit();
	
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : addUnit																	   */
	/* ROLE : Ajout une Unit avec les spécifications demandées (nom, positions, ...)	   */
	/* INPUT : Spécifications demandées (nom, positions, ...)							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void addUnit
	(
		const std::string &name,
		unsigned int x,
		unsigned int y,
		Unit_Movement_Type movementType,
		unsigned int life,
		unsigned int atq,
		unsigned int def,
		unsigned int move,
		unsigned int level
	);	

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deleteUnit																   */
	/* ROLE : Suppression d'une Unit du joueur											   */
	/* INPUT : unsigned int : index de Unit dans le tableau								   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void deleteUnit
	(
		unsigned int index
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : addCity																	   */
	/* ROLE : Ajout une City avec les spécifications demandées (nom, positions, ...)	   */
	/* INPUT : Spécifications demandées (nom, positions, ...)							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void addCity
	(
		const std::string &,
		unsigned int,
		unsigned int,
		std::vector<Tile>& tiles
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deleteCity																   */
	/* ROLE : Suppression d'une City du joueur											   */
	/* INPUT : unsigned int : index de City dans le tableau								   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void deleteCity
	(
		unsigned int
	);

	
public:
	/* *********************************************************
	 *				Player::METHODS::GET/SET				   *
	 ********************************************************* */
	 
	 
	inline virtual std::string GETname() const					{ return _name; };
	inline virtual Unit* GETtheUnit(unsigned int index) const	{ return _tabUnit[index]; };
	inline virtual std::vector<Unit*> GETtabUnit() const		{ return _tabUnit; };
	inline virtual City* GETtheCity(unsigned int index) const	{ return _tabCity[index]; };
	inline virtual std::vector<City*> GETtabCity() const		{ return _tabCity; };

	inline virtual void SETname(const std::string& msg)			{ _name = msg; };

	
	
private:
	/* *********************************************************
	 *					Player::ATTRIBUTS					   *
	 ********************************************************* */
	 
	 
	std::string _name;
	std::vector<Unit*> _tabUnit;
	std::vector<City*> _tabCity;
};



#endif /* Player_H */


/*
*	End Of File : Player.h
*/