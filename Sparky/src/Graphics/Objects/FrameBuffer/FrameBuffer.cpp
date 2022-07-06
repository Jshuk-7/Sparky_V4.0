#define GLFW_INCLUDE_OPENGL
#include <GLFW/glfw3.h>

#include "FrameBuffer.h"

Sparky::FrameBuffer::FrameBuffer(const FrameBufferCreateInfo* createInfo)
	:
	m_CreateInfo(*createInfo),
	m_ColorAttachment(SP_NULL),
	m_DepthAttachment(SP_NULL)
{
	m_Size = m_CreateInfo.size;
	CreateFrameBuffer();
}

Sparky::FrameBuffer::~FrameBuffer()
{
	if (m_Id)
		glDeleteFramebuffers(1, &m_Id);
	if (m_ColorAttachment)
		glDeleteTextures(1, &m_ColorAttachment);
	if (m_DepthAttachment)
		glDeleteTextures(1, &m_DepthAttachment);
}

void Sparky::FrameBuffer::CreateFrameBuffer() noexcept
{
	if (m_Id)
	{
		glDeleteFramebuffers(1, &m_Id);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}

	glViewport(SP_NULL, SP_NULL, m_Size.x, m_Size.y);

	glCreateFramebuffers(1, &m_Id);
	glBindFramebuffer(GL_FRAMEBUFFER, m_Id);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
	glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Size.x, m_Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, SP_NULL_HANDLE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
	glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Size.x, m_Size.y, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, SP_NULL_HANDLE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		SP_ERROR("Framebuffer is incomplete!");

	glBindFramebuffer(GL_FRAMEBUFFER, SP_NULL);
}

void Sparky::FrameBuffer::Resize(const vec2& size) noexcept
{
	m_Size = size;

	CreateFrameBuffer();
}

void Sparky::FrameBuffer::Bind() const noexcept
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
	glViewport(SP_NULL, SP_NULL, m_Size.x, m_Size.y);
}

void Sparky::FrameBuffer::Unbind() const noexcept
{
	glBindFramebuffer(GL_FRAMEBUFFER, SP_NULL);
}