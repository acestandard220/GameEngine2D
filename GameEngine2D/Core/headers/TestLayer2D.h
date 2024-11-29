#pragma once
#include <pch.h>
#include "Layer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "renderer.h"
#include "Camera.h"
#include "Cameracontrol.h"
#include "Texture.h"
#include "Framebuffer.h"
#include "Renderer2D.h"
#include "Application.h"
#include "Scene.h"


class Test2D : public Layer
{
public:
    Test2D(const char* name) :Layer(name)
    {
       
    }
    virtual void OnAttach() override;
    virtual void OnDettach() override;


    virtual void OnUpdate()override;
    void Key(KeyEvent& _event);
    void Mouse(MouseMoveEvent& e);
    virtual void OnEvent(Event& _event) override;
private:

    ShaderSource* source;
    Shader* shader;

    VertexArrayBuffer* vao;
    IBuffer* vbo;
    IBuffer* ebo;

    float vertex_data[20] = {
    -1.0,  1.0,  0.0,  /**/  0.0f, 1.0f,
     1.0,  1.0,  0.0,  /**/  1.0f, 1.0f,
     1.0, -1.0,  0.0,  /**/  1.0f, 0.0f,
    -1.0, -1.0,  0.0,  /**/  0.0f, 0.0f,
    };

    unsigned int indices[6] = {
        0,  1,  2,
        0,  3,  2
    };

    GE2D::ECS::SceneRef scene;
    GE2D::ECS::GameObjectRef gameObject;


};

