/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.15.0
	file version : 1.7

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

#include "NewGame.h"
#include "GamePlayScreen.h"

#include "Player.h"
#include "App.h"
#include "SaveReload.h"

#include <RealEngine2D/src/GUI.h>



//----------------------------------------------------------NewGame----------------------------------------------------------------//

/* ----------------------------------------------------------------------------------- */
/* NAME : newGame																	   */
/* ROLE : Create a new save with new spaw settlers		 							   */
/* ROLE : Players names are associate to radio button		 						   */
/* ROLE : Save the new game set								 						   */
/* INPUT : void																		   */
/* RETURNED VALUE : void														       */
/* ------------------------------------------------------------------------------------*/
void GamePlayScreen::newGame()
{
	App::logfileconsole("[INFO]___: Newgame Start");
	
	m_SaveReload->createSave(*m_file);

	makePlayersButtons();

	newGameSettlerSpawn(m_players, m_mainMap);

	SaveReload::save(*this);

	/* ### Don't put code below here ### */

	App::logfileconsole("[INFO]___: Newgame End");
}

/* ----------------------------------------------------------------------------------- */
/* NAME : makePlayersButtons														   */
/* ROLE : Create for p, number of players, a radio button 							   */
/* ROLE : Button will be arrange in vertical axis and by p order					   */
/* INPUT : void																		   */
/* RETURNED VALUE : void														       */
/* ------------------------------------------------------------------------------------*/
void GamePlayScreen::makePlayersButtons()
{
	float X_POS = 0.01f;
	float Y_POS = 0.20f;
	const float DIMS_PIXELS = 20.0f;
	const float PADDING = 0.035f;
	const float TEXT_SCALE = 0.6f;
	const int GROUP_ID = 1;

	m_screen.m_vectPlayerRadioButton.clear();
	m_screen.m_widgetLabels.clear();
	m_screen.m_vectPlayerRadioButton.resize(m_userInputNewGame->vectPlayerName.size());
	m_screen.m_widgetLabels.resize(m_userInputNewGame->vectPlayerName.size());

	for (size_t i(0); i < m_screen.m_vectPlayerRadioButton.size(); i++)
	{
		m_players.addPlayer(m_userInputNewGame->vectPlayerName[i]);

		m_screen.m_vectPlayerRadioButton[i]
			= static_cast<CEGUI::RadioButton*>
			(m_screen.m_gui.createWidget(
				"TaharezLook/RadioButton",
				glm::vec4(X_POS, Y_POS += PADDING, 0.0f, 0.0f),
				glm::vec4(0.0f, 0.0f, DIMS_PIXELS, DIMS_PIXELS),
				m_userInputNewGame->vectPlayerName[i]));

		m_screen.m_vectPlayerRadioButton[i]->setSelected(false);

		m_screen.m_vectPlayerRadioButton[i]->subscribeEvent
		(CEGUI::RadioButton::EventMouseClick,
			CEGUI::Event::Subscriber(&GamePlayScreen::onPlayerButtonClicked, this));
		m_screen.m_vectPlayerRadioButton[i]->setGroupID(GROUP_ID);

		m_screen.m_widgetLabels[i] = RealEngine2D::WidgetLabel(
			m_screen.m_vectPlayerRadioButton[i],
			m_userInputNewGame->vectPlayerName[i],
			TEXT_SCALE);

	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME : newGameSettlerSpawn														   */
/* ROLE : Création des position pour les settlers de chaque joueurs					   */
/* IN/OUT : Players& players			   */
/* IN : const MainMap& mainMap												   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
void GamePlayScreen::newGameSettlerSpawn
(
	Players& players,
	const MainMap& mainMap
)
{
	/* ---------------------------------------------------------------------- */
	/* association des vecteurs de position (x,y)							  */
	/* avec les settlers de départ											  */
	/* ---------------------------------------------------------------------- */
	unsigned int selectunit(0);
	selectunit = Unit::searchUnitByName("settler", players.GETvectUnitTemplate());

	std::vector<randomPos> tabRandom;
	for (unsigned int i(0); i < players.GETvectPlayer().size(); i++)
	{

		makeRandomPosTab(mainMap, tabRandom);

		players.GETvectPlayer()[i]->addUnit
		("settler",
			tabRandom[i].x,
			tabRandom[i].y,
			players.GETvectUnitTemplate()[selectunit].type,
			players.GETvectUnitTemplate()[selectunit].life,
			players.GETvectUnitTemplate()[selectunit].atq,
			players.GETvectUnitTemplate()[selectunit].def,
			players.GETvectUnitTemplate()[selectunit].movement,
			players.GETvectUnitTemplate()[selectunit].level,
			MAINTENANCE_COST_1TH_SETTLER);
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME : makeRandomPosTab															   */
/* ROLE : WHILE new positions are not valid, create new ones						   */
/* ROLE : --- create new positions with matriceMap & tileSize						   */
/* ROLE : --- IF positions are valid - on ground THEN quit loop						   */
/* ROLE : --- IF IN_DEBUG && iteration loop > MAX_RANDOM_POS_ITERATION THEN THROW	   */
/* ROLE : Push new valid position to vector of new positions						   */
/* IN : const Map& map : struct main map : map & tileSize							   */
/* IN/OUT : std::vector<randomPos>& : New vector positions							   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
void GamePlayScreen::makeRandomPosTab
(
	const MainMap& mainMap,
	std::vector<randomPos>& tabRandom
)
{
	randomPos RandomPOS;
	bool continuer(true);
	unsigned int iteration(0);

	while (continuer)
	{
		if (iteration >= MAX_RANDOM_POS_ITERATION)
		{
#ifdef _DEBUG
			throw(MAX_RANDOM_POS_ITERATION);
#endif // DEBUG_MODE
			/*
			TODO : remove existing settlers and players
				 : return to main menu with error message "too many player with this map size"
			*/
		}
		iteration++;

		makeRandomPos(RandomPOS, mainMap.GETmatriceMapConst(), mainMap.GETtileSize());
		if (conditionground(mainMap.GETmatriceMapConst(), RandomPOS))
		{
			continuer = !conditionspace(RandomPOS, tabRandom, mainMap.GETtileSize());
		}
	}
	tabRandom.push_back(RandomPOS);
}

/* ----------------------------------------------------------------------------------- */
/* NAME : makeRandomPos																   */
/* ROLE : Create random positions between matriceMap								   */
/* ROLE : pos === size - 2 * MAP_BORDER_MAX * tileSize								   */
/* ROLE : Ceil value with tileSize													   */
/* OUT : randomPos& RandomPOS :	New random positions								   */
/* IN : const MatriceMap& matriceMap : matriceMap for size							   */
/* IN : const unsigned int tileSize	: Globale tileSize								   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
void GamePlayScreen::makeRandomPos
(
	randomPos& RandomPOS,
	const MatriceMap& matriceMap,
	const unsigned int tileSize
)
{
	const unsigned int SEA_BORDER_MAP(MAP_BORDER_MAX * tileSize);

	unsigned int x((rand() % ((matriceMap.size() * tileSize) - SEA_BORDER_MAP)) + SEA_BORDER_MAP);
	unsigned int y((rand() % ((matriceMap[0].size() * tileSize) - SEA_BORDER_MAP)) + SEA_BORDER_MAP);

	RandomPOS.x = (unsigned int)ceil(x / tileSize) * tileSize;
	RandomPOS.y = (unsigned int)ceil(y / tileSize) * tileSize;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : conditionspace															   */
/* ROLE : IF empty tab return TRUE													   */
/* ROLE : ELSE test every positions with new positions  							   */
/* ROLE : --- IF new position is in a square of spaceBetweenSettler THEN return FALSE  */
/* ROLE : --- ELSE new position is not in a square with every positions				   */
/* ROLE : ---			of spaceBetweenSettler THEN return TRUE						   */
/* INPUT : const randomPos& RandomPOS : Positions to test							   */
/* INPUT : const std::vector<randomPos>& tabRandom : tab of positions				   */
/* INPUT : unsigned int tileSize : Globale tileSize									   */
/* RETURNED VALUE : TRUE -> New positions valid									       */
/* RETURNED VALUE : FALSE -> New positions not valid						           */
/* ------------------------------------------------------------------------------------*/
bool GamePlayScreen::conditionspace
(
	const randomPos& RandomPOS,
	const std::vector<randomPos>& tabRandom,
	const unsigned int tileSize
)
{
	/* Return true : Empty tab */
	if (tabRandom.empty()) return true;

	const unsigned int spaceBetweenSettler(tileSize * MIN_SPACE_BETWEEN_SETTLER);

	bool condition(false);
	for (size_t i(0); i < tabRandom.size(); i++)
	{
		if (
			((int)RandomPOS.x >= (int)((int)tabRandom[i].x + (int)spaceBetweenSettler)) /* West */
			||
			((int)RandomPOS.x <= (int)((int)tabRandom[i].x - (int)spaceBetweenSettler)) /* East */
			||
			((int)RandomPOS.y >= (int)((int)tabRandom[i].y + (int)spaceBetweenSettler)) /* North */
			||
			((int)RandomPOS.y <= (int)((int)tabRandom[i].y - (int)spaceBetweenSettler)) /* South */
			)
		{
			condition = true;
		}
		else
		{
			return false;
		}
	}
	return condition;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : conditionground															   */
/* ROLE : Convert new positions to index											   */
/* ROLE : IF Assert index to maticeMap size && tile index is ground THEN return TRUE   */
/* ROLE : ELSE return FALSE															   */
/* INPUT : const MatriceMap& matriceMap	: Map matrice								   */
/* INPUT : const randomPos& RandomPOS :	New positions								   */
/* RETURNED VALUE : TRUE -> New positions valid									       */
/* RETURNED VALUE : FALSE -> New positions not valid						           */
/* ------------------------------------------------------------------------------------*/
bool GamePlayScreen::conditionground
(
	const MatriceMap& matriceMap,
	const randomPos& RandomPOS
)
{
	unsigned int x(MainMap::convertPosXToIndex(RandomPOS.x));
	unsigned int y(MainMap::convertPosYToIndex(RandomPOS.y));

	if	(
			MainMap::assertRangeMapIndex(x, matriceMap.size())
			&&
			MainMap::assertRangeMapIndex(y, matriceMap[x].size())
		)
	{
		if	(
				matriceMap[x][y].tile_ground
				==
				Ground_Type::grass
			)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		throw("[ERROR]___: GamePlay::conditionground : assertRangeMapIndex == false");
	}
}
