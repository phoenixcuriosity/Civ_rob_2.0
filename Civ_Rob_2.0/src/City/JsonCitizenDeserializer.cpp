#include "JsonCitizenDeserializer.h"

#include "Citizen.h"

void
city::JsonCitizenDeserializer
::deserialize(const jsoncons::ojson& jsonLoad, std::shared_ptr<Citizen>& citizen) const
{
    if (
        jsonLoad.contains("m_tileOccupied") && jsonLoad.contains("m_food") &&
        jsonLoad.contains("m_work") && jsonLoad.contains("m_gold") &&
        jsonLoad.contains("m_happiness") && jsonLoad.contains("m_revolt") &&
        jsonLoad.contains("m_religion") && jsonLoad.contains("m_place")
        )
    {
        Citizen::TCitizenData data;
        data.tileOccupied = jsonLoad["m_tileOccupied"].as<unsigned int>();
        data.happiness = static_cast<Citizen::Emotion_Type>(jsonLoad["m_happiness"].as<int>());
        data.food = jsonLoad["m_food"].as<int>();
        data.work = jsonLoad["m_work"].as<int>();
        data.gold = jsonLoad["m_gold"].as<int>();
        data.revolt = jsonLoad["m_revolt"].as<int>();
        data.religion = static_cast<Citizen::Religion_Type>(jsonLoad["m_religion"].as<size_t>());
        data.place = jsonLoad["m_place"].as<bool>();

        citizen = std::make_shared<Citizen>(data);
    }
    else
    {
        throw std::runtime_error("JsonCitizenDeserializer: Missing fields in JSON");
    }
}
