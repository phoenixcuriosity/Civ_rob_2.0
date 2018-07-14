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

#include "Cities.h"
#include "sdl.h"

using namespace std;

Cities::Cities(const string& name, unsigned int x, unsigned int y, tile tiles[]) : _image("citie.png"),
_name(name), _x(x), _y(y), _tiles(createTiles(tiles)), _citizens(createCitizen(tiles[(unsigned int)ceil((initSizeView*initSizeView) / 2)])),
_influenceLevel(1),_nbpop(1), _atq(0), _def(0), _nbhappy(0), _nbsad(0), _nbstructurebuild(0),
_foodStock(0), _foodBalance(tiles[(unsigned int)ceil((initSizeView*initSizeView) / 2)].food)
{
	logfileconsole("Create Citie: " + _name + " Success");
}

Cities::~Cities()
{
	logfileconsole("Destroy Citie: " + _name + " Success");
}


std::vector<tile> createTiles(tile tiles[]){
	std::vector<tile> Atiles;
	for (unsigned int i = 0; i < initSizeView*initSizeView; i++)
		Atiles.push_back(tiles[i]);
	return Atiles;
}
std::vector<Citizen> createCitizen(tile tiles){
	std::vector<Citizen> Acitizen;
	Citizen acitizen(tiles);
	Acitizen.push_back(acitizen);	
	return Acitizen;
}



void Cities::afficher(sysinfo& information) {
	for (unsigned int i = information.allTextures.indexEndColorAppTileStartMiscTexture; i < information.allTextures.indexEndMiscTextureStartWrite; i++)
		information.allTextures.tabTexture[i]->renderTextureTestString(information.ecran.renderer, _image, _x, _y);
	for (unsigned int i = information.allTextures.indexEndMiscTextureStartWrite; i < information.allTextures.tabTexture.size(); i++)
		information.allTextures.tabTexture[i]->renderTextureTestString(information.ecran.renderer, _name, _x, _y + tileSize);
}


void Cities::affichercitiemap(sysinfo& information) {
	for (unsigned int i = 0; i < initSizeView*initSizeView; i++) {
		if (_tiles[i].tile_stringground.compare("grass.bmp") == 0)
			information.allTextures.tabTexture[0]->renderTexture(information.ecran.renderer, _tiles[i].tile_x, _tiles[i].tile_y);
		else if (_tiles[i].tile_stringground.compare("water.bmp") == 0)
			information.allTextures.tabTexture[1]->renderTexture(information.ecran.renderer, _tiles[i].tile_x, _tiles[i].tile_y);

		if (_tiles[i].tile_spec != 0) {
			for (unsigned int l = information.allTextures.indexEndGroundStartSpec; l < information.allTextures.indexEndSpecStartUnit; l++)
				information.allTextures.tabTexture[l]->renderTextureTestString(information.ecran.renderer, _tiles[i].tile_stringspec, _tiles[i].tile_x, _tiles[i].tile_y);
		}
		if (_tiles[i].appartenance != -1) {
			for (unsigned int l = information.allTextures.indexEndColorAppStartColorAppTile; l < information.allTextures.indexEndColorAppTileStartMiscTexture; l++)
				information.allTextures.tabTexture[l]->renderTextureTestString(information.ecran.renderer, "ColorPlayerTile" + to_string(_tiles[i].appartenance) + ".bmp", _tiles[i].tile_x, _tiles[i].tile_y);
		}
	}
}

void Cities::foodNextTurn(){
	double foodLimitPerLevelCurrent = 15 + (_nbpop - 1) * 6 + pow((_nbpop - 1), 1.8);
	double foodLimitPerLevelMinusOne = 15 + (_nbpop - 1 - 1) * 6 + pow((_nbpop - 1 - 1), 1.8);
	double sommeFoodCitizen = 0;
	bool change = false;

	
	_foodStock += _foodBalance ;
	cout << endl << "food = " << _foodStock;
	cout << endl << "level = " << _nbpop;
	cout << endl << "nbcitizen = " << _citizens.size();
	
	if (_foodStock < 0){
		_nbpop--;
		_citizens.pop_back();
		_foodStock = foodLimitPerLevelMinusOne;
		change = true;
	}
	else if (_foodStock >= foodLimitPerLevelCurrent){
		_nbpop++;
		Citizen c(_tiles, _citizens);
		_citizens.push_back(c);
		_foodStock -= foodLimitPerLevelCurrent;
		change = true;
	}
	if (change){
		for (unsigned int i = 0; i < _citizens.size(); i++)
			sommeFoodCitizen += _citizens[i].GETfood();
		_foodBalance = sommeFoodCitizen - (2 * (_nbpop - 1));
	}
}



int Cities::testPos(int mouse_x, int mouse_y) {
	if (_x == mouse_x && _y == mouse_y)
		return 1;
	return 0;
}

unsigned int Cities::GETx()const{
	return _x;
}
unsigned int Cities::GETy()const{
	return _y;
}
