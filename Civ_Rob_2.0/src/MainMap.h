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

#ifndef MainMap_H
#define MainMap_H

#include "LIB.h"

#include "GamePlayScreenEnumTexture.h"
#include "T_MainMap.h"

#include <R2D/src/Camera2D.h>
#include <R2D/src/SpriteBatch.h>

class MainMap
{
public:

	/* NAME : getPtrTileSize															   */
	/* ROLE : Initialize ptr on tileSize from sysinfo									   */
	/* INPUT : unsigned int* const : ptr on tileSize									   */
	/* RETURNED VALUE : void															   */
	void setStaticPtrTileSize();

public:

	/* NAME : convertIndexToPosX														   */
	/* ROLE : Convert the index of the matrix Map to a position on X axis in pixel		   */
	/* ROLE : Offset by toolBar size													   */
	/* ROLE : Use 2 input static const ptr : s_tileSize and s_screenWidth				   */
	/* INPUT : unsigned int index : index to convert									   */
	/* RETURNED VALUE : unsigned int : position on X axis in pixel						   */
	static unsigned int convertIndexToPosX
	(
		const unsigned int index
	);

	/* NAME : convertPosXToIndex														   */
	/* ROLE : Convert position on X axis in pixel of the matrix Map to a index			   */
	/* ROLE : Offset by toolBar size													   */
	/* ROLE : Use 2 input static const ptr : s_tileSize and s_screenWidth				   */
	/* INPUT : unsigned int index : position on X axis in pixel	to convert				   */
	/* RETURNED VALUE : unsigned int : index											   */
	static unsigned int convertPosXToIndex
	(
		const double posX
	);

	/* NAME : convertIndexToPosY														   */
	/* ROLE : Convert the index of the matrix Map to a position on Y axis in pixel		   */
	/* ROLE : Use 1 input static const ptr : s_tileSize									   */
	/* INPUT : unsigned int index : index to convert									   */
	/* RETURNED VALUE : unsigned int : position on Y axis in pixel						   */
	static unsigned int convertIndexToPosY
	(
		const unsigned int index
	);

	/* NAME : convertPosXToIndex														   */
	/* ROLE : Convert position on Y axis in pixel of the matrix Map to a index			   */
	/* ROLE : Use 1 input static const ptr : s_tileSize									   */
	/* INPUT : unsigned int index : position on Y axis in pixel	to convert				   */
	/* RETURNED VALUE : unsigned int : index											   */
	static unsigned int convertPosYToIndex
	(
		const double posY
	);

	/* NAME : assertRangeMapIndex														   */
	/* ROLE : assert that the index provided is between 0 and size						   */
	/* INPUT : unsigned int indexToTest : index to compare to size						   */
	/* INPUT : size_t size : reference size								 				   */
	/* RETURNED VALUE : bool : false -> indexToTest is equal or > than size				   */
	/* RETURNED VALUE : bool : true -> indexToTest is <	than size						   */
	static bool assertRangeMapIndex
	(
		const unsigned int indexToTest,
		const size_t size
	);

public:

	MainMap();
	~MainMap();

	void initMainMap(R2D::Camera2D& camera, const GamePlayScreenTexture& idTexture);

	void initMainMapTexture(const GamePlayScreenTexture& idTexture);

private:

	void initTile();

	void generateMap();

	void setMinMaxScale
	(
		R2D::Camera2D& camera
	);

	void updateOffset
	(
		const double x0,
		const double y0,
		const unsigned int windowWidth,
		const unsigned int windowHeight,
		R2D::Camera2D& camera
	);

	void updateOffsetX
	(
		const double x0,
		const unsigned int windowWidth,
		R2D::Camera2D& camera
	);

	void updateOffsetY
	(
		const double y0,
		const unsigned int windowHeight,
		R2D::Camera2D& camera
	);

public:

	void drawMap
	(
		R2D::Camera2D& camera,
		R2D::Window& window
	);

	void renderMap();

public:

	inline unsigned int GETmapSizePixX()		const { return m_mapSizePixX; };
	inline unsigned int GETmapSizePixY()		const { return m_mapSizePixY; };
	inline unsigned int GETtileSize()			const { return m_tileSize; };
	inline unsigned int* GETtileSizePtr()			  { return &m_tileSize; };
	inline unsigned int GETtoolBarSize()		const { return m_toolBarSize; };

	inline MatriceMap& GETmatriceMap()					  { return m_matriceMap; };
	inline const MatriceMap& GETmatriceMapConst()	const { return m_matriceMap; };
	inline const R2D::SpriteBatch& GETspriteBatch()	const { return m_spriteBatch; };

	inline void SETmapSizePixX(unsigned int mapSizePixX){  m_mapSizePixX = mapSizePixX; };
	inline void SETmapSizePixY(unsigned int mapSizePixY) {  m_mapSizePixY = mapSizePixY; };
	inline void SETtileSize(unsigned int tileSize) {  m_tileSize = tileSize; };
	inline void SETtoolBarSize(unsigned int toolBarSize) {  m_toolBarSize = toolBarSize; };
	inline void SETmatriceMap(const MatriceMap& matriceMap) {  m_matriceMap = matriceMap; };
	inline void SETneedToUpdateDraw(bool needToUpdateDraw) { m_needToUpdateDraw = needToUpdateDraw; };

private:

	/* NAME : mapBordersConditions														   */
	/* ROLE : Boucle For de conditions													   */
	/* ROLE : Nombre de conditions = (MAP_BORDER_MAX - MAP_BORDER_MIN) * 2				   */
	/* INPUT : const Map& map : structure de la MAP										   */
	/* INPUT : unsigned int i : index en X												   */
	/* INPUT : unsigned int j : index en Y												   */
	/* RETURNED VALUE : bool : valid = true / not valid = false							   */
	bool mapBordersConditions
	(
		const unsigned int i,
		const unsigned int j
	);

	/* NAME : mapBorders																   */
	/* ROLE : Affectation des caract�ristiques de la case en fonction ...				   */
	/* ROLE : ... de la fonction rand, dans la bordure de la map entre ...				   */
	/* ROLE : ... MAP_BORDER_MIN et MAP_BORDER_MAX										   */
	/* OUTPUT : Tile& tile : tile � affecter											   */
	/* RETURNED VALUE : void															   */
	void mapBorders
	(
		Tile& tile
	);

	/* NAME : mapIntern																	   */
	/* ROLE : Affectation des caract�ristiques de la case en fonction ...				   */
	/* ROLE : ... de la fonction rand, dans le reste de la map							   */
	/* ROLE : Si la case est de type water alors cr�ation de 2 autres ...				   */
	/* ROLE : ... cases de type water pour obtenir une forme en L						   */
	/* INPUT/OUTPUT : std::vector<std::vector<Tile>>& maps : matrice de la map			   */
	/* INPUT : unsigned int i : index en X												   */
	/* INPUT : unsigned int j : index en Y												   */
	/* RETURNED VALUE    : void															   */
	void mapIntern
	(
		MatriceMap& maps,
		const unsigned int i,
		const unsigned int j
	);

	/* NAME : tileAffectation															   */
	/* ROLE : Affectation des caract�ristiques � une case								   */
	/* OUTPUT : Tile& tile, : la case � affecter										   */
	/* INPUT : unsigned int tile_ground, std::string tile_stringground,					   */
	/* INPUT : unsigned int tile_spec, std::string tile_stringspec,						   */
	/* INPUT : int food, int work, int gold												   */
	/* RETURNED VALUE : void															   */
	void tileAffectation
	(
		Tile& tile,
		const Ground_Type tile_ground,
		const GroundSpec_Type tile_spec,
		const int food,
		const int work,
		const int gold
	);

public:

	jsoncons::ojson saveToOjson();

public:

	unsigned int* GETtileSizePtr()const { return (unsigned int*)&m_tileSize; };

private:

	/* Width of the map in pixels */
	unsigned int m_mapSizePixX;

	/* Height of the map in pixels */
	unsigned int m_mapSizePixY;

	/* Size of a default tile in the map */
	unsigned int m_tileSize;

	/* Size of the toolBar in pixels */
	unsigned int m_toolBarSize;

	unsigned int m_offsetMapCameraXmin;
	unsigned int m_offsetMapCameraXmax;

	unsigned int m_offsetMapCameraYmin;
	unsigned int m_offsetMapCameraYmax;

	/* Matrice x,y of tiles */
	MatriceMap m_matriceMap;

	/* Need to update re-draw when the camera moved */
	bool m_needToUpdateDraw;

	/* Dedicated spriteBatch for the map */
	R2D::SpriteBatch m_spriteBatch;
	/* Need seperate spriteBatch because of the Texture superposition */
	R2D::SpriteBatch m_spriteBatchAppartenance;

	GamePlayScreenTexture m_idTexture;

	static unsigned int* s_tileSize;
};

#endif /* MainMap_H */

/*
*	End Of File : MainMap.h
*/
