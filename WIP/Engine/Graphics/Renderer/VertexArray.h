#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace jci {

class VertexArray
{
public:
	VertexArray();
	inline ~VertexArray() { glDeleteVertexArrays(1, &m_id); } // Question -> Clean up index buffer and vertex Buffer.

	inline void Bind() const { /*m_vertBuffer->Bind(); m_indexBuffer->Bind();*/ glBindVertexArray(m_id); }
	inline void Unbind() const { glBindVertexArray(0); }

	void SetVertexBuffer(VertexBuffer* vertexBuffer);
	void SetIndexBuffer(uint32* indices, uint32 count);
private:
	uint32 m_id;

	VertexBuffer* m_vertBuffer;
	IndexBuffer* m_indexBuffer;
};

} // Namespace jci.