#pragma once

#include <memory>

#include <jsoncons/json.hpp>

class Player;

namespace R2D
{
	class Coor;
}

namespace city
{

class IBuild
{
public:
	using computeReturnedValue = std::pair<bool, double>;

protected:
	using PlayerPtrT = std::shared_ptr<Player>;

public:
	virtual ~IBuild() = default;

	virtual computeReturnedValue computeWorkToBuild(const double work, const R2D::Coor& coor) = 0;

	virtual void save(jsoncons::ojson& saveTo) = 0;

	virtual double getRemainingWorkoverWork() const = 0;
};

}
