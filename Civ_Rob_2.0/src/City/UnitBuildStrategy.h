#pragma once

#include "BuildUnitCallbackStrategy.h"

#include <memory>

class Player;

namespace city
{

class UnitBuildStrategy : public BuildUnitCallbackStrategy
{
private:
    using PlayerPtrT = std::shared_ptr<Player>;
public:
    explicit UnitBuildStrategy(PlayerPtrT owner) : m_owner(owner) {}
    void onBuild(const std::string& name, const R2D::Coor& coor) override;

private:
    PlayerPtrT m_owner;
};

}
