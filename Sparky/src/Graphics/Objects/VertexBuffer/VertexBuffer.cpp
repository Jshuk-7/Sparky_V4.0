#include "VertexBuffer.h"

Sparky::VertexBuffer::VertexBuffer(const VertexBufferCreateInfo* createInfo) noexcept
	: m_BufferId(SP_NULL), m_CreateInfo(*createInfo)
{
	glCreateBuffers(1, &m_BufferId);
}

Sparky::VertexBuffer* Sparky::VertexBuffer::Create(const VertexBufferCreateInfo* createInfo) noexcept
{
	return new VertexBuffer(createInfo);
}

void Sparky::VertexBuffer::Destroy() noexcept
{
	if (m_BufferId)
		glDeleteBuffers(1, &m_BufferId);
}