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

#ifndef Timing_H
#define Timing_H

#include <SDL/SDL.h>

#include <ratio>

namespace R2D
{

class FpsLimiter
{
public:
	FpsLimiter() : m_fps(0.0f), m_maxFPS(0.0f), m_frameTime(0), m_startTicks(0) {};

	void init(const float maxFps);

	void setMaxFPS(const float maxFps);

	void begin();

	float end();

private:

	void calculateFPS();

private:
	static constexpr int NUM_SAMPLES = 10;
	static constexpr float COEF = 1000.f;
private:
	float m_fps;
	float m_maxFPS;
	Uint32 m_frameTime;

	unsigned int m_startTicks;
};

}

#endif
