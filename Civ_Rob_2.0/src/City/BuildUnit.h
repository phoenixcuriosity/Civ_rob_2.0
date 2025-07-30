#pragma once

#include "Build.h"

#include <functional>

#include <R2D/src/T_Coor.h>
#include "BuildUnitCallbackStrategy.h"

namespace city
{

class BuildUnit : public Build
{
protected:
	using BuildCallbackStrategyPtr = std::shared_ptr<BuildUnitCallbackStrategy>;
	using Coor = R2D::Coor;

public:
	BuildUnit(const jsoncons::ojson& loadFrom, const Coor& coor, BuildCallbackStrategyPtr strategy)
		: Build(loadFrom), m_strategy(std::move(strategy)), m_coor(coor){ }
	~BuildUnit() = default;

public:
	void buildInPlayer() override;

	void save(jsoncons::ojson& saveTo) const override;

private:
	const std::string m_type = "Unit";
	const BuildCallbackStrategyPtr m_strategy;
	const Coor m_coor;
};

}