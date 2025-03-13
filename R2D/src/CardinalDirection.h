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

#ifndef CardinalDirection_H
#define CardinalDirection_H

namespace R2D
{

class CardinalDirection
{
public:

	static constexpr unsigned int PIXEL_DEFAULT = 0;

	enum class NorthSouth
	{
		error = 0,
		north = 1,
		neutral = 2,
		south = 3
	};

	enum class EstWest
	{
		error = 0,
		est = 1,
		neutral = 2,
		west = 3
	};

	enum class Directions
	{
		error = 0,
		North = 1,
		NorthEst = 2,
		Est = 3,
		SouthEst = 4,
		South = 5,
		SouthWest = 6,
		West = 7,
		NorthWest = 8
	};
public:

	CardinalDirection() = delete;

	CardinalDirection(  const NorthSouth NS,
						const EstWest EW,
						const int pixelValueNS,
						const int pixelValueEW) noexcept
		: m_NS(NS), m_EW(EW), m_pixelValueNS(pixelValueNS), m_pixelValueEW(pixelValueEW){};

public:

	const int m_pixelValueNS;
	const int m_pixelValueEW;

private:
	const NorthSouth m_NS;
	const EstWest m_EW;
};

}

#endif //!CardinalDirection