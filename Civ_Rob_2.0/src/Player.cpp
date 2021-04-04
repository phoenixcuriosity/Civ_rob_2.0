/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.7.0
	file version : 1.16

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
	m_selectedUnit(NO_UNIT_SELECTED),
	m_selectedCity(NO_CITY_SELECTED),
	m_goldStats{ INITIAL_GOLD , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
	m_onOffDisplay{ false }
{
	App::logfileconsole("[INFO]___: Create Player Par Defaut Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Player																	   */
/* ROLE : Constructeur par nom du joueur											   */
/* INPUT : const std::string&														   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Player::Player(const std::string& msg) :
	m_name(msg),
	m_selectedUnit(NO_UNIT_SELECTED), m_selectedCity(NO_CITY_SELECTED),
	m_goldStats{ INITIAL_GOLD , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
	m_onOffDisplay{ false }
{
	App::logfileconsole("[INFO]___: Create Player Success");
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

	unsigned int size((unsigned int)m_tabUnit.size());

	for (unsigned int i(0); i < size; i++)
	{
		delete m_tabUnit[i];

		//MainGame::logfileconsole("[INFO]___: Kill Unit n:" + std::to_string(i) + " of Player: " + m_name + " Success");
	}
	m_tabUnit.clear();
	
	size = (unsigned int)m_tabCity.size();

	for (unsigned int i(0); i < size; i++)
	{
		delete m_tabCity[i];

		//MainGame::logfileconsole("[INFO]___: Kill Citie n:" + std::to_string(i) + " of Player: " + m_name + " Success");
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
	m_tabUnit.push_back(new Unit());
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
	unsigned int level,
	double maintenance
)
{
	m_tabUnit.push_back(new Unit(name, x, y, movementType, life, atq, def, move, level, maintenance));
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
	unsigned int index
)
{
	if (Utility::assertSize(m_tabUnit.size(), index))
	{
		if (nullptr != m_tabUnit[index])
		{
			delete m_tabUnit[index];
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
	unsigned int x,
	unsigned int y,
	VectMap& tiles
)
{
	m_tabCity.push_back(new City(name, x, y, tiles));
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
	unsigned int index
)
{

	if (Utility::assertSize(m_tabCity.size(), index))
	{
		if (nullptr != m_tabCity[index])
		{
			delete m_tabCity[index];
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
	double goldToAdd
)
{
	m_goldStats.goldConversionSurplus += goldToAdd;
}


/* *********************************************************
 *				END Player::METHODS						   *
 ********************************************************* */



Players::Players()
:
m_selectedPlayer(NO_PLAYER_SELECTED),
m_citiesNameMaxToCreate(0),
m_vectCityName(),
m_vectUnitTemplate(),
m_vectID(),
m_vectPlayer(),
m_spriteBatchUnit(),
m_needToUpdateDrawUnit(true)
{

}

Players::~Players()
{
	for (unsigned int i(0); i < m_vectPlayer.size(); i++)
	{
		removeIndexPlayer(i);
	}
}

void Players::init(const std::string& filePath)
{
	m_vectID.resize(m_vectUnitTemplate.size() + LIFE_BAR_NB_SUBDIVISION + NB_MAX_PLAYER);

	/* Unit Texture */
	for (unsigned int i(0); i < m_vectUnitTemplate.size(); i++)
	{
		m_vectID[i] = RealEngine2D::ResourceManager::getTexture(filePath + "units/" + m_vectUnitTemplate[i].name + EXTENSION_PNG)->GETid();
	}

	/* Lifebar Texture */
	for (unsigned int i(0); i < LIFE_BAR_NB_SUBDIVISION - 1; i++)
	{
		m_vectID[m_vectUnitTemplate.size() + i]
			= RealEngine2D::ResourceManager::getTexture(filePath + "barre de vie/" + "0." + std::to_string(i) + "life" + EXTENSION_PNG)->GETid();
	}

	m_vectID[m_vectUnitTemplate.size() + LIFE_BAR_NB_SUBDIVISION - 1]
		= RealEngine2D::ResourceManager::getTexture(filePath + "barre de vie/" + "maxlife" + EXTENSION_PNG)->GETid();

	/* Appartenance Texture */
	for (unsigned int i(0); i < NB_MAX_PLAYER; i++)
	{
		m_vectID[m_vectUnitTemplate.size() + LIFE_BAR_NB_SUBDIVISION + i]
			= RealEngine2D::ResourceManager::getTexture(filePath + "couleur d'apartenance/" + "ColorPlayer" + std::to_string(i) + EXTENSION_PNG)->GETid();
	}

	m_spriteBatchUnit.init();
}

void Players::addPlayer(const std::string& name)
{
	m_vectPlayer.push_back(new Player(name));
}

void Players::removeIndexPlayer
(
	unsigned int index
)
{
	if (Utility::assertSize(m_vectPlayer.size(), index))
	{
		if (nullptr != m_vectPlayer[index])
		{
			delete m_vectPlayer[index];
		}
	}
	else
	{
		throw("[ERROR]__: removeIndexPlayer : assertSize");
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
		unsigned int tileSize = mainMap.GETtileSize();

		for (unsigned int i(0); i < m_vectPlayer.size(); i++)
		{
			for (unsigned int j(0); j < m_vectPlayer[i]->GETtabUnit().size(); j++)
			{
				Unit* unit = m_vectPlayer[i]->GETtabUnit()[j];
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
						m_vectID[Unit::searchUnitByName(unit->GETname(), m_vectUnitTemplate)],
						0.0f,
						RealEngine2D::COLOR_WHITE
					);

					/* Lifebar Texture */
					m_spriteBatchUnit.draw
					(
						glm::vec4(unit->GETx() + tileSize / 4, unit->GETy(), tileSize /2, 3),
						RealEngine2D::FULL_RECT,
						m_vectID
						[
							m_vectUnitTemplate.size() - 1
							+ 
							(int)std::floor(Utility::computeValueToScale(unit->GETlife(), 0, unit->GETmaxlife(), 0.0, (double)LIFE_BAR_NB_SUBDIVISION))
						],
						0.0f,
						RealEngine2D::COLOR_WHITE
					);

					/* Appartenance Texture */
					m_spriteBatchUnit.draw
					(
						glm::vec4(unit->GETx(), unit->GETy(), tileSize / 8, tileSize / 8),
						RealEngine2D::FULL_RECT,
						m_vectID
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
		}

		m_spriteBatchUnit.end();

		m_needToUpdateDrawUnit = false;
	}
}

void Players::renderUnit()
{
	m_spriteBatchUnit.renderBatch();
}

 /*
 *	End Of File : Player.cpp
 */