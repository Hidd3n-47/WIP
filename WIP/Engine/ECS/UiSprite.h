#pragma once
#include "pch.h"

#include "IComponent.h"
#include "Graphics/Renderer/IRenderable.h"

#include "UI/AnchorPoints.h"

namespace jci {

class UiSprite : public IComponent, public IRenderable
{
	friend class UiManager;
public:
	REGISTER_COMPONENT(ComponentTypes::UiSprite);

	UiSprite() = default;
	~UiSprite() = default;

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; m_layer = 200; }
	inline void OnComponentRemove() final { }

	inline AnchorPoints		GetAnchorPoint()	const { return m_anchorPoint; }
	inline vec2		GetPadding()	const { return m_padding; }
	inline bool		GetPressed()	const { return m_pressed; }

	inline void SetAnchorPoint(AnchorPoints anchorPoint) { m_anchorPoint = anchorPoint; }

	inline void SetPadding(vec2 padding)	{ m_padding = padding; }
	inline void SetTextureRenderPercentage(float percent) { m_renderPercent = abs(percent); CalculateUV(0); }
	inline void SetSize(vec2 size) final { m_size = size; m_originalSize = size; }

	inline UiSprite& operator=(UiSprite& other) noexcept
	{
		memcpy(this, &other, sizeof(UiSprite));

		return *this;
	}
private:
	Entity* m_entity = nullptr;
	entId m_id = invalid_id;

	AnchorPoints	m_anchorPoint	= AnchorPoints::Middle;

	vec2 m_padding	= vec2(0.0f);
	bool m_pressed	= false;
	float m_renderPercent = 1.0f;
	vec2 m_originalSize   = vec2(1.0f);
};

} // Namespace jci.