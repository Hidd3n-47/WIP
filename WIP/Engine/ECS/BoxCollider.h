#pragma once

#include "IComponent.h"

namespace jci {

class BoxCollider : public IComponent
{
public:
	void OnComponentAdd(GameObject* gameObject) final;
	void OnComponentRemove() final;

	virtual GameObject* GetGameObject() final { return m_gameObject; }

	static uint16 GetIdMask() { return (int)ComponentTypes::BoxCollider; }

private:
	GameObject* m_gameObject = nullptr;
};

} // Namespace jci.