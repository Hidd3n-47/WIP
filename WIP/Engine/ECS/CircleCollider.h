#pragma once

#include "IComponent.h"
#include "Collision/ICollision.h"

namespace jci {

/***
=========================================================================================
CIRCLE_COLLIDER (COMPONENT):
	Add collision/trigger to entity.
	Circle colliders are in the shape of a circle.
=========================================================================================
*/
class CircleCollider : public IComponent, public ICollider
{
public:
	REGISTER_COMPONENT(ComponentTypes::CircleCollider);
	
	CircleCollider() { m_body = ShapeBody::Circle; }
	~CircleCollider() = default;

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; }
	inline void OnComponentRemove() final { }

	// Accessors.
	/***
	* Get the radius of the circle collider.
	*
	*/
	inline float GetRadius() const { return m_radius; }
	/***
	* Get the body type of the circle collider
	* Note: Kinematic are object that move and have collision; Static are object that are stationary and have collision.
	*/
	inline BodyType GetBodyType() const { return m_bodyType; }

	// Mutators.
	/***
	* Set the radius of the collider.
	*
	*/
	inline void SetRadius(float radius) { m_radius = radius; }
	/***
	* Set the body type of the circle collider.
	* Note: Kinematic are objects that move and have collision; Static are object that are stationary and have collision.
	*/
	inline void SetBodyType(BodyType type) { m_bodyType = type; }

	inline CircleCollider& operator=(CircleCollider& other) noexcept
	{
		memcpy(this, &other, sizeof(CircleCollider));

		return *this;
	}
private:
	Entity*		m_entity = nullptr;
	entId		m_id = invalid_id;

	float		m_radius = 0.5f;
	BodyType	m_bodyType = BodyType::Static;
};

} // Namespace jci.