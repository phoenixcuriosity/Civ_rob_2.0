#pragma once

#include "ICitizenVisitor.h"

#include <jsoncons/json.hpp>

namespace city
{

class JsonCitizenSerializerVisitor : public ICitizenVisitor
{
public:
    jsoncons::ojson result;

    void visit(const Citizen& citizen) override;
};

}
