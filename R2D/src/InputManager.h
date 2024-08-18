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

#ifndef InputManager_H
#define InputManager_H

#include "API_fwd.h"

#include <glm/glm.hpp>
#include <SDL/SDL.h>

namespace R2D
{
class InputManager
{
public:
	InputManager();
	~InputManager();

	void init(unsigned int* tileSize);

	void update();

	void pressKey(SDL_Keycode keyID);
	void releaseKey(SDL_Keycode keyID);

	bool isKeyDown(SDL_Keycode keyID);

	bool isKeyPressed(SDL_Keycode keyID);

	void setMouseCoords
	(
		Sint32 x,
		Sint32 y
	);


	glm::i32vec2 GETmouseCoords()const { return m_mouseCoords; }
	glm::i32vec2 GETmouseCoordsTile()const
	{ 
		return glm::i32vec2
		(
			std::floor((m_mouseCoords.x / *m_tileSize) * *m_tileSize),
			std::floor((m_mouseCoords.y / *m_tileSize) * *m_tileSize)
		);
	}

private:

	bool wasKeyDown(SDL_Keycode keyID);

private:
	std::unordered_map<SDL_Keycode, bool> m_keyMap;
	std::unordered_map<SDL_Keycode, bool> m_previousKeyMap;
	glm::i32vec2 m_mouseCoords;

	unsigned int* m_tileSize = nullptr;
};
}

#endif // !InputManager_H
