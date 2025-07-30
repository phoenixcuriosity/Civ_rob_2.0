#include "BuildUnit.h"

#include "UnitBuildStrategy.h"

void
city::BuildUnit
::buildInPlayer()
{
	m_strategy->onBuild(m_name, m_coor);
}

void
city::BuildUnit
::save(jsoncons::ojson& saveTo) const
{
	saveTo.insert_or_assign("type", m_type);
	Build::save(saveTo);
}