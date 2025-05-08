/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)

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

#ifndef SaveReload_H
#define SaveReload_H

#include "LIB.h"

#include <R2D/src/FileSystemHandler.h>

#include <R2D/src/Files.h>
#include <R2D/src/IRegister.h>
#include <limits>

class SaveReload : public R2D::IRegisterSaveAble<jsoncons::ojson>, public R2D::IRegisterLoadAble<jsoncons::ojson>
{
private:
	using FilePath = std::string;
	using SaveId = size_t;
	using SaveIdVect = std::vector<SaveId>;

	static constexpr SaveId OFFSET_INDEX = 1;
	static constexpr SaveId NO_CURRENT_SAVE_SELECTED = std::numeric_limits<size_t>::max();
public:
	static SaveReload& getInstance()
	{
		static SaveReload instance;
		return instance;
	}

	SaveReload() : IRegisterSaveAble<jsoncons::ojson>(), IRegisterLoadAble<jsoncons::ojson>(), IRegister() , m_tabSave(), m_currentSave(NO_CURRENT_SAVE_SELECTED) {}
	SaveReload(const SaveReload&) = delete;
	virtual ~SaveReload() = default;

	void init();

	void load() override;

public:
	void createSave();
	void removeSave();
	void clearSave();

private:
	void createSaveDir();
	void removeSaveDir(const SaveId& index);
	void removeSaveFile(const std::string& file);
	void removeIndex(const SaveId& index);
	void unselectCurrentSave() noexcept;
	bool isSelectCurrentSaveInTab() const noexcept;

public:
	bool isSelectCurrentSave() const noexcept;

private:
	FilePath getSaveFilePath(const R2D::e_Files file);
	void ModifySaveFileLocationToCurrent();

public:
	inline const SaveId& getSave(const SaveId& saveId) const noexcept { return m_tabSave[saveId]; };
	inline size_t getSaveSize() const noexcept { return m_tabSave.size(); };
	inline const SaveId& getCurrentSave()const noexcept { return m_currentSave; };

	inline void setCurrentSave(const SaveId& currentSave) noexcept { m_currentSave = currentSave; };

	inline void resetCurrentSave() noexcept;

private:
	SaveIdVect m_tabSave;
	SaveId m_currentSave;
};


#endif /* SaveReload_H */

/*
*	End Of File : SaveReload.h
*/
