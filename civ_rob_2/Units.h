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

/*

	Units : 
	Cette classe est la représentation de l'objet Unit
	Cet objet est décrit par un nom qui sera lié par un objet de type Texture du meme nom lors de la création
	Cet objet a une position lors de la création qui correspond au coin haut gauche de la tile séléctionnée
	Les objets de type Unit ont des caractéristiques de vie, d'attaque ...
	_blit et _show permettent de savoir lorsqu'il faut afficher l'unité ou la faire clignoter



*/

#ifndef Units_H
#define Units_H

#include "civ_lib.h"
#include "sdl.h"

class Units{
	public:

		Units();
		Units::Units(const std::string &name, unsigned int x, unsigned int y, unsigned int life, unsigned int atq,
			unsigned int def, unsigned int move, unsigned int level);
		~Units();

		virtual void attack(Units*);
		virtual void defend(unsigned int);
		virtual void move(unsigned int&, int&, int, int);
		virtual void heal(tile[], unsigned int);
		virtual void levelup();
		virtual void RESETmovement();

		virtual int testPos(int, int);


		virtual void afficher(sysinfo&);
		virtual void afficherBardeVie(sysinfo&);
		virtual void afficherstat(sysinfo&);
		virtual void cmpblit();

		std::string GETname() const;
		unsigned int GETx() const;
		unsigned int GETy() const;
		unsigned int GETmaxlife() const;
		unsigned int GETmaxatq() const;
		unsigned int GETmaxdef() const;
		unsigned int GETmaxmovement() const;
		unsigned int GETmaxlevel() const;
		unsigned int GETlife() const;
		unsigned int GETatq() const;
		unsigned int GETdef() const;
		unsigned int GETmovement() const;
		unsigned int GETlevel() const;
		bool GETalive() const;
		bool GETblit() const;

		void SETname(const std::string &msg);
		void SETx(unsigned int);
		void SETy(unsigned int);
		void SETlife(unsigned int);
		void SETatq(unsigned int);
		void SETdef(unsigned int);
		void SETmovement(unsigned int);
		void SETlevel(unsigned int);
		void SETalive(bool);
		void SETblit(bool);
		
	private:
		std::string _name;
		unsigned int _x;
		unsigned int _y;

		unsigned int _maxlife;
		unsigned int _maxatq;
		unsigned int _maxdef;
		unsigned int _maxmovement;
		unsigned int _maxlevel;

		unsigned int _life;
		unsigned int _atq;
		unsigned int _def;
		unsigned int _movement;
		unsigned int _level;
		bool _alive;

		unsigned int _blit;
		bool _show;
};



#endif