#pragma once

#include "ICitizenManagerVisitor.h"

#include <jsoncons/json.hpp>

namespace city
{

class JsonCitizenManagerSerializerVisitor : public ICitizenManagerVisitor
{
public:
    jsoncons::ojson result;

    void visit(const CitizenManager& citizenManager) override;
};

}