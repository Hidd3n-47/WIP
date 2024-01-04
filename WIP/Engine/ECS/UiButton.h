#pragma once
#include "pch.h"

#include "IComponent.h"

#include "Graphics/Renderer/IRenderable.h"
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

class UiButton : public IComponent, public IRenderable
{
	friend class UiManager;
public:
	REGISTER_COMPONENT(ComponentTypes::UiButton);

	UiButton() = default;
	~UiButton() = default;

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; }
	inline void OnComponentRemove() final { }

	inline IButtonMethods*	GetButtonMethods()	const { return m_buttonMethods; }
	inline AnchorPoints		GetAnchorPoint()	const { return m_anchorPoint; }

	inline vec2		GetPadding()	const { return m_padding; }
	inline bool		GetPressed()	const { return m_pressed; }

	inline void SetButtonMethods(IButtonMethods* buttonMethods) { m_buttonMethods = buttonMethods; }
	inline void SetAnchorPoint(AnchorPoints anchorPoint)		{ m_anchorPoint = anchorPoint; }

	inline void SetPadding(vec2 padding)	{ m_padding = padding; }

	inline UiButton& operator=(UiButton& other) noexcept
	{
		m_id		= other.m_id;
		m_entity	= other.m_entity;

		m_buttonMethods = other.m_buttonMethods;
		m_anchorPoint	= other.m_anchorPoint;

		m_padding = other.m_padding;
		m_pressed = other.m_pressed;

		m_texture	= other.m_texture;
		m_uvRect	= other.m_uvRect;
		m_size		= other.m_size;
		m_layer		= other.m_layer;
		m_flipY		= other.m_flipY;

		return *this;
	}
private:
	entId m_id;
	Entity* m_entity;

	IButtonMethods* m_buttonMethods	= nullptr;
	AnchorPoints	m_anchorPoint	= AnchorPoints::Middle;

	vec2 m_padding	= vec2(0.0f);
	bool m_pressed	= false;
};

} // Namespace jci.