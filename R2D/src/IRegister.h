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


#include "FileSystem.h"
#include "FileSystemHandler.h"
#include "ISaveable.h"
#include "ILoadable.h"
#include "Files.h"

#include <jsoncons/json.hpp>

namespace R2D
{

class IRegister
{
protected:
    using FileSystemHandlerPtrT = std::shared_ptr<IFileSystem>;

public:
    IRegister() : m_fileSysteme(std::make_shared<FileSystemHandler>()) {}
	virtual ~IRegister() = default;

protected:
    FileSystemHandlerPtrT m_fileSysteme;
};

class IRegisterSaveAble : virtual public IRegister
{
private:
    using FilePath = e_Files;
    using SaveableSptr = ISaveable<jsoncons::ojson>*;
    using SaveableSptrFile = std::pair<FilePath, SaveableSptr>;
    using SaveableSptrFileVector = std::vector<SaveableSptrFile>;

public:
	IRegisterSaveAble() {};
	virtual ~IRegisterSaveAble() = default;
    void registerSaveable(const FilePath& file, const SaveableSptr saveable);
    void unRegisterSaveable(const FilePath& file, const SaveableSptr saveable);
    void save();

protected:
    SaveableSptrFileVector m_saveableSptrVector;
};

class IRegisterLoadAble : virtual public IRegister
{
private:
    using FilePath = e_Files;
	using LoadableSptr = ILoadable<jsoncons::ojson>*;
	using LoadableSptrFile = std::pair<FilePath, LoadableSptr>;
	using LoadableSptrFileVector = std::vector<LoadableSptrFile>;

public:
	IRegisterLoadAble() {};
	virtual ~IRegisterLoadAble() = default;
    void registerLoadable(const FilePath& file, const LoadableSptr loadable);
	void unRegisterLoadable(const FilePath& file, const LoadableSptr loadable);
    virtual void load();

protected:
	LoadableSptrFileVector m_loadableSptrVector;
};

using RegisterPtrT = R2D::IRegisterLoadAble*;
using RegisterPair = std::pair<RegisterPtrT, std::type_index>;
using RegisterPairVector = std::vector<RegisterPair>;


}
