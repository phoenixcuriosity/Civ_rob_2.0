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

#include "Citizen.h"

#include "App.h"
#include "City.h"
#include "LogSentences.h"
#include "T_Citizen.h"
#include "T_MainMap.h"

#include <R2D/src/Log.h>

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Citizen																	   */
/* ROLE : Constructeur par d�faut													   */
/* INPUT : void																		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Citizen::Citizen()
	:
	m_tileOccupied((unsigned int)ceil(CITY_INFLUENCE::INIT_AREA_VIEW / 2)),
	m_happiness(Emotion_Type::neutral),
	m_food(2),
	m_work(1),
	m_gold(1),
	m_revolt(0),
	m_religion(Religion_Type::catholic),
	m_place(false)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_CITIZEN, logS::DATA::CONSTRUCTOR_CITIZEN,
		m_tileOccupied, m_food, m_work, m_gold, m_revolt);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Citizen																	   */
/* ROLE : Constructeur par une Tile													   */
/* INPUT : Tile tile : tile centrale de la Citie									   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Citizen::Citizen
(
	const Tile& tile
)
	:
	m_tileOccupied((unsigned int)ceil(CITY_INFLUENCE::INIT_AREA_VIEW / 2)),
	m_happiness(Emotion_Type::neutral),
	m_food(tile.food),
	m_work(tile.work),
	m_gold(tile.gold),
	m_revolt(0),
	m_religion(Religion_Type::catholic),
	m_place(true)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_CITIZEN, logS::DATA::CONSTRUCTOR_CITIZEN,
		m_tileOccupied, m_food, m_work, m_gold, m_revolt);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Citizen																	   */
/* ROLE : Constructeur par une Tile													   */
/* INPUT : std::vector<Tile>& tile : tableau de Tile de la Citie					   */
/* INPUT : std::vector<Citizen*>& citizens : tableau de Citizens					   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Citizen::Citizen
(
	const unsigned int tileOccupied,
	const int food,
	const int work,
	const int gold
)
	:
	m_tileOccupied(tileOccupied),
	m_food(food),
	m_work(work),
	m_gold(gold),
	m_happiness(Emotion_Type::neutral),
	m_revolt(0),
	m_religion(Religion_Type::catholic),
	m_place(true)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_CITIZEN, logS::DATA::CONSTRUCTOR_CITIZEN,
		m_tileOccupied, m_food, m_work, m_gold, m_revolt);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : ~Citizen																	   */
/* ROLE : Destructeur																   */
/* INPUT : void																		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Citizen::~Citizen()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_CITIZEN, logS::DATA::EMPTY_DATA);
}


/* *********************************************************
 *					END Citizen::METHODS				   *
 ********************************************************* */

 /*
  *	End Of File : Citizen.cpp
  */