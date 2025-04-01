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

#include "Window.h"

#include <SDL\glew.h>
#include "RealEngineError.h"
#include "ValueToScale.h"

R2D::Window
::~Window()
{
	SDL_DestroyWindow(m_sdlWindow);
	m_sdlWindow = nullptr;
}

int
R2D::Window
::create(const std::string& name,
		 const int screenWidth,
		 const int screenHeight,
		 const unsigned int currentFlags)
{
	Uint32 flags = SDL_WINDOW_OPENGL;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

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

	m_sdlWindow = SDL_CreateWindow(name.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_screenWidth, m_screenHeight,
		SDL_WINDOW_OPENGL);

	if (nullptr == m_sdlWindow)
	{
		fatalError("[ERROR]___: CreateWindow Failed");
		return false;
	}
	else
	{


		SDL_GLContext glContext = SDL_GL_CreateContext(m_sdlWindow);

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

void
R2D::Window
::swap()
{
	SDL_GL_SwapWindow(m_sdlWindow);
}

double
R2D::Window
::getWidthPositionScaleToWindow(const double position2Scale)const
{
	return ValueToScale::computeValueToScale
	(
		position2Scale,
		WINDOW_SCALE_PERCENT_MIN,
		WINDOW_SCALE_PERCENT_MAX,
		WINDOW_SCALE_SCREEN_WIDTH_MIN,
		m_screenWidth
	);
}

double
R2D::Window
::getHeightPositionScaleToWindow(const double position2Scale)const
{
	return ValueToScale::computeValueToScale
	(
		position2Scale,
		WINDOW_SCALE_PERCENT_MIN,
		WINDOW_SCALE_PERCENT_MAX,
		WINDOW_SCALE_SCREEN_HEIGHT_MIN,
		m_screenHeight
	);
}

Uint16
R2D::Window
::getHorizontal()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	return (Uint16)desktop.right;
}

Uint16
R2D::Window
::getVertical()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	return (Uint16)desktop.bottom;
}