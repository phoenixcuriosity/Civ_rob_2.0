#pragma once

#include "IBuildManagerVisitor.h"

#include <jsoncons/json.hpp>

namespace city
{

class JsonBuildManagerSerializerVisitor : public IBuildManagerVisitor
{
public:
    jsoncons::ojson result;

    void visit(const BuildManager& buildManager) override;
};

}



