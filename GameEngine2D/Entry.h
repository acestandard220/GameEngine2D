#include "Application.h"
#include "ECS/Scene.h"
#include "ECS/Gameobject.h"

using namespace GE2D::ECS;

int main()
{
    Application* app = new Application("GAME_ENGINE_2D", 1280, 720);
	if (app->Init())
	{
		app->Run();
	}

	delete app;

	


}