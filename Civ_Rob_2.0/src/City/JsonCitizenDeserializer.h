#pragma once

#include <R2D/src/IDeserializer.h>

#include <jsoncons/json.hpp>

namespace city
{

class Citizen;

class JsonCitizenDeserializer : public R2D::IDeserializer<jsoncons::ojson, std::shared_ptr<Citizen>>
{
public:
    virtual ~JsonCitizenDeserializer() = default;

    void deserialize(const jsoncons::ojson& input, std::shared_ptr<Citizen>& citizen) const override;
};

}