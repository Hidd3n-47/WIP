#include "pch.h"
#include "BoxCollider.h"

#include "ECS/Entity.h"
#include "Collision/CollisionManager.h"

namespace jci {

void BoxCollider::OnComponentAdd(Entity* entity)
{
	// Add to Collision system.
	m_entity = entity;
	//CollisionManager::Instance()->AddObject(m_entity, m_bodyType);
#ifdef _DEBUG
	dbgQuad = Quad(&m_size, { 0.0f, 0.0f, 1.0f, 1.0f }, entity->GetComponent<Transform>()->GetPositionPointer(), nullptr, TextureManager::Instance()->GetTexture(EngineTextureIndex::Dbg_Box), nullptr, 255, false);
	Dbg_Render(&dbgQuad);
#endif // _DEBUG

}

void BoxCollider::OnComponentRemove()
{
	// Remove from collision system.
	//CollisionManager::Instance()->RemoveObject(m_entity, m_bodyType);

	Dbg_Render_Remove(&dbgQuad);
}

} // Namespace jci.