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

#include "Camera2D.h"

using namespace R2D;

Camera2D::Camera2D()
: 
m_screenWidth(1280),
m_screenHeight(720),
m_needMatixUpdate(true),
m_scale(1.0f),
m_scaleRate(1.25f),
m_maxScale(0.0f),
m_minScale(0.0f),
m_position(0.0f, 0.0f),
m_orthoMatrix(1),
m_cameraMatrix(1.0f),
m_moveRate(2.0f),
m_lockMove({false, false, false, false})
{

}
Camera2D::~Camera2D()
{

}

void Camera2D::init(int screenWidth, int screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
}

void Camera2D::update()
{
	if (m_needMatixUpdate)
	{
		glm::vec3 translate
		(-m_position.x + ((float)m_screenWidth / 2.0f), -m_position.y + ((float)m_screenHeight / 2.0f), 0.0f);
		m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

		glm::vec3 scale(m_scale, m_scale, 0.0f);
		m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
		m_needMatixUpdate = false;
	}
}

glm::vec2 Camera2D::convertScreenToMap(glm::vec2 screenPos)
{
	/*invert y*/
	screenPos.y = (float)m_screenHeight - screenPos.y;

	/* center pos 0,0 to middle */
	screenPos -= glm::vec2((float)m_screenWidth/2.0f, (float)m_screenHeight/2.0f);

	/* scale */
	screenPos /= m_scale;

	/* translation */
	screenPos += m_position;

	return screenPos;
}

bool Camera2D::isBoxInView
(
	const glm::vec2& position,
	const glm::vec2& dim,
	unsigned int toolBarSize
)
{
	glm::vec2 scaledDim
	(
		(float)((float)m_screenWidth - (float)toolBarSize) / m_scale,
		(float)m_screenHeight / m_scale
	);

	const float MIN_DISTANCE_X(dim.x / 2.0f + scaledDim.x / 2.0f);
	const float MIN_DISTANCE_Y(dim.y / 2.0f + scaledDim.y / 2.0f);

	glm::vec2 centerPos(position + dim / 2.0f);

	glm::vec2 io(m_position.x + ((float)toolBarSize/ m_scale), m_position.y);

	glm::vec2 distVect(centerPos - io);

	float xDepth(MIN_DISTANCE_X - abs(distVect.x));
	float yDepth(MIN_DISTANCE_Y - abs(distVect.y));


	if (xDepth > 0.0f && yDepth > 0.0f)
	{
		return true;
	}
	return false;
}

void Camera2D::zoom()
{
	if (m_scale < m_maxScale)
	{
		/* New Scale */
		m_scale *= m_scaleRate;

		/* Need to update matrix */
		m_needMatixUpdate = true;
	}
}

void Camera2D::deZoom()
{
	if (m_scale > m_minScale)
	{
		/* New Scale */
		m_scale /= m_scaleRate;
		
		/* Need to update matrix */
		m_needMatixUpdate = true;
	}
}