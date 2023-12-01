#include "pch.h"
#include "SpriteRenderer.h"

#include "Graphics/Texture/Texture.h"
#include "Graphics/Texture/TextureManager.h"
#include "Graphics/Renderer/RendererManager.h"

namespace jci {

void SpriteRenderer::OnComponentAdd(Entity* entity)
{
	// Add to the renderering queue.
	m_entity = entity;
	m_texture = TextureManager::Instance()->GetTexture(EngineTextureIndex::NoTexture);
	RendererManager::Instance()->AddQuadToQueue(this);
}

void SpriteRenderer::OnComponentRemove()
{
	// Remove from the rendering queue.
	RendererManager::Instance()->RemoveQuadFromQueue(this);
}

} // Namespace jci.