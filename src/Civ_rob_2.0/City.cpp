/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.17
	file version : 1.4

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

#include "City.h"
#include "IHM.h"

/* *********************************************************
 *					START City::STATIC					   *
 ********************************************************* */

 
 
/*
* NAME : createCity
* ROLE : Création d'une City à partir d'un settler sur la carte
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Création d'une City
* RETURNED VALUE    : void
*/
void City::createCity(Sysinfo& sysinfo)
{
	if (sysinfo.var.s_player.unitNameToMove.compare("settler") == 0)
	{

		std::string name(sysinfo.var.s_player.tabCitieName[(sysinfo.var.s_player.selectplayer * 5) + sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabCity().size()]);
		unsigned int x(sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(sysinfo.var.s_player.selectunit)->GETx());
		unsigned int y(sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(sysinfo.var.s_player.selectunit)->GETy());

		unsigned int middletileX = 0, middletileY = 0;

		Tile tabtile[initSizeView*initSizeView];
		for (unsigned int i(0); i < sysinfo.map.maps.size(); i++)
		{
			for (unsigned int j(0); j < sysinfo.map.maps.size(); j++)
			{
				if (sysinfo.map.maps[i][j].tile_x == x && sysinfo.map.maps[i][j].tile_y == y)
				{
					middletileX = i;
					middletileY = j;
					break;
				}
			}
		}
		unsigned int k(0);
		for (int o(-(int)ceil(initSizeView / 2)); o <= (int)ceil(initSizeView / 2); o++)
		{
			for (int p(-(int)ceil(initSizeView / 2)); p <= (int)ceil(initSizeView / 2); p++)
			{
				if (o > -initSizeInfluence && o < initSizeInfluence && p > -initSizeInfluence && p < initSizeInfluence)
					sysinfo.map.maps[middletileX + o][middletileY + p].appartenance = sysinfo.var.s_player.selectplayer;
				tabtile[k] = sysinfo.map.maps[middletileX + o][middletileY + p];
				tabtile[k].tile_x = (sysinfo.screen.screenWidth / 2) - (-o * sysinfo.map.tileSize);
				tabtile[k].tile_y = (sysinfo.screen.screenHeight / 2) - (-p * sysinfo.map.tileSize);
				k++;
			}
		}

		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->addCity(name, x, y, tabtile);

		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->deleteUnit(sysinfo.var.s_player.selectunit);
		sysinfo.var.s_player.selectunit = -1;
		sysinfo.var.s_player.unitNameToMove = "";
	}
}

		
/*
* NAME : searchCityTile
* ROLE : Recherche la case de la City et renvoie vers cityMap
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : la case de la City et renvoie vers cityMap
* RETURNED VALUE    : void
*/
void City::searchCityTile(Sysinfo& sysinfo)
{
	for (unsigned int i(0); i < sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabCity().size(); i++) 
	{
		if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheCity(i)->testPos(sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y()))
		{
			sysinfo.var.s_player.selectCitie = i;
			sysinfo.var.statescreen = STATEcitiemap;
			sysinfo.var.select = selectnothing;
			break;
		}
	}
}

/*
* NAME : createTiles
* ROLE : Création d'un tableau de Tile pour la City
* INPUT  PARAMETERS : Tile tile[] : données générale de la map
* OUTPUT PARAMETERS : std::vector<Tile>
* RETURNED VALUE    : std::vector<Tile> : données générale de la cityMap
*/
std::vector<Tile> City::createTiles(Tile tiles[])
{
	std::vector<Tile> Atiles;
	for (unsigned int i(0); i < initSizeView*initSizeView; i++)
		Atiles.push_back(tiles[i]);
	return Atiles;
}

/*
* NAME : createCitizen
* ROLE : Création d'un Citizen sur une case précise
* INPUT  PARAMETERS : Tile tile : données d'une case
* OUTPUT PARAMETERS : std::vector<Citizen>
* RETURNED VALUE    : std::vector<Citizen> : ajout du Citizen
*/
std::vector<Citizen> City::createCitizen(Tile tiles)
{
	std::vector<Citizen> Acitizen;
	Citizen acitizen(tiles);
	Acitizen.push_back(acitizen);	
	return Acitizen;
}


/* *********************************************************
 *					END City::STATIC					   *
 ********************************************************* */


 
/* *********************************************************
 *					START City::METHODS					   *
 ********************************************************* */


City::City(const std::string& name, unsigned int x, unsigned int y, Tile tile[]) : _image("citie.png"),
_name(name), _x(x), _y(y), _tile(createTiles(tile)), _citizens(createCitizen(tile[(unsigned int)ceil((initSizeView*initSizeView) / 2)])),
_influenceLevel(1),_nbpop(1), _atq(0), _def(0), _nbhappy(0), _nbsad(0), _nbstructurebuild(0),
_foodStock(0), _foodBalance(tile[(unsigned int)ceil((initSizeView*initSizeView) / 2)].food)
{
	IHM::logfileconsole("[INFO]___: Create Citie: " + _name + " Success");
}
City::~City()
{
	IHM::logfileconsole("[INFO]___: Destroy Citie: " + _name + " Success");
}

/*
* NAME : foodNextTurn
* ROLE : Calcul et application du niveau de Food pour le prochain tour
* INPUT  PARAMETERS : void
* OUTPUT PARAMETERS : Calcul et application du niveau de Food
* RETURNED VALUE    : void
*/
void City::foodNextTurn()
{
	double foodLimitPerLevelCurrent(15 + (_nbpop - 1) * 6 + pow((_nbpop - 1), 1.8));
	double foodLimitPerLevelMinusOne(15 + (_nbpop - 1 - 1) * 6 + pow((_nbpop - 1 - 1), 1.8));
	double sommeFoodCitizen(0);
	bool change(false);

	
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
		for (unsigned int i(0); i < _citizens.size(); i++)
			sommeFoodCitizen += _citizens[i].GETfood();
		_foodBalance = sommeFoodCitizen - (2 * (_nbpop - 1));
	}
}

/*
* NAME : testPos
* ROLE : Retourne si la position est valide
* INPUT  PARAMETERS : unsigned int x, unsigned int y : position de la souris
* OUTPUT PARAMETERS : Retourne si la position est valide
* RETURNED VALUE    : int : 0 : pas valide / 1 : valide
*/
int City::testPos(unsigned int mouse_x, unsigned int mouse_y)
{
	if (_x == mouse_x && _y == mouse_y)
		return 1;
	return 0;
}

/* *********************************************************
 *					END City::METHODS					   *
 ********************************************************* */

 
 
/* *********************************************************
 *				START City::METHODS::Affichage			   *
 ********************************************************* */


 /*
* NAME : afficher
* ROLE : Affichage de la City (Texture et nom)
* INPUT  PARAMETERS : truct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Affichage de la City (Texture et nom)
* RETURNED VALUE    : void
*/
void City::afficher(Sysinfo& sysinfo)
{
	unsigned int x(_x - sysinfo.map.screenOffsetXIndexMin * sysinfo.map.tileSize);
	unsigned int y(_y - sysinfo.map.screenOffsetYIndexMin * sysinfo.map.tileSize);

	sysinfo.allTextures.citieMap[_image]->render(x, y);

	sysinfo.allTextes.mainMap[_name]->render(x + sysinfo.map.tileSize / 2, y + sysinfo.map.tileSize);

	sysinfo.allTextes.number[std::to_string((unsigned int)floor(_nbpop))]->render(x + sysinfo.map.tileSize / 2 - 20, y + sysinfo.map.tileSize - 6);
}

/*
* NAME : affichercitiemap
* ROLE : Affichage des cases qui compose le secteur de la City
* INPUT  PARAMETERS : truct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Affichage des cases de la City
* RETURNED VALUE    : void
*/
void City::affichercitiemap(Sysinfo& sysinfo)
{
	for (unsigned int i(0); i < initSizeView*initSizeView; i++) 
	{
		switch (_tile[i].tile_ground)
		{
		case grass:
			sysinfo.allTextures.ground["grass.bmp"]->render(_tile[i].tile_x, _tile[i].tile_y);
			break;
		case water:
			sysinfo.allTextures.ground["water.bmp"]->render(_tile[i].tile_x, _tile[i].tile_y);
			break;
		}



		if (_tile[i].tile_spec > 0) 
		{
			sysinfo.allTextures.groundSpec[_tile[i].tile_stringspec]->render(_tile[i].tile_x, _tile[i].tile_y);
		}
		if (_tile[i].appartenance != -1)
		{
			sysinfo.allTextures.colorapptile["ColorPlayertile" + std::to_string(_tile[i].appartenance) + ".bmp"]->render(_tile[i].tile_x, _tile[i].tile_y);
		}
	}
}

/* *********************************************************
 *				END City::METHODS::Affichage			   *
 ********************************************************* */








/* *********************************************************
 *					START Citizen::STATIC				   *
 ********************************************************* */

/*
* NAME : placeCitizen
* ROLE : Placement d'un Citizen en fonction des cases occupées de la City
* INPUT  PARAMETERS : std::vector<Tile> : carte de la City
* INPUT  PARAMETERS : std::vector<Citizen> : tableau de Citizen
* INPUT  PARAMETERS : int& _food, int& _work, int& _gold : spec de la case
* OUTPUT PARAMETERS : Placement d'un Citizen
* RETURNED VALUE    : unsigned int : la place allouée
*/
unsigned int Citizen::placeCitizen(std::vector<Tile> tile, std::vector<Citizen> citizens, int& _food, int& _work, int& _gold)
{
	unsigned int condition(citizens.size());
	unsigned int checkcondition(0);
	unsigned int place(0);

	std::vector<unsigned int> tabpos;
	for (unsigned int j(0); j < condition; j++)
	{
		tabpos.push_back(citizens[j].GETtileOccupied());
	}
	for (unsigned int i(0); i < initSizeView*initSizeView; i++)
	{
		for (unsigned int p(0); p < condition; p++)
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


/* *********************************************************
 *					END Citizen::STATIC					   *
 ********************************************************* */
 
 
 
/* *********************************************************
 *					START Citizen::METHODS				   *
 ********************************************************* */
 
Citizen::Citizen() : _tileOccupied((unsigned int)ceil((initSizeView*initSizeView) / 2)), _happiness(1), _food(2), _work(1), _gold(1), _revolt(0), _religious(false), _place(false)
{
	IHM::logfileconsole("[INFO]___: Create Citizen par défaut Success");
}
Citizen::Citizen(Tile tile) : _tileOccupied((unsigned int)ceil((initSizeView*initSizeView) / 2)), _happiness(1), _food(tile.food), _work(tile.work), _gold(tile.gold), _revolt(0), _religious(false), _place(true)
{
	IHM::logfileconsole("[INFO]___: Create Citizen Success");
}
Citizen::Citizen(std::vector<Tile> tile, std::vector<Citizen> citizens) : _tileOccupied(placeCitizen(tile, citizens, _food, _work, _gold)), _happiness(1), _revolt(0), _religious(false), _place(true)
{
	IHM::logfileconsole("[INFO]___: Create Citizen Success");
}
Citizen::~Citizen()
{
	IHM::logfileconsole("[INFO]___: Kill Citizen Success");
}

/* *********************************************************
 *					END Citizen::METHODS				   *
 ********************************************************* */


/*
*	End Of File City.cpp
*/