#include "AssetManager.h"

const char* AssetManager::path = nullptr;
std::unordered_map<const char*, std::shared_ptr<Texture2D>> AssetManager::m_textures{};

bool AssetManager::Initialize(const char* path_to)
{
    path = path_to;

    return true;
}

void AssetManager::ShutDown()
{
}


bool AssetManager::LoadTexture(const char* name, const char* path_to)
{
    if (m_textures.find(name) != m_textures.end())
    {
        std::cout << "Texture has already been loaded\n";
        return false;
    }

    m_textures.insert({ name,std::make_shared<Texture2D>(path_to) });
    return true;
}

std::shared_ptr<Texture2D> AssetManager::GetTexture(const char* name)
{
    if (m_textures.find(name) == m_textures.end())
    {
        std::cout << "Texture has not been loaded\n";
        return nullptr;
    }
    return m_textures[name];
}

void AssetManager::DeleteTexture(const char* name)
{
    if (m_textures.find(name) == m_textures.end())
    {
        std::cout << "Texture has not been loaded\n";
        return;
    }
    m_textures.erase(name);
}
