#include "pch.h"
#include "RendererManager.h"

#include "Renderer.h"
#include "ECS/Entity.h"
#include "ECS/Transform.h"
#include "Scene/SceneManager.h"
#include "ECS/SpriteRenderer.h"
#include "Graphics/Texture/Texture.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Vertex.h"
#include "Shader.h"

namespace jci {

RendererManager* RendererManager::m_instance = nullptr;

void RendererManager::Init()
{ 
	m_renderData.vertexArray = new VertexArray();

	m_renderData.vertexBuffer = new VertexBuffer(m_renderData.MAX_QUADS * sizeof(Vertex) * 4);

	m_renderData.vertexArray->SetVertexBuffer(m_renderData.vertexBuffer);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glEnableVertexAttribArray(1);					
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);					
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 5));

	m_renderData.verticesBase = new Vertex[m_renderData.MAX_QUADS * 4];
	m_renderData.verticesPtr = m_renderData.verticesBase;

	uint32* indices = new uint32[m_renderData.MAX_QUADS * 6];

	uint32 offset = 0;
	for (uint32 i = 0; i < m_renderData.MAX_QUADS * 6; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	m_renderData.vertexArray->SetIndexBuffer(indices, m_renderData.MAX_QUADS * 6);

	int32 samplers[m_renderData.MAX_TEXTURE_SLOTS];
	for (uint32 i = 0; i < m_renderData.MAX_TEXTURE_SLOTS; i++)
	{
		samplers[i] = i;
	}

	m_renderData.shader = new Shader("Assets/Shader/shader.vert", "Assets/Shader/shader.frag");
	m_renderData.shader->Bind();

	m_renderData.shader->UploadUniformIntArray("u_texture", samplers, m_renderData.MAX_TEXTURE_SLOTS);

	delete[] indices;

	// Set first texture
	// Question could texture manager hold the textures and bind them?
}

void RendererManager::Begin()
{
	// bind texture
	// bind camera matrix
	//m_renderData.shader->UploadUniformInt("u_texture", 0);

	m_renderData.verticesPtr = m_renderData.verticesBase;
	m_renderData.indexCount = 0;

	for (SpriteRenderer* sr : m_quads)
	{
		vec2 position = sr->GetEntity()->GetComponent<Transform>()->GetPosition();
		vec2 size = sr->GetSize();
		Texture* text = sr->GetTexture();
		
		float textureIndex = -1.0f;
		for (uint32 i = 0; i < m_renderData.textureSlotIndex; i++)
		{
			if (m_renderData.textureSlots[i] == text)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == -1.0f)
		{
			textureIndex = (float)m_renderData.textureSlotIndex;
			m_renderData.textureSlots[m_renderData.textureSlotIndex] = text;
			m_renderData.textureSlotIndex++;
		}

		size *= 0.5f;

		m_renderData.verticesPtr->position = vec3(position-size, 0.0f);
		m_renderData.verticesPtr->uvCoord = { 0.0f, 0.0f };
		m_renderData.verticesPtr->textureId = textureIndex;
		m_renderData.verticesPtr++;

		m_renderData.verticesPtr->position = vec3(position.x+size.x,position.y-size.y, 0.0f);
		m_renderData.verticesPtr->uvCoord = { 1.0f, 0.0f };
		m_renderData.verticesPtr->textureId = textureIndex;
		m_renderData.verticesPtr++;

		m_renderData.verticesPtr->position = vec3(position + size, 0.0f);
		m_renderData.verticesPtr->uvCoord = { 1.0f, 1.0f };
		m_renderData.verticesPtr->textureId = textureIndex;
		m_renderData.verticesPtr++;

		m_renderData.verticesPtr->position = vec3(position.x-size.y, position.y + size.y, 0.0f);
		m_renderData.verticesPtr->uvCoord = { 0.0f, 1.0f };
		m_renderData.verticesPtr->textureId = textureIndex;
		m_renderData.verticesPtr++;

		m_renderData.indexCount += 6;
	}
}

void RendererManager::End()
{
	m_renderData.shader->UploadUniformMat4("u_orthoProjMatrix", SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetViewProjMat());

	uint32 size = (ubyte*)m_renderData.verticesPtr - (ubyte*)m_renderData.verticesBase;
	
	m_renderData.vertexBuffer->SetData(m_renderData.verticesBase, size);

	Flush();
}

void RendererManager::Flush()
{
	// RendererDraw(); <- pass in vertex array?
	// Pass throught the index count of the datat.
	for (uint32 i = 0; i < m_renderData.textureSlotIndex; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		m_renderData.textureSlots[i]->Bind();
	}
	
	glDrawElements(GL_TRIANGLES, m_renderData.indexCount, GL_UNSIGNED_INT, nullptr);
}

// TODO Ccould maybe remove passing in sprite renderer and pass in the actual stats.
void RendererManager::AddQuadToQueue(SpriteRenderer* spriteRenderer)
{
	Texture* text = spriteRenderer->GetTexture();

	m_quads.push_back(spriteRenderer);
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

void RendererManager::Update()
{
	for (SpriteRenderer* s : m_quads)
	{
		s->GetTexture()->Bind();
		//Renderer::DrawQuad(s->GetEntity()->GetComponent<Transform>()->GetPosition(), s->GetSize(), vec4(s->GetColor(), 1.0f), s->GetTexture());
		Transform* t = s->GetEntity()->GetComponent<Transform>();
		Renderer::DrawQuad(t->GetPosition(), s->GetSize(), t->GetScale(), vec4(s->GetColor(), 1.0f), s->GetTexture());
	}
}

} // Namespace jci.