#include "UnitBuildStrategy.h"

#include "../Player.h"

void
city::UnitBuildStrategy
::onBuild(const std::string& name, const R2D::Coor& coor)
{
    m_owner->addUnit(name, coor);
}
