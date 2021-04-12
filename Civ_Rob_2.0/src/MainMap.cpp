/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.13.0
	file version : 1.23

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

#include "MainMap.h"

#include <RealEngine2D/src/ResourceManager.h>

#include "App.h"

 /* *********************************************************
  *					  Static Var						   *
  ********************************************************* */

static unsigned int* s_tileSize;

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : getPtrTileSize															   */
/* ROLE : Initialize ptr on tileSize from sysinfo									   */
/* INPUT : unsigned int* const : ptr on tileSize									   */
/* RETURNED VALUE : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void MainMap::setStaticPtrTileSize()
{
	s_tileSize = &m_tileSize;
}


MainMap::MainMap()
	:m_mapSizePixX(0), m_mapSizePixY(0),
	m_tileSize(0), m_toolBarSize(0), m_needToUpdateDraw(true)
{
	setStaticPtrTileSize();
}

MainMap::~MainMap()
{

}


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initTile																	   */
/* ROLE : Initialisation des cases de la map en fonction de sa taille				   */
/* INPUT : struct Map& : données générale de la map : taille						   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void MainMap::initTile()
{
	Tile blankTile;
	std::vector<Tile> blank;
	for (unsigned int i(0); i < m_mapSizePixX / m_tileSize; i++)
	{
		m_matriceMap.push_back(blank);
		for (unsigned int j(0); j < m_mapSizePixY / m_tileSize; j++)
		{
			m_matriceMap[i].push_back(blankTile);
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : groundGen																	   */
/* ROLE : G�n�ration du sol et des spec de la map									   */
/* INPUT/OUTPUT : Map& map : structure de la MAP									   */
/* INPUT : Uint16 screenWidth : taille en de l'�cran en pixel (axe x)				   */
/* RETURNED VALUE : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void MainMap::generateMap()
{
	App::logfileconsole("[INFO]___: Groundgen Start");

	for (unsigned int i(0); i < m_mapSizePixX / m_tileSize; i++)
	{
		for (unsigned int j(0); j < m_mapSizePixY / m_tileSize; j++)
		{

			m_matriceMap[i][j].indexX = i;
			m_matriceMap[i][j].indexY = j;
			m_matriceMap[i][j].tile_x = convertIndexToPosX(i);
			m_matriceMap[i][j].tile_y = convertIndexToPosY(j);


			/* *********************************************************
			 *			bord de la map (MAP_BORDER_ZERO)			   *
			 ********************************************************* */

			if (
				(i == MAP_BORDER_ZERO)
				|| (i == (m_mapSizePixX / m_tileSize) - (MAP_BORDER_ZERO + 1))
				|| (j == MAP_BORDER_ZERO)
				|| (j == (m_mapSizePixY / m_tileSize) - (MAP_BORDER_ZERO + 1))
				)
			{
				tileAffectation
				(
					m_matriceMap[i][j],
					Ground_Type::deepwater,
					GroundSpec_Type::nothing,
					0,
					0,
					0
				);
			}

			/* *********************************************************
			 *	  bord de la map (MAP_BORDER_MIN to MAP_BORDER_MAX)    *
			 ********************************************************* */

			else if (mapBordersConditions(i, j))
			{
				mapBorders(m_matriceMap[i][j]);
			}

			/* *********************************************************
			 *					reste de la map						   *
			 ********************************************************* */
			else
			{
				mapIntern(m_matriceMap, i, j);
			}
		}
	}

	App::logfileconsole("[INFO]___: Groundgen End");
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
bool MainMap::mapBordersConditions
(
	unsigned int i,
	unsigned int j
)
{
	for (unsigned int index(MAP_BORDER_MIN); index < MAP_BORDER_MAX; index++)
	{
		if (
			(i == index)
			||
			(i == (m_mapSizePixX / m_tileSize) - (index + 1))
			||
			(j == index)
			||
			(j == (m_mapSizePixY / m_tileSize) - (index + 1))
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
/* ROLE : Affectation des caract�ristiques de la case en fonction ...				   */
/* ROLE : ... de la fonction rand, dans la bordure de la map entre ...				   */
/* ROLE : ... MAP_BORDER_MIN et MAP_BORDER_MAX										   */
/* OUTPUT : Tile& tile : tile � affecter											   */
/* RETURNED VALUE : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void MainMap::mapBorders
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
		(tile,
			Ground_Type::water,
			GroundSpec_Type::fish,
			3,
			2,
			1);
		break;
	case 2:
		tileAffectation
		(tile,
			Ground_Type::water,
			GroundSpec_Type::petroleum,
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
			GroundSpec_Type::nothing,
			1,
			1,
			1);
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : mapIntern																	   */
/* ROLE : Affectation des caract�ristiques de la case en fonction ...				   */
/* ROLE : ... de la fonction rand, dans le reste de la map							   */
/* ROLE : Si la case est de type water alors cr�ation de 2 autres ...				   */
/* ROLE : ... cases de type water pour obtenir une forme en L						   */
/* INPUT/OUTPUT : std::vector<std::vector<Tile>>& maps : matrice de la map			   */
/* INPUT : unsigned int i : index en X												   */
/* INPUT : unsigned int j : index en Y												   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void MainMap::mapIntern
(
	MatriceMap& maps,
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
		randomspecgrass =
			rand() % MAP_GEN_RANDOM_RANGE_SPEC_GRASS + MAP_GEN_RANDOM_OFFSET_SPEC_GRASS;
		switch (randomspecgrass)
		{
		case 1:
			maps[i][j].tile_spec = GroundSpec_Type::coal;
			break;
		case 2:
			maps[i][j].tile_spec = GroundSpec_Type::copper;
			break;
		case 3:
			maps[i][j].tile_spec = GroundSpec_Type::iron;
			break;
		case 4:
			maps[i][j].tile_spec = GroundSpec_Type::tree;
			break;
		case 5:
			maps[i][j].tile_spec = GroundSpec_Type::stone;
			break;
		case 6:
			maps[i][j].tile_spec = GroundSpec_Type::uranium;
			break;
		case 7:
			maps[i][j].tile_spec = GroundSpec_Type::horse;
			break;
		default:
			/* N/A */
			break;
		}
		if (randomspecgrass > 7 && randomspecgrass <= 32)
		{ // plus de chance d'avoir des arbres
			maps[i][j].tile_spec = GroundSpec_Type::tree;
			maps[i][j].food = 1;
			maps[i][j].work = 2;
			maps[i][j].gold = 1;
		}
		else if (randomspecgrass > 32)
		{
			maps[i][j].tile_spec = GroundSpec_Type::nothing;
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
		 *		g�n�ration de l'eau -> forme en L (3 cases)		   *
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
				(maps[i][j],
					Ground_Type::water,
					GroundSpec_Type::fish,
					3,
					2,
					1);
				break;
			case 2:
				tileAffectation
				(maps[i][j],
					Ground_Type::water,
					GroundSpec_Type::petroleum,
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
				(maps[i][j],
					Ground_Type::water,
					GroundSpec_Type::nothing,
					1,
					1,
					1);
		}
		else
		{
			/* N/A */
		}

		/* 2�me case */

		if (Ground_Type::deepwater != maps[i - 1][j].tile_ground)
		{
			randomspecwater1 =
				rand() % MAP_GEN_RANDOM_RANGE_SPEC_WATER1 + MAP_GEN_RANDOM_OFFSET_SPEC_WATER1;
			switch (randomspecwater1)
			{
			case 1:
				tileAffectation
				(maps[i - 1][j],
					Ground_Type::water,
					GroundSpec_Type::fish,
					3,
					2,
					1);
				break;
			case 2:
				tileAffectation
				(maps[i - 1][j],
					Ground_Type::water,
					GroundSpec_Type::petroleum,
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
				(maps[i - 1][j],
					Ground_Type::water,
					GroundSpec_Type::nothing,
					1,
					1,
					1);
		}
		else
		{
			/* N/A */
		}

		/* 3�me case */

		if (Ground_Type::deepwater != maps[i - 1][j - 1].tile_ground)
		{
			randomspecwater2 =
				rand() % MAP_GEN_RANDOM_RANGE_SPEC_WATER2 + MAP_GEN_RANDOM_OFFSET_SPEC_WATER2;
			switch (randomspecwater2)
			{
			case 1:
				tileAffectation
				(maps[i - 1][j - 1],
					Ground_Type::water,
					GroundSpec_Type::fish,
					3,
					2,
					1);
				break;
			case 2:
				tileAffectation
				(maps[i - 1][j - 1],
					Ground_Type::water,
					GroundSpec_Type::petroleum,
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
				(maps[i - 1][j - 1],
					Ground_Type::water,
					GroundSpec_Type::nothing,
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
/* ROLE : Affectation des caract�ristiques � une case								   */
/* OUTPUT : Tile& tile, : la case � affecter										   */
/* INPUT : unsigned int tile_ground, std::string tile_stringground,						   */
/* INPUT : unsigned int tile_spec, std::string tile_stringspec,							   */
/* INPUT : int food, int work, int gold									   */
/* RETURNED VALUE : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void MainMap::tileAffectation
(
	Tile& tile,
	Ground_Type tile_ground,
	GroundSpec_Type tile_spec,
	int food,
	int work,
	int gold
)
{
	tile.tile_ground = tile_ground;
	tile.tile_spec = tile_spec;
	tile.food = food;
	tile.work = work;
	tile.gold = gold;
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
unsigned int MainMap::convertIndexToPosX
(
	unsigned int index
)
{
	return *s_tileSize * index;
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
unsigned int MainMap::convertPosXToIndex
(
	double posX
)
{
	return (unsigned int)std::floor(posX / (double)*s_tileSize);
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
unsigned int MainMap::convertIndexToPosY
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
unsigned int MainMap::convertPosYToIndex
(
	double posY
)
{
	return (unsigned int)std::floor(posY / (double)*s_tileSize);
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
bool MainMap::assertRangeMapIndex
(
	unsigned int indexToTest,
	size_t size
)
{
	return indexToTest < size ? true : false;
}






void MainMap::drawMap
(
	RealEngine2D::Camera2D& camera
)
{
	static GLuint idGrass(RealEngine2D::ResourceManager::getTexture("bin/image/ground/hr-grass.png")->GETid());
	static GLuint idWater(RealEngine2D::ResourceManager::getTexture("bin/image/ground/hr-water.png")->GETid());
	static GLuint idDeepWater(RealEngine2D::ResourceManager::getTexture("bin/image/ground/hr-deepwater.png")->GETid());

	static GLuint idCoal(RealEngine2D::ResourceManager::getTexture("bin/image/spec/coal.png")->GETid());
	static GLuint idCopper(RealEngine2D::ResourceManager::getTexture("bin/image/spec/copper.png")->GETid());
	static GLuint idFish(RealEngine2D::ResourceManager::getTexture("bin/image/spec/fish.png")->GETid());
	static GLuint idHorse(RealEngine2D::ResourceManager::getTexture("bin/image/spec/horse.png")->GETid());
	static GLuint idIron(RealEngine2D::ResourceManager::getTexture("bin/image/spec/iron.png")->GETid());
	static GLuint idPetroleum(RealEngine2D::ResourceManager::getTexture("bin/image/spec/petroleum.png")->GETid());
	static GLuint idStone(RealEngine2D::ResourceManager::getTexture("bin/image/spec/stone.png")->GETid());
	static GLuint idtree1(RealEngine2D::ResourceManager::getTexture("bin/image/spec/tree1.png")->GETid());
	static GLuint iduranium(RealEngine2D::ResourceManager::getTexture("bin/image/spec/uranium.png")->GETid());

	if (m_needToUpdateDraw)
	{
		GLuint id(0);

		/* Use this because map is static */
		m_spriteBatch.begin();

		for (unsigned int i(0); i < m_mapSizePixX / m_tileSize; i++)
		{
			for (unsigned int j(0); j < m_mapSizePixY / m_tileSize; j++)
			{
				if (
					camera.isBoxInView
					(
						{ m_matriceMap[i][j].tile_x , m_matriceMap[i][j].tile_y },
						{ m_tileSize , m_tileSize },
						(m_toolBarSize - 1) * m_tileSize
					)
					)
				{
					switch (m_matriceMap[i][j].tile_ground)
					{
					case Ground_Type::grass:
						id = idGrass;
						break;
					case Ground_Type::water:
						id = idWater;
						break;
					case Ground_Type::deepwater:
						id = idDeepWater;
						break;
					case Ground_Type::dirt:
						App::exitError("[Error]___: drawMap : Ground_Type::dirt");
						break;
					case Ground_Type::sand:
						App::exitError("[Error]___: drawMap : Ground_Type::sand");
						break;
					case Ground_Type::error:
						App::exitError("[Error]___: drawMap : Ground_Type::error");
						break;
					default:
						App::exitError("[Error]___: drawMap : default");
						break;
					}

					m_spriteBatch.draw
					(
						glm::vec4(m_matriceMap[i][j].tile_x, m_matriceMap[i][j].tile_y, m_tileSize, m_tileSize),
						glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
						id,
						0.0f,
						RealEngine2D::COLOR_WHITE
					);

					switch (m_matriceMap[i][j].tile_spec)
					{
					case GroundSpec_Type::coal:
						id = idCoal;
						break;
					case GroundSpec_Type::copper:
						id = idCopper;
						break;
					case GroundSpec_Type::fish:
						id = idFish;
						break;
					case GroundSpec_Type::horse:
						id = idHorse;
						break;
					case GroundSpec_Type::iron:
						id = idIron;
						break;
					case GroundSpec_Type::petroleum:
						id = idPetroleum;
						break;
					case GroundSpec_Type::stone:
						id = idStone;
						break;
					case GroundSpec_Type::tree:
						id = idtree1;
						break;
					case GroundSpec_Type::uranium:
						id = iduranium;
						break;
					case GroundSpec_Type::nothing:
						/* N/A */
						break;
					}

					m_spriteBatch.draw
					(
						glm::vec4(m_matriceMap[i][j].tile_x, m_matriceMap[i][j].tile_y, m_tileSize, m_tileSize),
						glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
						id,
						0.0f,
						RealEngine2D::COLOR_WHITE
					);
				}
			}
		}

		m_spriteBatch.end();

		m_needToUpdateDraw = false;
	}
}

void MainMap::renderMap()
{
	m_spriteBatch.renderBatch();
}


/*
*	End Of File : GamePlay.cpp
*/