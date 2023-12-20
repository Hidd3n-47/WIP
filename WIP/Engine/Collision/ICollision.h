#pragma once

#include "CollisionBodyDetails.h"

namespace jci {

class Entity;

__interface ICollision
{
public:
	void OnCollisionEnter(Entity* other)	= 0;
	void OnCollisionStay(Entity* other)		= 0;
	void OnCollisionExit(Entity* other)		= 0;
};
//
//__interface ITrigger
//{
//public:
//	void OnTriggerEnter(Entity* other)	= 0;
//	void OnTriggerStay(Entity* other)	= 0;
//	void OnTriggerExit(Entity* other)	= 0;
//};

class ICollider
{
	friend class CollisionManager;
public:
	virtual ~ICollider() = default;

	inline void OnCollisionEnter(Entity* other) { if (m_collisionMethods) m_collisionMethods->OnCollisionEnter(other); }
	inline void OnCollisionStay(Entity* other)	{ if (m_collisionMethods) m_collisionMethods->OnCollisionStay(other); }
	inline void OnCollisionExit(Entity* other)	{ if (m_collisionMethods) m_collisionMethods->OnCollisionExit(other); }

	inline bool IsTrigger() const { return m_trigger; }

	inline void SetCollisionMethods(ICollision* collisionMethods) { m_collisionMethods = collisionMethods; }
	inline void SetTrigger(bool trigger) { m_trigger = trigger; }
protected:
	ShapeBody m_body;

	ICollision* m_collisionMethods = nullptr;
	bool m_trigger = false;

	std::vector<ICollider*> m_collidedLastFrame;
};

} // Namespace jci.