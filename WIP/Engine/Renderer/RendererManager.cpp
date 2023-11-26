#include "pch.h"
#include "RendererManager.h"

#include "Renderer.h"
#include "ECS/Entity.h"
#include "ECS/Transform.h"
#include "ECS/SpriteRenderer.h"

namespace jci {

RendererManager* RendererManager::m_instance = nullptr;

void RendererManager::AddQuadToQueue(SpriteRenderer* spriteRenderer)
{
	m_quads.emplace_back(spriteRenderer);
}

void RendererManager::RemoveQuadFromQueue(SpriteRenderer* spriteRenderer)
{
	for (int i = 0; i < m_quads.size(); i++)
	{
		if (m_quads[i] == spriteRenderer)
		{
			m_quads[i] = m_quads.back();
			m_quads.pop_back();
			return;
		}
	}

	ASSERT(false, "Sprite Renderer not found to remove.");
}

void RendererManager::RenderUpdate()
{
	for (SpriteRenderer* s : m_quads)
	{
		s->GetTexture()->Bind();
		Renderer::DrawQuad(s->GetEntity()->GetComponent<Transform>()->GetPosition(), s->GetSize(), vec4(s->GetColor(), 1.0f), s->GetTexture());
	}
}

} // Namespace jci.