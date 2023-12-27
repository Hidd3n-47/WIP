#pragma once
#include "pch.h"

#include "IComponent.h"

#include "Graphics/Renderer/RendererManager.h"
#include "Graphics/Texture/TextureManager.h"
#include "AnchorPoints.h"

namespace jci {

struct Quad;

__interface IButtonMethods
{
public:
	void OnButtonHover() = 0;
	void OnButtonPress() = 0;
};

class UiButton : public IComponent
{
	friend class ButtonManager;
public:
	REGISTER_COMPONENT(ComponentTypes::UiButton);

	UiButton() = default;
	~UiButton() = default;

	void OnComponentAdd(Entity* entity) final;
	void OnComponentRemove() final;

	inline IButtonMethods*	GetButtonMethods()	const { return m_buttonMethods; }
	inline AnchorPoints		GetAnchorPoint()	const { return m_anchorPoint; }

	inline vec2		GetPadding()	const { return m_padding; }
	inline vec2		GetSize()		const { return m_size; }
	inline bool		GetPressed()	const { return m_pressed; }

	inline void SetButtonMethods(IButtonMethods* buttonMethods) { m_buttonMethods = buttonMethods; }
	inline void SetTexture(uint32 textureId, uint32 index = 0)	{ m_quad.texture = TextureManager::Instance()->GetTexture(textureId); }
	inline void SetTexture(Texture* texture, uint8 layer)		{ m_quad.texture = texture; m_quad.layer = layer; }
	inline void SetAnchorPoint(AnchorPoints anchorPoint)		{ m_anchorPoint = anchorPoint; }

	inline void SetTexture(Texture* texture){ m_quad.texture = texture; }
	inline void SetPadding(vec2 padding)	{ m_padding = padding; }
	inline void SetSize(vec2 size)			{ m_size = size; }

	inline UiButton& operator=(UiButton& other) noexcept
	{
		m_id = std::move(other.m_id);
		m_entity = std::move(other.m_entity);
		m_anchorPoint = other.m_anchorPoint;
		m_padding = std::move(other.m_padding);
		m_size = std::move(other.m_size);
		m_pressed = other.m_pressed;
		m_buttonMethods = std::move(other.m_buttonMethods);

		return *this;
	}
private:
	entId m_id;
	Entity* m_entity;

	IButtonMethods* m_buttonMethods	= nullptr;
	AnchorPoints	m_anchorPoint	= AnchorPoints::Middle;

	vec2 m_position = vec2(0.0f);
	vec2 m_padding	= vec2(0.0f);
	vec2 m_size		= vec2(1.0f);
	bool m_pressed	= false;
	Quad m_quad;
};

} // Namespace jci.