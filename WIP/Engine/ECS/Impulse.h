/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once
#include "pch.h"

#include "IComponent.h"

namespace jci {

/***
=========================================================================================
IMPULSE (COMPONENT):
	Used to impusle the entity in a certain direction.
=========================================================================================
*/
class Impulse : public IComponent
{
	friend class PhysicsManager;
public:
	REGISTER_COMPONENT(ComponentTypes::Impulse);

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; }
	inline void OnComponentRemove() final { /* Empty. */ }

	// Accessors.
	/***
	* Get the velocity of the entity.
	* 
	*/
	inline vec2 GetVelocity() const { return m_velocity; }
	/***
	* Get the Acceleration of the object.
	* Note Acceleration should be negative.
	*/
	inline float GetAcceleration() const { return m_acceleration; }

	// Mutators.
	/***
	* Impulse the entity in the given direction.
	* Note direction should be normalised.
	*/
	inline void ImpulseEntity(vec2 impulse) { m_velocity = impulse; m_acceleration = m_maxAcceleration; }
	/***
	* Set the acceleration of the object.
	* Note acceleration should be negative.
	*/
	inline void SetAcceleration(float dampening) { m_maxAcceleration = dampening; }
	/***
	* Set the amount that the acceleration will change per frame.
	* This will make the acceleration dissepate over time and hence the entity not be impulsed forever.
	*/
	inline void SetAccelerationDecreasingFactor(float dampeningFactor) { m_dampeningFactor = dampeningFactor; }


	inline Impulse& operator=(Impulse& other) noexcept
	{
		memcpy(this, &other, sizeof(Impulse));

		return *this;
	}
private:
	Entity* m_entity = nullptr;
	entId m_id = invalid_id;

	vec2 m_velocity			= vec2(0.0f);
	float m_maxAcceleration = 5.0f;
	float m_acceleration	= 0.0f;
	float m_dampeningFactor = 0.1f;
};

}