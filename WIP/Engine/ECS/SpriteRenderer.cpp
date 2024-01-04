#include "pch.h"
#include "SpriteRenderer.h"

#include "Entity.h"

namespace jci {

void SpriteRenderer::OnComponentAdd(Entity* entity)
{
	m_entity = entity;
}

void SpriteRenderer::OnComponentRemove()
{
}

} // Namespace jci.