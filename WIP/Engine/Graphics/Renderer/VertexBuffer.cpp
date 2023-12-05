#include "pch.h"
#include "VertexBuffer.h"

#include "Vertex.h"

namespace jci
{

VertexBuffer::VertexBuffer(uint32 size)
{
	glCreateBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(float* vertices, uint32 size)
{
	glCreateBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, uint32 size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

} // Namespace jci.