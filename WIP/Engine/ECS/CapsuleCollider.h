#pragma once

#include "IComponent.h"
#include "Collision/ICollision.h"
#include "Collision/CollisionBodyDetails.h"

#ifdef _DEBUG
#include "Graphics/Renderer/RendererManager.h"
#endif

namespace jci {

class CapsuleCollider : public IComponent, public ICollider
{
public:
	REGISTER_COMPONENT(ComponentTypes::CapsuleCollider);

	CapsuleCollider() { m_body = ShapeBody::Capsule; }
	~CapsuleCollider() = default;

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; }
	inline void OnComponentRemove() final { }

	// Accessors.
	inline vec2 GetRectSize() const { return m_rectSize; }
	inline float GetRadius() const { return m_radius; }
	inline BodyType GetBodyType() const { return m_bodyType; }

	// Mutators.
	inline void SetRectSize(vec2 rectSize) { m_rectSize = rectSize; }
	inline void SetRadius(float radius) { m_radius = radius; }
	inline void SetBodyType(BodyType type) { m_bodyType = type; }

	inline CapsuleCollider& operator=(CapsuleCollider& other) noexcept
	{
		m_id = std::move(other.m_id);
		m_entity = std::move(other.m_entity);
		m_radius = std::move(other.m_radius);
		m_bodyType = std::move(other.m_bodyType);

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