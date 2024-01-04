#pragma once

#include "IComponent.h"

#include "Graphics/Texture/TextureManager.h"
#include "Graphics/Renderer/RendererManager.h"

namespace jci {

class Texture;

class SpriteRenderer : public IComponent
{
public:
	REGISTER_COMPONENT(ComponentTypes::SpriteRenderer);

	SpriteRenderer() = default;
	~SpriteRenderer() = default;

	virtual void OnComponentAdd(Entity* entity) final;
	virtual void OnComponentRemove() final;

	inline vec2 GetSize() const { return m_size; }
	inline Texture* GetTexture() const { return m_quad.texture; }
	inline bool GetVerticalFlip() const { return m_quad.flipVertically; }
	inline uint8 GetLayer() const { return m_quad.layer; }

	inline void SetSize(vec2 size) { m_size = size; }
	inline void SetRotation(float rotation) { *m_quad.rotation = rotation; }
	inline void SetTexture(Texture* texture) { m_quad.texture = texture; }
	inline void SetTexture(Texture* texture, uint8 layer) { m_quad.texture = texture; m_quad.layer = layer; }
	inline void SetTexture(uint32 textureId, uint32 index = 0) { m_quad.texture = TextureManager::Instance()->GetTexture(textureId); SetTextureIndex(index); }
	inline void SetVerticalFlip(bool flip) { m_quad.flipVertically = flip; }
	inline void SetLayer(uint8 layer) { m_quad.layer = layer; }
	inline void SetTextureIndex(uint32 index) { ASSERT(m_quad.texture, "Invalid texture to get uv Rect."); m_quad.uvRect = m_quad.texture->GetUVRect(index); }

	inline SpriteRenderer& operator=(SpriteRenderer& other) noexcept
	{
		m_id = std::move(other.m_id);
		m_entity = std::move(other.m_entity);
		m_quad = std::move(other.m_quad);
		return *this;
	}
private:
	Entity*		m_entity		= nullptr;
	entId		m_id			= invalid_id;
	vec2		m_size			= vec2(1.0f);
	Quad		m_quad;
};

} // Namespace jci.