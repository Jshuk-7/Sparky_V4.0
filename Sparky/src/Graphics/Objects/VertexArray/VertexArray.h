#pragma once

#define GLFW_INCLUDE_OPENGL
#include <GLFW/glfw3.h>

#include "Config/Defines.h"
#include "Graphics/Objects/VertexBuffer/VertexBuffer.h"
#include "Graphics/Objects/IndexBuffer/IndexBuffer.h"
#include "Core/SparkySTL/SparkySTL.h"

namespace Sparky {
	class VertexArray
	{
	public:
		VertexArray() noexcept;
		void Destroy() noexcept;

		void LinkVBO(const VertexBuffer* vb) noexcept;
		void PushAttrib(u32 attribIndex, u32 componentCount, b8 normalized, u32 relativeOffset);

		void LinkIBO(const IndexBuffer* ib) noexcept;

		auto GetIBODataType() const noexcept { return m_IndexBufferDataType; }

		auto GetLinkedVBOs() const noexcept { return m_Buffers; }

		void Bind() const noexcept;
		void Unbind() const noexcept;

	private:
		u32 m_ArrayId;
		u32 m_BindingIndex;
		IndexBufferDataType m_IndexBufferDataType;
		stl::Vector<const VertexBuffer*> m_Buffers;
	};
}