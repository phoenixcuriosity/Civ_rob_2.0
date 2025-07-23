#pragma once

#include "Build.h"

#include <functional>

#include "Unit/Unit.h"

namespace city
{

class BuildUnit : public Build
{
public:
	explicit BuildUnit(const jsoncons::ojson& loadFrom) : Build(loadFrom) {}
	BuildUnit(const double work, const std::string& name) : Build(work, name) {}
	BuildUnit(const double work, const double remainingWork, const std::string& name) : Build(work, remainingWork, name) {}
	~BuildUnit() = default;

	void buildInPlayer(PlayerPtrT& player, const R2D::Coor& coor) override;

	void save(jsoncons::ojson& saveTo) override;

private:
	const std::string m_type = "Unit";
};

}