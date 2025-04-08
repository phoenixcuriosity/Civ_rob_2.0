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

#include <jsoncons/json.hpp>
#include <R2D/src/ILoadable.h>
#include <R2D/src/IRegister.h>

namespace unit
{

class UnitTemplate : public R2D::ILoadable<jsoncons::ojson>
{
public:
	using UnitName = std::string;

	enum class Movement_Type : size_t
	{
		ground,			/* The Unit can move on ground (dirt,grass,...) */
		air,			/* The Unit can move on ground (dirt,grass,...) or on water */
		water,			/* The Unit can move on water */
		deepwater		/* The Unit can move on deepwater or on water */
	};

	struct UnitStat
	{
		UnitStat() noexcept : movementType(Movement_Type::ground), life(0), atq(0), def(0), movement(0), numberOfAttack(0), level(0) {};
		UnitStat(const Movement_Type qtype, const unsigned int qlife, const unsigned int qatq, const unsigned int qdef,
				 const unsigned int qmovement, const unsigned int qnumberOfAttack, const unsigned int qlevel) noexcept
		: movementType(qtype), life(qlife), atq(qatq), def(qdef), movement(qmovement), numberOfAttack(qnumberOfAttack), level(qlevel) {};
		UnitStat(const UnitStat& src) noexcept
			: movementType(src.movementType), life(src.life), atq(src.atq), def(src.def), movement(src.movement), numberOfAttack(src.numberOfAttack), level(src.level) {};
		void set(const Movement_Type qtype, const unsigned int qlife, const unsigned int qatq, const unsigned int qdef,
				 const unsigned int qmovement, const unsigned int qnumberOfAttack, const unsigned int qlevel) noexcept
		{
			movementType = qtype;
			life = qlife;
			atq = qatq;
			def = qdef;
			movement = qmovement;
			numberOfAttack = qnumberOfAttack;
			level = qlevel;
		};

		Movement_Type movementType;
		unsigned int life;
		unsigned int atq;
		unsigned int def;
		unsigned int movement;
		unsigned int numberOfAttack;
		unsigned int level;
	};

	struct Template
	{
		UnitName name;
		Movement_Type type = Movement_Type::ground;
		unsigned int life = 0;
		unsigned int atq = 0;
		unsigned int def = 0;
		unsigned int movement = 0;
		unsigned int numberOfAttack = 0;
		unsigned int level = 0;
		unsigned int nbturnToBuild = 0;
		double workToBuild = 0.0;
		double maintenance = 0.0;
	};

	using TemplateVect = std::vector<Template>;
	using TemplateMap = std::map<UnitName, Template>;

public:
	struct TemplateJson
	{
		UnitName name;
		std::underlying_type_t<Movement_Type> type;
		unsigned int life;
		unsigned int atq;
		unsigned int def;
		unsigned int movement;
		unsigned int numberOfAttack;
		unsigned int level;
		unsigned int nbturnToBuild;
		double workToBuild;
		double maintenance;
	};
	using TemplateJsonVect = std::vector<TemplateJson>;

private:
	static constexpr char KEY_UNIT_TEMPLATE[] = "Units";

public:

	static UnitTemplate& getSingleton(std::optional<R2D::RegisterPairVector> registerLoad = std::nullopt)
	{
		static UnitTemplate unitTemplate{ registerLoad.value() };
		return unitTemplate;
	};

	UnitTemplate() noexcept : m_mapUnitTemplate() {};
	UnitTemplate(R2D::RegisterPairVector& registerLoad);
	virtual ~UnitTemplate() = default;

	void load(jsoncons::ojson f)override;

	int64_t searchUnitByName(const std::string& name) const;

	const Template& getTemplate(const UnitName& unitName)const;
	const TemplateMap& getTemplateMap()const { return m_mapUnitTemplate; };

protected:
	TemplateMap m_mapUnitTemplate;
};

}