/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2024 (robin.sauter@orange.fr)

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

#ifndef Unit_H
#define Unit_H

#include "LIB.h"

#include <R2D/src/API_fwd.h>
#include <glm/glm.hpp>
#include <jsoncons/json.hpp>

class Unit
{
public:

	 /* NAME : searchUnitByName															   */
	 /* ROLE : Search the unit in vector template by name								   */
	 /* INPUT : std::string name : name to compared										   */
	 /* INPUT : std::vector<Unit_Template>& : vector of template unit 					   */
	 /* RETURNED VALUE : unsigned int : index of the unit								   */
	static unsigned int searchUnitByName
	(
		const std::string& name,
		const VectUnitTemplate& tabUnit_Template
	);

	/* NAME : searchUnitTile															   */
	/* ROLE : Cherche l'unit� �tant dans la case s�l�ctionn�							   */
	/* INPUT/OUTPUT : SubcatPlayer& s_player : structure concernant un joueur			   */
	/* INPUT : const KeyboardMouse& mouse : donn�es g�n�rale des entr�es utilisateur	   */
	/* INPUT/OUTPUT : std::vector<Player*>& tabplayer : Vecteur de joueurs				   */
	/* OUTPUT : Select_Type* select : type de s�lection									   */
	/* RETURNED VALUE    : void															   */
	static bool searchUnitTile
	(
		Players& players,
		const glm::i32vec2& mouseCoorNorm,
		Select_Type* select
	);

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
	static void tryToMove
	(
		const MatriceMap& maps,
		Players& players,
		Select_Type select,
		const R2D::CardinalDirection& cardinalDirection
	);

private:

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
	static Move_Type searchToMove
	(
		const MatriceMap& maps,
		Players& players,
		const R2D::CardinalDirection& cardinalDirection,
		int* const playerToAttack,
		int* const unitToAttack
	);

	/* NAME : checkUnitNextTile															   */
	/* ROLE : Check des �qualit�s des positions des Units avec + x et +y				   */
	/* INPUT : const Unit* from : Unit avec un mouvement possible + x + y				   */
	/* INPUT : const Unit* from : Unit aux positions + x + y							   */
	/* INPUT : int x : delta horizontal tileSize en fonction du cardinal				   */
	/* INPUT : int y : delta vertical tileSize en fonction du cardinal					   */
	/* RETURNED VALUE : bool : false->position diff�rente / true->m�me positions		   */
	static bool checkUnitNextTile
	(
		const Unit& from,
		const Unit& to,
		const int x,
		const int y
	);

	/* NAME : checkNextTile																   */
	/* ROLE : Check des �qualit�s des positions des Units avec + x et +y				   */
	/* INPUT : const Unit* from : Unit aux positions + x + y							   */
	/* INPUT : const Tile& to : Tile � tester											   */
	/* INPUT : int x : delta horizontal tileSize en fonction du cardinal				   */
	/* INPUT : int y : delta vertical tileSize en fonction du cardinal					   */
	/* RETURNED VALUE : bool : false->position diff�rente / true->m�me positions		   */
	static bool checkNextTile
	(
		const Unit& from,
		const Tile& to,
		const int x,
		const int y
	);
	

public:

	Unit();

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
		unsigned int numberOfAttack,
		unsigned int level,
		double maintenance,
		Player* ptrToPlayer
	);

	virtual ~Unit();

private:

	/* NAME : attack																	   */
	/* ROLE : Attaque la cible avec les dommages appliqu�s de l'unit�					   */
	/* INPUT/OUTPUT : Units* : pointeur vers l'unit� qui doit se d�fendre				   */
	/* RETURNED VALUE    : void															   */
	virtual void attack
	(
		Unit&
	);

	/* NAME : defend																	   */
	/* ROLE : D�fense de l'unit� face � une attaque										   */
	/* INPUT : unsigned int : dommage appliqu� par l'attaque							   */
	/* RETURNED VALUE    : void															   */
	virtual void defend
	(
		const int dmg
	);

	/* NAME : move																		   */
	/* ROLE : Application du mouvement � l'unit�										   */
	/* ROLE : Si l'unit� n'a plus de mouvement disponible alors arret					   */
	/* INPUT : unsigned int& : enum Select_Type												   */
	/* INPUT : int& : unit� s�l�ctionn�e												   */
	/* INPUT : int x : incrementation coor x											   */
	/* INPUT : int y : incrementation coor y											   */
	/* RETURNED VALUE    : void															   */
	virtual void move
	(
		Select_Type& select,
		int& selectunit,
		const R2D::CardinalDirection& cardinalDirection
	);

public:

	/* NAME : heal																		   */
	/* ROLE : Soigne l'unit� en fonction du territoire sur lequel elle se trouve		   */
	/* INPUT : const std::vector<std::vector<Tile>>& tiles : tableau de cases			   */
	/* INPUT : unsigned int : donn�es g�n�rale de la map : joueur s�lectionn�			   */
	/* RETURNED VALUE    : void															   */
	virtual void heal
	(
		const MatriceMap& tiles,
		const unsigned int selectplayer
	);

	/* NAME : levelup																	   */
	/* ROLE : Incr�mentation de 1 de level												   */
	/* INPUT : void																		   */
	/* RETURNED VALUE    : void															   */
	virtual void levelup();

	/* NAME : RESETmovement																   */
	/* ROLE : Reset du nombre de mouvement disponible pour un tour						   */
	/* INPUT : void																	       */
	/* RETURNED VALUE    : void															   */
	virtual void RESETmovement();

	virtual void RESETnumberOfAttack();

	/* ROLE : 	TODO																	   */
	/* RETURNED VALUE : bool															   */
	virtual bool irrigate
	(
		MatriceMap& map
	);

private:

	/* NAME : testPos																	   */
	/* ROLE : Test sur les positions de la souris et de l'unit�							   */
	/* INPUT : unsigned int mouse_x : position x										   */
	/* INPUT : unsigned int mouse_y : position y										   */
	/* RETURNED VALUE    : int : 0 : pas s�lection� / 1 : s�lectionn�					   */
	virtual bool testPos
	(
		const unsigned int mouse_x,
		const unsigned int mouse_y
	);

	/* NAME : isGroundMovement_Type														   */
	/* ROLE : Check if the movement type of the Unit is	ground							   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : bool : false -> movement type is not ground						   */
	/* RETURNED VALUE : bool : true -> movement type is ground							   */
	virtual bool isGroundMovement_Type();

	/* NAME : isAirMovement_Type														   */
	/* ROLE : Check if the movement type of the Unit is	air								   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : bool : false -> movement type is not air						   */
	/* RETURNED VALUE : bool : true -> movement type is air								   */
	virtual bool isAirMovement_Type();

	/* NAME : isWaterMovement_Type														   */
	/* ROLE : Check if the movement type of the Unit is	water							   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : bool : false -> movement type is not water						   */
	/* RETURNED VALUE : bool : true -> movement type is water							   */
	virtual bool isWaterMovement_Type();

	/* NAME : isDeepWaterMovement_Type													   */
	/* ROLE : Check if the movement type of the Unit is	DeepWater						   */
	/* INPUT : void																		   */
	/* RETURNED VALUE : bool : false -> movement type is not DeepWater					   */
	/* RETURNED VALUE : bool : true -> movement type is DeepWater						   */
	virtual bool isDeepWaterMovement_Type();

	virtual bool isPossibleToAttack();

public:

	virtual bool isThisUnitType
	(
		const std::string& nameToCompare
	);

public:

	/* NAME : cmpblit																	   */
	/* ROLE : Compteur permettant de faire clignoter l'unit�							   */
	/* ROLE : Attention : bas� sur SCREEN_REFRESH_RATE									   */
	/* INPUT : void																		   */
	/* RETURNED VALUE    : void															   */
	virtual void cmpblit();

public:

	jsoncons::ojson saveToOjson();

public:

	inline const std::string& GETname()				const { return m_name; };
	inline unsigned int GETx()						const { return m_x; };
	inline unsigned int GETy()						const { return m_y; };
	inline Unit_Movement_Type GETmovementType()		const { return m_movementType; };
	inline int GETmaxlife()							const { return m_maxlife; };
	inline int GETmaxatq()							const { return m_maxatq; };
	inline int GETmaxdef()							const { return m_maxdef; };
	inline int GETmaxmovement()						const { return m_maxmovement; };
	inline int GETmaxNumberOfAttack()				const { return m_maxNumberOfAttack; };
	inline int GETmaxlevel()						const { return m_maxlevel; };
	inline int GETlife()							const { return m_life; };
	inline int GETatq()								const { return m_atq; };
	inline int GETdef()								const { return m_def; };
	inline int GETmovement()						const { return m_movement; };
	inline int GETnumberOfAttack()					const { return m_numberOfAttack; };
	inline int GETlevel()							const { return m_level; };
	inline bool GETalive()							const { return m_alive; };
	inline double GETmaintenance()					const { return m_maintenance; }
	inline unsigned int GETblit()					const { return m_blit; };
	inline bool GETshow()							const { return m_show; };
	inline bool GETshowStats()						const { return m_showStats; };
	inline Player* GETowner()							  { return m_owner; };


	inline void SETname(const std::string& name) { m_name = name; };
	inline void SETx(unsigned int x) { m_x = x; };
	inline void SETy(unsigned int y) { m_y = y; };
	inline void SETmovementType(Unit_Movement_Type movementType) { m_movementType = movementType; };
	inline void SETmaxlife(int life) { m_maxlife = life; };
	inline void SETmaxatq(int atq) { m_maxatq = atq; };
	inline void SETmaxdef(int def) { m_maxdef = def; };
	inline void SETmaxmovement(int movement) { m_maxmovement = movement; };
	inline void SETmaxNumberOfAttack(int maxNumberOfAttack) { m_maxNumberOfAttack = maxNumberOfAttack; };
	inline void SETmaxlevel(int level) { m_maxlevel = level; };
	inline void SETlife(int life) { m_life = life; };
	inline void SETatq(int atq) { m_atq = atq; };
	inline void SETdef(int def) { m_def = def; };
	inline void SETmovement(int movement) { m_movement = movement; };
	inline void SETnumberOfAttack(int numberOfAttack) { m_numberOfAttack = numberOfAttack; };
	inline void SETlevel(int level) { m_level = level; };
	inline void SETalive(bool alive) { m_alive = alive; };
	inline void SETmaintenance(double maintenance) { m_maintenance = maintenance; }
	inline void SETblit(unsigned int blit) { m_blit = blit; };
	inline void SETshow(bool show) { m_show = show; };
	inline void SETshowStats(bool showStats) { m_showStats = showStats; };
	inline void SETowner(Player* owner) { m_owner = owner; };

private:

	std::string m_name;
	unsigned int m_x;
	unsigned int m_y;
	Unit_Movement_Type m_movementType;

	int m_maxlife;
	int m_maxatq;
	int m_maxdef;
	int m_maxmovement;
	int m_maxNumberOfAttack;
	int m_maxlevel;

	int m_life;
	int m_atq;
	int m_def;
	int m_movement;
	int m_numberOfAttack;
	int m_level;
	bool m_alive;

	double m_maintenance;

	unsigned int m_blit;
	bool m_show;
	bool m_showStats;

	Player* m_owner;
};

#endif /* Unit_H */

/*
*	End Of File : Unit.h
*/
