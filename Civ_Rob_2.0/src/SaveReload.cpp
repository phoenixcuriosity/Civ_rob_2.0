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

#include <jsoncons/json.hpp>
#include <R2D/src/ResourceManager.h>
#include <R2D/src/ErrorLog.h>
#include <R2D/src/ExitFromError.h>
#include <R2D/src/Log.h>

#include <filesystem>
#include <algorithm> // For std::max_element
#include <execution> // For std::execution::par

void
SaveReload
::init()
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

void
SaveReload
::registerSaveable(R2D::e_Files file, SaveableSptr saveable)
{
	m_saveableSptrVector.push_back({ file, saveable });
}

void
SaveReload
::registerLoadable(R2D::e_Files file, LoadableSptr loadable)
{
	m_loadableSptrVector.push_back({ file, loadable });
}

void
SaveReload
::unregisterSaveable(SaveableSptr saveable)
{
	std::erase_if(m_saveableSptrVector, [saveable](const SaveableSptrFile& pair)
		{
			return pair.second == saveable;
		});
}

void
SaveReload
::unregisterLoadable(LoadableSptr loadable)
{
	std::erase_if(m_loadableSptrVector, [loadable](const LoadableSptrFile& pair)
		{
			return pair.second == loadable;
		});
}


void SaveReload::save()
{
	try
	{
		assert(m_fileSysteme);

		std::for_each(std::begin(m_saveableSptrVector), std::end(m_saveableSptrVector),
			[this](SaveableSptrFile& saveable)
			{
				assert(saveable.second);
				m_fileSysteme->writeDataInFile(getSaveFilePath(saveable.first), saveable.second->save());
			});
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::OPEN_FILE, logS::DATA::ERROR_OPEN_FILE, e.what());
	}
}

void SaveReload::reload
(
	GamePlayScreen& mainGame
)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::RELOAD, logS::DATA::START);

	try
	{
		assert(m_fileSysteme);

		std::for_each(std::begin(m_loadableSptrVector), std::end(m_loadableSptrVector),
			[this](LoadableSptrFile& loadable)
			{
				assert(loadable.second);
				loadable.second->load(m_fileSysteme->readDataFromFile(getSaveFilePath(loadable.first), true));
			});
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_MAINMAP_CONFIG, logS::DATA::ERROR_KEY_JSON, e.what());
	}

	mainGame.GETvar().cinState = CinState_Type::cinMainMap;
	mainGame.GETPlayers().SETselectedPlayerId(SELECTION::NO_PLAYER_SELECTED);

	mainGame.makePlayersButtons();
	mainGame.GETmainMap().initMainMapTexture(mainGame.GETscreen().m_idTexture);

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::RELOAD, logS::DATA::END);
}

void SaveReload::createSave()
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_SAVE, logS::DATA::START);

	const auto max_it = std::max_element(std::execution::par, m_tabSave.begin(), m_tabSave.end());
	if (max_it != m_tabSave.end())
	{
		m_currentSave = (*max_it) + OFFSET_INDEX;
	}
	else
	{
		m_currentSave = OFFSET_INDEX;
	}
	m_tabSave.push_back(m_currentSave);

	createSaveDir();

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_SAVE, logS::DATA::END);
}

void SaveReload::createSaveDir()
{
	m_fileSysteme->createDirectory(std::format("{}{:04}", R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(), m_currentSave));
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

void SaveReload::removeSaveDir(const SaveId& index)
{
	const std::string dir{ std::format("{}{:04}", R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(), index) };
	removeSaveFile(dir + "/" + R2D::ResourceManager::getFile(R2D::e_Files::saveMaps)->getPath());
	removeSaveFile(dir + "/" + R2D::ResourceManager::getFile(R2D::e_Files::savePlayers)->getPath());
	removeSaveFile(dir);
}

void SaveReload::removeSaveFile(const std::string& file)
{
	m_fileSysteme->removeFile(file);
}

void SaveReload::removeIndex(const SaveId& index)
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

void SaveReload::unselectCurrentSave() noexcept
{
	m_currentSave = NO_CURRENT_SAVE_SELECTED;
}

bool SaveReload::isSelectCurrentSave() const noexcept
{
	return m_currentSave != NO_CURRENT_SAVE_SELECTED;
}

bool SaveReload::isSelectCurrentSaveInTab() const noexcept
{
	const auto findCurrentSave = std::find(m_tabSave.begin(), m_tabSave.end(), m_currentSave);
	if (findCurrentSave != m_tabSave.end())
	{
		return true;
	}
	return false;
}

void SaveReload::resetCurrentSave() noexcept
{
	m_currentSave = NO_CURRENT_SAVE_SELECTED;
}

SaveReload::FilePath
SaveReload
::getSaveFilePath(const R2D::e_Files file)
{
	return std::format("{}{:04}/{}",
		R2D::ResourceManager::getFile(R2D::e_Files::saveInfo)->getPath(),
		m_currentSave,
		R2D::ResourceManager::getFile(file)->getPath());
}

 /*
 *	End Of File : SaveReload.cpp
 */