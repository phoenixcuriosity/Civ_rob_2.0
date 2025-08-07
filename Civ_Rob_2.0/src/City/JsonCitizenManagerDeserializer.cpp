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

		for (const auto& citizen : jsonLoad["Citizens"].array_range())
		{
			JsonCitizenDeserializer jsonCitizenDeserializer;
			citizenManager.m_citizens.push_back(jsonCitizenDeserializer.deserialize(citizen));
		}
	}
    else
    {
        throw std::runtime_error("JsonCitizenDeserializer: Missing fields in JSON");
    }
}
