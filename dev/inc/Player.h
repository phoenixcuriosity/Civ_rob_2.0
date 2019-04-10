/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
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

#include "civ_lib.h"
#include "Unit.h"
#include "City.h"

class Player
{
public:
	/* *********************************************************
	 *					Player::METHODS						   *
	 ********************************************************* */
	 
	 
	Player();
	Player(const std::string&);
	~Player();

	
	/*
	 * NAME : addEmptyUnit
	 * ROLE : Initialisation d'une Unit vide
	 * INPUT  PARAMETERS : void
	 * OUTPUT PARAMETERS : Initialisation d'une Unit vide
	 * RETURNED VALUE    : void
	 */
	virtual void addEmptyUnit();
	
	
	/*
	 * NAME : addUnit
	 * ROLE : Ajout une Unit avec les spécifications demandées (nom, positions, ...)
	 * INPUT  PARAMETERS : Spécifications demandées (nom, positions, ...)
	 * OUTPUT PARAMETERS : Ajout une Unit
	 * RETURNED VALUE    : void
	 */
	virtual void addUnit(const std::string &name, unsigned int x,
		unsigned int y, unsigned int life, unsigned int atq,
		unsigned int def, unsigned int move, unsigned int level);
		
		
	/*
	 * NAME : deleteUnit
	 * ROLE : Suppression d'une Unit du joueur
	 * INPUT  PARAMETERS : unsigned int : index de Unit dans le tableau
	 * OUTPUT PARAMETERS : Suppression d'une Unit
	 * RETURNED VALUE    : void
	 */
	virtual void deleteUnit(unsigned int index);
	
	
	/*
	 * NAME : addCity
	 * ROLE : Ajout une City avec les spécifications demandées (nom, positions, ...)
	 * INPUT  PARAMETERS : Spécifications demandées (nom, positions, ...)
	 * OUTPUT PARAMETERS : Ajout une City
	 * RETURNED VALUE    : void
	 */
	virtual void addCity(const std::string &, unsigned int, unsigned int, Tile[]);
	
	
	/*
	 * NAME : deleteCity
	 * ROLE : Suppression d'une City du joueur
	 * INPUT  PARAMETERS : unsigned int : index de City dans le tableau
	 * OUTPUT PARAMETERS : Suppression d'une City
	 * RETURNED VALUE    : void
	 */
	virtual void deleteCity(unsigned int);

	
public:
	/* *********************************************************
	 *				Player::METHODS::GET/SET				   *
	 ********************************************************* */
	 
	 
	inline virtual std::string GETname() const					{ return _name; };
	inline virtual Unit* GETtheUnit(unsigned int index) const	{ return _tabUnit[index]; };
	inline virtual std::vector<Unit*> GETtabUnit() const		{ return _tabUnit; };
	inline virtual City* GETtheCity(unsigned int index) const{ return _tabCity[index]; };
	inline virtual std::vector<City*> GETtabCity() const	{ return _tabCity; };

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