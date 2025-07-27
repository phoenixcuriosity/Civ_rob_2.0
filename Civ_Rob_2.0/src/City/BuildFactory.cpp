#include "BuildFactory.h"

#include "BuildUnit.h"
#include "TBuild.h"
#include "Player.h"

const city::BuildFactory::IBuildPtrT
city::BuildFactory::createBuild(const buildT& buildTc, const PlayerPtrT owner)
{
	const auto fun = [owner](const auto& name, const auto& coor) {owner->addUnit(name, coor); };

	switch (buildTc.type)
	{
	case build_Type::unit:
		return std::move(std::make_shared<BuildUnit>(buildTc.work, buildTc.name, std::move(fun)));
		break;
	}
	return {};
}

const city::BuildFactory::IBuildPtrT
city::BuildFactory::createBuild(const jsoncons::ojson& buildTs, const PlayerPtrT owner)
{
	const auto fun = [owner](const auto& name, const auto& coor) {owner->addUnit(name, coor); };

	switch (static_cast<build_Type>(buildTs["type"].as<size_t>()))
	{
	case build_Type::unit:
		return std::move(std::make_shared<BuildUnit>(buildTs, std::move(fun)));
		break;
	}
	return {};
}
