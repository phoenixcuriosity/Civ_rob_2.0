#include "Build.h"

#include "LIB.h"


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

void city::Build::save(jsoncons::ojson& saveTo) const
{
	saveTo.insert_or_assign("name", m_name);
	saveTo.insert_or_assign("work", m_work);
	saveTo.insert_or_assign("remainingWork", m_remainingWork);
}


double city::Build::getRemainingWorkoverWork() const noexcept
{
	return ((m_work - m_remainingWork) / m_work) * PERCENTAGE::ONE_HUNDRED;
}

