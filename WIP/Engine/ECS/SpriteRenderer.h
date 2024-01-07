/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once

#include "IComponent.h"
#include "Graphics/Renderer/IRenderable.h"


namespace jci {

class Texture;

class SpriteRenderer : public IComponent, public IRenderable
{
public:
	REGISTER_COMPONENT(ComponentTypes::SpriteRenderer);

	SpriteRenderer() = default;
	~SpriteRenderer() = default;

	inline virtual void OnComponentAdd(Entity* entity) final { m_entity = entity; }
	inline virtual void OnComponentRemove() final { }

	inline SpriteRenderer& operator=(SpriteRenderer& other) noexcept
	{
		memcpy(this, &other, sizeof(SpriteRenderer));

		return *this;
	}
private:
	Entity*		m_entity		= nullptr;
	entId		m_id			= invalid_id;
};

} // Namespace jci.