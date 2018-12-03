/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.13

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

#include "Units.h"
#include "IHM.h"

Units::Units() : _name(""), _x(0), _y(0), _life(100), _atq(10), _def(5), _movement(1), _level(1), _alive(true)
{
	IHM::logfileconsole("Create Unit Par Defaut Success");
}
Units::Units(const std::string &name, unsigned int x, unsigned int y, unsigned int life, unsigned int atq,
	unsigned int def, unsigned int move, unsigned int level)
	: _name(name), _x(x), _y(y),
	_maxlife(life), _maxatq(atq), _maxdef(def), _maxmovement(move), _maxlevel(level),
	_life(life), _atq(atq), _def(def), _movement(move), _level(level), _alive(true), _blit(0), _show(true)
{
	IHM::logfileconsole("Create Unit:  Success");
}

Units::~Units(){

}

void Units::loadUnitAndSpec(Sysinfo& sysinfo) {
	std::ifstream UNIT("bin/UNIT.txt");
	if (UNIT) {
		std::string destroy;
		Unit_Struct currentUnit;

		UNIT >> destroy;
		UNIT >> sysinfo.var.s_player.unitNameMaxToCreate;

		for (unsigned int i = 0; i < sysinfo.var.s_player.unitNameMaxToCreate; i++) {
			UNIT >> destroy;
			UNIT >> currentUnit.name;

			UNIT >> destroy;
			UNIT >> currentUnit.life;

			UNIT >> destroy;
			UNIT >> currentUnit.atq;

			UNIT >> destroy;
			UNIT >> currentUnit.def;

			UNIT >> destroy;
			UNIT >> currentUnit.movement;

			UNIT >> destroy;
			UNIT >> currentUnit.level;
			sysinfo.var.s_player.tabUnit_Struct.push_back(currentUnit);
		}

	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier bin/UNIT.txt");
}
void Units::searchunit(Sysinfo& sysinfo) {
	sysinfo.var.s_player.unitNameToCreate = sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate].name;
}
void Units::searchUnittile(Sysinfo& sysinfo) {
	for (unsigned int i = 0; i < sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabunit().size(); i++) {
		if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(i)->testPos(sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y())) {
			sysinfo.var.s_player.selectunit = i;
			sysinfo.var.s_player.unitNameToMove = sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(i)->GETname();
			sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(i)->SETblit(true);
			break;
		}
	}
}
void Units::tryToMove(Sysinfo& sysinfo, int x, int y) {
	switch (searchToMove(sysinfo, x, y)) {
	case 0:
		break;
	case 1:
		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->move(sysinfo.var.select, sysinfo.var.s_player.selectunit, x, y);
		break;
	case 2:
		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->attack(sysinfo.tabplayer[sysinfo.var.s_player.selectPlayerToAttack]->GETtheunit(sysinfo.var.s_player.selectUnitToAttack));
		if (sysinfo.tabplayer[sysinfo.var.s_player.selectPlayerToAttack]->GETtheunit(sysinfo.var.s_player.selectUnitToAttack)->GETalive() == false) {
			sysinfo.tabplayer[sysinfo.var.s_player.selectPlayerToAttack]->deleteUnit(sysinfo.var.s_player.selectUnitToAttack);
			tryToMove(sysinfo, x, y);
		}
		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->SETmovement(0);
		break;
	}
}
int Units::searchToMove(Sysinfo& sysinfo, int x, int y) {
	/*
		conditions de mouvement :
			- que la case cible soit du sol et
					- que la case cible est libre
					- ou que la case cible est occupée par un ennemi susceptible de mourrir par l'attaque

	*/
	bool ground = false;

	for (unsigned int i = 0; i < sysinfo.map.screen.size(); i++) {
		for (unsigned int j = 0; j < sysinfo.map.screen[i].size(); j++) {
			if (sysinfo.map.screen[i][j].tile_x == sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->GETx() + x &&
				sysinfo.map.screen[i][j].tile_y == sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->GETy() + y) {
				if (sysinfo.map.screen[i][j].tile_ground == grass) {
					ground = true;
					break;
				}
			}
		}
	}

	if (ground) {
		for (unsigned int i = 0; i < sysinfo.tabplayer.size(); i++) {
			for (unsigned int j = 0; j < sysinfo.tabplayer[i]->GETtabunit().size(); j++) {
				if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->GETx() + x == sysinfo.tabplayer[i]->GETtheunit(j)->GETx()) {
					if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->GETy() + y == sysinfo.tabplayer[i]->GETtheunit(j)->GETy()) {
						if (sysinfo.var.s_player.selectplayer == (int)i)
							return 0;
						else {
							sysinfo.var.s_player.selectPlayerToAttack = (int)i;
							sysinfo.var.s_player.selectUnitToAttack = (int)j;
							return 2;
						}
					}
				}
			}
		}
	}
	else
		return 0;
	return 1;
}
bool Units::irrigate(Sysinfo&) {
	return false;
}





void Units::attack(Units* cible){
	if (_movement > 0) 
		cible->defend(_atq);
}
void Units::defend(unsigned int dmg){
	int test = 0;
	if (dmg > _def) {
		if ((test = (_life - (dmg - _def))) <= 0) {
			_life = 0;
			_alive = false;
		}
		else
			_life -= (dmg - _def);
	}	
}
void Units::heal(std::vector<std::vector<Tile>>& tiles, unsigned int selectplayer){
	for (unsigned int i = 0; i < tiles.size(); i++) {
		for (unsigned int j = 0; j < tiles[i].size(); j++) {
			if (_x == tiles[i][j].tile_x && _y == tiles[i][j].tile_y) {
				if (tiles[i][j].appartenance == -1) {
					_life += (unsigned int)ceil(_maxlife / 20);
					if (_life > _maxlife)
						_life = _maxlife;
					return;
				}
				else if (tiles[i][j].appartenance == (int)selectplayer) {
					_life += (unsigned int)ceil(_maxlife / 5);
					if (_life > _maxlife)
						_life = _maxlife;
					return;
				}
				else
					return;
			}
		}
	}
}
void Units::move(Uint8& select, int& selectunit, int x, int y){
	if (_movement > 0) {
		_x += x;
		_y += y;
		_movement--;
		
	}
	if (_movement == 0) {
		select = selectnothing;
		selectunit = -1;
		_blit = 0;
		_show = true;
	}
		
}
void Units::levelup(){
	_level++;
	//heal();
}
void Units::RESETmovement() {
	_movement = _maxmovement;
}
int Units::testPos(unsigned int mouse_x, unsigned int mouse_y) {
	if (_x == mouse_x && _y == mouse_y)
		return 1;
	return 0;
}
void Units::afficher(Sysinfo& sysinfo){
	if (_show) {
		for (unsigned int i = 0; i < sysinfo.allTextures.unit.size(); i++)
			sysinfo.allTextures.unit[i]->renderTextureTestString(sysinfo.screen.renderer, _name, _x, _y);
		//logfileconsole("Afficher Unit Success");
	}
}
void Units::afficherBardeVie(Sysinfo& sysinfo){
	if (_show) {
		if (_life == _maxlife) {
			for (unsigned int i = 0; i < sysinfo.allTextures.barLife.size(); i++)
				sysinfo.allTextures.barLife[i]->renderTextureTestString(sysinfo.screen.renderer, "maxlife.bmp", _x + (sysinfo.map.tileSize / 2) - 4, _y + sysinfo.map.tileSize);
		}
		else if (_life < _maxlife && _life >= (_maxlife - ceil(_maxlife * 0.1))){
			for (unsigned int i = 0; i < sysinfo.allTextures.barLife.size(); i++)
				sysinfo.allTextures.barLife[i]->renderTextureTestString(sysinfo.screen.renderer, "0.9life.bmp", _x + (sysinfo.map.tileSize / 2) - 4, _y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.1)) && _life >= (_maxlife - ceil(_maxlife * 0.2))) {
			for (unsigned int i = 0; i < sysinfo.allTextures.barLife.size(); i++)
				sysinfo.allTextures.barLife[i]->renderTextureTestString(sysinfo.screen.renderer, "0.8life.bmp", _x + (sysinfo.map.tileSize / 2) - 4, _y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.2)) && _life >= (_maxlife - ceil(_maxlife * 0.3))) {
			for (unsigned int i = 0; i < sysinfo.allTextures.barLife.size(); i++)
				sysinfo.allTextures.barLife[i]->renderTextureTestString(sysinfo.screen.renderer, "0.7life.bmp", _x + (sysinfo.map.tileSize / 2) - 4, _y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.3)) && _life >= (_maxlife - ceil(_maxlife * 0.4))) {
			for (unsigned int i = 0; i < sysinfo.allTextures.barLife.size(); i++)
				sysinfo.allTextures.barLife[i]->renderTextureTestString(sysinfo.screen.renderer, "0.6life.bmp", _x + (sysinfo.map.tileSize / 2) - 4, _y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.4)) && _life >= (_maxlife - ceil(_maxlife * 0.5))) {
			for (unsigned int i = 0; i < sysinfo.allTextures.barLife.size(); i++)
				sysinfo.allTextures.barLife[i]->renderTextureTestString(sysinfo.screen.renderer, "0.5life.bmp", _x + (sysinfo.map.tileSize / 2) - 4, _y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.5)) && _life >= (_maxlife - ceil(_maxlife * 0.6))) {
			for (unsigned int i = 0; i < sysinfo.allTextures.barLife.size(); i++)
				sysinfo.allTextures.barLife[i]->renderTextureTestString(sysinfo.screen.renderer, "0.4life.bmp", _x + (sysinfo.map.tileSize / 2) - 4, _y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.6)) && _life >= (_maxlife - ceil(_maxlife * 0.7))) {
			for (unsigned int i = 0; i < sysinfo.allTextures.barLife.size(); i++)
				sysinfo.allTextures.barLife[i]->renderTextureTestString(sysinfo.screen.renderer, "0.3life.bmp", _x + (sysinfo.map.tileSize / 2) - 4, _y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.7)) && _life >= (_maxlife - ceil(_maxlife * 0.8))) {
			for (unsigned int i = 0; i < sysinfo.allTextures.barLife.size(); i++)
				sysinfo.allTextures.barLife[i]->renderTextureTestString(sysinfo.screen.renderer, "0.2life.bmp", _x + (sysinfo.map.tileSize / 2) - 4, _y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.8)) && _life >= (_maxlife - ceil(_maxlife * 0.9))) {
			for (unsigned int i = 0; i < sysinfo.allTextures.barLife.size(); i++)
				sysinfo.allTextures.barLife[i]->renderTextureTestString(sysinfo.screen.renderer, "0.1life.bmp", _x + (sysinfo.map.tileSize / 2) - 4, _y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.9))) {
			for (unsigned int i = 0; i < sysinfo.allTextures.barLife.size(); i++)
				sysinfo.allTextures.barLife[i]->renderTextureTestString(sysinfo.screen.renderer, "0.0life.bmp", _x + (sysinfo.map.tileSize / 2) - 4, _y + sysinfo.map.tileSize);
		}
	}
}
void Units::afficherstat(Sysinfo& sysinfo) {
	if (_show) {
		int initspace = _y, space = 14;
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "Name: "  + _name, { 0, 64, 255, 255 }, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "X: " + std::to_string(_x), { 0, 64, 255, 255 }, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "Y: " + std::to_string(_y), { 0, 64, 255, 255 }, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "life: " + std::to_string(_life), { 0, 64, 255, 255 }, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "atq: " + std::to_string(_atq), { 0, 64, 255, 255 }, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "def: " + std::to_string(_def), { 0, 64, 255, 255 }, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "movement: " + std::to_string(_movement), { 0, 64, 255, 255 }, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "level: " + std::to_string(_level), { 0, 64, 255, 255 }, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space);
	}
}
void Units::cmpblit() {
	/*
		50% off 50% on , environ 1s le cycle
		probablement à changer dans le futur???
	*/
	if (_blit < 2000) {
		_blit++;
		_show = false;
	}
	else if (_blit >= 2000 && _blit < 4000) {
		_blit++;
		_show = true;
	}
	else if(_blit >= 4000)
		_blit = 0;
}
std::string Units::GETname() const{
	return _name;
}
unsigned int Units::GETx() const {
	return _x;
}
unsigned int Units::GETy() const {
	return _y;
}
unsigned int Units::GETmaxlife() const {
	return _maxlife;
}
unsigned int Units::GETmaxatq() const {
	return _maxatq;
}
unsigned int Units::GETmaxdef() const {
	return _maxdef;
}
unsigned int Units::GETmaxmovement() const {
	return _maxmovement;
}
unsigned int Units::GETmaxlevel() const {
	return _maxlevel;
}
unsigned int Units::GETlife() const{
	return _life;
}
unsigned int Units::GETatq() const{
	return _atq;
}
unsigned int Units::GETdef() const{
	return _def;
}
unsigned int Units::GETmovement() const{
	return _movement;
}
unsigned int Units::GETlevel() const{
	return _level;
}
bool Units::GETalive() const{
	return _life; //Renvoie true is m_life > 0 et false sinon.
}
bool Units::GETblit() const {
	return _blit;
}
void Units::SETname(const std::string &msg){
	_name = msg;
}
void Units::SETlife(unsigned int life){
	_life = life;
}
void Units::SETx(unsigned int x) {
	_x = x;
}
void Units::SETy(unsigned int y){
	_y = y;
}
void Units::SETatq(unsigned int atq){
	_atq = atq;
}
void Units::SETdef(unsigned int def){
	_def = def;
}
void Units::SETmovement(unsigned int movement){
	_movement = movement;
}
void Units::SETlevel(unsigned int level){
	_level = level;
}
void Units::SETalive(bool alive){
	_alive = alive;
}
void Units::SETblit(bool blit) {
	_blit = blit;
}
