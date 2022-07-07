#include "IndexBuffer.h"

Sparky::IndexBuffer::IndexBuffer(const IndexBufferCreateInfo* createInfo) noexcept
	: m_BufferId(SP_NULL), m_CreateInfo(*createInfo)
{
	glCreateBuffers(1, &m_BufferId);
}

Sparky::IndexBuffer* Sparky::IndexBuffer::Create(const IndexBufferCreateInfo* createInfo) noexcept
{
	return new IndexBuffer(createInfo);
}

void Sparky::IndexBuffer::Destroy() noexcept
{
	if (m_BufferId)
		glDeleteBuffers(1, &m_BufferId);
}