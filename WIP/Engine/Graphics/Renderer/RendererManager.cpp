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
	m_vertexArray = new VertexArray();

	m_vertexBuffer = new VertexBuffer(MAX_QUADS * sizeof(Vertex) * 4);

	m_vertexArray->SetVertexBuffer(m_vertexBuffer);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glEnableVertexAttribArray(1);					
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);					
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 5));

	m_verticesBase = new Vertex[MAX_QUADS * 4];
	m_verticesPtr = m_verticesBase;

	uint32* indices = new uint32[MAX_QUADS * 6];

	uint32 offset = 0;
	for (uint32 i = 0; i < MAX_QUADS * 6; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	m_vertexArray->SetIndexBuffer(indices, MAX_QUADS * 6);

	int32 samplers[MAX_TEXTURE_SLOTS];
	for (uint32 i = 0; i < MAX_TEXTURE_SLOTS; i++)
	{
		samplers[i] = i;
	}

	m_shader = new Shader("Assets/Shader/shader.vert", "Assets/Shader/shader.frag");
	m_shader->Bind();

	m_shader->UploadUniformIntArray("u_texture", samplers, MAX_TEXTURE_SLOTS);

	delete[] indices;
}

void RendererManager::Begin()
{
	m_verticesPtr = m_verticesBase;
	indexCount = 0;

	for(const Quad& q : m_quads)
	{
		vec2 size = q.spriteRenderer->GetSize();
		Texture* text = q.spriteRenderer->GetTexture();
		
		float textureIndex = -1.0f;
		for (uint32 i = 0; i < textureSlotIndex; i++)
		{
			if (m_textureSlots[i] == text)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == -1.0f)
		{
			textureIndex = (float)textureSlotIndex;
			m_textureSlots[textureSlotIndex] = text;
			textureSlotIndex++;
		}

		size = size * 0.5f;

		m_verticesPtr->position = vec3(*q.position - size, 0.0f);
		m_verticesPtr->uvCoord = { 0.0f, 0.0f };
		m_verticesPtr->textureId = textureIndex;
		m_verticesPtr++;
		
		m_verticesPtr->position = vec3(q.position->x + size.x, q.position->y - size.y, 0.0f);
		m_verticesPtr->uvCoord = { 1.0f, 0.0f };
		m_verticesPtr->textureId = textureIndex;
		m_verticesPtr++;
		
		m_verticesPtr->position = vec3(*q.position + size, 0.0f);
		m_verticesPtr->uvCoord = { 1.0f, 1.0f };
		m_verticesPtr->textureId = textureIndex;
		m_verticesPtr++;
		
		m_verticesPtr->position = vec3(q.position->x - size.x, q.position->y + size.y, 0.0f);
		m_verticesPtr->uvCoord = { 0.0f, 1.0f };
		m_verticesPtr->textureId = textureIndex;
		m_verticesPtr++;

		indexCount += 6;
	}
}

void RendererManager::End()
{
	m_shader->UploadUniformMat4("u_orthoProjMatrix", SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetViewProjMat());

	if (m_lightPosition)
	{
		m_shader->UploadUniformVec2("u_lightPos", *m_lightPosition);
	}
	else
	{
		m_shader->UploadUniformVec2("u_lightPos", vec2(0.0f));
	}

	uint32 size = (ubyte*)m_verticesPtr - (ubyte*)m_verticesBase;
	
	m_vertexBuffer->SetData(m_verticesBase, size);

	Flush();
}

void RendererManager::Flush()
{
	// RendererDraw(); <- pass in vertex array?
	// Pass throught the index count of the datat.
	for (uint32 i = 0; i < textureSlotIndex; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		m_textureSlots[i]->Bind();
	}
	
	m_vertexArray->Bind();
	m_shader->Bind();
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

// TODO Ccould maybe remove passing in sprite renderer and pass in the actual stats.
void RendererManager::AddQuadToQueue(SpriteRenderer* spriteRenderer)
{
	vec2* position = spriteRenderer->GetEntity()->GetComponent<Transform>()->GetPositionPointer();

	m_quads.emplace_back(position, spriteRenderer);
}

void RendererManager::RemoveQuadFromQueue(SpriteRenderer* spriteRenderer)
{
	for (int i = 0; i < m_quads.size(); i++)
	{
		if (m_quads[i].spriteRenderer == spriteRenderer)
		{
			m_quads[i] = m_quads.back();
			m_quads.pop_back();
			return;
		}
	}

	ASSERT(false, "Sprite Renderer not found to remove.");
}

} // Namespace jci.