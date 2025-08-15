#pragma once

namespace city
{

class BuildManager;

class IBuildManagerVisitor
{
public:
    virtual ~IBuildManagerVisitor() = default;
    virtual void visit(const BuildManager& buildManager) = 0;
};

}

