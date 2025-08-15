#pragma once

#include <string>

namespace R2D
{
    class Coor;
}

namespace city
{

class BuildUnitCallbackStrategy
{
public:
    virtual ~BuildUnitCallbackStrategy() = default;
    virtual void onBuild(const std::string& name, const R2D::Coor& coor) = 0;
};

}

