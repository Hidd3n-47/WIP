#pragma once

#include "IComponent.h"
#include "Graphics/Renderer/IRenderable.h"

#include "UI/AnchorPoints.h"

namespace jci {

/***
=========================================================================================
TEXT_ALIGNMENT (TEXT_ALIGNMENT):
	The alignment of the text.
=========================================================================================
*/
enum class TextAlignment
{
	Left,
	Right
};

/***
=========================================================================================
GLYPH (FONT_CHARACTER):
	A single character used for font renderering.
=========================================================================================
*/
struct Glyph
{
	Glyph() = default;
	Glyph(vec2 position, vec2 size, uint32 textureIndex) : position(position), size(size), textureIndex(textureIndex) { /* Empty. */ }

	vec2 position;
	vec2 size;
	uint32 textureIndex;
};

/***
=========================================================================================
UI_TEXT (COMPONENT):
	A component to add font renderering.
	UI Element therefore relative to the camera/anchor point.
	Note:
		The current UI Font renderering is for numbers only.
		Not implemented for strings of text.
=========================================================================================
*/
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

	/***
	* Get the padding of the font rendering.
	* Note: Padding is offset from anchor point.
	*/
	inline vec2			GetPadding()		const { return m_padding; }
	/***
	* Get the font size.
	*
	*/
	inline uint8		GetFontSize()		const { return m_fontSize; }
	/***
	* Get the anchor point of the UI element.
	*
	*/
	inline AnchorPoints	GetAnchorPoint()	const { return m_anchorPoint; }

	/***
	* Get the text of the UI element.
	*
	*/
	inline uint32 GetText()	const { return m_text; }

	/***
	* Set the anchor point of the UI element.
	*
	*/
	inline void SetAnchorPoint(AnchorPoints anchorPoint) { m_anchorPoint = anchorPoint; }
	/***
	* Set the text of the UI element.
	*
	*/
	inline void SetText(uint32 text)			 { m_text = text; m_recalculateGlyphs = true; }
	/***
	* Set the size of the font to be displayed.
	* 
	*/
	inline void SetFontSize(uint8 size)			 { m_fontSize = size; m_recalculateGlyphs = true;}
	/***
	* Set the padding of the UI element.
	* Note: Padding is the offset from the anchor point.
	*/
	inline void SetPadding(vec2 padding)		 { m_padding = padding; }
	/***
	* Set the text of the font as well as the size the font should be rendered at.
	*
	*/
	inline void SetText(uint32 text, uint8 size) { m_text = text; m_fontSize = size; m_recalculateGlyphs = true; }
	/***
	* Set the text alignment of the font.
	* Alignments: Left, Right.
	*/
	inline void SetTextAlign(TextAlignment align){ m_textAlign = align; m_recalculateGlyphs = true; }

	inline UiText& operator=(UiText& other) noexcept
	{
		m_entity = other.m_entity;
		m_id	 = other.m_id;

		m_text				= other.m_text;
		m_recalculateGlyphs = other.m_recalculateGlyphs;

		m_anchorPoint = other.m_anchorPoint;
		
		m_padding = other.m_padding;
		m_fontSize = other.m_fontSize;

		m_glyphs = other.m_glyphs;

		m_texture	= other.m_texture;
		m_uvRect	= other.m_uvRect;
		m_size		= other.m_size;
		m_layer		= other.m_layer;
		m_flipY		= other.m_flipY;

		return *this;
	}
private:
	Entity* m_entity = nullptr;
	entId m_id = invalid_id;

	uint32 m_text = 0;
	bool m_recalculateGlyphs = false;

	AnchorPoints	m_anchorPoint = AnchorPoints::Middle;
	TextAlignment	m_textAlign   = TextAlignment::Left;

	vec2 m_padding = vec2(0.0f);
	uint8 m_fontSize = 12;

	std::vector<Glyph> m_glyphs;
};

} // Namespace jci.