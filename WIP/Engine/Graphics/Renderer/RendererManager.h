#pragma once

namespace jci {

class SpriteRenderer;

class RendererManager
{
public:
	inline static RendererManager* Instance() { return m_instance == nullptr ? m_instance = new RendererManager() : m_instance; }

	void AddQuadToQueue(SpriteRenderer* spriteRenderer);
	void RemoveQuadFromQueue(SpriteRenderer* spriteRenderer);

	void RenderUpdate();

	inline void Destroy() { delete m_instance; }

private:
	RendererManager() = default;
	~RendererManager() = default;

	static RendererManager* m_instance;

	//std::vector<Quad> m_quads;
	std::vector<SpriteRenderer*> m_quads;
};

} // Namespace jci.