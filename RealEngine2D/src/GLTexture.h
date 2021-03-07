/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.2.0
	file version : 1.0

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


#include <string>
#include <vector>
#include <SDL\glew.h>

namespace RealEngine2D
{
	class GLTexture
	{
	public:
		GLTexture(const std::string& filePath);
		~GLTexture();

		inline GLuint& GETid() { return _id; };


	private:

		void init(const std::string& filePath);

		static bool readFileToBuffer
		(
			const std::string& filePath,
			std::vector<unsigned char>& buffer
		);


	private:

		GLuint _id;
		unsigned long  _width;
		unsigned long  _height;
	};
}
#endif /* GLTexture_H */