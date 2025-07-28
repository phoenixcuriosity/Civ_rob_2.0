#include "BuildUnit.h"

#include "UnitBuildStrategy.h"

void
city::BuildUnit
::buildInPlayer(const R2D::Coor& coor)
{
	m_strategy->onBuild(m_name, coor);
}

void
city::BuildUnit
::save(jsoncons::ojson& saveTo)
{
	saveTo.insert_or_assign("type", m_type);
	Build::save(saveTo);
}