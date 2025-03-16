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
		if (f.contains(jsonloader::KEY_UNIT_TEMPLATE))
		{
			const std::vector<jsonloader::Unit_Template> units = f[jsonloader::KEY_UNIT_TEMPLATE].as<std::vector<jsonloader::Unit_Template>>();

			Template currentUnit;
			for (const auto& unit : units)
			{
				currentUnit.name = unit.name;
				currentUnit.type = static_cast<Movement_Type>(unit.type);
				currentUnit.life = unit.life;
				currentUnit.atq = unit.atq;
				currentUnit.def = unit.def;
				currentUnit.movement = unit.movement;
				currentUnit.numberOfAttack = unit.numberOfAttack;
				currentUnit.level = unit.level;
				currentUnit.workToBuild = unit.workToBuild;
				currentUnit.maintenance = unit.maintenance;

				m_vectUnitTemplate.push_back(currentUnit);
			}
		}
		else
		{
			LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_UNIT_CONFIG, logS::DATA::MISSING_KEY_JSON,
				R2D::ResourceManager::getFile(R2D::e_Files::units), jsonloader::KEY_UNIT_TEMPLATE);
		}
	}
	catch (const std::exception& e)
	{
		LOG(R2D::LogLevelType::error, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_UNIT_CONFIG, logS::DATA::ERROR_KEY_JSON, e.what());
	}
	initialized = true;

	LOG(R2D::LogLevelType::info, 0, logS::WHO::GAMEPLAY, logS::WHAT::LOAD_UNIT_CONFIG, logS::DATA::END);
}

unsigned int
UnitTemplate
::searchUnitByName(const std::string& name)const
{
	auto it = std::find_if(std::begin(m_vectUnitTemplate), std::end(m_vectUnitTemplate),
		[&name](const auto& unit) { return unit.name == name; });

	if (it != std::end(m_vectUnitTemplate))
	{
		return static_cast<unsigned int>(std::distance(std::begin(m_vectUnitTemplate), it));
	}

	throw std::runtime_error("Unit name not found: " + name);
}

