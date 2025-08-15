#pragma once

namespace city
{

class CitizenManager;

class ICitizenManagerVisitor
{
public:
    virtual ~ICitizenManagerVisitor() = default;
    virtual void visit(const CitizenManager& citizenManager) = 0;
};

}

