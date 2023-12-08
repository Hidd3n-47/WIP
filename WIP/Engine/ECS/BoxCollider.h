#pragma once

#include "IComponent.h"

#include "Collision/ICollision.h"

namespace jci {

enum class BodyType
{
	Static,
	Kinematic
};

class BoxCollider : public IComponent
{
public:
	void OnComponentAdd(Entity* entity) final;
	void OnComponentRemove() final;

	virtual Entity* GetEntity() final { return m_entity; }

	void CollisionOccured(Entity* otherEntity);
	void CollisionExit();

	COMPONENT(ComponentTypes::BoxCollider);

	// Accessors.
	inline vec2 GetSize() const { return m_size; }
	inline BodyType GetBodyType() const { m_bodyType; }

	// Mutators.
	inline void SetSize(vec2 size) { m_size = size; }
	void SetBodyType(BodyType type);

	inline void SetCollisionMethods(ICollision* collisionMethods)	{ m_collisionMethods = collisionMethods; }
	inline void SetTriggerMethods(ITrigger* triggerMethods)			{ m_triggerMethods = triggerMethods; }
private:
	Entity*		m_entity	= nullptr;
	vec2		m_size		= vec2(1.0f);
	BodyType	m_bodyType	= BodyType::Static;
	bool		m_trigger	= false;

	bool		m_collisionOccured	= false;
	ICollision*	m_collisionMethods	= nullptr;
	ITrigger*	m_triggerMethods	= nullptr;
};

} // Namespace jci.