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
	namespace CARDINAL
	{
		namespace PIXEL
		{
			const unsigned int DEFAULT = 0;
		}
	}

	enum class NorthSouth
	{
		error	= 0,
		north	= 1,
		neutral = 2,
		south	= 3
	};

	enum class EstWest
	{
		error	= 0,
		est		= 1,
		neutral = 2,
		west	= 3
	};

	enum class CardinalDirections
	{
		error		= 0,
		North		= 1,
		NorthEst	= 2,
		Est			= 3,
		SouthEst	= 4,
		South		= 5,
		SouthWest	= 6,
		West	    = 7,
		NorthWest	= 8
	};

	class CardinalDirection
	{
	public:

		CardinalDirection();

		CardinalDirection
		(
			/* IN */
			const NorthSouth NS,
			const EstWest EW,
			const int pixelValueNS,
			const int pixelValueEW
		);

		~CardinalDirection() {};

		int GETpixelValueNS()const;
		int GETpixelValueEW()const;
		
	private:

		NorthSouth m_NS;
		EstWest m_EW;

		int m_pixelValueNS;
		int m_pixelValueEW;
	};

}

#endif //!CardinalDirection