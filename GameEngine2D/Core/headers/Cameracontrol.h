#pragma once
#include "camera.h"
#include "Event.h"

class OrthographicCameraController
{
	public:
		OrthographicCameraController(float);

		void OnUpdate();
		void OnEvent(Event& e);

		void Resize(float width, float height);

		void OnKey(KeyEvent& e);
		void OnMouseScroll(MouseScrollEvent& e);
		void OnResize(WindowResizeEvent& e);
		
		void SetZoomLevel(float zoom);
		const float& GetZoomLevel()const;

		OrthographicCamera& GetCamera();

		const OrthographicCamera& GetCamera()const;
    private:
		float m_zoomlevel = 1.0f;
		OrthographicCamera m_camera;
		
		glm::vec3 m_cameraPosition{ 0.0f, 0.0f, 0.0f };
		float m_aspectratio;
		
};