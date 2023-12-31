/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#include "pch.h"
#include "Texture.h"

#include <stb_image/stb_image.h>

namespace jci {

Texture::Texture(const std::string& filePath, int x, int y) :
	m_filePath(filePath),
	m_x(x),
	m_y(y)
{
	stbi_set_flip_vertically_on_load(1);

	m_localBuffer = stbi_load(filePath.c_str(), &m_width, &m_height, &m_bpp, 4);

	ASSERT(m_bpp && m_width, "Failed to load texture at given filepath.");
	ASSERT(m_bpp == 4, "The engine only supports textures with 4 channels.");

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_localBuffer)
	{
		stbi_image_free(m_localBuffer);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::Bind(uint32 slot) const
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

vec4 Texture::GetUVRect(uint32 index)
{
	vec4 rect;

	float w = 1.0f / m_x;
	float h = 1.0f / m_y;

	rect.x = (index % m_x) * w;
	rect.y = (index / m_x) * h;
	rect.z = w;
	rect.w = h;

	return rect;
}

} // Namespace jci.