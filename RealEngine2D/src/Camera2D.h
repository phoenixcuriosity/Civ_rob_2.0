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

		void SETposition(const glm::vec2& newPosition) { _position = newPosition; _needMatixUpdate = true; };
		void SETscale(float scale) { _scale = scale; _needMatixUpdate = true;};

		glm::vec2& GETposition() { return _position; };
		glm::mat4& GETcameraMatrix() { return _cameraMatrix; };
		float GETscale() { return _scale; };

	private:
		int _screenWidth, _screenHeight;
		bool _needMatixUpdate;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _orthoMatrix;
		glm::mat4 _cameraMatrix;
	};
}

#endif /* Camera2D_H */
