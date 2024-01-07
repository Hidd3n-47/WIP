/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#include "pch.h"
#include "AudioManager.h"

namespace jci {

AudioManager* AudioManager::m_pInstance = nullptr;

void AudioManager::Init()
{
	if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) == 0)
	{
		Log::FatalError("Failed to initialize SDL Mixer.\nSDL_Error: ", ERR_CODE::SDL_ERROR);
	}

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

void AudioManager::Destroy()
{
	for (auto it = m_music.begin(); it != m_music.end(); ++it)
	{
		Mix_FreeMusic(it->second);
	}

	for (auto it = m_sounds.begin(); it != m_sounds.end(); ++it)
	{
		Mix_FreeChunk(it->second);
	}

	Mix_Quit();

	delete m_pInstance;
}

uint32 AudioManager::LoadSound(const std::string& filePath)
{
	ASSERT(m_soundId <= (1 << 32) - 1, "Reached maximum number of Sound Effects.");

	m_sounds[m_soundId] = Mix_LoadWAV(filePath.c_str());

	if (m_sounds[m_soundId] == nullptr)
	{
		Log::FatalError("Failed to load WAV file at: " + filePath, ERR_CODE::SDL_ERROR);
	}

	return m_soundId++;
}

uint32 AudioManager::LoadSound(const std::string& filePath, int volume)
{
	ASSERT(m_soundId <= (1 << 32) - 1, "Reached maximum number of Music Tracks.");

	Uint16 id = LoadSound(filePath);

	m_sounds[id]->volume = volume;
	return id;
}

uint32 AudioManager::LoadMusic(const std::string& filePath)
{
	m_music[m_musicId] = Mix_LoadMUS(filePath.c_str());

	if (m_music[m_musicId] == nullptr)
	{
		Log::FatalError("Failed to load Mp3 file at: " + filePath, ERR_CODE::SDL_ERROR);
	}

	return m_musicId++;
}

uint32 AudioManager::LoadMusic(const std::string& filePath, int volume)
{
	Uint16 id = LoadMusic(filePath);

	SetMusicVolume(id, volume);
	return id;
}

void AudioManager::PlaySound(uint32 soundId)
{
	if (Mix_PlayChannel(-1, m_sounds[soundId], 0) == -1)
	{
		Log::FatalError("Failed to play sound effect with ID: " + std::to_string(soundId), ERR_CODE::SDL_ERROR);
	}
}

void AudioManager::PlayMusic(uint32 musicId)
{
		if (Mix_PlayMusic(m_music[musicId], -1) == -1)
		{
			Log::FatalError("Failed to play music with ID: " + std::to_string(musicId), ERR_CODE::SDL_ERROR);
		}
		else if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
		}
		m_currentPlayingMusicId = musicId;
}

void AudioManager::PauseMusic(uint32 musicId)
{
	if (Mix_PlayingMusic())
	{
		if (musicId != m_currentPlayingMusicId)
		{
			DLOG("Cannot pause track since that is not the music track playing.");
			return;
		}

		Mix_PauseMusic();
	}
}

void AudioManager::DestroySound(uint32 soundId)
{
	Mix_FreeChunk(m_sounds[soundId]);

	m_sounds.erase(soundId);
}

void AudioManager::DestroyMusic(uint32 musicId)
{
	Mix_FreeMusic(m_music[musicId]);

	m_music.erase(musicId);
}

} // Namespace jci.