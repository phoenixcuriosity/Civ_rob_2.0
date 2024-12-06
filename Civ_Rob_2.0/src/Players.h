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

#ifndef Players_H
#define Players_H

#include "LIB.h"

#include "GamePlayScreenEnumTexture.h"

#include <R2D/src/WidgetLabel.h>

class Players
{
public:
	Players();
	~Players();

	inline int GETselectedPlayerId()const { return m_selectedPlayer; };
	inline PlayerPtrT& GETselectedPlayerPtr() { return m_selectedPlayerPtr; };
	inline VectCityName& GETvectCityName() { return m_vectCityName; };
	inline VectUnitTemplate& GETvectUnitTemplate() { return m_vectUnitTemplate; };
	inline VectPlayer& GETvectPlayer() { return m_vectPlayer; };
	inline bool* GETneedToUpdateDrawUnitPtr() { return &m_needToUpdateDrawUnit; };
	inline CityPtrT& GETSelectedCity() { return m_selectedCity; };

	inline void SETselectedPlayerId(const int selectedPlayer) { m_selectedPlayer = selectedPlayer; };
	inline void SETselectedPlayerPtr(PlayerPtrT& selectedPlayerPtr) { m_selectedPlayerPtr = selectedPlayerPtr; };
	inline void SETneedToUpdateDrawUnit(const bool need) { m_needToUpdateDrawUnit = need; };
	inline void SETneedToUpdateDrawCity(const bool need) { m_needToUpdateDrawCity = need; };
	inline void SetSelectedCity(CityPtrT selectedCity) { m_selectedCity = selectedCity; };

	inline bool isValidSelectedCity() { if (m_selectedCity != nullptr) return true; else return false; };

public:

	void init(const GamePlayScreenTexture& idTexture);

	void addPlayer
	(
		const std::string& name,
		const int id
	);

	void deleteAllPlayers();

	void removeIndexPlayer
	(
		const unsigned int index
	);

	void clickToSelectUnit
	(
		const unsigned int x,
		const unsigned int y
	);

	void isAUnitSelected();

	void drawUnit
	(
		const MainMap& mainMap,
		R2D::Camera2D& camera
	);

	void renderUnit();

	void drawCity
	(
		const MainMap& mainMap,
		R2D::Camera2D& camera,
		SpriteFont_PtrT& font
	);

	void renderCity();

	virtual bool searchCity
	(
		const unsigned int indexX,
		const unsigned int indexY
	);

public:

	jsoncons::ojson saveToOjson()const;

	void loadFromOjson(const jsoncons::ojson& jsonLoad);

private:

	// index du joueur actuellement sélectionné
	int m_selectedPlayer;
	/* Ptr to the selected Player */
	PlayerPtrT m_selectedPlayerPtr;

	/* Ptr to the selected City */
	CityPtrT m_selectedCity;

	VectCityName m_vectCityName;

	// tableau des statistiques par défauts des unités
	VectUnitTemplate m_vectUnitTemplate;
	VectUnitTemplate m_vectCityTemplate;

	GamePlayScreenTexture m_idTexture;

	VectPlayer m_vectPlayer;

	/* Dedicated spriteBatch for all Unit */
	R2D::SpriteBatch m_spriteBatchUnit;
	bool m_needToUpdateDrawUnit;
	/* Dedicated spriteBatch for all Cities */
	R2D::SpriteBatch m_spriteBatchCity;
	bool m_needToUpdateDrawCity;

	R2D::SpriteBatch m_spriteBatchCityDynamic;
};

#endif /* Players_H */

/*
*	End Of File : Players.h
*/