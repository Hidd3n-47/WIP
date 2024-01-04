#pragma once
#include "pch.h"

#include "IComponent.h"

#include "Graphics/Renderer/IRenderable.h"
#include "Graphics/Renderer/RendererManager.h"
#include "Graphics/Texture/TextureManager.h"
#include "AnchorPoints.h"

namespace jci {

struct Quad;

class UiSprite : public IComponent, public IRenderable
{
	friend class UiManager;
public:
	REGISTER_COMPONENT(ComponentTypes::UiSprite);

	UiSprite() = default;
	~UiSprite() = default;

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; }
	inline void OnComponentRemove() final { }
	
	inline AnchorPoints		GetAnchorPoint()	const { return m_anchorPoint; }

	inline vec2		GetPadding()	const { return m_padding; }
	inline bool		GetPressed()	const { return m_pressed; }

	inline void SetAnchorPoint(AnchorPoints anchorPoint)		{ m_anchorPoint = anchorPoint; }

	inline void SetPadding(vec2 padding)	{ m_padding = padding; }

	inline UiSprite& operator=(UiSprite& other) noexcept
	{
		m_id = std::move(other.m_id);
		m_entity = std::move(other.m_entity);
		m_anchorPoint = other.m_anchorPoint;
		m_padding = std::move(other.m_padding);
		//m_size = std::move(other.m_size);
		m_pressed = other.m_pressed;

		return *this;
	}
private:
	entId m_id;
	Entity* m_entity;

	AnchorPoints	m_anchorPoint	= AnchorPoints::Middle;

	vec2 m_padding	= vec2(0.0f);
	bool m_pressed	= false;
};

} // Namespace jci.