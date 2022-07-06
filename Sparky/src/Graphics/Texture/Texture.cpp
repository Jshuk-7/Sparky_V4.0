#include "Texture.h"

Sparky::Texture::Texture(const TextureCreateInfo* createInfo)
	: m_CreateInfo(*createInfo), m_Id(SP_NULL)
{		
	if (m_CreateInfo.flipY)
		stbi_set_flip_vertically_on_load(true);

	i32 width, height, nrChannels;
	u8* textureData = stbi_load(m_CreateInfo.pFilename, &width, &height, &nrChannels, STBI_rgb_alpha);
	i32 pixelType = static_cast<i32>(m_CreateInfo.pixelType);

	if (!textureData) {
		SP_FATAL("Failed to load texture from: /" + (std::string)m_CreateInfo.pFilename);
		//throw SparkyException(__LINE__, __FILE__);
	}
	else {
		GLenum format = static_cast<GLenum>(m_CreateInfo.format);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);

		glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, pixelType);
		glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, pixelType);
		
		glTextureStorage2D(m_Id, 1, GL_RGBA8, width, height);
		glTextureSubImage2D(m_Id, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, textureData);

		stbi_image_free(textureData);
	}
}

Sparky::Texture::~Texture() noexcept
{
	glDeleteTextures(1, &m_Id);
}

void Sparky::Texture::Bind(u32 textureIndex) const noexcept
{
	if (m_Id)
		glBindTextureUnit(textureIndex, m_Id);
}

void Sparky::Texture::Unbind(u32 textureIndex) const noexcept
{
	glBindTextureUnit(textureIndex, SP_NULL);
}