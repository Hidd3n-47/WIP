#include "pch.h"
#include "RendererManager.h"

#include "ECS/Entity.h"
#include "ECS/SpriteRenderer.h"
#include "Scene/SceneManager.h"
#include "Graphics/Texture/TextureManager.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Vertex.h"
#include "Shader.h"

namespace jci {

RendererManager* RendererManager::m_instance = nullptr;

RendererManager::~RendererManager()
{
	delete m_particleShader;
	delete [] m_particleVerticesBase;
	delete m_particleVertexBuffer;
	delete m_particleVertexArray;

	delete m_shader;
	delete [] m_verticesBase;
	delete m_vertexBuffer;
	delete m_vertexArray;
}

void RendererManager::Init()
{ 
	// Sprite Rendering.
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

	// ParticleRenderering.
	{
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

		int offset = 0;
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
}

void RendererManager::Begin()
{
	// ------------------------ Sprites ------------------------
	m_verticesPtr = m_verticesBase;
	m_indexCount = 0;

	// Sprite Renderer component.
	{
		SpriteRenderer* sprite = ComponentManager::Instance()->GetComponentVector<SpriteRenderer>();
		entId count = ComponentManager::Instance()->GetComponentCount(ComponentTypes::SpriteRenderer);
		for (entId i = 0; i < count; i++)
		{
			AddRenderableToRenderBuffer((IRenderable*)&sprite[i], sprite[i].GetEntity());
		}
	}
	// UI Sprites component.
	{
		UiSprite* uiSprite = ComponentManager::Instance()->GetComponentVector<UiSprite>();
		entId count = ComponentManager::Instance()->GetComponentCount(ComponentTypes::UiSprite);
		for (entId i = 0; i < count; i++)
		{
			AddRenderableToRenderBuffer((IRenderable*)&uiSprite[i], uiSprite[i].GetEntity());
		}
	}
	// UI Buttons component.
	{
		UiButton* uiButton = ComponentManager::Instance()->GetComponentVector<UiButton>();
		entId count = ComponentManager::Instance()->GetComponentCount(ComponentTypes::UiButton);
		for (entId i = 0; i < count; i++)
		{
			AddRenderableToRenderBuffer((IRenderable*)&uiButton[i], uiButton[i].GetEntity());
		}
	}

	// ------------------------ Particle System ------------------------
	m_particleVerticesPtr = m_particleVerticesBase;
	m_particleIndexCount = 0;

	uint32 numParticles = ParticleManager::Instance()->m_particleIndex;
	std::vector<ParticleManager::Particle> particles = ParticleManager::Instance()->m_particles;
	for (uint32 i = 0; i < numParticles; i++)
	{
		float size = particles[i].size;

		m_particleVerticesPtr->position = vec3(particles[i].position - size, 0.0f);
		m_particleVerticesPtr->color = particles[i].color;
		m_particleVerticesPtr++;

		m_particleVerticesPtr->position = vec3(particles[i].position.x + size, particles[i].position.y - size, 0.0f);
		m_particleVerticesPtr->color = particles[i].color;
		m_particleVerticesPtr++;

		m_particleVerticesPtr->position = vec3(particles[i].position + size, 0.0f);
		m_particleVerticesPtr->color = particles[i].color;
		m_particleVerticesPtr++;

		m_particleVerticesPtr->position = vec3(particles[i].position.x - size, particles[i].position.y + size, 0.0f);
		m_particleVerticesPtr->color = particles[i].color;
		m_particleVerticesPtr++;

		m_particleIndexCount += 6;
	}
}

void RendererManager::End()
{
	uint64 size = (ubyte*)m_verticesPtr - (ubyte*)m_verticesBase;
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

void RendererManager::AddRenderableToRenderBuffer(IRenderable* renderable, Entity* entity)
{
	Transform* transform = entity->GetComponent<Transform>();

	if (!entity->IsActive())
	{
		return;
	}

	vec2 position = transform->GetPosition();

	Texture* texture = renderable->GetTexture();
	texture = texture ? texture : TextureManager::Instance()->GetTexture(EngineTextureIndex::NoTexture);

	float textureIndex = -1.0f;
	for (uint32 tex = 0; tex < m_textureSlotIndex; tex++)
	{
		if (m_textureSlots[tex] == texture)
		{
			textureIndex = (float)tex;
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
	vec2 halfSize = renderable->m_size * 0.5f;

	float angle = transform->GetRotation();

	float sina = glm::sin(glm::radians(angle));
	float cosa = glm::cos(glm::radians(angle));

	float xsina = halfSize.x * sina;
	float xcosa = halfSize.x * cosa;
	float ysina = halfSize.y * sina;
	float ycosa = halfSize.y * cosa;

	vec2 s1 = vec2( xcosa - ysina,  ycosa + xsina);
	vec2 s2 = vec2( xcosa + ysina, -ycosa + xsina);
	vec2 s3 = vec2(-xcosa - ysina,  ycosa - xsina);

	float layer = (float)(renderable->m_layer) / 256.0f;

	bool flipVertically = renderable->m_flipY;

	// uv calculations.
	vec2 botL(renderable->m_uvRect.x, renderable->m_uvRect.y);
	vec2 botR(renderable->m_uvRect.x + renderable->m_uvRect.z, renderable->m_uvRect.y);
	vec2 topR(renderable->m_uvRect.x + renderable->m_uvRect.z, renderable->m_uvRect.y + renderable->m_uvRect.w);
	vec2 topL(renderable->m_uvRect.x, renderable->m_uvRect.y + renderable->m_uvRect.w);

	// Vertices.
	m_verticesPtr->position = vec3(position - s1, layer);
	m_verticesPtr->uvCoord = (flipVertically ? botR : botL);
	m_verticesPtr->textureId = textureIndex;
	m_verticesPtr++;

	m_verticesPtr->position = vec3(position.x + s2.x, position.y + s2.y, layer);
	m_verticesPtr->uvCoord = (flipVertically ? botL : botR);
	m_verticesPtr->textureId = textureIndex;
	m_verticesPtr++;

	m_verticesPtr->position = vec3(position + s1, layer);
	m_verticesPtr->uvCoord = (flipVertically ? topL : topR);
	m_verticesPtr->textureId = textureIndex;
	m_verticesPtr++;

	m_verticesPtr->position = vec3(position.x + s3.x, position.y + s3.y, layer);
	m_verticesPtr->uvCoord = (flipVertically ? topR : topL);
	m_verticesPtr->textureId = textureIndex;
	m_verticesPtr++;

	m_indexCount += 6;
}

} // Namespace jci.