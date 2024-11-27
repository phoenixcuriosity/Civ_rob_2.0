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

#ifndef LogSentences_H
#define LogSentences_H

namespace logS
{
	namespace WHO
	{
		constexpr char APP[] = "[APP]";
		constexpr char GAMEPLAY[] = "[GamePlay]";
		constexpr char MAIN_MENU[] = "[MAIN_MENU]";
		constexpr char CITY_MENU[] = "[CITY_MENU]";
		constexpr char NEWGAME_MENU[] = "[NEWGAME_MENU]";
		constexpr char RELOAD_MENU[] = "[RELOAD_MENU]";
	};
	namespace WHAT
	{
		constexpr char CREATE_CITY[] = "[Create City]";
		constexpr char DELETE_CITY[] = "[Delete City]";

		constexpr char CREATE_CITIZEN[] = "[CREATE_CITIZEN]";
		constexpr char DELETE_CITIZEN[] = "[DELETE_CITIZEN]";

		constexpr char CREATE_PLAYER[] = "[CREATE_PLAYER]";
		constexpr char DELETE_PLAYER[] = "[DELETE_PLAYER]";

		constexpr char CREATE_UNIT[] = "[CREATE_UNIT]";
		constexpr char DELETE_UNIT[] = "[DELETE_UNIT]";

		constexpr char DELETE_TAB_CITY[] = "[DELETE_TAB_CITY]";
		constexpr char DELETE_TAB_UNIT[] = "[DELETE_TAB_UNIT]";

		constexpr char INIT_MAIN[] = "[INIT_MAIN]";
		constexpr char NEWGAME[] = "[newGame]";
		constexpr char LOAD_MAINMAP_CONFIG[] = "[loadMainMapConfig]";
		constexpr char LOAD_UNIT_CONFIG[] = "[LOAD_UNIT_CONFIG]";
		constexpr char LOAD_CITY_NAME[] = "[LOAD_CITY_NAME]";
		constexpr char LOAD_MAIN_MAP[] = "[LOAD_CITY_NAME]";
		constexpr char INIT_MAINMAP[] = "[initMainMap]";
		constexpr char GENERATION_MAINMAP[] = "[Map generation]";
		constexpr char RELOAD[] = "[RELOAD]";
		constexpr char SEARCH_UNIT_TILE[] = "[SEARCH_UNIT_TILE]";

		constexpr char CREATE_SAVE[] = "[CREATE_SAVE]";
		constexpr char CREATE_DIR[] = "[CREATE_DIR]";
		constexpr char DELETE_SAVE[] = "[DELETE_SAVE]";
		constexpr char DELETE_SAVE_FILE[] = "[DELETE_SAVE_FILE]";
		constexpr char CLEAR_SAVES[] = "[CLEAR_SAVES]";

		constexpr char CONSTRUCTOR[] = "[CONSTRUCTOR]";
		constexpr char DESTRUCTOR[] = "[DESTRUCTOR]";

		constexpr char OPEN_FILE[] = "[OPEN_FILE]";

		constexpr char ON_ENTRY[] = "[ON_ENTRY]";

		constexpr char COMPUTE_EMOTION[] = "[COMPUTE_EMOTION]";

		constexpr char BUTTON_CLICK[] = "[BUTTON_CLICK]";

		constexpr char VALUE_CONVERSION[] = "[VALUE_CONVERSION]";
		constexpr char TEXTURE[] = "[TEXTURE]";

		constexpr char UNIT[] = "[UNIT]";
	};
	namespace DATA
	{
		constexpr char MISSING_PATH_FILE[] = " Missing path for a file : {}";

		constexpr char CONSTRUCTOR_CITY[] = " : {}";
		constexpr char DESTRUCTOR_CITY[] = " -> m_name {}";

		constexpr char CONSTRUCTOR_CITIZEN[] = " : {}";

		constexpr char CONSTRUCTOR_PLAYER[] = " : {}";
		constexpr char DESTRUCTOR_PLAYER[] = " : {}";

		constexpr char CONSTRUCTOR_UNIT[] = " -> m_name : {} , m_x : {} , m_y : {}";
		constexpr char DESTRUCTOR_UNIT[] = " -> m_name {}";

		constexpr char ERROR_DELETE_TAB_UNIT[] = "[ERROR_DELETE_TAB_UNIT]";
		constexpr char ERROR_DELETE_TAB_CITY[] = "[ERROR_DELETE_TAB_CITY]";

		constexpr char EMPTY_DATA[] = "";
		constexpr char MSG_DATA[] = "{}";

		constexpr char START[] = "[START]";
		constexpr char END[] = "[END]";

		constexpr char MAINMAP[] = "[MAINMAP]";
		constexpr char SEARCH_UNIT_TILE[] = "Unit id selected : {} , Unit name {} , from player : {}";

		constexpr char ERROR_OPEN_FILE[] = "ERROR_OPEN_FILE : {}";
		constexpr char ERROR_CREATE_DIR[] = "ERROR_CREATE_DIR : {}";

		constexpr char ERROR_CURRENT_SAVE[] = "ERROR_CURRENT_SAVE : {}";
		constexpr char ERROR_DELETE_SAVE_FILE[] = "ERROR_DELETE_SAVE_FILE : {}";
		constexpr char ERROR_ERASE_INDEX[] = "ERROR_DELETE_SAVE_FILE : {}";

		constexpr char ERROR_DIV_ZERO[] = "ERROR_DIV_ZERO : {}";
		constexpr char ERROR_MIN_MAX_RANGE[] = "checkMinMaxValidityRange : {}";

		constexpr char PLAYER_BUTTON[] = "[PLAYER_BUTTON]";
		constexpr char EXIT_BUTTON[] = "[EXIT_BUTTON]";

		constexpr char ERROR_VALUE_CONVERSION[] = "[ERROR_VALUE_CONVERSION] : {} , {}";

		constexpr char SCREEN[] = "[SCREEN]";

		constexpr char ATTACK[] = "[ATTACK] : attack from {} to {}";
		constexpr char DIE_FROM_ATTACK[] = "[DIE_FROM_ATTACK] : {} : dmg receive : {}";
		constexpr char DMG_FROM_ATTACK[] = "[DMG_FROM_ATTACK] : {} : dmg receive : {} , life remaining {}";
		constexpr char MOVE[] = "[MOVE] : {} : movement remaining : {}";
		constexpr char FINISH_MOVING[] = "[FINISH_MOVING] : {}";


		constexpr char ERROR_KEY_JSON[] = "[ERROR_KEY_JSON] : {}";
		constexpr char MISSING_KEY_JSON[] = "[MISSING_KEY_JSON] : {} : {}";
	};
};



#endif // !LogSentences_H


