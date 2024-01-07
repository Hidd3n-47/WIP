/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once

namespace jci {

class IndexBuffer
{
public:
	IndexBuffer(uint32 count);
	IndexBuffer(uint32* indices, uint32 count);
	~IndexBuffer();
	void Bind();
	void Unbind();
private:
	uint32 m_id;
};

} // Namespace jci.