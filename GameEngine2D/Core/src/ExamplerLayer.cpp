#include "ExampleLayer.h"
#include "Application.h"
#include "Engine.Config/ConfigurationManager.h"


#define ENGINE_BIND(fn) std::bind(&ExampleLayer::fn,this,std::placeholders::_1)

void ExampleLayer::OnAttach()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	texture = Texture::CreateTexture2D("C:/Users/User/Downloads/Checkerboard.png");
	lay = BufferLayout::UseDefaultLayout(POS3_TEX2);

	anothersource = new ShaderSource("P:/Projects/VS/GameEngine2D/GameEngine2D/Core/assets/builtin_shaders/quads_vertex.glsl", "P:/Projects/VS/GameEngine2D/GameEngine2D/Core/assets/builtin_shaders/quads_fragment.glsl");
	anotherShader = new Shader(*anothersource);

	sqaure_buffer = IBuffer::CreateVertexBuffer(vertex_data, sizeof(vertex_data));
	square_index = IBuffer::CreateIndexBuffer(indices, 6);
	sqaure_buffer->SetBufferLayout(*lay);
	sqaure_VAO.AddVertexbuffer(*sqaure_buffer);
	sqaure_VAO.SetIndexbuffer(*square_index);

	FramebufferSpecification spec{ 1280,720 };
	framebuffer = new Framebuffer(spec);
	

}

void ExampleLayer::OnDettach()
{

	delete texture;
	delete lay;
	delete sqaure_buffer;
	delete square_index;
	delete anotherShader;
	delete anothersource;
}

void ExampleLayer::OnUpdate()
{
	
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	Application& app = Application::GetApp();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(0.3f));
	model = glm::translate(model, glm::vec3(0.0f));
	glm::mat4 mvp = app.editor->m_cameracontrol->GetCamera().GetViewProjection();


	
	anotherShader->Use();
	anotherShader->SetInt("texture_", 0);
	texture->Bind();
	glBindTexture(GL_TEXTURE_2D,texture->GetTextureID());
	model = glm::translate(model, glm::vec3(1.2f, 1.2f, 1.0f));
	mvp = app.editor->m_cameracontrol->GetCamera().GetViewProjection();
	
	anotherShader->SetMatrix4("u_mvp", mvp);
	anotherShader->SetMatrix4("model", model);

	Renderer::BeginScene();
	//Renderer::Submit(sqaure_VAO);
	Renderer::EndScene();

	//Renderer2D test

	glm::vec3 pos = glm::vec3(25.0f, 35.0f, -1.0f);
	glm::vec3 col = glm::vec3(0.0f,  0.0f, 1.0f);



}

void ExampleLayer::Key(KeyEvent& _event)
{

}

void ExampleLayer::Mouse(MouseMoveEvent& e)
{

}

void ExampleLayer::OnEvent(Event& _event)
{
	EventDispatcher d(_event);
	d.Dispatch<KeyEvent>(ENGINE_BIND(Key));
	d.Dispatch<MouseMoveEvent>(ENGINE_BIND(Mouse));

	//Pass event to camera control

}