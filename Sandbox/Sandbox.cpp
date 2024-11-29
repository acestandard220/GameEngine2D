#include <iostream>
#include <Application.h>

class Sandbox :public Application
{
	public:
	    Sandbox() : Application("GAME_ENGINE_2D", 1280, 720) {
	    
	    }
	    ~Sandbox()
	    {
	    
	    }
};

int main()
{
	Application::APPLICATION = nullptr;
	Sandbox* app = new Sandbox;
	app->Init();
	app->Run();
	
	delete app;
}