#pragma once

#include <string>

namespace city
{

enum class build_Type : unsigned int
{
	building,	/* ### Not implemented as of 0.20.3.1 ### */
	unit
};

struct buildT
{
	std::string name;
	build_Type type = build_Type::building;
	double work = 0.0;
	double remainingWork = 0.0;
};

}



