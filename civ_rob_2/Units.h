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

class Units
{
	public:

		Units();
		Units::Units(const std::string &name, unsigned int x, unsigned int y, unsigned int life, unsigned int atq,
			unsigned int def, unsigned int move, unsigned int level);
		~Units();

		static void loadUnitAndSpec(Sysinfo& sysinfo);
		static void searchunit(Sysinfo&);
		static void searchUnittile(Sysinfo&);
		static void tryToMove(Sysinfo&, int, int);
		static int searchToMove(Sysinfo&, int, int);
		static bool irrigate(Sysinfo&);

		virtual void attack(Units*);
		virtual void defend(unsigned int);
		virtual void move(Uint8&, int&, int, int);
		virtual void heal(std::vector<std::vector<Tile>>& tiles, unsigned int selectplayer);
		virtual void levelup();
		virtual void RESETmovement();

		virtual int testPos(unsigned int mouse_x, unsigned int mouse_y);


		virtual void afficher(Sysinfo&);
		virtual void afficherBardeVie(Sysinfo&);
		virtual void afficherstat(Sysinfo&);
		virtual void cmpblit();

		inline std::string GETname()			const { return _name; };
		inline unsigned int GETx()				const { return _x; };
		inline unsigned int GETy()				const { return _y; };
		inline unsigned int GETmaxlife()		const { return _maxlife; };
		inline unsigned int GETmaxatq()			const { return _maxatq; };
		inline unsigned int GETmaxdef()			const { return _maxdef; };
		inline unsigned int GETmaxmovement()	const { return _maxmovement; };
		inline unsigned int GETmaxlevel()		const { return _maxlevel; };
		inline unsigned int GETlife()			const { return _life; };
		inline unsigned int GETatq()			const { return _atq; };
		inline unsigned int GETdef()			const { return _def; };
		inline unsigned int GETmovement()		const { return _movement; };
		inline unsigned int GETlevel()			const { return _level; };
		inline bool GETalive()					const { return _alive; };
		inline bool GETblit()					const { return _blit; };

		inline void SETname(const std::string &name)		{ _name = name; };
		inline void SETx(unsigned int x)					{ _x = x; };
		inline void SETy(unsigned int y)					{ _y = y; };
		inline void SETlife(unsigned int life)				{ _life = life; };
		inline void SETatq(unsigned int atq)				{ _atq = atq; };
		inline void SETdef(unsigned int def)				{ _def = def; };
		inline void SETmovement(unsigned int movement)		{ _movement = movement; };
		inline void SETlevel(unsigned int level)			{ _level = level; };
		inline void SETalive(bool alive)					{ _alive = alive; };
		inline void SETblit(bool blit)						{ _blit = blit; };
		
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

/*
*	End Of File
*/