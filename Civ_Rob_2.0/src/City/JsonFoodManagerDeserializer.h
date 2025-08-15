#pragma once

#include <R2D/src/IDeserializer.h>

#include <jsoncons/json.hpp>

namespace city
{

class FoodManager;

class JsonFoodManagerDeserializer : public R2D::IDeserializer<jsoncons::ojson, FoodManager>
{
public:
    JsonFoodManagerDeserializer() = default;
    virtual ~JsonFoodManagerDeserializer() = default;

    void deserialize(const jsoncons::ojson& input, FoodManager& foodManager) const override;
};

}


