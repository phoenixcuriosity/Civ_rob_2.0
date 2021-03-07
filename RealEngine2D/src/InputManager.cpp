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

#include "InputManager.h"

namespace RealEngine2D
{

InputManager::InputManager()
:_mouseCoords({0.0f, 0.0f})
{

}
InputManager::~InputManager()
{

}

void InputManager::update()
{
	for (auto& it : _keyMap)
	{
		_previousKeyMap[it.first] = it.second;
	}
}

void InputManager::pressKey
(
	unsigned int keyID
)
{
	_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID)
{
	_keyMap[keyID] = false;
}

bool InputManager::isKeyDown(unsigned int keyID)
{
	auto it = _keyMap.find(keyID);
	if (it != _keyMap.end())
	{
		return it->second;
	}
	return false;
}

bool InputManager::isKeyPressed(unsigned int keyID)
{
	if (isKeyDown(keyID) && !wasKeyDown(keyID))
	{
		return true;
	}
	return false;
}

void InputManager::setMouseCoords
(
	Sint32 x,
	Sint32 y
)
{
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}


bool InputManager::wasKeyDown(unsigned int keyID)
{
	auto it = _previousKeyMap.find(keyID);
	if (it != _previousKeyMap.end())
	{
		return it->second;
	}
	return false;
}

}

