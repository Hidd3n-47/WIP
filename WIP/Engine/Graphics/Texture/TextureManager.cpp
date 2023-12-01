#include "pch.h"
#include "TextureManager.h"

#include "Texture.h"

namespace jci {

TextureManager* TextureManager::m_instance = nullptr;

void TextureManager::Init()
{
	// allocate the default textures.
	CreateTexture("Assets/Texture/dbg/no_texture.png");
	CreateTexture("Assets/Texture/dbg/dbg_box.png");
}

uint32 TextureManager::CreateTexture(const std::string& filePath)
{
	DLOG("Created texture " + filePath);
	m_textures[m_index] = new Texture(filePath);

	return m_index++;
}

Texture* TextureManager::GetTexture(uint32 id)
{
	auto item = m_textures.find(id);
	
	return item == m_textures.end() ? nullptr : item->second;
}

} // Namespace jci.