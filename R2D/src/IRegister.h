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
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <typeindex>

#include "FileSystemHandler.h"
#include "ISaveable.h"
#include "ILoadable.h"
#include "Files.h"
#include "ResourceManager.h"

#include <jsoncons/json.hpp>

namespace R2D
{

class IRegister
{
protected:
    using FileSystemHandlerPtrT = std::shared_ptr<FileSystemHandler<jsoncons::ojson>>;

public:
    IRegister() : m_fileSysteme(std::make_shared<FileSystemHandler<jsoncons::ojson>>()) {}
	virtual ~IRegister() = default;

protected:
    FileSystemHandlerPtrT m_fileSysteme;
};

template<typename T>
class IRegisterSaveAble : virtual public IRegister
{
private:
    using FilePath = e_Files;
    using SaveableSptr = ISaveable<T>*;
    using SaveableSptrFile = std::pair<FilePath, SaveableSptr>;
    using SaveableSptrFileVector = std::vector<SaveableSptrFile>;

public:
	IRegisterSaveAble() {};
	virtual ~IRegisterSaveAble() = default;

    void registerSaveable(const FilePath& file, const SaveableSptr saveable)
	{
		m_saveableSptrVector.push_back({ file , saveable });
	}

    void unRegisterSaveable(const FilePath& file, const SaveableSptr saveable)
	{
		std::erase_if(m_saveableSptrVector, [file, saveable](const SaveableSptrFile& pair)
			{
				return ((pair.first == file) && (pair.second == saveable));
			});
	}

    void save()
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
			LOG(R2D::LogLevelType::error, 0, logR::WHO::REGISTER, logR::WHAT::REGISTER_DIRECTORY, logR::DATA::ERROR_DIR, e.what());
		}
	};

protected:
    SaveableSptrFileVector m_saveableSptrVector;
};

template<typename T>
class IRegisterLoadAble : virtual public IRegister
{
private:
    using FilePath = e_Files;
	using LoadableSptr = ILoadable<T>*;
	using LoadableSptrFile = std::pair<FilePath, LoadableSptr>;
	using LoadableSptrFileVector = std::vector<LoadableSptrFile>;

public:
	IRegisterLoadAble() {};
	virtual ~IRegisterLoadAble() = default;

    void registerLoadable(const FilePath& file, const LoadableSptr loadable)
	{
		m_loadableSptrVector.push_back({ file , loadable });
	}

	void unRegisterLoadable(const FilePath& file, const LoadableSptr loadable)
	{
		std::erase_if(m_loadableSptrVector, [file, loadable](const LoadableSptrFile& pair)
			{
				return ((pair.first == file) && (pair.second == loadable));
			});
	}

    virtual void load()
	{
		assert(m_fileSysteme);

		try
		{
			std::for_each(std::begin(m_loadableSptrVector), std::end(m_loadableSptrVector),
				[this](const LoadableSptrFile& loadable)
				{
					assert(loadable.second);
					loadable.second->load(m_fileSysteme->readDataFromFile(ResourceManager::getFile(loadable.first)));
				});
		}
		catch (const std::exception& e)
		{
			LOG(R2D::LogLevelType::error, 0, logR::WHO::REGISTER, logR::WHAT::REGISTER_DIRECTORY, logR::DATA::ERROR_DIR, e.what());
		}

	}

protected:
	LoadableSptrFileVector m_loadableSptrVector;
};

using RegisterPtrT = R2D::IRegisterLoadAble<jsoncons::ojson>*;
using RegisterPair = std::pair<RegisterPtrT, std::type_index>;
using RegisterPairVector = std::vector<RegisterPair>;


}
