#pragma once

#include "Build.h"

#include <functional>

#include "Unit/Unit.h"
#include "BuildUnitCallbackStrategy.h"

namespace city
{

class BuildUnit : public Build
{
protected:
	using BuildCallbackStrategyPtr = std::shared_ptr<BuildUnitCallbackStrategy>;

public:
	BuildUnit(const jsoncons::ojson& loadFrom, BuildCallbackStrategyPtr strategy)
		: Build(loadFrom), m_strategy(std::move(strategy)) {}
	~BuildUnit() = default;

public:
	void buildInPlayer(const R2D::Coor& coor) override;

	void save(jsoncons::ojson& saveTo) override;

private:
	const std::string m_type = "Unit";
	const BuildCallbackStrategyPtr m_strategy;
};

}