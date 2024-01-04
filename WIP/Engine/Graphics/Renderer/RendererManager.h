#pragma once

namespace jci {

class SpriteRenderer;
class VertexArray;
class VertexBuffer;
class Shader;
class Texture;
struct Vertex;

struct Quad
{
	inline Quad() = default;
	inline Quad(vec2* size, vec4 uvRect, vec2* position, float* rotation, Texture* texture, bool* active, uint8 layer, bool flipVertically) :
				size(size),
				uvRect(uvRect),	
				position(position),
				rotation(rotation),
				texture(texture),
				layer(layer),
				flipVertically(flipVertically)
	{ 
		/* Empty. */ 
	}
	
	vec2*		size				= nullptr;
	vec4		uvRect				= vec4(0.0f, 0.0f, 1.0f, 1.0f);
	vec2*		position			= nullptr;
	float*		rotation			= nullptr;
	Texture*	texture				= nullptr;
	bool*		active				= nullptr;
	uint8		layer				= 0;
	bool		flipVertically		= false;
};

struct ParticleVertex
{
	inline ParticleVertex() = default;
	inline ParticleVertex(vec2 position, vec4 color) : position(vec3(position, 0.0f)), color(color) { /* Empty. */ }

	vec3 position = vec3(0.0f);
	vec4 color = vec4(1.0f);
};

struct UiVertex
{
	inline UiVertex() = default;
	inline UiVertex(vec2 position, vec4 color, vec2 uv, float textureIndex) : position(position), color(color), uv(uv), textureIndex(textureIndex) { }

	vec2 position = vec2(0.0f);
	vec4 color = vec4(1.0f);
	vec2 uv = vec2(0.0f);
	float textureIndex = 0.0f;
};

class RendererManager
{
public:
	inline static RendererManager* Instance() { return m_instance == nullptr ? m_instance = new RendererManager() : m_instance; }

	void AddQuadToQueue(Quad* quad);
	void RemoveQuadFromQueue(Quad* quad);

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

	std::vector<Quad*> m_quads;

	// Sprite Renderering.
	VertexBuffer* m_vertexBuffer	= nullptr;
	VertexArray* m_vertexArray		= nullptr;
	Vertex* m_verticesBase			= nullptr;
	Vertex* m_verticesPtr			= nullptr;
	Shader* m_shader				= nullptr;

	// Particle Rendering.
	VertexBuffer* m_particleVertexBuffer	= nullptr;
	VertexArray* m_particleVertexArray		= nullptr;
	ParticleVertex* m_particleVerticesBase	= nullptr;
	ParticleVertex* m_particleVerticesPtr	= nullptr;
	Shader* m_particleShader				= nullptr;

	// UI Rendering.
	VertexBuffer* m_uiVertexBuffer	= nullptr;
	VertexArray* m_uiVertexArray	= nullptr;
	UiVertex* m_uiVerticesBase		= nullptr;
	UiVertex* m_uiVerticesPtr		= nullptr;
	Shader* m_uiShader				= nullptr;

	// Textures.
	std::array<Texture*, MAX_TEXTURE_SLOTS> m_textureSlots;
	uint32 m_textureSlotIndex = 0;

	// Index Count.
	uint32 m_indexCount = 0;
	uint32 m_particleIndexCount = 0;
	uint32 m_uiIndexCount = 0;
};

} // Namespace jci.