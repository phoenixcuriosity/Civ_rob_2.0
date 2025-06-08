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
#pragma once

#include <map>
#include <string>

#include <SDL\glew.h>
#include <SDL/SDL_mixer.h>

namespace R2D
{

class Music
{
public:
	friend class AudioEngine;

	void play(int loop = 0);
public:
	static void pause();
	static void resume();
	static void stop();

private:
	Mix_Music* m_music = nullptr;
};

class SoundEffect
{
public:
	friend class AudioEngine;

	void play(int loop = 1);

private:
	Mix_Chunk* m_chunk = nullptr;
};



class AudioEngine
{
public:

	AudioEngine();
	~AudioEngine();

	void init();
	void destroy();

	SoundEffect loadSoundEffect(const std::string& filePath);
	Music loadMusic(const std::string& filePath);

private:
	bool m_isInit = false;
	std::map<std::string, Mix_Chunk*> m_effectMap;
	std::map<std::string, Mix_Music*> m_musicMap;
};

}
