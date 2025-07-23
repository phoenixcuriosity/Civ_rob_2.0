#pragma once

#include <memory>

#include <jsoncons/json.hpp>

namespace city
{

class IBuild;
struct buildT;

class BuildFactory
{
private:
	using IBuildPtrT = std::shared_ptr<IBuild>;

public:
	static const IBuildPtrT createBuild(const buildT& buildT);
	static const IBuildPtrT createBuild(const jsoncons::ojson& buildT);
};


}

