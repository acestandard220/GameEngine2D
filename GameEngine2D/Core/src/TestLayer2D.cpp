#include "TestLayer2D.h"
#include "SystemManager.h"
#include "Systems.h"
#include "Application.h"

void Test2D::TempImGuiStuff()
{
	ImGui::Begin("Temporary Component Editor");
	{
		auto& transform = gameObject->GetComponent<GE2D::ECS::TransformComponent>();

		ImGui::InputFloat3("Test", &transform.Position[0]);
	}
	ImGui::End();
}

using namespace GE2D;
void Test2D::OnAttach()
{
	glm::vec4 c{ 1.0,0.0,0.0,0.0 };
	scene = std::make_shared<GE2D::ECS::Scene>("TEST2D_SCENE");
	auto& coordinator = scene->GetCoordinator();

	gameObject = scene->AddGameObject();
	GE2D::ECS::TagComponent tg = { { "Spiral" } };
	gameObject->AddComponent<GE2D::ECS::TagComponent>(tg);

	tc = {
		{ 0.00f, 0.00f, 0.00f},
		{ 0.20f, 0.50f, 0.30f} ,
		{ 0.0f, 0.0f, 0.0f}
	};
	GE2D::ECS::SpriteMeshComponent sp =
	{
		{1.0,0.0,0.0,1.0}
	};

	gameObject->AddComponent<GE2D::ECS::TransformComponent>(tc);
	gameObject->AddComponent<GE2D::ECS::SpriteMeshComponent>(sp);

	//std::cout << coordinator.GetEntitySignature(gameObject->GetGameObjectID());

	std::shared_ptr<GE2D::ECS::GameObject> gameObject_2 = scene->AddGameObject();


	std::cout << gameObject->GetGameObjectName();
	
	

	source = new ShaderSource
	(
		"P:/Projects/VS/GameEngine2D/GameEngine2D/Core/assets/builtin_shaders/triangle_vertex.glsl",
		"P:/Projects/VS/GameEngine2D/GameEngine2D/Core/assets/builtin_shaders/triangle_fragment.glsl"
	);
	shader = new Shader(*source);
	

	BufferLayout* layout = new BufferLayout{
		{"Positions",FLOAT3,POSITION},
		{"Textures",FLOAT2,TEXTURE}
	};

	vao = new VertexArrayBuffer;
	vbo = IBuffer::CreateVertexBuffer(vertex_data, sizeof(vertex_data));
	ebo = IBuffer::CreateIndexBuffer(indices, 6);

	vbo->SetBufferLayout(*layout);
	vao->SetIndexbuffer(*ebo);
	vao->AddVertexbuffer(*vbo);

	Renderer2D::Init();
}

void Test2D::OnDettach()
{

}

void Test2D::OnUpdate()
{
	RenderCommand::SetClearColor({ 0.3, 0.5, 0.1, 0.7 });
	RenderCommand::ClearColorBuffer();

	Application& app = Application::GetApp();

	Renderer2D::BeginScene(app.editor->GetCamera());
	scene->OnUpdate();
	Renderer2D::EndScene();


	glm::vec3 pos{ 0.0,0.0,0.0 };
	glm::vec3 color{ 1.0,1.0,0.2 };




	glm::vec3 pos2 = glm::vec3(0.7, 0.0, 0);
	glm::vec3 pos3 = glm::vec3(0.0, 0.7, 0);
	glm::vec3 pos4 = glm::vec3(0.7, 0.7, 0);

	color = glm::vec3(1.0, 0.0, 1.0);

	//Renderer2D::BeginScene(app.editor->GetCamera());
	//Renderer2D::DrawQuad(pos, 0.5f, color);
	//Renderer2D::DrawQuad(pos2,0.5f,color);
	//Renderer2D::DrawQuad(pos3, 0.5f, color);
	//Renderer2D::DrawQuad(pos4, 0.5f, color);
	//Renderer2D::EndScene();

}

void Test2D::Key(KeyEvent& _event)
{
}

void Test2D::Mouse(MouseMoveEvent& e)
{

}

void Test2D::OnEvent(Event& _event)
{
}
