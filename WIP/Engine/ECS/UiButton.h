/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once
#include "pch.h"

#include "IComponent.h"
#include "Graphics/Renderer/IRenderable.h"

#include "UI/AnchorPoints.h"

namespace jci {
/***
=========================================================================================
IBUTTON_METHODS (CALLBACK):
	Interface to create the callback methods of a Button.
=========================================================================================
*/
__interface IButtonMethods
{
public:
	void OnButtonHover() = 0;
	void OnButtonPress() = 0;
};

/***
=========================================================================================
UI_BUTTON (COMPONENT):
	A component to add a button on the screen.
	UI Element therefore relative to the camera/anchor point.
=========================================================================================
*/
class UiButton : public IComponent, public IRenderable
{
	friend class UiManager;
public:
	REGISTER_COMPONENT(ComponentTypes::UiButton);

	UiButton() = default;
	~UiButton() = default;

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; m_layer = 200; }
	inline void OnComponentRemove() final { }

	/***
	* Get the button callback methods.
	*
	*/
	inline IButtonMethods*	GetButtonMethods()	const { return m_buttonMethods; }
	/***
	* Get the anchor point of the UI element.
	*
	*/
	inline AnchorPoints		GetAnchorPoint()	const { return m_anchorPoint; }

	/***
	* Get the padding (offset from the anchor point).
	*
	*/
	inline vec2		GetPadding()	const { return m_padding; }
	/***
	* Get if the button is pressed or not.
	*
	*/
	inline bool		GetPressed()	const { return m_pressed; }

	/***
	* Set the button callback methods.
	* These callbacks will be called when the button hovers/is pressed.
	*/
	inline void SetButtonMethods(IButtonMethods* buttonMethods) { m_buttonMethods = buttonMethods; }
	/***
	* Set the anchor point of the UI element.
	*
	*/
	inline void SetAnchorPoint(AnchorPoints anchorPoint)		{ m_anchorPoint = anchorPoint; }
	/***
	* Set the padding of the UI element.
	* Note: Padding is the offset from the anchor point.
	*/
	inline void SetPadding(vec2 padding)	{ m_padding = padding; }

	inline UiButton& operator=(UiButton& other) noexcept
	{
		memcpy(this, &other, sizeof(UiButton));

		return *this;
	}
private:
	Entity* m_entity = nullptr;
	entId m_id		 = invalid_id;

	IButtonMethods* m_buttonMethods	= nullptr;
	AnchorPoints	m_anchorPoint	= AnchorPoints::Middle;

	vec2 m_padding	= vec2(0.0f);
	bool m_pressed	= false;
};

} // Namespace jci.