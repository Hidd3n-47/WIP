/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#include "pch.h"
#include "IndexBuffer.h"

namespace jci
{

IndexBuffer::IndexBuffer(uint32 count)
{
	glCreateBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), nullptr, GL_DYNAMIC_DRAW);
}

IndexBuffer::IndexBuffer(uint32* indices, uint32 count)
{
	glCreateBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // Namespace jci.