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

#include "Timing.h"
#include <iostream>

void 
R2D::FpsLimiter
::init(const float maxFps)
{
	setMaxFPS(maxFps);
}

void 
R2D::FpsLimiter
::setMaxFPS(const float maxFps)
{
	m_maxFPS = maxFps;
}

void 
R2D::FpsLimiter
::begin()
{
	m_startTicks = SDL_GetTicks();
}

float 
R2D::FpsLimiter
::end()
{
	calculateFPS();

	Uint32 frameTicks(SDL_GetTicks() - m_startTicks);
	if ((COEF / m_maxFPS) > frameTicks)
	{
		SDL_Delay((Uint32)((COEF / m_maxFPS) - frameTicks));
	}

	return m_fps;
}

void 
R2D::FpsLimiter
::calculateFPS()
{
	static Uint32 frameTimes[NUM_SAMPLES];
	static int currentFrame(0);

	static Uint32 prevTicks(SDL_GetTicks());

	const Uint32 currentTicks(SDL_GetTicks());

	m_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

	prevTicks = currentTicks;

	unsigned int count(0);
	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage(0.0f);
	for (unsigned int i(0); i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;
	

	if (frameTimeAverage > 0.0f)
	{
		m_fps = COEF / frameTimeAverage;
	}
	else
	{
		m_fps = 10000.0f;
	}
}

