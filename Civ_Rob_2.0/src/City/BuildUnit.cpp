#include "BuildUnit.h"

#include "../Player.h"

void
city::BuildUnit
::buildInPlayer(PlayerPtrT& player, const R2D::Coor& coor)
{
	player->addUnit(m_name, coor);
}

void
city::BuildUnit
::save(jsoncons::ojson& saveTo)
{
	saveTo.insert_or_assign("type", m_type);
	Build::save(saveTo);
}