#pragma once

#include "ICitizenManagerDeserializer.h"

#include <jsoncons/json.hpp>


namespace city
{

class JsonCitizenManagerDeserializer : public ICitizenManagerDeserializer<jsoncons::ojson>
{
public:
    JsonCitizenManagerDeserializer() = default;
    virtual ~JsonCitizenManagerDeserializer() = default;

    void deserialize(const jsoncons::ojson& input, CitizenManager& citizenManager) const override;
};

}

