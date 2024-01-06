#pragma once
#include "pch.h"

#include "IComponent.h"
#include "Graphics/Renderer/IRenderable.h"

#include "UI/AnchorPoints.h"

namespace jci {

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

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; m_layer = 200; }
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
		memcpy(this, &other, sizeof(UiButton));

		return *this;
	}
private:
	Entity* m_entity = nullptr;
	entId m_id = invalid_id;

	IButtonMethods* m_buttonMethods	= nullptr;
	AnchorPoints	m_anchorPoint	= AnchorPoints::Middle;

	vec2 m_padding	= vec2(0.0f);
	bool m_pressed	= false;
};

} // Namespace jci.