#pragma once

#define GLFW_INCLUDE_OPENGL
#include <GLFW/glfw3.h>

#include "Config/Defines.h"
#include "Core/SparkySTL/SparkySTL.h"

namespace Sparky {
	enum class IndexBufferDataType {
		UByte   = GL_UNSIGNED_BYTE,
		UShort  = GL_UNSIGNED_SHORT,
		UInt    = GL_UNSIGNED_INT,
	};

	enum class IndexBufferStorageType {
		Dynamic = GL_DYNAMIC_STORAGE_BIT,
		Static
	};

	struct IndexBufferCreateInfo {
		IndexBufferDataType dataType;
		IndexBufferStorageType storageType;
		u32 indexCount;
		stl::Array<u8, 6> indices;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer(const IndexBufferCreateInfo* createInfo) noexcept;
		static IndexBuffer* Create(const IndexBufferCreateInfo* createInfo) noexcept;
		void Destroy() noexcept;

		inline const u32 GetId() const noexcept { return m_BufferId; }
		inline auto DataType() const noexcept{ return m_CreateInfo.dataType; }
		inline auto GetStorageType() const noexcept { return m_CreateInfo.storageType; }
		inline u32 GetIndexCount() const noexcept { return m_CreateInfo.indexCount; }
		inline auto GetIndices() const noexcept { return m_CreateInfo.indices; }

	private:
		IndexBufferCreateInfo m_CreateInfo;
		u32 m_BufferId;

	};
}