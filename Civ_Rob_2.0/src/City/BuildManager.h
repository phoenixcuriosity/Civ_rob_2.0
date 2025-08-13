/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2024 (robin.sauter@orange.fr)

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Civ_rob_2.0

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#pragma once

#include <deque>
#include <memory>
#include <string>

namespace CEGUI
{
	class PushButton;
}

namespace R2D
{
	class Coor;
}

class Player;

namespace city
{

class IBuild;
class IBuildManagerVisitor;
class CitizenManager;
class FoodManager;
enum class conversionSurplus_Type : unsigned int;

class BuildManager
{
	friend class JsonBuildManagerDeserializer;
	friend class JsonBuildManagerSerializerVisitor;

private:
	using PlayerPtrT = std::shared_ptr<Player>;
private:
	static constexpr double RESOURCES_WORK_ZERO = 0.0;

public:
	using IBuildPtrT = std::shared_ptr<IBuild>;
	struct buildGUI
	{
		CEGUI::PushButton* buildG = nullptr;
		IBuildPtrT buildQ;
		std::string name;
	};
	using dequeBuild = std::deque<buildGUI>;

	/* Define the multiplier coefficient to convert work to food */
	static constexpr double WORK_TO_FOOD = 10.0;

	/* Define the multiplier coefficient to convert food to work */
	static constexpr double FOOD_TO_WORK = (1.0 / WORK_TO_FOOD);

	/* Define the multiplier coefficient to convert work to gold */
	static constexpr double WORK_TO_GOLD = (10.0 * WORK_TO_FOOD);

	/* Define the multiplier coefficient to convert food to gold */
	static constexpr double FOOD_TO_GOLD = (WORK_TO_GOLD / FOOD_TO_WORK);

public:

	BuildManager
	(
		const CitizenManager& citizenManager,
		FoodManager& foodManager,
		const conversionSurplus_Type& conversionToApplyf
	);
	~BuildManager();

public:
	void computeWork();
	void computeWorkToBuild(bool& needToUpdateDrawUnit);
	void convertFoodSurplusToWork(const double foodSurplus);
	void addBuildToQueue(const buildGUI& buildToQueue);
	void removeBuildToQueueFront();
	void removeBuildToQueue(const size_t index);
	void clearDynamicContextBuildToQueue();

	double GETBuildPerc()const;
	double getWorkBalance()const			{ return m_workBalance; };

	dequeBuild& getBuildQueue()				{ return m_buildQueue; };
	const dequeBuild& getBuildQueue()const	{ return m_buildQueue; };

public:
	void accept(IBuildManagerVisitor& visitor) const;

private:
	const CitizenManager& m_citizenManager;
	FoodManager& m_foodManager;
	const conversionSurplus_Type& m_conversionToApply;

	double m_workBalance;
	double m_workSurplusPreviousTurn;

	dequeBuild m_buildQueue;
};

}