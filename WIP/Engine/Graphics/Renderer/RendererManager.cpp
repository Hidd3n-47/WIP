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

	for(const Quad* q : m_quads)
	{		
		vec2 position = !q->position ? vec2(0.0f) : *q->position;

		Texture* texture = !q->texture ? TextureManager::Instance()->GetTexture(EngineTextureIndex::NoTexture) : q->texture;

		float textureIndex = -1.0f;
		for (uint32 i = 0; i < textureSlotIndex; i++)
		{
			if (m_textureSlots[i] == texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == -1.0f)
		{
			textureIndex = (float)textureSlotIndex;
			m_textureSlots[textureSlotIndex] = texture;
			textureSlotIndex++;
		}

		// Rotation.
		vec2 size = !q->size ? vec2(0.5f) : *q->size * 0.5f;

		float angle = !q->rotation ? 0.0f : *q->rotation;

		float sina = glm::sin(glm::radians(angle));
		float cosa = glm::cos(glm::radians(angle));

		float xsina = size.x * sina;
		float xcosa = size.x * cosa;
		float ysina = size.y * sina;
		float ycosa = size.y * cosa;

		vec2 s1 = vec2( xcosa - ysina,  ycosa + xsina);
		vec2 s2 = vec2( xcosa + ysina, -ycosa + xsina);
		vec2 s3 = vec2(-xcosa - ysina,  ycosa - xsina);

		// uv calculations.
		vec2 botL(q->uvRect.x, q->uvRect.y);
		vec2 botR(q->uvRect.x + q->uvRect.z, q->uvRect.y);
		vec2 topR(q->uvRect.x + q->uvRect.z, q->uvRect.y + q->uvRect.w);
		vec2 topL(q->uvRect.x, q->uvRect.y + q->uvRect.w);

		// Vertices.
		m_verticesPtr->position = vec3(position - s1, (float)(q->layer) / 256.0f);
		m_verticesPtr->uvCoord = (q->flipVertically ? botR : botL);
		m_verticesPtr->textureId = textureIndex;
		m_verticesPtr++;
		
		m_verticesPtr->position = vec3(position.x + s2.x, position.y + s2.y, (float)(q->layer) / 256.0f);
		m_verticesPtr->uvCoord = (q->flipVertically ? botL : botR);
		m_verticesPtr->textureId = textureIndex;
		m_verticesPtr++;
		
		m_verticesPtr->position = vec3(position + s1, (float)(q->layer) / 256.0f);
		m_verticesPtr->uvCoord = (q->flipVertically ? topL : topR);
		m_verticesPtr->textureId = textureIndex;
		m_verticesPtr++;
		
		m_verticesPtr->position = vec3(position.x + s3.x, position.y + s3.y, (float)(q->layer) / 256.0f);
		m_verticesPtr->uvCoord = (q->flipVertically ? topR : topL);
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
	for (uint32 i = 0; i < textureSlotIndex; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		m_textureSlots[i]->Bind();
	}
	
	m_vertexArray->Bind();
	m_shader->Bind();
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}


void RendererManager::AddQuadToQueue(Quad* quad)
{
	m_quads.push_back(quad);
}

void RendererManager::RemoveQuadFromQueue(Quad* quad)
{
	for (int i = 0; i < m_quads.size(); i++)
	{
		if (m_quads[i] == quad)
		{
			m_quads[i] = m_quads.back();
			m_quads.pop_back();
			return;
		}
	}

	ASSERT(false, "Quad to renderer not found to remove.");
}

} // Namespace jci.