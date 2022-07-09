#pragma once

#define GLFW_INCLUDE_OPENGL
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include "Config/Defines.h"
#include "Utilities/Utilities.h"

namespace Sparky {
	enum class TextureFormatType {
		Red             = GL_RED,
		RG              = GL_RG,
		RGB             = GL_RGB,
		BGR             = GL_BGR,
		RGBA            = GL_RGBA,
		BGRA            = GL_BGRA,
		DepthComponent  = GL_DEPTH_COMPONENT,
		StencilIndex    = GL_STENCIL_INDEX,
	};

	enum class TexturePixelType {
		Smooth = GL_LINEAR,
		Pixelated = GL_NEAREST,
	};

	struct TextureCreateInfo {
		const i8* pFilename;
		TextureFormatType format;
		TexturePixelType pixelType;
		bool flipY;
	};

	class Texture
	{
	public:
		Texture(const TextureCreateInfo* createInfo);
		~Texture() noexcept;

		void Bind(u32 textureIndex) const noexcept;
		void Unbind(u32 textureIndex) const noexcept;

		const u32& GetId() const noexcept { return m_Id; }

	private:
		TextureCreateInfo m_CreateInfo;
		u32 m_Id;
	};
}