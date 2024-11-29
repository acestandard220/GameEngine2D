#include <Application.h>

Application* Application::APPLICATION = nullptr;



Application::Application(const char* title, int width, int height)
	:configuration("P:/Projects/VS/GameEngine2D/GameEngine2D/Core/EngineConfig.json")
{
	m_window = nullptr;
	m_eventmanager = nullptr;
	editor = nullptr;
	APPLICATION = this;

	
}

Application::~Application()
{
	Shutdown();
}
    

bool Application::Init()
{
	if (!glfwInit())
		return false;

	Configure();
	
	m_window = glfwCreateWindow(windowsproperties.__width, windowsproperties.__height, windowsproperties.__title.c_str(), NULL, NULL);
	if (!m_window)
		return false;

	glfwMakeContextCurrent(m_window);//Must be created before glewInit();

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
		return false;


	m_eventmanager = new EventManager;
	m_eventmanager->Init(m_window);
	m_eventmanager->SetEventCallBackFn(OnEvent);

	ImGuiInit();

	//PushLayer(new ExampleLayer("Example Layer"));
	PushLayer(new Test2D("Sandbox_2D_"));
	
	editor = new EditorLayer;
	PushOverLay(editor);



	return true;
}


void Application::OnEvent(Event& _event)
{
	//Pass event to layerstack
	APPLICATION->m_layerstack.OnEvent(_event);

	//Handle resize events.
	if (_event.type == EVENT_TYPE_RESIZE)
	{
		WindowResizeEvent e = *(WindowResizeEvent*)&_event;
		APPLICATION->windowsproperties.__width  = e.__width;
		APPLICATION->windowsproperties.__height = e.__height;
	}
}

void Application::Configure()
{
	configuration.EngineConfigInit();
	windowsproperties.__title = configuration.GetWindowConfig()->__title.c_str();
	windowsproperties.__height = configuration.GetWindowConfig()->__height;
	windowsproperties.__width = configuration.GetWindowConfig()->__width;
	
	editor->SetTheme(EDITOR_THEME_LIGHT);
}


bool Application::Run()
{
	//glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(m_window))
	{
		/*glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
		
	    OnUpdate();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
	
	return true;
}

void Application::Shutdown()
{
	configuration.SetConfig(&windowsproperties);

	m_layerstack.FlushLayers();
	delete editor;
	delete m_eventmanager;
	delete m_window;
    
}

void Application::PushLayer(Layer* layer)
{
	m_layerstack.PushLayer(layer);
}

void Application::PushOverLay(Layer* overlay)
{
	m_layerstack.PushOverlay(overlay);
}

void Application::PopLayer(Layer* layer)
{
	m_layerstack.PopLayer(layer);
}

void Application::OnUpdate()
{
	ImGuiBegin();
	editor->frame->Bind();

	m_layerstack.OnUpdate();

	editor->frame->UnBind();

	ImGuiEnd();
}
void Application::ImGuiInit()
{

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	io.DisplaySize.x = GetWidth();
	io.DisplaySize.y = GetHeight();

	//ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	ImGui::StyleColorsLight();


	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplGlfw_InitForOpenGL(&Application::GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 410");
}

void Application::ImGuiBegin()
{
	ImGuiIO& i_o = ImGui::GetIO();
	i_o.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	i_o.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
}

void Application::ImGuiEnd()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

