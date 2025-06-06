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
#include "jsonloader.h"
#include "LogSentences.h"
#include "MainMap.h"
#include "Player.h"
#include "SaveReload.h"
#include "Utility.h"

#include <jsoncons/json.hpp>
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

Players::Players(R2D::RegisterPairVector& registerLoad, MatriceMapPtrT matriceMapPtrT)
:
m_selectedPlayer(SELECTION::NO_PLAYER_SELECTED),
m_selectedPlayerPtr(),
m_selectedCity(),
m_vectPlayer(),
m_idTexture(),
m_spriteBatchUnit(),
m_needToUpdateDrawUnit(true),
m_spriteBatchCity(),
m_needToUpdateDrawCity(true),
m_matriceMapPtrT(matriceMapPtrT),
m_registerLoad(registerLoad)
{
	SaveReload::getInstance().registerSaveable(R2D::e_Files::savePlayers, this);
	SaveReload::getInstance().registerLoadable(R2D::e_Files::savePlayers, this);
	m_spriteBatchCityDynamic.init();
}

Players::~Players()
{
	SaveReload::getInstance().unRegisterSaveable(R2D::e_Files::savePlayers, this);
	SaveReload::getInstance().unRegisterLoadable(R2D::e_Files::savePlayers, this);
	deleteAllPlayers();
}

void Players::init(const GamePlayScreenTexture& idTexture)
{
	m_idTexture = idTexture;
	m_spriteBatchUnit.init();
	m_spriteBatchCity.init();
}

void Players::addPlayer
(
	const std::string& name,
	const int id
)
{
	m_vectPlayer.push_back(Player::create(name, id));
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
					u->getX() == x
					&&
					u->getY() == y
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
			bool prevShow{ u->m_show };
			u->cmpblit();
			if (prevShow != u->m_show)
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

				if (unit->m_show)
				{
					if	(
							camera.isBoxInView
							(
								{ unit->getX(), unit->getY() },
								{ tileSize , tileSize },
								mainMap.GETtoolBarSize() * tileSize
							)
						)
					{

						const GamePlayScreenEnumTexture idTunit
							{ static_cast<GamePlayScreenEnumTexture>(
								static_cast<size_t>(GamePlayScreenEnumTexture::battleoids)
								+ static_cast<size_t>(UnitTemplate::getSingleton().searchUnitByName(unit->GETname()))
							)};

						/* Unit Texture */
						m_spriteBatchUnit.draw
						(
							glm::vec4(unit->getX(), unit->getY(), tileSize, tileSize),
							R2D::FULL_RECT,
							m_idTexture[idTunit],
							0.0f,
							R2D::COLOR_WHITE
						);

						/* Lifebar Texture */
						if (unit->isFullLife())
						{
							m_spriteBatchUnit.draw
							(
								glm::vec4(unit->getX() + tileSize / 4, unit->getY(), tileSize / 2, 3),
								R2D::FULL_RECT,
								m_idTexture[GamePlayScreenEnumTexture::maxlife],
								0.0f,
								R2D::COLOR_WHITE
							);
						}
						else
						{
							m_spriteBatchUnit.draw
							(
								glm::vec4(unit->getX() + tileSize / 4, unit->getY(), tileSize / 2, 3),
								R2D::FULL_RECT,
								m_idTexture[static_cast<GamePlayScreenEnumTexture>(static_cast<size_t>(GamePlayScreenEnumTexture::life0) +
									std::floor(R2D::ValueToScale::computeValueToScale(unit->GETlife(), 0, unit->GETmaxlife(), 0.0, 9.99)))],
								0.0f,
								R2D::COLOR_WHITE
							);
						}


						/* Appartenance Texture */
						m_spriteBatchUnit.draw
						(
							glm::vec4(unit->getX(), unit->getY(), tileSize / 8, tileSize / 8),
							R2D::FULL_RECT,
							m_idTexture[static_cast<GamePlayScreenEnumTexture>(static_cast<size_t>(GamePlayScreenEnumTexture::ColorPlayer0) + i)],
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
							{ city->getCoor().x, city->getCoor().y },
							{ tileSize , tileSize },
							mainMap.GETtoolBarSize() * tileSize
						)
					)
				{
					/* City Texture */
					m_spriteBatchCity.draw
					(
						glm::vec4(city->getCoor().x, city->getCoor().y, tileSize, tileSize),
						R2D::FULL_RECT,
						m_idTexture[GamePlayScreenEnumTexture::city],
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
							static_cast<float>(city->getCoor().x),
							static_cast<float>(city->getCoor().y)
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

jsoncons::ojson Players::saveToOjson()const
{
	jsoncons::ojson value;
	jsoncons::ojson players{ jsoncons::ojson::make_array() };;

	for (const auto& player : m_vectPlayer)
	{
		players.push_back(player->saveToOjson());
	}

	value.insert_or_assign(jsonloader::KEY_PLAYERS, players);

	return value;
}

void Players::loadFromOjson(const jsoncons::ojson& jsonLoad)
{
	if (jsonLoad.contains(jsonloader::KEY_PLAYERS) && jsonLoad[jsonloader::KEY_PLAYERS].is_array())
	{
		for (const auto& player : jsonLoad[jsonloader::KEY_PLAYERS].array_range())
		{
			if (player.contains("m_name") && player.contains("m_id"))
			{
				assert(m_matriceMapPtrT);
				if (m_matriceMapPtrT)
				{
					addPlayer(player["m_name"].as_string(), player["m_id"].as<int32_t>());
					m_vectPlayer.back()->loadFromOjson(player, *m_matriceMapPtrT);
				}
			}
			else
			{
				LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_SAVE_PLAYER, logS::DATA::MISSING_KEY_JSON,
					R2D::ResourceManager::getFile(R2D::e_Files::savePlayers), jsonloader::KEY_PLAYERS);
			}
		}
	}
	else
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_SAVE_PLAYER, logS::DATA::MISSING_KEY_JSON,
			R2D::ResourceManager::getFile(R2D::e_Files::savePlayers), jsonloader::KEY_PLAYERS);
	}
}

 /*
 *	End Of File : Players.cpp
 */