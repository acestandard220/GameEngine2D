#include "AssetManager.h"

void AssetManager::Initialize()
{

}

void AssetManager::Shutdown()
{

}

bool AssetManager::LoadTexture(const char* name, const char* path_to)
{
	if (mTextures.find(name) != mTextures.end())
	{
		std::cout << "There is a textures with this name\n";
		return false;
	}
	mTextures.insert({ name, std::make_shared<Texture>(Texture::CreateTexture2D(path_to)) });
}

std::shared_ptr<Texture> AssetManager::GetTexture(const char* name)
{
	if (mTextures.find(name) == mTextures.end())
	{
		std::cout << "Could not find texture in database\n";
		return nullptr;
	}
	return mTextures[name];
}