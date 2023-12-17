#pragma once

#include "IComponent.h"
#include "Collision/BodyType.h"
#include "Collision/ICollision.h"

#ifdef _DEBUG
#include "Graphics/Renderer/RendererManager.h"
#endif

namespace jci {

class CircleCollider : public IComponent
{
public:
	REGISTER_COMPONENT(ComponentTypes::CircleCollider);

	void OnComponentAdd(Entity* entity) final;
	void OnComponentRemove() final;
   
	void CollisionOccured(Entity* otherEntity);
	void CollisionExit();

	// Accessors.
	inline float GetRadius() const { return m_radius; }
	inline BodyType GetBodyType() const { return m_bodyType; }
	inline bool IsTrigger() const { return m_trigger; }

	// Mutators.
	inline void SetRadius(float radius) { m_radius = radius; }
	inline void SetTrigger(bool trigger) { m_trigger = trigger; }
	inline void SetBodyType(BodyType type) { m_bodyType = type; }

	inline void SetCollisionMethods(ICollision* collisionMethods) { m_collisionMethods = collisionMethods; }
	inline void SetTriggerMethods(ITrigger* triggerMethods) { m_triggerMethods = triggerMethods; }

	inline CircleCollider& operator=(CircleCollider& other) noexcept
	{
		m_id = std::move(other.m_id);
		m_entity = std::move(other.m_entity);
		m_radius = std::move(other.m_radius);
		m_bodyType = std::move(other.m_bodyType);
		m_trigger = other.m_trigger;

		m_collisionOccured = other.m_collisionOccured;
		m_collisionMethods = std::move(other.m_collisionMethods);
		m_triggerMethods = std::move(other.m_triggerMethods);

		return *this;
	}
private:
	Entity*		m_entity = nullptr;
	entId		m_id = invalid_id;

	float		m_radius = 0.5f;
	BodyType	m_bodyType = BodyType::Static;
	bool		m_trigger = false;

	bool		m_collisionOccured = false;
	ICollision* m_collisionMethods = nullptr;
	ITrigger*	m_triggerMethods = nullptr;

#ifdef _DEBUG
	Quad dbgQuad;
	vec2 size = vec2(m_radius * 2.0f);
#endif
};

} // Namespace jci.