#include "Renderer2D.h"
#include "Texture.h"

struct RendererData2D
{
	VertexArrayBuffer* vao;
	IBuffer* vbo;
	IBuffer* ebo;

	Shader* shader = nullptr;
	Texture* texture;
};

RendererData2D* s_Data;


void Renderer2D::Init()
{
	s_Data = new RendererData2D;
	s_Data->vao = new VertexArrayBuffer;

	s_Data->shader = new Shader
	(
		*new ShaderSource
		("P:/Projects/VS/GameEngine2D/GameEngine2D/Core/assets/builtin_shaders/quads_vertex.glsl",
			"P:/Projects/VS/GameEngine2D/GameEngine2D/Core/assets/builtin_shaders/quads_fragment.glsl"
		)
	);
	

    float vertex_data[] = {
        -1.0,  1.0,  0.0,  /**/  0.0f, 1.0f,
         1.0,  1.0,  0.0,  /**/  1.0f, 1.0f,
         1.0, -1.0,  0.0,  /**/  1.0f, 0.0f,
        -1.0, -1.0,  0.0,  /**/  0.0f, 0.0f,
    };

    unsigned int indices[6] = {
        0,  1,  2,
        0,  3,  2
    };


	BufferLayout lay = {
		{"POSITION",FLOAT3,POSITION},
		{"TEXCORDS",FLOAT2,TEXTURE}
	};

	s_Data->vbo = IBuffer::CreateVertexBuffer(vertex_data, sizeof(vertex_data));
	s_Data->ebo = IBuffer::CreateIndexBuffer(indices, 6);
	s_Data->vbo->SetBufferLayout(lay);
	s_Data->vao->AddVertexbuffer(*s_Data->vbo);
	s_Data->vao->SetIndexbuffer(*s_Data->ebo);

	s_Data->vao->Bind();
	GAME_ENGINE_2D_OPENGL_ERROR();
  
}

void Renderer2D::BeginScene(OrthographicCamera& camera)
{
	s_Data->shader->Use();
	s_Data->shader->SetMatrix4("vp", camera.GetViewProjection());
	GAME_ENGINE_2D_OPENGL_ERROR();
}


void Renderer2D::EndScene()
{
	s_Data->vao->Bind();
	RenderCommand::DrawIndexed(*s_Data->vao);
	s_Data->vao->Unbind();
	GAME_ENGINE_2D_OPENGL_ERROR();
}

void Renderer2D::DrawQuad(glm::vec3& position,float size ,glm::vec3 color)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(size));
	model = glm::translate(model, position);

	s_Data->shader->Use();
	s_Data->shader->SetMatrix4("model", model);

	s_Data->shader->SetVec3("color", color);
	
	//GAME_ENGINE_2D_OPENGL_ERROR();

}


void Renderer2D::DrawQuad(glm::vec3& position, glm::vec3& scale, glm::vec3& rotation, glm::vec3 color)
{
	glm::mat4 model = glm::mat4(1.0f);
	
	model = glm::scale(model, scale);

	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));

	model = glm::translate(model, position);

	s_Data->shader->Use();
	s_Data->shader->SetMatrix4("model", model);

	s_Data->shader->SetVec3("color", color);

	//GAME_ENGINE_2D_OPENGL_ERROR();

}