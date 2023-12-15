#include "pch.h"
#include "Animation.h"

#include "Entity.h"

namespace jci {

void Animation::OnComponentAdd(Entity* entity)
{
	m_entity = entity; RendererManager::Instance()->AddQuadToQueue(&m_quad);

	Transform* t = entity->GetComponent<Transform>();
	m_quad.position = t->GetPositionPointer();
	m_quad.rotation = t->GetRotationPointer();
}

}