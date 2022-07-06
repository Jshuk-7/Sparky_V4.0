#pragma once

#include "Config/Defines.h"
#include "Math/SparkyMath.h"
#include "Graphics/Texture/Texture.h"

namespace Sparky {
	struct FrameBufferCreateInfo {
		vec2 size;
	};

	class FrameBuffer
	{
	public:
		FrameBuffer(const FrameBufferCreateInfo* createInfo);
		FrameBuffer() = default;
		~FrameBuffer();

	private:
		void CreateFrameBuffer() noexcept;

	public:

		void Resize(const vec2& size) noexcept;

		void Bind() const noexcept;
		void Unbind() const noexcept;

		u32 GetColorAttachmentId() const { return m_ColorAttachment; }
		u32 GetDepthAttachmentId() const { return m_DepthAttachment; }

	private:
		FrameBufferCreateInfo m_CreateInfo;
		u32 m_ColorAttachment;
		u32 m_DepthAttachment;
		vec2 m_Size;
		u32 m_Id;
	};
}