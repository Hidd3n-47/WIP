#pragma once

#include "IComponent.h"

namespace jci {

enum class BodyType
{
	Static,
	Kinematic
};

class BoxCollider : public IComponent
{
public:
	COMPONENT(ComponentTypes::BoxCollider);

	void OnComponentAdd(Entity* entity) final;
	void OnComponentRemove() final;

	inline virtual Entity* GetEntity() final { return m_entity; }

	// Accessors.
	inline vec2 GetSize() const { return m_size; }
	inline BodyType GetBodyType() const { m_bodyType; }

	// Mutators.
	inline void SetSize(vec2 size) { m_size = size; }
	void SetBodyType(BodyType type);
private:
	Entity*		m_entity	= nullptr;
	vec2		m_size		= vec2(1.0f);
	BodyType	m_bodyType	= BodyType::Static;
};

} // Namespace jci.