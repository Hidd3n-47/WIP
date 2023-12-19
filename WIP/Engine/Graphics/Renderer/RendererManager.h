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
	inline Quad(vec2* size, vec4 uvRect, vec2* position, float* rotation, Texture* texture, uint8 layer, bool flipVertically) : 
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
	uint8		layer				= 0;
	bool		flipVertically		= false;
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

	const uint32 MAX_QUADS = (MAX_ENTITIES - 1) * 2;
	static const uint32 MAX_TEXTURE_SLOTS = 32;

	inline void SetLightPosition(vec2* lightPos) { m_lightPosition = lightPos; }
private:
	RendererManager() = default;
	~RendererManager() = default;

	static RendererManager* m_instance;

	std::vector<Quad*> m_quads;

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