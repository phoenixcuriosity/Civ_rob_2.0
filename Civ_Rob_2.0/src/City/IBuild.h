#pragma once

#include <memory>

#include <jsoncons/json.hpp>

namespace city
{

class IBuild
{
public:
	using computeReturnedValue = std::pair<bool, double>;

public:
	virtual ~IBuild() = default;

	virtual computeReturnedValue computeWorkToBuild(const double work) = 0;

	virtual void save(jsoncons::ojson& saveTo) const = 0;

	virtual double getRemainingWorkoverWork() const noexcept = 0;
};

}
