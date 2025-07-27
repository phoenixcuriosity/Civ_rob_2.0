#pragma once

#include <memory>

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

public:
	static const IBuildPtrT createBuild(const buildT& buildT, const PlayerPtrT owner);
	static const IBuildPtrT createBuild(const jsoncons::ojson& buildT, const PlayerPtrT owner);
};


}

