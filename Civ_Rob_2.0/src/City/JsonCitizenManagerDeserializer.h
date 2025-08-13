#pragma once

#include <R2D/src/IDeserializer.h>

#include <jsoncons/json.hpp>


namespace city
{

class CitizenManager;

class JsonCitizenManagerDeserializer : public R2D::IDeserializer<jsoncons::ojson, CitizenManager>
{
public:
    virtual ~JsonCitizenManagerDeserializer() = default;

    void deserialize(const jsoncons::ojson& input, CitizenManager& citizenManager) const override;
};

}

