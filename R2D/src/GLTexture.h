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

#ifndef GLTexture_H
#define GLTexture_H

#include "API_fwd.h"

namespace R2D
{
	class GLTexture
	{
	public:
		GLTexture(const std::string& filePath);
		~GLTexture();

		inline GLuint& GETid() { return m_id; };


	private:

		void init(const std::string& filePath);

		static bool readFileToBuffer
		(
			const std::string& filePath,
			std::vector<unsigned char>& buffer
		);


	private:

		GLuint m_id;
		unsigned long m_width;
		unsigned long m_height;
	};
}
#endif /* GLTexture_H */