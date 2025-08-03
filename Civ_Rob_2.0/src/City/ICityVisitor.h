#pragma once

namespace city
{

class City;

class ICityVisitor
{
public:
	virtual ~ICityVisitor() = default;
	virtual void visit(const City& city) = 0;
};

}

