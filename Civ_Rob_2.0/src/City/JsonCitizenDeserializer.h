#pragma once

#include "ICitizenDeserializer.h"

#include <jsoncons/json.hpp>

namespace city
{

class JsonCitizenDeserializer : public ICitizenDeserializer<jsoncons::ojson>
{
public:
    JsonCitizenDeserializer() = default;
    virtual ~JsonCitizenDeserializer() = default;

    CitizenPtrT deserialize(const jsoncons::ojson& input) const override;
};

}