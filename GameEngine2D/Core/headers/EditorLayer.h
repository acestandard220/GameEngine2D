#pragma once
#include "pch.h"
#include "Layer.h"
#include "Cameracontrol.h"
#include "Framebuffer.h"
#include "Renderer2D.h"
#include "Scene.h"

enum EDITOR_THEME
{
	EDITOR_THEME_DARK,
	EDITOR_THEME_LIGHT,
	EDITOR_THEME_CLASSIC
};


class EditorLayer : public Layer
{
public:
	EditorLayer() :Layer("Editor"){}
	
	virtual void OnAttach()override;
	virtual void OnDettach()override;

	void SetTheme(EDITOR_THEME);
	virtual void OnUpdate()override;
	virtual void OnEvent(Event& _event) override;

	void OnKeyPressed(KeyEvent& e);
	void OnMouseMoved(MouseMoveEvent& e);
	void OnMouseScrolled(MouseScrollEvent& e);
	void OnWindowResize(WindowResizeEvent& e);

	void RenderPropertiesPanel();

	void RenderSceneHierachyPanel();
	
	void RenderDockSpace();
	
	OrthographicCamera& GetCamera() { return m_cameracontrol->GetCamera(); }
	const OrthographicCamera& GetCamera()const { return m_cameracontrol->GetCamera(); }

	inline const std::string& GetDebugName()const {
		return m_debugname;
	}
	
	Framebuffer* frame;
	OrthographicCameraController* m_cameracontrol;

	//In Construction:
	GE2D::ECS::SceneRef sampleScene;

	glm::vec2 m_viewPortSize{ 0.0,0.0 };

private:
	bool demo;
	bool another;

};
