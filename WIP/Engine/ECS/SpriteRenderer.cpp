#include "pch.h"
#include "SpriteRenderer.h"

#include "Renderer/RendererManager.h"

namespace jci {

void SpriteRenderer::OnComponentAdd(GameObject* gameObject)
{
	// Add to the renderering queue.
	m_gameObject = gameObject;
	m_texture = new Texture("Assets/Texture/circ.png");
	RendererManager::Instance()->AddQuadToQueue(this);
}

void SpriteRenderer::OnComponentRemove()
{
	// Remove from the rendering queue.
	RendererManager::Instance()->RemoveQuadFromQueue(this);
	delete m_texture;
	m_texture = nullptr;
}

} // Namespace jci.