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

#include "Window.h"
#include "Error.h"

#include <SDL\glew.h>

using namespace RealEngine2D;

Window::Window()
: _sdlWindow(nullptr), _screenWidth(0), _screenHeight(0)
{
}

Window::~Window()
{
	SDL_DestroyWindow(_sdlWindow);
	_sdlWindow = nullptr;
}

int Window::create
(
	const std::string& name,
	int screenWidth,
	int screenHeight,
	unsigned int currentFlags
)
{
	Uint32 flags = SDL_WINDOW_OPENGL;

	if (currentFlags & INVISIBLE)
	{
		flags |= SDL_WINDOW_HIDDEN;
	}
	if (currentFlags & FULLSCREEN)
	{
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (currentFlags & BORDERLESS)
	{
		flags |= SDL_WINDOW_BORDERLESS;
	}

	_sdlWindow = SDL_CreateWindow(name.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			screenWidth, screenHeight,
			SDL_WINDOW_OPENGL);

	if (nullptr == _sdlWindow)
	{
		fatalError("[ERROR]___: CreateWindow Failed");
		return false;
	}
	else
	{
		

		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);

		if (nullptr == glContext)
		{
			fatalError("[ERROR]___: glContext Failed");
			return false;
		}
		

		GLenum error = glewInit();
		if (GLEW_OK != error)
		{
			fatalError("[ERROR]___: GLenum Failed");
		}


		/* vsync OFF */
		SDL_GL_SetSwapInterval(0);

		// enable alpha
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}
	return 0;
}

void  Window::swap()
{
	SDL_GL_SwapWindow(_sdlWindow);
}