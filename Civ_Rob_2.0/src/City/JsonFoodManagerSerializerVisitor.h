#pragma once

#include "IFoodManagerVisitor.h"

#include <jsoncons/json.hpp>

namespace city
{

class JsonFoodManagerSerializerVisitor : public IFoodManagerVisitor
{
public:
    jsoncons::ojson result;

    void visit(const FoodManager& foodManager) override;
};

}

