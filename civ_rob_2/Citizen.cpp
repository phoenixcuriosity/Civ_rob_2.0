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

#include "Citizen.h"
#include "sdl.h"

using namespace std;


Citizen::Citizen() : _tileOccupied((unsigned int)ceil((initSizeView*initSizeView)/2)), _happiness(1), _food(2), _work(1), _gold(1), _revolt(0), _religious(false), _place(false)
{
	logfileconsole("Create Citizen par défaut Success");
}
Citizen::Citizen(tile tiles) : _tileOccupied((unsigned int)ceil((initSizeView*initSizeView) / 2)), _happiness(1), _food(tiles.food), _work(tiles.work), _gold(tiles.gold), _revolt(0), _religious(false), _place(true)
{
	logfileconsole("Create Citizen Success");
}
Citizen::Citizen(std::vector<tile> tiles, std::vector<Citizen> citizens) : _tileOccupied(placeCitizen(tiles, citizens, _food, _work, _gold)), _happiness(1), _revolt(0), _religious(false), _place(true)
{
	logfileconsole("Create Citizen Success");
}
Citizen::~Citizen()
{
	logfileconsole("Kill Citizen Success");
}

unsigned int placeCitizen(std::vector<tile> tiles, std::vector<Citizen> citizens, int& _food, int& _work, int& _gold){
	unsigned int condition = citizens.size();
	unsigned int checkcondition = 0;
	unsigned int place = 0;

	vector<unsigned int> tabpos;
	for (unsigned int j = 0; j < condition; j++){
		tabpos.push_back(citizens[j].GETtileOccupied());
	}
	for (unsigned int i = 0; i < initSizeView*initSizeView; i++){
		for (unsigned int p = 0; p < condition; p++){
			checkcondition = 0;
			if (i != tabpos[p])
				checkcondition++;
			if (checkcondition == condition)
				place = i;
		}
	}
	_food = tiles[place].food;
	_work = tiles[place].work;
	_gold = tiles[place].gold;
	return place;
}


unsigned int Citizen::GETtileOccupied()const{
	return _tileOccupied;
}
int Citizen::GETfood()const{
	return _food;
}
int Citizen::GETwork()const{
	return _work;
}
int Citizen::GETgold()const{
	return _gold;
}
