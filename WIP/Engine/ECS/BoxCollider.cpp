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
#ifdef _DEBUG
	dbgQuad = Quad(&m_size, { 0.0f, 0.0f, 1.0f, 1.0f }, entity->GetComponent<Transform>()->GetPositionPointer(), nullptr, TextureManager::Instance()->GetTexture(EngineTextureIndex::Dbg_Box), 255, false);
	Dbg_Render(&dbgQuad);
#endif // _DEBUG

}

void BoxCollider::OnComponentRemove()
{
	// Remove from collision system.
	CollisionManager::Instance()->RemoveObject(m_entity, m_bodyType);

	Dbg_Render_Remove(&dbgQuad);
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