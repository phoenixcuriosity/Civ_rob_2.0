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

#include "Window.h"

namespace R2D
{

class IBlickable
{
private:
	using BlickingUnit = unsigned int;
	static constexpr BlickingUnit ZERO_BLICKING = 0;

public:
	IBlickable() = delete;
	IBlickable(const BlickingUnit& blickingRate) noexcept : m_show(true), m_blicking(ZERO_BLICKING), m_blickingRate(blickingRate) {};
	virtual ~IBlickable() = default;

	virtual void cmpblit() noexcept { if ((++m_blicking %= (SCREEN_REFRESH_RATE / m_blickingRate)) == ZERO_BLICKING) { m_show = !m_show; } };

protected:
	void makeShow() noexcept
	{
		m_blicking = ZERO_BLICKING;
		m_show = true;
	};

public:
	bool m_show;

private:
	BlickingUnit m_blicking;
	const BlickingUnit m_blickingRate;
};


}
