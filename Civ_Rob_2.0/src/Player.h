/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
	last modification on this file on version:0.24.1.0
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

#ifndef Player_H
#define Player_H

#include "LIB.h"

#include <RealEngine2D/src/IGameScreen.h>
#include <RealEngine2D/src/IMainGame.h>
#include <RealEngine2D/src/GLSLProgram.h>
#include <RealEngine2D/src/Camera2D.h>
#include <RealEngine2D/src/WidgetLabel.h>
#include <RealEngine2D/src/SpriteBatch.h>
#include <RealEngine2D/src/AudioEngine.h>
#include <RealEngine2D/src/GUI.h>
#include <RealEngine2D/src/Window.h>

#include "Unit.h"
#include "City.h"

#include <memory>

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

#define INITIAL_GOLD 100.0

#define NO_PLAYER_SELECTED -1
#define NO_UNIT_SELECTED -1
#define NO_CITY_SELECTED -1

const unsigned int LIFE_BAR_NB_SUBDIVISION = 11;
const unsigned int NB_MAX_PLAYER = 9;
const unsigned int VECT_SIZE_OFFSET_ID = 1;

const unsigned int CITY_TYPE = 1;

/* *********************************************************
 *						 Enum							   *
 ********************************************************* */

enum class MajorAge : Uint8
{
	Nomade,
	Farming,
	Stone,
	Bronze,
	Iron,
	Antiquity,
	Vikings,
	Crusade,
	Renaissance,
	Colonization,
	Enlightenment,
	Industrial,
	Modern,
	Cyber,
	Stellar,
	Galactic
};

/* *********************************************************
 *						Structures						   *
 ********************************************************* */

struct GoldStats
{
	double gold;
	double goldBalance;
	double income;
	double cost;

	double taxIncome;
	double commerceIncome;
	double goldConversionSurplus;

	double armiesCost;
	double buildingsCost;
};

struct OnOffDisplay
{
	bool showContextGoldStats;
};


typedef std::vector<std::string> VectCityName;


/* *********************************************************
 *						 Classes						   *
 ********************************************************* */

class Player
{
public:
	/* *********************************************************
	 *					Player::METHODS						   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Player																	   */
	/* ROLE : Constructeur par d�faut													   */
	/* INPUT : void																		   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	Player();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Player																	   */
	/* ROLE : Constructeur par nom du joueur											   */
	/* INPUT : const std::string&														   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	Player
	(
		const std::string&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : ~Player																	   */
	/* ROLE : Initialisation d'une Unit vide											   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual ~Player();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator=																	   */
	/* ROLE : Red�finition de l'op�rateur =												   */
	/* INPUT : const Player& player : l'objet � copier									   */
	/* RETURNED VALUE : Player&	: l'objet recopi�										   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	Player& operator=
	(
		const Player& player
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deletePlayer																   */
	/* ROLE : Destruction de l'objet et de ses ptr										   */
	/* INPUT : void																		   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void deletePlayer();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : addEmptyUnit																   */
	/* ROLE : Initialisation d'une Unit vide											   */
	/* INPUT : void																		   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void addEmptyUnit();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : addUnit																	   */
	/* ROLE : Ajout une Unit avec les sp�cifications demand�es (nom, positions, ...)	   */
	/* INPUT : Sp�cifications demand�es (nom, positions, ...)							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void addUnit
	(
		const std::string& name,
		unsigned int x,
		unsigned int y,
		Unit_Movement_Type movementType,
		unsigned int life,
		unsigned int atq,
		unsigned int def,
		unsigned int move,
		unsigned int level,
		double maintenance
	);
	

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deleteUnit																   */
	/* ROLE : Suppression d'une Unit du joueur											   */
	/* INPUT : unsigned int : index de Unit dans le tableau								   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void deleteUnit
	(
		unsigned int index
	);
	

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : addCity																	   */
	/* ROLE : Ajout une City avec les sp�cifications demand�es (nom, positions, ...)	   */
	/* INPUT : Sp�cifications demand�es (nom, positions, ...)							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void addCity
	(
		const std::string&,
		unsigned int,
		unsigned int,
		VectMap& tiles
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deleteCity																   */
	/* ROLE : Suppression d'une City du joueur											   */
	/* INPUT : unsigned int : index de City dans le tableau								   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void deleteCity
	(
		unsigned int
	);

	virtual std::shared_ptr<City>* searchCity
	(
		unsigned int indexX,
		unsigned int indexY
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : computeGold																   */
	/* ROLE : Compute income and cost then the balance between the two					   */
	/* ROLE : Add balance to the player gold											   */
	/* INPUT : void																		   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void computeGold();

	virtual void computeMaintenanceCostUnit();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : resetGoldStats															   */
	/* ROLE : Reset all stats of m_goldStats except gold									   */
	/* INPUT : void																		   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void resetGoldStats();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : resetGoldStats															   */
	/* ROLE : Reset all stats of m_goldStats except gold									   */
	/* INPUT : double goldToAdd	: gold to add in goldConversionSurplus					   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	virtual void addGoldToGoldConversionSurplus
	(
		double goldToAdd
	);


public:
	/* *********************************************************
	 *				Player::METHODS::GET/SET				   *
	 ********************************************************* */


	inline virtual std::string GETname() const { return m_name; };
	inline virtual VectUnit GETtabUnit() const { return m_tabUnit; };
	inline virtual VectCity GETtabCity() const { return m_tabCity; };
	inline virtual int GETselectedUnit()const { return m_selectedUnit; };
	inline virtual int GETselectedCity() { return m_selectedCity; };
	inline virtual GoldStats& GETgoldStats() { return m_goldStats; };
	inline virtual GoldStats GETgoldStatsConst()const { return m_goldStats; };
	inline virtual OnOffDisplay& GETonOffDisplay() { return m_onOffDisplay; };
	inline virtual OnOffDisplay GETonOffDisplayConst()const { return m_onOffDisplay; };

	virtual std::shared_ptr<Unit>& GETSelectedUnitPtr(){return m_tabUnit[m_selectedUnit];}

	inline virtual void SETname(const std::string& msg) { m_name = msg; };
	inline virtual void SETselectedUnit(int selectedUnit) { m_selectedUnit = selectedUnit; };
	inline virtual void SETselectedCity(int selectedCity) { m_selectedCity = selectedCity; };

private:
	/* *********************************************************
	 *					Player::ATTRIBUTS					   *
	 ********************************************************* */


	std::string m_name;
	VectUnit m_tabUnit;
	VectCity m_tabCity;
	int m_selectedUnit;
	int m_selectedCity;
	GoldStats m_goldStats;
	OnOffDisplay m_onOffDisplay;
};

typedef std::vector< std::shared_ptr<Player>> VectPlayer;
typedef std::vector<GLuint> VectID;

class Players
{
public:
	Players();
	~Players();

	inline int GETselectedPlayerId()const { return m_selectedPlayer; };
	inline std::shared_ptr<Player>& GETselectedPlayerPtr() { return m_selectedPlayerPtr; };
	inline VectCityName& GETvectCityName() { return m_vectCityName; };
	inline VectUnitTemplate& GETvectUnitTemplate() { return m_vectUnitTemplate; };
	inline VectPlayer& GETvectPlayer() { return m_vectPlayer; };
	inline bool* GETneedToUpdateDrawUnitPtr() { return &m_needToUpdateDrawUnit; };
	inline std::shared_ptr<City>& GETSelectedCity() { return m_selectedCity; };

	inline void SETselectedPlayerId(int selectedPlayer) { m_selectedPlayer = selectedPlayer; };
	inline void SETselectedPlayerPtr(std::shared_ptr<Player>& selectedPlayerPtr) { m_selectedPlayerPtr = selectedPlayerPtr; };
	inline void SETneedToUpdateDrawUnit(bool need) { m_needToUpdateDrawUnit = need; };
	inline void SETneedToUpdateDrawCity(bool need) { m_needToUpdateDrawCity = need; };
	inline void SetSelectedCity(std::shared_ptr<City> selectedCity) { m_selectedCity = selectedCity; };

	inline bool isValidSelectedCity() { if (m_selectedCity != nullptr) return true; else return false; };

public:

	void init(const std::string& filePath);

	void addPlayer(const std::string& name);

	void deleteAllPlayers();

	void removeIndexPlayer
	(
		unsigned int index
	);

	void clickToSelectUnit(unsigned int x, unsigned int y);

	void isAUnitSelected();

	void drawUnit
	(
		const MainMap& mainMap,
		RealEngine2D::Camera2D& camera
	);

	void renderUnit();

	void drawCity
	(
		const MainMap& mainMap,
		RealEngine2D::Camera2D& camera,
		std::shared_ptr<RealEngine2D::SpriteFont>& font
	);

	void renderCity();

	virtual bool searchCity
	(
		unsigned int indexX,
		unsigned int indexY
	);

private:

	// index du joueur actuellement s�lectionn�
	int m_selectedPlayer;
	/* Ptr to the selected Player */
	std::shared_ptr<Player> m_selectedPlayerPtr;

	/* Ptr to the selected City */
	std::shared_ptr<City> m_selectedCity;

	VectCityName m_vectCityName;

	// tableau des statistiques par d�fauts des unit�s
	VectUnitTemplate m_vectUnitTemplate;
	VectID m_vectIDUnit;
	VectUnitTemplate m_vectCityTemplate;
	VectID m_vectIDCity;

	VectPlayer m_vectPlayer;

	/* Dedicated spriteBatch for all Unit */
	RealEngine2D::SpriteBatch m_spriteBatchUnit;
	bool m_needToUpdateDrawUnit;
	/* Dedicated spriteBatch for all Cities */
	RealEngine2D::SpriteBatch m_spriteBatchCity;
	bool m_needToUpdateDrawCity;

	RealEngine2D::SpriteBatch m_spriteBatchCityDynamic;
};



#endif /* Player_H */

/*
*	End Of File : Player.h
*/