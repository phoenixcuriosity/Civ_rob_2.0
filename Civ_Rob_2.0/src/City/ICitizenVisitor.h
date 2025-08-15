#pragma once

namespace city
{

class Citizen;

class ICitizenVisitor
{
public:
    virtual ~ICitizenVisitor() = default;
    virtual void visit(const Citizen& citizen) = 0;
};

}


