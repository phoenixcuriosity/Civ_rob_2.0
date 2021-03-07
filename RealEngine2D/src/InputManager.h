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

#ifndef InputManager_H
#define InputManager_H

#include <unordered_map>
#include <glm/glm.hpp>
#include <SDL/SDL.h>

namespace RealEngine2D
{
class InputManager
{
public:
	InputManager();
	~InputManager();

	void update();

	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);

	bool isKeyDown(unsigned int keyID);

	bool isKeyPressed(unsigned int keyID);

	void setMouseCoords
	(
		Sint32 x,
		Sint32 y
	);


	glm::vec2 GETmouseCoords()const { return _mouseCoords; }

private:

	bool wasKeyDown(unsigned int keyID);

private:
	std::unordered_map<unsigned int, bool> _keyMap;
	std::unordered_map<unsigned int, bool> _previousKeyMap;
	glm::ivec2 _mouseCoords;
};
}

#endif // !InputManager_H
