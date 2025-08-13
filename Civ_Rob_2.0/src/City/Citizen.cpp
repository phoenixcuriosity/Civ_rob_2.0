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

#include "City.h"
#include "../LogSentences.h"
#include "../T_MainMap.h"
#include "ICitizenVisitor.h"
#include "JsonCitizenSerializerVisitor.h"
#include <R2D/src/Log.h>

void logConstructor(const city::Citizen& citizen)
{
	city::JsonCitizenSerializerVisitor jVisitor;
	citizen.accept(jVisitor);
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_CITIZEN, logS::DATA::CONSTRUCTOR_CITIZEN,
		jVisitor.result.as_string());
}

city::Citizen::Citizen
(
	const Tile& tile
)
	:
	m_tileOccupied((unsigned int)ceil(City::INIT_AREA_VIEW / 2)),
	m_happiness(Emotion_Type::neutral),
	m_food(tile.food),
	m_work(tile.work),
	m_gold(tile.gold),
	m_revolt(0),
	m_religion(Religion_Type::catholic),
	m_place(true)
{
	logConstructor(*this);
}

city::Citizen::Citizen
(
	const unsigned int tileOccupied,
	const int food,
	const int work,
	const int gold
)
	:
	m_tileOccupied(tileOccupied),
	m_happiness(Emotion_Type::neutral),
	m_food(food),
	m_work(work),
	m_gold(gold),
	m_revolt(0),
	m_religion(Religion_Type::catholic),
	m_place(true)
{
	logConstructor(*this);
}

city::Citizen::Citizen(const TCitizenData& data)
: m_tileOccupied(data.tileOccupied),
m_happiness(data.happiness),
m_food(data.food),
m_work(data.work),
m_gold(data.gold),
m_revolt(data.revolt),
m_religion(data.religion),
m_place(data.place)
{
	logConstructor(*this);
}

city::Citizen::~Citizen()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_CITIZEN, logS::DATA::EMPTY_DATA);
}

void
city::Citizen
::accept(ICitizenVisitor& visitor) const
{
	visitor.visit(*this);
}