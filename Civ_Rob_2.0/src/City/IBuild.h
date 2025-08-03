#pragma once

#include <utility>

namespace city
{

class IBuildVisitor;

class IBuild
{
public:
	using computeReturnedValue = std::pair<bool, double>;

public:
	virtual ~IBuild() = default;

	virtual computeReturnedValue computeWorkToBuild(const double work) = 0;

	virtual double getRemainingWorkoverWork() const noexcept = 0;

	virtual void accept(IBuildVisitor& visitor) const = 0;
};

}
