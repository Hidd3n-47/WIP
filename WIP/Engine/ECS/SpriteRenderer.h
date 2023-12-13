#pragma once

#include "IComponent.h"

#include "Graphics/Texture/TextureManager.h"

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
	inline Texture* GetTexture() const { return m_texture; }
	inline bool GetVerticalFlip() const { return m_verticalFlip; }
	inline uint8 GetLayer() const { return m_layer; }


	inline void SetSize(vec2 size) { m_size = size; }
	inline void SetTexture(Texture* texture) { m_texture = texture; }
	inline void SetTexture(uint32 textureId) { m_texture = TextureManager::Instance()->GetTexture(textureId); }
	inline void SetVerticalFlip(bool flip) { m_verticalFlip = flip; }
	inline void SetLayer(uint8 layer) { m_layer = layer; }

	inline SpriteRenderer& operator=(SpriteRenderer& other) noexcept
	{
		m_id = std::move(other.m_id);
		m_entity = std::move(other.m_entity);
		m_size = std::move(other.m_size);
		m_texture = std::move(other.m_texture);
		return *this;
	}
private:
	Entity*		m_entity		= nullptr;
	Texture*	m_texture		= nullptr;
	vec2		m_size			= vec2(1.0f);
	entId		m_id			= invalid_id;
	uint8		m_layer			= 0;
	bool		m_verticalFlip	= false;
};

} // Namespace jci.