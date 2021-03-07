/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.2.0
	file version : 1.13

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

#include "Utility.h"
#include "MainGame.h"

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
Player::Player() :
	_name("NoName"),
	_selectedUnit(NO_UNIT_SELECTED), _selectedCity(NO_CITY_SELECTED),
	_goldStats{ INITIAL_GOLD , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
	_onOffDisplay{ false }
{
	MainGame::logfileconsole("[INFO]___: Create Player Par Defaut Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Player																	   */
/* ROLE : Constructeur par nom du joueur											   */
/* INPUT : const std::string&														   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Player::Player(const std::string& msg) :
	_name(msg),
	_selectedUnit(NO_UNIT_SELECTED), _selectedCity(NO_CITY_SELECTED),
	_goldStats{ INITIAL_GOLD , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
	_onOffDisplay{ false }
{
	MainGame::logfileconsole("[INFO]___: Create Player Success");
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
		_goldStats = player.GETgoldStatsConst();
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

		MainGame::logfileconsole("[INFO]___: Kill Unit n:" + std::to_string(i) + " of Player: " + _name + " Success");
	}

	for (unsigned int i(0); i < size; i++)
		_tabUnit.pop_back();

	if (_tabUnit.empty())
		MainGame::logfileconsole("[INFO]___: Kill ALL Unit of Player:" + _name + " Success");
	else
		MainGame::logfileconsole("[ERROR]__: _tabunit.size() != 0");

	
	size = (unsigned int)_tabCity.size();

	for (unsigned int i(0); i < size; i++)
	{
		delete _tabCity[i];

		MainGame::logfileconsole("[INFO]___: Kill Citie n:" + std::to_string(i) + " of Player: " + _name + " Success");
	}

	for (unsigned int i(0); i < size; i++)
		_tabCity.pop_back();

	if (_tabCity.empty())
		MainGame::logfileconsole("[INFO]___: Kill ALL Cities of Player:" + _name + " Success");
	else
		MainGame::logfileconsole("[ERROR]__: _tabcities.size() != 0");
		
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
	const std::string& name,
	unsigned int x,
	unsigned int y,
	Unit_Movement_Type movementType,
	unsigned int life,
	unsigned int atq,
	unsigned int def,
	unsigned int move,
	unsigned int level,
	double maintenance
)
{
	_tabUnit.push_back(new Unit(name, x, y, movementType, life, atq, def, move, level, maintenance));
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
	if (Utility::assertSize(_tabUnit.size(), index))
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
	const std::string& name,
	unsigned int x,
	unsigned int y,
	VectMap& tiles
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

	if (Utility::assertSize(_tabCity.size(), index))
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
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : computeGold																   */
/* ROLE : Compute income and cost then the balance between the two					   */
/* ROLE : Add balance to the player gold											   */
/* INPUT : void																		   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::computeGold()
{
	computeMaintenanceCostUnit();

	_goldStats.income = _goldStats.taxIncome
		+ _goldStats.commerceIncome
		+ _goldStats.goldConversionSurplus;

	_goldStats.cost = _goldStats.buildingsCost
		+ _goldStats.armiesCost;

	_goldStats.goldBalance = _goldStats.income - _goldStats.cost;
	_goldStats.gold += _goldStats.goldBalance;

}

void Player::computeMaintenanceCostUnit()
{
	/*
	for (unsigned int i(0); i < _tabUnit.size(); i++)
	{
		_goldStats.armiesCost += _tabUnit[i]->GETmaintenance();
	}
	*/
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : resetGoldStats															   */
/* ROLE : Reset all stats of _goldStats except gold									   */
/* INPUT : void																		   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::resetGoldStats()
{
	_goldStats.goldBalance = 0.0;
	_goldStats.cost = 0.0;
	_goldStats.taxIncome = 0.0;
	_goldStats.commerceIncome = 0.0;
	_goldStats.goldConversionSurplus = 0.0;
	_goldStats.buildingsCost = 0.0;
	_goldStats.armiesCost = 0.0;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : resetGoldStats															   */
/* ROLE : Reset all stats of _goldStats except gold									   */
/* INPUT : double goldToAdd	: gold to add in goldConversionSurplus					   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::addGoldToGoldConversionSurplus
(
	double goldToAdd
)
{
	_goldStats.goldConversionSurplus += goldToAdd;
}


/* *********************************************************
 *				END Player::METHODS						   *
 ********************************************************* */






Players::Players()
:_selectedPlayer(NO_PLAYER_SELECTED), _nbNoNamePlayer(0), _citiesNameMaxToCreate(0)
{

}

Players::~Players()
{
	for (unsigned int i(0); i < _vectPlayer.size(); i++)
	{
		removeIndexPlayer(i);
	}
}

void Players::addPlayer()
{

}

void Players::removeIndexPlayer
(
	unsigned int index
)
{
	if (Utility::assertSize(_vectPlayer.size(), index))
	{
		if (nullptr != _vectPlayer[index])
		{
			delete _vectPlayer[index];
		}
	}
	else
	{
		throw("[ERROR]__: removeIndexPlayer : assertSize");
	}
}



 /*
 *	End Of File : Player.cpp
 */