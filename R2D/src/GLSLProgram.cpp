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

#include "GLSLProgram.h"

#include "RealEngineError.h"

#include <fstream>

using namespace R2D;

GLSLProgram::GLSLProgram()
: m_numAttribut(0), m_programID(0), m_vertexID(0), m_fragID(0)
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
	m_programID = glCreateProgram();

	m_vertexID = glCreateShader(GL_VERTEX_SHADER);
	if (m_vertexID == 0)
	{
		fatalError("[ERROR]___: compileShaders : m_vertexID == 0 ");
	}

	m_fragID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_fragID == 0)
	{
		fatalError("[ERROR]___: compileShaders : m_fragID == 0 ");
	}

	getFileCompile(filePathColorShadingVert, m_vertexID);
	getFileCompile(filePathColorShadingFrag, m_fragID);


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
		fatalError("[ERROR]___: compileShaders :" + filePath);
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
		std::vector<GLchar> errorLog((size_t)maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		line = "";

		for (unsigned int i(0); i < errorLog.size(); i++)
		{
			line += errorLog[i];
		}


		fatalError("[ERROR]___: compileShaders : compile failed" + filePath + " gg : " + line);


		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.
		return;
	}
}

void GLSLProgram::linkShaders()
{
	

	glAttachShader(m_programID, m_vertexID);
	glAttachShader(m_programID, m_fragID);

	glLinkProgram(m_programID);

	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog((size_t)maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_programID);
		// Don't leak shaders either.
		glDeleteShader(m_vertexID);
		glDeleteShader(m_fragID);

		fatalError("[ERROR]___: linkShaders : compile failed ");

		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(m_programID, m_vertexID);
	glDetachShader(m_programID, m_fragID);
	glDeleteShader(m_vertexID);
	glDeleteShader(m_fragID);
}

void GLSLProgram::addAttribut(const std::string& name)
{
	glBindAttribLocation( m_programID, m_numAttribut++, name.c_str());
}

GLint GLSLProgram::getUnitformLocation(const std::string& uniformName)
{
	GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		fatalError("[ERROR]___: getUnitformLocation : location == GL_INVALID_INDEX");
	}
	return location;
}

void GLSLProgram::use()
{
	glUseProgram(m_programID);
	for (GLuint i(0); i < m_numAttribut; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse()
{
	glUseProgram(0);
	for (GLuint i(0); i < m_numAttribut; i++)
	{
		glDisableVertexAttribArray(i);
	}
}