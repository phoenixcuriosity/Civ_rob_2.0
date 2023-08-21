/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.3.0
	file version : 1.28

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

#include "Player.h"

#include "Utility.h"
#include "App.h"
#include "City.h"

#include <RealEngine2D/src/ResourceManager.h>
#include <RealEngine2D/src/ValueToScale.h>
#include <RealEngine2D/src/ErrorLog.h> 


namespace
{
	const unsigned int LIFE_BAR_NB_SUBDIVISION = 11;

	const unsigned int VECT_SIZE_OFFSET_ID = 1;

	const unsigned int CITY_TYPE = 1;
}

 /* *********************************************************
  *				START Player::METHODS					   *
  ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Player																	   */
/* ROLE : Constructeur par défaut													   */
/* INPUT : void																		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Player::Player() :
	m_name("NoName"),
	m_tabUnit(),
	m_tabCity(),
	m_selectedUnit(SELECTION::NO_UNIT_SELECTED),
	m_selectedCity(SELECTION::NO_CITY_SELECTED),
	m_goldStats{ PlayerH::INITIAL_GOLD , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
	m_onOffDisplay{ false }
{
	RealEngine2D::ErrorLog::logEvent("[INFO]___: Create Player Par Defaut Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Player																	   */
/* ROLE : Constructeur par nom du joueur											   */
/* INPUT : const std::string&														   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Player::Player
(
	const std::string& name,
	const int id
) 
:
	m_name(name),
	m_id(id),
	m_tabUnit(),
	m_tabCity(),
	m_selectedUnit(SELECTION::NO_UNIT_SELECTED),
	m_selectedCity(SELECTION::NO_CITY_SELECTED),
	m_goldStats{ PlayerH::INITIAL_GOLD , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
	m_onOffDisplay{ false }
{
	RealEngine2D::ErrorLog::logEvent("[INFO]___: Create Player Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : ~Player																	   */
/* ROLE : Initialisation d'une Unit vide											   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Player::~Player()
{
	deletePlayer();
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : operator=																	   */
/* ROLE : Redéfinition de l'opérateur =												   */
/* INPUT : const Player& player : l'objet à copier									   */
/* RETURNED VALUE : Player&	: l'objet recopié										   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Player& Player::operator=
(
	const Player& player
)
{
	if (this != &player)
	{
		deletePlayer();
		m_name = player.GETname();
		m_tabUnit = player.GETtabUnit();
		m_tabCity = player.GETtabCity();
		m_goldStats = player.GETgoldStatsConst();
	}
	return *this;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : deletePlayer																   */
/* ROLE : Destruction de l'objet et de ses ptr										   */
/* INPUT : void																		   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::deletePlayer()
{
	for (auto& u : m_tabUnit)
	{
		u.reset();
	}
	m_tabUnit.clear();

	for (auto& c : m_tabCity)
	{
		c.reset();
	}
	m_tabCity.clear();
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : addEmptyUnit																   */
/* ROLE : Initialisation d'une Unit vide											   */
/* INPUT : void																		   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::addEmptyUnit()
{
	m_tabUnit.push_back(std::make_shared<Unit>());
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : addUnit																	   */
/* ROLE : Ajout une Unit avec les spécifications demandées (nom, positions, ...)	   */
/* INPUT : Spécifications demandées (nom, positions, ...)							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::addUnit
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
)
{
	m_tabUnit.push_back
	(
		std::make_shared<Unit>
		(
			name, x, y, movementType, life, atq, def, move, numberOfAttack, level, maintenance, this
		)
	);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : deleteUnit																   */
/* ROLE : Suppression d'une Unit du joueur											   */
/* INPUT : unsigned int : index de Unit dans le tableau								   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::deleteUnit
(
	const unsigned int index
)
{
	if (Utility::assertSize(m_tabUnit.size(), index))
	{
		if (nullptr != m_tabUnit[index])
		{
			m_tabUnit[index].reset();
			if (m_tabUnit.size() > 1 && index < m_tabUnit.size() - 1)
			{
				for (unsigned int i(index); i < (m_tabUnit.size() - 1); i++)
					m_tabUnit[i] = m_tabUnit[(unsigned __int64)i + 1];
			}
			m_tabUnit.pop_back();
		}
		else
		{
			throw("[ERROR]__: deleteUnit : nullptr == m_tabUnit[index]");
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : addCity																	   */
/* ROLE : Ajout une City avec les spécifications demandées (nom, positions, ...)	   */
/* INPUT : Spécifications demandées (nom, positions, ...)							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::addCity
(
	const std::string& name,
	const unsigned int x,
	const unsigned int y,
	VectMap& tiles
)
{
	m_tabCity.push_back(std::make_shared<City>(name, x, y, tiles));
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : deleteCity																   */
/* ROLE : Suppression d'une City du joueur											   */
/* INPUT : unsigned int : index de City dans le tableau								   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::deleteCity
(
	const unsigned int index
)
{

	if (Utility::assertSize(m_tabCity.size(), index))
	{
		if (nullptr != m_tabCity[index])
		{
			m_tabCity[index].reset();
			if (m_tabCity.size() > 1 && index < m_tabCity.size() - 1)
			{
				for (unsigned int i(index); i < (m_tabCity.size() - 1); i++)
					m_tabCity[i] = m_tabCity[(unsigned __int64)i + 1];
			}
			m_tabCity.pop_back();
		}
		else
		{
			throw("[ERROR]__: deleteCity : nullptr == m_tabCity[index]");
		}
	}
}

std::shared_ptr<City>* Player::searchCity
(
	const unsigned int indexX,
	const unsigned int indexY
)
{
	for (auto &c : m_tabCity)
	{
		if (c->searchCityTile(indexX, indexY)) return &c;
	}
	return nullptr;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : computeGold																   */
/* ROLE : Compute income and cost then the balance between the two					   */
/* ROLE : Add balance to the player gold											   */
/* INPUT : void																		   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::computeGold()
{
	computeMaintenanceCostUnit();

	m_goldStats.income = m_goldStats.taxIncome
		+ m_goldStats.commerceIncome
		+ m_goldStats.goldConversionSurplus;

	m_goldStats.cost = m_goldStats.buildingsCost
		+ m_goldStats.armiesCost;

	m_goldStats.goldBalance = m_goldStats.income - m_goldStats.cost;
	m_goldStats.gold += m_goldStats.goldBalance;

}

void Player::computeMaintenanceCostUnit()
{
	/*
	for (unsigned int i(0); i < m_tabUnit.size(); i++)
	{
		m_goldStats.armiesCost += m_tabUnit[i]->GETmaintenance();
	}
	*/
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : resetGoldStats															   */
/* ROLE : Reset all stats of m_goldStats except gold									   */
/* INPUT : void																		   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::resetGoldStats()
{
	m_goldStats.goldBalance = 0.0;
	m_goldStats.cost = 0.0;
	m_goldStats.taxIncome = 0.0;
	m_goldStats.commerceIncome = 0.0;
	m_goldStats.goldConversionSurplus = 0.0;
	m_goldStats.buildingsCost = 0.0;
	m_goldStats.armiesCost = 0.0;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : resetGoldStats															   */
/* ROLE : Reset all stats of m_goldStats except gold									   */
/* INPUT : double goldToAdd	: gold to add in goldConversionSurplus					   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Player::addGoldToGoldConversionSurplus
(
	const double goldToAdd
)
{
	m_goldStats.goldConversionSurplus += goldToAdd;
}


/* *********************************************************
 *				END Player::METHODS						   *
 ********************************************************* */



Players::Players()
:
m_selectedPlayer(SELECTION::NO_PLAYER_SELECTED),
m_selectedPlayerPtr(),
m_selectedCity(),
m_vectCityName(),
m_vectUnitTemplate(),
m_vectIDUnit(),
m_vectCityTemplate(),
m_vectIDCity(),
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

void Players::init(const std::string& filePath)
{
	/*---UNIT---*/

	m_vectIDUnit.resize(m_vectUnitTemplate.size() + LIFE_BAR_NB_SUBDIVISION + PlayerH::NB_MAX_PLAYER);

	/* Unit Texture */
	for (unsigned int i(0); i < m_vectUnitTemplate.size(); i++)
	{
		m_vectIDUnit[i] = RealEngine2D::ResourceManager::getTexture(filePath + "units/" + m_vectUnitTemplate[i].name + EXTENSION_PNG)->GETid();
	}

	/* Lifebar Texture */
	for (unsigned int i(0); i < LIFE_BAR_NB_SUBDIVISION - 1; i++)
	{
		m_vectIDUnit[m_vectUnitTemplate.size() + i]
			= RealEngine2D::ResourceManager::getTexture(filePath + "barre de vie/" + "0." + std::to_string(i) + "life" + EXTENSION_PNG)->GETid();
	}

	m_vectIDUnit[m_vectUnitTemplate.size() + LIFE_BAR_NB_SUBDIVISION - 1]
		= RealEngine2D::ResourceManager::getTexture(filePath + "barre de vie/" + "maxlife" + EXTENSION_PNG)->GETid();

	/* Appartenance Texture */
	for (unsigned int i(0); i < PlayerH::NB_MAX_PLAYER; i++)
	{
		m_vectIDUnit[m_vectUnitTemplate.size() + LIFE_BAR_NB_SUBDIVISION + i]
			= RealEngine2D::ResourceManager::getTexture(filePath + "couleur d'apartenance/" + "ColorPlayer" + std::to_string(i) + EXTENSION_PNG)->GETid();
	}

	m_spriteBatchUnit.init();

	/*---CITY---*/

	m_vectIDCity.resize(CITY_TYPE);

	m_vectIDCity[0] = RealEngine2D::ResourceManager::getTexture(filePath + "city/city" + EXTENSION_PNG)->GETid();

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
		std::shared_ptr<Player> p{ m_vectPlayer[m_selectedPlayer] };
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
		std::shared_ptr<Player> p{ m_vectPlayer[m_selectedPlayer] };

		if (p->GETselectedUnit() != SELECTION::NO_UNIT_SELECTED)
		{
			std::shared_ptr<Unit> u{ p->GETtabUnit()[p->GETselectedUnit()] };
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
	RealEngine2D::Camera2D& camera
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
				std::shared_ptr<Unit>unit(m_vectPlayer[i]->GETtabUnit()[j]);

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
							RealEngine2D::FULL_RECT,
							m_vectIDUnit[Unit::searchUnitByName(unit->GETname(), m_vectUnitTemplate)],
							0.0f,
							RealEngine2D::COLOR_WHITE
						);

						/* Lifebar Texture */
						m_spriteBatchUnit.draw
						(
							glm::vec4(unit->GETx() + tileSize / 4, unit->GETy(), tileSize / 2, 3),
							RealEngine2D::FULL_RECT,
							m_vectIDUnit
							[
								m_vectUnitTemplate.size() - VECT_SIZE_OFFSET_ID
								+
								(int)std::floor(RealEngine2D::ValueToScale::computeValueToScale(unit->GETlife(), 0, unit->GETmaxlife(), 0.0, (double)LIFE_BAR_NB_SUBDIVISION))
							],
							0.0f,
							RealEngine2D::COLOR_WHITE
						);

						/* Appartenance Texture */
						m_spriteBatchUnit.draw
						(
							glm::vec4(unit->GETx(), unit->GETy(), tileSize / 8, tileSize / 8),
							RealEngine2D::FULL_RECT,
							m_vectIDUnit
							[
								m_vectUnitTemplate.size()
								+
								LIFE_BAR_NB_SUBDIVISION
								+
								i
							],
							0.0f,
							RealEngine2D::COLOR_WHITE
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
	RealEngine2D::Camera2D& camera,
	std::shared_ptr<RealEngine2D::SpriteFont>& font
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
				std::shared_ptr<City>city(m_vectPlayer[i]->GETtabCity()[j]);

				
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
						RealEngine2D::FULL_RECT,
						m_vectIDCity[0],
						0.0f,
						RealEngine2D::COLOR_WHITE
					);

					/* City Name */
					font->draw
					(
						m_spriteBatchCityDynamic,
						city->GETname().c_str(),
						glm::vec2(500.0f, 500.0f), // offset pos
						glm::vec2(0.32f), // size
						0.0f,
						RealEngine2D::COLOR_WHITE
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
	std::shared_ptr<City>* ptrCity{};
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
 *	End Of File : Player.cpp
 */