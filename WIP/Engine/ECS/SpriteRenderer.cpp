#include "pch.h"
#include "SpriteRenderer.h"

#include "Renderer/RendererManager.h"

namespace jci {

void SpriteRenderer::OnComponentAdd()
{
	// Add to the renderering queue.

	// tmp.
	m_texture = new Texture("Assets/Texture/circ.png");
	RendererManager::Instance()->AddQuadToQueue(this);
}

void SpriteRenderer::OnComponentRemove()
{
	// Remove from the rendering queue.
	RendererManager::Instance()->RemoveQuadFromQueue(this);
	delete m_texture;
}

} // Namespace jci.