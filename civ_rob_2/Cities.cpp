/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.12

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
#include "IHM.h"

Cities::Cities(const std::string& name, unsigned int x, unsigned int y, tile tiles[]) : _image("citie.png"),
_name(name), _x(x), _y(y), _tiles(createTiles(tiles)), _citizens(createCitizen(tiles[(unsigned int)ceil((initSizeView*initSizeView) / 2)])),
_influenceLevel(1),_nbpop(1), _atq(0), _def(0), _nbhappy(0), _nbsad(0), _nbstructurebuild(0),
_foodStock(0), _foodBalance(tiles[(unsigned int)ceil((initSizeView*initSizeView) / 2)].food)
{
	IHM::logfileconsole("Create Citie: " + _name + " Success");
}
Cities::~Cities()
{
	IHM::logfileconsole("Destroy Citie: " + _name + " Success");
}

void Cities::createcitie(sysinfo& information, std::vector<Player*>& tabplayer) {
	if (information.variable.s_player.unitNameToMove.compare("settler") == 0) {

		std::string name = information.variable.s_player.tabCitieName[(information.variable.s_player.selectplayer * 5) + tabplayer[information.variable.s_player.selectplayer]->GETtabcities().size()];
		int x = tabplayer[information.variable.s_player.selectplayer]->GETtheunit(information.variable.s_player.selectunit)->GETx();
		int y = tabplayer[information.variable.s_player.selectplayer]->GETtheunit(information.variable.s_player.selectunit)->GETy();

		unsigned int middleTile = 0;

		tile tabtile[initSizeView*initSizeView];
		for (unsigned int i = 0; i < information.maps.maps.size(); i++) {
			if (information.maps.maps[i].tile_x == x && information.maps.maps[i].tile_y == y) {
				middleTile = i;
				break;
			}
		}
		int o = (int)floor((double)initSizeView / 2.0);
		for (int z = -(int)floor((double)initSizeView / 2.0); z < (int)ceil((double)initSizeView / 2.0); z++) {
			o = (int)floor((double)initSizeView / 2.0);
			for (int i = (initSizeView * (z + (int)floor((double)initSizeView / 2.0))); i < (initSizeView * (z + (int)ceil((double)initSizeView / 2.0))); i++) {
				if (o > -initSizeInfluence && o < initSizeInfluence && z > -initSizeInfluence && z < initSizeInfluence)
					information.maps.maps[middleTile - z - (o * (information.maps.mapSize / information.maps.tileSize))].appartenance = information.variable.s_player.selectplayer;
				tabtile[i] = information.maps.maps[middleTile - z - (o * (information.maps.mapSize / information.maps.tileSize))];
				tabtile[i].tile_x = (SCREEN_WIDTH / 2) - (o * information.maps.tileSize);
				tabtile[i].tile_y = (SCREEN_HEIGHT / 2) - (z * information.maps.tileSize);
				o--;
			}
		}
		tabplayer[information.variable.s_player.selectplayer]->addCitie(name, x, y, tabtile);

		tabplayer[information.variable.s_player.selectplayer]->deleteUnit(information.variable.s_player.selectunit);
		information.variable.s_player.selectunit = -1;
		information.variable.s_player.unitNameToMove = "";
	}
}
void Cities::searchCitieTile(sysinfo& information, std::vector<Player*>& tabplayer) {
	for (unsigned int i = 0; i < tabplayer[information.variable.s_player.selectplayer]->GETtabcities().size(); i++) {
		if (tabplayer[information.variable.s_player.selectplayer]->GETthecitie(i)->testPos(information.variable.mouse.GETmouse_x(), information.variable.mouse.GETmouse_y())) {
			information.variable.s_player.selectCitie = i;
			information.variable.statescreen = STATEcitiemap;
			information.variable.select = selectnothing;
			break;
		}
	}
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
	for (unsigned int i = 0; i < information.allTextures.miscTexture.size(); i++)
		information.allTextures.miscTexture[i]->renderTextureTestString(information.ecran.renderer, _image, _x, _y);
	for (unsigned int i = 0; i < information.allTextures.txtmainmap.size(); i++)
		information.allTextures.txtmainmap[i]->renderTextureTestString(information.ecran.renderer, _name, _x, _y + information.maps.tileSize);
}
void Cities::affichercitiemap(sysinfo& information) {
	for (unsigned int i = 0; i < initSizeView*initSizeView; i++) {
		if (_tiles[i].tile_stringground.compare("grass.bmp") == 0)
			information.allTextures.ground[0]->render(information.ecran.renderer, _tiles[i].tile_x, _tiles[i].tile_y);
		else if (_tiles[i].tile_stringground.compare("water.bmp") == 0)
			information.allTextures.ground[1]->render(information.ecran.renderer, _tiles[i].tile_x, _tiles[i].tile_y);

		if (_tiles[i].tile_spec != 0) {
			for (unsigned int l = 0; l < information.allTextures.groundSpec.size(); l++)
				information.allTextures.groundSpec[l]->renderTextureTestString(information.ecran.renderer, _tiles[i].tile_stringspec, _tiles[i].tile_x, _tiles[i].tile_y);
		}
		if (_tiles[i].appartenance != -1) {
			for (unsigned int l = 0; l < information.allTextures.colorappTile.size(); l++)
				information.allTextures.colorappTile[l]->renderTextureTestString(information.ecran.renderer, "ColorPlayerTile" + std::to_string(_tiles[i].appartenance) + ".bmp", _tiles[i].tile_x, _tiles[i].tile_y);
		}
	}
}
void Cities::foodNextTurn(){
	double foodLimitPerLevelCurrent = 15 + (_nbpop - 1) * 6 + pow((_nbpop - 1), 1.8);
	double foodLimitPerLevelMinusOne = 15 + (_nbpop - 1 - 1) * 6 + pow((_nbpop - 1 - 1), 1.8);
	double sommeFoodCitizen = 0;
	bool change = false;

	
	_foodStock += _foodBalance ;
	std::cout << std::endl << "food = " << _foodStock;
	std::cout << std::endl << "level = " << _nbpop;
	std::cout << std::endl << "nbcitizen = " << _citizens.size();
	
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





Citizen::Citizen() : _tileOccupied((unsigned int)ceil((initSizeView*initSizeView) / 2)), _happiness(1), _food(2), _work(1), _gold(1), _revolt(0), _religious(false), _place(false)
{
	IHM::logfileconsole("Create Citizen par défaut Success");
}
Citizen::Citizen(tile tiles) : _tileOccupied((unsigned int)ceil((initSizeView*initSizeView) / 2)), _happiness(1), _food(tiles.food), _work(tiles.work), _gold(tiles.gold), _revolt(0), _religious(false), _place(true)
{
	IHM::logfileconsole("Create Citizen Success");
}
Citizen::Citizen(std::vector<tile> tiles, std::vector<Citizen> citizens) : _tileOccupied(placeCitizen(tiles, citizens, _food, _work, _gold)), _happiness(1), _revolt(0), _religious(false), _place(true)
{
	IHM::logfileconsole("Create Citizen Success");
}
Citizen::~Citizen()
{
	IHM::logfileconsole("Kill Citizen Success");
}
unsigned int placeCitizen(std::vector<tile> tiles, std::vector<Citizen> citizens, int& _food, int& _work, int& _gold) {
	unsigned int condition = citizens.size();
	unsigned int checkcondition = 0;
	unsigned int place = 0;

	std::vector<unsigned int> tabpos;
	for (unsigned int j = 0; j < condition; j++) {
		tabpos.push_back(citizens[j].GETtileOccupied());
	}
	for (unsigned int i = 0; i < initSizeView*initSizeView; i++) {
		for (unsigned int p = 0; p < condition; p++) {
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
unsigned int Citizen::GETtileOccupied()const {
	return _tileOccupied;
}
int Citizen::GETfood()const {
	return _food;
}
int Citizen::GETwork()const {
	return _work;
}
int Citizen::GETgold()const {
	return _gold;
}