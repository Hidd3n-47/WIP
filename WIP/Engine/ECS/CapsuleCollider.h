#pragma once

#include "IComponent.h"
#include "Collision/ICollision.h"

namespace jci {

/***
=========================================================================================
CAPSULE_COLLIDER (COMPONENT):
	Add collision/trigger to entity.
	Capsule colliders are in the shape of a vertical capsule. 
		Semi-Circle top and bottom, rectangle for body.
=========================================================================================
*/
class CapsuleCollider : public IComponent, public ICollider
{
public:
	REGISTER_COMPONENT(ComponentTypes::CapsuleCollider);

	CapsuleCollider() { m_body = ShapeBody::Capsule; }
	~CapsuleCollider() = default;

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; }
	inline void OnComponentRemove() final { }

	// Accessors.
	/***
	* Get the rectangle size of the capsule collider.
	* Note: The capsule is a vertical capsule; The radius is half the width of the rectangle.
	*/
	inline vec2 GetRectSize() const { return m_rectSize; }
	/***
	* Get the radius of the circle for the capsual.
	* Note: The radius is automatically half the width of the rectangle.
	*/
	inline float GetRadius() const { return m_radius; }
	/***
	* Get the body type of the capsule collider.
	* Note: Kinematic objects are object that move and have collision, whilst static are object that are stationary and have collision.
	*/
	inline BodyType GetBodyType() const { return m_bodyType; }

	// Mutators.
	/***
	* Set the size of the capsules rectangle.
	* Note: The capsule is a vertical capsule; The radius is half the width of the rectangle.
	*/
	inline void SetRectSize(vec2 rectSize) { m_rectSize = rectSize; }
	/***
	* Set the body type of the capsule collider.
	* Note: Kinematic obejects are objects taht move and have collision, whilst static are objects that are stationary and have collision.
	*/
	inline void SetBodyType(BodyType type) { m_bodyType = type; }

	inline CapsuleCollider& operator=(CapsuleCollider& other) noexcept
	{
		m_entity	= other.m_entity;
		m_id		= other.m_id;
		m_rectSize	= other.m_rectSize;
		m_radius	= other.m_radius;
		m_bodyType	= other.m_bodyType;

		m_body				= other.m_body;
		m_collisionMethods	= other.m_collisionMethods;
		m_trigger			= other.m_trigger;
		m_collidedLastFrame = other.m_collidedLastFrame;

		return *this;
	}
private:
	Entity*		m_entity = nullptr;
	entId		m_id = invalid_id;

	vec2		m_rectSize = vec2(0.5f, 0.5f);
	float		m_radius = 0.25f;
	BodyType	m_bodyType = BodyType::Static;
};

} // Namespace jci.