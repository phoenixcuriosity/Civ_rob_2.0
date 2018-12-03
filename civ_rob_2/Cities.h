/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.6

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

#ifndef Cities_H
#define Cities_H

#include "civ_lib.h"
#include "Player.h"

class Cities {
public:
	Cities() {}; // garder le constructeur par défaut
	Cities(const std::string &, unsigned int, unsigned int, Tile[]);
	~Cities();

	friend std::vector<Tile> createtiles(Tile tile[]);
	friend std::vector<Citizen> createCitizen(Tile tile);

	static void createcitie(Sysinfo& sysinfo);
	static void searchCitietile(Sysinfo& sysinfo);

	virtual void afficher(Sysinfo&);
	virtual void affichercitiemap(Sysinfo&);


	virtual void foodNextTurn();

	virtual int testPos(unsigned int, unsigned int);

	virtual unsigned int GETx()const;
	virtual unsigned int GETy()const;

	

private:
	std::string _image;
	std::string _name;
	unsigned int _x;
	unsigned int _y;
	std::vector<Tile> _tile;
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



class Citizen {
public:
	Citizen();
	Citizen(Tile tiles);
	Citizen(std::vector<Tile> tile, std::vector<Citizen> citizens);
	~Citizen();

	friend unsigned int placeCitizen(std::vector<Tile> tile, std::vector<Citizen> citizens, int& _food, int& _work, int& _gold);

	void placeCitizenWithMouse();

	unsigned int GETtileOccupied()const;
	int GETfood()const;
	int GETwork()const;
	int GETgold()const;

private:
	unsigned int _tileOccupied;
	int _happiness;
	int _food;
	int _work;
	int _gold;
	int _revolt;

	bool _religious;
	bool _place;
};

#endif