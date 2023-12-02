#pragma once

namespace jci {

class Texture
{
public:
	Texture() = default;
	Texture(const std::string& filePath);
	~Texture();

	void Bind(uint32 slot = 0) const;
	void Unbind() const;

	inline uint32 GetId() const { return m_id; }
private:
	uint32 m_id = 0;
	std::string m_filePath;
	ubyte* m_localBuffer = nullptr;
	int m_width = 0;
	int m_height = 0;
	int m_bpp = 0;
};

} // Namespace jci.