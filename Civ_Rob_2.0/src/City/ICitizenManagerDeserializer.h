#pragma once

#include <memory>

namespace city
{

class CitizenManager;

template<typename FormatType>
class ICitizenManagerDeserializer
{
public:
    virtual ~ICitizenManagerDeserializer() = default;
    virtual void deserialize(const FormatType& input, CitizenManager& citizenManager) const = 0;
};

}
