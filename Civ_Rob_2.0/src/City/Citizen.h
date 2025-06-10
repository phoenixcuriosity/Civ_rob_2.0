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
#pragma once

#include "../LIB.h"

struct Tile;

namespace city
{

class Citizen
{
public:
	enum class Emotion_Type
	{
		ecstatic = 2,
		happy = 1,
		neutral = 0,
		sad = -1,
		angry = -2
	};

	enum class Religion_Type
	{
		catholic,
		protestant,
		reformed,
		anglican,
		orthodox,
		coptic,
		sunni,
		shiite,
		ibadi,
		buddhism,
		vajrayana,
		mahayana,
		confucianism,
		shinto,
		hinduism,
		sikhism,
		animism,
		shamanism,
		totemism,
		inti,
		nahuatl,
		jewish,
		zoroastrian
	};

	/* Define the maximum range of emotion */
	static constexpr double EMOTION_MAX = 100.0;

	/* Define the minimum range of emotion */
	static constexpr double EMOTION_MIN = 0.0;

	/* Define the mean emotion */
	static constexpr double EMOTION_MEAN = ((EMOTION_MAX + EMOTION_MIN) / 2.0);

public:
	Citizen();
	Citizen(const Tile& tile);
	Citizen(const unsigned int tileOccupied,
			const int food,
			const int work,
			const int gold);
	virtual ~Citizen();

public:
	jsoncons::ojson saveToOjson()const;
	void loadFromOjson(const jsoncons::ojson& jsonLoad);

public:
	inline void SETtileOccupied(unsigned int tileOccupied) { m_tileOccupied = tileOccupied; };
	inline void SEThappiness(Emotion_Type happiness) { m_happiness = happiness; };
	inline void SETfood(int food) { m_food = food; };
	inline void SETwork(int work) { m_work = work; };
	inline void SETgold(int gold) { m_gold = gold; };
	inline void SETrevolt(int revolt) { m_revolt = revolt; };
	inline void SETreligion(Religion_Type religion) { m_religion = religion; };
	inline void SETplace(bool place) { m_place = place; };

	inline unsigned int GETtileOccupied()const { return m_tileOccupied; };
	inline Emotion_Type GEThappiness()const { return m_happiness; };
	inline int GETfood()const { return m_food; };
	inline int GETwork()const { return m_work; };
	inline int GETgold()const { return m_gold; };
	inline int GETrevolt()const { return m_revolt; };
	inline Religion_Type GETreligion()const { return m_religion; };
	inline bool GETplace()const { return m_place; };

private:
	unsigned int m_tileOccupied;
	Emotion_Type m_happiness;
	int m_food;
	int m_work;
	int m_gold;
	int m_revolt;
	Religion_Type m_religion;

	bool m_place;
};

}
