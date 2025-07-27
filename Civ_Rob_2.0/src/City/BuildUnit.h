#pragma once

#include "Build.h"

#include <functional>

#include "Unit/Unit.h"

namespace city
{

class BuildUnit : public Build
{
protected:
	using CallbackT = std::function<void(const unit::Unit::UnitName&, const R2D::Coor&)>;

public:
	BuildUnit(const jsoncons::ojson& loadFrom, CallbackT cb)
		: Build(loadFrom), m_callback(std::move(cb))
	{
		if (!m_callback) throw std::runtime_error("Missing callback");
	}
	BuildUnit(const double work, const std::string& name, CallbackT cb)
		: Build(work, name), m_callback(std::move(cb))
	{
		if (!m_callback) throw std::runtime_error("Missing callback");
	}
	BuildUnit(const double work, const double remainingWork, const std::string& name, CallbackT cb)
		: Build(work, remainingWork, name), m_callback(std::move(cb))
	{
		if (!m_callback) throw std::runtime_error("Missing callback");
	}
	~BuildUnit() = default;

public:
	void buildInPlayer(const R2D::Coor& coor) override;

	void save(jsoncons::ojson& saveTo) override;

private:
	const std::string m_type = "Unit";
	CallbackT m_callback;
};

}