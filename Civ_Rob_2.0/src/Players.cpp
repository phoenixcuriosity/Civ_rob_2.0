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

#include "Players.h"

#include "App.h"
#include "City.h"
#include "LogSentences.h"
#include "MainMap.h"
#include "Player.h"
#include "Unit.h"
#include "Utility.h"
#include "T_Unit.h"

#include <R2D/src/ErrorLog.h> 
#include <R2D/src/Log.h> 
#include <R2D/src/GLTexture.h>
#include <R2D/src/ResourceManager.h>
#include <R2D/src/ValueToScale.h>



namespace
{
	constexpr unsigned int LIFE_BAR_NB_SUBDIVISION = 11;

	constexpr unsigned int VECT_SIZE_OFFSET_ID = 1;

	constexpr unsigned int CITY_TYPE = 1;
}

Players::Players()
:
m_selectedPlayer(SELECTION::NO_PLAYER_SELECTED),
m_selectedPlayerPtr(),
m_selectedCity(),
m_vectCityName(),
m_vectUnitTemplate(),
m_vectCityTemplate(),
m_vectPlayer(),
m_spriteBatchUnit(),
m_needToUpdateDrawUnit(true),
m_spriteBatchCity(),
m_needToUpdateDrawCity(true)
{
	m_spriteBatchCityDynamic.init();
}

Players::~Players()
{
	deleteAllPlayers();
}

void Players::init()
{
	R2D::ResourceManager::copyIdMap(m_idMap);

	m_spriteBatchUnit.init();
	m_spriteBatchCity.init();
}

void Players::addPlayer
(
	const std::string& name,
	const int id
)
{
	m_vectPlayer.push_back(std::make_shared<Player>(name, id));
}

void Players::deleteAllPlayers()
{
	for (auto& p : m_vectPlayer)
	{
		p.reset();
	}
}

void Players::removeIndexPlayer
(
	const unsigned int index
)
{
	if (Utility::assertSize(m_vectPlayer.size(), index))
	{
		m_vectPlayer[index].reset();
	}
	else
	{
		throw("[ERROR]__: removeIndexPlayer : assertSize");
	}
}

void Players::clickToSelectUnit
(
	const unsigned int x,
	const unsigned int y
)
{
	if (m_selectedPlayer != SELECTION::NO_PLAYER_SELECTED)
	{
		PlayerPtrT p{ m_vectPlayer[m_selectedPlayer] };
		unsigned int i{ 0 };
		for (const auto& u : p->GETtabUnit())
		{
			if	(
					u->GETx() == x
					&&
					u->GETy() == y
				)
			{
				p->SETselectedUnit(i);
				break;
			}
			i++;
		}
		p.reset();
	}
}


void Players::isAUnitSelected()
{
	if (m_selectedPlayer != SELECTION::NO_PLAYER_SELECTED)
	{
		PlayerPtrT p{ m_vectPlayer[m_selectedPlayer] };

		if (p->GETselectedUnit() != SELECTION::NO_UNIT_SELECTED)
		{
			UnitPtrT u{ p->GETtabUnit()[p->GETselectedUnit()] };
			bool prevShow{ u->GETshow() };
			u->cmpblit();
			if (prevShow != u->GETshow())
			{
				m_needToUpdateDrawUnit = true;
			}
		}
	}
}

void Players::drawUnit
(
	const MainMap& mainMap,
	R2D::Camera2D& camera
)
{
	if (m_needToUpdateDrawUnit)
	{
		m_spriteBatchUnit.begin();
		const unsigned int tileSize{ mainMap.GETtileSize() };

		for (unsigned int i(0); i < m_vectPlayer.size(); i++)
		{
			for (unsigned int j(0); j < m_vectPlayer[i]->GETtabUnit().size(); j++)
			{
				UnitPtrT unit(m_vectPlayer[i]->GETtabUnit()[j]);

				if (unit->GETshow())
				{
					if	(
							camera.isBoxInView
							(
								{ unit->GETx(), unit->GETy() },
								{ tileSize , tileSize },
								mainMap.GETtoolBarSize() * tileSize
							)
						)
					{
						/* Unit Texture */
						m_spriteBatchUnit.draw
						(
							glm::vec4(unit->GETx(), unit->GETy(), tileSize, tileSize),
							R2D::FULL_RECT,
							m_idMap[unit->GETname()],
							0.0f,
							R2D::COLOR_WHITE
						);

						/* Lifebar Texture */
						if (unit->GETlife() == unit->GETmaxlife())
						{
							m_spriteBatchUnit.draw
							(
								glm::vec4(unit->GETx() + tileSize / 4, unit->GETy(), tileSize / 2, 3),
								R2D::FULL_RECT,
								m_idMap["maxlife"],
								0.0f,
								R2D::COLOR_WHITE
							);
						}
						else
						{
							m_spriteBatchUnit.draw
							(
								glm::vec4(unit->GETx() + tileSize / 4, unit->GETy(), tileSize / 2, 3),
								R2D::FULL_RECT,
								m_idMap[std::format("{:.1f}life",
									R2D::ValueToScale::computeValueToScale(unit->GETlife(), 0, unit->GETmaxlife(), 0.0, 0.99))],
								0.0f,
								R2D::COLOR_WHITE
							);
						}
						

						/* Appartenance Texture */
						m_spriteBatchUnit.draw
						(
							glm::vec4(unit->GETx(), unit->GETy(), tileSize / 8, tileSize / 8),
							R2D::FULL_RECT,
							m_idMap[std::format("ColorPlayer{}", i)],
							0.0f,
							R2D::COLOR_WHITE
						);

					}
				}
				unit.reset();
			}
		}

		m_spriteBatchUnit.end();

		m_needToUpdateDrawUnit = false;
	}
}

void Players::renderUnit()
{
	m_spriteBatchUnit.renderBatch();
}

void Players::drawCity
(
	const MainMap& mainMap,
	R2D::Camera2D& camera,
	SpriteFont_PtrT& font
)
{
	if (m_needToUpdateDrawCity)
	{
		m_spriteBatchCity.begin();
		m_spriteBatchCityDynamic.begin();

		const unsigned int tileSize{ mainMap.GETtileSize() };

		for (unsigned int i(0); i < m_vectPlayer.size(); i++)
		{
			for (unsigned int j(0); j < m_vectPlayer[i]->GETtabCity().size(); j++)
			{
				CityPtrT city(m_vectPlayer[i]->GETtabCity()[j]);

				
				if	(
						camera.isBoxInView
						(
							{ city->GETx(), city->GETy() },
							{ tileSize , tileSize },
							mainMap.GETtoolBarSize() * tileSize
						)
					)
				{
					/* City Texture */
					m_spriteBatchCity.draw
					(
						glm::vec4(city->GETx(), city->GETy(), tileSize, tileSize),
						R2D::FULL_RECT,
						m_idMap["city"],
						0.0f,
						R2D::COLOR_WHITE
					);

					/* City Name */
					font->draw
					(
						m_spriteBatchCityDynamic,
						city->GETname().c_str(),
						glm::vec2
						(
							static_cast<float>(city->GETx()),
							static_cast<float>(city->GETy())
						), // offset pos
						glm::vec2(0.32f), // size
						0.0f,
						R2D::COLOR_WHITE
					);
				}
				city.reset();
			}
		}

		m_spriteBatchCity.end();
		m_spriteBatchCityDynamic.end();

		m_needToUpdateDrawCity = false;
	}
}

void Players::renderCity()
{
	m_spriteBatchCity.renderBatch();
	m_spriteBatchCityDynamic.renderBatch();
}


bool Players::searchCity
(
	const unsigned int indexX,
	const unsigned int indexY
)
{
	CityPtrT* ptrCity{};
	for (auto& p : m_vectPlayer)
	{
		ptrCity = p->searchCity(indexX, indexY);
		if (ptrCity != nullptr && *ptrCity != nullptr)
		{
			m_selectedCity = *ptrCity;
			return true;
		}
	}
	return false;
}

 /*
 *	End Of File : Players.cpp
 */