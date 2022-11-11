/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.5.0
	file version : 1.20

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
	Cette classe est la repr�sentation de l'objet Unit
	Cet objet est d�crit par un nom qui sera li� par un objet de type Texture du meme nom lors de la cr�ation
	Cet objet a une position lors de la cr�ation qui correspond au coin haut gauche de la tile s�l�ctionn�e
	Les objets de type Unit ont des caract�ristiques de vie, d'attaque ...
	m_blit et m_show permettent de savoir lorsqu'il faut afficher l'unit� ou la faire clignoter



*/

#ifndef Unit_H
#define Unit_H

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"

#include "MainMap.h"

#include <vector>
#include <memory>
#include <glm/glm.hpp>

class Players;
class GameInput;


 /* *********************************************************
  *						Constantes						   *
  ********************************************************* */

const unsigned int NO_MOVEMENT = 0;

const unsigned int ENOUGH_DAMAGE_TO_KILL = 0;

const unsigned int ZERO_LIFE = 0;

const unsigned int ZERO_BLIT = 0;

const unsigned int FIRST_TRY_TO_MOVE = 0;

/*
	use as 1/x
	default : x = 20
*/
const unsigned int COEF_DIV_HEAL_NO_APPARTENANCE = 20;

/*
	use as 1/x
	default : x = 5
*/
const unsigned int COEF_DIV_HEAL_APPARTENANCE = 5;

/*
	use as 1/x
	default : x = 4
*/
const unsigned int COEF_DIV_LEVELUP = 4;

/*
	use as 1/x
	Use for screen_refresh_rate/BLIT_RATE
	default = 2
*/
const unsigned int BLIT_RATE = 2;

  /* *********************************************************
   *						 Enum							   *
   ********************************************************* */

   /* Define movement for the Unit in case of tryToMove */
enum class Move_Type
{
	cannotMove,		/* The Unit cannot move to the next Tile */
	canMove,		/* The Unit can move to the next Tile */
	attackMove		/* The Unit can move to the next Tile and attack the other Unit standing on the this Tile */
};

/* Define movement type of the Unit */
enum class Unit_Movement_Type
{
	ground,			/* The Unit can move on ground (dirt,grass,...) */
	air,			/* The Unit can move on ground (dirt,grass,...) or on water */
	water,			/* The Unit can move on water */
	deepwater		/* The Unit can move on deepwater or on water */
};

/* *********************************************************
 *						 Structs						   *
 ********************************************************* */

struct Unit_Template
{

	// nom de l'unit� -> /bin/UNITNAME.txt
	std::string name;

	/*
		statistiques concernant l'unit� -> /bin/UNIT.txt
	*/
	Unit_Movement_Type type = Unit_Movement_Type::ground;
	unsigned int life = 0;
	unsigned int atq = 0;
	unsigned int def = 0;
	unsigned int movement = 0;
	unsigned int level = 0;
	unsigned int nbturnToBuild = 0;
	double workToBuild = 0.0;
	double maintenance = 0.0;
};

typedef std::vector<Unit_Template> VectUnitTemplate;

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */

class Unit
{
public:
	/* *********************************************************
	 *					Unit::STATIC						   *
	 ********************************************************* */


	 /* ----------------------------------------------------------------------------------- */
	 /* ----------------------------------------------------------------------------------- */
	 /* NAME : searchUnitByName															   */
	 /* ROLE : Search the unit in vector template by name								   */
	 /* INPUT : std::string name : name to compared										   */
	 /* INPUT : std::vector<Unit_Template>& : vector of template unit 					   */
	 /* RETURNED VALUE : unsigned int : index of the unit										   */
	 /* ----------------------------------------------------------------------------------- */
	 /* ----------------------------------------------------------------------------------- */
	static unsigned int searchUnitByName
	(
		const std::string& name,
		const VectUnitTemplate& tabUnit_Template
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : searchUnitTile															   */
	/* ROLE : Cherche l'unit� �tant dans la case s�l�ctionn�							   */
	/* INPUT/OUTPUT : SubcatPlayer& s_player : structure concernant un joueur			   */
	/* INPUT : const KeyboardMouse& mouse : donn�es g�n�rale des entr�es utilisateur	   */
	/* INPUT/OUTPUT : std::vector<Player*>& tabplayer : Vecteur de joueurs				   */
	/* OUTPUT : Select_Type* select : type de s�lection									   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static bool searchUnitTile
	(
		Players& players,
		const glm::i32vec2& mouseCoorNorm,
		Select_Type* select
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : tryToMove*																	   */
	/* ROLE : Recherche � faire bouger l'unit� selon le contexte						   */
	/* ROLE : Attention : contient un rappel r�cursif									   */
	/* INPUT : const std::vector<std::vector<Tile>>& : Matrice de la MAP				   */
	/* INPUT/OUTPUT : Struct SubcatPlayer& : structure concernant un joueur				   */
	/* INPUT/OUTPUT : std::vector<Player*>& : Vecteur de joueurs						   */
	/* INPUT : Select_Type : �tat de la s�lection du joueur (enum Select_Type : unsigned int)	   */
	/* INPUT : int x : pos X															   */
	/* INPUT : int y : pos Y															   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void tryToMove
	(
		const MatriceMap& maps,
		Players& players,
		Select_Type select,
		const int x,
		const int y,
		unsigned int recursiveIt = FIRST_TRY_TO_MOVE
	);

private:

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : searchToMove																   */
	/* ROLE : Recherche � faire bouger l'unit� selon le contexte						   */
	/* ROLE : Action conditionnelle (case libre, ennemi, amis)							   */
	/* INPUT : const std::vector<std::vector<Tile>>& : Matrice de la MAP			   	   */
	/* INPUT : Struct SubcatPlayer& : structure concernant un joueur					   */
	/* INPUT : const std::vector<Player*>& : Vecteur de joueurs							   */
	/* INPUT : int x : pos X														   	   */
	/* INPUT : int y : pos Y															   */
	/* RETURNED VALUE : Move_Type : / 0 : ne bouge pas / 1 : case libre : peut bouger	   */
	/* RETURNED VALUE : Move_Type : / 2 : ennemi : ne bouge pas							   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static Move_Type searchToMove
	(
		const MatriceMap& maps,
		Players& players,
		const int x,
		const int y,
		int* const playerToAttack,
		int* const unitToAttack
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : checkUnitNextTile															   */
	/* ROLE : Check des �qualit�s des positions des Units avec + x et +y				   */
	/* INPUT : const Unit* from : Unit avec un mouvement possible + x + y				   */
	/* INPUT : const Unit* from : Unit aux positions + x + y							   */
	/* INPUT : int x : delta horizontal tileSize en fonction du cardinal				   */
	/* INPUT : int y : delta vertical tileSize en fonction du cardinal					   */
	/* RETURNED VALUE : bool : false->position diff�rente / true->m�me positions		   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static bool checkUnitNextTile
	(
		const Unit& from,
		const Unit& to,
		const int x,
		const int y
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : checkNextTile																   */
	/* ROLE : Check des �qualit�s des positions des Units avec + x et +y				   */
	/* INPUT : const Unit* from : Unit aux positions + x + y							   */
	/* INPUT : const Tile& to : Tile � tester											   */
	/* INPUT : int x : delta horizontal tileSize en fonction du cardinal				   */
	/* INPUT : int y : delta vertical tileSize en fonction du cardinal					   */
	/* RETURNED VALUE : bool : false->position diff�rente / true->m�me positions		   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static bool checkNextTile
	(
		const Unit& from,
		const Tile& to,
		const int x,
		const int y
	);

public:

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : irrigate																	   */
	/* ROLE : 	TODO																	   */
	/* RETURNED VALUE : bool															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static bool irrigate
	(

	);

public:
	/* *********************************************************
	 *					Unit::METHODS						   *
	 ********************************************************* */

	 /* ----------------------------------------------------------------------------------- */
	 /* ----------------------------------------------------------------------------------- */
	 /* NAME : Unit																		   */
	 /* ROLE : Constructeur par d�faut													   */
	 /* INPUT : void																		   */
	 /* ----------------------------------------------------------------------------------- */
	 /* ----------------------------------------------------------------------------------- */
	Unit();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Unit																		   */
	/* ROLE : Constructeur par complet													   */
	/* INPUT : const std::string &name : nom											   */
	/* INPUT : unsigned int x :	position en x sur la map								   */
	/* INPUT : unsigned int y : position en y sur la map								   */
	/* INPUT : unsigned int life : vie max												   */
	/* INPUT : unsigned int atq	: atq max												   */
	/* INPUT : unsigned int def	: def max												   */
	/* INPUT : unsigned int move : move max												   */
	/* INPUT : unsigned int level : level 1												   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	Unit
	(
		const std::string& name,
		unsigned int x,
		unsigned int y,
		Unit_Movement_Type movementType,
		unsigned int life,
		unsigned int atq,
		unsigned int def,
		unsigned int move,
		unsigned int level,
		double maintenance
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : ~Unit																		   */
	/* ROLE : Destructeur																   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual ~Unit();

private:

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : attack																	   */
	/* ROLE : Attaque la cible avec les dommages appliqu�s de l'unit�					   */
	/* INPUT/OUTPUT : Units* : pointeur vers l'unit� qui doit se d�fendre				   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void attack
	(
		Unit&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : defend																	   */
	/* ROLE : D�fense de l'unit� face � une attaque										   */
	/* INPUT : unsigned int : dommage appliqu� par l'attaque							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void defend
	(
		const int dmg
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : move																		   */
	/* ROLE : Application du mouvement � l'unit�										   */
	/* ROLE : Si l'unit� n'a plus de mouvement disponible alors arret					   */
	/* INPUT : unsigned int& : enum Select_Type												   */
	/* INPUT : int& : unit� s�l�ctionn�e												   */
	/* INPUT : int x : incrementation coor x											   */
	/* INPUT : int y : incrementation coor y											   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void move
	(
		Select_Type& select,
		int& selectunit,
		const int x,
		const int y
	);

public:

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : heal																		   */
	/* ROLE : Soigne l'unit� en fonction du territoire sur lequel elle se trouve		   */
	/* INPUT : const std::vector<std::vector<Tile>>& tiles : tableau de cases			   */
	/* INPUT : unsigned int : donn�es g�n�rale de la map : joueur s�lectionn�			   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void heal
	(
		const MatriceMap& tiles,
		const unsigned int selectplayer
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : levelup																	   */
	/* ROLE : Incr�mentation de 1 de level												   */
	/* INPUT : void																		   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void levelup();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : RESETmovement																   */
	/* ROLE : Reset du nombre de mouvement disponible pour un tour						   */
	/* INPUT : void																	       */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void RESETmovement();

private:

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : testPos																	   */
	/* ROLE : Test sur les positions de la souris et de l'unit�							   */
	/* INPUT : unsigned int mouse_x : position x										   */
	/* INPUT : unsigned int mouse_y : position y										   */
	/* RETURNED VALUE    : int : 0 : pas s�lection� / 1 : s�lectionn�					   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual bool testPos
	(
		const unsigned int mouse_x,
		const unsigned int mouse_y
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : isGroundMovement_Type														   */
	/* ROLE : Check if the movement type of the Unit is	ground							   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : bool : false -> movement type is not ground						   */
	/* RETURNED VALUE : bool : true -> movement type is ground							   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual bool isGroundMovement_Type();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : isAirMovement_Type														   */
	/* ROLE : Check if the movement type of the Unit is	air								   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : bool : false -> movement type is not air						   */
	/* RETURNED VALUE : bool : true -> movement type is air								   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual bool isAirMovement_Type();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : isWaterMovement_Type														   */
	/* ROLE : Check if the movement type of the Unit is	water							   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : bool : false -> movement type is not water						   */
	/* RETURNED VALUE : bool : true -> movement type is water							   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual bool isWaterMovement_Type();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : isDeepWaterMovement_Type													   */
	/* ROLE : Check if the movement type of the Unit is	DeepWater						   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : bool : false -> movement type is not DeepWater					   */
	/* RETURNED VALUE : bool : true -> movement type is DeepWater						   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual bool isDeepWaterMovement_Type();

public:
	/* *********************************************************
	 *				Unit::METHODS::AFFICHAGE				   *
	 ********************************************************* */

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : cmpblit																	   */
	/* ROLE : Compteur permettant de faire clignoter l'unit�							   */
	/* ROLE : Attention : bas� sur SCREEN_REFRESH_RATE									   */
	/* INPUT : void																		   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void cmpblit();


public:
	/* *********************************************************
	 *				Unit::METHODS::GET/SET					   *
	 ********************************************************* */

	inline std::string GETname()				const { return m_name; };
	inline unsigned int GETx()							const { return m_x; };
	inline unsigned int GETy()							const { return m_y; };
	inline Unit_Movement_Type GETmovementType() const { return m_movementType; };
	inline int GETmaxlife()						const { return m_maxlife; };
	inline int GETmaxatq()						const { return m_maxatq; };
	inline int GETmaxdef()						const { return m_maxdef; };
	inline int GETmaxmovement()					const { return m_maxmovement; };
	inline int GETmaxlevel()					const { return m_maxlevel; };
	inline int GETlife()						const { return m_life; };
	inline int GETatq()							const { return m_atq; };
	inline int GETdef()							const { return m_def; };
	inline int GETmovement()					const { return m_movement; };
	inline int GETlevel()						const { return m_level; };
	inline bool GETalive()						const { return m_alive; };
	inline double GETmaintenance()				const { return m_maintenance; }
	inline unsigned int GETblit()				const { return m_blit; };
	inline bool GETshow()						const { return m_show; };
	inline bool GETshowStats()					const { return m_showStats; };


	inline void SETname(const std::string& name) { m_name = name; };
	inline void SETx(unsigned int x) { m_x = x; };
	inline void SETy(unsigned int y) { m_y = y; };
	inline void SETmovementType(Unit_Movement_Type movementType) { m_movementType = movementType; };
	inline void SETmaxlife(int life) { m_maxlife = life; };
	inline void SETmaxatq(int atq) { m_maxatq = atq; };
	inline void SETmaxdef(int def) { m_maxdef = def; };
	inline void SETmaxmovement(int movement) { m_maxmovement = movement; };
	inline void SETmaxlevel(int level) { m_maxlevel = level; };
	inline void SETlife(int life) { m_life = life; };
	inline void SETatq(int atq) { m_atq = atq; };
	inline void SETdef(int def) { m_def = def; };
	inline void SETmovement(int movement) { m_movement = movement; };
	inline void SETlevel(int level) { m_level = level; };
	inline void SETalive(bool alive) { m_alive = alive; };
	inline void SETmaintenance(double maintenance) { m_maintenance = maintenance; }
	inline void SETblit(unsigned int blit) { m_blit = blit; };
	inline void SETshow(bool show) { m_show = show; };
	inline void SETshowStats(bool showStats) { m_showStats = showStats; };

private:
	/* *********************************************************
	 *					Unit::ATTRIBUTS					       *
	 ********************************************************* */
	std::string m_name;
	unsigned int m_x;
	unsigned int m_y;
	Unit_Movement_Type m_movementType;

	int m_maxlife;
	int m_maxatq;
	int m_maxdef;
	int m_maxmovement;
	int m_maxlevel;

	int m_life;
	int m_atq;
	int m_def;
	int m_movement;
	int m_level;
	bool m_alive;

	double m_maintenance;

	unsigned int m_blit;
	bool m_show;
	bool m_showStats;
};

typedef std::vector<std::shared_ptr<Unit>> VectUnit;


#endif /* Unit_H */

/*
*	End Of File : Unit.h
*/
