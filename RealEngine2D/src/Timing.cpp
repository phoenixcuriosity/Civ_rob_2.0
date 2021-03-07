/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.2.0
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

#include "Timing.h"
#include <iostream>

namespace RealEngine2D
{

	
FpsLimiter::FpsLimiter()
:_fps(0.0f), _maxFPS(0.0f), _frameTime(0), _startTicks(0)
{

}
FpsLimiter::~FpsLimiter()
{

}

void FpsLimiter::init
(
	float maxFps
)
{
	setMaxFPS(maxFps);
}
void FpsLimiter::setMaxFPS
(
	float maxFps
)
{
	_maxFPS = maxFps;
}

void FpsLimiter::begin()
{
	_startTicks = SDL_GetTicks();
}

float FpsLimiter::end()
{
	calculateFPS();

	
	Uint32 frameTicks(SDL_GetTicks() - _startTicks);
	if ((1000.0f / _maxFPS) > frameTicks)
	{
		SDL_Delay((Uint32)((1000.0f / _maxFPS) - frameTicks));
	}

	return _fps;
}

void FpsLimiter::calculateFPS()
{
	static const int NUM_SAMPLES(10);
	static Uint32 frameTimes[NUM_SAMPLES];
	static int currentFrame(0);

	static Uint32 prevTicks(SDL_GetTicks());

	Uint32 currentTicks(SDL_GetTicks());

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

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
		_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		_fps = 10000.0f;
	}
}


}

