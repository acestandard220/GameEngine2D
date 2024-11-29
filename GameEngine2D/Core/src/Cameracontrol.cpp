#include "Cameracontrol.h"

#define ENGINE_BIND(x) std::bind(&OrthographicCameraController::x,this,std::placeholders::_1)
OrthographicCameraController::OrthographicCameraController(float aspectratio)
	:m_aspectratio(aspectratio),
	m_camera(-aspectratio,aspectratio,m_zoomlevel,-m_zoomlevel) , m_zoomlevel(1.0f)
{
	m_camera.SetPosition(m_cameraPosition);
}

void OrthographicCameraController::OnUpdate()
{

	

}

void OrthographicCameraController::OnEvent(Event& e)
{
	//Dispatcher:
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyEvent>(ENGINE_BIND(OnKey));
		dispatcher.Dispatch<MouseScrollEvent>(ENGINE_BIND(OnMouseScroll));
		dispatcher.Dispatch<WindowResizeEvent>(ENGINE_BIND(OnResize));
	}
}

void OrthographicCameraController::Resize(float width, float height)
{
	m_aspectratio = width/height;
	m_camera.SetProjection(-m_aspectratio, m_aspectratio, m_zoomlevel, -m_zoomlevel); std::cout << m_aspectratio << "\n";
}

void OrthographicCameraController::OnKey(KeyEvent& e)
{
	float cameraSpeed = 0.05f;
	if (e.__key == GLFW_KEY_W && e.__action == GLFW_PRESS)
	{
		m_cameraPosition.y += cameraSpeed;
	}
	if (e.__key == GLFW_KEY_S && e.__action == GLFW_PRESS)
	{
		m_cameraPosition.y -= cameraSpeed;
	}
	if (e.__key == GLFW_KEY_A && e.__action == GLFW_PRESS)
	{
		m_cameraPosition.x -= cameraSpeed;
	}
	if (e.__key == GLFW_KEY_D && e.__action == GLFW_PRESS)
	{
		m_cameraPosition.x += cameraSpeed;
	}
	if (e.__key == GLFW_KEY_ESCAPE && e.__action == GLFW_PRESS)
	{
		std::cout << "Can't quit through camera controller\n";
	}

	m_camera.SetPosition(m_cameraPosition);
}

void OrthographicCameraController::OnMouseScroll(MouseScrollEvent& e)
{

}

void OrthographicCameraController::OnResize(WindowResizeEvent& e)
{
	Resize(e.__width, e.__height);
	
}

void OrthographicCameraController::SetZoomLevel(float zoom)
{
	m_zoomlevel = zoom;
}

const float& OrthographicCameraController::GetZoomLevel() const
{
	return m_zoomlevel;
}

OrthographicCamera& OrthographicCameraController::GetCamera() 
{
	return m_camera;
}

const OrthographicCamera& OrthographicCameraController::GetCamera() const
{
	return m_camera;
}
