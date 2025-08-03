#include "JsonCitySerializerVisitor.h"

#include "City.h"

#include "JsonBuildManagerSerializerVisitor.h"
#include "JsonCitizenManagerSerializerVisitor.h"
#include "JsonFoodManagerSerializerVisitor.h"

void city::JsonCitySerializerVisitor::visit(const City& city)
{
	result.clear();
	result.insert_or_assign("m_image", city.m_image);
	result.insert_or_assign("m_name", city.m_name);
	result.insert_or_assign("m_x", city.m_coor.x);
	result.insert_or_assign("m_y", city.m_coor.y);
	result.insert_or_assign("m_influenceLevel", city.m_influenceLevel);
	result.insert_or_assign("m_atq", city.m_atq);
	result.insert_or_assign("m_def", city.m_def);
	result.insert_or_assign("m_nbstructurebuild", city.m_nbstructurebuild);

	JsonCitizenManagerSerializerVisitor citizenManagerVisitor;
	city.m_citizenManager.accept(citizenManagerVisitor);
	result.insert_or_assign("Citizens", citizenManagerVisitor.result);

	JsonFoodManagerSerializerVisitor foodManagerVisitor;
	city.m_foodManager.accept(foodManagerVisitor);
	result.insert_or_assign("Food", foodManagerVisitor.result);

	JsonBuildManagerSerializerVisitor buildManagervisitor;
	city.m_buildManager.accept(buildManagervisitor);
	result.insert_or_assign("BuildQueue", buildManagervisitor.result);
}

