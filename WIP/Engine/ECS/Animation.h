#pragma once

#include "IComponent.h"
#include "Time/Timer.h"

#include "Graphics/Texture/TextureManager.h"
#include "Graphics/Renderer/RendererManager.h"

namespace jci {

class Animation : public IComponent
{
	friend class AnimationManager;
public:
	REGISTER_COMPONENT(ComponentTypes::Animation);

	void OnComponentAdd(Entity* entity) final;
	inline void OnComponentRemove() final { RendererManager::Instance()->RemoveQuadFromQueue(&m_quad); }

	inline uint32 GetAnimationIndex() const { return m_animationCount; }

	inline void SetAnimationCount(uint32 count) { m_animationCount = count; m_animationIndex = 0; }

	inline void SetTimeBetweenFrames(float time) { m_frameTimer.SetTime(time); }

	inline vec2 GetSize() const { return m_size; }
	inline Texture* GetTexture() const { return m_quad.texture; }
	inline bool GetVerticalFlip() const { return m_quad.flipVertically; }
	inline uint8 GetLayer() const { return m_quad.layer; }

	inline void SetSize(vec2 size) { m_size; }
	inline void SetTexture(Texture* texture) { m_quad.texture = texture; }
	inline void SetTexture(uint32 textureId, uint32 index = 0) { m_quad.texture = TextureManager::Instance()->GetTexture(textureId); SetTextureIndex(index); }
	inline void SetVerticalFlip(bool flip) { m_quad.flipVertically = flip; }
	inline void SetLayer(uint8 layer) { m_quad.layer = layer; }
	inline void SetTextureIndex(uint32 index) { ASSERT(m_quad.texture, "Invalid texture to get uv Rect."); m_quad.uvRect = m_quad.texture->GetUVRect(index); }

	inline Animation& operator=(Animation& other) noexcept
	{
		m_id = std::move(other.m_id);
		m_entity = std::move(other.m_entity);
		m_quad = std::move(other.m_quad);

		return *this;
	}
private:
	Entity* m_entity	= nullptr;
	entId	m_id		= invalid_id;

	vec2	m_size				= vec2(1.0f);
	Timer	m_frameTimer		= Timer(0.0f, true);
	uint32	m_animationIndex	= 0;
	uint32	m_animationCount	= 1;

	Quad	m_quad;
};

} // Namespace jci.