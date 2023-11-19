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
	void OnComponentAdd(GameObject* gameObject) final;
	void OnComponentRemove() final;

	virtual GameObject* GetGameObject() final { return m_gameObject; }

	COMPONENT(ComponentTypes::BoxCollider);

	// Accessors.
	inline vec2 GetSize() const { return m_size; }
	inline BodyType GetBodyType() const { m_bodyType; }

	// Mutators.
	inline void SetSize(vec2 size) { m_size = size; }
	void SetBodyType(BodyType type);
private:
	GameObject* m_gameObject	= nullptr;
	vec2 m_size					= vec2(1.0f);
	BodyType m_bodyType			= BodyType::Static;
};

} // Namespace jci.