#pragma once

#define GLFW_INCLUDE_OPENGL
#include <GLFW/glfw3.h>

#include "Config/Defines.h"
#include "Math/SparkyMath.h"
#include "Core/SparkySTL/SparkySTL.h"

namespace Sparky {
	enum class VertexBufferStorageType {
		Dynamic = GL_DYNAMIC_STORAGE_BIT,
		Static
	};

	enum class VertexBufferDataType {
		Float = GL_FLOAT,
		Double = GL_DOUBLE,
	};

	struct VertexBufferCreateInfo {
		VertexBufferDataType dataType;
		VertexBufferStorageType storageType;
		u32 stride;
		u32 offset;
		u32 vertexCount;
		stl::Array<Vertex, 4> vertices;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(const VertexBufferCreateInfo* createInfo) noexcept;

		static VertexBuffer* Create(const VertexBufferCreateInfo* createInfo) noexcept;
		void Destroy() noexcept;

		inline const u32 GetId() const noexcept { return m_BufferId; }
		inline auto GetDataType() const noexcept { return m_CreateInfo.dataType; }
		inline auto GetStorageType() const noexcept { return m_CreateInfo.storageType; }
		inline u32 GetOffset() const noexcept { return m_CreateInfo.offset; }
		inline u32 GetStride() const noexcept { return m_CreateInfo.stride; }
		inline const u32 GetVertexCount() const noexcept { return m_CreateInfo.vertexCount; }
		inline auto GetVertices() const noexcept { return m_CreateInfo.vertices; }

	private:
		VertexBufferCreateInfo m_CreateInfo;
		u32 m_BufferId;

	};
}