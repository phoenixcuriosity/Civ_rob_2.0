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

#include "UnitTemplate.h"
#include "jsonloader.h"

#include "LogSentences.h"
#include <R2D/src/Log.h>
#include <R2D/src/ResourceManager.h>

UnitTemplate
::UnitTemplate(R2D::RegisterPairVector& registerLoad)
: UnitTemplate()
{
	auto it = std::find_if(std::begin(registerLoad), std::end(registerLoad),
		[](const auto& pair) { return pair.second == typeid(UnitTemplate); });

	if (it != std::end(registerLoad))
	{
		it->first->registerLoadable(R2D::e_Files::units, this);
	}
}

void
UnitTemplate
::load(jsoncons::ojson f)
{
	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_UNIT_CONFIG, logS::DATA::START);
	try
	{
		if (f.contains(KEY_UNIT_TEMPLATE))
		{
			const TemplateJsonVect units = f[KEY_UNIT_TEMPLATE].as<TemplateJsonVect>();

			std::transform(units.begin(), units.end(), std::inserter(m_mapUnitTemplate, m_mapUnitTemplate.end()), [](const auto& unit)
				{
					return std::make_pair(unit.name,
						Template{
							unit.name,
							static_cast<Movement_Type>(unit.type),
							unit.life,
							unit.atq,
							unit.def,
							unit.movement,
							unit.numberOfAttack,
							unit.level,
							unit.nbturnToBuild,
							unit.workToBuild,
							unit.maintenance
						});
				});
		}
		else
		{
			LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_UNIT_CONFIG, logS::DATA::MISSING_KEY_JSON,
				R2D::ResourceManager::getFile(R2D::e_Files::units), KEY_UNIT_TEMPLATE);
		}
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_UNIT_CONFIG, logS::DATA::ERROR_KEY_JSON, e.what());
	}

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_UNIT_CONFIG, logS::DATA::END);
}

int64_t
UnitTemplate
::searchUnitByName(const std::string& name)const
{
	const auto it{ m_mapUnitTemplate.find(name) };

	if (it != m_mapUnitTemplate.end())
	{
		return std::distance(m_mapUnitTemplate.begin(), it);
	}

	throw std::runtime_error("Unit name not found: " + name);
}

const UnitTemplate::Template&
UnitTemplate
::getTemplate(const UnitName& unitName)const
{
	try
	{
		return m_mapUnitTemplate.at(unitName);
	}
	catch (const std::out_of_range& e)
	{
		throw std::runtime_error("Unit key not found in m_mapUnitTemplate: " + std::string(e.what()));
	}
}
