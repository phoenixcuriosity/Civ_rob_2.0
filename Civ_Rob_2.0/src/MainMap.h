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
#pragma once

#include "LIB.h"

#include "Screens/GamePlayScreenEnumTexture.h"
#include "T_MainMap.h"
#include "MainMapConfig.h"

#include <R2D/src/Camera2D.h>
#include <R2D/src/SpriteBatch.h>
#include <R2D/src/ISaveable.h>
#include <R2D/src/ILoadable.h>
#include <R2D/src/IRegister.h>

#include <jsoncons/json.hpp>


class MainMap : public R2D::ISaveable<jsoncons::ojson>, public R2D::ILoadable<jsoncons::ojson>
{
private:
	using VectMap = std::vector<Tile>;
	using MatriceMap = std::vector<VectMap>;

public:
	void setStaticPtrTileSize();

public:
	static unsigned int convertIndexToPosX(const unsigned int index);
	static unsigned int convertPosXToIndex(const double posX);
	static unsigned int convertIndexToPosY(const unsigned int index);
	static unsigned int convertPosYToIndex(const double posY);
	static bool assertRangeMapIndex(const unsigned int indexToTest, const size_t size);

public:
	MainMap() = delete;
	explicit MainMap(R2D::RegisterPairVector& registerLoad);
	~MainMap();

	void initMainMap(R2D::Camera2D& camera, const GamePlayScreenTexture& idTexture);
	void initMainMapTexture(const GamePlayScreenTexture& idTexture);

private:
	void initTile();
	void generateMap();
	void setMinMaxScale(R2D::Camera2D& camera);
	void updateOffset(
		const double x0,
		const double y0,
		const unsigned int windowWidth,
		const unsigned int windowHeight,
		R2D::Camera2D& camera);
	void updateOffsetX(
		const double x0,
		const unsigned int windowWidth,
		R2D::Camera2D& camera);
	void updateOffsetY(
		const double y0,
		const unsigned int windowHeight,
		R2D::Camera2D& camera);

public:
	void drawMap(R2D::Camera2D& camera, R2D::Window& window);
	void renderMap();

public:
	inline unsigned int* GETtileSizePtr()			  { return &m_mainMapConfig.m_tileSize; };
	inline unsigned int GETtileSize()			const { return m_mainMapConfig.m_tileSize; };
	inline unsigned int GETtoolBarSize()		const { return m_toolBarSize; };

	inline MatriceMap& GETmatriceMap()					  { return m_matriceMap; };
	inline const MatriceMap& GETmatriceMapConst()	const { return m_matriceMap; };
	inline const R2D::SpriteBatch& GETspriteBatch()	const { return m_spriteBatch; };

	inline void SETMainMapConfig(const MainMapConfig& mainMapConfig) { m_mainMapConfig = mainMapConfig; };
	inline void SETtoolBarSize(unsigned int toolBarSize) {  m_toolBarSize = toolBarSize; };
	inline void SETmatriceMap(const MatriceMap& matriceMap) {  m_matriceMap = matriceMap; };
	inline void SETneedToUpdateDraw(bool needToUpdateDraw) { m_needToUpdateDraw = needToUpdateDraw; };

private:
	bool mapBordersConditions(const unsigned int i, const unsigned int j);
	void mapBorders(Tile& tile);
	void mapIntern(
		MatriceMap& maps,
		const unsigned int i,
		const unsigned int j);
	void tileAffectation(
		Tile& tile,
		const Ground_Type tile_ground,
		const GroundSpec_Type tile_spec,
		const int food,
		const int work,
		const int gold);

public:
	jsoncons::ojson save()const override { return saveToOjson(); };
	jsoncons::ojson saveToOjson()const;
	void load(jsoncons::ojson f)override { loadFromOjson(f); };
	void loadFromOjson(const jsoncons::ojson& jsonLoad);

public:
	unsigned int* GETtileSizePtr()const { return (unsigned int*)&m_mainMapConfig.m_tileSize; };

private:

	MainMapConfig m_mainMapConfig;

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