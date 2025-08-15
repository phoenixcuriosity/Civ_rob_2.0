#pragma once

#include "IBuildVisitor.h"

#include <jsoncons/json.hpp>

namespace city
{

class JsonBuildSerializerVisitor : public IBuildVisitor
{
public:
    jsoncons::ojson result;

    void visit(const Build& build) override;
    void visit(const BuildUnit& build) override;
};

}


