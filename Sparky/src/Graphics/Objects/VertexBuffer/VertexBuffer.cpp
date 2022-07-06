#include "VertexBuffer.h"

Sparky::VertexBuffer::VertexBuffer(const VertexBufferCreateInfo& createInfo) noexcept
	:
	m_BufferId(SP_NULL),
	m_VertexCount(createInfo.vertexCount),
	m_BindingIndex(createInfo.bindingIndex),
	m_ComponentCount(createInfo.componentCount),
	m_Offset(createInfo.offset),
	m_RelativeOffset(createInfo.relativeOffset),
	m_AttributeIndex(createInfo.attribIndex)
{
	glCreateBuffers(1, &m_BufferId);
	glNamedBufferStorage(m_BufferId, createInfo.vertexCount * sizeof(Vertex), createInfo.pData, GL_DYNAMIC_STORAGE_BIT);
}

void Sparky::VertexBuffer::Destroy() noexcept
{
	glDeleteBuffers(1, &m_BufferId);
}