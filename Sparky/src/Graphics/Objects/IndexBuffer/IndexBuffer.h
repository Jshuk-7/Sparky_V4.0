#pragma once

#define GLFW_INCLUDE_OPENGL
#include <GLFW/glfw3.h>

#include "Config/Defines.h"

namespace Sparky {
	enum class IndexBufferDataType {
		UByte   = GL_UNSIGNED_BYTE,
		UShort  = GL_UNSIGNED_SHORT,
		UInt    = GL_UNSIGNED_INT,
		Default = UByte
	};

	struct IndexBufferCreateInfo
	{
		IndexBufferDataType dataType;
		u8* pData;
		u32 indexCount;

		IndexBufferCreateInfo(
			IndexBufferDataType dataType,
			u8* pData,
			u32 indexCount
		) :
			dataType(dataType),
			pData(pData),
			indexCount(indexCount)
		{ }
	};

	class IndexBuffer
	{
	public:
		inline IndexBuffer() noexcept : m_BufferId(SP_NULL), m_IndexCount(SP_NULL), m_DataType(IndexBufferDataType::Default) { }
		IndexBuffer(const IndexBufferCreateInfo& createInfo) noexcept;
		void Destroy() noexcept;

		inline const u32 GetId() const noexcept { return m_BufferId; }
		inline const GLenum& DataType() const noexcept{ return static_cast<GLenum>(m_DataType); }
		inline u32 GetIndexCount() const noexcept { return m_IndexCount; }

	private:
		u32 m_BufferId;
		u32 m_IndexCount;
		IndexBufferDataType m_DataType;

	};
}