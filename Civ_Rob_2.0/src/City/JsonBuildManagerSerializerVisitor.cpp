#include "JsonBuildManagerSerializerVisitor.h"

#include "BuildManager.h"
#include "IBuild.h"
#include "JsonBuildSerializerVisitor.h"

void city::JsonBuildManagerSerializerVisitor::visit(const BuildManager& buildManager)
{
	result.clear();
	jsoncons::ojson builds{ jsoncons::ojson::make_array() };

	for (const auto& build : buildManager.m_buildQueue)
	{
		JsonBuildSerializerVisitor visitor;
		build.buildQ->accept(visitor);
		builds.push_back(visitor.result);
	}

	result.insert_or_assign("m_workBalance", buildManager.m_workBalance);
	result.insert_or_assign("m_workSurplusPreviousTurn", buildManager.m_workSurplusPreviousTurn);
	result.insert_or_assign("m_buildQueue", builds);
}

