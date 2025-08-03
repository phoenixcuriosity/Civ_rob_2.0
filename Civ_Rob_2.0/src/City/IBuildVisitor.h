#pragma once

namespace city
{

class Build;
class BuildUnit;

class IBuildVisitor
{
public:
    virtual ~IBuildVisitor() = default;
    virtual void visit(const Build& build) = 0;
    virtual void visit(const BuildUnit& build) = 0;
};

}
