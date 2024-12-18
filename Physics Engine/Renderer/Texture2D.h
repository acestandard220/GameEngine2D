#pragma once
#include <GL/glew.h>
#include <cstdint>
#include "../stb_image.h"

class Texture2D
{
public:
	Texture2D();
	Texture2D(const char* path_to);
	~Texture2D();

	const int GetWidth()const { return width; }
	const int GetHeight()const { return height; }
	const int GetChannels()const { return nChannels; }

	const uint32_t GetID()const { return id; }
private:
	bool LoadTexture();
	bool CreateTexture();

	GLenum get_channel_enum();
private:
	int width;
	int height;
	int nChannels;

	const char* path;
	unsigned char* data;
	uint32_t id =-1;
};
