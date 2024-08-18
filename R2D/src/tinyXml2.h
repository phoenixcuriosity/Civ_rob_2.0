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

#ifndef tinyXml2_H
#define tinyXml2_H

#include <tinyxml2/tinyxml2.h>

namespace R2D
{
	namespace C_TINY_XML2
	{
		const uint8_t MAX_LEVEL = 10;
	}


	class tinyXml2
	{
	public:

		static tinyxml2::XMLElement* getFirstElement
		(
			/* IN */
			tinyxml2::XMLDocument& parentNode,
			const uint8_t maxLevel = C_TINY_XML2::MAX_LEVEL
		);

	private:

	};

}

#endif // !tinyXml2_H

