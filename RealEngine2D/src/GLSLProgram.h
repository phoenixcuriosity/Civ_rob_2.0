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

#ifndef GLSLProgram_H
#define GLSLProgram_H

#include <string>
#include <SDL\glew.h>

namespace RealEngine2D
{
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

	private:


	public:

		void compileShaders
		(
			const std::string& filePathColorShadingVert,
			const std::string& filePathColorShadingFrag
		);

		void linkShaders();

		void addAttribut(const std::string& name);

		GLuint getUnitformLocation(const std::string& uniformName);

		void use();

		void unuse();

	private:

		void getFileCompile
		(
			const std::string& filePath,
			GLuint id
		);

	private:
		int _numAttribut;

		GLuint _programID;
		GLuint _vertexID;
		GLuint _fragID;

	};
}

#endif // !GLSLProgram_H