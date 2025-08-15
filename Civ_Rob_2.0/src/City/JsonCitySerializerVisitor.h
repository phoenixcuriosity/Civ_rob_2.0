#pragma once

#include "ICityVisitor.h"

#include <jsoncons/json.hpp>

namespace city
{

class JsonCitySerializerVisitor : public ICityVisitor
{
public:
    jsoncons::ojson result;

    void visit(const City& city) override;
};

}
