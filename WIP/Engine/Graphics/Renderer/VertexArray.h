#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace jci {

class VertexArray
{
public:
	VertexArray();
	inline ~VertexArray() { delete m_indexBuffer; glDeleteVertexArrays(1, &m_id); }

	void Bind() const;
	inline void Unbind() const { glBindVertexArray(0); }

	void SetVertexBuffer(VertexBuffer* vertexBuffer);
	void SetIndexBuffer(uint32* indices, uint32 count);
private:
	uint32 m_id;

	VertexBuffer* m_vertBuffer;
	IndexBuffer* m_indexBuffer;
};

} // Namespace jci.