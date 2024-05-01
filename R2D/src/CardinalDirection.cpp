/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.7.0
	file version : 1.1

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

#include "CardinalDirection.h"

using namespace R2D;



CardinalDirection::CardinalDirection()
:
m_NS(NorthSouth::error),
m_EW(EstWest::error),
m_pixelValueNS(CARDINAL::PIXEL::DEFAULT),
m_pixelValueEW(CARDINAL::PIXEL::DEFAULT)
{
}

CardinalDirection::CardinalDirection
(
	/* IN */
	const NorthSouth NS,
	const EstWest EW,
	const int pixelValueNS,
	const int pixelValueEW
)
:
m_NS(NS),
m_EW(EW),
m_pixelValueNS(pixelValueNS),
m_pixelValueEW(pixelValueEW)
{
}

int CardinalDirection::GETpixelValueNS()const
{
	return m_pixelValueNS;
}

int CardinalDirection::GETpixelValueEW()const
{
	return m_pixelValueEW;
}