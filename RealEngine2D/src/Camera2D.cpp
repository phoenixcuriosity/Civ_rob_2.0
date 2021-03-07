/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.2.0
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

#include "Camera2D.h"

using namespace RealEngine2D;

Camera2D::Camera2D()
: _screenWidth(NULL), _screenHeight(NULL),
_needMatixUpdate(true), _scale(1.0f), _position(0.0f, 0.0f),
_cameraMatrix(1.0f), _orthoMatrix(1)
{

}
Camera2D::~Camera2D()
{

}

void Camera2D::init(int screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
}

void Camera2D::update()
{
	if (_needMatixUpdate)
	{
		glm::vec3 translate
		(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
		_cameraMatrix = glm::translate(_orthoMatrix, translate);

		glm::vec3 scale(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
		_needMatixUpdate = false;
	}
}

glm::vec2 Camera2D::convertScreenToMap(glm::vec2 screenPos)
{
	/*invert y*/
	screenPos.y = _screenHeight - screenPos.y;

	/* center pos 0,0 to middle */
	screenPos -= glm::vec2(_screenWidth/2, _screenHeight/2);

	/* scale */
	screenPos /= _scale;

	/* translation */
	screenPos += _position;

	return screenPos;
}
