/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.14
	file version : 1.0

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

Player::Player() : _name("NoName")
{
	IHM::logfileconsole("Create Player Par Defaut Success");
}
Player::Player(const std::string &msg) : _name(msg)
{
	IHM::logfileconsole("Create Player Success");
}
Player::~Player()
{
	unsigned int size = _tabunit.size();

	for (unsigned int i = 0; i < size; i++)
	{
		delete _tabunit[i];

		IHM::logfileconsole("Kill Unit n:" + std::to_string(i) + " of Player: " + _name + " Success");
	}

	for (unsigned int i = 0; i < size; i++)
		_tabunit.pop_back();

	if (_tabunit.size() != 0)
		IHM::logfileconsole("___________ERROR : _tabunit.size() != 0");
	else
		IHM::logfileconsole("Kill ALL Unit of Player:" + _name + " Success");


	size = _tabcities.size();

	for (unsigned int i = 0; i < size; i++)
	{
		delete _tabcities[i];

		IHM::logfileconsole("Kill Citie n:" + std::to_string(i) + " of Player: " + _name + " Success");
	}

	for (unsigned int i = 0; i < size; i++)
		_tabcities.pop_back();

	if (_tabcities.size() != 0)
		IHM::logfileconsole("___________ERROR : _tabcities.size() != 0");
	else
		IHM::logfileconsole("Kill ALL Cities of Player:" + _name + " Success");

	
}
void Player::addEmptyUnit()
{
	_tabunit.push_back(new Units());
}
void Player::addUnit(const std::string &name, unsigned int x, unsigned int y, unsigned int life, unsigned int atq,
	unsigned int def, unsigned int move, unsigned int level) 
{
	_tabunit.push_back(new Units(name, x, y, life, atq, def, move, level));
}
void Player::deleteUnit(unsigned int index)
{
	delete _tabunit[index];
	if (_tabunit.size() > 1 && index < _tabunit.size() - 1)
	{
		for (unsigned int i = index; i < (_tabunit.size() - 1); i++)
			_tabunit[i] = _tabunit[i + 1];
	}
	_tabunit.pop_back();
}
void Player::addCitie(const std::string &name, unsigned int x, unsigned int y, Tile tiles[])
{
	_tabcities.push_back(new Cities(name, x, y, tiles));
}
void Player::deleteCitie(unsigned int index)
{
	delete _tabcities[index];
	if (_tabcities.size() > 1 && index < _tabcities.size() - 1)
	{
		for (unsigned int i = index; i < (_tabcities.size() - 1); i++)
			_tabcities[i] = _tabcities[i + 1];
	}
	_tabcities.pop_back();
}
const std::string Player::GETname() const
{
	return _name;
}
Units* Player::GETtheunit(unsigned int index) const
{
	return _tabunit[index];
}
std::vector<Units*> Player::GETtabunit() const
{
	return _tabunit;
}
Cities* Player::GETthecitie(unsigned int index) const
{
	return _tabcities[index];
}
std::vector<Cities*> Player::GETtabcities() const
{
	return _tabcities;
}
void Player::SETname(const std::string &msg)
{
	_name = msg;
}

/*
*	End Of File
*/