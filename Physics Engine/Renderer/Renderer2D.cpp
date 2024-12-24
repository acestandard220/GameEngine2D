#include "Renderer2D.h"
#include "../System/GameObject.h"

std::shared_ptr<Texture2D> Renderer::white_texture = nullptr;
glm::mat4 Renderer::view = glm::mat4(1.0f);
glm::mat4 Renderer::proj = glm::mat4(1.0f);
glm::mat4 Renderer::model = glm::mat4(1.0f);

uint32_t Renderer::vao = 0;
uint32_t Renderer::vbo = 0;
uint32_t Renderer::program = 0;

int Renderer::shared_offset = 0;
int Renderer::shared_draw_count = 6;


bool Renderer::Initialize()
{
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		//NEW
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 30 * 10000, nullptr, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	{
		uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
		glShaderSource(fragment_shader, 1, &fragment_source, nullptr);

		glCompileShader(vertex_shader);
		glCompileShader(fragment_shader);

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);

		glLinkProgram(program);


		int success;
		char infoLog[512];
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
			std::cout << infoLog;
		}

		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
			std::cout << infoLog;
		}

		glGetShaderiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(program, 512, NULL, infoLog);
			std::cout << infoLog;
		}
	}

	{
		AssetManager::LoadTexture("White Texture", "white.png");
		white_texture = AssetManager::GetTexture("White Texture");
	}

	{
		view = glm::lookAt(glm::vec3( 0.0f,0.0f,1.0f), glm::vec3( 0.0f,0.0f,0.0f ), glm::vec3( 0.0f,1.0f,0.0f ));
		proj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f);

	}

	return true;
}



void Renderer::DrawQuad(GameObject& object)
{
	VertexType* vertex_data = new VertexType[6];
	vertex_data[0].position = { object.bounds.position };
	vertex_data[0].texture_coord = { 0.0f, 0.0f };

	vertex_data[1].position = { object.bounds.position.x, object.bounds.position.y + object.bounds.size.y, 0.0f };
	vertex_data[1].texture_coord = { 0.0f, 1.0f };

	vertex_data[2].position = { object.bounds.position.x + object.bounds.size.x,object.bounds.position.y + object.bounds.size.y, 0.0f };
	vertex_data[2].texture_coord = { 1.0f, 1.0f };

	vertex_data[3].position = { object.bounds.position.x,object.bounds.position.y,0.0f };
	vertex_data[3].texture_coord = { 0.0f, 0.0f };

	vertex_data[4].position = { object.bounds.position.x + object.bounds.size.x,object.bounds.position.y,0.0f };
	vertex_data[4].texture_coord = { 1.0f, 0.0f };

	vertex_data[5].position = { object.bounds.position.x + object.bounds.size.x, object.bounds.position.y + object.bounds.size.y, 0.0f };
	vertex_data[5].texture_coord = { 1.0f, 1.0f };

	//NEW
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, shared_offset, sizeof(float) * 30, vertex_data);

	shared_draw_count += 6;
	shared_offset += sizeof(float) * 30;
	
	glUseProgram(program);

	glUniform1i(glGetUniformLocation(program, "text"), 0);
	glActiveTexture(GL_TEXTURE0);
	if (object.sprite->IsTextured())
	{
		glBindTexture(GL_TEXTURE_2D, object.sprite->GetTexture());
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, white_texture->GetID());
	}

	glUniform3f(glGetUniformLocation(program, "color"), object.sprite->GetColor().x, object.sprite->GetColor().y, object.sprite->GetColor().z);

	glm::mat4 vp = proj * view;
	glUniformMatrix4fv(glGetUniformLocation(program, "vp"), 1, GL_FALSE, &vp[0][0]);

}

void Renderer::EndScene()
{
	glDrawArrays(GL_TRIANGLES, 0, shared_draw_count);
	shared_draw_count = 0;
	shared_offset = 0;
}
