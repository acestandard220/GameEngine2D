#pragma once
#include "../../Deps/json/json/json.h"
#include "../../Deps/json/json/value.h"
#include "../core.h"
#include "pch.h"

namespace GE2D
{
    namespace EC
    {
        struct IConfig
        {
            virtual inline const std::string& GetKey() const{ return __key; }
            virtual void FetchConfig(Json::Value) = 0;
            virtual Json::Value SetConfig(Json::Value,void*) = 0;
            protected:
                std::string __key;
        };
        /// @brief Structures that store read config information.
        struct WindowConfig : public IConfig
        {
            WindowConfig()
            {
                __key = "WindowSetting";
            }
            std::string __title = "NULL";
            uint32_t __width = 1280;
            uint32_t __height = 720;
            bool __fullscreen = false;

            virtual void FetchConfig(Json::Value) override;
            virtual Json::Value SetConfig(Json::Value configSection, void* newConfig) override;

        };
        struct ImGuiConfig : public IConfig
        {
            ImGuiConfig()
            {
                __key = "ImGuiSetting";
            }

            std::string theme;

            virtual void FetchConfig(Json::Value) override;
            virtual Json::Value SetConfig(Json::Value configSection, void* newConfig) override;


        };


        /// @brief Manages the config of only the engine
        class EngineConfiguration
        {
        public:
            EngineConfiguration(const char*);

            bool EngineConfigInit();

            void FetchConfig();
            void SetConfig(void* newConfig);

            void UpdateFile();

            inline std::shared_ptr<WindowConfig> GetWindowConfig()
            {
                return std::static_pointer_cast<WindowConfig>(mConfigs[typeid(WindowConfig).name()]);
            }
            inline std::shared_ptr<ImGuiConfig> GetImGuiConfig()
            {
                return std::static_pointer_cast<ImGuiConfig>(mConfigs[typeid(ImGuiConfig).name()]);
            }

        private:
            std::unordered_map<const char*,std::shared_ptr<IConfig>> mConfigs;

            Json::Value object;
            std::string configPath;
        };

        
    }

}