#pragma once

#pragma once

#include <memory>
#include <functional>
#include <unordered_map>
#include <string>

#include <jsoncons/json.hpp>

class Player;

namespace city
{

class IBuild;
struct buildT;

class BuildFactory
{
private:
    using IBuildPtrT = std::shared_ptr<IBuild>;
    using PlayerPtrT = std::shared_ptr<Player>;
    using CreatorFn = std::function<IBuildPtrT(const jsoncons::ojson&, const PlayerPtrT&)>;

    static std::unordered_map<std::string, CreatorFn>& getRegistry();
    static jsoncons::ojson toJson(const city::buildT& build);

public:
    static IBuildPtrT commonUnitBuilder(const jsoncons::ojson& data, const PlayerPtrT& owner);

public:
    static IBuildPtrT createBuild(const buildT& buildT, const PlayerPtrT& owner);
    static IBuildPtrT createBuild(const jsoncons::ojson& buildTJson, const PlayerPtrT& owner);

    static void registerType(const std::string& typeName, CreatorFn creator);
};
}


