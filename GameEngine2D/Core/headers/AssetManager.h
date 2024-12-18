#pragma once
#include "pch.h"
#include "../core.h"
#include "Texture.h"
#include "Shader.h"



namespace GE2D
{
    class AssetManager
    {

        public:
    		static bool Initialize(std::string path_to = "P:/Projects/VS/GameEngine2D/GameEngine2D/Core/assets");
    		static bool Shutdown();

            static bool CreateTexture(const char* name,const char* path);
            static std::shared_ptr<Texture> GetTexture(const char* name);
            static bool RemoveTexture(const char* name);

            static bool CreateShader(const char* name, ShaderSource& shader_source);
            static std::shared_ptr<Shader> GetShader(const char* name);
            static bool RemoveShader(const char* name);
            
            static void Dump();
    
    	private:
    		static std::string asset_path;
            static std::unordered_map<const char*, std::shared_ptr<Texture>> m_textures;
            static std::unordered_map<const char*, std::shared_ptr<Shader>> m_shaders;
    };
}