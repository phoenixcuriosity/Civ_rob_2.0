/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2025 (robin.sauter@orange.fr)

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

#include "T_Coor.h"
#include "Window.h"
#include <jsoncons/json.hpp>

namespace R2D
{

class IMoveable
{
protected:
	using Position = Coor::Position;
	using DeltaPosition = int;

public:
	IMoveable() : m_coor() {};
	IMoveable(const Coor& coor) : m_coor(coor) {};
	IMoveable(const Position& posX, const Position& posY) : m_coor(posX, posY) {};
	virtual ~IMoveable() = default;

	void moveX(const DeltaPosition& posX) { m_coor.x += posX; };
	void moveY(const DeltaPosition& posY) { m_coor.y += posY; };

	bool testPos(const Position& mouse_x, const Position& mouse_y) const noexcept { return (m_coor.x == mouse_x && m_coor.y == mouse_y);};
	bool testPos(const Coor& coor) const noexcept{ return testPos(coor.x, coor.y); };

public:
	const Coor& getCoor() const { return m_coor; };
	Coor& getCoor() { return m_coor; };
	const Position& getX() const { return m_coor.x; };
	const Position& getY() const { return m_coor.y; };

	void setCoor(const Coor& coor) { m_coor = coor; };

protected:
	Coor m_coor;
};


}
