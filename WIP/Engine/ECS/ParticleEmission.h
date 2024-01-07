#pragma once

#include "IComponent.h"

#include "ParticleSystem/ParticleManager.h"

namespace jci {

/***
=========================================================================================
PARTICLE_EMISSION (COMPONENT):
	A component which can be used to create a particle system.
	The particles created follow the behavious created in ParticleProperties.
=========================================================================================
*/
class ParticleEmission : public IComponent
{
public:
	REGISTER_COMPONENT(ComponentTypes::ParticleEmission);

	void OnComponentAdd(Entity* entity) final { m_entity = entity;}
	void OnComponentRemove() final { }

	/***
	* Emit will emit the particles based off of the particle properties.
	*
	*/
	void Emit() { ParticleManager::Instance()->Emit(m_properties); }
	
	/***
	* Get a reference to the particle properties.
	*
	*/
	inline ParticleProperties& GetProperties() { return m_properties; }

	/***
	* Set the particle emission position.
	*
	*/
	inline void SetParticlePosition(vec2 position) { m_properties.position = position; }
	/***
	* Set the particle emission direction.
	*
	*/
	inline void SetParticleDirection(vec2 direction) { m_properties.direction = direction; }
	/***
	* Set the properties of the particle emission.
	*
	*/
	inline void SetProperties(ParticleProperties& properties) { m_properties = properties; }

	inline ParticleEmission& operator=(ParticleEmission& other) noexcept
	{
		memcpy(this, &other, sizeof(ParticleEmission));

		return *this;
	}
private:
	Entity* m_entity	= nullptr;
	entId	m_id		= invalid_id;
	ParticleProperties	m_properties;
};

} // Namespace jci.