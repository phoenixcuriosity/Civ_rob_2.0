#include "BuildFactory.h"
#include "BuildUnit.h"
#include "Player.h"
#include "TBuild.h"


std::unordered_map<std::string, city::BuildFactory::CreatorFn>&
city::BuildFactory
::getRegistry()
{
    static std::unordered_map<std::string, CreatorFn> registry;
    return registry;
}

std::string toString(city::build_Type type)
{
    switch (type)
    {
    case city::build_Type::unit: return "Unit";
    case city::build_Type::building: return "Building";
    }
    return "Unknown";
}

static jsoncons::ojson toJson(const city::buildT& build)
{
    jsoncons::ojson obj;
    obj.insert_or_assign("name", build.name);
    obj.insert_or_assign("work", build.work);
    obj.insert_or_assign("remainingWork", build.remainingWork);
    obj.insert_or_assign("type", toString(build.type));
    return obj;
}

city::BuildFactory::IBuildPtrT
city::BuildFactory
::commonUnitBuilder(const jsoncons::ojson& data, const PlayerPtrT& owner)
{
    auto callback = [owner](const auto& name, const auto& coor){owner->addUnit(name, coor);};
    return std::make_shared<BuildUnit>(data, std::move(callback));
}

city::BuildFactory::IBuildPtrT
city::BuildFactory
::createBuild(const buildT& buildTc, const PlayerPtrT& owner)
{
    return createBuild(toJson(buildTc), owner);
}

city::BuildFactory::IBuildPtrT
city::BuildFactory
::createBuild(const jsoncons::ojson& buildTs, const PlayerPtrT& owner)
{
    const auto& typeStr = buildTs["type"].as_string();
    auto& registry = getRegistry();

    auto it = registry.find(typeStr);
    if (it != registry.end())
    {
        return it->second(buildTs, owner);
    }
    throw std::runtime_error("Unknown build type: " + typeStr);
}

void
city::BuildFactory
::registerType(const std::string& typeName, CreatorFn creator)
{
    getRegistry()[typeName] = std::move(creator);
}