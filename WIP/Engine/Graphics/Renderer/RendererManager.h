#pragma once

namespace jci {

class SpriteRenderer;
class VertexArray;
class VertexBuffer;
class Vertex;
class Shader;
class Texture;

struct Quad
{
	inline Quad(SpriteRenderer* sr, vec2* position, float* rotation) : spriteRenderer(sr), position(position), rotation(rotation) { /* Empty. */ }
	SpriteRenderer*		spriteRenderer;
	vec2*				position;
	float*				rotation;
};

class RendererManager
{
public:
	inline static RendererManager* Instance() { return m_instance == nullptr ? m_instance = new RendererManager() : m_instance; }

	void AddQuadToQueue(SpriteRenderer* spriteRenderer);
	void RemoveQuadFromQueue(SpriteRenderer* spriteRenderer);

	void Init();
	void Begin();

	void End();
	void Flush();

	inline void Destroy() { delete m_instance; }

	const uint32 MAX_QUADS = (MAX_ENTITIES - 1) * 4;
	static const uint32 MAX_TEXTURE_SLOTS = 32;

	inline void SetLightPosition(vec2* lightPos) { m_lightPosition = lightPos; }
private:
	RendererManager() = default;
	~RendererManager() = default;

	static RendererManager* m_instance;

	std::vector<Quad> m_quads;

	VertexBuffer* m_vertexBuffer	= nullptr;
	VertexArray* m_vertexArray		= nullptr;
	Vertex* m_verticesBase			= nullptr;
	Vertex* m_verticesPtr			= nullptr;
	Shader* m_shader				= nullptr;

	std::array<Texture*, MAX_TEXTURE_SLOTS> m_textureSlots;
	uint32 textureSlotIndex = 0;
	uint32 indexCount = 0;

	vec2* m_lightPosition = nullptr;
};

} // Namespace jci.