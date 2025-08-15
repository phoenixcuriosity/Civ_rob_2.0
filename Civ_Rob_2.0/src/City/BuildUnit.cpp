#include "BuildUnit.h"

#include "BuildUnitCallbackStrategy.h"
#include "JsonBuildSerializerVisitor.h"

void
city::BuildUnit
::buildInPlayer()
{
	m_strategy->onBuild(m_name, m_coor);
}

void
city::BuildUnit
::accept(IBuildVisitor& visitor) const
{
	Build::accept(visitor);
	visitor.visit(*this);
}