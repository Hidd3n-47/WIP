#include "pch.h"
#include "UiButton.h"

#include "Entity.h"

namespace jci {

void UiSprite::OnComponentAdd(Entity* entity)
{
	m_entity = entity;
	RendererManager::Instance()->AddQuadToQueue(&m_quad);

	m_quad.size = &m_size;
	m_quad.layer = 255;
	m_quad.position = &m_position;
	m_quad.active = m_entity->GetActivePointer();
}

void UiSprite::OnComponentRemove()
{
	RendererManager::Instance()->RemoveQuadFromQueue(&m_quad);
}

} // Namespace jci.