/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "Player.h"
#include "IHM.h"
#include "LoadConfig.h"

/* *********************************************************
 *				START Player::METHODS					   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Player																	   */
/* ROLE : Constructeur par défaut													   */
/* INPUT : void																		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Player::Player() : _name("NoName")
{
	LoadConfig::logfileconsole("[INFO]___: Create Player Par Defaut Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Player																	   */
/* ROLE : Constructeur par nom du joueur											   */
/* INPUT : const std::string&														   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Player::Player(const std::string &msg) : _name(msg)
{
	LoadConfig::logfileconsole("[INFO]___: Create Player Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : ~Player																	   */
/* ROLE : Initialisation d'une Unit vide											   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Player::~Player()
{
	deletePlayer();
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : operator=																	   */
/* ROLE : Redéfinition de l'opérateur =												   */
/* INPUT : const Player& player : l'objet à copier									   */
/* RETURNED VALUE : Player&	: l'objet recopié										   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Player& Player::operator=
(
	const Player& player
)
{
	if (this != &player)
	{
		deletePlayer();
		_name = player.GETname();
		_tabUnit = player.GETtabUnit();
		_tabCity = player.GETtabCity();
	}
	return *this;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : deletePlayer																   */
/* ROLE : Destruction de l'objet et de ses ptr										   */
/* INPUT : void																		   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::deletePlayer()
{
	unsigned int size((unsigned int)_tabUnit.size());

	for (unsigned int i(0); i < size; i++)
	{
		delete _tabUnit[i];

		LoadConfig::logfileconsole("[INFO]___: Kill Unit n:" + std::to_string(i) + " of Player: " + _name + " Success");
	}

	for (unsigned int i(0); i < size; i++)
		_tabUnit.pop_back();

	if (_tabUnit.size() > 0)
		LoadConfig::logfileconsole("[ERROR]__: _tabunit.size() != 0");
	else
		LoadConfig::logfileconsole("[INFO]___: Kill ALL Unit of Player:" + _name + " Success");


	size = (unsigned int)_tabCity.size();

	for (unsigned int i(0); i < size; i++)
	{
		delete _tabCity[i];

		LoadConfig::logfileconsole("[INFO]___: Kill Citie n:" + std::to_string(i) + " of Player: " + _name + " Success");
	}

	for (unsigned int i(0); i < size; i++)
		_tabCity.pop_back();

	if (_tabCity.size() > 0)
		LoadConfig::logfileconsole("[ERROR]__: _tabcities.size() != 0");
	else
		LoadConfig::logfileconsole("[INFO]___: Kill ALL Cities of Player:" + _name + " Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : addEmptyUnit																   */
/* ROLE : Initialisation d'une Unit vide											   */
/* INPUT : void																		   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::addEmptyUnit()
{
	_tabUnit.push_back(new Unit());
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : addUnit																	   */
/* ROLE : Ajout une Unit avec les spécifications demandées (nom, positions, ...)	   */
/* INPUT : Spécifications demandées (nom, positions, ...)							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::addUnit
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
) 
{
	_tabUnit.push_back(new Unit(name, x, y, movementType, life, atq, def, move, level));
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : deleteUnit																   */
/* ROLE : Suppression d'une Unit du joueur											   */
/* INPUT : unsigned int : index de Unit dans le tableau								   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::deleteUnit
(
	unsigned int index
)
{
	if (nullptr != _tabUnit[index])
	{
		delete _tabUnit[index];
		if (_tabUnit.size() > 1 && index < _tabUnit.size() - 1)
		{
			for (unsigned int i(index); i < (_tabUnit.size() - 1); i++)
				_tabUnit[i] = _tabUnit[(unsigned __int64)i + 1];
		}
		_tabUnit.pop_back();
	}
	else
	{
		throw("[ERROR]__: deleteUnit : nullptr == _tabUnit[index]");
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : addCity																	   */
/* ROLE : Ajout une City avec les spécifications demandées (nom, positions, ...)	   */
/* INPUT : Spécifications demandées (nom, positions, ...)							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::addCity
(
	const std::string &name,
	unsigned int x,
	unsigned int y,
	std::vector<Tile>& tiles
)
{
	_tabCity.push_back(new City(name, x, y, tiles));
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : deleteCity																   */
/* ROLE : Suppression d'une City du joueur											   */
/* INPUT : unsigned int : index de City dans le tableau								   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::deleteCity
(
	unsigned int index
)
{
	if (nullptr != _tabCity[index])
	{
		delete _tabCity[index];
		if (_tabCity.size() > 1 && index < _tabCity.size() - 1)
		{
			for (unsigned int i(index); i < (_tabCity.size() - 1); i++)
				_tabCity[i] = _tabCity[(unsigned __int64)i + 1];
		}
		_tabCity.pop_back();
	}
	else
	{
		throw("[ERROR]__: deleteCity : nullptr == _tabCity[index]");
	}
}


/* *********************************************************
 *				END Player::METHODS						   *
 ********************************************************* */

/*
*	End Of File : Player.cpp
*/