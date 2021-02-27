/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.1.0
	file version : 1.0

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

#ifndef GamePlay_H
#define GamePlay_H

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"

 /* *********************************************************
  *						Constantes						   *
  ********************************************************* */

  /* MAP -> Max size - Min size of the map for sea borders */
#define MAP_BORDER_MAX 4
#define MAP_BORDER_MIN 1

/* MAP -> value deep_water */
#define MAP_BORDER_ZERO 0

/* MAP_GEN_RANDOM */
#define MAP_GEN_RANDOM_RANGE_GROUND 100
#define MAP_GEN_RANDOM_OFFSET_GROUND 1

#define MAP_GEN_RANDOM_RANGE_SPEC_GRASS 100
#define MAP_GEN_RANDOM_OFFSET_SPEC_GRASS 1

#define MAP_GEN_RANDOM_RANGE_SPEC_WATER 20
#define MAP_GEN_RANDOM_OFFSET_SPEC_WATER 1

#define MAP_GEN_RANDOM_RANGE_SPEC_WATER1 10
#define MAP_GEN_RANDOM_OFFSET_SPEC_WATER1 1

#define MAP_GEN_RANDOM_RANGE_SPEC_WATER2 10
#define MAP_GEN_RANDOM_OFFSET_SPEC_WATER2 1

#define MAP_GEN_RANDOM_RANGE_SPEC_WATER_BORDER 50
#define MAP_GEN_RANDOM_OFFSET_SPEC_WATER_BORDER 1

#define MAX_RANDOM_POS_ITERATION 10000

/* Minimum space beetween two or more settlers */
#define MIN_SPACE_BETWEEN_SETTLER 8

/* The tile is not own by a player */
#define NO_APPARTENANCE -1

#define GROUNDSPEC_NOTHING "void"

/* The first settler to spawn in the map for each Player does not cost maintenance */
#define MAINTENANCE_COST_1TH_SETTLER 0.0

/* *********************************************************
 *						 Enum							   *
 ********************************************************* */

 // Define Ground type use on the map
enum class Ground_Type : Uint8
{
	error,			/* ### Reserved on error detection ### */
	grass,
	water,
	deepwater,
	dirt,			/* ### Not use as of 0.20.0.3 ### */
	sand			/* ### Not use as of 0.20.0.3 ### */
};

// Define specification for a tile on the map
enum class GroundSpec_Type : Uint8
{
	nothing,		/* The Tile has no specification */
	coal,
	copper,
	iron,
	tree,
	stone,
	uranium,
	horse,
	fish,
	petroleum
};

/* *********************************************************
 *						 Structs						   *
 ********************************************************* */

struct Tile
{

	// index en X de la case : en tileSize
	Uint8 indexX = 0;

	// index en Y de la case : en tileSize
	Uint8 indexY = 0;

	// index en X de la case : en pixel
	unsigned int tile_x = 0;

	// index en Y de la case : en pixel
	unsigned int tile_y = 0;

	// nom du type de sol
	std::string tile_stringground = EMPTY_STRING;

	// type de sol -> enum Ground_Type : Uint8 { noGround, grass, water, deepwater, dirt, sand};
	Ground_Type tile_ground = Ground_Type::error;

	// nom du type de sp�cification de la case
	std::string tile_stringspec = EMPTY_STRING;

	/*
		type de sp�cification
		-> enum GroundSpec_Type : Uint8 { nothing, coal, copper, iron, tree, stone, uranium, horse, fish, petroleum };
	*/
	GroundSpec_Type tile_spec = GroundSpec_Type::nothing;

	// index d'appartenance d'un case � un joueur : appartenance neutre = -1
	int appartenance = NO_APPARTENANCE;

	// indice de nourriture de la case
	int8_t food = -1;

	// indice de production de la case
	int8_t work = -1;

	// indice financier de la case
	int8_t gold = -1;
};

/* ---------------------------------------------------------------------- */
/* Structure d'un couple de positions									  */
/* Positions en x et y permettant le spawn des settlers					  */
/* ---------------------------------------------------------------------- */
struct randomPos
{
	int x;
	int y;
};

/* *********************************************************
 *						  Classe						   *
 ********************************************************* */

class MainMap
{
public:

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : getPtrTileSize															   */
	/* ROLE : Initialize ptr on tileSize from sysinfo									   */
	/* INPUT : unsigned int* const : ptr on tileSize									   */
	/* RETURNED VALUE : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void setStaticPtrTileSize();

public:

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
	static unsigned int convertIndexToPosX
	(
		unsigned int index
	);

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
	static unsigned int convertPosXToIndex
	(
		unsigned int posX
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : convertIndexToPosY														   */
	/* ROLE : Convert the index of the matrix Map to a position on Y axis in pixel		   */
	/* ROLE : Use 1 input static const ptr : s_tileSize									   */
	/* INPUT : unsigned int index : index to convert									   */
	/* RETURNED VALUE : unsigned int : position on Y axis in pixel						   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static unsigned int convertIndexToPosY
	(
		unsigned int index
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : convertPosXToIndex														   */
	/* ROLE : Convert position on Y axis in pixel of the matrix Map to a index			   */
	/* ROLE : Use 1 input static const ptr : s_tileSize									   */
	/* INPUT : unsigned int index : position on Y axis in pixel	to convert				   */
	/* RETURNED VALUE : unsigned int : index											   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static unsigned int convertPosYToIndex
	(
		unsigned int posY
	);

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
	static bool assertRangeMapIndex
	(
		unsigned int indexToTest,
		size_t size
	);

public:

	MainMap();
	~MainMap();

	void initTile();

public:

	void generateMap();

public:

	inline unsigned int GETmapSizePixX()const { return _mapSizePixX; };
	inline unsigned int GETmapSizePixY()const { return _mapSizePixY; };
	inline unsigned int GETtileSize()const { return _tileSize; };
	inline unsigned int GETtoolBarSize()const { return _toolBarSize; };
	inline unsigned int GETscreenOffsetXIndexMin()const { return _screenOffsetXIndexMin; };
	inline unsigned int GETscreenOffsetYIndexMin()const { return _screenOffsetYIndexMin; };
	inline unsigned int GETscreenOffsetXIndexMax()const { return _screenOffsetXIndexMax; };
	inline unsigned int GETscreenOffsetYIndexMax()const { return _screenOffsetYIndexMax; };
	inline MatriceMap& GETmatriceMap() { return _matriceMap; };
	inline const MatriceMap& GETmatriceMapConst()const { return _matriceMap; };

	inline void SETmapSizePixX(unsigned int mapSizePixX){  _mapSizePixX = mapSizePixX; };
	inline void SETmapSizePixY(unsigned int mapSizePixY) {  _mapSizePixY = mapSizePixY; };
	inline void SETtileSize(unsigned int tileSize) {  _tileSize = tileSize; };
	inline void SETtoolBarSize(unsigned int toolBarSize) {  _toolBarSize = toolBarSize; };
	inline void SETscreenOffsetXIndexMin(unsigned int screenOffsetXIndexMin) {  _screenOffsetXIndexMin = screenOffsetXIndexMin; };
	inline void SETscreenOffsetYIndexMin(unsigned int screenOffsetYIndexMin) {  _screenOffsetYIndexMin = screenOffsetYIndexMin; };
	inline void SETscreenOffsetXIndexMax(unsigned int screenOffsetXIndexMax) {  _screenOffsetXIndexMax = screenOffsetXIndexMax; };
	inline void SETscreenOffsetYIndexMax(unsigned int screenOffsetYIndexMax) {  _screenOffsetYIndexMax = screenOffsetYIndexMax; };
	inline void SETmatriceMap(MatriceMap& matriceMap) {  _matriceMap = matriceMap; };

private:

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
	bool mapBordersConditions
	(
		unsigned int i,
		unsigned int j
	);

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
	void mapBorders
	(
		Tile& tile
	);

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
	void mapIntern
	(
		MatriceMap& maps,
		unsigned int i,
		unsigned int j
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : tileAffectation															   */
	/* ROLE : Affectation des caract�ristiques � une case								   */
	/* OUTPUT : Tile& tile, : la case � affecter										   */
	/* INPUT : Uint8 tile_ground, std::string tile_stringground,						   */
	/* INPUT : Uint8 tile_spec, std::string tile_stringspec,							   */
	/* INPUT : int8_t food, int8_t work, int8_t gold									   */
	/* RETURNED VALUE : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void tileAffectation
	(
		Tile& tile,
		Ground_Type tile_ground,
		std::string tile_stringground,
		GroundSpec_Type tile_spec,
		std::string tile_stringspec,
		int8_t food,
		int8_t work,
		int8_t gold
	);

private:

	unsigned int _mapSizePixX;
	unsigned int _mapSizePixY;
	unsigned int _tileSize;
	unsigned int _toolBarSize;
	unsigned int _screenOffsetXIndexMin;
	unsigned int _screenOffsetYIndexMin;
	unsigned int _screenOffsetXIndexMax;
	unsigned int _screenOffsetYIndexMax;
	MatriceMap _matriceMap;

};

#endif /* GamePlay_H */

/*
*	End Of File : GamePlay.h
*/
