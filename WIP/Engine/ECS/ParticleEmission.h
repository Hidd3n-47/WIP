#pragma once

#include "IComponent.h"

#include "ParticleSystem/ParticleManager.h"

namespace jci {

class ParticleEmission : public IComponent
{
public:
	REGISTER_COMPONENT(ComponentTypes::ParticleEmission);

	void OnComponentAdd(Entity* entity) final { m_entity = entity;}
	void OnComponentRemove() final { }

	void Emit() { ParticleManager::Instance()->Emit(m_properties); }
	
	inline ParticleProperties& GetProperties() { return m_properties; }

	inline void SetParticlePosition(vec2 position) { m_properties.position = position; }
	inline void SetParticleDirection(vec2 direction) { m_properties.direction = direction; }
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