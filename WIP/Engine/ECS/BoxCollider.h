/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once

#include "IComponent.h"
#include "Collision/ICollision.h"


namespace jci {

/***
=========================================================================================
BOX_COLLIDER (COMPONENT):
	Add collision/trigger box to the entity. 
	Box colliders have the shape of a rectangle.
=========================================================================================
*/
class BoxCollider : public IComponent, public ICollider
{
public:
	REGISTER_COMPONENT(ComponentTypes::BoxCollider);

	BoxCollider() { m_body = ShapeBody::Box; }
	~BoxCollider() = default;

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; }
	inline void OnComponentRemove() final { }

	// Accessors.
	/***
	* Get the size of the box collider.
	*
	*/
	inline vec2 GetSize() const { return m_size; }
	/***
	* Get the body type of the box collider.
	* Kinematic is something that moves and has collision. Static is a stationary object that has collision.
	*/
	inline BodyType GetBodyType() const { return m_bodyType; }

	// Mutators.
	/***
	* Set the size of the box collider.
	*
	*/
	inline void SetSize(vec2 size) { m_size = size; }
	/***
	* Set the body type of the box collider.
	* Kinematic is something that moves and has collision. Static is a stationary object that has collision.
	*/
	inline void SetBodyType(BodyType type) { m_bodyType = type; }

	inline BoxCollider& operator=(BoxCollider& other) noexcept
	{
		m_entity	= other.m_entity;
		m_id		= other.m_id;
		m_size		= other.m_size;
		m_bodyType	= other.m_bodyType;

		m_body				= other.m_body;
		m_collisionMethods	= other.m_collisionMethods;
		m_trigger			= other.m_trigger;
		m_collidedLastFrame = other.m_collidedLastFrame;

		return *this;
	}
private:
	Entity*		m_entity	= nullptr;
	entId		m_id		= invalid_id;

	vec2		m_size		= vec2(1.0f);
	BodyType	m_bodyType	= BodyType::Static;
};

} // Namespace jci.