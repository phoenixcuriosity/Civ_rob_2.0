#pragma once


#include <memory>

namespace city
{

class FoodManager;

template<typename FormatType>
class IFoodManagerDeserializer
{
public:
    virtual ~IFoodManagerDeserializer() = default;
    virtual void deserialize(const FormatType& input, FoodManager& foodManager) const = 0;
};

}

