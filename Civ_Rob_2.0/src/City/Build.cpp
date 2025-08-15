#include "Build.h"

#include "LIB.h"

#include "JsonBuildSerializerVisitor.h"

city::Build::Build(const jsoncons::ojson& loadFrom)
:
m_name(loadFrom["name"].as_string()),
m_work(loadFrom["work"].as<double>()),
m_remainingWork(loadFrom["remainingWork"].as<double>())
{
}

city::IBuild::computeReturnedValue
city::Build
::computeWorkToBuild(const double work)
{
	bool returnValueBool{ false };
	double returnValueDouble{ 0.0 };

	m_remainingWork -= work;

	if (m_remainingWork <= 0.0)
	{
		buildInPlayer();
		returnValueBool = true;
		returnValueDouble = -m_remainingWork;
	}

	return { returnValueBool , returnValueDouble };
}

double city::Build::getRemainingWorkoverWork() const noexcept
{
	return ((m_work - m_remainingWork) / m_work) * PERCENTAGE::ONE_HUNDRED;
}

void
city::Build
::accept(IBuildVisitor& visitor) const
{
	visitor.visit(*this);
}

