#include "Renderer2D.h"
#include "Texture.h"

using TextureCoord = glm::vec2;
using Position     = glm::vec3;
using Colour       = glm::vec4;

struct QuadVertex
{
	Position position;
	TextureCoord texC;

};

struct RendererData2D
{
	const uint32_t MAX_QUADS = 10000;
	const uint32_t MAX_VERTICE = MAX_QUADS * 4;
	const uint32_t MAX_INDEX = MAX_QUADS * 6;
	uint32_t QuadIndexCount = 0;

	VertexArrayBuffer* vao;
	IBuffer* vbo;
	IBuffer* ebo;

	Shader* shader = nullptr;
	Texture* texture;

	bool textured = false;

	struct CameraData {
		glm::mat4 __viewprojection;

		operator glm::mat4& () { return __viewprojection; }
	};

	CameraData cameraData;

	QuadVertex* quadvertex_base;
	QuadVertex* quadvertex_ptr;
};

RendererData2D* s_Data;


void Renderer2D::Init()
{
	s_Data      = new RendererData2D;
	s_Data->vao = new VertexArrayBuffer;

	s_Data->shader = new Shader
	(
		*new ShaderSource
		(
			"P:/Projects/VS/GameEngine2D/GameEngine2D/Core/assets/builtin_shaders/quads_vertex.glsl",
			"P:/Projects/VS/GameEngine2D/GameEngine2D/Core/assets/builtin_shaders/quads_fragment.glsl"
		)
	);

	BufferLayout lay = 
	{
		{"POSITION", FLOAT3, POSITION},
		{"TEXCORDS", FLOAT2, TEXTURE},
	};

	uint32_t* dynamic_indices = new uint32_t[s_Data->MAX_INDEX];
	uint32_t offset = 0;
	for (uint32_t i = 0; i < s_Data->MAX_INDEX; i += 6)
	{
		dynamic_indices[i + 0] = offset + 0;
		dynamic_indices[i + 1] = offset + 1;
		dynamic_indices[i + 2] = offset + 2;

	    dynamic_indices[i + 3] = offset + 2;
		dynamic_indices[i + 4] = offset + 3;
		dynamic_indices[i + 5] = offset + 0;

		offset += 4;
	}
	s_Data->ebo = IBuffer::CreateIndexBuffer(dynamic_indices,s_Data->MAX_INDEX);
	s_Data->vao->SetIndexbuffer(*s_Data->ebo);
	delete[] dynamic_indices;

	s_Data->vbo = IBuffer::CreateVertexBuffer(s_Data->MAX_VERTICE);
	s_Data->vbo->SetBufferLayout(lay);
	s_Data->vao->AddVertexbuffer(*s_Data->vbo);

	s_Data->quadvertex_base = new QuadVertex[s_Data->MAX_QUADS];
	s_Data->QuadIndexCount = 0;
	
	GAME_ENGINE_2D_OPENGL_ERROR();

}

void Renderer2D::BeginScene(OrthographicCamera& camera)
{
	s_Data->cameraData.__viewprojection = camera.GetViewProjection();
	s_Data->quadvertex_ptr = s_Data->quadvertex_base;

	s_Data->shader->Use();
	s_Data->shader->SetMatrix4("vp", s_Data->cameraData);

	GAME_ENGINE_2D_OPENGL_ERROR();
}


void Renderer2D::EndScene()
{
	uint32_t dataSize = (uint8_t*)s_Data->quadvertex_ptr - (uint8_t*)s_Data->quadvertex_base;
	s_Data->vbo->SetData(s_Data->quadvertex_base, dataSize);
	Flush();
	GAME_ENGINE_2D_OPENGL_ERROR();
}

void Renderer2D::Flush()
{
	s_Data->vao->Bind();
	RenderCommand::DrawIndexed(*s_Data->vao,s_Data->QuadIndexCount);
	s_Data->vao->Unbind();
}

void Renderer2D::DrawQuad(glm::vec3& position,float size ,glm::vec3 color)
{
	//Generating data for the vertex buffer.
	{
		s_Data->quadvertex_ptr->position = position;
		s_Data->quadvertex_ptr->texC = { 0.0f,0.0f };
		s_Data->quadvertex_ptr++;

		s_Data->quadvertex_ptr->position = { position.x, position.y + size, position.z };
		s_Data->quadvertex_ptr->texC = { 0.0f,1.0f };
		s_Data->quadvertex_ptr++;

		s_Data->quadvertex_ptr->position = { position.x + size,position.y + size, position.z };
		s_Data->quadvertex_ptr->texC = { 1.0f,1.0f };
		s_Data->quadvertex_ptr++;

		s_Data->quadvertex_ptr->position = { position.x + size, position.y, position.z };
		s_Data->quadvertex_ptr->texC = { 1.0f,0.0f };
		s_Data->quadvertex_ptr++;

		s_Data->QuadIndexCount += 6;
	}

	s_Data->textured = false;
	s_Data->shader->Use();
	s_Data->shader->SetVec3("color", color);
	s_Data->shader->SetInt("textured", s_Data->textured);

}


void Renderer2D::DrawQuad(glm::vec3& position, glm::vec3& scale, glm::vec3& rotation, glm::vec3 color)
{
	{
		glm::mat4 rotation_factor;
		rotation_factor = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
		rotation_factor = glm::rotate(rotation_factor, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
		rotation_factor = glm::rotate(rotation_factor, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));

		auto rotated_position = rotation_factor * glm::vec4(position, 1.0f);
		s_Data->quadvertex_ptr->position = rotated_position;
		s_Data->quadvertex_ptr->texC = { 0.0f,0.0f };
		s_Data->quadvertex_ptr++;

		rotated_position = rotation_factor * glm::vec4( position.x, position.y + scale.y, position.z,1.0f );
		s_Data->quadvertex_ptr->position = rotated_position;
		s_Data->quadvertex_ptr->texC = { 0.0f,1.0f };
		s_Data->quadvertex_ptr++;

		rotated_position = rotation_factor * glm::vec4(position.x + scale.x, position.y + scale.y, position.z, 1.0f);
		s_Data->quadvertex_ptr->position = rotated_position;
		s_Data->quadvertex_ptr->texC = { 1.0f,1.0f };
		s_Data->quadvertex_ptr++;

		rotated_position = rotation_factor * glm::vec4(position.x + scale.x, position.y, position.z, 1.0f);
		s_Data->quadvertex_ptr->position = rotated_position;
		s_Data->quadvertex_ptr->texC = { 1.0f,0.0f };
		s_Data->quadvertex_ptr++;

		s_Data->QuadIndexCount += 6;
	}

	s_Data->textured = false;
	
	s_Data->shader->Use();
	s_Data->shader->SetVec3("color", color);
	s_Data->shader->SetInt("textured", s_Data->textured);

}

void Renderer2D::DrawQuad(glm::vec3& position, glm::vec3& scale, glm::vec3& rotation)
{

	s_Data->textured = true;
	s_Data->shader->Use();
	s_Data->shader->SetInt("textured", s_Data->textured);
}
