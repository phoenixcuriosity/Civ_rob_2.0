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

#include "SaveReload.h"

#include "App.h"
#include "Citizen.h"
#include "City.h"
#include "GamePlayScreen.h"
#include "LogSentences.h"
#include "MainMap.h"
#include "NewGameScreen.h"
#include "Player.h"
#include "Unit.h"
#include "T_Unit.h"

#include <jsoncons/json.hpp>
#include <R2D/src/ResourceManager.h> 
#include <R2D/src/ErrorLog.h> 
#include <R2D/src/ExitFromError.h> 
#include <R2D/src/Log.h> 

#include <filesystem>
#include <algorithm> // For std::max_element
#include <execution> // For std::execution::par

namespace SAVE
{
	constexpr size_t OFFSET_INDEX = 1;
}

void SaveReload::init()
{
	const std::string filePath{ R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath() };
	if (std::filesystem::exists(filePath) && std::filesystem::is_directory(filePath))
	{
		for (const auto& entry : std::filesystem::directory_iterator(filePath))
		{
			if (entry.is_directory())
			{
				m_tabSave.push_back(std::stoul(entry.path().stem().string()));
			}
		}
	}
}

void SaveReload::save
(
	const MainMap& mainMap,
	const Players& players
)
{
	saveMaps(mainMap);
	savePlayer(players);
}

void SaveReload::saveMaps
(
	const MainMap& mainMap
)
{
	try
	{
		std::ofstream ofs{ std::format("{}{:04}/{}",
				R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(),
				m_currentSave,
				R2D::ResourceManager::getFile(R2D::e_Files::saveMaps)->getPath() )};

		if (!ofs) { throw std::runtime_error("Failed to open file for writing."); }
	
		jsoncons::encode_json(mainMap.saveToOjson(), ofs, jsoncons::indenting::indent);
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::OPEN_FILE, logS::DATA::ERROR_OPEN_FILE,
			e.what());
	}
}

void SaveReload::savePlayer
(
	const Players& players
)
{
	try
	{
		std::ofstream ofs((std::format("{}{:04}/{}",
			R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(),
			m_currentSave,
			R2D::ResourceManager::getFile(R2D::e_Files::savePlayers)->getPath()).c_str()));

		if (!ofs) { throw std::runtime_error("Failed to open file for writing."); }

		jsoncons::encode_json(players.saveToOjson(), ofs, jsoncons::indenting::indent);
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::OPEN_FILE, logS::DATA::ERROR_OPEN_FILE,
			e.what());
	}
}

void SaveReload::reload
(
	GamePlayScreen& mainGame
)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::RELOAD, logS::DATA::START);

	loadMaps(mainGame.GETmainMap());
	loadPlayer(mainGame.GETPlayers());

	mainGame.GETvar().cinState = CinState_Type::cinMainMap;
	mainGame.GETPlayers().SETselectedPlayerId(SELECTION::NO_PLAYER_SELECTED);
	
	mainGame.makePlayersButtons();
	mainGame.GETmainMap().initMainMapTexture(mainGame.GETscreen().m_idTexture);

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::RELOAD, logS::DATA::END);
}

void SaveReload::loadMaps
(
	MainMap& mainMap
)
{
	try
	{
		const std::string text{ R2D::ResourceManager::loadFileToString((std::format("{}{:04}/{}",
			R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(),
			m_currentSave,
			R2D::ResourceManager::getFile(R2D::e_Files::saveMaps)->getPath()).c_str())) };

		mainMap.loadFromOjson(jsoncons::ojson::parse(text));
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_MAINMAP_CONFIG, logS::DATA::ERROR_KEY_JSON, e.what());
	}
}

void SaveReload::loadPlayer
(
	Players& players
)
{
	try
	{
		const std::string text{ R2D::ResourceManager::loadFileToString((std::format("{}{:04}/{}",
		R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(),
		m_currentSave,
		R2D::ResourceManager::getFile(R2D::e_Files::savePlayers)->getPath()).c_str())) };

		players.loadFromOjson(jsoncons::ojson::parse(text));
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_MAINMAP_CONFIG, logS::DATA::ERROR_KEY_JSON, e.what());
	}
}

void SaveReload::createSave()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_SAVE, logS::DATA::START);

	const auto max_it = std::max_element(std::execution::par, m_tabSave.begin(), m_tabSave.end());
	if (max_it != m_tabSave.end())
	{
		m_currentSave = (*max_it) + SAVE::OFFSET_INDEX;
	}
	else
	{
		m_currentSave = SAVE::OFFSET_INDEX;
	}
	m_tabSave.push_back(m_currentSave);

	createSaveDir();

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_SAVE, logS::DATA::END);
}

void SaveReload::createSaveDir()
{
	const std::string dir{ std::format("{}{:04}", R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(), m_currentSave) };

	if (!std::filesystem::create_directory(dir))
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_DIR, logS::DATA::ERROR_CREATE_DIR, dir);
	}
}

void SaveReload::removeSave()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_SAVE, logS::DATA::START);

	if (isSelectCurrentSave() && isSelectCurrentSaveInTab())
	{
		removeSaveDir(m_currentSave);

		removeIndex(m_currentSave);

		unselectCurrentSave();
	}
	else
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_SAVE, logS::DATA::ERROR_CURRENT_SAVE, m_currentSave);
	}

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_SAVE, logS::DATA::END);
}

void SaveReload::clearSave()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CLEAR_SAVES, logS::DATA::START);

	for (const auto index : m_tabSave)
	{
		removeSaveDir(index);
	}

	m_tabSave.clear();

	unselectCurrentSave();

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CLEAR_SAVES, logS::DATA::END);
}

void SaveReload::removeSaveDir(const size_t index)
{
	const std::string dir{ std::format("{}{:04}", R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(), index) };
	removeSaveFile(dir + "/" + R2D::ResourceManager::getFile(R2D::e_Files::saveMaps)->getPath());
	removeSaveFile(dir + "/" + R2D::ResourceManager::getFile(R2D::e_Files::savePlayers)->getPath());
	removeSaveFile(dir);
}

void SaveReload::removeSaveFile(const std::string& file)
{
	if (!std::filesystem::remove(file))
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_SAVE_FILE, logS::DATA::ERROR_DELETE_SAVE_FILE, file);
	}
	else
	{
		LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_SAVE_FILE, logS::DATA::ERROR_DELETE_SAVE_FILE, file + " successfully remove");
	}
}

void SaveReload::removeIndex(const size_t index)
{
	const auto itFound = std::find(m_tabSave.begin(), m_tabSave.end(), index);
	if (itFound != m_tabSave.end())
	{
		m_tabSave.erase(itFound);
	}
	else
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::DELETE_SAVE_FILE, logS::DATA::ERROR_ERASE_INDEX, *itFound);
	}
}

void SaveReload::unselectCurrentSave()
{
	m_currentSave = SELECTION::NO_CURRENT_SAVE_SELECTED;
}

bool SaveReload::isSelectCurrentSave()
{
	return m_currentSave != SELECTION::NO_CURRENT_SAVE_SELECTED;
}

bool SaveReload::isSelectCurrentSaveInTab()
{
	const auto findCurrentSave = std::find(m_tabSave.begin(), m_tabSave.end(), static_cast<size_t>(m_currentSave));
	if (findCurrentSave != m_tabSave.end())
	{
		return true;
	}
	return false;
}

SaveReload::SaveReload() 
: 
m_tabSave(),
m_currentSave(SELECTION::NO_CURRENT_SAVE_SELECTED)
{
}

SaveReload::~SaveReload()
{
}

void SaveReload::resetCurrentSave()
{
	m_currentSave = SELECTION::NO_CURRENT_SAVE_SELECTED;
}

 /*
 *	End Of File : SaveReload.cpp
 */