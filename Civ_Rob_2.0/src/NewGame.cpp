/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.4.0
	file version : 1.1

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

#include "GamePlaySrceen.h"
#include "NewGameScreen.h"
#include "Player.h"
#include "App.h"
#include "SaveReload.h"



void WidgetLabel::draw(RealEngine2D::SpriteBatch& sb, RealEngine2D::SpriteFont& sf, RealEngine2D::Window* w) {
	if (!widget->isVisible()) return;
	glm::vec2 pos;
	pos.x = widget->getInnerRectClipper().getPosition().d_x + widget->getInnerRectClipper().getWidth() / 2.0f;
	pos.y = w->GETscreenHeight() - widget->getInnerRectClipper().getPosition().d_y;

	sf.draw(sb, text.c_str(), pos, glm::vec2(0.24f), 0.0f, color, RealEngine2D::Justification::MIDDLE);
}


//----------------------------------------------------------NewGame----------------------------------------------------------------//


void NewGame::newGame(GamePlayScreen& mainGame)
{
	App::logfileconsole("[INFO]___: Newgame Start");

	mainGame.getSaveReload()->createSave(*mainGame.getFile());

	float X_POS = 0.01f;
	float Y_POS = 0.20f;
	const float DIMS_PIXELS = 20.0f;
	const float PADDING = 0.035f;
	const float TEXT_SCALE = 0.6f;
	const int GROUP_ID = 1;
	mainGame.GETscreen().m_vectPlayerRadioButton.clear();
	mainGame.GETscreen().m_widgetLabels.clear();
	mainGame.GETscreen().m_vectPlayerRadioButton.resize(mainGame.getUserInputNewGame()->vectPlayerName.size());
	mainGame.GETscreen().m_widgetLabels.resize(mainGame.getUserInputNewGame()->vectPlayerName.size());
	for (size_t i(0); i < mainGame.GETscreen().m_vectPlayerRadioButton.size(); i++)
	{
		
		mainGame.GETscreen().m_vectPlayerRadioButton[i] 
			= static_cast<CEGUI::RadioButton*>
			(mainGame.GETscreen().m_gui.createWidget(
				"TaharezLook/RadioButton",
				glm::vec4(X_POS, Y_POS += PADDING, 0.0f, 0.0f),
				glm::vec4(0.0f, 0.0f, DIMS_PIXELS, DIMS_PIXELS),
				mainGame.getUserInputNewGame()->vectPlayerName[i]));

		mainGame.GETscreen().m_vectPlayerRadioButton[i]->setSelected(false);

		mainGame.GETscreen().m_vectPlayerRadioButton[i]->subscribeEvent
		(CEGUI::RadioButton::EventMouseClick,
			CEGUI::Event::Subscriber(&GamePlayScreen::onPlayerButtonClicked, &mainGame));
		mainGame.GETscreen().m_vectPlayerRadioButton[i]->setGroupID(GROUP_ID);

		mainGame.GETscreen().m_widgetLabels[i] = WidgetLabel(
			mainGame.GETscreen().m_vectPlayerRadioButton[i],
			mainGame.getUserInputNewGame()->vectPlayerName[i],
			TEXT_SCALE);

	}

	newGameSettlerSpawn(mainGame.GETPlayers(), mainGame.GETmainMap());

	SaveReload::save(mainGame);

	/* ### Don't put code below here ### */

	App::logfileconsole("[INFO]___: Newgame End");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : newGameSettlerSpawn														   */
/* ROLE : Création des position pour les settlers de chaque joueurs					   */
/* INPUT : const std::vector<Unit_Template>& : tableau des statistiques ...			   */
/* INPUT : ...  par défauts des unités												   */
/* INPUT : const struct Map& map : structure globale de la map						   */
/* INPUT/OUTPUT : std::vector<Player*>& : vecteurs de joueurs						   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void NewGame::newGameSettlerSpawn
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
/* ----------------------------------------------------------------------------------- */
/* NAME : makeRandomPosTab															   */
/* ROLE : Créér autant de vecteur de position (x,y) que de joueur initial			   */
/* INPUT : const Map& map : structure globale de la map								   */
/* INPUT/OUTPUT : std::vector<randomPos>& : vecteurs de positions					   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void NewGame::makeRandomPosTab
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
			App::exitError("[ERROR]___: makeRandomPosTab, Too many Iterations");
#endif // DEBUG_MODE
			/*
			TODO : remove existing settlers and players
				 : return to main menu with error message "too many player with this map size"
			*/
		}
		iteration++;

		makeRandomPos(RandomPOS, mainMap.GETmatriceMapConst(), mainMap.GETtoolBarSize(), mainMap.GETtileSize());
		if (conditionground(mainMap.GETmatriceMapConst(), RandomPOS))
		{
			continuer = !conditionspace(RandomPOS, tabRandom, mainMap.GETtileSize());
		}
	}
	tabRandom.push_back(RandomPOS);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : makeRandomPos																   */
/* ROLE : créér un vecteur de position (x,y) aléatoire respectant la taille de l'écran */
/* OUTPUT : randomPos& RandomPOS : couple de positions								   */
/* INPUT : const std::vector<std::vector<Tile>>& maps : Matrice maps				   */
/* INPUT : unsigned int toolBarSize: taille de la barre d'outil						   */
/* INPUT : unsigned int tileSize													   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void NewGame::makeRandomPos
(
	randomPos& RandomPOS,
	const MatriceMap& matriceMap,
	unsigned int toolBarSize,
	unsigned int tileSize
)
{
	unsigned int x((rand() % ((unsigned int)(matriceMap.size() * tileSize) - (unsigned int)(toolBarSize * tileSize))) + (toolBarSize * tileSize));
	unsigned int y((rand() % (matriceMap[0].size() * tileSize)));
	RandomPOS.x = (unsigned int)ceil(x / tileSize) * tileSize;
	RandomPOS.y = (unsigned int)ceil(y / tileSize) * tileSize;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : conditionspace															   */
/* ROLE : condition pour valider les coordonnées crées:								   */
/* ROLE : etre en dehors d'un carré d'influence (ici tileSize * 8) d'une autre entitée */
/* INPUT : const randomPos& RandomPOS : couple de positions							   */
/* INPUT : const std::vector<randomPos>& : vecteurs de positions					   */
/* INPUT : unsigned int tileSize													   */
/* INPUT : unsigned int i : couple de positions courant								   */
/* RETURNED VALUE    : true -> condition de position validée / false -> non valide     */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
bool NewGame::conditionspace
(
	const randomPos& RandomPOS,
	const std::vector<randomPos>& tabRandom,
	unsigned int tileSize
)
{
	unsigned int spaceBetweenSettler(tileSize * MIN_SPACE_BETWEEN_SETTLER);

	for (size_t i(0); i < tabRandom.size(); i++)
	{
		if (
			(RandomPOS.x >= (tabRandom[i].x - spaceBetweenSettler)) /* West */
			&&
			(RandomPOS.x <= (tabRandom[i].x + spaceBetweenSettler)) /* East */
			&&
			(RandomPOS.y >= (tabRandom[i].y - spaceBetweenSettler)) /* North */
			&&
			(RandomPOS.y <= (tabRandom[i].y + spaceBetweenSettler)) /* South */
			)
		{
			return false;
		}
	}
	return true;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : conditionground															   */
/* ROLE : condition pour valider les coordonnées crées:								   */
/* ROLE : - etre sur une tile possédant la caractéristique d'etre du sol			   */
/* INPUT : const std::vector<std::vector<Tile>>& : Matrice de la map				   */
/* INPUT : const std::vector<randomPos>& : vecteurs de positions					   */
/* RETURNED VALUE    : true -> condition de position validée / false -> non valide	   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
bool NewGame::conditionground
(
	const MatriceMap& matriceMap,
	const randomPos& RandomPOS
)
{
	unsigned int x(MainMap::convertPosXToIndex(RandomPOS.x));
	unsigned int y(MainMap::convertPosYToIndex(RandomPOS.y));

	if (
		MainMap::assertRangeMapIndex(x, matriceMap.size())
		&&
		MainMap::assertRangeMapIndex(y, matriceMap[x].size())
		)
	{
		if (
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
