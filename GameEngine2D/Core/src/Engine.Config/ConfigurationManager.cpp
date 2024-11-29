#include "Engine.Config/ConfigurationManager.h"

namespace GE2D
{
	namespace EC
	{

		void WindowConfig::FetchConfig(Json::Value configSection)
		{
			__title = configSection["title"].asString();
			__width = configSection["width"].asUInt();
			__height = configSection["height"].asUInt();
			__fullscreen = configSection["fullscreen"].asBool();
			std::cout <<"TITLE: "<<__title << "\nWIDTH: " << __width << "\nHEIGHT: " << __height << std::endl;
		}
		Json::Value WindowConfig::SetConfig(Json::Value configSection,void* newConfig )
		{
			WindowConfig* config = (WindowConfig*)newConfig;
			configSection["width"] = config->__width;
			configSection["height"] = config->__height;
			configSection["title"] = config->__title;

			return configSection;
		}

		void ImGuiConfig::FetchConfig(Json::Value configSection)
		{
			theme = configSection["theme"].asString();
			std::cout << "Theme: " << theme << std::endl;

		}

		Json::Value ImGuiConfig::SetConfig(Json::Value configSection, void* newConfig)
		{
			ImGuiConfig* config = (ImGuiConfig*)newConfig;
			configSection["theme"] = config->theme;
			return configSection;
		}

		EngineConfiguration::EngineConfiguration(const char* path)
		{
			configPath = path;		
			mConfigs.insert({ typeid(WindowConfig).name(),std::make_shared<WindowConfig>()});
			mConfigs.insert({ typeid(ImGuiConfig).name(),std::make_shared<ImGuiConfig>() });
		}

		bool EngineConfiguration::EngineConfigInit()
		{
			std::ifstream file(configPath, std::ios::binary);
			if (!file.is_open())
			{
				std::cout << "Failed to load engine configuration\n";
				return false;
			}
            
			file >> object;
			object = object["EngineConfiguration"];
			file.close();

			FetchConfig();

			return true;
		}
		void EngineConfiguration::FetchConfig()
		{
			for (auto& pair : mConfigs)
			{
				auto& config = pair.second;
				Json::Value section = object[config->GetKey()];
				config->FetchConfig(section);
			}
		}

		void EngineConfiguration::SetConfig(void* newConfig)
		{
			for (auto& pair : mConfigs)
			{
				auto& config = pair.second;
				Json::Value section = object[config->GetKey()];
				object[config->GetKey()] = config->SetConfig(section, newConfig);
			}
			UpdateFile();
		}

		void EngineConfiguration::UpdateFile()
		{
			std::ofstream file(configPath, std::ios::binary);
			if (!file.is_open())
			{
				std::cout << "Failed to save new configurations.\n";
			}
			Json::Value x;
			x["EngineConfiguration"] = object;
			file << x;

			file.close();
		}
		
	}
}
