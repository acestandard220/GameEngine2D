#pragma once
#include "pch.h"
#include "Event.h"
#include "Layerstack.h"
#include "ExampleLayer.h"
#include "../core.h"
#include "EditorLayer.h"
#include "Engine.Config/ConfigurationManager.h"
#include "TestLayer2D.h"


#include "Scene.h"
#include "Gameobject.h"

class Application
{
    public:
        Application(const char* title, int width, int height);
        ~Application();
    
        bool Init();
        bool Run();
        void Shutdown();

        static void OnEvent(Event& _event);

        void Configure();
    
        void PushLayer(Layer* layer);
        void PushOverLay(Layer* overlay);
        void PopLayer(Layer* layer);
        void OnUpdate();
    
        void ImGuiInit();
        void ImGuiBegin();
        void ImGuiEnd();
    
    
        static Application* APPLICATION;
        static inline Application& GetApp() { return *APPLICATION; }
        static inline GLFWwindow& GetWindow() { return *APPLICATION->m_window; }
    
        int GetWidth() const { return windowsproperties.__width; }
        int GetHeight() const { return windowsproperties.__height; }
    
        EditorLayer* editor;

        std::shared_ptr<GE2D::ECS::Scene> scene;
        GE2D::ECS::GameObject* o;

    private:
    
    private:
        EventManager* m_eventmanager;
        LayerStack    m_layerstack;
        GLFWwindow*   m_window;

        GE2D::EC::EngineConfiguration configuration;

    private:
        struct WindowProps
        {
            std::string title;
            uint32_t width;
            uint32_t height;
            bool fullscreen;
        };
       
        GE2D::EC::WindowConfig windowsproperties;
};


