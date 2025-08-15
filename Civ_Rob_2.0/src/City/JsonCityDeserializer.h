#pragma once

#include <R2D/src/IDeserializer.h>

#include <memory>

#include <jsoncons/json.hpp>


namespace city
{

class City;

class JsonCityDeserializer : public R2D::IDeserializer<jsoncons::ojson, std::shared_ptr<City>>
{
public:
    virtual ~JsonCityDeserializer() = default;

    void deserialize(const jsoncons::ojson& jsonLoad, std::shared_ptr<City>& city) const override;
};

}


