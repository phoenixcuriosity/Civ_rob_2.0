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

#ifndef Player_H
#define Player_H

#include "LIB.h"

#include "T_Player.h"

namespace PlayerH
{
	constexpr unsigned int NB_MAX_PLAYER = 9;

	constexpr double INITIAL_GOLD = 100.0;
	
	constexpr bool NEED_TO_UPDATE_DRAW_UNIT = true;
}


class Player
{
public:

	/* NAME : Player																	   */
	/* ROLE : Constructeur par défaut													   */
	/* INPUT : void																		   */
	Player();

	/* NAME : Player																	   */
	/* ROLE : Constructeur par nom du joueur											   */
	/* INPUT : const std::string&														   */
	Player
	(
		const std::string& name,
		const int id
	);

	/* NAME : ~Player																	   */
	/* ROLE : Initialisation d'une Unit vide											   */
	virtual ~Player();

	/* NAME : operator=																	   */
	/* ROLE : Redéfinition de l'opérateur =												   */
	/* INPUT : const Player& player : l'objet à copier									   */
	/* RETURNED VALUE : Player&	: l'objet recopié										   */
	Player& operator=
	(
		const Player& player
	);

	/* NAME : deletePlayer																   */
	/* ROLE : Destruction de l'objet et de ses ptr										   */
	/* INPUT : void																		   */
	/* RETURNED VALUE    : void															   */
	virtual void deletePlayer();

	/* NAME : addUnit																	   */
	/* ROLE : Ajout une Unit avec les spécifications demandées (nom, positions, ...)	   */
	/* INPUT : Spécifications demandées (nom, positions, ...)							   */
	/* RETURNED VALUE    : void															   */
	virtual void addUnit
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
		double maintenance
	);

	virtual void addEmptyUnit();
	
	/* NAME : deleteUnit																   */
	/* ROLE : Suppression d'une Unit du joueur											   */
	/* INPUT : unsigned int : index de Unit dans le tableau								   */
	/* RETURNED VALUE    : void															   */
	virtual void deleteUnit
	(
		const unsigned int index
	);
	
	/* NAME : addCity																	   */
	/* ROLE : Ajout une City avec les spécifications demandées (nom, positions, ...)	   */
	/* INPUT : Spécifications demandées (nom, positions, ...)							   */
	/* RETURNED VALUE    : void															   */
	virtual void addCity
	(
		const std::string&,
		const unsigned int,
		const unsigned int,
		VectMap& tiles
	);

	/* NAME : deleteCity																   */
	/* ROLE : Suppression d'une City du joueur											   */
	/* INPUT : unsigned int : index de City dans le tableau								   */
	/* RETURNED VALUE    : void															   */
	virtual void deleteCity
	(
		const unsigned int index
	);

	virtual CityPtrT* searchCity
	(
		const unsigned int indexX,
		const unsigned int indexY
	);

	/* NAME : computeGold																   */
	/* ROLE : Compute income and cost then the balance between the two					   */
	/* ROLE : Add balance to the player gold											   */
	/* INPUT : void																		   */
	/* RETURNED VALUE    : void															   */
	virtual void computeGold();

	virtual void computeMaintenanceCostUnit();

	/* NAME : resetGoldStats															   */
	/* ROLE : Reset all stats of m_goldStats except gold									   */
	/* INPUT : void																		   */
	/* RETURNED VALUE    : void															   */
	virtual void resetGoldStats();

	/* NAME : resetGoldStats															   */
	/* ROLE : Reset all stats of m_goldStats except gold									   */
	/* INPUT : double goldToAdd	: gold to add in goldConversionSurplus					   */
	/* RETURNED VALUE    : void															   */
	virtual void addGoldToGoldConversionSurplus
	(
		const double goldToAdd
	);

public:

	jsoncons::ojson saveToOjson();

	void loadFromOjson(const jsoncons::ojson& jsonLoad);

public:

	inline virtual const std::string& GETname()			const { return m_name; };
	inline virtual const VectUnit& GETtabUnit()			const { return m_tabUnit; };
	inline virtual const VectCity& GETtabCity()			const { return m_tabCity; };
	inline virtual const GoldStats& GETgoldStats()		const { return m_goldStats; };
	inline virtual const OnOffDisplay& GETonOffDisplay()const { return m_onOffDisplay; };
	inline virtual const UnitPtrT& GETSelectedUnitPtr() const { return m_tabUnit[m_selectedUnit]; }

	inline virtual int GETid()							const { return m_id; };
	inline virtual int GETselectedUnit()				const { return m_selectedUnit; };
	inline virtual int GETselectedCity()				const { return m_selectedCity; };

	inline virtual GoldStats& GETgoldStats()				  { return m_goldStats; };
	inline virtual OnOffDisplay& GETonOffDisplay()		      { return m_onOffDisplay; };

	inline virtual void SETname(const std::string& msg) { m_name = msg; };
	inline virtual void SETid(const int id) { m_id = id; };
	inline virtual void SETselectedUnit(const int selectedUnit) { m_selectedUnit = selectedUnit; };
	inline virtual void SETselectedCity(const int selectedCity) { m_selectedCity = selectedCity; };

private:

	std::string m_name;
	int m_id;

	VectUnit m_tabUnit;
	VectCity m_tabCity;
	int m_selectedUnit;
	int m_selectedCity;
	GoldStats m_goldStats;
	OnOffDisplay m_onOffDisplay;
};

#endif /* Player_H */

/*
*	End Of File : Player.h
*/