/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.14
	file version : 1.1

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

#include "Cities.h"
#include "HashTable.h"
#include "IHM.h"

Cities::Cities(const std::string& name, unsigned int x, unsigned int y, Tile tile[]) : _image("citie.png"),
_name(name), _x(x), _y(y), _tile(createtiles(tile)), _citizens(createCitizen(tile[(unsigned int)ceil((initSizeView*initSizeView) / 2)])),
_influenceLevel(1),_nbpop(1), _atq(0), _def(0), _nbhappy(0), _nbsad(0), _nbstructurebuild(0),
_foodStock(0), _foodBalance(tile[(unsigned int)ceil((initSizeView*initSizeView) / 2)].food)
{
	IHM::logfileconsole("Create Citie: " + _name + " Success");
}
Cities::~Cities()
{
	IHM::logfileconsole("Destroy Citie: " + _name + " Success");
}

void Cities::createcitie(Sysinfo& sysinfo)
{
	if (sysinfo.var.s_player.unitNameToMove.compare("settler") == 0)
	{

		std::string name = sysinfo.var.s_player.tabCitieName[(sysinfo.var.s_player.selectplayer * 5) + sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabcities().size()];
		unsigned int x = sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->GETx();
		unsigned int y = sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->GETy();

		unsigned int middletileX = 0, middletileY = 0;

		Tile tabtile[initSizeView*initSizeView];
		for (unsigned int i = 0; i < sysinfo.map.maps.size(); i++)
		{
			for (unsigned int j = 0; j < sysinfo.map.maps.size(); j++)
			{
				if (sysinfo.map.maps[i][j].tile_x == x && sysinfo.map.maps[i][j].tile_y == y)
				{
					middletileX = i;
					middletileY = j;
					break;
				}
			}
		}
		unsigned int k = 0;
		for (int o = -(int)ceil(initSizeView / 2); o <= (int)ceil(initSizeView / 2); o++)
		{
			for (int p = -(int)ceil(initSizeView / 2); p <= (int)ceil(initSizeView / 2); p++)
			{
				if (o > -initSizeInfluence && o < initSizeInfluence && p > -initSizeInfluence && p < initSizeInfluence)
					sysinfo.map.maps[middletileX + o][middletileY + p].appartenance = sysinfo.var.s_player.selectplayer;
				tabtile[k] = sysinfo.map.maps[middletileX + o][middletileY + p];
				tabtile[k].tile_x = (SCREEN_WIDTH / 2) - (-o * sysinfo.map.tileSize);
				tabtile[k].tile_y = (SCREEN_HEIGHT / 2) - (-p * sysinfo.map.tileSize);
				k++;
			}
		}

		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->addCitie(name, x, y, tabtile);

		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->deleteUnit(sysinfo.var.s_player.selectunit);
		sysinfo.var.s_player.selectunit = -1;
		sysinfo.var.s_player.unitNameToMove = "";
	}
}
void Cities::searchCitietile(Sysinfo& sysinfo)
{
	for (unsigned int i = 0; i < sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabcities().size(); i++) 
	{
		if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETthecitie(i)->testPos(sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
		{
			sysinfo.var.s_player.selectCitie = i;
			sysinfo.var.statescreen = STATEcitiemap;
			sysinfo.var.select = selectnothing;
			break;
		}
	}
}
std::vector<Tile> createtiles(Tile tiles[])
{
	std::vector<Tile> Atiles;
	for (unsigned int i = 0; i < initSizeView*initSizeView; i++)
		Atiles.push_back(tiles[i]);
	return Atiles;
}
std::vector<Citizen> createCitizen(Tile tiles)
{
	std::vector<Citizen> Acitizen;
	Citizen acitizen(tiles);
	Acitizen.push_back(acitizen);	
	return Acitizen;
}
void Cities::afficher(Sysinfo& sysinfo)
{
	sysinfo.allTextures.miscTexture[searchIndex(_image, sysinfo.allTextures.miscTexture)]->render(_x, _y);

	sysinfo.allTextes.mainMap[searchIndex(_name, sysinfo.allTextes.mainMap)]->render(_x, _y);
}
void Cities::affichercitiemap(Sysinfo& sysinfo)
{
	for (unsigned int i = 0; i < initSizeView*initSizeView; i++) 
	{
		if (_tile[i].tile_stringground.compare("grass.bmp") == 0)
			sysinfo.allTextures.ground[0]->render(_tile[i].tile_x, _tile[i].tile_y);
		else if (_tile[i].tile_stringground.compare("water.bmp") == 0)
			sysinfo.allTextures.ground[1]->render(_tile[i].tile_x, _tile[i].tile_y);

		if (_tile[i].tile_spec != 0) 
		{
			for (unsigned int l = 0; l < sysinfo.allTextures.groundSpec.size(); l++)
				sysinfo.allTextures.groundSpec[l]->renderTextureTestString(_tile[i].tile_stringspec, _tile[i].tile_x, _tile[i].tile_y);
		}
		if (_tile[i].appartenance != -1)
		{
			for (unsigned int l = 0; l < sysinfo.allTextures.colorapptile.size(); l++)
				sysinfo.allTextures.colorapptile[l]->renderTextureTestString("ColorPlayertile" + std::to_string(_tile[i].appartenance) + ".bmp", _tile[i].tile_x, _tile[i].tile_y);
		}
	}
}
void Cities::foodNextTurn()
{
	double foodLimitPerLevelCurrent = 15 + (_nbpop - 1) * 6 + pow((_nbpop - 1), 1.8);
	double foodLimitPerLevelMinusOne = 15 + (_nbpop - 1 - 1) * 6 + pow((_nbpop - 1 - 1), 1.8);
	double sommeFoodCitizen = 0;
	bool change = false;

	
	_foodStock += _foodBalance ;
	std::cout << std::endl << "food = " << _foodStock;
	std::cout << std::endl << "level = " << _nbpop;
	std::cout << std::endl << "nbcitizen = " << _citizens.size();
	
	if (_foodStock < 0
		){
		_nbpop--;
		_citizens.pop_back();
		_foodStock = foodLimitPerLevelMinusOne;
		change = true;
	}
	else if (_foodStock >= foodLimitPerLevelCurrent)
	{
		_nbpop++;
		Citizen c(_tile, _citizens);
		_citizens.push_back(c);
		_foodStock -= foodLimitPerLevelCurrent;
		change = true;
	}
	if (change)
	{
		for (unsigned int i = 0; i < _citizens.size(); i++)
			sommeFoodCitizen += _citizens[i].GETfood();
		_foodBalance = sommeFoodCitizen - (2 * (_nbpop - 1));
	}
}
int Cities::testPos(unsigned int mouse_x, unsigned int mouse_y)
{
	if (_x == mouse_x && _y == mouse_y)
		return 1;
	return 0;
}






Citizen::Citizen() : _tileOccupied((unsigned int)ceil((initSizeView*initSizeView) / 2)), _happiness(1), _food(2), _work(1), _gold(1), _revolt(0), _religious(false), _place(false)
{
	IHM::logfileconsole("Create Citizen par défaut Success");
}
Citizen::Citizen(Tile tile) : _tileOccupied((unsigned int)ceil((initSizeView*initSizeView) / 2)), _happiness(1), _food(tile.food), _work(tile.work), _gold(tile.gold), _revolt(0), _religious(false), _place(true)
{
	IHM::logfileconsole("Create Citizen Success");
}
Citizen::Citizen(std::vector<Tile> tile, std::vector<Citizen> citizens) : _tileOccupied(placeCitizen(tile, citizens, _food, _work, _gold)), _happiness(1), _revolt(0), _religious(false), _place(true)
{
	IHM::logfileconsole("Create Citizen Success");
}
Citizen::~Citizen()
{
	IHM::logfileconsole("Kill Citizen Success");
}
unsigned int placeCitizen(std::vector<Tile> tile, std::vector<Citizen> citizens, int& _food, int& _work, int& _gold)
{
	unsigned int condition = citizens.size();
	unsigned int checkcondition = 0;
	unsigned int place = 0;

	std::vector<unsigned int> tabpos;
	for (unsigned int j = 0; j < condition; j++)
	{
		tabpos.push_back(citizens[j].GETtileOccupied());
	}
	for (unsigned int i = 0; i < initSizeView*initSizeView; i++)
	{
		for (unsigned int p = 0; p < condition; p++)
		{
			checkcondition = 0;
			if (i != tabpos[p])
				checkcondition++;
			if (checkcondition == condition)
				place = i;
		}
	}
	_food = tile[place].food;
	_work = tile[place].work;
	_gold = tile[place].gold;
	return place;
}


/*
*	End Of File
*/