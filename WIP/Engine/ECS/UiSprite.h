#pragma once
#include "pch.h"

#include "IComponent.h"

#include "Graphics/Renderer/IRenderable.h"
#include "Graphics/Renderer/RendererManager.h"
#include "Graphics/Texture/TextureManager.h"
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
		/*m_id		= other.m_id;
		m_entity	= other.m_entity;

		m_anchorPoint = other.m_anchorPoint;

		m_padding = other.m_padding;
		m_pressed = other.m_pressed;

		m_texture	= other.m_texture;
		m_uvRect	= other.m_uvRect;
		m_size		= other.m_size;
		m_layer		= other.m_layer;
		m_flipY		= other.m_flipY;

		m_renderPercent = other.m_renderPercent;
		m_originalSize = other.m_originalSize;

		return *this;*/
		memcpy(this, &other, sizeof(UiSprite));

		return *this;
	}
private:
	entId m_id;
	Entity* m_entity;

	AnchorPoints	m_anchorPoint	= AnchorPoints::Middle;

	vec2 m_padding	= vec2(0.0f);
	bool m_pressed	= false;
	float m_renderPercent = 1.0f;
	vec2 m_originalSize = vec2(1.0f);
};

} // Namespace jci.