#include "pch.h"
#include "BoxCollider.h"

#include "Collision/CollisionManager.h"

namespace jci {

void BoxCollider::OnComponentAdd(GameObject* gameObject)
{
	// Add to Collision system.
	m_gameObject = gameObject;
	CollisionManager::Instance()->AddObject(m_gameObject, m_bodyType);
}

void BoxCollider::OnComponentRemove()
{
	// Remove from collision system.
	CollisionManager::Instance()->RemoveObject(m_gameObject, m_bodyType);
}

void BoxCollider::SetBodyType(BodyType type)
{
	if (m_bodyType == type) return;

	CollisionManager::Instance()->UpdateBodyType(m_gameObject, m_bodyType, type);
	m_bodyType = type;
}

} // Namespace jci.