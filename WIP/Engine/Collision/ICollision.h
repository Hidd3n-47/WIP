#pragma once

#include "CollisionBodyDetails.h"

namespace jci {

class Entity;

/***
=========================================================================================
ICollision (CALLBACK):
	Callback methods for the collision.
=========================================================================================
*/
__interface ICollision
{
public:
	void OnCollisionEnter(Entity* other) = 0;
	void OnCollisionStay(Entity* other) = 0;
	void OnCollisionExit(Entity* other) = 0;
};

/***
=========================================================================================
ICOLLIDER (COLLISION_INTERFACE):
	Interface for the colliders.
=========================================================================================
*/
class ICollider
{
	friend class CollisionManager;
public:
	virtual ~ICollider() = default;

	inline void OnCollisionEnter(Entity* other) { if (m_collisionMethods) m_collisionMethods->OnCollisionEnter(other); }
	inline void OnCollisionStay(Entity* other)	{ if (m_collisionMethods) m_collisionMethods->OnCollisionStay(other); }
	inline void OnCollisionExit(Entity* other)	{ if (m_collisionMethods) m_collisionMethods->OnCollisionExit(other); }

	/***
	* Get if the collider is only a trigger.
	*
	*/
	inline bool IsTrigger() const { return m_trigger; }

	/***
	* Set the collision callback methods.
	*
	*/
	inline void SetCollisionMethods(ICollision* collisionMethods) { m_collisionMethods = collisionMethods; }
	/***
	* Set if the collider is only a trigger.
	*
	*/
	inline void SetTrigger(bool trigger) { m_trigger = trigger; }
protected:
	ShapeBody m_body = ShapeBody::Box;

	ICollision* m_collisionMethods = nullptr;
	bool m_trigger = false;

	std::vector<ICollider*> m_collidedLastFrame;
};

} // Namespace jci.