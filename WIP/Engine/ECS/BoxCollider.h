#pragma once

#include "IComponent.h"

#include "Collision/ICollision.h"

namespace jci {

struct BoxCollisionProps
{
	BoxCollisionProps() = default;
};

enum class BodyType
{
	Static,
	Kinematic
};

class BoxCollider : public IComponent
{
public:
	REGISTER_COMPONENT(ComponentTypes::BoxCollider);

	void OnComponentAdd(Entity* entity) final;
	void OnComponentRemove() final;

	void CollisionOccured(Entity* otherEntity);
	void CollisionExit();

	// Accessors.
	inline vec2 GetSize() const { return m_size; }
	inline BodyType GetBodyType() const { return m_bodyType; }
	inline bool IsTrigger() const { return m_trigger; }

	// Mutators.
	inline void SetSize(vec2 size) { m_size = size; }
	inline void SetTrigger(bool trigger) { m_trigger = trigger; }
	void SetBodyType(BodyType type);

	inline void SetCollisionMethods(ICollision* collisionMethods)	{ m_collisionMethods = collisionMethods; }
	inline void SetTriggerMethods(ITrigger* triggerMethods)			{ m_triggerMethods = triggerMethods; }

	inline BoxCollider& operator=(BoxCollider& other) noexcept
	{
		m_id = std::move(other.m_id);
		m_entity = std::move(other.m_entity);
		m_size = std::move(other.m_size);
		m_bodyType = std::move(other.m_bodyType);
		m_trigger = other.m_trigger;

		m_collisionOccured = other.m_collisionOccured;
		m_collisionMethods = std::move(other.m_collisionMethods);
		m_triggerMethods = std::move(other.m_triggerMethods);

		return *this;
	}
private:
	Entity*		m_entity	= nullptr;
	entId		m_id		= invalid_id;

	vec2		m_size		= vec2(1.0f);
	BodyType	m_bodyType	= BodyType::Static;
	bool		m_trigger	= false;

	bool		m_collisionOccured	= false;
	ICollision*	m_collisionMethods	= nullptr;
	ITrigger*	m_triggerMethods	= nullptr;
};

} // Namespace jci.