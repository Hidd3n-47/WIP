#pragma once

namespace jci {

class VertexBuffer
{
public:
	VertexBuffer(uint32 size);
	VertexBuffer(float* vertices, uint32 size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetData(const void* data, uint32 size);
private:
	uint32 m_id;
};

} // Namespace jci.