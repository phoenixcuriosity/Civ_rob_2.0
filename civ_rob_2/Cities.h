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

#ifndef Cities_H
#define Cities_H

#include "civ_lib.h"
#include "Citizen.h"

class Cities {
public:
	Cities() {}; // garder le constructeur par défaut
	Cities(const std::string &, unsigned int, unsigned int, tile[]);
	~Cities();

	friend std::vector<tile> createTiles(tile tiles[]);
	friend std::vector<Citizen> createCitizen(tile tiles);

	virtual void afficher(sysinfo&);
	virtual void affichercitiemap(sysinfo&);


	virtual void foodNextTurn();

	virtual int testPos(int, int);

	virtual unsigned int GETx()const;
	virtual unsigned int GETy()const;

	

private:
	std::string _image;
	std::string _name;
	unsigned int _x;
	unsigned int _y;
	std::vector<tile> _tiles;
	std::vector<Citizen> _citizens;
	unsigned int _influenceLevel;
	unsigned int _nbpop;
	unsigned int _atq;
	unsigned int _def;
	unsigned int _nbhappy;
	unsigned int _nbsad;
	unsigned int _nbstructurebuild;

	double _foodStock;
	double _foodBalance;
};

#endif