#pragma once

#define GLFW_INCLUDE_OPENGL
#include <GLFW/glfw3.h>

#include "Config/Defines.h"
#include "Math/SparkyMath.h"

namespace Sparky {
	struct VertexBufferCreateInfo
	{
		u32 vertexCount;
		u32 attribIndex;
		u32 bindingIndex;
		u32 componentCount;
		u32 offset;
		u32 relativeOffset;
		Vertex* pData;

		VertexBufferCreateInfo(
			u32 vertexCount,
			u32 attribIndex,
			u32 bindingIndex,
			u32 componentCount,
			u32 offset,
			u32 relativeOffset,
			Vertex* pData
		) :
			vertexCount(vertexCount),
			attribIndex(attribIndex),
			bindingIndex(bindingIndex),
			componentCount(componentCount),
			offset(offset),
			relativeOffset(relativeOffset),
			pData(pData)
		{ }
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(const VertexBufferCreateInfo& createInfo) noexcept;
		void Destroy() noexcept;

		inline const u32 GetId() const noexcept { return m_BufferId; }
		inline u32 GetAttribIndex() const noexcept { return m_AttributeIndex; }
		inline u32 GetBindingIndex() const noexcept { return m_BindingIndex; }
		inline u32 GetComponentCount() const noexcept { return m_ComponentCount; }
		inline u32 GetOffset() const noexcept { return m_Offset; }
		inline u32 GetRelativeOffset() const noexcept { return m_RelativeOffset; }

	private:
		u32 m_BufferId;
		u32 m_VertexCount;
		u32 m_BindingIndex;
		u32 m_ComponentCount;
		u32 m_Offset;
		u32 m_RelativeOffset;
		u32 m_AttributeIndex;
	};
}