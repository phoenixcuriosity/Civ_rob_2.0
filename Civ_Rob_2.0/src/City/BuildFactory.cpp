#include "BuildFactory.h"

#include "BuildUnit.h"
#include "TBuild.h"

const city::BuildFactory::IBuildPtrT
city::BuildFactory::createBuild(const buildT& buildTc)
{
	switch (buildTc.type)
	{
	case build_Type::unit:
		return std::move(std::make_shared<BuildUnit>(buildTc.work, buildTc.name));
		break;
	}
	return {};
}

const city::BuildFactory::IBuildPtrT
city::BuildFactory::createBuild(const jsoncons::ojson& buildTs)
{
	switch (static_cast<build_Type>(buildTs["type"].as<size_t>()))
	{
	case build_Type::unit:
		return std::move(std::make_shared<BuildUnit>(buildTs));
		break;
	}
	return {};
}
