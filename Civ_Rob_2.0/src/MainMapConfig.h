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

#include "LIB.h"

#include "T_MainMap.h"

#include <R2D/src/Camera2D.h>
#include <R2D/src/T_Coor.h>
#include <R2D/src/SpriteBatch.h>
#include <R2D/src/ISaveable.h>
#include <R2D/src/ILoadable.h>
#include <R2D/src/IRegister.h>


class MainMapConfig : public R2D::ILoadable<jsoncons::ojson>
{
private:
	static constexpr char KEY_MAP[] = "Map";
public:
	unsigned int m_tileSize = 0;
	R2D::Coor m_mapSizePix;
public:
	MainMapConfig() = default;
	MainMapConfig(R2D::RegisterPairVector& registerLoad);
	~MainMapConfig() = default;
	void load(jsoncons::ojson f)override;
};