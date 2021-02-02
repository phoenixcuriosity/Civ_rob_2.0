/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.22.0.0
	file version : 1.10

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
#include "civ_lib.h"

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
_goldStats{ INITIAL_GOLD , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
_onOffDisplay{ false }
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
Player::Player(const std::string &msg):
_name(msg),
_goldStats{ INITIAL_GOLD , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
_onOffDisplay{ false }
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

		LoadConfig::logfileconsole("[INFO]___: Kill Unit n:" + std::to_string(i) + " of Player: " + _name + " Success");
	}

	for (unsigned int i(0); i < size; i++)
		_tabUnit.pop_back();

	if (_tabUnit.empty())
		LoadConfig::logfileconsole("[INFO]___: Kill ALL Unit of Player:" + _name + " Success");
	else
		LoadConfig::logfileconsole("[ERROR]__: _tabunit.size() != 0");


	size = (unsigned int)_tabCity.size();

	for (unsigned int i(0); i < size; i++)
	{
		delete _tabCity[i];

		LoadConfig::logfileconsole("[INFO]___: Kill Citie n:" + std::to_string(i) + " of Player: " + _name + " Success");
	}

	for (unsigned int i(0); i < size; i++)
		_tabCity.pop_back();

	if (_tabCity.empty())
		LoadConfig::logfileconsole("[INFO]___: Kill ALL Cities of Player:" + _name + " Success");
	else
		LoadConfig::logfileconsole("[ERROR]__: _tabcities.size() != 0");
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
	if (assertSize(_tabUnit.size(), index))
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
	if (assertSize(_tabCity.size(), index))
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
	_goldStats.income =		_goldStats.taxIncome
						 +  _goldStats.commerceIncome
						 +  _goldStats.goldConversionSurplus;

	_goldStats.cost =		_goldStats.buildingsCost
						 +  _goldStats.armiesCost;

	_goldStats.goldBalance = _goldStats.income - _goldStats.cost;
	_goldStats.gold += _goldStats.goldBalance;
	
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

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : displayGoldStats															   */
/* ROLE : Display gold Stats per player												   */
/* INPUT : SDL_Renderer*& : ptr on SDL Renderer										   */
/* INPUT : TTF_Font* font[]	: ptr on font array										   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::displayGoldStats
(
	SDL_Renderer*& renderer,
	TTF_Font* font[]
)
{
	std::ostringstream stream;
	stream << std::fixed;
	stream << std::setprecision(1);
	stream << _goldStats.gold;

	Texte::writeTexte(renderer, font, Index_staticIndexVectorTextes::PLAYER_GOLD, Texte_Type::shaded,
		"Gold : " + stream.str(), White, { 64, 64, 64, 255 }, 24,
		0, 900, nonTransparent, no_angle, Center_Type::nocenter);

	if (_onOffDisplay.showContextGoldStats)
	{
		unsigned int initX(200), spaceX(150);
		unsigned int initY(900), spaceY(32);

		stream.str("");
		stream.clear();
		stream << _goldStats.goldBalance;

		Texte::writeTexte(renderer, font, Index_staticIndexVectorTextes::PLAYER_GOLD_BALANCE, Texte_Type::shaded,
			"Balance : " + stream.str(), White, { 64, 64, 64, 255 }, 18,
			initX, initY,nonTransparent, no_angle, Center_Type::nocenter);

		stream.str("");
		stream.clear();
		stream << _goldStats.income;
		Texte::writeTexte(renderer, font, Index_staticIndexVectorTextes::PLAYER_INCOME, Texte_Type::shaded,
			"Income : " + stream.str(), White, { 64, 64, 64, 255 }, 18,
			initX += spaceX, initY, nonTransparent, no_angle, Center_Type::nocenter);

		stream.str("");
		stream.clear();
		stream << _goldStats.cost;
		Texte::writeTexte(renderer, font, Index_staticIndexVectorTextes::PLAYER_COST, Texte_Type::shaded,
			"Cost : " + stream.str(), White, { 64, 64, 64, 255 }, 18,
			initX += spaceX, initY, nonTransparent, no_angle, Center_Type::nocenter);



		stream.str("");
		stream.clear();
		stream << _goldStats.taxIncome;
		Texte::writeTexte(renderer, font, Index_staticIndexVectorTextes::PLAYER_TAX_INCOME, Texte_Type::shaded,
			"Tax : " + stream.str(), White, { 64, 64, 64, 255 }, 18,
			initX = 200, initY += spaceY,
			nonTransparent, no_angle, Center_Type::nocenter);

		stream.str("");
		stream.clear();
		stream << _goldStats.commerceIncome;
		Texte::writeTexte(renderer, font, Index_staticIndexVectorTextes::PLAYER_COMMERCE_INCOME, Texte_Type::shaded,
			"Commerce : " + stream.str(), White, { 64, 64, 64, 255 }, 18,
			initX += spaceX, initY,
			nonTransparent, no_angle, Center_Type::nocenter);

		stream.str("");
		stream.clear();
		stream << _goldStats.goldConversionSurplus;
		Texte::writeTexte(renderer, font, Index_staticIndexVectorTextes::PLAYER_GOLD_CONVERSION_SURPLUS, Texte_Type::shaded,
			"Surplus : " + stream.str(), White, { 64, 64, 64, 255 }, 18,
			initX += spaceX, initY,
			nonTransparent, no_angle, Center_Type::nocenter);



		stream.str("");
		stream.clear();
		stream << _goldStats.buildingsCost;
		Texte::writeTexte(renderer, font, Index_staticIndexVectorTextes::PLAYER_BUILDINGS_COST, Texte_Type::shaded,
			"Building cost : " + stream.str(), White, { 64, 64, 64, 255 }, 18,
			initX = 200, initY += spaceY,
			nonTransparent, no_angle, Center_Type::nocenter);

		stream.str("");
		stream.clear();
		stream << _goldStats.armiesCost;
		Texte::writeTexte(renderer, font, Index_staticIndexVectorTextes::PLAYER_ARMIES_COST, Texte_Type::shaded,
			"Armies cost : " + stream.str(), White, { 64, 64, 64, 255 }, 18,
			initX += 200, initY,
			nonTransparent, no_angle, Center_Type::nocenter);
	}
}

bool Player::assertSize
(
	size_t size,
	unsigned int index
)
{
	return index < size ? true : false;
}

/* *********************************************************
 *				END Player::METHODS						   *
 ********************************************************* */

/*
*	End Of File : Player.cpp
*/