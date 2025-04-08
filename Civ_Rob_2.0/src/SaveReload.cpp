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
#include "City/Citizen.h"
#include "City/City.h"
#include "Screens/GamePlayScreen.h"
#include "LogSentences.h"
#include "MainMap.h"
#include "Screens/NewGameScreen.h"
#include "Player.h"
#include "Unit/Unit.h"

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
	const std::string filePath{ R2D::ResourceManager::getFile(R2D::e_Files::saveInfo) };
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

void SaveReload::load()
{
	ModifySaveFileLocationToCurrent();
	IRegisterLoadAble::load();
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

	ModifySaveFileLocationToCurrent();

	createSaveDir();

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::CREATE_SAVE, logS::DATA::END);
}

void SaveReload::createSaveDir()
{
	m_fileSysteme->createDirectory(std::format("{}{:04}", R2D::ResourceManager::getFile(R2D::e_Files::saveInfo), m_currentSave));
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
	const std::string dir{ std::format("{}{:04}", R2D::ResourceManager::getFile(R2D::e_Files::saveInfo), index) };
	removeSaveFile(dir + "/" + R2D::ResourceManager::getFile(R2D::e_Files::saveMaps));
	removeSaveFile(dir + "/" + R2D::ResourceManager::getFile(R2D::e_Files::savePlayers));
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
	return std::format("{}{:04}/{}", R2D::ResourceManager::getFile(R2D::e_Files::saveInfo), m_currentSave, R2D::ResourceManager::getFile(file));
}

void
SaveReload
::ModifySaveFileLocationToCurrent()
{
	R2D::ResourceManager::ModifyFilePath(R2D::e_Files::saveMaps, getSaveFilePath(R2D::e_Files::saveMaps));
	R2D::ResourceManager::ModifyFilePath(R2D::e_Files::savePlayers, getSaveFilePath(R2D::e_Files::savePlayers));
}

 /*
 *	End Of File : SaveReload.cpp
 */