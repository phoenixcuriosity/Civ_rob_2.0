#pragma once

#include "IFoodManagerDeserializer.h"

#include <jsoncons/json.hpp>


namespace city
{

class JsonFoodManagerDeserializer : public IFoodManagerDeserializer<jsoncons::ojson>
{
public:
    JsonFoodManagerDeserializer() = default;
    virtual ~JsonFoodManagerDeserializer() = default;

    void deserialize(const jsoncons::ojson& input, FoodManager& foodManager) const override;
};

}


