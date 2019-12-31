/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.16
	file version : 1.6

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

#ifndef Unit_H
#define Unit_H

#include "civ_lib.h"

enum Move_Type : Uint8 { cannotMove, canMove, attackMove};

class Unit
{
public:
	/* *********************************************************
	 *					Unit::STATIC						   *
	 ********************************************************* */

	/*
	* NAME : loadUnitAndSpec
	* ROLE : Chargement des informations concernant les unités à partir d'un fichier
	* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
	* OUTPUT PARAMETERS : tableau de nom et spec concernant les unités
	* RETURNED VALUE    : void
	*/
	static void loadUnitAndSpec(Sysinfo& sysinfo);

	/*
	* NAME : searchunit
	* ROLE : Sélection du nom de l'unité à partir de l'index du tableau
	* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
	* OUTPUT PARAMETERS : nom de l'unité
	* RETURNED VALUE    : void
	*/
	static void searchUnit(Sysinfo&);

	/*
	* NAME : searchUnittile
	* ROLE : Cherche l'unité étant dans la case séléctionné
	* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
	* OUTPUT PARAMETERS : index et nom de l'unité sélectionnée
	* OUTPUT PARAMETERS : activation de la méthode blit (clignotement)
	* RETURNED VALUE    : void
	*/
	static void searchUnitTile(Sysinfo&);

	/*
	* NAME : tryToMove
	* ROLE : Recherche à faire bouger l'unité selon le contexte
	* ROLE : Attention : contient un rappel récursif
	* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
	* OUTPUT PARAMETERS : l'unité reste à sa place ou bouge en fonction du contexte
	* RETURNED VALUE    : void
	*/
	static void tryToMove(Sysinfo&, int, int);

	/*
	* NAME : searchToMove
	* ROLE : Recherche à faire bouger l'unité selon le contexte
	* ROLE : Action conditionnelle (case libre, ennemi, amis)
	* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
	* OUTPUT PARAMETERS : l'unité reste à sa place ou bouge en fonction du contexte
	* RETURNED VALUE    : int : 0 : ne bouge pas / 1 : case libre : peut bouger / 2 : ennemi : ne bouge pas
	* 
	*/
	static Move_Type searchToMove(Sysinfo&, int, int);

	/*
	* NAME : irrigate
	* ROLE : 
	* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
	* OUTPUT PARAMETERS :
	* RETURNED VALUE    : bool
	*/
	static bool irrigate(Sysinfo&);

public:
	/* *********************************************************
	 *					Unit::METHODS						   *
	 ********************************************************* */

	Unit();
	Unit(const std::string &name, unsigned int x, unsigned int y, unsigned int life, unsigned int atq,
		unsigned int def, unsigned int move, unsigned int level);
	~Unit();


	/*
	* NAME : attack
	* ROLE : Attaque la cible avec les dommages appliqués de l'unité 
	* INPUT  PARAMETERS : Units* : pointeur vers l'unité qui doit se défendre
	* OUTPUT PARAMETERS : Attaque d'une unité
	* RETURNED VALUE    : void
	*/
	virtual void attack(Unit*);

	/*
	* NAME : defend
	* ROLE : Défense de l'unité face à une attaque
	* INPUT  PARAMETERS : unsigned int : dommage appliqué par l'attaque
	* OUTPUT PARAMETERS : l'unité peut prendre des dommage et/ou mourrir
	* RETURNED VALUE    : void
	*/
	virtual void defend(unsigned int dmg);

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
	virtual void move(Uint8& select, int& selectunit, int x, int y);

	/*
	* NAME : heal
	* ROLE : Soigne l'unité en fonction du territoire sur lequel elle se trouve
	* INPUT  PARAMETERS : std::vector<std::vector<Tile>>& tiles : tableau de cases
	* INPUT  PARAMETERS : unsigned int : données générale de la map : joueur sélectionné
	* OUTPUT PARAMETERS : Soigne l'unité en fonction du contexte
	* RETURNED VALUE    : void
	*/
	virtual void heal(std::vector<std::vector<Tile>>& tiles, unsigned int selectplayer);

	/*
	* NAME : levelup
	* ROLE : levelup
	* INPUT  PARAMETERS : void
	* OUTPUT PARAMETERS : levelup
	* RETURNED VALUE    : void
	*/
	virtual void levelup();

	/*
	* NAME : RESETmovement
	* ROLE : RESETmovement
	* INPUT  PARAMETERS : void
	* OUTPUT PARAMETERS : RESETmovement
	* RETURNED VALUE    : void
	*/
	virtual void RESETmovement();

	/*
	* NAME : testPos
	* ROLE : Test sur les positions de la souris et de l'unité
	* INPUT  PARAMETERS : unsigned int mouse_x : position x
	* OUTPUT PARAMETERS : unsigned int mouse_y : position y
	* RETURNED VALUE    : int : 0 : pas sélectioné / 1 : sélectionné
	*/
	virtual bool testPos(unsigned int mouse_x, unsigned int mouse_y);


public:
	/* *********************************************************
	 *				Unit::METHODS::AFFICHAGE				   *
	 ********************************************************* */

	/*
	* NAME : afficher
	* ROLE : Affichage de la Texture de l'unité ainsi que la barre de vie et couleur
	* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
	* INPUT  PARAMETERS : unsigned int iPlayer : joueur sélectionné
	* OUTPUT PARAMETERS : Affichage de l'unité
	* RETURNED VALUE    : void
	*/
	virtual void afficher(Sysinfo&, unsigned int iPlayer);

	/*
	* NAME : afficherstat
	* ROLE : Affichage des statistiques de l'unité (nom, x, y ...)
	* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
	* OUTPUT PARAMETERS : Affichage des statistiques de l'unité
	* RETURNED VALUE    : void
	*/
	virtual void afficherstat(Sysinfo&);

	/*
	* NAME : cmpblit
	* ROLE : Compteur permettant de faire clignoter l'unité
	* ROLE : Attention : basé sur SCREEN_REFRESH_RATE
	* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
	* OUTPUT PARAMETERS : Compteur permettant de faire clignoter l'unité
	* RETURNED VALUE    : void
	*/
	virtual void cmpblit();


public:
	/* *********************************************************
	 *				Unit::METHODS::GET/SET					   *
	 ********************************************************* */

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
	/* *********************************************************
	 *					Unit::ATTRIBUTS					       *
	 ********************************************************* */
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



#endif /* Unit_H */

/*
*	End Of File : Unit.h
*/