#include "EditorLayer.h"


void EditorLayer::SetTheme(EDITOR_THEME theme)
{
	switch (theme)
	{
	case EDITOR_THEME_DARK:
		break;
	case EDITOR_THEME_LIGHT:
		break;
	case EDITOR_THEME_CLASSIC:
		break;
	default:
		break;
	}
}
void EditorLayer::OnAttach()
{
	
	FramebufferSpecification spec{
		1280,720
	};
	frame = new Framebuffer(spec);
	m_cameracontrol = new OrthographicCameraController(1280.0f / 720.0f);
}

void EditorLayer::OnDettach()
{
	delete frame;
	delete m_cameracontrol;
}

void EditorLayer::OnUpdate()
{
	RenderDockSpace();
	
	RenderPropertiesPanel();
	RenderSceneHierachyPanel();
    ImGui::ShowDemoWindow(&demo);

}

void EditorLayer::OnEvent(Event& _event)
{
	EventDispatcher dispatcher(_event);
	dispatcher.Dispatch<KeyEvent>(std::bind(&EditorLayer::OnKeyPressed,this,std::placeholders::_1));
	dispatcher.Dispatch<MouseMoveEvent>(std::bind(&EditorLayer::OnMouseMoved, this, std::placeholders::_1));
	dispatcher.Dispatch<MouseScrollEvent>(std::bind(&EditorLayer::OnMouseScrolled, this, std::placeholders::_1));
	dispatcher.Dispatch<WindowResizeEvent>(std::bind(&EditorLayer::OnWindowResize, this, std::placeholders::_1));

	m_cameracontrol->OnEvent(_event);
}


void EditorLayer::OnKeyPressed(KeyEvent& e)
{
	;
}

void EditorLayer::OnMouseMoved(MouseMoveEvent& e)
{
	;
}

void EditorLayer::OnMouseScrolled(MouseScrollEvent& e)
{

}

void EditorLayer::OnWindowResize(WindowResizeEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize.x = e.__width;
	io.DisplaySize.y = e.__height;
}

void EditorLayer::RenderPropertiesPanel()
{
	ImGui::SetNextWindowSizeConstraints(ImVec2{ 200,800 }, ImVec2{ 400,800 });
	ImGui::Begin("Properties");
	ImGui::Text("This is the properties window");
	ImGui::End();
}

void EditorLayer::RenderSceneHierachyPanel()
{
	ImGui::SetNextWindowSizeConstraints(ImVec2{ 200,800 }, ImVec2{ 400,800 });
	ImGui::Begin("Scene Hierachy");
	ImGui::Text("This is the Scene hierachy.");
	ImGui::End();
}

void EditorLayer::RenderDockSpace()
{
	static bool dockspaceOpen = true;
	static bool opt_fullscreen = true;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
	    ImGui::PopStyleVar(2);

	// Submit the DockSpace
	    ImGuiIO& io = ImGui::GetIO();
	
	    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	    {
		    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			
	    }

		ImGui::Begin("ENGINE");
		bool demo = true;
		ImGui::Text("%s", "This is a test window");
		
		ImGui::Checkbox("DEMO?", &demo);

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("ScenePort");
		ImVec2 view = ImGui::GetContentRegionAvail();
		if (m_viewPortSize != *(glm::vec2*)&view)
		{
			m_viewPortSize = { view.x,view.y };
			frame->Resize((uint32_t)view.x, (uint32_t)view.y);
			m_cameracontrol->Resize(view.x, view.y);
		}
	
		ImGui::Image(frame->GetColorAttachmentID(), ImVec2(view.x, view.y),ImVec2(0,1),ImVec2(1,0));
		
		ImGui::End();
		ImGui::PopStyleVar();

	
	ImGui::End(); // End DockSpace
  }