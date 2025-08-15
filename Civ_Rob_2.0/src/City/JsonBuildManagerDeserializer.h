#pragma once

#include <R2D/src/IDeserializer.h>

#include <memory>

#include <jsoncons/json.hpp>

class Player;

namespace city
{

class BuildManager;

class JsonBuildManagerDeserializer : public R2D::IDeserializer<jsoncons::ojson, BuildManager, std::shared_ptr<Player>>
{
public:
    JsonBuildManagerDeserializer() = default;
    virtual ~JsonBuildManagerDeserializer() = default;

    void deserialize(const jsoncons::ojson& input, BuildManager& buildManager, std::shared_ptr<Player>& owner) const override;
};

}


