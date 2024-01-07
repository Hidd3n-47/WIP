/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once
#include "pch.h"

#include "Graphics/Texture/TextureManager.h"

namespace jci {


class IRenderable
{
	friend class RendererManager;
public:
	virtual ~IRenderable() = default;

	inline void CalculateUV(uint32 textureIndex) { m_uvRect = m_texture->GetUVRect(textureIndex);  }

	//Accessors.
	inline Texture* GetTexture() const	{ return m_texture; }
	inline vec4		GetUvRect()	 const	{ return m_uvRect; }
	inline vec2		GetSize()	 const	{ return m_size; }
	inline uint8	GetLayer()	 const	{ return m_layer; }
	inline bool		GetFlipY()	 const	{ return m_flipY; }

	// Mutators.
	inline void SetTexture(Texture* texture) { m_texture = texture; }
	inline void SetTexture(uint32 textureId) { m_texture = TextureManager::Instance()->GetTexture(textureId); }
	inline void SetLayer(uint8 layer)		 { m_layer = layer; }
	inline void SetFlipY(bool flipY)		 { m_flipY = flipY; }
	virtual void SetSize(vec2 size)			 { m_size = size; }
protected:
	Texture*	m_texture = nullptr;
	vec4		m_uvRect = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	vec2		m_size = vec2(1.0f);
	uint8		m_layer = 0;
	bool		m_flipY = false;
};

} // Namespace jci.