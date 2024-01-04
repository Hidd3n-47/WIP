#pragma once

#include "IComponent.h"

#include "Graphics/Texture/TextureManager.h"
#include "Graphics/Renderer/RendererManager.h"
#include "Graphics/Renderer/IRenderable.h"

namespace jci {

class Texture;

class SpriteRenderer : public IComponent, public IRenderable
{
	friend class RendererManager;
public:
	REGISTER_COMPONENT(ComponentTypes::SpriteRenderer);

	SpriteRenderer() = default;
	~SpriteRenderer() = default;

	virtual void OnComponentAdd(Entity* entity) final;
	virtual void OnComponentRemove() final;

	inline SpriteRenderer& operator=(SpriteRenderer& other) noexcept
	{
		m_id = other.m_id;
		m_entity = other.m_entity;
		
		m_texture = other.m_texture;
		m_uvRect = other.m_uvRect;
		m_size = other.m_size;
		m_layer = other.m_layer;
		m_flipY = other.m_flipY;

		return *this;
	}
private:
	Entity*		m_entity		= nullptr;
	entId		m_id			= invalid_id;
};

} // Namespace jci.