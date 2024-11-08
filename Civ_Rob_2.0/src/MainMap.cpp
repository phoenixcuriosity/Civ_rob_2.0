﻿/*

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
#include "Player.h"

#include <R2D/src/GLTexture.h>
#include <R2D/src/ResourceManager.h>
#include <R2D/src/ErrorLog.h> 

namespace MAP_GEN
{
	/* MAP -> Max size - Min size of the map for sea borders */
	const unsigned int BORDER_MIN = 1;

	/* MAP -> value deep_water */
	const unsigned int BORDER_ZERO = 0;

	/* MAP_GEN_RANDOM */
	namespace RANDOM
	{
		namespace RANGE
		{
			const unsigned int GROUND = 100;
			const unsigned int SPEC_GRASS = 100;
			const unsigned int SPEC_WATER = 20;
			const unsigned int SPEC_WATER1 = 10;
			const unsigned int SPEC_WATER2 = 10;
			const unsigned int SPEC_WATER_BORDER = 50;
		}

		namespace OFFSET
		{
			const unsigned int GROUND = 1;
			const unsigned int SPEC_GRASS = 1;
			const unsigned int SPEC_WATER = 1;
			const unsigned int SPEC_WATER1 = 1;
			const unsigned int SPEC_WATER2 = 1;
			const unsigned int SPEC_WATER_BORDER = 1;
		}
	}

	const unsigned int MAX_ITERATION_SCALE = 10000;
}

namespace MAPCamera
{
	/* Avoid seeing nothing before next tile */
	const unsigned int MIN_BORDER = 1;

	/* Define the index to look in the matrix for its size */
	const unsigned int INDEX_SIZE = 0;
}

namespace MAPGUI
{
	/* Define an ID which is unused */
	const GLuint UNUSED_ID = 0;
}

 /* *********************************************************
  *					  Static Var						   *
  ********************************************************* */

unsigned int* MainMap::s_tileSize;

static size_t START_APPARTENANCE_INDEX = 0;
static size_t START_GROUND_SPEC_INDEX = 0;
const uint8_t OFFSET_GROUND_TYPE = 1;

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
m_spriteBatch(),
s_vectID()
{
	setStaticPtrTileSize();
}

MainMap::~MainMap()
{

}


void MainMap::initMainMap(R2D::Camera2D& camera)
{
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
		R2D::ErrorLog::logEvent("[ERROR]___: initMainMap : " + std::string(msg.what()));
	}
	

	initMainMapTexture();
}

void MainMap::initMainMapTexture()
{
	m_spriteBatch.init();
	m_spriteBatchAppartenance.init();


	s_vectID.push_back(R2D::ResourceManager::getTexture("bin/image/ground/hr-grass.png")->GETid());
	s_vectID.push_back(R2D::ResourceManager::getTexture("bin/image/ground/hr-water.png")->GETid());
	s_vectID.push_back(R2D::ResourceManager::getTexture("bin/image/ground/hr-deepwater.png")->GETid());
	s_vectID.push_back(R2D::ResourceManager::getTexture("bin/image/ground/hr-grass_irr.png")->GETid());

	START_GROUND_SPEC_INDEX = s_vectID.size();
	s_vectID.push_back(R2D::ResourceManager::getTexture("bin/image/spec/coal.png")->GETid());
	s_vectID.push_back(R2D::ResourceManager::getTexture("bin/image/spec/copper.png")->GETid());
	s_vectID.push_back(R2D::ResourceManager::getTexture("bin/image/spec/iron.png")->GETid());
	s_vectID.push_back(R2D::ResourceManager::getTexture("bin/image/spec/tree1.png")->GETid());
	s_vectID.push_back(R2D::ResourceManager::getTexture("bin/image/spec/stone.png")->GETid());
	s_vectID.push_back(R2D::ResourceManager::getTexture("bin/image/spec/uranium.png")->GETid());
	s_vectID.push_back(R2D::ResourceManager::getTexture("bin/image/spec/horse.png")->GETid());
	s_vectID.push_back(R2D::ResourceManager::getTexture("bin/image/spec/fish.png")->GETid());
	s_vectID.push_back(R2D::ResourceManager::getTexture("bin/image/spec/petroleum.png")->GETid());

	START_APPARTENANCE_INDEX = s_vectID.size();
	for (unsigned int i(0); i < PlayerH::NB_MAX_PLAYER; i++)
	{
		s_vectID.push_back
			(R2D::ResourceManager::getTexture("bin/image/couleur d'apartenance/ColorPlayer" + std::to_string(i) + EXTENSION_PNG)->GETid());
	}
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
	R2D::ErrorLog::logEvent("[INFO]___: Groundgen Start");

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

	R2D::ErrorLog::logEvent("[INFO]___: Groundgen End");
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
	const unsigned int index
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
	const double posX
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
	const unsigned int index
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
	const double posY
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
					id = s_vectID[(uint8_t)Ground_Type::grass - OFFSET_GROUND_TYPE];
					break;
				case Ground_Type::water:
					id = s_vectID[(uint8_t)Ground_Type::water - OFFSET_GROUND_TYPE];
					break;
				case Ground_Type::deepwater:
					id = s_vectID[(uint8_t)Ground_Type::deepwater - OFFSET_GROUND_TYPE];
					break;
				case Ground_Type::irragated:
					id = s_vectID[(uint8_t)Ground_Type::irragated - OFFSET_GROUND_TYPE];
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
					id = s_vectID[START_GROUND_SPEC_INDEX];
					break;
				case GroundSpec_Type::copper:
					id = s_vectID[START_GROUND_SPEC_INDEX + (uint8_t)GroundSpec_Type::coal];
					break;
				case GroundSpec_Type::iron:
					id = s_vectID[START_GROUND_SPEC_INDEX + (uint8_t)GroundSpec_Type::copper];
					break;
				case GroundSpec_Type::tree:
					id = s_vectID[START_GROUND_SPEC_INDEX + (uint8_t)GroundSpec_Type::iron];
					break;
				case GroundSpec_Type::stone:
					id = s_vectID[START_GROUND_SPEC_INDEX + (uint8_t)GroundSpec_Type::tree];
					break;
				case GroundSpec_Type::uranium:
					id = s_vectID[START_GROUND_SPEC_INDEX + (uint8_t)GroundSpec_Type::stone];
					break;
				case GroundSpec_Type::horse:
					id = s_vectID[START_GROUND_SPEC_INDEX + (uint8_t)GroundSpec_Type::uranium];
					break;
				case GroundSpec_Type::fish:
					id = s_vectID[START_GROUND_SPEC_INDEX + (uint8_t)GroundSpec_Type::horse];
					break;
				case GroundSpec_Type::petroleum:
					id = s_vectID[START_GROUND_SPEC_INDEX + (uint8_t)GroundSpec_Type::fish];
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
						0.0f,
						R2D::COLOR_WHITE
					);
				}

				if (m_matriceMap[i][j].appartenance != SELECTION::NO_APPARTENANCE)
				{
					m_spriteBatchAppartenance.draw
					(
						glm::vec4(m_matriceMap[i][j].tile_x, m_matriceMap[i][j].tile_y, m_tileSize, m_tileSize),
						R2D::FULL_RECT,
						s_vectID[START_APPARTENANCE_INDEX + m_matriceMap[i][j].appartenance],
						0.0f,
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