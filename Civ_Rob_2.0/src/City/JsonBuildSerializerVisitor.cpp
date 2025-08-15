#include "JsonBuildSerializerVisitor.h"

#include "BuildUnit.h"

void city::JsonBuildSerializerVisitor::visit(const Build& build)
{
    result.clear();
    result.insert_or_assign("name", build.m_name);
    result.insert_or_assign("work", build.m_work);
    result.insert_or_assign("remainingWork", build.m_remainingWork);
}


void city::JsonBuildSerializerVisitor::visit(const BuildUnit& build)
{
    result.insert_or_assign("type", build.m_type);
}
