#include "JsonCitizenSerializerVisitor.h"

#include "Citizen.h"

void city::JsonCitizenSerializerVisitor::visit(const Citizen& citizen)
{
	result.clear();
	result.insert_or_assign("m_tileOccupied", citizen.m_tileOccupied);
	result.insert_or_assign("m_happiness", static_cast<int>(citizen.m_happiness));
	result.insert_or_assign("m_food", citizen.m_food);
	result.insert_or_assign("m_work", citizen.m_work);
	result.insert_or_assign("m_gold", citizen.m_gold);
	result.insert_or_assign("m_revolt", citizen.m_revolt);
	result.insert_or_assign("m_religion", static_cast<size_t>(citizen.m_religion));
	result.insert_or_assign("m_place", citizen.m_place);
}

