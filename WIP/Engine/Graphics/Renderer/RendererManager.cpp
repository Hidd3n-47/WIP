#include "pch.h"
#include "RendererManager.h"

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
	// Sprite Rendering.
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

	// ParticleRenderering.
	const uint16 MAX_PARTICLES = ParticleManager::Instance()->MAX_PARTICLES;

	m_particleVertexArray = new VertexArray();

	m_particleVertexBuffer = new VertexBuffer(MAX_PARTICLES * sizeof(ParticleVertex) * 4);

	m_particleVertexArray->SetVertexBuffer(m_particleVertexBuffer);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (void*)(sizeof(float) * 3));

	m_particleVerticesBase = new ParticleVertex[MAX_PARTICLES * 4];
	m_particleVerticesPtr = m_particleVerticesBase;

	uint32* partIndices = new uint32[MAX_PARTICLES * 6];

	offset = 0;
	for (uint32 i = 0; i < MAX_PARTICLES * 6; i += 6)
	{
		partIndices[i + 0] = offset + 0;
		partIndices[i + 1] = offset + 1;
		partIndices[i + 2] = offset + 2;

		partIndices[i + 3] = offset + 2;
		partIndices[i + 4] = offset + 3;
		partIndices[i + 5] = offset + 0;

		offset += 4;
	}

	m_particleVertexArray->SetIndexBuffer(partIndices, MAX_PARTICLES * 6);

	m_particleShader = new Shader("Assets/Shader/particleShader.vert", "Assets/Shader/particleShader.frag");
	m_particleShader->Bind();

	delete[] partIndices;
}

void RendererManager::Begin()
{
	m_verticesPtr = m_verticesBase;
	m_indexCount = 0;

	for(const Quad* q : m_quads)
	{
		if (q->active && !*q->active)
		{
			continue;
		}

		vec2 position = !q->position ? vec2(0.0f) : *q->position;

		Texture* texture = !q->texture ? TextureManager::Instance()->GetTexture(EngineTextureIndex::NoTexture) : q->texture;

		float textureIndex = -1.0f;
		for (uint32 i = 0; i < m_textureSlotIndex; i++)
		{
			if (m_textureSlots[i] == texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == -1.0f)
		{
			textureIndex = (float)m_textureSlotIndex;
			m_textureSlots[m_textureSlotIndex] = texture;
			m_textureSlotIndex++;
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

		m_indexCount += 6;
	}

	m_particleVerticesPtr = m_particleVerticesBase;
	m_particleIndexCount = 0;

	uint32 numParticles = ParticleManager::Instance()->m_particleIndex;
	std::vector<ParticleManager::Particle> particles = ParticleManager::Instance()->m_particles;
	for (uint32 i = 0; i < numParticles; i++)
	{
		float size = particles[i].size;

		m_particleVerticesPtr->position = vec3(particles[i].position - size, 0.99f);
		m_particleVerticesPtr->color = particles[i].color;
		m_particleVerticesPtr++;

		m_particleVerticesPtr->position = vec3(particles[i].position.x + size, particles[i].position.y - size, 0.99f);
		m_particleVerticesPtr->color = particles[i].color;
		m_particleVerticesPtr++;

		m_particleVerticesPtr->position = vec3(particles[i].position + size, 0.99f);
		m_particleVerticesPtr->color = particles[i].color;
		m_particleVerticesPtr++;

		m_particleVerticesPtr->position = vec3(particles[i].position.x - size, particles[i].position.y + size, 0.99f);
		m_particleVerticesPtr->color = particles[i].color;
		m_particleVerticesPtr++;

		m_particleIndexCount += 6;
	}
}

void RendererManager::End()
{
	uint32 size = (ubyte*)m_verticesPtr - (ubyte*)m_verticesBase;
	m_vertexBuffer->Bind();
	m_vertexBuffer->SetData(m_verticesBase, size);

	size = (ubyte*)m_particleVerticesPtr - (ubyte*)m_particleVerticesBase;
	m_particleVertexBuffer->Bind();
	m_particleVertexBuffer->SetData(m_particleVerticesBase, size);

	Flush();
}

void RendererManager::Flush()
{
	mat4 viewProj = SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetViewProjMat();

	for (uint32 i = 0; i < m_textureSlotIndex; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		m_textureSlots[i]->Bind();
	}
	
	m_vertexArray->Bind();
	m_shader->Bind();
	m_shader->UploadUniformMat4("u_orthoProjMatrix", viewProj);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);

	m_particleVertexArray->Bind();
	m_particleShader->Bind();
	m_particleShader->UploadUniformMat4("u_orthoProjMatrix", viewProj);
	glDrawElements(GL_TRIANGLES, m_particleIndexCount, GL_UNSIGNED_INT, nullptr);
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