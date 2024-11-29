#include "Texture.h"

Texture2D::Texture2D(const char* path) : m_path(path)
{
	isLoaded = false;
	data = nullptr;
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	if (LoadTexture())
		isLoaded = true;


	glBindTexture(GL_TEXTURE_2D, 0);
	
}

void Texture2D::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

uint32_t Texture2D::GetHeight() const
{
	return m_height;
}

uint32_t Texture2D::GetWidth() const
{
	return m_width;
}

void Texture2D::Reload()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	if (LoadTexture())
		isLoaded = true;
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_TextureID);
}

bool Texture2D::LoadTexture()
{
	int width;
	int height;
	int nChannels;
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(m_path.c_str(), &width, &height, &nChannels, 0);
	GLenum format;
	GLenum internal;
	switch (nChannels)
	{
	case 1:
		format = GL_RED;
		break;
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;

	}
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		std::cout << "Could not load texture.\n";
		return false;
	}

	stbi_image_free(data);
	data = nullptr;

	m_width = width;
	m_height = height;
	m_nChannels = m_nChannels;
	return true;

}

Texture* Texture::CreateTexture2D(const char* path)
{
	Texture* buffer = new Texture2D(path);
	return buffer;
}
