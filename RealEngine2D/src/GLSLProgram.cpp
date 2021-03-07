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

#include "GLSLProgram.h"
#include <fstream>
#include <vector>

using namespace RealEngine2D;

GLSLProgram::GLSLProgram()
: _numAttribut(0), _programID(0), _vertexID(0), _fragID(0)
{

}

GLSLProgram::~GLSLProgram()
{

}

void GLSLProgram::compileShaders
(
	const std::string& filePathColorShadingVert,
	const std::string& filePathColorShadingFrag
)
{
	_programID = glCreateProgram();

	_vertexID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexID == 0)
	{
		//MainGame::exitError("[ERROR]___: compileShaders : _vertexID == 0 ");
	}

	_fragID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragID == 0)
	{
		//MainGame::exitError("[ERROR]___: compileShaders : _fragID == 0 ");
	}

	getFileCompile(filePathColorShadingVert, _vertexID);
	getFileCompile(filePathColorShadingFrag, _fragID);


}

void GLSLProgram::getFileCompile
(
	const std::string& filePath,
	GLuint id
)
{
	std::ifstream vertexFile(filePath);
	if (vertexFile.fail())
	{
		//MainGame::exitError("[ERROR]___: compileShaders :" + filePath);
	}

	std::string fileContent("");
	std::string line("");

	while (std::getline(vertexFile, line))
	{
		fileContent += line + "\n";
	}

	vertexFile.close();

	const char* contentPtr = fileContent.c_str();
	glShaderSource(id, 1, &contentPtr, nullptr);

	glCompileShader(id);

	GLint result(0);
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		line = "";

		for (unsigned int i(0); i < errorLog.size(); i++)
		{
			line += errorLog[i];
		}


		//MainGame::exitError("[ERROR]___: compileShaders : compile failed" + filePath + " gg : " + line);


		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.
		return;
	}
}

void GLSLProgram::linkShaders()
{
	

	glAttachShader(_programID, _vertexID);
	glAttachShader(_programID, _fragID);

	glLinkProgram(_programID);

	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(_programID);
		// Don't leak shaders either.
		glDeleteShader(_vertexID);
		glDeleteShader(_fragID);

		//MainGame::exitError("[ERROR]___: linkShaders : compile failed ");

		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexID);
	glDetachShader(_programID, _fragID);
	glDeleteShader(_vertexID);
	glDeleteShader(_fragID);
}

void GLSLProgram::addAttribut(const std::string& name)
{
	glBindAttribLocation( _programID, _numAttribut++, name.c_str());
}

GLuint GLSLProgram::getUnitformLocation(const std::string& uniformName)
{
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		//MainGame::exitError("[ERROR]___: getUnitformLocation : location == GL_INVALID_INDEX");
	}
	return location;
}

void GLSLProgram::use()
{
	glUseProgram(_programID);
	for (int i(0); i < _numAttribut; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse()
{
	glUseProgram(0);
	for (int i(0); i < _numAttribut; i++)
	{
		glDisableVertexAttribArray(i);
	}
}