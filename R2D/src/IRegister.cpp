/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2025 (robin.sauter@orange.fr)

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

#include "IRegister.h"
#include "ResourceManager.h"

#include "ErrorLog.h"
#include "log.h"
#include "LogSentences.h"

void
R2D::IRegisterSaveAble
::registerSaveable(const FilePath& file, const SaveableSptr saveable)
{
	m_saveableSptrVector.push_back({ file , saveable });
};

void
R2D::IRegisterSaveAble
::unRegisterSaveable(const FilePath& file, const SaveableSptr saveable)
{
	std::erase_if(m_saveableSptrVector, [file, saveable](const SaveableSptrFile& pair)
		{
			return ((pair.first == file) && (pair.second == saveable));
		});
};


void
R2D::IRegisterSaveAble
::save()
{
	assert(m_fileSysteme);

	try
	{
		std::for_each(std::begin(m_saveableSptrVector), std::end(m_saveableSptrVector),
		[this](const SaveableSptrFile& saveable)
		{
			assert(saveable.second);
			m_fileSysteme->writeDataInFile(ResourceManager::getFile(saveable.first), saveable.second->save());
		});
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::REGISTER, logS::WHAT::REGISTER_DIRECTORY, logS::DATA::ERROR_DIR, e.what());
	}
};

void
R2D::IRegisterLoadAble
::registerLoadable(const FilePath& file, const LoadableSptr loadable)
{
	m_loadableSptrVector.push_back({ file , loadable });
};

void
R2D::IRegisterLoadAble
::unRegisterLoadable(const FilePath& file, const LoadableSptr loadable)
{
	std::erase_if(m_loadableSptrVector, [file, loadable](const LoadableSptrFile& pair)
		{
			return ((pair.first == file) && (pair.second == loadable));
		});
};

void
R2D::IRegisterLoadAble
::load()
{
	assert(m_fileSysteme);

	try
	{
		std::for_each(std::begin(m_loadableSptrVector), std::end(m_loadableSptrVector),
			[this](const LoadableSptrFile& loadable)
			{
				assert(loadable.second);
				loadable.second->load(m_fileSysteme->readDataFromFile(ResourceManager::getFile(loadable.first), true));
			});
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::REGISTER, logS::WHAT::REGISTER_DIRECTORY, logS::DATA::ERROR_DIR, e.what());
	}

};
