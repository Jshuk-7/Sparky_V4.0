#include "VertexArray.h"

Sparky::VertexArray::VertexArray() noexcept
	: m_ArrayId(SP_NULL), m_BindingIndex(SP_NULL)
{
	glCreateVertexArrays(1, &m_ArrayId);
}

void Sparky::VertexArray::Destroy() noexcept
{
	glDeleteVertexArrays(1, &m_ArrayId);

	m_Buffers.Destroy();
}

void Sparky::VertexArray::LinkVBO(const VertexBuffer* vb) noexcept
{
	m_Buffers.PushBack(vb);

	glVertexArrayVertexBuffer(m_ArrayId, m_BindingIndex, vb->GetId(), vb->GetOffset(), vb->GetStride());
	glNamedBufferStorage(
		vb->GetId(),
		vb->GetVertices().Bytes(),
		vb->GetVertices().Data(),
		static_cast<GLbitfield>(vb->GetStorageType())
	);

	m_BindingIndex++;
}

void Sparky::VertexArray::PushAttrib(u32 attribIndex, u32 componentCount, b8 normalized, u32 relativeOffset)
{
	u32 currentBufferIndex = m_BindingIndex - 1;

	glEnableVertexArrayAttrib(m_ArrayId, attribIndex);
	glVertexArrayAttribFormat(
		m_ArrayId,
		attribIndex,
		componentCount,
		static_cast<GLenum>(m_Buffers[currentBufferIndex]->GetDataType()),
		normalized,
		relativeOffset
	);
	glVertexArrayAttribBinding(m_ArrayId, attribIndex, currentBufferIndex);
}

void Sparky::VertexArray::LinkIBO(const IndexBuffer* ib) noexcept
{
	m_IndexBufferDataType = ib->DataType();

	glVertexArrayElementBuffer(m_ArrayId, ib->GetId());
	glNamedBufferStorage(
		ib->GetId(),
		ib->GetIndices().Bytes(),
		ib->GetIndices().Data(),
		static_cast<GLbitfield>(ib->GetStorageType())
	);

	delete ib;
}

void Sparky::VertexArray::Bind() const noexcept
{
	if (m_ArrayId)
		glBindVertexArray(m_ArrayId);
}

void Sparky::VertexArray::Unbind() const noexcept
{
	glBindVertexArray(SP_NULL);
}