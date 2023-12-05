#pragma once

#include "IComponent.h"

#include "Graphics/Texture/TextureManager.h"

namespace jci {

class Texture;

class SpriteRenderer : public IComponent
{
public:
	SpriteRenderer() = default;
	~SpriteRenderer() = default;

	virtual void OnComponentAdd(Entity* entity) final;
	virtual void OnComponentRemove() final;

	inline virtual Entity* GetEntity() final { return m_entity; }

	COMPONENT(ComponentTypes::SpriteRenderer);

	inline vec2 GetSize() const { return m_size; }
	inline vec3 GetColor() const { return m_color; }
	inline Texture* GetTexture() const { return m_texture; }
	inline void SetSize(vec2 size) { m_size = size; }
	inline void SetColor(vec3 color) { m_color = color; }
	inline void SetTexture(Texture* texture) { m_texture = texture; }
	inline void SetTexture(uint32 textureId) { m_texture = TextureManager::Instance()->GetTexture(textureId); }
private:
	Entity*		m_entity		= nullptr;
	vec2		m_size			= vec2(1.0f);
	vec3		m_color			= vec3(1.0f, 1.0f, 1.0f);
	Texture*	m_texture		= nullptr;
};

} // Namespace jci.