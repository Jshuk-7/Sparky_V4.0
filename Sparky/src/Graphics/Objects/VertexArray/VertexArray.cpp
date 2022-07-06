#include "VertexArray.h"

Sparky::VertexArray::VertexArray() noexcept
{
	glGenVertexArrays(1, &m_ArrayId);
}

void Sparky::VertexArray::Destroy() noexcept
{
	for (auto& buffer : m_Buffers)
		delete buffer;

	glDeleteVertexArrays(1, &m_ArrayId);
}

void Sparky::VertexArray::AddVertexBuffer(VertexBuffer* buffer) noexcept
{
	m_Buffers.push_back(buffer);

	static b8 vboLinked{};

	if (!vboLinked)
	{
		glVertexArrayVertexBuffer(m_ArrayId, buffer->GetBindingIndex(), buffer->GetId(), buffer->GetOffset(), sizeof(Vertex));
		vboLinked = true;
	}

	glEnableVertexArrayAttrib(m_ArrayId, buffer->GetAttribIndex());
	glVertexArrayAttribFormat(m_ArrayId, buffer->GetAttribIndex(), buffer->GetComponentCount(), GL_FLOAT, SP_FALSE, buffer->GetRelativeOffset());
	glVertexArrayAttribBinding(m_ArrayId, buffer->GetAttribIndex(), buffer->GetBindingIndex());
}

void Sparky::VertexArray::LinkIBO(IndexBuffer* buffer) noexcept
{
	glVertexArrayElementBuffer(m_ArrayId, buffer->GetId());
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