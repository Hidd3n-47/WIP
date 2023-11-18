#pragma once

namespace jci {

class VertexBuffer
{
public:
	VertexBuffer(float* vertices, uint32 size);
	~VertexBuffer();

	void Bind();
	void Unbind();
private:
	uint32 m_id;
};

} // Namespace jci.