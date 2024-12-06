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

#ifndef CitizenManager_H
#define CitizenManager_H

#include "LIB.h"

class CitizenManager
{
public:

	CitizenManager(const VectMap& tiles);
	~CitizenManager();

public:

	/* ----------------------------------------------------------------------------------- */
	/* NAME : resetTabCitizen															   */
	/* ROLE : Remove all Citizens in the City											   */
	/* RETURNED VALUE : void															   */
	/* ----------------------------------------------------------------------------------- */
	void resetTabCitizen();

	void addCitizen();
	void addCitizen(bool uselessArg);
	void addCitizen(const Tile& tile);

	void removeCitizen();


	void computeEmotion();

	const VectCitizen& getCitizens()const { return m_citizens; };
	unsigned int getEmotion() const { return m_emotion; };
	unsigned int& getEmotion()		{ return m_emotion; };
	void setEmotion(unsigned int emotion){ m_emotion = emotion; };

	double getWorkFromCitizen()const;
	double getGoldFromCitizen()const;
	double getFoodFromCitizen()const;
	
private:

	/* ----------------------------------------------------------------------------------- */
	/* NAME : placeCitizen																   */
	/* ROLE : Placement d'un Citizen en fonction des cases occup�es de la City			   */
	/* INPUT : std::vector<Tile> : carte de la City										   */
	/* INPUT : std::vector<Citizen> : tableau de Citizen								   */
	/* INPUT : int& m_food, int& m_work, int& m_gold : spec de la case					   */
	/* RETURNED VALUE    : unsigned int : la place allou�e								   */
	/* ----------------------------------------------------------------------------------- */
	unsigned int placeCitizen
	(
		int& m_food,
		int& m_work,
		int& m_gold
	);

	virtual double tileValue
	(
		const Tile& tile,
		const double coefFood = 1.0,
		const double coefWork = 1.0,
		const double coefGold = 1.0
	) const;

public:

	jsoncons::ojson saveToOjson()const;

	void loadFromOjson(const jsoncons::ojson& jsonLoad);

private:

	const VectMap& m_tiles;

	VectCitizen m_citizens;
	unsigned int m_emotion;

};


#endif /* CitizenManager_H */

/*
*	End Of File : CitizenManager.h
*/
