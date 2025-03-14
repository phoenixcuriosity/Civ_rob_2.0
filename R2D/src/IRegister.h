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

#include "FileSystem.h"
#include "FileSystemHandler.h"
#include "ISaveable.h"
#include "Files.h"

#include <jsoncons/json.hpp>

namespace R2D
{

class IRegister
{
private:
    using FilePath = e_Files;
    using FileSystemHandlerPtrT = std::shared_ptr<IFileSystem>;

    using SaveableSptr = R2D::ISaveable<jsoncons::ojson>*;
    using SaveableSptrFile = std::pair<FilePath, const SaveableSptr>;
    using SaveableSptrFileVector = std::vector<SaveableSptrFile>;

public:
    IRegister() : m_fileSysteme(std::make_shared<FileSystemHandler>()) {}
    void registerSaveable(const FilePath& file, const SaveableSptr loadable) { m_saveableSptrVector.push_back({ file , loadable }); };
    void save();

protected:
    FileSystemHandlerPtrT m_fileSysteme;
    SaveableSptrFileVector m_saveableSptrVector;
};


}
