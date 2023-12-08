#include "pch.h"
#include "BoxCollider.h"

#include "ECS/Entity.h"
#include "Collision/CollisionManager.h"

namespace jci {

void BoxCollider::OnComponentAdd(Entity* entity)
{
	// Add to Collision system.
	m_entity = entity;
	CollisionManager::Instance()->AddObject(m_entity, m_bodyType);
}

void BoxCollider::OnComponentRemove()
{
	// Remove from collision system.
	CollisionManager::Instance()->RemoveObject(m_entity, m_bodyType);
}

void BoxCollider::CollisionOccured(Entity* otherEntity)
{
	if (m_trigger && m_triggerMethods)
	{
		if (!m_collisionOccured)
		{
			m_collisionOccured = true;
			m_triggerMethods->OnTriggerEnter(otherEntity);
			return;
		}
		else
		{
			m_triggerMethods->OnTriggerStay(otherEntity);
			return;
		}
	}

	if (m_collisionMethods)
	{
		if (!m_collisionOccured)
		{
			m_collisionOccured = true;
			m_collisionMethods->OnCollisionEnter(otherEntity);
			return;
		}
		else
		{
			m_collisionMethods->OnCollisionStay(otherEntity);
			return;
		}
	}
}

void BoxCollider::CollisionExit()
{
	m_collisionOccured = false;

	if (m_trigger && m_triggerMethods)
	{
		m_triggerMethods->OnTriggerExit();
	}

	if (m_collisionMethods)
	{
		m_collisionMethods->OnCollisionExit();
	}
}

void BoxCollider::SetBodyType(BodyType type)
{
	if (m_bodyType == type) return;

	CollisionManager::Instance()->UpdateBodyType(m_entity, m_bodyType, type);
	m_bodyType = type;
}

} // Namespace jci.