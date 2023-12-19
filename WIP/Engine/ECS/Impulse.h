#pragma once
#include "pch.h"

#include "IComponent.h"

namespace jci {

class Impulse : public IComponent
{
	friend class PhysicsManager;
public:
	REGISTER_COMPONENT(ComponentTypes::Impulse);

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; }
	inline void OnComponentRemove() final { /* Empty. */ }

	// Accessors.
	inline vec2 GetVelocity() const { return m_velocity; }
	inline float GetAcceleration() const { return m_dampening; }

	// Mutators.
	inline void ImpulseEntity(vec2 impulse) { m_velocity = impulse; m_dampening = m_maxDapening; }
	inline void SetDampening(float dampening) { m_maxDapening = dampening; }
	inline void SetDampeningFactor(float dampeningFactor) { m_dampeningFactor = dampeningFactor; }


	inline Impulse& operator=(Impulse& other) noexcept
	{
		m_id = std::move(other.m_id);
		m_entity = std::move(other.m_entity);
		m_velocity = std::move(other.m_velocity);
		m_dampening = std::move(other.m_dampening);
		m_dampeningFactor = std::move(other.m_dampeningFactor);

		return *this;
	}
private:
	Entity* m_entity;
	entId m_id;

	vec2 m_velocity = vec2(0.0f);
	float m_maxDapening = 5.0f;
	float m_dampening = 0.0f;
	float m_dampeningFactor = 0.1f;
};

}