/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.14.4
	file version : 1.4

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

public:

	void zoom();
	void deZoom();

public:

	bool isLockMoveUP() { return m_lockMove.lockMoveUP; }
	bool isLockMoveDOWN() { return m_lockMove.lockMoveDOWN; }
	bool isLockMoveLEFT() { return m_lockMove.lockMoveLEFT; }
	bool isLockMoveRIGHT() { return m_lockMove.lockMoveRIGHT; }

	void lockMoveUP() { m_lockMove.lockMoveUP = true; }
	void lockMoveDOWN() { m_lockMove.lockMoveDOWN = true; }
	void lockMoveLEFT() { m_lockMove.lockMoveLEFT = true; }
	void lockMoveRIGHT() { m_lockMove.lockMoveRIGHT = true; }

	void unlockMoveUP() { m_lockMove.lockMoveUP = false; }
	void unlockMoveDOWN() { m_lockMove.lockMoveDOWN = false; }
	void unlockMoveLEFT() { m_lockMove.lockMoveLEFT = false; }
	void unlockMoveRIGHT() { m_lockMove.lockMoveRIGHT = false; }

public:

	void SETposition(const glm::vec2& newPosition) { m_position = newPosition; m_needMatixUpdate = true; };
	void SETscale(float scale) { m_scale = scale; m_needMatixUpdate = true;};
	void SETmaxScale(float max) { m_maxScale = max; }
	void SETminScale(float min) { m_minScale = min; }

	glm::vec2& GETposition() { return m_position; };
	glm::mat4& GETcameraMatrix() { return m_cameraMatrix; };
	float GETscale() { return m_scale; };
	float GETscaleRate() { return m_scaleRate; };
	float getOffsetByZoomX() { return m_offsetByZoomX; }
	float getOffsetByZoomY() { return m_offsetByZoomY; }

	int getScreenWidth()const { return m_screenWidth; }
	int getScreenHeight()const { return m_screenHeight; }

private:

	/* Screen Width : default = 1280 */
	int m_screenWidth;

	/* Screen Width : default = 720 */
	int m_screenHeight;

	/* if position change : need to update */
	bool m_needMatixUpdate;

	/* Scale of the Camera : Zoom */
	float m_scale;

	/* Rate of zoom and deZoom, default : 1.25f */
	float m_scaleRate;
	
	/* max camera Zoom */
	float m_maxScale;

	/* max camera DeZoom */
	float m_minScale;

	int m_zoomLevel;

	float m_offsetByZoomX;
	float m_offsetByZoomY;

	/* Center position of Camera */
	glm::vec2 m_position;

	glm::mat4 m_orthoMatrix;
	glm::mat4 m_cameraMatrix;

	/* move rate of camera, default : 2.0f */
	float m_moveRate;

	struct LockMove
	{
		bool lockMoveUP;
		bool lockMoveDOWN;
		bool lockMoveLEFT;
		bool lockMoveRIGHT;
	} m_lockMove;
};

}

#endif /* Camera2D_H */
