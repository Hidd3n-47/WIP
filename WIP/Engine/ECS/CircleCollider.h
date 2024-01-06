#pragma once

#include "IComponent.h"
#include "Collision/ICollision.h"

namespace jci {

class CircleCollider : public IComponent, public ICollider
{
public:
	REGISTER_COMPONENT(ComponentTypes::CircleCollider);
	
	CircleCollider() { m_body = ShapeBody::Circle; }
	~CircleCollider() = default;

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; }
	inline void OnComponentRemove() final { }

	// Accessors.
	inline float GetRadius() const { return m_radius; }
	inline BodyType GetBodyType() const { return m_bodyType; }

	// Mutators.
	inline void SetRadius(float radius) { m_radius = radius; }
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