#pragma once

#include "Build.h"
#include <memory>

#include <R2D/src/T_Coor.h>

namespace city
{

class BuildUnitCallbackStrategy;

class BuildUnit : public Build
{
	friend class JsonBuildSerializerVisitor;
protected:
	using BuildCallbackStrategyPtr = std::shared_ptr<BuildUnitCallbackStrategy>;
	using Coor = R2D::Coor;

public:
	BuildUnit(const jsoncons::ojson& loadFrom, const Coor& coor, BuildCallbackStrategyPtr strategy)
		: Build(loadFrom), m_strategy(std::move(strategy)), m_coor(coor){ }
	~BuildUnit() = default;

public:
	void buildInPlayer() override;

	void accept(IBuildVisitor& visitor) const override;

private:
	const std::string m_type = "Unit";
	const BuildCallbackStrategyPtr m_strategy;
	const Coor m_coor;
};

}