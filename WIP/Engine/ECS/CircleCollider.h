#pragma once

#include "IComponent.h"
#include "Collision/ICollision.h"
#include "Collision/CollisionBodyDetails.h"

#ifdef _DEBUG
#include "Graphics/Renderer/RendererManager.h"
#endif

namespace jci {

class CircleCollider : public IComponent, public ICollider
{
public:
	REGISTER_COMPONENT(ComponentTypes::CircleCollider);
	
	CircleCollider() { m_body = ShapeBody::Circle; }
	~CircleCollider() = default;

	void OnComponentAdd(Entity* entity) final;
	void OnComponentRemove() final;

	// Accessors.
	inline float GetRadius() const { return m_radius; }
	inline BodyType GetBodyType() const { return m_bodyType; }

	// Mutators.
	inline void SetRadius(float radius) { m_radius = radius; }
	inline void SetBodyType(BodyType type) { m_bodyType = type; }

	inline CircleCollider& operator=(CircleCollider& other) noexcept
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

	float		m_radius = 0.5f;
	BodyType	m_bodyType = BodyType::Static;

#ifdef _DEBUG
	//Quad dbgQuad;
	//vec2 size = vec2(m_radius * 2.0f);
#endif
};

} // Namespace jci.