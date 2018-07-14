/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.6

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Civ_rob_2

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
#include "Units.h"
#include "Cities.h"

class Player{
	public:
		Player();
		Player(const std::string&);
		~Player();

		virtual void addEmptyUnit();
		virtual void addUnit(const std::string &, unsigned int, unsigned int, unsigned int,
			unsigned int, unsigned int, unsigned int, unsigned int);
		virtual void deleteUnit(unsigned int);
		virtual void addCitie(const std::string &, unsigned int, unsigned int, tile[]);
		virtual void deleteCitie(unsigned int);

		virtual const std::string GETname() const;
		virtual Units* GETtheunit(unsigned int) const;
		virtual std::vector<Units*> GETtabunit() const;
		virtual Cities* GETthecitie(unsigned int) const;
		virtual std::vector<Cities*> GETtabcities() const;

		virtual void SETname(const std::string&);

	private:
		std::string _name;
		std::vector<Units*> _tabunit;
		std::vector<Cities*> _tabcities;
};



#endif