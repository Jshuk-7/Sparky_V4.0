#include "IndexBuffer.h"

Sparky::IndexBuffer::IndexBuffer(const IndexBufferCreateInfo& createInfo) noexcept
	:
	m_BufferId(SP_NULL),
	m_IndexCount(createInfo.indexCount),
	m_DataType(createInfo.dataType)
{
	glCreateBuffers(1, &m_BufferId);
	glNamedBufferStorage(m_BufferId, m_IndexCount * sizeof(u8), createInfo.pData, GL_DYNAMIC_STORAGE_BIT);
}

void Sparky::IndexBuffer::Destroy() noexcept
{
	glDeleteBuffers(1, &m_BufferId);
}