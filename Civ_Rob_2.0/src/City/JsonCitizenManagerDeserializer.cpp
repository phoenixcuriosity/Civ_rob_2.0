#include "JsonCitizenManagerDeserializer.h"

#include "CitizenManager.h"
#include  "JsonCitizenDeserializer.h"

void
city::JsonCitizenManagerDeserializer
::deserialize(const jsoncons::ojson& jsonLoad, CitizenManager& citizenManager) const
{
	if (
			jsonLoad.contains("Emotion") &&
			jsonLoad.contains("Citizens") &&
			jsonLoad["Citizens"].is_array()
		)
	{
		citizenManager.m_emotion = jsonLoad["Emotion"].as<unsigned int>();

		for (const auto& citizenJson : jsonLoad["Citizens"].array_range())
		{
			std::shared_ptr<Citizen> citizenPtrT{nullptr};
			JsonCitizenDeserializer jsonCitizenDeserializer;
			jsonCitizenDeserializer.deserialize(citizenJson, citizenPtrT),
			citizenManager.m_citizens.push_back(citizenPtrT);
		}
	}
    else
    {
        throw std::runtime_error("JsonCitizenDeserializer: Missing fields in JSON");
    }
}
