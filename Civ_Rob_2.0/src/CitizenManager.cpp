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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "CitizenManager.h"

#include "Citizen.h"
#include "LogSentences.h"
#include "T_Citizen.h"
#include "T_City.h"
#include "T_MainMap.h"

#include <jsoncons/json.hpp>
#include <R2D/src/ValueToScale.h>
#include <R2D/src/ErrorLog.h> 
#include <R2D/src/Log.h> 


CitizenManager::CitizenManager(const VectMap& tiles)
: 
m_tiles(tiles),
m_citizens(),
m_emotion((unsigned int)EMOTION_RANGE::MEAN)
{
	if (!m_tiles.empty())
	{
		/* Add initial citizen in the middle case */
		addCitizen(m_tiles[(unsigned int)ceil(CITY_INFLUENCE::INIT_AREA_VIEW / 2)]);
	}
}

CitizenManager::~CitizenManager()
{
	resetTabCitizen();
}

/* ----------------------------------------------------------------------------------- */
/* NAME : resetTabCitizen															   */
/* ROLE : Remove all Citizens in the City											   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
void CitizenManager::resetTabCitizen()
{
	for (auto& n : m_citizens)
	{
		n.reset();
	}
	m_citizens.clear();
	m_citizens.resize(0);
}

void CitizenManager::addCitizen()
{
	int food{ 0 }, work{ 0 }, gold{ 0 };
	unsigned int place{ placeCitizen(food, work, gold) };
	m_citizens.push_back(std::make_shared<Citizen>(place, food, work, gold));
}

void CitizenManager::addCitizen(bool /* uselessArg */)
{
	m_citizens.push_back(std::make_shared<Citizen>());
}

void CitizenManager::addCitizen(const Tile& tile)
{
	m_citizens.push_back(std::make_shared<Citizen>(tile));
}


unsigned int CitizenManager::placeCitizen
(
	int& m_food,
	int& m_work,
	int& m_gold
)
{
	const unsigned int condition((unsigned int)m_citizens.size());
	unsigned int checkcondition(0);
	unsigned int place(0);
	bool continuer(true);

	std::vector<unsigned int> tabpos;
	for (unsigned int j(0); j < condition; j++)
	{
		tabpos.push_back(m_citizens[j]->GETtileOccupied());
	}


	for (unsigned int i(0); (i < m_tiles.size()) && (true == continuer); i++)
	{
		if (m_tiles[i].appartenance == m_tiles[m_citizens[0]->GETtileOccupied()].appartenance)
		{
			checkcondition = 0;
			for (unsigned int p(0); (p < condition) && (true == continuer); p++)
			{
				if (i != tabpos[p])
				{
					checkcondition++;
				}
				else
				{
					/* N/A */
				}

				if (checkcondition == condition)
				{
					place = i;
					continuer = false;
				}
				else
				{
					/* N/A */
				}
			}
		}
	}

	m_food = m_tiles[place].food;
	m_work = m_tiles[place].work;
	m_gold = m_tiles[place].gold;
	return place;
}

void CitizenManager::removeCitizen()
{
	double minValueTile{ 999.9 }, curV{ 0.0 };
	int selectedCitizen{ -1 };
	for (size_t c(0); c < m_citizens.size(); c++)
	{
		if (m_citizens[c]->GETplace() && ((curV = tileValue(m_tiles[m_citizens[c]->GETtileOccupied()])) < minValueTile))
		{
			minValueTile = curV;
			selectedCitizen = (int)c;
		}
	}

	m_citizens[selectedCitizen].reset();
	m_citizens.erase(m_citizens.begin() + selectedCitizen);
}

double CitizenManager::tileValue
(
	const Tile& tile,
	const double coefFood,
	const double coefWork,
	const double coefGold
)const
{
	double sum{ 0.0 };
	sum = tile.food * coefFood + tile.gold * coefGold + tile.work * coefWork;
	return sum;
}

void CitizenManager::computeEmotion()
{
	double result{ 0.0 };

	for (const auto& c : m_citizens)
	{
		result += (double)c->GEThappiness();
	}

	try
	{
		m_emotion = (unsigned int)R2D::ValueToScale::computeValueToScale
		(
			result,
			(double)Emotion_Type::angry,
			(double)Emotion_Type::ecstatic,
			EMOTION_RANGE::MIN,
			EMOTION_RANGE::MAX,
			(int)m_citizens.size()
		);
	}
	catch (std::string const& msg)
	{
		if (msg.compare("[ERROR]___: protectedDiv: div by 0") == STRINGS::IDENTICAL)
		{
			LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::COMPUTE_EMOTION, logS::DATA::ERROR_DIV_ZERO, msg);
			m_emotion = (unsigned int)EMOTION_RANGE::SCALE_MEAN;
#ifdef _DEBUG
			throw(msg);
#endif // _DEBUG
		}
		else if (msg.compare("[ERROR]___: computeValueToScale : checkMinMaxValidityRange") == STRINGS::IDENTICAL)
		{
			LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::COMPUTE_EMOTION, logS::DATA::ERROR_MIN_MAX_RANGE, msg);
			m_emotion = (unsigned int)EMOTION_RANGE::SCALE_MEAN;
#ifdef _DEBUG
			throw(msg);
#endif // _DEBUG
		}
	}
}

double CitizenManager::getWorkFromCitizen()const
{
	double rValue{0.0};
	for (const auto& c : m_citizens)
	{
		rValue += (double)c->GETwork();
	}
	return rValue;
}

double CitizenManager::getGoldFromCitizen()const
{
	double rValue{ 0.0 };
	for (const auto& c : m_citizens)
	{
		rValue += (double)c->GETgold();
	}
	return rValue;
}

double CitizenManager::getFoodFromCitizen()const
{
	double rValue{ 0.0 };
	for (const auto& c : m_citizens)
	{
		rValue += (double)c->GETfood();
	}
	return rValue;
}

jsoncons::ojson CitizenManager::saveToOjson()const
{
	jsoncons::ojson value;
	jsoncons::ojson citizens{ jsoncons::ojson::make_array() };

	for (const auto citizen : m_citizens)
	{
		citizens.push_back(citizen->saveToOjson());
	}
	value.insert_or_assign("Emotion", m_emotion);
	value.insert_or_assign("Citizens", citizens);
	return value;
}

void CitizenManager::loadFromOjson(const jsoncons::ojson& jsonLoad)
{
	if	(
			jsonLoad.contains("Emotion") && 
			jsonLoad.contains("Citizens") && 
			jsonLoad["Citizens"].is_array()
		)
	{
		m_emotion = jsonLoad["Emotion"].as<unsigned int>();

		for (const auto& citizen : jsonLoad["Citizens"].array_range())
		{
			addCitizen(true);
			m_citizens.back()->loadFromOjson(citizen);
		}
	}
}


/*
*	End Of File : CitizenManager.cpp
*/