#pragma once
#include "../Renderer/Sprite.h"
#include <memory>
#include <unordered_map>
#include <iostream>

class AssetManager
{
private:
	static const char* path; //Path to assets

	static std::unordered_map<const char*,std::shared_ptr<Texture2D>> m_textures;

public:
	static bool Initialize(const char* path_to);

	static void ShutDown();

	static bool LoadTexture(const char* name,const char* path_to);
	static std::shared_ptr<Texture2D> GetTexture(const char* name);
	static void DeleteTexture(const char* name);



};

