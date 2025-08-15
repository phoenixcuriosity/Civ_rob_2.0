#include "JsonFoodManagerDeserializer.h"

#include "FoodManager.h"

void
city::JsonFoodManagerDeserializer
::deserialize(const jsoncons::ojson& input, FoodManager& foodManager) const
{
	if (
		input.contains("m_foodStock") && input.contains("m_foodBalance") && input.contains("m_foodConsumption") &&
		input.contains("m_foodSurplusPreviousTurn") && input.contains("m_foodToLevelUp") && input.contains("m_emotionCoef") &&
		input.contains("m_foodManagerType")
		)
	{
		foodManager.m_foodStock = input["m_foodStock"].as<double>();
		foodManager.m_foodBalance = input["m_foodBalance"].as<double>();
		foodManager.m_foodConsumption = input["m_foodConsumption"].as<double>();
		foodManager.m_foodSurplusPreviousTurn = input["m_foodSurplusPreviousTurn"].as<double>();
		foodManager.m_foodToLevelUp = input["m_foodToLevelUp"].as<double>();
		foodManager.m_emotionCoef = input["m_emotionCoef"].as<double>();
		foodManager.m_foodManagerType = static_cast<FoodManager::FoodManagerType>(input["m_foodStock"].as<double>());
	}
}
