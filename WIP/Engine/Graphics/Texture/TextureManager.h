#pragma once

#include "Texture.h"

namespace jci {

enum class EngineTextureIndex
{
	NoTexture,
	Dbg_Box,
	Dbg_Circle,
	Count
};

class TextureManager
{
public:
	inline static TextureManager* Instance() { return m_instance == nullptr ? m_instance = new TextureManager() : m_instance; }

	void Init();

	uint32 CreateTexture(const std::string& filePath, uint32 x = 1, uint32 y = 1);

	Texture* GetTexture(uint32 id);
	inline Texture* GetTexture(EngineTextureIndex id) { return GetTexture((uint32)id); }

	inline void RemoveTexture(uint32 id) { ASSERT(id >= (uint32)EngineTextureIndex::Count, "Cannot remove engine default textures.");  m_textures.erase(id); }

private:
	TextureManager()	= default;
	~TextureManager()	= default;

	static TextureManager* m_instance;

	std::unordered_map<uint32, Texture*> m_textures;

	uint32	m_index = 0;
};

} // Namespace jci.