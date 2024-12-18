#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer/Renderer2D.h"
#include "System/GameObject.h"
#include "System/CollisionSystem.h"

constexpr int width  = 800;
constexpr int height = 800;
constexpr const char* title = "Physics Engine";

int main()
{
    GLFWwindow* window = nullptr;

    // glfw init / window creation
    {
        if (!glfwInit())
        {
            std::cout << "Could not initialize GLFW.\n";
            return -1;
        }

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window)
        {
            std::cout << "Could not create window\n";
            return -1;
        }
        glfwMakeContextCurrent(window);
    }
    //GLEW INIT
    {
        if (glewInit())
        {
            std::cout << "Could not initialize Glew\n";
            return -1;
        }
    }


    {
        AssetManager::Initialize("");
        AssetManager::LoadTexture("Anime", "picture.png");
        AssetManager::LoadTexture("Ball", "ball.png");
        Renderer::Initialize();
    }

    QuadTree tree(0,{ LEFT_BOUND, BOTTOM_BOUND ,0.0f}, { 1.0f,1.0 });

    Sprite sprite({ 1.0f,1.0f,0.0f });
    sprite.LoadTexture("Ball");
    
    Ball* ball = new Ball({0.0, 0.0f, 0.0f }, {0.2,0.2}, {-0.150,-0.20,0.0}, sprite);
    Ball* ball2 = new Ball({ 0.3,-0.2f, 0.0f }, { 0.2,0.2 }, { 0.10,-0.20,0.0 }, sprite);
    Ball* ball3 = new Ball({ 0.3,-0.2f, 0.0f }, { 0.2,0.2 }, { 0.70,-0.20,0.0 }, sprite);
    Ball* ball4 = new Ball({ 0.3,-0.2f, 0.0f }, { 0.2,0.2 }, { -0.280,0.20,0.0 }, sprite);
    Ball* ball5 = new Ball({ 0.3,-0.2f, 0.0f }, { 0.2,0.2 }, { 1.800,0.20,0.0 }, sprite);
    Ball* ball6 = new Ball({ 0.3,-0.2f, 0.0f }, { 0.2,0.2 }, { 0.0,-0.20,0.0 }, sprite);
    Ball* ball7 = new Ball({ 0.3,-0.2f, 0.0f }, { 0.2,0.2 }, { -1.0,-0.20,0.0 }, sprite);
  

    tree.Insert(*ball);
    CollisionSystem::mObjects.push_back(ball2);
    CollisionSystem::mObjects.push_back(ball3);
    CollisionSystem::mObjects.push_back(ball4);
    CollisionSystem::mObjects.push_back(ball5);
    CollisionSystem::mObjects.push_back(ball6);
    CollisionSystem::mObjects.push_back(ball7);


    glDisable(GL_DEPTH_TEST); 
    glDisable(GL_CULL_FACE);  

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        {
            //Render
            glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            Renderer::DrawQuad(*ball);
            Renderer::DrawQuad(*ball2);
            Renderer::DrawQuad(*ball3);
            Renderer::DrawQuad(*ball4);
            Renderer::DrawQuad(*ball5);
            Renderer::DrawQuad(*ball6);
            Renderer::DrawQuad(*ball7);

            ball->OnUpdate();
            ball2->OnUpdate();
            ball3->OnUpdate();
            ball4->OnUpdate();
            ball5->OnUpdate();
            ball6->OnUpdate();
            ball7->OnUpdate();

            CollisionSystem::OnBoundsCollided(*ball);
            CollisionSystem::OnBoundsCollided(*ball2);
            CollisionSystem::OnBoundsCollided(*ball3);
            CollisionSystem::OnBoundsCollided(*ball4);
            CollisionSystem::OnBoundsCollided(*ball5);
            CollisionSystem::OnBoundsCollided(*ball6);
            CollisionSystem::OnBoundsCollided(*ball7);

            CollisionSystem::OnOtherCollided(*ball);

            tree.Render({ LEFT_BOUND,BOTTOM_BOUND,0.0f }, { 1.0f,1.0f }, 0);

        }
        glfwSwapBuffers(window);
    }
}

