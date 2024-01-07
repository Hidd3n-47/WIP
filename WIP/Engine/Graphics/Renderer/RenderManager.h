/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once

#include "ECS/ComponentTypes.h"

namespace jci {

class Entity;
class IRenderable;
class SpriteRenderer;
class VertexArray;
class VertexBuffer;
class Shader;
class Texture;
struct Vertex;
struct ParticleVertex;

class RendererManager
{
public:
	inline static RendererManager* Instance() { return m_instance == nullptr ? m_instance = new RendererManager() : m_instance; }

	void Init();

	void Begin();
	void End();
	void Flush();

	inline void Destroy() { delete m_instance; }

	// Max quads is number of components that can have quads: 1) SpriteRenderer, 2) UiButton, 3) UiSprite.
	const uint32 MAX_QUADS = (MAX_ENTITIES - 1) * 3;
	static const uint32 MAX_TEXTURE_SLOTS = 32;
private:
	RendererManager() = default;
	~RendererManager();

	static RendererManager* m_instance;

	// Sprite Renderering.
	VertexBuffer*	m_vertexBuffer	= nullptr;
	VertexArray*	m_vertexArray	= nullptr;
	Vertex*			m_verticesBase	= nullptr;
	Vertex*			m_verticesPtr	= nullptr;
	Shader*			m_shader		= nullptr;

	// Particle Rendering.
	VertexBuffer*	m_particleVertexBuffer	= nullptr;
	VertexArray*	m_particleVertexArray	= nullptr;
	ParticleVertex* m_particleVerticesBase	= nullptr;
	ParticleVertex* m_particleVerticesPtr	= nullptr;
	Shader*			m_particleShader		= nullptr;

	// Textures.
	std::array<Texture*, MAX_TEXTURE_SLOTS> m_textureSlots = { };
	uint32 m_textureSlotIndex = 0;

	// Index Count.
	uint32 m_indexCount = 0;
	uint32 m_particleIndexCount = 0;
	uint32 m_uiIndexCount = 0;

	void AddRenderableToRenderBuffer(IRenderable* renderable, Entity* entity);
	void AddToRenderQueue(vec2 position, Texture* texture, vec2 halfSize, float angle, float layer, bool flipY, vec4 uvRect);
};

} // Namespace jci.