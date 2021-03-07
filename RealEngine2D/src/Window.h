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

#ifndef Window_H
#define Window_H

#include <SDL\SDL.h>
#include <string>

namespace RealEngine2D
{

	enum WindowFlags
	{
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};

	class Window
	{
	public:
		Window();
		~Window();

		int create
		(
			const std::string& name,
			int screenWidth,
			int screenHeight,
			unsigned int currentFlags
		);

		void swap();

		int GETscreenWidth() { return _screenWidth; };
		int GETscreenHeight() { return _screenHeight; };

		int SETscreenWidth(int screenWidth) { _screenWidth = screenWidth; };
		int SETscreenHeight(int screenHeight) { _screenHeight = screenHeight; };

	private:

		SDL_Window* _sdlWindow;
		int _screenWidth = 0;
		int _screenHeight = 0;
	};

}

#endif // !Window_H

