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

#include <R2D/src/ILoadable.h>
#include <R2D/src/IRegister.h>

namespace city
{

class CityNameTemplate : public R2D::ILoadable<jsoncons::ojson>
{
public:
	using CityName = std::string;
	using VectCityName = std::vector<CityName>;
	using VectPlayerCityName = std::vector<VectCityName>;

public:

	static CityNameTemplate& getSingleton(std::optional<R2D::RegisterPairVector> registerLoad = std::nullopt)
	{
		static CityNameTemplate CityNameTemplate{ registerLoad };
		return CityNameTemplate;
	};

	explicit CityNameTemplate(std::optional<R2D::RegisterPairVector> registerLoad = std::nullopt);

	void load(jsoncons::ojson f)override;
	CityName& getCityName(const size_t indexPlayer, const size_t indexCityName) noexcept { return m_vectTemplate[indexPlayer][indexCityName]; };
	const CityName& getCityName(const size_t indexPlayer, const size_t indexCityName)const noexcept { return m_vectTemplate[indexPlayer][indexCityName]; };
protected:
	VectPlayerCityName m_vectTemplate;
};

}