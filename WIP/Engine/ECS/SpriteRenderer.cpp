#include "pch.h"
#include "SpriteRenderer.h"

#include "Entity.h"

namespace jci {

void SpriteRenderer::OnComponentAdd(Entity* entity)
{
	// Add to the renderering queue.
	m_entity = entity;
	RendererManager::Instance()->AddQuadToQueue(&m_quad);

	Transform* t = entity->GetComponent<Transform>();
	m_quad.size = &m_size;
	m_quad.position = t->GetPositionPointer();
	m_quad.rotation = t->GetRotationPointer();
}

void SpriteRenderer::OnComponentRemove()
{
	// Remove from the rendering queue.
	RendererManager::Instance()->RemoveQuadFromQueue(&m_quad);
}

} // Namespace jci.