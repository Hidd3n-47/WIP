#pragma once

namespace jci {

class Texture
{
public:
	Texture() = default;
	Texture(const std::string& filePath, int x, int y);
	~Texture();

	void Bind(uint32 slot = 0) const;
	void Unbind() const;

	vec4 GetUVRect(uint32 index);

	inline uint32 GetId() const { return m_id; }
private:
	uint32 m_id = 0;
	std::string m_filePath;
	ubyte* m_localBuffer = nullptr;
	uint32 m_x = 1;
	uint32 m_y = 1;
	int m_width = 0;
	int m_height = 0;
	int m_bpp = 0;
};

} // Namespace jci.