/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.3.0
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

#include "AudioEngine.h"

#include "RealEngineError.h"

namespace RealEngine2D
{

void SoundEffect::play(int loop /* = 0*/)
{
	if (Mix_PlayChannel(-1, m_chunk, loop))
	{
		if (Mix_PlayChannel(0, m_chunk, loop))
		{
			fatalError("Mix_Init error : play : " + std::string(Mix_GetError()));
		}
	}
}

void Music::play(int loop /* = 1*/)
{
	if (Mix_PlayMusic(m_music, loop))
	{
		fatalError("Mix_Init error : play : " + std::string(Mix_GetError()));
	}
}

void Music::pause()
{
	Mix_PauseMusic();
}

void Music::resume()
{
	Mix_ResumeMusic();
}

void Music::stop()
{
	Mix_HaltMusic();
}






AudioEngine::AudioEngine()
{

}
AudioEngine::~AudioEngine()
{
	destroy();
}

void AudioEngine::init()
{
	/* MIX_INIT_FLAC MIX_INIT_MOD MIX_INIT_MP3 MIX_INIT_OGG */
	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1)
	{
		fatalError("Mix_Init error : " + std::string(Mix_GetError()));
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		fatalError("Mix_Init error : " + std::string(Mix_GetError()));
	}
	m_isInit = true;
}

void AudioEngine::destroy()
{
	if (m_isInit)
	{
		m_isInit = false;

		for (auto& it : m_effectMap)
		{
			Mix_FreeChunk(it.second);
		}
		for (auto& it : m_musicMap)
		{
			Mix_FreeMusic(it.second);
		}
		m_effectMap.clear();
		m_musicMap.clear();

		Mix_CloseAudio();
		Mix_Quit();
	}
}


SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath)
{
	SoundEffect soundEffect;

	auto it = m_effectMap.find(filePath);
	if (it == m_effectMap.end())
	{
		Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
		if (nullptr == chunk)
		{
			//fatalError("Mix_Init error : " + filePath);
		}
		soundEffect.m_chunk = chunk;

		m_effectMap[filePath] = chunk;
	}
	else
	{
		soundEffect.m_chunk = it->second;
	}
	return soundEffect;
}

Music AudioEngine::loadMusic(const std::string& filePath)
{
	Music music;

	auto it = m_musicMap.find(filePath);
	if (it == m_musicMap.end())
	{
		Mix_Music* musicL = Mix_LoadMUS(filePath.c_str());
		if (nullptr == musicL)
		{
			fatalError("Mix_Init error : " + filePath);
		}
		music.m_music = musicL;

		m_musicMap[filePath] = musicL;
	}
	else
	{
		music.m_music = it->second;
	}
	return music;
}

}