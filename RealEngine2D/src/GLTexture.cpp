/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.3.0
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

#include "GLTexture.h"
#include <iostream>
#include <fstream>
#include <picopng\picoPNG.h>

#include "RealEngineError.h"

using namespace RealEngine2D;

GLTexture::GLTexture(const std::string& filePath)
{
	init(filePath);
}

GLTexture::~GLTexture()
{

}

void GLTexture::init(const std::string& filePath)
{
	std::vector<unsigned char> bufferFromFile;
	std::vector<unsigned char> bufferFromDecode;

	readFileToBuffer(filePath, bufferFromFile);

	int result = decodePNG(bufferFromDecode, m_width, m_height, &(bufferFromFile[0]), bufferFromFile.size());
	if (result != 0)
	{
		fatalError("[ERROR]___: init : decodePNG fail");
	}

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)m_width, (GLsizei)m_height, (GLint)0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)&(bufferFromDecode[0]));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

bool GLTexture::readFileToBuffer
(
	const std::string& filePath,
	std::vector<unsigned char>& buffer
)
{
	std::ifstream file(filePath, std::ios::binary);

	if (file.fail())
	{
		fatalError("[ERROR]___: readFileToBuffer : " + filePath + " fail");
		return false;
	}

	file.seekg(0, std::ios::end);
	std::streampos fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	fileSize -= file.tellg();
	buffer.resize((size_t)fileSize);
	file.read((char*)&(buffer[0]), fileSize);

	return true;
}