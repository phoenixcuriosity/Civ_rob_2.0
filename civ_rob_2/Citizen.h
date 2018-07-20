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

#ifndef Citizen_H
#define Citizen_H

#include "civ_lib.h"

class Citizen{
public:
	Citizen();
	Citizen(tile tiles);
	Citizen(std::vector<tile> tiles, std::vector<Citizen> citizens);
	~Citizen();

	friend unsigned int placeCitizen(std::vector<tile> tiles, std::vector<Citizen> citizens, int& _food, int& _work, int& _gold);

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
