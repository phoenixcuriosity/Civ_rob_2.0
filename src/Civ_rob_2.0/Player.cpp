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

#include "Player.h"
#include "IHM.h"


/* *********************************************************
 *				START Player::METHODS					   *
 ********************************************************* */

Player::Player() : _name("NoName")
{
	IHM::logfileconsole("[INFO]___: Create Player Par Defaut Success");
}
Player::Player(const std::string &msg) : _name(msg)
{
	IHM::logfileconsole("[INFO]___: Create Player Success");
}
Player::~Player()
{
	unsigned int size = (unsigned int)_tabUnit.size();

	for (unsigned int i = 0; i < size; i++)
	{
		delete _tabUnit[i];

		IHM::logfileconsole("[INFO]___: Kill Unit n:" + std::to_string(i) + " of Player: " + _name + " Success");
	}

	for (unsigned int i = 0; i < size; i++)
		_tabUnit.pop_back();

	if (_tabUnit.size() != 0)
		IHM::logfileconsole("[ERROR]__: _tabunit.size() != 0");
	else
		IHM::logfileconsole("[INFO]___: Kill ALL Unit of Player:" + _name + " Success");


	size = (unsigned int)_tabCity.size();

	for (unsigned int i = 0; i < size; i++)
	{
		delete _tabCity[i];

		IHM::logfileconsole("[INFO]___: Kill Citie n:" + std::to_string(i) + " of Player: " + _name + " Success");
	}

	for (unsigned int i = 0; i < size; i++)
		_tabCity.pop_back();

	if (_tabCity.size() != 0)
		IHM::logfileconsole("[ERROR]__: _tabcities.size() != 0");
	else
		IHM::logfileconsole("[INFO]___: Kill ALL Cities of Player:" + _name + " Success");
}


/*
* NAME : addEmptyUnit
* ROLE : Initialisation d'une Unit vide
* INPUT  PARAMETERS : void
* OUTPUT PARAMETERS : Initialisation d'une Unit vide
* RETURNED VALUE    : void
*/
void Player::addEmptyUnit()
{
	_tabUnit.push_back(new Unit());
}


/*
* NAME : addUnit
* ROLE : Ajout une Unit avec les spécifications demandées (nom, positions, ...)
* INPUT  PARAMETERS : Spécifications demandées (nom, positions, ...)
* OUTPUT PARAMETERS : Ajout une Unit
* RETURNED VALUE    : void
*/
void Player::addUnit(const std::string &name, unsigned int x, unsigned int y, unsigned int life, unsigned int atq,
	unsigned int def, unsigned int move, unsigned int level) 
{
	_tabUnit.push_back(new Unit(name, x, y, life, atq, def, move, level));
}

/*
* NAME : deleteUnit
* ROLE : Suppression d'une Unit du joueur
* INPUT  PARAMETERS : unsigned int : index de Unit dans le tableau
* OUTPUT PARAMETERS : Suppression d'une Unit
* RETURNED VALUE    : void
*/
void Player::deleteUnit(unsigned int index)
{
	delete _tabUnit[index];
	if (_tabUnit.size() > 1 && index < _tabUnit.size() - 1)
	{
		for (unsigned int i(index); i < (_tabUnit.size() - 1); i++)
			_tabUnit[i] = _tabUnit[(unsigned __int64)i + 1];
	}
	_tabUnit.pop_back();
}

/*
* NAME : addCity
* ROLE : Ajout une City avec les spécifications demandées (nom, positions, ...)
* INPUT  PARAMETERS : Spécifications demandées (nom, positions, ...)
* OUTPUT PARAMETERS : Ajout une City
* RETURNED VALUE    : void
*/
void Player::addCity(const std::string &name, unsigned int x, unsigned int y, Tile tiles[])
{
	_tabCity.push_back(new City(name, x, y, tiles));
}

/*
* NAME : deleteCity
* ROLE : Suppression d'une City du joueur
* INPUT  PARAMETERS : unsigned int : index de City dans le tableau
* OUTPUT PARAMETERS : Suppression d'une City
* RETURNED VALUE    : void
*/
void Player::deleteCity(unsigned int index)
{
	delete _tabCity[index];
	if (_tabCity.size() > 1 && index < _tabCity.size() - 1)
	{
		for (unsigned int i(index); i < (_tabCity.size() - 1); i++)
			_tabCity[i] = _tabCity[(unsigned __int64)i + 1];
	}
	_tabCity.pop_back();
}


/* *********************************************************
 *				END Player::METHODS						   *
 ********************************************************* */

/*
*	End Of File : Player.cpp
*/