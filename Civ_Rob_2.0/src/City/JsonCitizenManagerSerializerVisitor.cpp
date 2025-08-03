#include "JsonCitizenManagerSerializerVisitor.h"

#include "CitizenManager.h"
#include "Citizen.h"
#include "JsonCitizenSerializerVisitor.h"

void city::JsonCitizenManagerSerializerVisitor::visit(const CitizenManager& citizenManager)
{
	result.clear();
	jsoncons::ojson citizens{ jsoncons::ojson::make_array() };

	for (const auto citizen : citizenManager.m_citizens)
	{
		JsonCitizenSerializerVisitor visitor;
		citizen->accept(visitor);
		citizens.push_back(visitor.result);
	}
	result.insert_or_assign("Emotion", citizenManager.m_emotion);
	result.insert_or_assign("Citizens", citizens);
}


