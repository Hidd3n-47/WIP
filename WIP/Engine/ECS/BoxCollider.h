#pragma once

#include "IComponent.h"
#include "Collision/ICollision.h"
#include "Collision/CollisionBodyDetails.h"

#ifdef _DEBUG
#include "Graphics/Renderer/RendererManager.h"
#endif

namespace jci {

class BoxCollider : public IComponent, public ICollider
{
public:
	REGISTER_COMPONENT(ComponentTypes::BoxCollider);

	BoxCollider() { m_body = ShapeBody::Box; }
	~BoxCollider() = default;

	void OnComponentAdd(Entity* entity) final;
	void OnComponentRemove() final;

	// Accessors.
	inline vec2 GetSize() const { return m_size; }
	inline BodyType GetBodyType() const { return m_bodyType; }

	// Mutators.
	inline void SetSize(vec2 size) { m_size = size; }
	inline void SetBodyType(BodyType type) { m_bodyType = type; }

	inline BoxCollider& operator=(BoxCollider& other) noexcept
	{
		m_id = std::move(other.m_id);
		m_entity = std::move(other.m_entity);
		m_size = std::move(other.m_size);
		m_bodyType = std::move(other.m_bodyType);

		return *this;
	}
private:
	Entity*		m_entity	= nullptr;
	entId		m_id		= invalid_id;

	vec2		m_size		= vec2(1.0f);
	BodyType	m_bodyType	= BodyType::Static;

#ifdef _DEBUG
	Quad dbgQuad;
#endif
};

} // Namespace jci.