#pragma once
#include "Texture.h"


class AssetManager
{
public:
	static void Initialize();
	static void Shutdown();

	static bool LoadTexture(const char* name, const char* path_to);
	static std::shared_ptr<Texture> GetTexture(const char* name);

private:
	static std::unordered_map<const char*, std::shared_ptr<Texture>> mTextures;

};

