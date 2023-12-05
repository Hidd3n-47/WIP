#include "pch.h"
#include "VertexArray.h"

#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace jci {

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
	glBindVertexArray(m_id);

	Bind();
}

void VertexArray::SetVertexBuffer(VertexBuffer* vertexBuffer)
{
	m_vertBuffer = vertexBuffer;

	m_vertBuffer->Bind();
}

void VertexArray::SetIndexBuffer(uint32* indices, uint32 count)
{
	delete m_indexBuffer;
	m_indexBuffer = new IndexBuffer(indices, count);
	m_indexBuffer->Bind();
}

}