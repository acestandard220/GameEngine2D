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


class ExampleLayer : public Layer
{
public:
    ExampleLayer(const char* name) :Layer(name)
    {
        can = true;
    }
    virtual void OnAttach() override;
    virtual void OnDettach() override;

   
    virtual void OnUpdate()override;
    void Key(KeyEvent& _event);
    void Mouse(MouseMoveEvent& e);
    virtual void OnEvent(Event& _event) override;
    bool can;
private:
   


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
    

    Texture* texture;
    BufferLayout* lay;
    IBuffer* sqaure_buffer;
    IBuffer* square_index;
    VertexArrayBuffer sqaure_VAO;
    ShaderSource* anothersource;
    Shader* anotherShader;
    Framebuffer* framebuffer;
};

