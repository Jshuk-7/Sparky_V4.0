#pragma once

#include <vector>

#define GLFW_INCLUDE_OPENGL
#include <GLFW/glfw3.h>

#include "Config/Defines.h"
#include "Graphics/Objects/VertexBuffer/VertexBuffer.h"
#include "Graphics/Objects/IndexBuffer/IndexBuffer.h"

namespace Sparky {
	class VertexArray
	{
	public:
		VertexArray() noexcept;
		void Destroy() noexcept;

		void AddVertexBuffer(VertexBuffer* buffer) noexcept;
		void LinkIBO(IndexBuffer* buffer) noexcept;

		auto GetVertexBuffers() const noexcept { return m_Buffers; }

		void Bind() const noexcept;
		void Unbind() const noexcept;

	private:
		u32 m_ArrayId;
		std::vector<VertexBuffer*> m_Buffers;
	};
}