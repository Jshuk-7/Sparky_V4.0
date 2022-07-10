#pragma once

#define GLFW_INCLUDE_OPENGL
#include <GLFW/glfw3.h>

#include "Config/Defines.h"
#include "Core/SparkySTL/SparkySTL.h"
#include "Math/SparkyMath.h"
#include "Graphics/Objects/FrameBuffer/FrameBuffer.h"
#include "Graphics/Objects/VertexArray/VertexArray.h"
#include "Graphics/Objects/VertexBuffer/VertexBuffer.h"
#include "Graphics/Objects/IndexBuffer/IndexBuffer.h"
#include "Graphics/Shader/Shader.h"

namespace Sparky {
	enum class PrimitiveType {
		Triangles = GL_TRIANGLES,
		Lines     = GL_LINES,
		Points    = GL_POINTS
	};

	struct RendererStatistics {
		u32 drawCalls;
		u32 triangleCount;
		u32 vertices;
	};

	struct RendererDataCreateInfo {
		FrameBuffer framebuffer;
		Shader shader;
		VertexArray vao;
		vec3 clearColor;
		PrimitiveType primitiveType;
	};

	class Renderer
	{
	public:
		Renderer();

		void Submit(const RendererDataCreateInfo* info) noexcept;
		void Flush() noexcept;
		
		void SetClearColor(const vec3& color) const noexcept;
		void RenderClear() const noexcept;

		void Render(PrimitiveType primitive, u32 totalVertices, IndexBufferDataType iboDataType) noexcept;
		void SwapFrameBuffers() const noexcept;

		void SubmitStats(const RendererStatistics* stats) noexcept;
		const RendererStatistics& GetStats() const noexcept { return m_RendererStats; }

	private:
		stl::Vector<const RendererDataCreateInfo*> m_RenderQueue;
		RendererStatistics m_RendererStats;
		FrameBuffer m_TargetFrameBuffer;

	};
}