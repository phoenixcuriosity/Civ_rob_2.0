#include "JsonCityDeserializer.h"

#include "City.h"

#include "JsonBuildManagerDeserializer.h"
#include "JsonCitizenManagerDeserializer.h"
#include "JsonFoodManagerDeserializer.h"

void
city::JsonCityDeserializer
::deserialize(const jsoncons::ojson& jsonLoad, std::shared_ptr<City>& city) const
{
	if (
		jsonLoad.contains("m_image") && jsonLoad.contains("m_name") && jsonLoad.contains("m_x") &&
		jsonLoad.contains("m_y") && jsonLoad.contains("m_influenceLevel") && jsonLoad.contains("m_atq") &&
		jsonLoad.contains("m_def") && jsonLoad.contains("m_nbstructurebuild") && jsonLoad.contains("Citizens") &&
		jsonLoad.contains("Food") && jsonLoad.contains("BuildQueue")
		)
	{
		city->m_image = jsonLoad["m_image"].as_string();
		city->m_name = jsonLoad["m_name"].as_string();
		city->m_coor.x = jsonLoad["m_x"].as<unsigned int>();
		city->m_coor.y = jsonLoad["m_y"].as<unsigned int>();
		city->m_influenceLevel = jsonLoad["m_influenceLevel"].as<unsigned int>();
		city->m_atq = jsonLoad["m_atq"].as<unsigned int>();
		city->m_def = jsonLoad["m_def"].as<unsigned int>();
		city->m_nbstructurebuild = jsonLoad["m_nbstructurebuild"].as<unsigned int>();

		JsonCitizenManagerDeserializer jsonCitizenManagerDeserializer;
		jsonCitizenManagerDeserializer.deserialize(jsonLoad["Citizens"], city->m_citizenManager);

		JsonFoodManagerDeserializer jsonFoodManagerDeserializer;
		jsonFoodManagerDeserializer.deserialize(jsonLoad["Food"], city->m_foodManager);

		JsonBuildManagerDeserializer jsonBuildManagerDeserializer;
		jsonBuildManagerDeserializer.deserialize(jsonLoad["BuildQueue"], city->m_buildManager, city->m_owner);
	}
    else
    {
        throw std::runtime_error("JsonCitizenDeserializer: Missing fields in JSON");
    }
}

