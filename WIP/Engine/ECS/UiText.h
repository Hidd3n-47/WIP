#pragma once

#include "IComponent.h"
#include "Graphics/Renderer/IRenderable.h"

#include "UI/AnchorPoints.h"

namespace jci {

struct Glyph
{
	Glyph() = default;
	Glyph(vec2 position, vec2 size, uint32 textureIndex) : position(position), size(size), textureIndex(textureIndex) { /* Empty. */ }

	vec2 position;
	vec2 size;
	uint32 textureIndex;
};

class UiText : public IComponent, public IRenderable
{
	friend class UiManager;
	friend class RendererManager;
public:
	REGISTER_COMPONENT(ComponentTypes::UiText);

	UiText() = default;
	~UiText() = default;

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; m_layer = 200; }
	inline void OnComponentRemove() final { }

	inline vec2			GetPadding()		const { return m_padding; }
	inline uint8		GetFontSize()		const { return m_fontSize; }
	inline AnchorPoints	GetAnchorPoint()	const { return m_anchorPoint; }

	inline uint32 GetText()	const { return m_text; }


	inline void SetAnchorPoint(AnchorPoints anchorPoint) { m_anchorPoint = anchorPoint; }

	inline void SetText(uint32 text)			 { m_text = text; m_recalculateGlyphs = true; }
	inline void SetFontSize(uint8 size)			 { m_fontSize = size; m_recalculateGlyphs = true;}
	inline void SetPadding(vec2 padding)		 { m_padding = padding; }
	inline void SetText(uint32 text, uint8 size) { m_text = text; m_fontSize = size; m_recalculateGlyphs = true; }

	inline UiText& operator=(UiText& other) noexcept
	{
		//memcpy(this, &other, sizeof(UiText));
		m_entity = other.m_entity;
		m_id = other.m_id;

		m_text = other.m_text;
		m_recalculateGlyphs = other.m_recalculateGlyphs;

		m_anchorPoint = other.m_anchorPoint;
		
		m_padding = other.m_padding;
		m_fontSize = other.m_fontSize;

		m_glyphs = other.m_glyphs;

		return *this;
	}
private:
	Entity* m_entity = nullptr;
	entId m_id = invalid_id;

	uint32 m_text = 0;
	bool m_recalculateGlyphs = false;

	AnchorPoints	m_anchorPoint = AnchorPoints::Middle;

	vec2 m_padding = vec2(0.0f);
	uint8 m_fontSize = 12;

	std::vector<Glyph> m_glyphs;

};

} // Namespace jci.