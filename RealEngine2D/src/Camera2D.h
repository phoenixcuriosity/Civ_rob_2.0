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

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#ifndef Camera2D_H
#define Camera2D_H

namespace RealEngine2D
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight);

		void update();

		glm::vec2 convertScreenToMap(glm::vec2 screenPos);

		bool isBoxInView
		(
			const glm::vec2& position,
			const glm::vec2& dim,
			unsigned int toolBarSize
		);

		void SETposition(const glm::vec2& newPosition) { m_position = newPosition; m_needMatixUpdate = true; };
		void SETscale(float scale) { m_scale = scale; m_needMatixUpdate = true;};

		glm::vec2& GETposition() { return m_position; };
		glm::mat4& GETcameraMatrix() { return m_cameraMatrix; };
		float GETscale() { return m_scale; };

	private:

		/* Screen Width : default = 1280 */
		int m_screenWidth = 1280;

		/* Screen Width : default = 720 */
		int m_screenHeight = 720;

		/* if position change : need to update */
		bool m_needMatixUpdate = true;

		/* Scale of the Camera : Zoom */
		float m_scale = 1.0f;

		/* Center position of Camera */
		glm::vec2 m_position;

		glm::mat4 m_orthoMatrix;
		glm::mat4 m_cameraMatrix;
	};
}

#endif /* Camera2D_H */
