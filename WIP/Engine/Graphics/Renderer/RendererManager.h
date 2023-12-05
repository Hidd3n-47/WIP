#pragma once

namespace jci {

class SpriteRenderer;
class VertexArray;
class VertexBuffer;
class Vertex;
class Shader;
class Texture;

struct RenderData
{
	const uint32 MAX_QUADS = 10000;
	static const uint32 MAX_TEXTURE_SLOTS = 32;

	VertexArray* vertexArray;
	VertexBuffer* vertexBuffer;
	Shader* shader;

	uint32 indexCount = 0;

	Vertex* verticesBase = nullptr;
	Vertex* verticesPtr = nullptr;

	std::array<Texture*, MAX_TEXTURE_SLOTS> textureSlots;
	uint32 textureSlotIndex = 0;
};

class RendererManager
{
public:
	inline static RendererManager* Instance() { return m_instance == nullptr ? m_instance = new RendererManager() : m_instance; }

	void AddQuadToQueue(SpriteRenderer* spriteRenderer);
	void RemoveQuadFromQueue(SpriteRenderer* spriteRenderer);

	void Init();
	void Begin();

	void Update();

	void End();
	void Flush();

	inline void Destroy() { delete m_instance; }

private:
	RendererManager() = default;
	~RendererManager() = default;

	static RendererManager* m_instance;

	RenderData m_renderData;

	//std::vector<Quad> m_quads;
	std::vector<SpriteRenderer*> m_quads;
};

} // Namespace jci.