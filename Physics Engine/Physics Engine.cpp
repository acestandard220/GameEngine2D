#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

#include "Renderer/Renderer2D.h"
#include "System/GameObject.h"
#include "System/CollisionSystem.h"


#define TIMER_TRACK(name) auto name## = glfwGetTime(); 
#define TIMER_STAMP(name) std::cout<<"[TIME_STAMP:["<<#name<<"]]: "<<(glfwGetTime()-name##) <<std::endl;

#define FPS_TRACK() \
    auto fps =0;\
    auto new_frame = glfwGetTime();

#define FPS_STAMP(window,x)\
    fps++;\
    if(glfwGetTime() - new_frame >= x)\
    {\
        std::cout << "FPS: " << fps << std::endl;\
        glfwSetWindowTitle(window,std::to_string(fps).c_str());\
        fps =0;\
        new_frame = glfwGetTime();\
    }


constexpr int width  = 800;
constexpr int height = 800;
constexpr const char* title = "Physics Engine";

int main()
{
    srand(time(0));
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

    {
        if (glewInit())
        {
            std::cout << "Could not initialize Glew\n";
            return -1;
        }
    }

    {
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glViewport(0, 0, 800, 800);
    }

    {
        AssetManager::Initialize("");
        AssetManager::LoadTexture("Anime", "picture.png");
        AssetManager::LoadTexture("Ball", "ball.png");
        Renderer::Initialize();
    }

    glm::vec3 bottom_position = { 0.0,0.0,0.0f };
    glm::vec3 size(20.f);
  
    QuadTree tree(0, { LEFT_BOUND, BOTTOM_BOUND , 0.0f}, { 20.0f, 20.0 });
    Grid grids({ bottom_position,size },20);
    
	Sprite sprite({ 1.0f,1.0f,0.0f });
	sprite.LoadTexture("Ball");
	sprite.SetColor({ 1.0f,0.0f,0.0f });

    std::vector<GameObject*> balls;

    std::random_device rd; // Obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

    // Define ranges for position and velocity
    std::uniform_real_distribution<> posDist(-9.8f, 9.8f); // Position range
    std::uniform_real_distribution<> velDist(-5.0f, 5.0f);   // Velocity range

    balls.push_back(new Ball({ 1.0f, 1.0f, 0.0f }, { 0.20f, 0.20f }, { -1.32f, 1.0f, 0.0f }, sprite)); // First ball manually set

    for (int i = 1; i < 100; ++i) { 
        glm::vec3 position = { posDist(gen), posDist(gen), 0.0f }; // Random position in 2D space
        glm::vec3 velocity = { velDist(gen), velDist(gen), 0.0f }; // Random velocity in 2D space
        balls.push_back(new Ball(position, { 0.20f, 0.20f }, velocity, sprite));
    }
    CollisionSystem::mObjects = balls;


    for (auto x : balls)
        tree.Insert(*x);

    grids.Spit_Debug();

    FPS_TRACK();
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        {
            glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            //TIMER_TRACK(ON_COLLISION_OTHER);
            tree.Clear();
            for (auto x : balls)
            {
                
                Renderer::DrawQuad(*x);
                x->OnUpdate(0.005);
                CollisionSystem::OnBoundsCollided(*x);
                //CollisionSystem::OnOtherCollided(*x);

                tree.Insert(*x);
                auto c = tree.GetFriendObjects(*x);
                
                CollisionSystem::OnOtherCollided(*x, c);
            }
            Renderer::EndScene();
          
            
        }
        glfwSwapBuffers(window);
        FPS_STAMP(window,1.0);
        

        
    }
    return 4;
}

