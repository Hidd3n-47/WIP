/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once

#include "audio/SDL_mixer.h"

namespace jci {

/***
=========================================================================================
AUDIO:
	Deals with playing audio sound effects as well as music.
=========================================================================================
*/
class AudioManager
{
public:
	inline static AudioManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new AudioManager() : m_pInstance; }

	void Init();
	void Destroy();

	/***
	* Create a sound by passing in file path.
	*
	*/
	uint32 LoadSound(const std::string& filePath);
	/***
	* Create a sound by passing in file path and set the volume.
	* Volume is an integer between 0 and 128 with 0 being no audio and 128 being max volume.
	*/
	uint32 LoadSound(const std::string& filePath, int volume);
	/***
	* Create music track by passing in file path.
	* 
	*/
	uint32 LoadMusic(const std::string& filePath);
	/***
	* Create music track by passing in file path and set the volume.
	* Volume is an integer between 0 and 128 with 0 being no audio and 128 being max volume.
	*/
	uint32 LoadMusic(const std::string& filePath, int volume);

	/***
	* Play a given sound effect with passed in ID.
	*
	*/
	void PlaySound(uint32 soundId);
	/***
	* Play music track with passed in ID.
	*
	*/
	void PlayMusic(uint32 musicId);
	/***
	* Pause the current playing music track.
	*
	*/
	void PauseMusic(uint32 musicId);

	/***
	* Destroy a given sound effect with passed in ID.
	*
	*/
	void DestroySound(uint32 soundId);
	/***
	* Destroy music track with passed in ID.
	*
	*/
	void DestroyMusic(uint32 musicId);

	/***
	* Set the volume of given sound effect.
	* Volume is an integer between 0 and 128 with 0 being no audio and 128 being max volume.
	*/
	inline void SetSoundVolume(uint32 soundId, int volume) { m_sounds[soundId]->volume = volume; }
	/***
	* Set the volume of given music track.
	* Volume is an integer between 0 and 128 with 0 being no audio and 128 being max volume.
	*/
	inline void SetMusicVolume(uint32 musicId, int volume) { Mix_VolumeMusic(volume); }
private:
	AudioManager()	= default;
	~AudioManager()	= default;

	static AudioManager* m_pInstance;

	uint32 m_soundId = 0;
	uint32 m_musicId = 0;

	std::unordered_map<uint32, Mix_Chunk*> m_sounds;
	std::unordered_map<uint32, Mix_Music*> m_music;

	uint32 m_currentPlayingMusicId = -1;
};

} // Namespace jci.