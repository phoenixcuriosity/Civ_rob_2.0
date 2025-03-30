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

#include "Unit.h"
#include "UnitManager.h"
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

	Player() = delete;
	Player(const std::string& name, const int id);
	virtual ~Player();

	virtual void addUnit(const Unit::UnitName& name,
						 const Unit::Coor coor);

private:
	virtual void addEmptyUnit();

public:
	virtual void deleteUnit(const unsigned int index);
	virtual void addCity(
		const std::string&,
		const unsigned int,
		const unsigned int,
		VectMapPtr& tiles);

private:
	virtual void addEmptyCity();

public:
	virtual void deleteCity(const unsigned int index);
	virtual CityPtrT* searchCity(const unsigned int indexX, const unsigned int indexY);
	virtual void computeGold();
	virtual void computeMaintenanceCostUnit();
	virtual void resetGoldStats();
	virtual void addGoldToGoldConversionSurplus(const double goldToAdd);

public:
	jsoncons::ojson saveToOjson()const;
	void loadFromOjson(const jsoncons::ojson& jsonLoad, MatriceMap& matriceMap);

public:
	inline virtual const std::string& GETname()			const { return m_name; };
	inline virtual const VectUnit& GETtabUnit()			const { return m_unitManager.getUnits(); };
	inline virtual const VectCity& GETtabCity()			const { return m_tabCity; };
	inline virtual const GoldStats& GETgoldStats()		const { return m_goldStats; };
	inline virtual const OnOffDisplay& GETonOffDisplay()const { return m_onOffDisplay; };
	inline virtual const UnitPtrT& GETSelectedUnitPtr() const { return m_unitManager.getUnits()[m_selectedUnit]; }

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

	UnitManager m_unitManager;
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