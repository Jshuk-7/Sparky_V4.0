#pragma once

#include <deque>
#include <vector>

#define GLFW_INCLUDE_OPENGL
#include <GLFW/glfw3.h>

#include "Config/Defines.h"
#include "Math/SparkyMath.h"
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

	struct RendererDataCreateInfo {
		u32& vertexArrayId;
		u32& vertexBufferId;
		u32& indexBufferId;
		u32 indexCount;
		u32 attributeCount;
		Vertex* pVertices;
		u8* pIndices;
		PrimitiveType primitiveType;
	};

	struct RendererStatistics {
		u32 drawCalls;
		u32 triangleCount;
		u32 vertices;
	};

	class Renderer
	{
	public:
		Renderer();

		void Submit(const RendererDataCreateInfo* info) noexcept;
		void Flush() noexcept;
		
		void SetRenderClearColor(const vec3& color) const noexcept;

		void Update() const noexcept;
		void RenderClear() const noexcept;

		void Render(GLenum mode, GLsizei vertexCount, GLenum type) noexcept;

		void SubmitRendererStats(const RendererStatistics& stats) noexcept;
		const RendererStatistics& GetStats() const noexcept { return m_RendererStats; }

	public:


	private:
		void SwapFrameBuffers() const noexcept;

	private:
		std::deque<const RendererDataCreateInfo*> m_RenderQueue;
		RendererStatistics m_RendererStats;

	};
}