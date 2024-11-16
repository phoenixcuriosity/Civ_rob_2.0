/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)

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

#include "MainMap.h"

#include "App.h"
#include "LogSentences.h"
#include "Player.h"

#include <R2D/src/GLTexture.h>
#include <R2D/src/ResourceManager.h>
#include <R2D/src/Log.h> 

namespace MAP_GEN
{
	/* MAP -> Max size - Min size of the map for sea borders */
	constexpr unsigned int BORDER_MIN = 1;

	/* MAP -> value deep_water */
	constexpr unsigned int BORDER_ZERO = 0;

	/* MAP_GEN_RANDOM */
	namespace RANDOM
	{
		namespace RANGE
		{
			constexpr unsigned int GROUND = 100;
			constexpr unsigned int SPEC_GRASS = 100;
			constexpr unsigned int SPEC_WATER = 20;
			constexpr unsigned int SPEC_WATER1 = 10;
			constexpr unsigned int SPEC_WATER2 = 10;
			constexpr unsigned int SPEC_WATER_BORDER = 50;
		}

		namespace OFFSET
		{
			constexpr unsigned int GROUND = 1;
			constexpr unsigned int SPEC_GRASS = 1;
			constexpr unsigned int SPEC_WATER = 1;
			constexpr unsigned int SPEC_WATER1 = 1;
			constexpr unsigned int SPEC_WATER2 = 1;
			constexpr unsigned int SPEC_WATER_BORDER = 1;
		}
	}

	constexpr unsigned int MAX_ITERATION_SCALE = 10000;
}

namespace MAPCamera
{
	/* Avoid seeing nothing before next tile */
	constexpr unsigned int MIN_BORDER = 1;

	/* Define the index to look in the matrix for its size */
	constexpr unsigned int INDEX_SIZE = 0;
}

namespace MAPGUI
{
	/* Define an ID which is unused */
	constexpr GLuint UNUSED_ID = 0;
}

unsigned int* MainMap::s_tileSize;


void MainMap::setStaticPtrTileSize()
{
	s_tileSize = &m_tileSize;
}


MainMap::MainMap():
m_mapSizePixX(0),
m_mapSizePixY(0),
m_tileSize(0),
m_toolBarSize(0),
m_offsetMapCameraXmin(0),
m_offsetMapCameraXmax(0),
m_offsetMapCameraYmin(0),
m_offsetMapCameraYmax(0),
m_matriceMap(),
m_needToUpdateDraw(true),
m_spriteBatch()
{
	setStaticPtrTileSize();
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CONSTRUCTOR, logS::DATA::MAINMAP);
}

MainMap::~MainMap()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DESTRUCTOR, logS::DATA::MAINMAP);
}


void MainMap::initMainMap(R2D::Camera2D& camera)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::INIT_MAINMAP, logS::DATA::START);
	initTile();

	generateMap();

	updateOffset
	(
		((double)camera.GETposition().x - (double)camera.getScreenWidth() / 2.0),
		((double)camera.GETposition().y - (double)camera.getScreenHeight() / 2.0),
		(unsigned int)camera.getScreenWidth(),
		(unsigned int)camera.getScreenHeight(),
		camera
	);

	try
	{
		setMinMaxScale(camera);
	}
	catch (const std::invalid_argument& msg)
	{
		LOG(R2D::LogLevelType::warning, 0, logS::WHO::GAMEPLAY, logS::WHAT::INIT_MAINMAP, logS::DATA::MSG_DATA, msg.what());
	}
	

	initMainMapTexture();
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::INIT_MAINMAP, logS::DATA::END);
}

void MainMap::initMainMapTexture()
{
	m_spriteBatch.init();
	m_spriteBatchAppartenance.init();

	static const std::string CITY_IMAGE_PATH{ R2D::ResourceManager::getFile(R2D::e_Files::imagesPath)->getPath() };

	using R2D::ResourceManager;
	ResourceManager::getTextureIdFromDir(CITY_IMAGE_PATH, m_idMap);
}

void MainMap::initTile()
{
	const Tile blankTile;
	const std::vector<Tile> blank;
	const unsigned int endI{ m_mapSizePixX / m_tileSize };
	const unsigned int endJ{ m_mapSizePixY / m_tileSize };

	for (unsigned int i(0); i < endI; i++)
	{
		m_matriceMap.push_back(blank);
		for (unsigned int j(0); j < endJ; j++)
		{
			m_matriceMap[i].push_back(blankTile);
		}
	}
}

void MainMap::generateMap()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::GENERATION_MAINMAP, logS::DATA::START);

	const unsigned int endI{ m_mapSizePixX / m_tileSize };
	const unsigned int endJ{ m_mapSizePixY / m_tileSize };

	for (unsigned int i(0); i < endI; i++)
	{
		for (unsigned int j(0); j < endJ; j++)
		{

			m_matriceMap[i][j].indexX = i;
			m_matriceMap[i][j].indexY = j;
			m_matriceMap[i][j].tile_x = convertIndexToPosX(i);
			m_matriceMap[i][j].tile_y = convertIndexToPosY(j);


			/* *********************************************************
			 *			bord de la map (MAP_BORDER_ZERO)			   *
			 ********************************************************* */

			if (
				(i == MAP_GEN::BORDER_ZERO)
				|| (i == (m_mapSizePixX / m_tileSize) - (MAP_GEN::BORDER_ZERO + 1))
				|| (j == MAP_GEN::BORDER_ZERO)
				|| (j == (m_mapSizePixY / m_tileSize) - (MAP_GEN::BORDER_ZERO + 1))
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

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::GENERATION_MAINMAP, logS::DATA::END);
}

bool MainMap::mapBordersConditions
(
	const unsigned int i,
	const unsigned int j
)
{
	const unsigned int cmpX{ m_mapSizePixX / m_tileSize };
	const unsigned int cmpY{ m_mapSizePixY / m_tileSize };
	for (unsigned int index(MAP_GEN::BORDER_MIN); index < MAPH::MAP_BORDER_MAX; index++)
	{
		if (
			(i == index)
			||
			(i == cmpX - (index + 1))
			||
			(j == index)
			||
			(j == cmpY - (index + 1))
			)
		{
			return true;
		}
	}
	return false;
}

void MainMap::mapBorders
(
	Tile& tile
)
{
	unsigned int randomspecwaterborder
	((rand() % MAP_GEN::RANDOM::RANGE::SPEC_WATER_BORDER) + MAP_GEN::RANDOM::OFFSET::SPEC_WATER_BORDER);
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

void MainMap::mapIntern
(
	MatriceMap& maps,
	const unsigned int i,
	const unsigned int j
)
{
	unsigned int	randomground(0),
		randomspecgrass(0),
		randomspecwater(0),
		randomspecwater1(0),
		randomspecwater2(0);

	randomground = rand() % MAP_GEN::RANDOM::RANGE::GROUND + MAP_GEN::RANDOM::OFFSET::GROUND;
	if (randomground < 92)
	{
		maps[i][j].tile_ground = Ground_Type::grass;
		randomspecgrass =
			rand() % MAP_GEN::RANDOM::RANGE::SPEC_GRASS + MAP_GEN::RANDOM::OFFSET::SPEC_GRASS;
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
				rand() % MAP_GEN::RANDOM::RANGE::SPEC_WATER + MAP_GEN::RANDOM::OFFSET::SPEC_WATER;
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
				rand() % MAP_GEN::RANDOM::RANGE::SPEC_WATER1 + MAP_GEN::RANDOM::OFFSET::SPEC_WATER1;
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
				rand() % MAP_GEN::RANDOM::RANGE::SPEC_WATER2 + MAP_GEN::RANDOM::OFFSET::SPEC_WATER2;
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

void MainMap::tileAffectation
(
	Tile& tile,
	const Ground_Type tile_ground,
	const GroundSpec_Type tile_spec,
	const int food,
	const int work,
	const int gold
)
{
	tile.tile_ground = tile_ground;
	tile.tile_spec = tile_spec;
	tile.food = food;
	tile.work = work;
	tile.gold = gold;
}

unsigned int MainMap::convertIndexToPosX
(
	const unsigned int index
)
{
	return *s_tileSize * index;
}

unsigned int MainMap::convertPosXToIndex
(
	const double posX
)
{
	return (unsigned int)std::floor(posX / (double)*s_tileSize);
}

unsigned int MainMap::convertIndexToPosY
(
	const unsigned int index
)
{
	return *s_tileSize * index;
}

unsigned int MainMap::convertPosYToIndex
(
	const double posY
)
{
	return (unsigned int)std::floor(posY / (double)*s_tileSize);
}

bool MainMap::assertRangeMapIndex
(
	const unsigned int indexToTest,
	const size_t size
)
{
	return indexToTest < size ? true : false;
}




void MainMap::setMinMaxScale
(
	R2D::Camera2D& camera
)
{
	/* Min Scale, to avoid OOR */
	if	(
			((unsigned int)camera.GETscale() * (unsigned int)camera.getScreenWidth()) > m_mapSizePixX
			||
			((unsigned int)camera.GETscale() * (unsigned int)camera.getScreenHeight()) > m_mapSizePixY
		)
	{
		throw std::invalid_argument("Width or Height is higher than mapSize");
	}

	unsigned int i(0);
	float buffer((float)std::max(camera.getScreenWidth(), camera.getScreenHeight()));
	bool on(true);
	while (on)
	{
		buffer *= camera.GETscaleRate();
		i++;

		if (buffer >= (float)std::min(m_mapSizePixX, m_mapSizePixY))
		{
			on = false;
			i--;
		}
		if (i > MAP_GEN::MAX_ITERATION_SCALE)
		{
			throw("[Error]___: setMinMaxScale : MAX_ITERATION_SCALE");
		}
	}

	camera.SETminScale(camera.GETscale() / std::pow(camera.GETscaleRate(), (float)i));

	i = 0;
	buffer = (float)std::min(camera.getScreenWidth(), camera.getScreenHeight());
	on = true;
	while (on)
	{
		buffer /= camera.GETscaleRate();
		i++;

		if (buffer <= ((float)m_tileSize * 8))
		{
			on = false;
			i--;
		}
		if (i > MAP_GEN::MAX_ITERATION_SCALE)
		{
			throw("[Error]___: setMinMaxScale : MAX_ITERATION_SCALE");
		}
	}

	camera.SETmaxScale(camera.GETscale() * std::pow(camera.GETscaleRate(), (float)i));

}





void MainMap::updateOffset
(
	const double x0,
	const double y0,
	const unsigned int windowWidth,
	const unsigned int windowHeight,
	R2D::Camera2D& camera
)
{
	updateOffsetX(x0, windowWidth, camera);
	updateOffsetY(y0, windowHeight, camera);
}


void MainMap::updateOffsetX
(
	const double x0,
	const unsigned int windowWidth,
	R2D::Camera2D& camera
)
{
	int buffer(0);

	if (x0 <= -((double)m_toolBarSize * m_tileSize * camera.GETscale()))
	{
		m_offsetMapCameraXmin = 0;
		buffer = -(int)m_toolBarSize - (int)std::floor(x0 / ((double)m_tileSize * camera.GETscale()));
		camera.lockMoveLEFT();
	}
	else
	if (x0 > ((double)m_mapSizePixX - (double)windowWidth))
	{
		m_offsetMapCameraXmin = m_toolBarSize;
		m_offsetMapCameraXmin += (unsigned int)std::floor(x0 / (double)m_tileSize);
		camera.lockMoveRIGHT();
		return;
	}
	else
	{
		/* Positive LEFT offset HUD */
		m_offsetMapCameraXmin = m_toolBarSize;
		m_offsetMapCameraXmin += (unsigned int)std::floor(x0 / (double)m_tileSize);
		camera.unlockMoveLEFT();
		camera.unlockMoveRIGHT();
	}


	if ((x0 + (double)windowWidth) > (double)m_mapSizePixX)
	{
		m_offsetMapCameraXmax = (unsigned int)m_matriceMap.size();
	}
	else
	{
		m_offsetMapCameraXmax =
			m_offsetMapCameraXmin
			+ (unsigned int)std::floor((double)windowWidth / ((double)m_tileSize * camera.GETscale())) /* width of screen */
			- buffer
			+ MAPCamera::MIN_BORDER
			- m_toolBarSize; /* Negative RIGHT offset HUD */

		if (m_offsetMapCameraXmax >= (unsigned int)m_matriceMap.size() + MAPCamera::MIN_BORDER)
		{
			camera.lockMoveRIGHT();
		}

		if (m_offsetMapCameraXmax >= (unsigned int)m_matriceMap.size())
		{
			m_offsetMapCameraXmax = (unsigned int)m_matriceMap.size();
		}
	}

}


void MainMap::updateOffsetY
(
	const double y0,
	const unsigned int windowHeight,
	R2D::Camera2D& camera
)
{
	int buffer(0);

	if (y0 < 0.0)
	{
		m_offsetMapCameraYmin = 0;
		buffer = -(int)std::floor((double)y0 / ((double)m_tileSize * camera.GETscale()));
		camera.lockMoveDOWN();
	}
	else
	{
		m_offsetMapCameraYmin = (unsigned int)std::floor(y0 / (double)m_tileSize);
		camera.unlockMoveUP();
		camera.unlockMoveDOWN();
	}


	if ((y0 + (double)windowHeight) >= ((double)m_mapSizePixY - ((double)m_tileSize * camera.GETscale())))
	{
		m_offsetMapCameraYmax = (unsigned int)m_matriceMap[MAPCamera::INDEX_SIZE].size();
	}
	else
	{
		m_offsetMapCameraYmax = 
			m_offsetMapCameraYmin 
			+ (unsigned int)std::ceil((double)windowHeight / ((double)m_tileSize * camera.GETscale()))
			- buffer
			+ MAPCamera::MIN_BORDER;

		if (m_offsetMapCameraYmax >= (unsigned int)m_matriceMap[MAPCamera::INDEX_SIZE].size() + MAPCamera::MIN_BORDER)
		{
			camera.lockMoveUP();
		}

		if (m_offsetMapCameraYmax >= (unsigned int)m_matriceMap[MAPCamera::INDEX_SIZE].size())
		{
			m_offsetMapCameraYmax = (unsigned int)m_matriceMap[MAPCamera::INDEX_SIZE].size();
		}
	}

}




void MainMap::drawMap
(
	R2D::Camera2D& camera,
	R2D::Window& window
)
{
	if (m_needToUpdateDraw)
	{
		GLuint id(MAPGUI::UNUSED_ID);

		updateOffset
		(
			((double)camera.GETposition().x - (double)window.GETscreenWidth() / 2),
			((double)camera.GETposition().y - (double)window.GETscreenHeight() / 2),
			(unsigned int)window.GETscreenWidth(),
			(unsigned int)window.GETscreenHeight(),
			camera
		);

		/* Use this because map is static */
		m_spriteBatch.begin();
		m_spriteBatchAppartenance.begin();

		for (unsigned int i(m_offsetMapCameraXmin); i < m_offsetMapCameraXmax; i++)
		{
			for (unsigned int j(m_offsetMapCameraYmin); j < m_offsetMapCameraYmax; j++)
			{
				switch (m_matriceMap[i][j].tile_ground)
				{
				case Ground_Type::grass:
					id = m_idMap["grass"];
					break;
				case Ground_Type::water:
					id = m_idMap["water"];
					break;
				case Ground_Type::deepwater:
					id = m_idMap["deepwater"];
					break;
				case Ground_Type::irragated:
					id = m_idMap["grassIrr"];
					break;
				case Ground_Type::dirt:
					throw("[Error]___: drawMap : Ground_Type::dirt");
					break;
				case Ground_Type::sand:
					throw("[Error]___: drawMap : Ground_Type::sand");
					break;
				case Ground_Type::error:
					throw("[Error]___: drawMap : Ground_Type::error");
					break;
				default:
					throw("[Error]___: drawMap : default");
					break;
				}

				m_spriteBatch.draw
				(
					glm::vec4(m_matriceMap[i][j].tile_x, m_matriceMap[i][j].tile_y, m_tileSize, m_tileSize),
					R2D::FULL_RECT,
					id,
					0.0f,
					R2D::COLOR_WHITE
				);

				switch (m_matriceMap[i][j].tile_spec)
				{
				case GroundSpec_Type::coal:
					id = m_idMap["coal"];
					break;
				case GroundSpec_Type::copper:
					id = m_idMap["copper"];
					break;
				case GroundSpec_Type::iron:
					id = m_idMap["iron"];
					break;
				case GroundSpec_Type::tree:
					id = m_idMap["tree1"];
					break;
				case GroundSpec_Type::stone:
					id = m_idMap["stone"];
					break;
				case GroundSpec_Type::uranium:
					id = m_idMap["uranium"];
					break;
				case GroundSpec_Type::horse:
					id = m_idMap["horse"];
					break;
				case GroundSpec_Type::fish:
					id = m_idMap["fish"];
					break;
				case GroundSpec_Type::petroleum:
					id = m_idMap["petroleum"];
					break;
				case GroundSpec_Type::nothing:
					id = MAPGUI::UNUSED_ID;
					break;
				}

				if (MAPGUI::UNUSED_ID != id)
				{
					m_spriteBatch.draw
					(
						glm::vec4(m_matriceMap[i][j].tile_x, m_matriceMap[i][j].tile_y, m_tileSize, m_tileSize),
						R2D::FULL_RECT,
						id,
						0.1f,
						R2D::COLOR_WHITE
					);
				}

				if (m_matriceMap[i][j].appartenance != SELECTION::NO_APPARTENANCE)
				{
					m_spriteBatchAppartenance.draw
					(
						glm::vec4(m_matriceMap[i][j].tile_x, m_matriceMap[i][j].tile_y, m_tileSize, m_tileSize),
						R2D::FULL_RECT,
						m_idMap[std::format("ColorPlayer{}", m_matriceMap[i][j].appartenance)],
						0.5f,
						R2D::COLOR_WHITE_T25
					);
				}
			}
		}

		m_spriteBatch.end();
		m_spriteBatchAppartenance.end();

		m_needToUpdateDraw = false;
	}
}

void MainMap::renderMap()
{
	m_spriteBatch.renderBatch();
	m_spriteBatchAppartenance.renderBatch();
}


/*
*	End Of File : GamePlay.cpp
*/