#pragma once
#include "pch.h"

#include "IComponent.h"
#include "Graphics/Renderer/IRenderable.h"

#include "UI/AnchorPoints.h"

namespace jci {

/***
=========================================================================================
UI_Sprite (COMPONENT):
	A component to add a sprite on the screen.
	UI Element therefore relative to the camera/anchor point.
=========================================================================================
*/
class UiSprite : public IComponent, public IRenderable
{
	friend class UiManager;
public:
	REGISTER_COMPONENT(ComponentTypes::UiSprite);

	UiSprite() = default;
	~UiSprite() = default;

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; m_layer = 200; }
	inline void OnComponentRemove() final { }

	/***
	* Get the anchor point of the UI element.
	*
	*/
	inline AnchorPoints	GetAnchorPoint() const { return m_anchorPoint; }
	/***
	* Set the padding of the UI element.
	* Note: Padding is the offset from the anchor point.
	*/
	inline vec2	 GetPadding() const { return m_padding; }

	/***
	* Set the anchor point of the UI element.
	*
	*/
	inline void SetAnchorPoint(AnchorPoints anchorPoint) { m_anchorPoint = anchorPoint; }
	/***
	* Set the padding of the UI element.
	* Note: Padding is the offset from the anchor point.
	*/
	inline void SetPadding(vec2 padding)	{ m_padding = padding; }
	/***
	* Set the texture render percentage.
	* This is how much of the texture should be used. Example of use is in a heatlh bar.
	*/
	inline void SetTextureRenderPercentage(float percent) { m_renderPercent = abs(percent); CalculateUV(0); }
	/***
	* Set the size of the size of the UI Sprite.
	* 
	*/
	inline void SetSize(vec2 size) final { m_size = size; m_originalSize = size; }

	inline UiSprite& operator=(UiSprite& other) noexcept
	{
		memcpy(this, &other, sizeof(UiSprite));

		return *this;
	}
private:
	Entity* m_entity = nullptr;
	entId m_id		 = invalid_id;

	AnchorPoints m_anchorPoint = AnchorPoints::Middle;

	vec2 m_padding			= vec2(0.0f);
	float m_renderPercent	= 1.0f;
	vec2 m_originalSize		= vec2(1.0f);
};

} // Namespace jci.