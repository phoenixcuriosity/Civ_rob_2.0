#pragma once

#include "IBuild.h"

#include <string>

#include <jsoncons/json.hpp>


namespace city
{

class Build : public IBuild
{
public:
	explicit Build(const jsoncons::ojson& loadFrom);
	Build(const double work, const std::string& name) noexcept : m_name(name), m_work(work), m_remainingWork(work) {}
	Build(const double work, const double remainingWork, const std::string& name) noexcept : m_name(name), m_work(work), m_remainingWork(remainingWork) {}
	virtual ~Build() = default;

	computeReturnedValue computeWorkToBuild(const double work) override;

	double getRemainingWorkoverWork() const noexcept override;

	virtual void accept(IBuildVisitor& visitor) const override;

protected:
	friend class JsonBuildSerializerVisitor;

	virtual void buildInPlayer() = 0;

protected:
	std::string m_name;
	double m_work;
	double m_remainingWork;
};


}
