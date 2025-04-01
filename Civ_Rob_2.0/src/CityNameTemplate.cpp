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

#include "CityNameTemplate.h"
#include "jsonloader.h"

#include "LogSentences.h"
#include <R2D/src/Log.h>
#include <R2D/src/ResourceManager.h>

CityNameTemplate
::CityNameTemplate(R2D::RegisterPairVector& registerLoad)
:CityNameTemplate()
{
	auto it = std::find_if(std::begin(registerLoad), std::end(registerLoad),
		[](const auto& pair) { return pair.second == typeid(CityNameTemplate); });

	if (it != std::end(registerLoad))
	{
		it->first->registerLoadable(R2D::e_Files::citiesNames, this);
	}
}

void
CityNameTemplate
::load(jsoncons::ojson f)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_CITY_NAME, logS::DATA::START);

	try
	{
		for (const auto& country : f.object_range())
		{
			m_vectTemplate.push_back(country.value().as<VectCityName>());
		}
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_UNIT_CONFIG, logS::DATA::ERROR_KEY_JSON, e.what());
	}

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_CITY_NAME, logS::DATA::END);
}