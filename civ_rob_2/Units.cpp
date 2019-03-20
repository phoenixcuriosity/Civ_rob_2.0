/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.15
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

#include "Units.h"
#include "IHM.h"
#include "HashTable.h"


/* *********************************************************
 *				START Units::STATIC
 ********************************************************* */


/*
* NAME : loadUnitAndSpec
* ROLE : Chargement des informations concernant les unités à partir d'un fichier
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : tableau de nom et spec concernant les unités
* RETURNED VALUE    : void
*/
void Units::loadUnitAndSpec(Sysinfo& sysinfo)
{
	std::ifstream UNIT("bin/UNIT.txt");
	if (UNIT) 
	{
		std::string destroy;
		Unit_Struct currentUnit;

		UNIT >> destroy;
		UNIT >> sysinfo.var.s_player.unitNameMaxToCreate;

		for (unsigned int i = 0; i < sysinfo.var.s_player.unitNameMaxToCreate; i++)
		{
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


/*
* NAME : searchunit
* ROLE : Sélection du nom de l'unité à partir de l'index du tableau
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : nom de l'unité
* RETURNED VALUE    : void
*/
void Units::searchunit(Sysinfo& sysinfo)
{
	sysinfo.var.s_player.unitNameToCreate = sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate].name;
}


/*
* NAME : searchUnittile
* ROLE : Cherche l'unité étant dans la case séléctionné
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : index et nom de l'unité sélectionnée
* OUTPUT PARAMETERS : activation de la méthode blit (clignotement)
* RETURNED VALUE    : void
*/
void Units::searchUnittile(Sysinfo& sysinfo)
{
	for (unsigned int i = 0; i < sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabunit().size(); i++)
	{
		if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(i)
			->testPos(sysinfo.var.mouse.GETmouse_x() + sysinfo.map.screenOffsetXIndexMin * sysinfo.map.tileSize,
				sysinfo.var.mouse.GETmouse_y() + sysinfo.map.screenOffsetYIndexMin * sysinfo.map.tileSize))
		{
			sysinfo.var.s_player.selectunit = i;
			sysinfo.var.s_player.unitNameToMove = sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(i)->GETname();
			sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(i)->SETblit(true);
			break;
		}
	}
}


/*
* NAME : tryToMove
* ROLE : Recherche à faire bouger l'unité selon le contexte
* ROLE : Attention : contient un rappel récursif
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : l'unité reste à sa place ou bouge en fonction du contexte
* RETURNED VALUE    : void
*/
void Units::tryToMove(Sysinfo& sysinfo, int x, int y)
{
	switch (searchToMove(sysinfo, x, y))
	{
	case 0:
		break;
	case 1:
		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->move(sysinfo.var.select, sysinfo.var.s_player.selectunit, x, y);
		break;
	case 2:
		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->attack(sysinfo.tabplayer[sysinfo.var.s_player.selectPlayerToAttack]->GETtheunit(sysinfo.var.s_player.selectUnitToAttack));
		if (sysinfo.tabplayer[sysinfo.var.s_player.selectPlayerToAttack]->GETtheunit(sysinfo.var.s_player.selectUnitToAttack)->GETalive() == false)
		{
			sysinfo.tabplayer[sysinfo.var.s_player.selectPlayerToAttack]->deleteUnit(sysinfo.var.s_player.selectUnitToAttack);
			tryToMove(sysinfo, x, y);
		}
		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->SETmovement(0);
		break;
	}
}


/*
* NAME : searchToMove
* ROLE : Recherche à faire bouger l'unité selon le contexte
* ROLE : Action conditionnelle (case libre, ennemi, amis)
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : l'unité reste à sa place ou bouge en fonction du contexte
* RETURNED VALUE    : int : 0 : ne bouge pas / 1 : case libre : peut bouger / 2 : ennemi : ne bouge pas
*
*/
int Units::searchToMove(Sysinfo& sysinfo, int x, int y)
{
	/*
		conditions de mouvement :
			- que la case cible soit du sol et
					- que la case cible est libre
					- ou que la case cible est occupée par un ennemi susceptible de mourrir par l'attaque

	*/
	bool ground = false;

	for (unsigned int i = 0; i < sysinfo.map.maps.size(); i++)
	{
		for (unsigned int j = 0; j < sysinfo.map.maps[i].size(); j++)
		{
			if (sysinfo.map.maps[i][j].tile_x == sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->GETx() + x &&
				sysinfo.map.maps[i][j].tile_y == sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->GETy() + y)
			{
				if (sysinfo.map.maps[i][j].tile_ground == grass)
				{
					ground = true;
					break;
				}
			}
		}
	}

	if (ground)
	{
		for (unsigned int i = 0; i < sysinfo.tabplayer.size(); i++) 
		{
			for (unsigned int j = 0; j < sysinfo.tabplayer[i]->GETtabunit().size(); j++) 
			{
				if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->GETx() + x == sysinfo.tabplayer[i]->GETtheunit(j)->GETx())
				{
					if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheunit(sysinfo.var.s_player.selectunit)->GETy() + y == sysinfo.tabplayer[i]->GETtheunit(j)->GETy())
					{
						if (sysinfo.var.s_player.selectplayer == (int)i)
							return 0;
						else
						{
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


/*
* NAME : irrigate
* ROLE :
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS :
* RETURNED VALUE    : bool
*/
bool Units::irrigate(Sysinfo&)
{
	return false;
}

/* *********************************************************
 *					END Units::STATIC
 ********************************************************* */


/* *********************************************************
 *				START Units::METHODS
 ********************************************************* */

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
Units::~Units()
{
}


/*
* NAME : attack
* ROLE : Attaque la cible avec les dommages appliqués de l'unité
* INPUT  PARAMETERS : Units* : pointeur vers l'unité qui doit se défendre
* OUTPUT PARAMETERS : Attaque d'une unité
* RETURNED VALUE    : void
*/
void Units::attack(Units* cible)
{
	if (_movement > 0) 
		cible->defend(_atq);
}


/*
* NAME : defend
* ROLE : Défense de l'unité face à une attaque
* INPUT  PARAMETERS : unsigned int : dommage appliqué par l'attaque
* OUTPUT PARAMETERS : l'unité peut prendre des dommage et/ou mourrir
* RETURNED VALUE    : void
*/
void Units::defend(unsigned int dmg)
{
	int test = 0;
	if (dmg > _def)
	{
		if ((test = (_life - (dmg - _def))) <= 0) 
		{
			_life = 0;
			_alive = false;
		}
		else
			_life -= (dmg - _def);
	}	
}


/*
* NAME : move
* ROLE : Application du mouvement à l'unité
* ROLE : Si l'unité n'a plus de mouvement disponible alors arret
* INPUT  PARAMETERS : Uint8& : enum Select_Type
* INPUT  PARAMETERS : int& : unité séléctionnée
* INPUT  PARAMETERS : int x : incrementation coor x
* INPUT  PARAMETERS : int y : incrementation coor y
* OUTPUT PARAMETERS : Application du mouvement à l'unité
* RETURNED VALUE    : void
*/
void Units::move(Uint8& select, int& selectunit, int x, int y)
{
	if (_movement > 0)
	{
		_x += x;
		_y += y;
		_movement--;

	}
	if (_movement == 0)
	{
		select = selectnothing;
		selectunit = -1;
		_blit = 0;
		_show = true;
	}

}


/*
* NAME : heal
* ROLE : Soigne l'unité en fonction du territoire sur lequel elle se trouve
* INPUT  PARAMETERS : std::vector<std::vector<Tile>>& tiles : tableau de cases
* INPUT  PARAMETERS : unsigned int : données générale de la map : joueur sélectionné
* OUTPUT PARAMETERS : Soigne l'unité en fonction du contexte
* RETURNED VALUE    : void
*/
void Units::heal(std::vector<std::vector<Tile>>& tiles, unsigned int selectplayer)
{
	for (unsigned int i = 0; i < tiles.size(); i++) 
	{
		for (unsigned int j = 0; j < tiles[i].size(); j++)
		{
			if (_x == tiles[i][j].tile_x && _y == tiles[i][j].tile_y)
			{
				if (tiles[i][j].appartenance == -1) 
				{
					_life += (unsigned int)ceil(_maxlife / 20);
					if (_life > _maxlife)
						_life = _maxlife;
					return;
				}
				else if (tiles[i][j].appartenance == (int)selectplayer)
				{
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


/*
* NAME : levelup
* ROLE : levelup
* INPUT  PARAMETERS : void
* OUTPUT PARAMETERS : levelup
* RETURNED VALUE    : void
*/
void Units::levelup()
{
	_level++;
	//heal();
}


/*
* NAME : RESETmovement
* ROLE : RESETmovement
* INPUT  PARAMETERS : void
* OUTPUT PARAMETERS : RESETmovement
* RETURNED VALUE    : void
*/
void Units::RESETmovement()
{
	_movement = _maxmovement;
}


/*
* NAME : testPos
* ROLE : Test sur les positions de la souris et de l'unité
* INPUT  PARAMETERS : unsigned int mouse_x : position x
* OUTPUT PARAMETERS : unsigned int mouse_y : position y
* RETURNED VALUE    : int : 0 : pas sélectioné / 1 : sélectionné
*/
int Units::testPos(unsigned int mouse_x, unsigned int mouse_y) 
{
	if (_x == mouse_x && _y == mouse_y)
		return 1;
	return 0;
}

/* *********************************************************
 *					END Units::METHODS
 ********************************************************* */


/* *********************************************************
 *			START Units::METHODS::AFFICHAGE
 ********************************************************* */


/*
* NAME : afficher
* ROLE : Affichage de la Texture de l'unité ainsi que la barre de vie et couleur
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* INPUT  PARAMETERS : unsigned int iPlayer : joueur sélectionné
* OUTPUT PARAMETERS : Affichage de l'unité
* RETURNED VALUE    : void
*/
void Units::afficher(Sysinfo& sysinfo, unsigned int iPlayer){
	if (_show)
	{
		unsigned int x = _x - sysinfo.map.screenOffsetXIndexMin * sysinfo.map.tileSize;
		unsigned int y = _y - sysinfo.map.screenOffsetYIndexMin * sysinfo.map.tileSize;
		sysinfo.allTextures.unit[searchIndex(_name, sysinfo.allTextures.unit)]->render( x, y);
	
		if (_life == _maxlife)
		{
			sysinfo.allTextures.barLife[0]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < _maxlife && _life >= (_maxlife - ceil(_maxlife * 0.1)))
		{
			sysinfo.allTextures.barLife[1]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.1)) && _life >= (_maxlife - ceil(_maxlife * 0.2))) 
		{
			sysinfo.allTextures.barLife[2]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.2)) && _life >= (_maxlife - ceil(_maxlife * 0.3)))
		{
			sysinfo.allTextures.barLife[3]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.3)) && _life >= (_maxlife - ceil(_maxlife * 0.4)))
		{
			sysinfo.allTextures.barLife[4]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.4)) && _life >= (_maxlife - ceil(_maxlife * 0.5)))
		{
			sysinfo.allTextures.barLife[5]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.5)) && _life >= (_maxlife - ceil(_maxlife * 0.6))) 
		{
			sysinfo.allTextures.barLife[6]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.6)) && _life >= (_maxlife - ceil(_maxlife * 0.7))) 
		{
			sysinfo.allTextures.barLife[7]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.7)) && _life >= (_maxlife - ceil(_maxlife * 0.8)))
		{
			sysinfo.allTextures.barLife[8]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.8)) && _life >= (_maxlife - ceil(_maxlife * 0.9)))
		{
			sysinfo.allTextures.barLife[9]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}
		else if (_life < (_maxlife - ceil(_maxlife * 0.9)))
		{
			sysinfo.allTextures.barLife[10]->render(x + (sysinfo.map.tileSize / 2) - 4, y + sysinfo.map.tileSize);
		}


		sysinfo.allTextures.colorapp[iPlayer]->render(x, y + sysinfo.map.tileSize);
	}
}


/*
* NAME : afficherstat
* ROLE : Affichage des statistiques de l'unité (nom, x, y ...)
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : Affichage des statistiques de l'unité
* RETURNED VALUE    : void
*/
void Units::afficherstat(Sysinfo& sysinfo)
{
	if (_show)
	{
		int initspace = _y, space = 14;
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "Name: "  + _name, Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace, no_angle);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "X: " + std::to_string(_x), Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space, no_angle);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "Y: " + std::to_string(_y), Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space, no_angle);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "life: " + std::to_string(_life), Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space, no_angle);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "atq: " + std::to_string(_atq), Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space, no_angle);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "def: " + std::to_string(_def), Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space, no_angle);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "movement: " + std::to_string(_movement), Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space, no_angle);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, "level: " + std::to_string(_level), Red, { 255, 255, 255, 255 }, 12, _x + sysinfo.map.tileSize, initspace += space, no_angle);
	}
}


/*
* NAME : cmpblit
* ROLE : Compteur permettant de faire clignoter l'unité
* ROLE : Attention : basé sur SCREEN_REFRESH_RATE
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : Compteur permettant de faire clignoter l'unité
* RETURNED VALUE    : void
*/
void Units::cmpblit() 
{
	/*
		50% off 50% on , environ 1s le cycle
	*/
	++_blit %= 30;
	if(_blit == 0)
	{
		_show = !_show;
	}
}


/* *********************************************************
 *				END Units::METHODS::AFFICHAGE
 ********************************************************* */


/*
*	End Of File
*/