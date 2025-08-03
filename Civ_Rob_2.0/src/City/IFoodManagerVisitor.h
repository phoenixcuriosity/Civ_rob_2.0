#pragma once

namespace city
{

class FoodManager;

class IFoodManagerVisitor
{
public:
	virtual ~IFoodManagerVisitor() = default;
	virtual void visit(const FoodManager& foodManager) = 0;
};

}

