#pragma once
#include "pch.h"

#include "IComponent.h"
#include "Audio/AudioManager.h"
#include "Audio/SoundEffect.h"

namespace jci {

class Audio : public IComponent
{
public:
	REGISTER_COMPONENT(ComponentTypes::Audio);

	Audio() = default;
	~Audio() = default;

	inline virtual void OnComponentAdd(Entity* entity)	final { m_entity = entity; }
	inline virtual void OnComponentRemove()				final { /* Empty. */ }
	/***
	* Play the sound effect attached to component.
	* 
	*/
	inline void PlaySound() const { AudioManager::Instance()->PlaySound(m_sound); }
	/***
	* Play the music attached to component.
	*
	*/
	inline void PlayMusic() const { AudioManager::Instance()->PlayMusic(m_music); }


	// Accessors.
	/***
	* Get the sound effect attached to the component.
	*
	*/
	inline uint32 GetSoundEffectId() const { return m_sound; }

	// Mutators.
	/***
	* Set the sound effect of the component.
	*
	*/
	inline void SetSoundEffect(uint32 soundEffect) { m_sound = soundEffect; }
	/***
	* Set the sound effect of the component.
	* Volume is between 0 - 128, with 128 being the louded.
	*/
	inline void SetSoundEffect(const std::string& filePath, int volume = 128) { m_sound = AudioManager::Instance()->LoadSound(filePath, volume); }
	/***
	* Set the music of the component.
	* Volume is between 0 - 128, with 128 being the louded.
	*/
	inline void SetMusic(const std::string& filePath, int volume = 128) { m_music = AudioManager::Instance()->LoadMusic(filePath, volume); }

	inline Audio& operator=(Audio& other) noexcept
	{
		/*m_id = std::move(other.m_id);
		m_entity = std::move(other.m_entity);
		m_sound = std::move(other.m_sound);

		return *this;*/
		memcpy(this, &other, sizeof(Audio));

		return *this;
	}
private:
	Entity*	m_entity = nullptr;
	entId	m_id = invalid_id;

	uint32	m_sound;
	uint32	m_music;
};

} // Namespace jci.