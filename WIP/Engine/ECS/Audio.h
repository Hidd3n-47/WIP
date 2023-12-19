#pragma once
#include "pch.h"

#include "IComponent.h"
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
	inline void PlaySound() const { ASSERT(m_sound, "Sound effect not loaded."); if(m_sound) m_sound->Play(); }

	// Accessors.
	/***
	* Get the sound effect attached to the component.
	*
	*/
	inline SoundEffect* GetSoundEffect() const { return m_sound; }

	// Mutators.
	/***
	* Set the sound effect of the component.
	*
	*/
	inline void SetSoundEffect(SoundEffect* soundEffect) { m_sound = soundEffect; }

	inline Audio& operator=(Audio& other) noexcept
	{
		m_id = std::move(other.m_id);
		m_entity = std::move(other.m_entity);
		m_sound = std::move(other.m_sound);

		return *this;
	}
private:
	Entity*			m_entity = nullptr;
	entId			m_id = invalid_id;

	SoundEffect*	m_sound = nullptr;
};

} // Namespace jci.