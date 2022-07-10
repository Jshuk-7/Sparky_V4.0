#include "Renderer.h"

Sparky::Renderer::Renderer()
	: m_RendererStats{} { }

void Sparky::Renderer::Submit(const RendererDataCreateInfo* info) noexcept
{
	m_RenderQueue.PushBack(info);
	SetClearColor(info->clearColor);

	RendererStatistics renderStats{};
	renderStats.drawCalls = 1;
	renderStats.triangleCount = info->vao.GetLinkedVBOs()[0]->GetVertexCount() / SP_VERTICES_PER_TRIANGLE;
	renderStats.vertices = info->vao.GetLinkedVBOs()[0]->GetVertexCount();

	m_RendererStats = renderStats;

	m_TargetFrameBuffer = info->framebuffer;
}

void Sparky::Renderer::Flush() noexcept
{
	m_TargetFrameBuffer.Bind();
	RenderClear();

	for (auto& renderData : m_RenderQueue)
	{
		renderData->shader.Enable();
		renderData->vao.Bind();

		Render(renderData->primitiveType, renderData->vao.GetLinkedVBOs()[0]->GetVertexCount(), renderData->vao.GetIBODataType());
	}

	SwapFrameBuffers();
	m_TargetFrameBuffer.Unbind();
}

void Sparky::Renderer::SetClearColor(const vec3& color) const noexcept
{
	glClearColor(color.r, color.g, color.b, 1.0f);
}

void Sparky::Renderer::RenderClear() const noexcept
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Sparky::Renderer::Render(PrimitiveType primitive, u32 totalVertices, IndexBufferDataType iboDataType) noexcept
{
	glDrawElements(
		static_cast<GLenum>(primitive),
		totalVertices,
		static_cast<GLenum>(iboDataType),
		SP_NULL_HANDLE
	);
}

void Sparky::Renderer::SubmitStats(const RendererStatistics* stats) noexcept
{
	m_RendererStats = *stats;
}

void Sparky::Renderer::SwapFrameBuffers() const noexcept
{
	glfwSwapBuffers(glfwGetCurrentContext());
}