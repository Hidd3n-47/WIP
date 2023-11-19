#pragma once

#include "IComponent.h"

#include "Renderer/Texture.h"

namespace jci {

class SpriteRenderer : public IComponent
{
public:
	SpriteRenderer() = default;
	~SpriteRenderer() = default;

	virtual void OnComponentAdd(GameObject* gameObject) final;
	virtual void OnComponentRemove() final;

	inline virtual GameObject* GetGameObject() final { return m_gameObject; }

	inline static uint16 GetIdMask() { return 1 << (int)ComponentTypes::SpriteRenderer; }

	inline vec2 GetPosition() const { return m_position; }
	inline vec2 GetSize() const { return m_size; }
	inline vec3 GetColor() const { return m_color; }
	inline Texture* GetTexture() const { return m_texture; }
	inline void SetPosition(vec2 position) { m_position = position; }
	inline void SetSize(vec2 size) { m_size = size; }
	inline void SetColor(vec3 color) { m_color = color; }
private:
	GameObject* m_gameObject	= nullptr;
	vec2 m_position				= vec2(0.0f);
	vec2 m_size					= vec2(1.0f);
	vec3 m_color				= vec3(1.0f, 0.0f, 1.0f);
	Texture* m_texture			= nullptr;
};

} // Namespace jci.