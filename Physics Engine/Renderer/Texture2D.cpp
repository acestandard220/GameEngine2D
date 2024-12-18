#include "Texture2D.h"
#include <iostream>

Texture2D::Texture2D()
	:path("picture.png")
{

}

Texture2D::Texture2D(const char* path_to)
	:path(path_to)
{
	LoadTexture();
	CreateTexture();
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &id);

}

bool Texture2D::LoadTexture()
{
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(path, &width, &height, &nChannels, 0);
	if (!data)
	{
		std::cout << "Could not load texture\n";
		return false;
	}
	return true;
}

bool Texture2D::CreateTexture()
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, get_channel_enum(), width, height, 0,get_channel_enum(),GL_UNSIGNED_BYTE,data);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glBindTexture(GL_TEXTURE_2D,0);

	return true;
}

GLenum Texture2D::get_channel_enum()
{
	switch (nChannels)
	{
		case 1:
		{
			return GL_RED;
		}
		case 2:
		{
			return GL_RG;
		}
	    case 3:
	    {
			return GL_RGB;
	    }
		case 4:
		{
			return GL_RGBA;
		}
		default:
		{
			return GL_RGB;
		}
	}
}
