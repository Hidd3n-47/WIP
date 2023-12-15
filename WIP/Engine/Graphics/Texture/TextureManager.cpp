#include "pch.h"
#include "TextureManager.h"

#include "Texture.h"

namespace jci {

TextureManager* TextureManager::m_instance = nullptr;

void TextureManager::Init()
{
	CreateTexture("Assets/Texture/dbg/no_texture.png");
	CreateTexture("Assets/Texture/dbg/dbg_box.png");
}

uint32 TextureManager::CreateTexture(const std::string& filePath, uint32 x, uint32 y)
{
	ASSERT(m_index < 32, "Max textures reached for current performance of renderer.");

	DOUT("Created texture " + filePath);
	m_textures[m_index] = new Texture(filePath, x, y);

	return m_index++;
}

Texture* TextureManager::GetTexture(uint32 id)
{
	auto item = m_textures.find(id);
	
	return item == m_textures.end() ? nullptr : item->second;
}

} // Namespace jci.