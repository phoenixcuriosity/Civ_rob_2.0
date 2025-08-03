#include "JsonFoodManagerSerializerVisitor.h"

#include "FoodManager.h"

void city::JsonFoodManagerSerializerVisitor::visit(const FoodManager& foodManager)
{
	result.clear();
	result.insert_or_assign("m_foodStock", foodManager.m_foodStock);
	result.insert_or_assign("m_foodBalance", foodManager.m_foodBalance);
	result.insert_or_assign("m_foodConsumption", foodManager.m_foodConsumption);
	result.insert_or_assign("m_foodSurplusPreviousTurn", foodManager.m_foodSurplusPreviousTurn);
	result.insert_or_assign("m_foodToLevelUp", foodManager.m_foodToLevelUp);
	result.insert_or_assign("m_emotionCoef", foodManager.m_emotionCoef);
	result.insert_or_assign("m_foodManagerType", static_cast<size_t>(foodManager.m_foodManagerType));
}

