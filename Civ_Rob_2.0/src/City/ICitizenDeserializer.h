#pragma once

#include <memory>

namespace city
{

class Citizen;

template<typename FormatType>
class ICitizenDeserializer
{
protected:
    using CitizenPtrT = std::shared_ptr<Citizen>;

public:
    virtual ~ICitizenDeserializer() = default;
    virtual CitizenPtrT deserialize(const FormatType& input) const = 0;
};

}

