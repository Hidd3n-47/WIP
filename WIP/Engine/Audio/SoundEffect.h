#pragma once
#include "pch.h"

#include "Audio/AudioManager.h"

namespace jci {

/***
=========================================================================================
SOUND_EFFECT:
	Sound effects for the game.
	Loads a sound effect from file path and handles volume, loading and destruction.
=========================================================================================
*/
class SoundEffect
{
public:
	/***
	* Create a sound effect that can be played at any time.
	* Paramater: file path of sound effect.
	*/
	SoundEffect(const std::string& filePath) { m_soundId = AudioManager::Instance()->LoadSound(filePath); }
	/***
	* Create a sound effect that can be played at any time.
	* Paramater: file path of sound effect, volume for how lound the audio is where 0 <= volume <= 128.
	*/
	SoundEffect(const std::string& filePath, int volume) : m_volume(volume) { m_soundId = AudioManager::Instance()->LoadSound(filePath, volume); }

	~SoundEffect() { AudioManager::Instance()->DestroySound(m_soundId); }

	/***
	* Play the sound effect.
	* 
	*/
	inline void Play() { AudioManager::Instance()->PlaySound(m_soundId); }

	// Accessors.
	/***
	* Get the volume of the sound effect.
	* Volume is an integer between 0 and 128, 0 being no sound, 128 being loudest.
	*/
	inline int GetVolume() const { return m_volume; }

	// Mutators.
	/***
	* Set the volume of the sound effect.
	* Volume is an integer between 0 and 128, 0 being no sound, 128 being loudest.
	*/
	inline void SetVolume(int volume) { m_volume = volume; AudioManager::Instance()->SetSoundVolume(m_soundId, m_volume); }
private:
	uint32	m_soundId	= 0;
	uint8	m_volume	= 128;
};

} // Namespace jci.