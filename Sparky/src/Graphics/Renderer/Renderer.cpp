#include "Renderer.h"

Sparky::Renderer::Renderer()
	: m_RendererStats{} { }

void Sparky::Renderer::Submit(const RendererDataCreateInfo* info) noexcept
{
	
}

void Sparky::Renderer::Flush() noexcept
{
	
}

void Sparky::Renderer::Update() const noexcept
{
	SwapFrameBuffers();
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

void Sparky::Renderer::SubmitStats(const RendererStatistics& stats) noexcept
{
	m_RendererStats = stats;
}

void Sparky::Renderer::SwapFrameBuffers() const noexcept
{
	glfwSwapBuffers(glfwGetCurrentContext());
}