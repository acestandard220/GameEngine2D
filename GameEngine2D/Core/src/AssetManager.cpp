#include "AssetManager.h"

namespace GE2D
{
	bool AssetManager::Initialize(std::string path_to)
	{
		asset_path = path_to;
		return true;
	}

	bool AssetManager::Shutdown()
	{
		std::cout << "Asset manager has been destroyed\n";
		Dump();
		return true;
	}


	bool AssetManager::CreateTexture(const char* name, const char* path)
	{
		if (m_textures.find(name) != m_textures.end())
		{
#ifdef _DEBUG
			std::cout << "This texture has already been loaded\n";
#endif 
			return false;
		}
		std::string path_s = asset_path + path;
		m_textures.insert({ name,std::make_shared<Texture>(Texture::CreateTexture2D(path_s.c_str())) });
		return true;
	}

	std::shared_ptr<Texture> AssetManager::GetTexture(const char* name)
	{
		if (m_textures.find(name) == m_textures.end())
		{
			std::cout << "This texture has not been loaded\n";
			return nullptr;
		}
		return m_textures[name];
	}
	
	bool AssetManager::RemoveTexture(const char* name)
	{
		if (m_textures.find(name) == m_textures.end())
		{
			std::cout << "This texture has not been loaded\n";
			return false;
		}
		m_textures.erase(name);
		return true;
	}
	
	bool AssetManager::CreateShader(const char* name, ShaderSource& shader_source)
	{
		if (m_shaders.find(name) != m_shaders.end())
		{

#ifdef _DEBUG
			std::cout << "This shader has already been loaded\n";
#endif
			return false;
		}
		//std::string path_s = asset_path + path;
		m_shaders.insert({ name,std::make_shared<Shader>(shader_source) });
		return true;
	}
	
	std::shared_ptr<Shader> AssetManager::GetShader(const char* name)
	{
		if (m_shaders.find(name) == m_shaders.end())
		{
			return nullptr;
		}
		return m_shaders[name];
	}

	
	bool AssetManager::RemoveShader(const char* name)
	{
		if (m_shaders.find(name) == m_shaders.end())
		{
			std::cout << "This shader has not been loaded\n";
			return false;
		}
		m_shaders.erase(name);
		return true;
	}


	void AssetManager::Dump()
	{
		m_textures.clear();
		m_shaders.clear();
	}
}
