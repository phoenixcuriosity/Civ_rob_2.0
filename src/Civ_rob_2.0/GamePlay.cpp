/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.22.3.0
	file version : 1.18

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

#include "GamePlay.h"

#include "IHM.h"
#include "LoadConfig.h"
#include "civ_lib.h"
#include "End.h"

/* *********************************************************
 *					  Static Var						   *
 ********************************************************* */

/* Init in main with LoadConfig::updateStaticValues -> GamePlay::getPtrTileSize */
static unsigned int* s_tileSize;

/* Init in main with LoadConfig::updateStaticValues -> GamePlay::getScreenWidth */
static Uint16* s_screenWidth;

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : getPtrTileSize															   */
/* ROLE : Initialize ptr on tileSize from sysinfo									   */
/* INPUT : unsigned int* const : ptr on tileSize									   */
/* RETURNED VALUE : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void GamePlay::getPtrTileSize
(
	 unsigned int* const ptrtileSize
)
{
	s_tileSize = ptrtileSize;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : getPtrScreenWidth															   */
/* ROLE : Initialize ptr on screenWidth from sysinfo								   */
/* INPUT : Uint16* const : ptr on screenWidth										   */
/* RETURNED VALUE : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void GamePlay::getPtrScreenWidth
(
	Uint16* const ptrscreenWidth
)
{
	s_screenWidth = ptrscreenWidth;
}


/* *********************************************************
 *			START GamePlay::STATIC::NEW-GAME			   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : newGame																	   */
/* ROLE : Initialisation de la nouvelle partie										   */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
/* RETURNED VALUE : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void GamePlay::newGame
(
	Sysinfo& sysinfo
)
{
	LoadConfig::logfileconsole("[INFO]___: Newgame Start");
	sysinfo.var.statescreen = State_Type::STATEscreenNewgame;

	SaveReload::createSave(sysinfo);

	SDL_RenderClear(sysinfo.screen.renderer);

	/* *********************************************************
	 *						Nb player ?						   *
	 ********************************************************* */

	/* ---------------------------------------------------------------------- */
	/* Première demande au joueur : 										  */
	/* Le nombre de joueurs ?												  */
	/* ---------------------------------------------------------------------- */
	sysinfo.allTextes.newGame["Press Return or kpad_Enter to valid selection"]->render();
	sysinfo.allTextes.newGame["How many player(s) (max 9):"]->render();
	SDL_RenderPresent(sysinfo.screen.renderer);

	sysinfo.var.cinState = CinState_Type::cinScreenNewGameNbPlayer;
	sysinfo.var.waitEvent = true;

	unsigned int space(32);

	sysinfo.var.tempX = sysinfo.screen.screenWidth / 2;
	sysinfo.var.tempY = 164;

	/* ---------------------------------------------------------------------- */
	/* Le joueur doit rentrer une valeur entre 1 et 9, par défaut 1 		  */
	/* ---------------------------------------------------------------------- */
	KeyboardMouse::checkCaseSDL(sysinfo);

	/* *********************************************************
	 *					Name of player ?					   *
	 ********************************************************* */

	sysinfo.var.tempY += space;
	sysinfo.var.cinState = CinState_Type::cinScreenNewGameNamePlayer;

	/* ---------------------------------------------------------------------- */
	/* Deuxième demande au joueur : 										  */
	/* Le nom des joueurs													  */
	/* ---------------------------------------------------------------------- */
	for (unsigned int i(0); i < sysinfo.var.nbPlayer; i++)
	{
		sysinfo.var.waitEvent = true;

		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font, Index_staticIndexVectorTextes::PLAYER_NAME,
			Texte_Type::blended, "Name of player nb:" + std::to_string(i), { 255, 0, 0, 255 }, NoColor,
			24, sysinfo.screen.screenWidth / 2, sysinfo.var.tempY, nonTransparent, no_angle, Center_Type::center_x);

		SDL_RenderPresent(sysinfo.screen.renderer);

		sysinfo.var.tempY += space;

		/* ---------------------------------------------------------------------- */
		/* Valeur par défaut avec incrémentation en fonction			 		  */
		/* du nombre de joueur : noName									 		  */
		/* ---------------------------------------------------------------------- */
		KeyboardMouse::checkCaseSDL(sysinfo);

		sysinfo.var.s_player.tabPlayerName.push_back(sysinfo.var.tempPlayerName);
		sysinfo.var.tempPlayerName = EMPTY_STRING;
		sysinfo.tabplayer.push_back(new Player(sysinfo.var.s_player.tabPlayerName[i]));
		sysinfo.var.tempY += space;
	}

	/* *********************************************************
	 *					Map Generation						   *
	 ********************************************************* */
	
	groundGen(sysinfo.map, sysinfo.screen.screenWidth);
	newGameSettlerSpawn
		(
			sysinfo.var.s_player.tabUnit_Template,
			sysinfo.map,
			sysinfo.tabplayer
		);

	/* *********************************************************
	 *							Save						   *
	 ********************************************************* */

	SaveReload::save(sysinfo);

	/* *********************************************************
	 *					 Button Creation					   *
	 ********************************************************* */
	
	/* ---------------------------------------------------------------------- */
	/* Création des boutons pour séléctionner les joueurs			 		  */
	/* ---------------------------------------------------------------------- */
	
	sysinfo.var.statescreen = State_Type::STATEmainMap;
	sysinfo.var.cinState = CinState_Type::cinMainMap;
	
	GamePlay::createPlayerButton(sysinfo);

	/* ### Don't put code below here ### */

	LoadConfig::logfileconsole("[INFO]___: Newgame End");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : groundGen																	   */
/* ROLE : Génération du sol et des spec de la map									   */
/* INPUT/OUTPUT : Map& map : structure de la MAP									   */
/* INPUT : Uint16 screenWidth : taille en de l'écran en pixel (axe x)				   */
/* RETURNED VALUE : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void GamePlay::groundGen
(
	Map& map,
	Uint16 screenWidth
)
{
	LoadConfig::logfileconsole("[INFO]___: Groundgen Start");
	
	for (Uint8 i(0); i < map.mapSize / map.tileSize; i++)
	{
		for (Uint8 j(0); j < map.mapSize / map.tileSize; j++)
		{
			
			map.maps[i][j].indexX = i + (Uint8)((screenWidth / 10) / map.tileSize);
			map.maps[i][j].indexY = j;
			map.maps[i][j].tile_x = convertIndexToPosX(i);
			map.maps[i][j].tile_y = convertIndexToPosY(j);
			

			/* *********************************************************
			 *			bord de la map (MAP_BORDER_ZERO)			   *
			 ********************************************************* */

			if (   (i == MAP_BORDER_ZERO)
				|| (i == (map.mapSize / map.tileSize) - (MAP_BORDER_ZERO + 1))
				|| (j == MAP_BORDER_ZERO)
				|| (j == (map.mapSize / map.tileSize) - (MAP_BORDER_ZERO + 1))
				)
			{
				tileAffectation
				(
					map.maps[i][j],
					Ground_Type::deepwater,
					(std::string)"deepwater.bmp",
					GroundSpec_Type::nothing,
					GROUNDSPEC_NOTHING,
					0,
					0,
					0
				);
			}
					
			/* *********************************************************
			 *	  bord de la map (MAP_BORDER_MIN to MAP_BORDER_MAX)    *
			 ********************************************************* */

			else if (mapBordersConditions(map, i, j))
			{
				mapBorders(map.maps[i][j]);
			}

			/* *********************************************************
			 *					reste de la map						   *
			 ********************************************************* */
			else
			{
				mapIntern(map.maps, i, j);
			}
		}
	}
	LoadConfig::logfileconsole("[INFO]___: Groundgen End");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : mapBordersConditions														   */
/* ROLE : Boucle For de conditions													   */
/* ROLE : Nombre de conditions = (MAP_BORDER_MAX - MAP_BORDER_MIN) * 2				   */
/* INPUT : const Map& map : structure de la MAP										   */
/* INPUT : unsigned int i : index en X												   */
/* INPUT : unsigned int j : index en Y												   */
/* RETURNED VALUE : bool : valid = true / not valid = false							   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
bool GamePlay::mapBordersConditions
(
	const Map& map,
	unsigned int i,
	unsigned int j
)
{
	for (unsigned int index(MAP_BORDER_MIN); index < MAP_BORDER_MAX; index++)
	{
		if	(
				(i == index)
				||
				(i == (map.mapSize / map.tileSize) - (index + 1))
				||
				(j == index)
				||
				(j == (map.mapSize / map.tileSize) - (index + 1))
			)
		{
			return true;
		}
	}
	return false;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : mapBorders																   */
/* ROLE : Affectation des caractéristiques de la case en fonction ...				   */
/* ROLE : ... de la fonction rand, dans la bordure de la map entre ...				   */
/* ROLE : ... MAP_BORDER_MIN et MAP_BORDER_MAX										   */
/* OUTPUT : Tile& tile : tile à affecter											   */
/* RETURNED VALUE : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void GamePlay::mapBorders
(
	Tile& tile
)
{
	unsigned int randomspecwaterborder
	((rand() % MAP_GEN_RANDOM_RANGE_SPEC_WATER_BORDER) + MAP_GEN_RANDOM_OFFSET_SPEC_WATER_BORDER);
	switch (randomspecwaterborder)
	{
	case 1:
		tileAffectation
		(	tile,
			Ground_Type::water,
			(std::string)"water.bmp",
			GroundSpec_Type::fish,
			(std::string)"fish.bmp",
			3,
			2,
			1);
		break;
	case 2:
		tileAffectation
		(	tile,
			Ground_Type::water,
			(std::string)"water.bmp",
			GroundSpec_Type::petroleum,
			(std::string)"petroleum.bmp",
			1,
			3,
			4);
		break;
	default:
		/* N/A */
		break;
	}
	if (randomspecwaterborder > 2)
	{
		tileAffectation
		(tile,
			Ground_Type::water,
			(std::string)"water.bmp",
			GroundSpec_Type::nothing,
			GROUNDSPEC_NOTHING,
			1,
			1,
			1);
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : mapIntern																	   */
/* ROLE : Affectation des caractéristiques de la case en fonction ...				   */
/* ROLE : ... de la fonction rand, dans le reste de la map							   */
/* ROLE : Si la case est de type water alors création de 2 autres ...				   */
/* ROLE : ... cases de type water pour obtenir une forme en L						   */
/* INPUT/OUTPUT : std::vector<std::vector<Tile>>& maps : matrice de la map			   */
/* INPUT : unsigned int i : index en X												   */
/* INPUT : unsigned int j : index en Y												   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void GamePlay::mapIntern
(
	std::vector<std::vector<Tile>>& maps,
	unsigned int i,
	unsigned int j
)
{
	unsigned int	randomground(0),
					randomspecgrass(0),
					randomspecwater(0),
					randomspecwater1(0),
					randomspecwater2(0);

	randomground = rand() % MAP_GEN_RANDOM_RANGE_GROUND + MAP_GEN_RANDOM_OFFSET_GROUND;
	if (randomground < 92)
	{
		maps[i][j].tile_ground = Ground_Type::grass;
		maps[i][j].tile_stringground = "grass.bmp";
		randomspecgrass =
			rand() % MAP_GEN_RANDOM_RANGE_SPEC_GRASS + MAP_GEN_RANDOM_OFFSET_SPEC_GRASS;
		switch (randomspecgrass)
		{
		case 1:
			maps[i][j].tile_spec = GroundSpec_Type::coal;
			maps[i][j].tile_stringspec = "coal.png";
			break;
		case 2:
			maps[i][j].tile_spec = GroundSpec_Type::copper;
			maps[i][j].tile_stringspec = "copper.png";
			break;
		case 3:
			maps[i][j].tile_spec = GroundSpec_Type::iron;
			maps[i][j].tile_stringspec = "iron.png";
			break;
		case 4:
			maps[i][j].tile_spec = GroundSpec_Type::tree;
			maps[i][j].tile_stringspec = "tree1.bmp";
			break;
		case 5:
			maps[i][j].tile_spec = GroundSpec_Type::stone;
			maps[i][j].tile_stringspec = "stone.png";
			break;
		case 6:
			maps[i][j].tile_spec = GroundSpec_Type::uranium;
			maps[i][j].tile_stringspec = "uranium.png";
			break;
		case 7:
			maps[i][j].tile_spec = GroundSpec_Type::horse;
			maps[i][j].tile_stringspec = "horse.bmp";
			break;
		default:
			/* N/A */
			break;
		}
		if (randomspecgrass > 7 && randomspecgrass <= 32)
		{ // plus de chance d'avoir des arbres
			maps[i][j].tile_spec = GroundSpec_Type::tree;
			maps[i][j].tile_stringspec = "tree1.bmp";
			maps[i][j].food = 1;
			maps[i][j].work = 2;
			maps[i][j].gold = 1;
		}
		else if (randomspecgrass > 32)
		{
			maps[i][j].tile_spec = GroundSpec_Type::nothing;
			maps[i][j].tile_stringspec = GROUNDSPEC_NOTHING;
			maps[i][j].food = 2;
			maps[i][j].work = 1;
			maps[i][j].gold = 1;
		}
		else if (randomspecgrass <= 7)
		{
			maps[i][j].food = 1;
			maps[i][j].work = 2;
			maps[i][j].gold = 3;
		}
		else
		{
			/* N/A */
		}
	}
	else
	{

		/* *********************************************************
		 *		génération de l'eau -> forme en L (3 cases)		   *
		 ********************************************************* */

		/* 1er case */

		if (i > 2 && j > 2)
		{
			randomspecwater =
				rand() % MAP_GEN_RANDOM_RANGE_SPEC_WATER + MAP_GEN_RANDOM_OFFSET_SPEC_WATER;
			switch (randomspecwater)
			{
			case 1:
				tileAffectation
				(	maps[i][j],
					Ground_Type::water,
					(std::string)"water.bmp",
					GroundSpec_Type::fish,
					(std::string)"fish.bmp",
					3,
					2,
					1);
				break;
			case 2:
				tileAffectation
				(	maps[i][j],
					Ground_Type::water,
					(std::string)"water.bmp",
					GroundSpec_Type::petroleum,
					(std::string)"petroleum.bmp",
					1,
					3,
					4);
				break;
			default:
				/* N/A */
				break;
			}
			if (randomspecwater > 2)
				tileAffectation
				(	maps[i][j],
					Ground_Type::water,
					(std::string)"water.bmp",
					GroundSpec_Type::nothing,
					GROUNDSPEC_NOTHING,
					1,
					1,
					1);
		}
		else
		{
			/* N/A */
		}

		/* 2ème case */

		if (Ground_Type::deepwater != maps[i - 1][j].tile_ground)
		{
			randomspecwater1 =
				rand() % MAP_GEN_RANDOM_RANGE_SPEC_WATER1 + MAP_GEN_RANDOM_OFFSET_SPEC_WATER1;
			switch (randomspecwater1)
			{
			case 1:
				tileAffectation
				(	maps[i - 1][j],
					Ground_Type::water,
					(std::string)"water.bmp",
					GroundSpec_Type::fish,
					(std::string)"fish.bmp",
					3,
					2,
					1);
				break;
			case 2:
				tileAffectation
				(	maps[i - 1][j],
					Ground_Type::water,
					(std::string)"water.bmp",
					GroundSpec_Type::petroleum,
					(std::string)"petroleum.bmp",
					1,
					3,
					4);
				break;
			default:
				/* N/A */
				break;
			}
			if (randomspecwater1 > 2)
				tileAffectation
				(	maps[i - 1][j],
					Ground_Type::water,
					(std::string)"water.bmp",
					GroundSpec_Type::nothing,
					GROUNDSPEC_NOTHING,
					1,
					1,
					1);
		}
		else
		{
			/* N/A */
		}

		/* 3ème case */

		if (Ground_Type::deepwater != maps[i - 1][j - 1].tile_ground)
		{
			randomspecwater2 =
				rand() % MAP_GEN_RANDOM_RANGE_SPEC_WATER2 + MAP_GEN_RANDOM_OFFSET_SPEC_WATER2;
			switch (randomspecwater2)
			{
			case 1:
				tileAffectation
				(	maps[i - 1][j - 1],
					Ground_Type::water,
					(std::string)"water.bmp",
					GroundSpec_Type::fish,
					(std::string)"fish.bmp",
					3,
					2,
					1);
				break;
			case 2:
				tileAffectation
				(	maps[i - 1][j - 1],
					Ground_Type::water,
					(std::string)"water.bmp",
					GroundSpec_Type::petroleum,
					(std::string)"petroleum.bmp",
					1,
					3,
					4);
				break;
			default:
				/* N/A */
				break;
			}
			if (randomspecwater2 > 2)
				tileAffectation
				(	maps[i - 1][j - 1],
					Ground_Type::water,
					(std::string)"water.bmp",
					GroundSpec_Type::nothing,
					GROUNDSPEC_NOTHING,
					1,
					1,
					1);
		}
		else
		{
			/* N/A */
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : tileAffectation															   */
/* ROLE : Affectation des caractéristiques à une case								   */
/* OUTPUT : Tile& tile, : la case à affecter										   */
/* INPUT : Uint8 tile_ground, std::string tile_stringground,						   */
/* INPUT : Uint8 tile_spec, std::string tile_stringspec,							   */
/* INPUT : int8_t food, int8_t work, int8_t gold									   */
/* RETURNED VALUE : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void GamePlay::tileAffectation
(	
	Tile& tile,
	Ground_Type tile_ground,
	std::string tile_stringground,
	GroundSpec_Type tile_spec,
	std::string tile_stringspec,
	int8_t food,
	int8_t work,
	int8_t gold
)
{
	tile.tile_ground = tile_ground;
	tile.tile_stringground = tile_stringground;
	tile.tile_spec = tile_spec;
	tile.tile_stringspec = tile_stringspec;
	tile.food = food;
	tile.work = work;
	tile.gold = gold;
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
void GamePlay::newGameSettlerSpawn
(
	const std::vector<Unit_Template>& tabUnit_Template,
	const Map& map,
	std::vector<Player*>& tabplayer
)
{
	/* ---------------------------------------------------------------------- */
	/* association des vecteurs de position (x,y)							  */
	/* avec les settlers de départ											  */
	/* ---------------------------------------------------------------------- */
	unsigned int selectunit(0);
	selectunit = Unit::searchUnitByName("settler", tabUnit_Template);

	std::vector<randomPos> tabRandom;
	for (unsigned int i(0); i < tabplayer.size(); i++)
	{

		makeRandomPosTab(map, tabRandom);

		tabplayer[i]->addUnit
		(	"settler",
			tabRandom[i].x,
			tabRandom[i].y,
			tabUnit_Template[selectunit].type,
			tabUnit_Template[selectunit].life,
			tabUnit_Template[selectunit].atq,
			tabUnit_Template[selectunit].def,
			tabUnit_Template[selectunit].movement,
			tabUnit_Template[selectunit].level,
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
void GamePlay::makeRandomPosTab
(
	const Map& map,
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
#ifdef _DEBUG_MODE
			End::exitError("[ERROR]___: makeRandomPosTab, Too many Iterations");
#endif // DEBUG_MODE
			/*
			TODO : remove existing settlers and players 
				 : return to main menu with error message "too many player with this map size"
			*/
		}
		iteration++;

		makeRandomPos(RandomPOS, map.maps, map.toolBarSize, map.tileSize);
		if (conditionground(map.maps, RandomPOS))
		{
			continuer = !conditionspace(RandomPOS, tabRandom);
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
void GamePlay::makeRandomPos
(	
	randomPos& RandomPOS,
	const std::vector<std::vector<Tile>>& maps,
	unsigned int toolBarSize,
	unsigned int tileSize
)
{
	int x((rand() % ((unsigned int)(maps.size() * tileSize) - (unsigned int)(toolBarSize * tileSize))) + (toolBarSize * tileSize));
	int y((rand() % (maps[0].size() * tileSize)));
	RandomPOS.x = (int)ceil(x / tileSize) * tileSize;
	RandomPOS.y = (int)ceil(y / tileSize) * tileSize;
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
bool GamePlay::conditionspace
(	
	const randomPos& RandomPOS,
	const std::vector<randomPos>& tabRandom
)
{
	int spaceBetweenSettler(*s_tileSize * MIN_SPACE_BETWEEN_SETTLER);

	for (unsigned int i(0); i < tabRandom.size(); i++)
	{
		if	(
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
bool GamePlay::conditionground
(
	const std::vector<std::vector<Tile>>& maps,
	const randomPos& RandomPOS
)
{
	unsigned int x(convertPosXToIndex(RandomPOS.x));
	unsigned int y(convertPosYToIndex(RandomPOS.y));

	if	(
			assertRangeMapIndex(x, maps.size())
			&&
			assertRangeMapIndex(y, maps[x].size())
		)
	{
		if	(
				maps[x][y].tile_ground
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

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : convertIndexToPosX														   */
/* ROLE : Convert the index of the matrix Map to a position on X axis in pixel		   */
/* ROLE : Offset by toolBar size													   */
/* ROLE : Use 2 input static const ptr : s_tileSize and s_screenWidth				   */
/* INPUT : unsigned int index : index to convert									   */
/* RETURNED VALUE : unsigned int : position on X axis in pixel						   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
unsigned int GamePlay::convertIndexToPosX
(
	unsigned int index
)
{
	return *s_tileSize * index + (*s_screenWidth / 10);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : convertPosXToIndex														   */
/* ROLE : Convert position on X axis in pixel of the matrix Map to a index			   */
/* ROLE : Offset by toolBar size													   */
/* ROLE : Use 2 input static const ptr : s_tileSize and s_screenWidth				   */
/* INPUT : unsigned int index : position on X axis in pixel	to convert				   */
/* RETURNED VALUE : unsigned int : index											   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
unsigned int GamePlay::convertPosXToIndex
(
	unsigned int posX
)
{
	return (posX - (*s_screenWidth / 10)) / *s_tileSize;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : convertIndexToPosY														   */
/* ROLE : Convert the index of the matrix Map to a position on Y axis in pixel		   */
/* ROLE : Use 1 input static const ptr : s_tileSize									   */
/* INPUT : unsigned int index : index to convert									   */
/* RETURNED VALUE : unsigned int : position on Y axis in pixel						   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
unsigned int GamePlay::convertIndexToPosY
(
	unsigned int index
)
{
	return *s_tileSize * index;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : convertPosXToIndex														   */
/* ROLE : Convert position on Y axis in pixel of the matrix Map to a index			   */
/* ROLE : Use 1 input static const ptr : s_tileSize									   */
/* INPUT : unsigned int index : position on Y axis in pixel	to convert				   */
/* RETURNED VALUE : unsigned int : index											   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
unsigned int GamePlay::convertPosYToIndex
(
	unsigned int posY
)
{
	return posY / *s_tileSize;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : assertRangeMapIndex														   */
/* ROLE : assert that the index provided is between 0 and size						   */
/* INPUT : unsigned int indexToTest : index to compare to size						   */
/* INPUT : size_t size : reference size								 				   */
/* RETURNED VALUE : bool : false -> indexToTest is equal or > than size				   */
/* RETURNED VALUE : bool : true -> indexToTest is <	than size						   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
bool GamePlay::assertRangeMapIndex
(
	unsigned int indexToTest,
	size_t size
)
{
	return indexToTest < size ? true : false;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : createPlayerButton														   */
/* ROLE : Create a number of Buttons equal to the number of player					   */
/* INPUT/OUTPUT : struct Sysinfo& : Global structure								   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void GamePlay::createPlayerButton
(
	Sysinfo& sysinfo
)
{
	int initspacename(200), spacename(24);

	for (unsigned int i(0); i < sysinfo.tabplayer.size(); i++)
	{
		ButtonTexte::createButtonTexte
		(sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var.statescreen,
			sysinfo.var.select,
			sysinfo.allButton.player,
			Texte_Type::shaded,
			sysinfo.var.s_player.tabPlayerName[i],
			{ 127, 255, 127, 255 },
			{ 64, 64, 64, 255 },
			16,
			0,
			initspacename += spacename,
			nonTransparent,
			no_angle);
	}
}


/* *********************************************************
 *			 END GamePlay::STATIC::NEW-GAME				   *
 ********************************************************* */


 
 
/* *********************************************************
 *			 START GamePlay::STATIC::NextTurn			   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : nextTurn																	   */
/* ROLE : Action à réaliser lors du passage à un nouveau tour					       */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void GamePlay::nextTurn
(
	Sysinfo& sysinfo
)
{
	for (unsigned int i(0); i < sysinfo.tabplayer.size(); i++) 
	{
		sysinfo.tabplayer[i]->resetGoldStats();
		for (unsigned int j(0); j < sysinfo.tabplayer[i]->GETtabUnit().size(); j++) 
		{
			sysinfo.tabplayer[i]->GETtheUnit(j)->RESETmovement();
			sysinfo.tabplayer[i]->GETtheUnit(j)->heal(sysinfo.map.maps, i);
		}
		for (unsigned int j(0); j < sysinfo.tabplayer[i]->GETtabCity().size(); j++)
		{
			/* computeEmotion must be in first : Emotion use on other computations */
			sysinfo.tabplayer[i]->GETtheCity(j)->computeEmotion();

			/* Food */
			sysinfo.tabplayer[i]->GETtheCity(j)->foodNextTurn(sysinfo.tabplayer[i]->GETgoldStats());

			/* Work */
			sysinfo.tabplayer[i]->GETtheCity(j)->computeWork();
			sysinfo.tabplayer[i]->GETtheCity(j)
				->computeWorkToBuild
					(
						sysinfo.tabplayer[i],
						sysinfo.var.s_player.tabUnit_Template
					);

			/* Gold */
			sysinfo.tabplayer[i]->GETtheCity(j)->computeGold();
			sysinfo.tabplayer[i]->GETtheCity(j)->addCityGoldToTaxIncome(sysinfo.tabplayer[i]->GETgoldStats());
		}
		sysinfo.tabplayer[i]->computeGold();
	}
	sysinfo.var.nbturn++;
}


/* *********************************************************
 *				END GamePlay::STATIC::NextTurn			   *
 ********************************************************* */

/*
*	End Of File : GamePlay.cpp
*/
